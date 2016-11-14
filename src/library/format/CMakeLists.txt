
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

cmake_minimum_required( VERSION 2.8 )

set( format_sources
   ${CMAKE_CURRENT_SOURCE_DIR}/ascii_table.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/auto_sprintf.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/grouped_int2str.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/int2str.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/text_block.cpp
)

add_subdirectory( test )
