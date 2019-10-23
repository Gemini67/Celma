
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2017-2018 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

cmake_minimum_required( VERSION 3.5 )

# list of files to add to the library
# use GLOB (instead of GLOB_RECURSE) so we can exclude the test directory
file( GLOB appl_sources
      "*.cpp"
)

add_subdirectory( test )
