#include "MMplayer/MMplayer.h"
#include <windows.h>

int main() {
	MMplayer player("A:/videoTemplate.mp4");
	int ret = player.Open();
	if (ret) {
		printf("Player Open Fail\n");
	}
	
	std::this_thread::sleep_for(std::chrono::seconds(10));
	/*Sleep(100000);*/

	player.Play();

	//.........wait

	player.Pause();

	//.........wait
	
	player.Play();

	//.........wait

	player.Stop();

	return 0;
}