

#include <iostream>
#include <thread>
#include <mutex>
#include <random>

//uncomment line below to get correct result
//#define SYNC
int y = 0;
int num_iterations = 100000;
int num_trials=10;
std::mutex m;
#define INC 1
#define DEC -1
int gcd(int a,int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}
void doit(int a, int b,int op) {
    for (int i = 0; i < num_iterations; i++) {
        gcd(a, b);
#ifdef SYNC
        std::lock_guard<std::mutex> g(m);
#endif      
        op>=0?y++:y--;

    }
}
class funcObject {
    int& _x;
    int _a, _b, _op;
public:
    funcObject(int& x, int a, int b,int op) 
        :_x(x), _a(a), _b(b),_op(op) {}
    void operator() () {
        for (int i = 0; i <num_iterations; i++) {
            gcd(_a, _b);
#ifdef SYNC
            std::lock_guard<std::mutex> g(m);
#endif    
           _op>=0?_x++:_x--;
        }

    }
};

int main()
{
    int a, b;
    std::default_random_engine e;
    std::uniform_int_distribution<int> id(100000, 1000000);
    a = id(e);
    b = id(e);
    for (int j = 0; j <num_trials; j++) {
        std::vector<std::thread > mythreads;
        int x = 0;
        y = 0;
        funcObject c(x, a, b,INC);
        std::thread t1(c);
        std::thread t2(doit, a, b,INC);
        /* below will not work because a
           vector will attempt to make a copy
           of t1 and t2 and the copy constructor
           for the thread class is deleted
        mythreads.push_back(t1);
        mythreads.push_back(t2);
        */
        mythreads.push_back(std::move(t1));
        mythreads.push_back(std::move(t2));
        mythreads.push_back(
            std::thread(funcObject(x,a,b,DEC)));
        mythreads.push_back(
           std::thread(doit, a, b,DEC));
        
        for (auto& t : mythreads)
            t.join();
        
        std::cout << "trial " << j << ",x=" << x << ",y=" <<y << std::endl;

    }

}
