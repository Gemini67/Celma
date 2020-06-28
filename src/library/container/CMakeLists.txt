
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2020 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

cmake_minimum_required( VERSION 3.5 )

# list of files to add to the library
# use GLOB (instead of GLOB_RECURSE) so we can exclude the test directory
file( GLOB container_sources
      "*.cpp"
      "detail/*.cpp"
)

add_subdirectory( test )

