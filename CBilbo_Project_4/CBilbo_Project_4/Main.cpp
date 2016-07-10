#include<vector>
#include<thread>
#include<string>
#include<iostream>
#include<mutex>
using namespace std;

class Counter	//counter class
{
public:
	std::mutex mutex;	//mutex class
	int value;	//declares value variable

	 Counter() : value(0)
	 {
	 }

	 void increment()	//function that locks and unlocks mutex
	 {
		 mutex.lock();	//locks mutex and blocks execution unless lock aquired
		 ++value;	//adds 1 to value
		 mutex.unlock();	//unlocks mutex and allowas execution
	 }
};

int main()
{
	Counter counter;	//initialize counter object

	std::vector<std::thread> threads;

	for (int i = 0; i < 5; ++i)
	{
		threads.push_back(std::thread([&counter]()
		{
			for (int i = 0; i < 5000; ++i)
			{
				counter.increment();
			}
		}));
	}

	for (auto & thread : threads)
	{
		thread.join();
	}

	std::cout << counter.value << std::endl;	//displays counter value

	system("pause");
	return 0;
}