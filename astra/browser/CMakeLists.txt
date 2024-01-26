cmake_minimum_required(VERSION 3.27)
project(astra)

include_directories(astra, include)
include_directories(astra, vendor/webview2/include)
include_directories(astra, vendor/will/include)

set(CMAKE_CXX_STANDARD 20)

add_executable(astra source/main.cpp
        include/astra/astra.h
        source/astra.cpp
        include/astra/base.h
)

target_link_libraries(astra PRIVATE
        WebView2Loader.dll
)

target_link_libraries(astra PRIVATE
        WebView2Loader.lib
)

set(WEBVIEW_LIB_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/webview2/x64/WebView2Loader.dll
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/webview2/x64/WebView2Loader.lib
)

set(TOOLBAR_UI
        ${CMAKE_CURRENT_SOURCE_DIR}/source/toolbar
)


file(COPY ${WEBVIEW_LIB_FILES} DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${TOOLBAR_UI} DESTINATION ${CMAKE_BINARY_DIR})
