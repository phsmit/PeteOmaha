#include <stdio.h>
#include <string.h>

#include "preflop_holes.h"

int main(int argc, char** argv) {
    init_preflop_holes();
    double wins[NUM_UNIQUES];
    double draws[NUM_UNIQUES];
    double losses[NUM_UNIQUES];
    
    size_t nbytes = 100;
    char *line;
    line = (char *) malloc(nbytes + 1);
    
    StdDeck_CardMask hole, card;
    
    int i, card_i, index;
    
    while(getline(&line, &nbytes, stdin)  > 0)
    {
        StdDeck_CardMask_RESET(hole);
        for (i = 0; i < 4; ++i) {
            StdDeck_stringToCard(line+i*3, &card_i); 
            card = StdDeck_MASK(card_i);
            StdDeck_CardMask_OR(hole, hole, card);
        }
        
        line[strlen(line) - 1] = '\0';
        double win = atof(strtok(line+12, " "));
        double draw = atof(strtok(NULL, " "));
        double loss = atof(strtok(NULL, " "));
        
        index = get_preflop_index(hole);
        
        wins[index] = win;
        draws[index] = draw;
        losses[index] = loss;
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
    
    printf("double loss_table[%d] = { \n", NUM_UNIQUES);
    for (i = 0; i < NUM_UNIQUES; ++i) {
        printf("%.2f", losses[i]);
        if (i < NUM_UNIQUES -1) {
            printf(",\n");
        }
    }
    printf("};\n\n");
    
    return (EXIT_SUCCESS);
}

