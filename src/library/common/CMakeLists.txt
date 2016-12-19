
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

cmake_minimum_required( VERSION 2.8 )

set( common_sources
   ${CMAKE_CURRENT_SOURCE_DIR}/arg_string_2_array.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/exception_base.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/extract_funcname.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/print_version_info.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/range_expression.cpp
)

add_subdirectory( test )
