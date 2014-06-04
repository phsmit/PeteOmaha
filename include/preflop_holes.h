#ifndef STARTING_HANDS_H
#define	STARTING_HANDS_H

#include "datatypes.h"

#define NUM_UNIQUES 16432

StdDeck_CardMask uniques[NUM_UNIQUES];

void init_preflop_holes();

po_probs preflop_probs(StdDeck_CardMask hole);

int get_preflop_index(StdDeck_CardMask hole);


#endif	/* STARTING_HANDS_H */

