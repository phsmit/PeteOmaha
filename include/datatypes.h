#ifndef DATATYPES_H
#define	DATATYPES_H

#include "poker_defs.h"

#define MY_HOLE -4
#define OPPONENT_HOLE -3
#define NEW_STAGE -2
#define NEW_ROUND -1
#define NO_ACTION 0

typedef enum  {
    ME = 0,
    OTHER = 1
} PLAYER;

typedef enum {
    PREFLOP = 0,
    FLOP = 1,
    TURN = 2,
    RIVER = 3,
    FINISHED = 4
} STAGE;

typedef struct po_probs {
    double win;
    double draw;
    double loss;
} po_probs;

typedef struct po_settings {
    int time_bank;
    int time_per_move;
    int hands_per_level;
    int starting_stack;
    char my_player[8];
} po_settings;

typedef struct po_match {
    int round;
    
    STAGE stage; // 0=preflop, 1=flop, 2=turn, 3=river
    int small_blind;
    int big_blind;
    PLAYER on_button;
    
    int stack[2]; // before game
    int result[2]; //after game
    
    int win[2]; 
    
    int max_win_pot;
    int amount_to_call;
    
    StdDeck_CardMask board[4];
    
    StdDeck_CardMask hole[2];
    
    int bets[2][4]; // amounts raised. if no folds then: pot = (big_blind + sum(bets)) * 2
    
    int fold_stage[2]; // -1 = no fold
    
    po_probs probs[2][4];
    
} po_match;

#endif	/* DATATYPES_H */

