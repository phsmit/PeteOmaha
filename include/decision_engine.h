#ifndef DECISION_ENGINE_H
#define	DECISION_ENGINE_H

#include "datatypes.h"

#define CHECKFOLD -1
#define UNKNOWN -2

void play_poker(po_match * match, po_match * match_history) {
    fprintf(stderr, "----------------\n");
    fprintf(stderr, "my hole: %s\n", StdDeck_maskString(match->hole[ME]));
    fprintf(stderr, "board  : %s\n", StdDeck_maskString(match->board[match->stage]));

    fprintf(stderr, "win %.2f%%, draw %.2f%%, loss %.2f%%\n", 
            match->probs[ME][match->stage].win, 
            match->probs[ME][match->stage].draw, 
            match->probs[ME][match->stage].loss
            );
            
    po_probs * probs = &match->probs[ME][match->stage];
    int decision = UNKNOWN;
    
    switch (match->stage) {
        
        case PREFLOP:
            if(probs->win + probs->draw > 0.65) {
                if( match->bets[ME][PREFLOP] == 0) {
                    decision = match->big_blind;
                } else {
                    decision = 0;
                }
            }
            else if(match->bets[ME][PREFLOP] + match->amount_to_call <= match->big_blind) {
                decision = 0;
            } else {
                decision = CHECKFOLD;
            }
            break;
        case FLOP:
            if (probs->win + probs->draw < 0.7) {
                decision = CHECKFOLD;
            }
            break;
        case RIVER:
        case TURN:
            if (probs->win + probs->draw < 0.55) {
                decision = CHECKFOLD;
            }
            break;
    }
    
        // If decision is still UNKNOWN, we have good chances.
    
    if (probs->win + probs->draw > 0.85) decision = match->big_blind;
    if (probs->win + probs->draw > 0.97) decision = match->max_win_pot + match->amount_to_call;
    if (decision == UNKNOWN) decision = 0;
    
    switch (decision) {
        case CHECKFOLD:
            if (match->amount_to_call == 0) {
                puts("check 0");
            } else {
                puts("fold 0");
            }
            break;
        case 0:
            if (match->amount_to_call == 0) {
                puts("check 0");
            } else {
                puts("call 0");
            }
            break;
        default:
            printf("raise %d\n",decision);
            break;
    }
}
#endif	/* DECISION_ENGINE_H */

