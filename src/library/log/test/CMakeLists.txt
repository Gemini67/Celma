
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

CMAKE_MINIMUM_REQUIRED( VERSION 3.5 )

ADD_DEFINITIONS( -DBOOST_TEST_DYN_LINK)


FILE( GLOB log_testprograms *.cpp )

FOREACH( testsource ${log_testprograms} )
   GET_FILENAME_COMPONENT( filename ${testsource} NAME_WE )
   IF (NOT filename MATCHES test_log_file_policies_stub)
      celma_add_celma_boost_testprogram( ${filename} )
   ENDIF()
ENDFOREACH()


add_executable( test_log_file_policies_stub
   test_log_file_policies_stub.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/../detail/log_msg.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/../detail/log_msg_property.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/../files/counted.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/../files/max_size.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/../files/simple.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/../files/timestamped.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/../filename/builder.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/../filename/creator.cpp
)

target_compile_definitions( test_log_file_policies_stub
   PUBLIC -DCELMA_LOG_POLICY_BASE_STUB
)

target_link_libraries( test_log_file_policies_stub  celma-common ${Boost_Test_Link_Libs} )

add_test( test_log_file_policies_stub  ${CMAKE_CURRENT_BINARY_DIR}/test_log_file_policies_stub )


# test_log_standard_argument
# --------------------------

set( test_log_standard_argument_result
   "This is the only message that you should see!\n"
   "$"
)

celma_add_test_output_check( test_log_standard_argument  test_log_standard_argument_result )

