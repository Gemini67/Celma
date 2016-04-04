
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

cmake_minimum_required( VERSION 2.8 )

project( Celma )

set( MAJORVERSION    0 )
set( MINORVERSION    0 )
set( RELEASE_VERSION 2 )
set( PATCHLEVEL      0 )

enable_testing()
include( CTest)

add_definitions( --std=c++1y
                 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter
                 -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated
                 -Woverloaded-virtual -Wwrite-strings -Wextra -pedantic
                 -fdiagnostics-show-option )

# Boost stuff ------------------------------------------------------------------
find_package( Boost ${BOOST_VERSION} REQUIRED
   thread
   system
   unit_test_framework
)

message( STATUS "Boost_INCLUDE_DIRS ${Boost_INCLUDE_DIRS}" )
message( STATUS "Boost_LIBRARY_DIRS ${Boost_LIBRARY_DIRS}" )

set( Boost_Link_Libs       boost_thread boost_system )
set( Boost_Test_Link_Libs  boost_unit_test_framework ${Boost_Link_Libs} )

# include directories ----------------------------------------------------------

set( CELMA_INCLUDE_DIRS
     ${CMAKE_CURRENT_SOURCE_DIR}/src
)

include_directories(
   ${CELMA_INCLUDE_DIRS}
   ${Boost_INCLUDE_DIRS}
)

# suppress warnings for external libraries
add_definitions( -isystem ${Boost_INCLUDE_DIR} )

link_directories( ${Boost_LIBRARY_DIRS} )

# Celma specific CMake extensions
set( CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake-macros" )
include( celma_add_test )
include( celma_add_test_output_check )

add_subdirectory( src)

