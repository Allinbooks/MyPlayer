#include "MMplayer.h"

MMplayer::MMplayer(std::string _path) {
	path = _path;
}


MMplayer::~MMplayer() {


}

int MMplayer::Open() {
	

	if (readerThread == nullptr) {
		MMPlayerReaderThread* readerThread = new MMPlayerReaderThread(path);
		readerThread->Start();

		return 0;
	}
	
	return -1;
}


int MMplayer::Stop() {
	if (readerThread != nullptr) {
		readerThread->Stop();
		readerThread = nullptr;
	}
	return 0;
}

int MMplayer::Play() {

	return 0;
}

int MMplayer::Pause() {

	return 0;
}

int MMplayer::Seek(double time) {

	return 0;
}