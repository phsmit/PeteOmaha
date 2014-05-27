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
target_link_libraries ( peteomaha pokereval )

