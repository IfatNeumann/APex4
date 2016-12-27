cmake_minimum_required(VERSION 3.6)
project(APex4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/Point.h src/Point.cpp src/BFS.cpp src/BFS.h src/Node.cpp src/Node.h
        src/Grid.cpp src/Grid.h src/Driver.cpp src/Driver.h src/Passenger.h src/Passenger.cpp
        src/TripInfo.h src/TripInfo.cpp src/TaxiCenter.h src/TaxiCenter.cpp src/Cab.h src/Cab.cpp
        src/StandardCab.h src/StandardCab.cpp src/LuxuryCab.h src/LuxuryCab.cpp src/MainFlow.h
        src/MainFlow.cpp src/Color.h src/Manufacturer.h src/MaritalStatus.h src/Client.cpp src/Server.cpp
        sockets/Socket.cpp sockets/Socket.h sockets/Udp.cpp sockets/Udp.h)
add_executable(APex4 ${SOURCE_FILES})

add_executable(Server src/Server.cpp)
add_executable(Client src/Client.cpp)

target_link_libraries(Server sockets)
target_link_libraries(Client sockets)