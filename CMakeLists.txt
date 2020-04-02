cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)

project(AnnBenchmark)
include_directories ("${PROJECT_SOURCE_DIR}/external/annoy/src")
include_directories ("${PROJECT_SOURCE_DIR}/external/nsg/include")
include_directories ("${PROJECT_SOURCE_DIR}/external/efanna_graph/include")

include_directories ("${PROJECT_SOURCE_DIR}/ann/")
include_directories ("${PROJECT_SOURCE_DIR}/util/")

#OpenMP
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
else()
    message(FATAL_ERROR "no OpenMP supprot")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free")

add_definitions (-std=c++11 -O2 -g -mavx -msse -msse2 -msse3 -mavx2)

set (SRC_FILES
	"${PROJECT_SOURCE_DIR}/ann/AnnBase.cpp"
	"${PROJECT_SOURCE_DIR}/ann/Annoy.cpp"
	"${PROJECT_SOURCE_DIR}/ann/Nsg.cpp"
	"${PROJECT_SOURCE_DIR}/util/SiftUtil.cpp"
)

add_executable(test_ann ${SRC_FILES} "test/test.cpp")

target_link_libraries(test_ann "${PROJECT_SOURCE_DIR}/external/nsg/build/src/libefanna2e_s.a"
			     "${PROJECT_SOURCE_DIR}/external/efanna_graph/src/libefanna2e_s.a")
			     
add_executable(test_annoy ${SRC_FILES} "test/test_annoy.cpp")
target_link_libraries(test_annoy "${PROJECT_SOURCE_DIR}/external/nsg/build/src/libefanna2e_s.a"
			     "${PROJECT_SOURCE_DIR}/external/efanna_graph/src/libefanna2e_s.a")

add_executable(test_nsg ${SRC_FILES} "test/test_nsg.cpp")
target_link_libraries(test_nsg "${PROJECT_SOURCE_DIR}/external/nsg/build/src/libefanna2e_s.a"
			     "${PROJECT_SOURCE_DIR}/external/efanna_graph/src/libefanna2e_s.a")


