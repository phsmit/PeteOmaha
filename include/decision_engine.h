#ifndef DECISION_ENGINE_H
#define	DECISION_ENGINE_H

#include "datatypes.h"

#define CHECKFOLD -1
#define UNKNOWN -2

void make_probabilistic_descision2(po_match * match, po_probs * probs) {
    int decision = UNKNOWN;
    
    switch (match->stage) {
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

void play_poker(po_match * match, po_match * match_history) {
    
    switch (match->stage) {
        case PREFLOP:
            if (match->amount_to_call == 0) {
                puts("check 0");
                break;
            }
            if(match->bets[ME][PREFLOP] + match->amount_to_call <= match->big_blind) {
                printf("call %i\n", match->amount_to_call);
            } else {
                puts("fold 0");
            }
            break;
        default:
            fprintf(stderr, "----------------\n");
            fprintf(stderr, "my hole: %s\n", StdDeck_maskString(match->hole[ME]));
            fprintf(stderr, "board  : %s\n", StdDeck_maskString(match->board));

            fprintf(stderr, "win %.2f%%, draw %.2f%%, loss %.2f%%\n", 
                    match->probs[ME][match->stage].win, 
                    match->probs[ME][match->stage].draw, 
                    match->probs[ME][match->stage].loss
                    );

            make_probabilistic_descision2(match, &match->probs[ME][match->stage]);

            break;
        }
}
#endif	/* DECISION_ENGINE_H */

