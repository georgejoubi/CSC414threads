// readersWriters.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <mutex>
#include <chrono>
#include <shared_mutex>

std::random_device e;
std::uniform_int_distribution<> dist(1,9);
std::vector<int> v;
#define DATA_SIZE 100
#define NUM_TRIALS 10

/* Readers writer setup. The common data is the 
 * vector of integers v. The writers write a random
 * value from 1 to 9 and the next its negative such
 * that the total sum is 0. for example
 * [2,-2,2,-2,2,-2....]
 * The readers check that the sum in the vector is zero
 * if not it will print the sum (which means data is corrupted)
 */
/* You must not remove any of the code below. ADD to it sync
 * primites so it works. Basically using c++ to implement the
 * solution we saw in class (it is in the lecture notes)
 */
class Reader {
public:
    static int num;
    void operator() () {
        int sum = 0;
        for (auto x : v) {
            sum += x;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        if(sum!=0) std::cout<< "sum is " << sum << std::endl;
    }
};

class Writer {
   
public:
    Writer() {
   }
    void operator() () {
        int value = dist(e);

        for (auto& x : v) {
            x = value;
            value = -value;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
};

int main()
{
    int value = 1;
    for (int i = 0; i < DATA_SIZE; i++) {
        v.push_back(value);
        value = -value;
    }
    for (int i = 0; i < NUM_TRIALS; i++) {
        std::cout << "Trial " << i << std::endl;
        std::vector<std::thread> mythreads;
        for(int i=0;i<5;i++){
            Reader r1, r2;
            Writer w;
            std::thread t1(r1);
            std::thread t2(w);
            std::thread t3(r2);
            mythreads.push_back(std::move(t1));
            mythreads.push_back(std::move(t2));
            mythreads.push_back(std::move(t3));
        }
       for (auto& t : mythreads)
            t.join();
        std::cout << "----------------" << std::endl;
    }
    
   
}
