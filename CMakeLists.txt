cmake_minimum_required(VERSION 3.12...3.19)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS -pthread)

project(microtubule_simulation VERSION 0.0
				DESCRIPTION "Simulation of acetylation along a 1D microtubule"
				LANGUAGES CXX)

message("---------------------------Release information---------------------------")
message("- Toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
message("  - C   Compiler: ${CMAKE_C_COMPILER}")
message("  - CPP Compiler: ${CMAKE_CXX_COMPILER}")
message("CMAKE_PROJECT_VERSION = ${CMAKE_PROJECT_VERSION}")
message("-------------------------------------------------------------------------")

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(output ${SOURCES})


set_target_properties(output PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/obj"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/obj"
)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
target_link_libraries (output PRIVATE Eigen3::Eigen)
