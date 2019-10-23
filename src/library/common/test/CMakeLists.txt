
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
# - test programs ending in _mt are built with multi-threading options
# - test programs ending in _c are linked against the Celma library
# - all remainng test programs are just linked against the Boost (Test) library

FILE( GLOB common_testprograms *.cpp )

FOREACH( testsource ${common_testprograms} )
   GET_FILENAME_COMPONENT( filename ${testsource} NAME_WE )
   IF (filename MATCHES test_.*_mt)
      celma_add_boost_mt_testprogram( ${filename} )
   ELSEIF (filename MATCHES test_.*_c)
      celma_add_celma_boost_testprogram( ${filename} )
   ELSE()
      celma_add_boost_testprogram( ${filename} )
   ENDIF()
ENDFOREACH()

add_test( test_execute_statistic_erase_path  ${CMAKE_CURRENT_BINARY_DIR}/test_execute_statistic_c -- ${PROJECT_SOURCE_DIR} )

