#include <stdio.h>
#include <stdlib.h>

#include "datatypes.h"
#include "parsing.h"
#include "omaha_calc.h"


#define CHECKFOLD -1
#define UNKNOWN -2

void make_probabilistic_descision2(po_match * match, po_settings * settings, po_probs * probs) {
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

int main(int argc, char** argv) {          
    size_t nbytes = 100;
    char *line;
    
    po_settings settings;
    po_match match;

    po_probs probs;
    
    line = (char *) malloc(nbytes + 1);
    
    int action_time = 0;
    while(getline(&line, &nbytes, stdin))
    {
        action_time = po_parse_next_line(line, &match, &settings);
        if (action_time) {
            switch (match.stage) {
                case PREFLOP:
                    if (match.amount_to_call == 0) {
                        puts("check 0");
                        break;
                    }
                    if(match.bets[ME][PREFLOP] + match.amount_to_call <= match.big_blind) {
                        printf("call %i\n", match.amount_to_call);
                    } else {
                        puts("fold 0");
                    }
                    break;
                default:
                    probs = get_probs(match.hand[ME], match.table);
                    fprintf(stderr, "----------------\n");
                    fprintf(stderr, "my hole: %s\n", StdDeck_maskString(match.hand[ME]));
                    fprintf(stderr, "board  : %s\n", StdDeck_maskString(match.table));
                    
                    fprintf(stderr, "win %.2f%%, draw %.2f%%, loss %.2f%%\n", 
                            probs.win, probs.draw, probs.loss
                            );
                        
                    make_probabilistic_descision2(&match, &settings, & probs);

                    break;
            }            
            fflush(stdout);
        }
    }

    return (EXIT_SUCCESS);
}

