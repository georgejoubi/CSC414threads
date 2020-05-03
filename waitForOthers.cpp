
#include <iostream>
#include <condition_variable>
#include <random>
#include <mutex>
#include <chrono>
#include <string>
#define SYNC

int num_threads = 10;
int count = num_threads;
std::condition_variable cv;
std::mutex m;
std::default_random_engine e;
std::uniform_int_distribution<> id(1, 2000);

void thread(std::string s) {

#ifdef SYNC
    std::unique_lock<std::mutex> lock(m);
#endif // SYNC

    std::this_thread::sleep_for(std::chrono::milliseconds(id(e)));
    std::cout << "phase 1 " << std::endl;
    count--;


#ifdef SYNC
    cv.wait(lock, [] {return (count <= 0) ? true : false; });
#endif // SYNC

    std::this_thread::sleep_for(std::chrono::milliseconds(id(e)));

    std::cout << s << " is done" << std::endl;
#ifdef SYNC
    cv.notify_all();
#endif // SYNC
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
