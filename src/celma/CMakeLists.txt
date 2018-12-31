
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

cmake_minimum_required( VERSION 3.5 )

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
   configure_file(
      "${CMAKE_CURRENT_SOURCE_DIR}/detail/celma_version.hpp.in"
      "${CMAKE_CURRENT_SOURCE_DIR}/celma_version.hpp"
   )
endif()
