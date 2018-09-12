
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

cmake_minimum_required( VERSION 3.5 )

# list of files to add to the library
# use GLOB (instead of GLOB_RECURSE) so we can exclude the test directory
file( GLOB log_sources
      "*.cpp"
      "detail/*.cpp"
      "filename/*.cpp"
      "files/*.cpp"
      "formatting/*.cpp"
)

add_subdirectory( test)
# add_subdirectory( test_output)
