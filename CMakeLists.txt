cmake_minimum_required(VERSION 3.25)
project(VirtualNetworkSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SourceFiles "src/*.cpp")

include_directories(include)

add_executable(virtualnetworksimulator ${SourceFiles})