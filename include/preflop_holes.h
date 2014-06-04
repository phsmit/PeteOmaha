#ifndef STARTING_HANDS_H
#define	STARTING_HANDS_H

#include "poker_defs.h"

#define NUM_UNIQUES 16432

StdDeck_CardMask uniques[NUM_UNIQUES];

void init_preflop_holes();

void preflop_probs(StdDeck_CardMask hole, double * win, double * loss, double *draw);

int get_preflop_index(StdDeck_CardMask hole);


#endif	/* STARTING_HANDS_H */

