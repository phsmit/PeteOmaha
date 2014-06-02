cmake_minimum_required(VERSION 2.8)
PROJECT(PeteOmaha)

include_directories("pe/include")

set(POKEREVALSOURCES 
pe/lib/deck.c
pe/lib/deck_std.c
pe/lib/t_cardmasks.c
pe/lib/t_topfivecards.c
pe/lib/t_straight.c
pe/lib/t_nbits.c
pe/lib/t_topcard.c
pe/lib/t_botfivecards.c
pe/lib/rules_std.c
)
add_library( pokereval ${POKEREVALSOURCES})
add_executable( peteomaha peteomaha.c )
add_executable( pregen pregen/pregen.c )
add_executable( test_starting_hands pregen/test_starting_hands.c )
add_executable( print_unique_hands pregen/print_unique_hands.c )
add_executable( classify_hands pregen/classify_hands.c )

target_link_libraries ( pregen pokereval )
target_link_libraries ( peteomaha pokereval )
target_link_libraries ( test_starting_hands pokereval)
target_link_libraries ( print_unique_hands pokereval)
target_link_libraries ( classify_hands pokereval)