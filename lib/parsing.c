#include "parsing.h"

static inline StdDeck_CardMask read_cards(char* s) {
    StdDeck_CardMask handm, cardm;
    StdDeck_CardMask_RESET(handm);
    
    int cardi;
    int num_cards = (strlen(s) -1) / 3;
    int i;
    for (i = 0; i < num_cards; ++i) {
       StdDeck_stringToCard(s+1+i*3, &cardi); 
       cardm = StdDeck_MASK(cardi);
       StdDeck_CardMask_OR(handm, handm, cardm);
    }
//    fprintf(stderr, "%d cards read\n", StdDeck_numCards(handm));
    return handm;
}

static inline void new_round(po_match *match, int round) {
    fprintf(stderr,"Round %d\n", round);
    match->round = round;
    match->stage = PREFLOP;
    
    StdDeck_CardMask_RESET(match->table);
    StdDeck_CardMask_RESET(match->hand[ME]);
    StdDeck_CardMask_RESET(match->hand[OTHER]);
    
    memset(match->bets, 0, sizeof(match->bets[0][0]) * 2 * 4);
    
}
int po_parse_next_line(char* line, po_match * match, po_settings * settings) {
    line[strlen(line) - 1] = '\0';
    char* keyword_one = strtok(line, " ");
    char* keyword_two = strtok(NULL, " ");
    char* value = strtok(NULL, " ");
    
    
    if (strcmp(keyword_one, "Match") == 0) {
        if (strcmp(keyword_two, "round") == 0) {
            // TODO save previous round
            new_round(match, atoi(value));            
        } else if (strcmp(keyword_two, "smallBlind") == 0) {
            match->small_blind = atoi(value);
        } else if (strcmp(keyword_two, "bigBlind") == 0) {
            match->big_blind = atoi(value);
        } else if (strcmp(keyword_two, "onButton") == 0) {
            match->me_on_button = strcmp(value, settings->my_player) == 0;
        } else if (strcmp(keyword_two, "table") == 0) {
            match->table = read_cards(value);
            switch (StdDeck_numCards(match->table)) {
                case 3:
                    match->stage = FLOP;
                    break;
                case 4:
                    match->stage = TURN;
                    break;
                case 5:
                    match->stage = RIVER;
                    break;
            }
        } else if (strcmp(keyword_two, "maxWinPot") == 0) {
            match->max_win_pot = atoi(value);
        } else if (strcmp(keyword_two, "amountToCall") == 0) {
            match->amount_to_call = atoi(value);
        }
    }
    else if (strcmp(keyword_one, "player1") == 0 || 
             strcmp(keyword_one, "player2") == 0) {
        short player = strcmp(keyword_one, settings->my_player) == 0 ? ME : OTHER;
        if (strcmp(keyword_two, "stack") == 0) {
            match->stack[player] = atoi(value);
        } else if (strcmp(keyword_two, "post") == 0) {
            match->bets[player][match->stage] += atoi(value);
        } else if (strcmp(keyword_two, "hand") == 0) {
            match->hand[player] = read_cards(value);
        } else if (strcmp(keyword_two, "fold") == 0) {
            // TODO Register fold?
        } else if (strcmp(keyword_two, "check") == 0 ||
                   strcmp(keyword_two, "call") == 0 ||
                   strcmp(keyword_two, "raise")) {
            match->bets[player][match->stage] += atoi(value);           
        } else if (strcmp(keyword_two, "wins") == 0) {
            // TODO am I interested in this?
            // End of round, but two people can win
        }
    }
    else if (strcmp(keyword_one, "Action") == 0) {
        return atoi(value);
    } 
    else if (strcmp(keyword_one, "Settings") == 0) {
        if (strcmp(keyword_two, "timeBank") == 0) {
            settings->time_bank = atoi(value);
        } else if (strcmp(keyword_two, "timePerMove") == 0) {
            settings->time_per_move = atoi(value);
        } else if (strcmp(keyword_two, "handsPerLevel") == 0) {
            settings->hands_per_level = atoi(value);
        } else if (strcmp(keyword_two, "startingStack") == 0) {
            settings->hands_per_level = atoi(value);
        } else if (strcmp(keyword_two, "yourBot") == 0) {
            strcpy(settings->my_player, value);
        }
    }
    else if (strcmp(keyword_one, "Quit") == 0) {
        exit(0);
    }
    return 0;
}

