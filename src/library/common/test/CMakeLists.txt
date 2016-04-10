
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

cmake_minimum_required( VERSION 2.8 )

add_definitions( -DBOOST_TEST_DYN_LINK)

celma_add_boost_testprogram( test_clear_container )
celma_add_boost_testprogram( test_first_pass )
celma_add_boost_testprogram( test_reset_at_exit )
celma_add_boost_testprogram( test_tokenizer )
celma_add_boost_testprogram( test_tokenizer_base )
celma_add_boost_testprogram( test_type_name )

celma_add_celma_boost_testprogram( test_arg_string_2_array )
celma_add_celma_boost_testprogram( test_auto_sprintf )
celma_add_celma_boost_testprogram( test_exception )
celma_add_celma_boost_testprogram( test_extract_func_name )
celma_add_celma_boost_testprogram( test_range_dest )
celma_add_celma_boost_testprogram( test_range_expression )
celma_add_celma_boost_testprogram( test_range_generator )
celma_add_celma_boost_testprogram( test_range_string )
celma_add_celma_boost_testprogram( test_singleton )
celma_add_celma_boost_testprogram( test_version_info )