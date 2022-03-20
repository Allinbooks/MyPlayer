# CMakeList.txt: MMplayer 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

include_directories(../)
link_directories(../3rdpart/ffmpeg/lib)

# 将源代码添加到此项目的可执行文件。
add_executable (MMplayer "MMplayer.cpp" "MMplayer.h")


target_link_libraries(MMplayer MMThread)
target_link_libraries(MMplayer MMAV)


target_link_libraries(MMplayer avcodec)
target_link_libraries(MMplayer avdevice)
target_link_libraries(MMplayer avformat)
target_link_libraries(MMplayer avutil)
target_link_libraries(MMplayer postproc)
target_link_libraries(MMplayer swresample)
target_link_libraries(MMplayer swscale)
target_link_libraries(MMplayer avfilter)

# TODO: 如有需要，请添加测试并安装目标。
