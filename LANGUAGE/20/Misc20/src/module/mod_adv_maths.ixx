
//export module mod_adv_maths; -> default come to me
//export void MyFunc();

export module AdvancedMathematics;


export auto plus_int(auto x, auto y) -> decltype(x + y) {
    return x + y;
}
export namespace AdvancedMathematics {
    auto minus(auto x, auto y) -> decltype(x - y) {
        return x - y;
    }
}
void this_function_will_not_be_exported() {}
