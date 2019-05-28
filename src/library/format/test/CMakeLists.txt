
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2016-2019 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

cmake_minimum_required( VERSION 3.5 )

add_definitions( -DBOOST_TEST_DYN_LINK)


# search for all test programs and build them depending on their names:
# - test programs ending in _h are just linked against the Boost (Test) library
# - all remainng test programs are also linked against the Celma library

FILE( GLOB format_testprograms *.cpp )

FOREACH( testsource ${format_testprograms} )
   GET_FILENAME_COMPONENT( filename ${testsource} NAME_WE )
   IF (filename MATCHES test_.*_h)
      celma_add_boost_testprogram( ${filename} )
   ELSE()
      celma_add_celma_boost_testprogram( ${filename} )
   ENDIF()
ENDFOREACH()

