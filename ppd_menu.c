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

#include "ppd_menu.h"
#include "ppd_options.h" 
/**
 * @file ppd_menu.c handles the initialised and management of the menu 
 * array
 **/

/**
 * @param menu the menu item array to initialise
 **/
void init_menu( struct menu_item* menu)
{
	int i;
	char *menu_names[NUM_MENU_ITEMS]  = {
		"1.Display Items\n",
    	"2.Purchase Items\n",
    	"3.Save and Exit\n",
    	"4.Add Item\n",
    	"5.Remove Item\n",
    	"6.Display Coins\n",
    	"7.Reset Stock\n",
    	"8.Reset Coins\n",
    	"9.Abort Program\n" 
    };
    BOOLEAN (*menu_function[NUM_MENU_ITEMS])(struct ppd_system*) = {
    	display_items,
    	purchase_item,
    	save_system,
    	add_item,
    	remove_item,
    	display_coins,
    	reset_stock,
    	reset_coins,
    	abort_program 
    };

    /*Declared arrays to be assigned to menu_item attributes */

    for (i = 0; i < NUM_MENU_ITEMS; i++) {
    	strcpy(menu[i].name, menu_names[i]);
    	menu[i].function = menu_function[i];
    }
}

/**
 * @return a menu_function that defines how to perform the user's
 * selection
 **/
menu_function get_menu_choice(struct menu_item * menu)
{
	char input[MENU_INPUT + EXTRACHARS], *end;
	int index;

	display_menu(menu);
	/* Checking ctrl+d input immediately */
	if ( fgets (input, MENU_INPUT+EXTRACHARS, stdin)==NULL )
	{
	    printf("\n\nThat is not a valid option. Please try again.");
	    return get_menu_choice(menu);
	}
	/* Checking for buffer overflow (this case input over 1 char) */
	if ( input[strlen(input)-1]!='\n')
	{
	    printf("\nError: buffer overflow. ");
	    read_rest_of_line();
	    return get_menu_choice(menu);
	}

	/* Remove newline character, change input to comparable number */
	input[strcspn(input, "\n")] = 0;
	index = strtol(input, &end, 0);

	/* Checking for non-numeric input */
	if (*end || !index) {
		printf("\n\nThat is not a valid option. Please try again.");
		return get_menu_choice(menu);
	}
	/* Will need more validation for if NUM_MENU_ITEMS > 9 */
	return menu[index-1].function;
}

/* Function to display all menu_item names, not hardcoded */
void display_menu(struct menu_item * menu) {
	int i;

	printf("\n\nMain Menu:\n");
	for (i = 0; i < NUM_MENU_ITEMS; i++) {
		printf("%s", menu[i].name);
	}
	printf("Select your option (1-9):");
}