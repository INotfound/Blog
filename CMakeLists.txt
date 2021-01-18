cmake_minimum_required(VERSION 3.0)

project(Blog)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#Please Add The Directory Path Of The Magic Library.
set(MAGIC /home/magic/Magic)
#set(MAGIC /home/magic/WorkSpace/Magic)

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

GENEX(${MAGIC} Blog MODULE 
    ${MAGIC}/Magic.magic
    ${MAGIC}/WebServer.magic
    ${PROJECT_SOURCE_DIR}/DataBase.magic
    ${PROJECT_SOURCE_DIR}/WebServlet.magic
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