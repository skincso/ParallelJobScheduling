# CMakeList.txt : CMake project for PJS, include source and define
# project specific logic here.
#

set(CMAKE_CXX_STANDARD 14)

add_executable (${PROJECT_NAME} 
	"main.cpp"
	"node.h"
	"node.cpp"
	"graph.h"
	"graph.cpp")

set(InputFile example.txt)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/graphs/${InputFile}
	${CMAKE_CURRENT_BINARY_DIR}/graph.txt COPYONLY)
