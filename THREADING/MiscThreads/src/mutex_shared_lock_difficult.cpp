#include <iostream>
using namespace std;

/*
    1. std::shared_lock
   
*/
void run_shared_lock();
//
#include <mutex>
#include <shared_mutex>
#include <array>
#include <optional>
#include <chrono>
#include <thread>
#include <iostream>

struct Data {};
struct RecentSnapshots {
    void push(const Data& data) {
        // We are about to modify the data, grab a unique_lock
        std::unique_lock lock(mux_);
        buffer_[offset_ % 64] = data;
        ++offset_;
    }
    std::optional<Data> get(size_t index) const {
        // We only read, but need to prevent concurrent writes, grab a shared_lock
        std::shared_lock lock(mux_);
        if (index >= offset_)
            return std::nullopt;
        if (offset_ >= 64 && offset_ - 64 > index)
            return std::nullopt;
        return buffer_[index % 64];
    }
    size_t min_offset() const {
        // We only read, but need to prevent concurrent writes, grab a shared_lock
        std::shared_lock lock(mux_);
        if (offset_ <= 64) return 0;
        return offset_ - 64;
    }
private:
    // We need mutable, since we mutate the state
    // of this mutex (by grabbing a lock) in const methods (like const unlock_shared() called at destructor).
    mutable std::shared_mutex mux_;
    //mutable std::mutex mux_;
    std::array<Data, 64> buffer_;
    size_t offset_ = 0;
};

void run_shared_lock() {
    using namespace std::chrono_literals;
    RecentSnapshots snapshots;

    // Writer that generates snapshots
    auto thobj = std::jthread([&snapshots](std::stop_token stop) {
        while (!stop.stop_requested()) {
            std::this_thread::sleep_for(100ms);
            snapshots.push(Data{});
        }
        });
    // Run for two seconds.
    auto deadline = std::chrono::system_clock::now() + 0.5s;

    while (true) {
        if (std::chrono::system_clock::now() > deadline)
            break;

        // Start two readers that will concurently read snapshots.
        int r1_cnt = 0;
        auto r1 = std::jthread([&snapshots, &r1_cnt]() {
            size_t offset = snapshots.min_offset();
            for (size_t i = offset; i < offset + 64; i++)
                r1_cnt += snapshots.get(i) != std::nullopt;
            });
        int r2_cnt = 0;
        auto r2 = std::jthread([&snapshots, &r2_cnt]() {
            size_t offset = snapshots.min_offset();
            for (size_t i = offset; i < offset + 64; i++)
                r2_cnt += snapshots.get(i) != std::nullopt;
            });
        r1.join();
        r2.join();
        // Note: join() introduces a synchronization point, meaning that
        // the main thread can now safely read r1_cnt and r2_cnt despite
        // these variables not being atomic.

        std::cout << "First reader read " << r1_cnt << " snapshots\n";
        std::cout << "Second reader read " << r2_cnt << " snapshots\n";
        std::this_thread::sleep_for(50ms);
    }

    // Stop the writer
    thobj.request_stop();
}

//int main() {
//    run_shared_lock();
//}
/*
    First reader read 0 snapshots
    Second reader read 0 snapshots
    First reader read 0 snapshots
    Second reader read 0 snapshots
    First reader read 1 snapshots
    Second reader read 1 snapshots
    First reader read 1 snapshots
    Second reader read 1 snapshots
    First reader read 2 snapshots
    Second reader read 2 snapshots
    First reader read 2 snapshots
    Second reader read 2 snapshots
    First reader read 3 snapshots
    Second reader read 3 snapshots
    First reader read 4 snapshots
    Second reader read 4 snapshots
*/

