
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2016-2020 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

cmake_minimum_required( VERSION 3.5 )

project( Celma )

set( MAJORVERSION    1 )
set( MINORVERSION    34 )
set( RELEASE_VERSION 2 )
set( PATCHLEVEL      0 )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

enable_testing()
include( CTest)

# Celma specific CMake extensions
set( CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake-macros" )
include( celma_add_test )
include( celma_add_test_output_check )

add_definitions( -Wall -W -Wshadow -Wunused-variable -Wunused-parameter
                 -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated
                 -Woverloaded-virtual -Wwrite-strings -Wextra -pedantic
                 -fdiagnostics-show-option )

if (CMAKE_BUILD_TYPE MATCHES Coverage)
   set( CMAKE_BUILD_TYPE Debug)
   include( CodeCoverage)
   set( CMAKE_CXX_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage" )
   set( CMAKE_SHARED_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

   # setup_target_for_coverage( <target name> <test runner script> <output name>)
   setup_target_for_coverage( Celma_coverage c_coverage_test_runner coverage )
endif (CMAKE_BUILD_TYPE MATCHES Coverage)


# test that filesystem header actually is there and works
try_compile( HAS_FS "${CMAKE_BINARY_DIR}/temp"
   "${PROJECT_SOURCE_DIR}/cmake-macros/has_filesystem.cpp"
   CMAKE_FLAGS -DCMAKE_CXX_STANDARD=17 -DCMAKE_CXX_STANDARD_REQUIRED=ON
   LINK_LIBRARIES stdc++fs)
if (HAS_FS)
   message( STATUS "std::filesystem is available")
   set( LINK_LIBRARIES stdc++fs)
else()
   message( STATUS "std::filesystem is not available (yet)")
endif()


# Boost stuff ------------------------------------------------------------------
find_package( Boost ${BOOST_VERSION} REQUIRED
   filesystem
   thread
   system
   unit_test_framework
)

message( STATUS "Boost_INCLUDE_DIRS ${Boost_INCLUDE_DIRS}" )
message( STATUS "Boost_LIBRARY_DIRS ${Boost_LIBRARY_DIRS}" )

if (HAS_FS)
   set( Boost_Link_Libs       boost_thread boost_system )
else()
   set( Boost_Link_Libs       boost_filesystem boost_thread boost_system )
endif()
set( Boost_Test_Link_Libs  boost_unit_test_framework ${Boost_Link_Libs} )


# include directories ----------------------------------------------------------

set( CELMA_INCLUDE_DIRS
     ${CMAKE_CURRENT_SOURCE_DIR}/src
)

include_directories(
   ${CELMA_INCLUDE_DIRS}
   SYSTEM ${Boost_INCLUDE_DIRS}
)

# suppress warnings for external libraries
add_definitions( -isystem ${Boost_INCLUDE_DIR} )

link_directories( ${Boost_LIBRARY_DIRS} )

add_subdirectory( src)

