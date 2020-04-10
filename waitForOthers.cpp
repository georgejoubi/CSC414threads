#include <iostream>
#include <condition_variable>
#include <random>
#include <mutex>
#include <chrono>
#include <string>

int num_threads = 10;
std::default_random_engine e;
std::uniform_int_distribution<> id(1,2000);

void thread(std::string s) {
     std::this_thread::sleep_for(std::chrono::milliseconds(id(e)));
     std::cout << "phase 1 " << std::endl;

     std::this_thread::sleep_for(std::chrono::milliseconds(id(e)));

     std::cout << s << " is done" << std::endl;

}
int main()
{
   
    std::vector<std::thread> mythreads;
    for (int i = 0; i < num_threads; i++) {
        mythreads.push_back(std::thread(thread, std::to_string(i)));
    }
    for (auto& t : mythreads)
        t.join();
  
}
