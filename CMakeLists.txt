cmake_minimum_required(VERSION 2.8)
PROJECT(PeteOmaha)

add_subdirectory( vendor )

include_directories("include")
include_directories("vendor/poker-eval/include")
#include_directories(${POKEREVAL_INCLUDEDIRS})

set(PO_FILES
lib/omaha_calc.c
lib/parsing.c
lib/preflop_holes.c
lib/t_probtables.c
)

set(PO_CMDS
build_probs_file
hole_probs 
peteomaha 
unique_holes
)

foreach(PO_CMD ${PO_CMDS})
    add_executable ( ${PO_CMD} programs/${PO_CMD}.c ${PO_FILES})
    target_link_libraries ( ${PO_CMD} pokereval )
endforeach(PO_CMD)