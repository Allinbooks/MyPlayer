cmake_minimum_required (VERSION 3.8)

include_directories(../3rdpart/ffmpeg/include)

add_library(
	MMAV
	MMAVPacket.cpp
	MMAVReader.cpp
	MMAVDecoder.cpp
	MMAVStream.cpp
	MMAVFrame.cpp)