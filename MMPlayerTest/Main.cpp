#include "MMplayer/MMplayer.h"
#include <windows.h>

int main() {
	// long long t = MMAVTime::GetTime();
	// printf("t:%lld\n", t);

	MMplayer player("A:/videoTemplate.mp4");
	int ret = player.Open();
	if (ret) {
		printf("Player Open Fail\n");
		return -1;
	}

	player.Play();
	printf("===============1 PLAY===============\n");

	//.........wait
	std::this_thread::sleep_for(std::chrono::seconds(1));

	player.Seek(4.5);
	std::this_thread::sleep_for(std::chrono::seconds(2));

	player.Pause();
	printf("===============1 PAUSE===============\n");

	//.........wait
	std::this_thread::sleep_for(std::chrono::seconds(1));

	player.Play();
	printf("===============2 PLAY===============\n");

	//.........wait
	std::this_thread::sleep_for(std::chrono::seconds(2));


	player.Pause();
	printf("===============2 PAUSE===============\n");

	//.........wait
	std::this_thread::sleep_for(std::chrono::seconds(10));

	player.Play();

	//.........wait
	std::this_thread::sleep_for(std::chrono::seconds(1));

	player.Stop();

	return 0;
}