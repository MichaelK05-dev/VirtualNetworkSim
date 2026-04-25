cmake_minimum_required(VERSION 3.25)
project(VirtualNetworkSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SourceFiles 
    src/CommandManager.cpp
    src/main.cpp
    src/LAN.cpp
    src/CreateCommand.cpp
    src/NetworkManager.cpp
    src/Node.cpp
    src/Parser.cpp
    src/NetworkInterface.cpp
    src/PC.cpp
    src/ListCommand.cpp
    )

include_directories(include)

add_executable(virtualnetworksimulator ${SourceFiles})