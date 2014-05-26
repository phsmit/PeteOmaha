cmake_minimum_required(VERSION 2.8)
PROJECT(PeteOmaha)

include_directories("pe/include")

set(POKEREVALSOURCES 
pe/lib/combinations.c
pe/lib/deck_astud.c
pe/lib/deck.c
pe/lib/deck_joker.c
pe/lib/deck_std.c
pe/lib/enumerate.c
pe/lib/enumord.c
pe/lib/evx.c
pe/lib/lowball.c
pe/lib/mktable.c
pe/lib/mktable_utils.c
pe/lib/poker_wrapper.c
pe/lib/rules_astud.c
pe/lib/rules_joker.c
pe/lib/rules_std.c
pe/lib/t_astudcardmasks.c
pe/lib/t_botcard.c
pe/lib/t_botfivecards.c
pe/lib/t_botfivecardsj.c
pe/lib/t_cardmasks.c
pe/lib/t_evx_flushcards.c
pe/lib/t_evx_pairval.c
pe/lib/t_evx_strval.c
pe/lib/t_evx_tripsval.c
pe/lib/t_jokercardmasks.c
pe/lib/t_jokerstraight.c
pe/lib/t_maskrank.c
pe/lib/t_nbitsandstr.c
pe/lib/t_nbits.c
pe/lib/t_straight.c
pe/lib/t_topbit.c
pe/lib/t_topcard.c
pe/lib/t_topfivebits.c
pe/lib/t_topfivecards.c
pe/lib/t_toptwobits.c
)
add_library( pokereval ${POKEREVALSOURCES})
add_executable( seven_card_hands seven_card_hands.c )
target_link_libraries ( seven_card_hands pokereval )

