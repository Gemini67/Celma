
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

cmake_minimum_required( VERSION 2.8 )

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
   configure_file(
      "${CMAKE_CURRENT_SOURCE_DIR}/detail/celma_version.hpp.in"
      "${CMAKE_CURRENT_SOURCE_DIR}/celma_version.hpp"
   )
endif()
