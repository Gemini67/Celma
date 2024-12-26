
##
##    ####   ######  #       #    #   ####
##   #    #  #       #       ##  ##  #    #
##   #       ###     #       # ## #  ######    (C) 2017-2018 Rene Eng
##   #    #  #       #       #    #  #    #        LGPL
##    ####   ######  ######  #    #  #    #
##

cmake_minimum_required( VERSION 2.8 )

add_definitions( -DBOOST_TEST_DYN_LINK)

celma_add_boost_testprogram( test_balanced_binary_tree )
celma_add_boost_testprogram( test_binary_tree )
celma_add_boost_testprogram( test_binary_tree_greater )
celma_add_boost_testprogram( test_binary_tree_permutations )
celma_add_boost_testprogram( test_btree )
celma_add_boost_testprogram( test_bit_range )
celma_add_boost_testprogram( test_btree_permutations )

