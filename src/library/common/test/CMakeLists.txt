
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

cmake_minimum_required( VERSION 2.8 )

add_definitions( -DBOOST_TEST_DYN_LINK)

celma_add_boost_testprogram( test_first_pass )
celma_add_boost_testprogram( test_tokenizer_base )
celma_add_boost_testprogram( test_tokenizer )

celma_add_celma_boost_testprogram( test_arg_string_2_array )
