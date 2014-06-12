#include <stdio.h>
#include <string.h>

#include "preflop_holes.h"

int main(int argc, char** argv) {
    init_preflop_holes();
    double wins[NUM_UNIQUES];
    double draws[NUM_UNIQUES];
    double hole_probs_me[NUM_UNIQUES][HandType_COUNT];
    double hole_probs_other[NUM_UNIQUES][HandType_COUNT];
    
    size_t nbytes = 0;
    char *line = NULL;
    
    StdDeck_CardMask hole, card;
    
    int i, j, card_i, index;
    
    while(getline(&line, &nbytes, stdin)  > 0)
    {
        StdDeck_CardMask_RESET(hole);
        for (i = 0; i < 4; ++i) {
            StdDeck_stringToCard(line+i*3, &card_i); 
            card = StdDeck_MASK(card_i);
            StdDeck_CardMask_OR(hole, hole, card);
        }
        
        line[strlen(line) - 1] = '\0';
        
        index = get_preflop_index(hole);
        
        wins[index] = atof(strtok(line+12, " "));
        draws[index] = atof(strtok(NULL, " "));
        
        for (i = 0; i < HandType_COUNT; ++i) {
            hole_probs_me[index][i] = atof(strtok(NULL, " "));
        }
        
        for (i = 0; i < HandType_COUNT; ++i) {
            hole_probs_other[index][i] = atof(strtok(NULL, " "));
        }
       
    }
    puts("#include \"probtables.h\"");
    printf("double win_table[%d] = { \n", NUM_UNIQUES);
    for (i = 0; i < NUM_UNIQUES; ++i) {
        printf("%.2f", wins[i]);
        if (i < NUM_UNIQUES -1) {
            printf(",\n");
        }
    }
    printf("};\n\n");
    
    printf("double draw_table[%d] = { \n", NUM_UNIQUES);
    for (i = 0; i < NUM_UNIQUES; ++i) {
        printf("%.2f", draws[i]);
        if (i < NUM_UNIQUES -1) {
            printf(",\n");
        }
    }
    printf("};\n\n");
    
    printf("double my_hand_probs_table[%d][%d] = { \n", NUM_UNIQUES, HandType_COUNT);
    for (i = 0; i < NUM_UNIQUES; ++i) {
        for (j = 0; j < HandType_COUNT; ++j) {
            printf("%.2f", hole_probs_me[i][j]);
            if (j < HandType_COUNT -1) {
                printf(",");
            }
        }
        if (i < NUM_UNIQUES -1) {
            printf(",\n");
        }
    }
    printf("};\n\n");
    
    printf("double other_hand_probs_table[%d][%d] = { \n", NUM_UNIQUES, HandType_COUNT);
    for (i = 0; i < NUM_UNIQUES; ++i) {
        for (j = 0; j < HandType_COUNT; ++j) {
            printf("%.2f", hole_probs_other[i][j]);
            if (j < HandType_COUNT -1) {
                printf(",");
            }
        }
        if (i < NUM_UNIQUES -1) {
            printf(",\n");
        }
    }
    printf("};\n\n");
    
    return (EXIT_SUCCESS);
}

