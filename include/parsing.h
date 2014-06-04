#ifndef PARSING_H
#define	PARSING_H

#include "poker_defs.h"

#include <string.h>

#define ME 0
#define OTHER 1

#define PREFLOP 0
#define FLOP 1
#define TURN 2
#define RIVER 3

typedef struct po_settings {
    int time_bank;
    int time_per_move;
    int hands_per_level;
    int starting_stack;
    char my_player[8];
} po_settings;

typedef struct po_match {
    int round;
    
    int stage; // 0=preflop, 1=flop, 2=turn, 3=river
    int small_blind;
    int big_blind;
    short me_on_button;
    int stack[2];
    
    int max_win_pot;
    int amount_to_call;
    
    StdDeck_CardMask table;
    
    StdDeck_CardMask hand[2];
    
    int bets[2][4];
    
} po_match;

int po_parse_next_line(char* line, po_match * match, po_settings * settings);

#endif	/* PARSING_H */

