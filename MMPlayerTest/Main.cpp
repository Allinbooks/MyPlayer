#include "MMplayer/MMplayer.h"
#include <windows.h>

int main() {
	MMplayer player("A:/44315a0bc6fb773fc280f0cb97bedde6.mp4");
	int ret = player.Open();
	if (ret) {
		printf("Player Open Fail\n");
	}
	
	Sleep(100000);

	player.Play();

	//.........wait

	player.Pause();

	//.........wait
	
	player.Play();

	//.........wait

	player.Stop();

	return 0;
}