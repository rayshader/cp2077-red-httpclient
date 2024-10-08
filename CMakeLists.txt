cmake_minimum_required(VERSION 3.27)
project(RedHttpClient VERSION 0.4.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

configure_file(src/Config.h.in Config/Config.h)

set(INC_FILES
        src/AsyncHttpClient.h
        src/HttpCallback.h
        src/HttpClient.h
        src/HttpHeader.h
        src/HttpMethod.h
        src/HttpMultipart.h
        src/HttpPair.h
        src/HttpPlugin.h
        src/HttpResponse.h
        src/HttpStatus.h

        src/Settings.h
)

set(SRC_FILES
        src/main.cpp

        src/AsyncHttpClient.cpp
        src/HttpClient.cpp

        src/HttpPlugin.cpp
)

source_group(include FILES INC_FILES)
source_group(source FILES SRC_FILES)

add_library(RedHttpClient SHARED
        ${INC_FILES}
        ${SRC_FILES}
)

target_include_directories(RedHttpClient PRIVATE src/)

# Include configured files
target_include_directories(RedHttpClient PUBLIC "${PROJECT_BINARY_DIR}/Config")

# Exclude unused Windows headers
add_compile_definitions(WIN32_LEAN_AND_MEAN)

## Library RED4ext.SDK
option(RED4EXT_HEADER_ONLY "" ON)
add_subdirectory(deps/RED4ext.SDK)
set_target_properties(RED4ext.SDK PROPERTIES FOLDER "Dependencies")
mark_as_advanced(RED4EXT_BUILD_EXAMPLES RED4EXT_HEADER_ONLY)
##

## Library RedLib
add_compile_definitions(NOMINMAX)
add_subdirectory(deps/RedLib)
set_target_properties(RedLib PROPERTIES FOLDER "Dependencies")
##

## Library cpr
include(FetchContent)
FetchContent_Declare(cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 3b15fa82ea74739b574d705fea44959b58142eb8)
FetchContent_MakeAvailable(cpr)
##

## Library RedData
add_subdirectory(deps/RedData)
set_target_properties(RedData PROPERTIES FOLDER "Dependencies")
##

## Library RedFileSystem
add_subdirectory(deps/RedFileSystem)
set_target_properties(RedFileSystem PROPERTIES FOLDER "Dependencies")
##

target_link_libraries(RedHttpClient PRIVATE
        RED4ext::SDK
        RedLib
        RedData
        RedFileSystem
        cpr::cpr
)

## Debug mode: install scripts (+ tests) and plugin in game folder.
## Release mode: create archive with bundled scripts and plugin.
add_custom_command(
        TARGET RedHttpClient
        POST_BUILD
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "$<$<CONFIG:Debug>:Install scripts with red-cli>" "$<$<CONFIG:Release>:Build archive with red-cli>"
        COMMAND "$<$<CONFIG:Debug>:red-cli;install>" "$<$<CONFIG:Release>:red-cli;pack>"
        COMMAND_EXPAND_LISTS
)