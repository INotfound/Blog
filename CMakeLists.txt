cmake_minimum_required(VERSION 3.0)
project(Web)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32 AND NOT MINGW)
    message("~~~~~~~~~WIN32 Configuration~~~~~~~~")
elseif(WIN32 AND MINGW)
    message("~~~~~~~~~MINGW Configuration~~~~~~~~")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g2")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb")
elseif(UNIX AND NOT ANDROID)
    message("~~~~~~~~~UNIX Configuration~~~~~~~~~")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g2")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()


set(SRC
    Build.cpp
)

include_directories(Include)

#Magic
add_subdirectory(../Magic Magic.out)
include_directories(../Magic/Include)
#Gzip
include_directories(../Magic/ThirdParty/Gzip)
#ASIO
include_directories(../Magic/ThirdParty/Asio/asio/include)
#RapidJSON
include_directories(../Magic/ThirdParty/RapidJSON/include)

add_executable(WebServer ${SRC})
target_link_libraries(WebServer Magic)