#include "MMThread.h"
using namespace std;

int MMThread::Start()
{
	thread t(&MMThread::run,this);
	t.detach();
	return 0;
}