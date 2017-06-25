/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #2
 * Full Name        : Neil D'souza
 * Student Number   : s3600251
 * Course Code      : COOSC1076
 * Program Code     : BP096
 * Start up code provided by Paul Miller
 * Some codes are adopted here with permission by an anonymous author
 ***********************************************************************/

#include "ppd_main.h"
#include "ppd_menu.h"
#include "ppd_options.h"
#include "ppd_utility.h"
#include <stdio.h>

/**
 * @file ppd_main.c contains the main function implementation and any 
 * helper functions for main such as a display_usage() function.
 **/

/**
 * manages the running of the program, initialises data structures, loads
 * data and handles the processing of options. The bulk of this function
 * should simply be calling other functions to get the job done.
 **/

int main(int argc, char **argv)
{
    /* uncomment this menu structure when you are ready to work on the 
     * menu system with function pointers */
    struct menu_item menu[NUM_MENU_ITEMS]; 
    /* represents the data structures to manage the system */
    struct ppd_system system;
    system_init(&system);
    
     /* validate command line arguments */
    if (argc < 2) {
        printf("Error: not enough arguements\n");
        return EXIT_SUCCESS;
    }
    else if (argc > 3) {
        printf("Error: too many arguements\n");
        return EXIT_SUCCESS;
    }
    /* check for a coins arguement */
    
    system.coin_from_file = FALSE;
    
    /* load data  */
    if (!load_stock(&system, *++argv))
        return EXIT_SUCCESS;
    /* load coins, but exit if load fails */
    if (argc == 3) {
        system.coin_from_file = TRUE;
        if (!load_coins(&system, *++argv))
            return EXIT_SUCCESS;
    }

    /* test if everything has been initialised correctly */
    /* initialise the menu system */
    init_menu(menu);
    do {
        (*get_menu_choice(menu))(&system);
    }  while (TRUE);
       
    /* until the user quits */
}
