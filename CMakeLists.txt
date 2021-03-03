cmake_minimum_required(VERSION 3.0)

project(Blog)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#Please Add The Directory Path Of The Magic Library.
#set(MAGIC /home/magic/Magic)
set(MAGIC /home/magic/WorkSpace/Magic)

if(NOT DEFINED MAGIC)
    message(FATAL_ERROR "Please Add The Directory Path Of The Magic Library!!!")
endif()

include_directories(
    ${MAGIC}
    ${MAGIC}/Include
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/Include
    ${MAGIC}/ThirdParty/Asio/Include
    ${MAGIC}/ThirdParty/RapidJSON/Include
)
link_directories(
    ${MAGIC}/Lib
)
link_libraries(Magic pq pqxx)
include(${MAGIC}/Magic.cmake)
include_directories(${CMAKE_BINARY_DIR})

set(LIBRARY_HEADERS
    -I${MAGIC}/Include
    -I${PROJECT_SOURCE_DIR}/Include
    -I${MAGIC}/ThirdParty/Asio/Include
    -I${MAGIC}/ThirdParty/RapidJSON/Include
)

## Servlet
set(ServletHeaders
    -H${PROJECT_SOURCE_DIR}/Include/Servlet/EditorServlet.h
    -H${PROJECT_SOURCE_DIR}/Include/Servlet/DetailsServlet.h
    -H${PROJECT_SOURCE_DIR}/Include/Servlet/ResourceServlet.h
    -H${PROJECT_SOURCE_DIR}/Include/Servlet/NotFoundServlet.h
    -H${PROJECT_SOURCE_DIR}/Include/Servlet/ArticleListServlet.h
)

set(MODULES
    ${MAGIC}/Modules/Magic.magic
    ${MAGIC}/Modules/WebServer.magic
    ${CMAKE_BINARY_DIR}/WebServlet.magic
)

add_custom_target(Gen ALL)

add_custom_command(
    TARGET Gen
    COMMAND ${MAGIC}/Bin/Analysis ${LIBRARY_HEADERS} ${ServletHeaders} -D -P -Finit -NBlog -OWebServlet
)

add_custom_command(
    TARGET Gen
    COMMAND ${MAGIC}/Bin/Gen ${MODULES} Blog
)

set(CPPSRC
    Source/Main.cpp
    Source/Data/Article.cpp
    Source/Servlet/EditorServlet.cpp
    Source/Servlet/DetailsServlet.cpp
    Source/Servlet/NotFoundServlet.cpp
    Source/Servlet/ResourceServlet.cpp
    Source/Servlet/ArticleListServlet.cpp
)

add_executable(Blog ${CPPSRC})
