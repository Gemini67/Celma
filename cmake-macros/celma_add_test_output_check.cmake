
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##
##
##   Description:
##      Macro definition for specifying the expected program output from a list.
##


# convert list to string and specify as expected test output
macro( celma_add_test_output_check  testname output_list_var_name )
   string( REPLACE ";" "" expected_output ${${output_list_var_name}} )
   set_tests_properties( ${testname}
      PROPERTIES PASS_REGULAR_EXPRESSION ${expected_output}
   )
endmacro( celma_add_test_output_check )


