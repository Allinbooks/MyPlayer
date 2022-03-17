#pragma once
#include <thread>
class MMThread
{
public:
	virtual void run() = 0;
	int Start();
};