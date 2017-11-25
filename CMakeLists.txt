cmake_minimum_required (VERSION 2.6)
project (Genetics)

set(CMAKE_CXX_FLAGS " -W -Wall -pedantic -std=c++11")

enable_testing()
add_subdirectory(gtest)
set(SOURCE_FILES
	src/main.cpp
	src/Simulation.cpp
	src/Simulation.hpp
	src/Allele.cpp
	src/Allele.hpp
	src/Generation.cpp
	src/Generation.hpp
	src/Experiment.cpp
	src/Experiment.hpp)


include_directories(${gtest_SOURCE_DIR}/include${gtest_SOURCE_FILES})
add_executable(Genetics ${SOURCE_FILES})
add_executable(genetics_unittest src/Simulation.cpp src/Allele.cpp src/Generation.cpp test/test/genetics_unittest.cpp)


target_link_libraries(genetics_unittest gtest gtest_main)
add_test(genetics_unittest genetics_unittest)


# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files

	set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/doc/Doxyfile)
    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)



