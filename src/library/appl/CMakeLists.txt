
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2017 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

cmake_minimum_required( VERSION 2.8 )

set( appl_sources
   ${CMAKE_CURRENT_SOURCE_DIR}/arg_string_2_array.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/generation_file_creator.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/project_path.cpp
)

add_subdirectory( test )
