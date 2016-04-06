
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

cmake_minimum_required( VERSION 2.8 )

# list of files to add to the library
# use GLOB (instead of GLOB_RECURSE) so we can exclude the test directory
file( GLOB prog_args_sources
      "*.cpp"
      "detail/*.cpp"
)

add_subdirectory( test)
