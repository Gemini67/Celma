
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

ADD_DEFINITIONS( -DBOOST_TEST_DYN_LINK)


FILE( GLOB log_testprograms *.cpp )

FOREACH( testsource ${log_testprograms} )
   GET_FILENAME_COMPONENT( filename ${testsource} NAME_WE )
   celma_add_celma_boost_testprogram( ${filename} )
ENDFOREACH()


# test_log_standard_argument
# --------------------------

set( test_log_standard_argument_result
   "This is the only message that you should see!\n"
   "$"
)

celma_add_test_output_check( test_log_standard_argument  test_log_standard_argument_result )

