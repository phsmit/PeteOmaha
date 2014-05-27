/* 
 * File:   peteomaha.c
 * Author: psmit
 *
 * Created on May 26, 2014, 3:31 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "parsing.h"
#include "my_poker_calc.h"
/*
 * 
 */

void make_probabilistic_descision(po_match * match, po_settings * settings, po_res_counts * counts) {
    long sum = counts->wins + counts->losses + counts->draws;
    double w = (double) counts->wins / (double) sum;
    double l = (double) counts->losses / (double) sum;
    
    if (l > w) {
        if (match->amount_to_call == 0) {
            puts("check 0");
        }
        else if (l * match->amount_to_call < match->max_win_pot) {
            puts("call 0");
        } else {
            puts("fold 0");
        }
    } else {
        // we at least call, 
        int max_raise = match->max_win_pot + match->amount_to_call;
        int raise = 0;
        
        double prob_delta = w - l;
        
        if (prob_delta > 0.6) {
            raise = max_raise;
        } else if (prob_delta > 0.4) {
            raise = max_raise / 2;
        }
        
        if (raise == 0) {
            puts("call 0");
        } else {
            printf("raise %d\n",raise);
        }
    }
    
}

int main(int argc, char** argv) {          
    size_t nbytes = 100;
    char *line;
    
    po_settings settings;
    po_match match;
    po_res_counts counts;
    
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
                    clear_counts(&counts);
                    get_win_chance(match.hand[ME], match.table, &counts);
                    fprintf(stderr, "----------------\n");
                    fprintf(stderr, "my hole: %s\n", StdDeck_maskString(match.hand[ME]));
                    fprintf(stderr, "board  : %s\n", StdDeck_maskString(match.table));
                    long sum = counts.draws + counts.wins + counts.losses;
                    fprintf(stderr, "win %.2f%%, draw %.2f%%, loss %.2f%%\n", 
                            (double) counts.wins / (double)sum * 100.0,
                            (double) counts.draws / (double)sum * 100.0,
                            (double) counts.losses / (double)sum * 100.0
                            );
                        
                    make_probabilistic_descision(&match, &settings, & counts);
//                    // We first implement the rules from http://cowboyprogramming.com/2007/01/04/programming-poker-ai/
//                    double hand_strength = ((double) counts.wins + (double) counts.draws / 2) / (double) sum;
//                    int call = match.amount_to_call;
//                    if (call < match.small_blind) {
//                        
//                        call = match.small_blind;
//                    }
//                    
//                    double pot_odds = (double)call / ((double)call + (double) match.max_win_pot);
//                    double rr = hand_strength / pot_odds;
//                    double rand_n = (double) rand() / (double) RAND_MAX;
//                    
//                    fprintf(stderr, "hs: %.2f, po: %.2f, rr: %.2f, rnd: %.2f\n", hand_strength, pot_odds, rr, rand_n);
//                    int amount = 0;
//                    int raise = 2 * call;
//                    if (rr < 0.8) {
//                        if (rand_n > 0.95) amount = raise;
//                    } else if (rr < 1.0) {
//                        if (rand_n > 0.8) {
//                            amount = call;
//                        } else if (rand_n > 0.85) {
//                            amount = raise;
//                        }
//                    } else if (rr < 1.3) {
//                        if (rand_n < 0.6) {
//                            amount = call;
//                        } else {
//                            amount = raise;
//                        }
//                    } else {
//                        if (rand_n < 0.3) {
//                            amount = call;
//                        } else {
//                            amount = raise;
//                        }
//                    }
//                    
//                    
//                    fprintf(stderr, "amount: %d\n", amount);
//                    
//                    if (amount == 0) {
//                        if (match.amount_to_call == 0) {
//                            puts("check 0");
//                        } else {
//                            puts("fold 0");
//                        }
//                    } else if (amount <= match.amount_to_call) {
//                        puts("call 0");
//                    } else {
//                        printf("raise %d\n", amount);
//                    }
                    
//                    puts("check 0");
                    break;
            }            
            fflush(stdout);
        }
    }

    return (EXIT_SUCCESS);
}

