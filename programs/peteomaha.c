#include <stdio.h>

#include "datatypes.h"
#include "preflop_holes.h"
#include "omaha_calc.h"
#include "parsing.h"
#include "decision_engine.h"

#define MAX_MATCHES 256

void calculate_my_probs(po_match * match) {
    match->probs[ME][match->stage] = get_probs(match->hole[ME], match->board[match->stage]);
}

void calculate_opponent_probs(po_match * match) {
    int stage;
    for (stage = 1; stage <= match->stage; ++stage) {
        match->probs[ME][stage] = get_probs(match->hole[OTHER], match->board[stage]);
    }
}

void init_matches(po_match * matches) {
    int id;
    for (id = 0; id < MAX_MATCHES; ++id) {
        matches[id].round = id + 1;
        matches[id].fold_stage[ME] = -1;
        matches[id].fold_stage[OTHER] = -1;
    }
}

int main(int argc, char** argv) {    
    init_preflop_holes();
    size_t nbytes = 0;
    char *line = NULL;
    
    po_settings settings;
    
    po_match match_history[MAX_MATCHES];
    memset(match_history, 0, sizeof(*match_history) * MAX_MATCHES);
    init_matches(match_history);
    
    po_match * current_match = match_history;
    
    int action;
    while(getline(&line, &nbytes, stdin))
    {
        action = po_parse_next_line(line, current_match, &settings);
        switch (action) {
            case NEW_STAGE:
            case MY_HOLE:
                calculate_my_probs(current_match);
                break;
            case OPPONENT_HOLE:
                calculate_opponent_probs(current_match);
                break;
            case NEW_ROUND:
                current_match++;
                break;
            case NO_ACTION:
                break;        
            default:
                play_poker(current_match, match_history);
                fflush(stdout);
                break; 
        }
    }
    
    free(line);

    return (EXIT_SUCCESS);
}

