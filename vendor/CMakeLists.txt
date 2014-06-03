
include_directories("poker-eval/include")

set(POKEREVAL_INCLUDEDIRS
poker-eval/include)

set(POKEREVALSOURCES 
poker-eval/lib/deck.c
poker-eval/lib/deck_std.c
poker-eval/lib/t_cardmasks.c
poker-eval/lib/t_topfivecards.c
poker-eval/lib/t_straight.c
poker-eval/lib/t_nbits.c
poker-eval/lib/t_topcard.c
poker-eval/lib/t_botfivecards.c
poker-eval/lib/rules_std.c
)
add_library( pokereval ${POKEREVALSOURCES})


