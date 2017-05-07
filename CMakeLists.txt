cmake_minimum_required(VERSION 3.7)
project(p2pchatc)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c peer.c peer.h message.h aes.c aes.h sha256.c sha256.h)
add_executable(p2pchatc ${SOURCE_FILES} peer.c peer.h aes.c sha256.c sha256.h)
target_link_libraries(p2pchatc pthread)
if(WIN32)
    target_link_libraries(p2pchatc wsock32 ws2_32)
endif()