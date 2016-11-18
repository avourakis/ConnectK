#include <iostream>
#include <atomic>
#include <time.h>
#include <thread>
#include <chrono>
#include <future>


int minimax2(std::atomic<int>& done, std::atomic<int>& time)
{
        for (int i =0; i < 10000000; i++)
        {    
            if(done)
            {   
                std::cout << "Child is done " << time<< std::endl;
                break;
            }
            std::cout << "Hello World" << std::endl;
        }
        std::this_thread::yield();
        return 2;
}

void minimax(std::atomic<int>& done, std::atomic<int>& time)
{
        for (int i =0; i < 10000000; i++)
        {    
            if(done)
            {   
                std::cout << "Child is done " << time<< std::endl;
                break;
            }
            std::cout << "Hello World" << std::endl;
        }
        std::this_thread::yield();
}


int main()
{
    using namespace std::chrono;

    std::atomic<int> done{0};
    //clock_t start = clock();
    //std::atomic<clock_t> now;
    std::atomic<int> timeElapsed;
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

    auto future = std::async(minimax2, std::ref(done), std::ref(timeElapsed));
    //std::thread thread1(minimax, std::ref(done), std::ref(timeElapsed));
    
    while(!done)
    {
        //now = clock() - start;
        std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
        std::chrono::milliseconds mill = duration_cast<std::chrono::milliseconds>(t2 - t1);
        timeElapsed = mill.count();
        if( mill.count() >= 4000 && !done)
        {
            done = 1;
            std::cout << "Time elapsed: " << mill.count() << std::endl;
        }
    }

    std::cout << "The return value is: " << future.get() << std::endl;
    //thread1.join();
    return 0;
}
