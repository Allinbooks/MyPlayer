#include "MMThread.h"
using namespace std;

int MMThread::Start()
{
	if (t == nullptr) {
		stopFlag = 0;
		t = new thread(&MMThread::run, this);
	}
	//t.detach();
	return 0;
}

int MMThread::Stop()
{
	if (t != nullptr) {
		stopFlag = 1;
		t->join();  // ȷ�����߳�ִ��������ͷ�
		delete t;
		t = nullptr;
	}
	return 0;
}