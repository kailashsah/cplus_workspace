#include <iostream>
using namespace std;

// https://leetcode.com/problems/gas-station/
/*
There are n gas stations along a circular route, where the amount of gas at the ith station is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from the ith station to its next (i + 1)th station. You begin the journey with an empty tank at one of the gas stations.

Given two integer arrays gas and cost, return the starting gas station's index if you can travel around the circuit once in the clockwise direction, otherwise return -1. If there exists a solution, it is guaranteed to be unique



Example 1:

Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
Output: 3
Explanation:
Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 4. Your tank = 4 - 1 + 5 = 8
Travel to station 0. Your tank = 8 - 2 + 1 = 7
Travel to station 1. Your tank = 7 - 3 + 2 = 6
Travel to station 2. Your tank = 6 - 4 + 3 = 5
Travel to station 3. The cost is 5. Your gas is just enough to travel back to station 3.
Therefore, return 3 as the starting index.
Example 2:

Input: gas = [2,3,4], cost = [3,4,3]
Output: -1
Explanation:
You can't start at station 0 or 1, as there is not enough gas to travel to the next station.
Let's start at station 2 and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 0. Your tank = 4 - 3 + 2 = 3
Travel to station 1. Your tank = 3 - 3 + 3 = 3
You cannot travel back to station 2, as it requires 4 unit of gas but you only have 3.
Therefore, you can't travel around the circuit once no matter where you start.

*/
// ...........................................
#include <vector>

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int start{};
        int sum{};
        int round2{};
        int start_nxt_itr{};
        size_t count{gas.size()};
        for (int i{}; i < count; ++i) {
            //if (i == 0)
                sum += gas[i] - cost[i];
            //else
                //sum += gas[i] - cost[i - 1];

            if (start_nxt_itr == 2 && i == start) {
                // if it reaches back
                return i;
            }
            if(start_nxt_itr == 1) start_nxt_itr++;
            if (sum < 0) {
                // if car is out of gas
                start++;
                i = start-1;
                sum = {};
                round2 = {};
                start_nxt_itr == 1;

            }
            if (i == count - 1) {
                // if there is reverse/back itreration
                round2++;
                i = -1;
            }
            if (start == count - 1)
                return -1;
            
           
        }

    }

    int canCompleteCircuit_copied(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        int total_surplus = 0;
        int surplus = 0;
        int start = 0;

        for (int i = 0; i < n; i++) {
            total_surplus += gas[i] - cost[i];
            surplus += gas[i] - cost[i];
            if (surplus < 0) {
                surplus = 0;
                start = i + 1;
            }
        }
        return (total_surplus < 0) ? -1 : start;
    }
};

void run_gas_station() {
    vector<int> gas{ 2,3,4 };
    vector<int> cost{ 3,4,3 };
    Solution obj;
    cout << "output -1: " << obj.canCompleteCircuit_copied(gas, cost) << endl; // output -1
    //
    //gas = [], cost = []
    vector<int> gas2{ 1, 2, 3, 4, 5 };
    vector<int> cost2{ 3, 4, 5, 1, 2 };
    Solution obj2;
    cout << "output 3: "<< obj2.canCompleteCircuit_copied(gas2, cost2); // output 3
}

//int main()
//{
//	run_gas_station();
//}

