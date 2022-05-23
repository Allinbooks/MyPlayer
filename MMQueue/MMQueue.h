#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <queue>
#include <mutex>
// template实现是在编译阶段，因此要在头文件进行函数实现

/*
MMQueue<MMAVFrame> queue
MMQueue<MMAVPacket> queue
*/
template<typename T>
class MMQueue
{
public:
	MMQueue() {

	}

	~MMQueue() {
		std::lock_guard<std::mutex> lck(mut);
		while (Size() > 0) {
			queue.pop();
		}
	}

	int Push(T* t) {
		std::lock_guard<std::mutex> lck(mut);
		queue.push(t);
		return 0;
	}

	int Pop(T** t) {
		std::lock_guard<std::mutex> lck(mut);
		int size = Size();
		if (size > 0) {
			*t = queue.front();
			queue.pop();
			return 0;
		}
		return -1;
	}

	int Size() {
		return queue.size();
	}

private:
	std::queue<T *> queue;
	std::mutex mut;
	// std::recursive_mutex mut;
};