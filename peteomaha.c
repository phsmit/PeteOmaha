/* 
 * File:   peteomaha.c
 * Author: psmit
 *
 * Created on May 26, 2014, 3:31 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "parsing.h"
/*
 * 
 */
int main(int argc, char** argv) {          
    size_t nbytes = 100;
    char *line;
    
    po_settings *settings;
    po_match *match;
    
    line = (char *) malloc(nbytes + 1);
    
    int action_time = 0;
    while(getline(&line, &nbytes, stdin))
    {
        action_time = po_parse_next_line(line, match, settings);
        if (action_time) {
            puts("check 0");
            fflush(stdout);
        }
    }

    return (EXIT_SUCCESS);
}

