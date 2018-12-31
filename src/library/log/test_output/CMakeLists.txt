
##
##
##            ####  #  ####    ####
##           #      #      #  #
##          #       #       ##         (C) 2015 SIX Group Services
##         #        #       ##             All rights reserved
##        #         #      #  #
##    ####          #  ####    ####
##
##

CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

add_executable( test_log_cout_cerr          test_log_cout_cerr.cpp )
add_executable( test_log_standard_argument  test_log_standard_argument.cpp )

target_link_libraries( test_log_cout_cerr          sfndtn ${Boost_Link_Libs} )
target_link_libraries( test_log_standard_argument  sfndtn ${Boost_Link_Libs} )

add_test( test_log_cout_cerr_complete   ${CMAKE_CURRENT_BINARY_DIR}/test_log_standard_argument )
add_test( test_log_cout_cerr_cerr_only  ${CMAKE_CURRENT_BINARY_DIR}/test_log_standard_argument >/dev/null )
add_test( test_log_cout_cerr_cout_only  ${CMAKE_CURRENT_BINARY_DIR}/test_log_standard_argument 2>/dev/null )
add_test( test_log_standard_argument    ${CMAKE_CURRENT_BINARY_DIR}/test_log_standard_argument )


# test_log_cout_cerr_complete
# ---------------------------

set( test_log_cout_cerr_complete_result
   "message with level 'fatal' expected on stderr!\n"
   ".*message with level 'error' expected on stderr!\n"
   ".*message with level 'warning' expected on stdout!\n"
   ".*message with level 'info' expected on stdout!\n"
   ".*message with level 'debug' expected on stdout!\n"
   ".*message with level 'full debug' expected on stdout!\n"
   "$"
)

add_test_output_check( test_log_cout_cerr_complete  test_log_cout_cerr_complete_result )

# test_log_standard_argument
# --------------------------

set( test_log_standard_argument_result
   "This is the only message that you should see!\n"
   "$"
)

add_test_output_check( test_log_standard_argument  test_log_standard_argument_result )

