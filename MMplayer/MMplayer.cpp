#include "MMplayer.h"

MMplayer::MMplayer(std::string _path) {
	path = _path;
}


MMplayer::~MMplayer() {


}

int MMplayer::Open(double time) {
	

	/*if (readerThread == nullptr) {
		MMPlayerReaderThread* readerThread = new MMPlayerReaderThread(path);
		readerThread->Start();

		return 0;
	}*/
	
	if (playerCtr == nullptr) {
		playerCtr = new MMPlayerCtr(time);
		playerCtr->Start();

		return 0;
	}


	return -1;
}


int MMplayer::Stop() {
	/*if (readerThread != nullptr) {
		readerThread->Stop();
		readerThread = nullptr;
	}*/

	if (playerCtr != nullptr) {
		playerCtr->Stop();
		delete playerCtr;
		playerCtr = nullptr;
	}

	return 0;
}

int MMplayer::Play() {
	if (playerCtr != nullptr) {
		playerCtr->Play();
	}
	return 0;
}

int MMplayer::Pause() {
	if (playerCtr != nullptr) {
		playerCtr->Pause();
	}
	return 0;
}

int MMplayer::Seek(double time) {
	Stop();
	Open(time);
	return 0;
}