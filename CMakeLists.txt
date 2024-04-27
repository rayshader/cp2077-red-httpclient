cmake_minimum_required(VERSION 3.27)
project(RedHttpClient VERSION 0.3.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_library(RedHttpClient INTERFACE)
target_compile_definitions(RedHttpClient INTERFACE HAS_REDHTTPCLIENT)
target_include_directories(RedHttpClient INTERFACE include)