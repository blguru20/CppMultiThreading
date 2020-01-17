//============================================================================
// Name        : MultiThreading.cpp
// Author      : Guru
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>

std::condition_variable cv;
std::mutex cv_m;
int i = 0;


void PrintOdd(){
    std::unique_lock<std::mutex> lk(cv_m);


    while (i<=100)
    {

    	std::cout << "Waiting... \n";
    	    cv.wait(lk, []{i++; return 1 == (i % 2);});

    	    std::cout << "...finished waiting...thread Odd!  " << i << "\n";
        std::cout << "Notifying other thread : \n";
        lk.unlock();
        cv.notify_one(); // waiting thread is notified with i == 1, cv.wait returns
        std::this_thread::sleep_for(std::chrono::seconds(1));
        lk.lock();
    }
}

void PrintEven()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::unique_lock<std::mutex> lk(cv_m);

    while (1<=100)
    {

    	std::cout << "Waiting... \n";

    	cv.wait(lk, []{i++; return (i % 2) == 0;});
    	    std::cout << "...finished waiting...  ThreadEven! " << i << "\n";

        std::cout << "Notifying other thread : \n";

        lk.unlock();
        cv.notify_one(); // waiting thread is notified with i == 1, cv.wait returns
        std::this_thread::sleep_for(std::chrono::seconds(1));
        lk.lock();
    }
}

int main()
{
    std::thread t1(PrintEven), t2(PrintOdd);
    t1.join();
    t2.join();
}
