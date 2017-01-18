cmake_minimum_required(VERSION 3.6)
project(APex4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system log)
include_directories(${Boost_INCLUDE_DIR})
add_definitions(-DBOOST_ALL_DYN_LINK)

set(core_sockets sockets/Socket.cpp sockets/Socket.h sockets/Udp.cpp sockets/Udp.h sockets/Tcp.cpp sockets/Tcp.h)
add_library(sockets ${core_sockets})

set(SOURCE_FILES_CLIENT src/Client.h src/Client.cpp src/Point.h src/Point.cpp src/BFS.cpp src/BFS.h src/Node.cpp src/Node.h
        src/Grid.cpp src/Grid.h src/Driver.cpp src/Driver.h src/Passenger.h src/Passenger.cpp
        src/TripInfo.h src/TripInfo.cpp src/TaxiCenter.h src/TaxiCenter.cpp src/Cab.h src/Cab.cpp
        src/StandardCab.h src/StandardCab.cpp src/LuxuryCab.h src/LuxuryCab.cpp src/MainFlow.h
        src/MainFlow.cpp src/Color.h src/Manufacturer.h src/MaritalStatus.h src/ThreadClient.cpp src/ThreadClient.h)

set(SOURCE_FILES_SERVER src/Server.cpp src/Point.h src/Point.cpp src/BFS.cpp src/BFS.h src/Node.cpp src/Node.h
        src/Grid.cpp src/Grid.h src/Driver.cpp src/Driver.h src/Passenger.h src/Passenger.cpp
        src/TripInfo.h src/TripInfo.cpp src/TaxiCenter.h src/TaxiCenter.cpp src/Cab.h src/Cab.cpp
        src/StandardCab.h src/StandardCab.cpp src/LuxuryCab.h src/LuxuryCab.cpp src/MainFlow.h
        src/MainFlow.cpp src/Color.h src/Manufacturer.h src/MaritalStatus.h)

add_executable(Server ${SOURCE_FILES_SERVER})
add_executable(Client ${SOURCE_FILES_CLIENT})

target_link_libraries(Server sockets ${Boost_LIBRARIES})
target_link_libraries(Client sockets ${Boost_LIBRARIES})