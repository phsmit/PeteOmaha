cmake_minimum_required(VERSION 2.8)
PROJECT(PeteOmaha)

add_subdirectory( vendor )

include_directories("include")
include_directories("vendor/poker-eval/include")
#include_directories(${POKEREVAL_INCLUDEDIRS})

add_executable( peteomaha programs/peteomaha.c )
add_executable( pregen programs/pregen.c )
add_executable( test_starting_hands programs/test_starting_hands.c )
add_executable( print_unique_hands programs/print_unique_hands.c )
add_executable( classify_hands programs/classify_hands.c )

target_link_libraries ( pregen pokereval )
target_link_libraries ( peteomaha pokereval )
target_link_libraries ( test_starting_hands pokereval)
target_link_libraries ( print_unique_hands pokereval)
target_link_libraries ( classify_hands pokereval)

add_executable( test_search programs/test_search.c )
target_link_libraries (test_search pokereval)