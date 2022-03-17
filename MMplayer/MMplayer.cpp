// MMplayer.cpp: 定义应用程序的入口点。
//

#include "MMplayer.h"
#include "MMThread/MMThread.h"
using namespace std;

static void threadfun(int m) {
	while (true)
	{
		cout << "hello world" << m << endl;
	}
	
}

void threadfunction(int i) {
	while (true) {
		cout << "xiaoming " << i << endl;
	}
}
class MyMMThread : public MMThread
{
public:
	virtual void run()
	{
		printf("MyMMThread\n");
	}
};
int main()
{
	//thread t(threadfun, 1);
	//thread h(threadfunction, 2);
	//t.join();
	//h.join();
	////t.detach();
	////t.joinable();

	MyMMThread t;
	t.Start();
	this_thread::sleep_for(chrono::seconds(2));
	cout << "Hello MMplayer." << endl;
	return 0;
}
