include_directories( ${CMAKE_BINARY_DIR}/include )
include_directories( ${PROJECT_SOURCE_DIR} )
include_directories( ${Boost_INCLUDE_DIRS} )

#Setup CMake to run tests
enable_testing()

##if(${Boost_FOUND})
##	set(TEST_LIBRARIES
##		${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
##	    lava
##	)
##	#include(CommonCTest)
##endif()

add_definitions (-DBOOST_TEST_DYN_LINK)

include(BoostTestHelpers)
add_boost_test(ExampleTest.cpp lava)