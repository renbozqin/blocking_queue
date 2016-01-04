#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include "blocking_queue.h"

#include <sys/time.h>

static double getMS(){
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return tv.tv_sec*1000.0 + tv.tv_usec/1000.0;
}

const size_t queueSize = 10;

template<typename T>
void thread1(BlockingQueue<T> &queue){
	for(int i = 0; i < queueSize; ++i){
		queue.Put(i);
		std::this_thread::sleep_for(std::chrono::milliseconds(18));
	}
}

template<typename T>
void thread2(BlockingQueue<T> &queue, BlockingQueue<T>& queue2){
	int k = 0;
	while(1){
	while(queue.Size()){
		T front = queue.Take();
		queue2.Put(front);
		std::this_thread::sleep_for(std::chrono::milliseconds(37));
		k++;
	}
	if(k==queueSize) break;}
}

template<typename T>
void thread3(BlockingQueue<T>& queue){
	int k = 0;
	while(1){
	while(queue.Size()){
		queue.Take();
		std::this_thread::sleep_for(std::chrono::milliseconds(18));
		k++;
	}
	if(k==queueSize)break;}
}

int main(int argc, char* argv[]){

	BlockingQueue<int> queue;
	BlockingQueue<int> queue2;

	double st = getMS();
	std::thread t1(thread1<int>,std::ref(queue));
	std::thread t2(thread2<int>,std::ref(queue),std::ref(queue2));
	std::thread t3(thread3<int>,std::ref(queue2));

	t1.join();
	t2.join();
	t3.join();
	double et = getMS();
	std::cout << "Muil threads use time: " << et-st << "ms" << std::endl;

	st = getMS();
	thread1(queue);
	thread2(queue,queue2);
	thread3(queue2);
	et = getMS();
	std::cout << "Single thread use time: " << et-st << "ms" << std::endl;

	return 0;
}

