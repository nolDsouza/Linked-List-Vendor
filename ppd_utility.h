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

#include <stdio.h>
#include "ppd_main.h"
#ifndef PPD_UTILITY
#define PPD_UTILITY
#define DOUBLE_DIGIT 10 
#define DOLLAR_MARK 100
#define MAX_DEPOSIT 4 
/**
 * @file ppd_utility.h defines some helper functions for the rest of your
 * program. In particular, it declares three of the most important 
 * functions for your application: @ref load_data which loads the data
 * in from files, @ref system_init which initialises the system to a 
 * known safe state and @ref system_free which frees all memory when you
 * are going to quit the application.
 **/

/**
 * the function to call for buffer clearing. This was discussed extensively
 * for assignment 1
 **/
void read_rest_of_line(void);

/**
 * Initialise the system to a known safe state. Before you post on the
 * discussion board about this, have a look at the structures as defined
 * in ppd_stock.h, ppd_coin.h and ppd_main.h. Given that nothing is 
 * initialized by the system if it
 * is a local variable, what would be good starting values for each of 
 * these. You already have some experience with this from assignment 
 * 1 to help you.
 **/
BOOLEAN system_init(struct ppd_system *);

/**
 * loads the stock file's data into the system. This needs to be 
 * implemented as part of requirement 2 of the assignment specification.
 **/
BOOLEAN load_stock(struct ppd_system *, const char *);

/**
 * loads the contents of the coins file into the system. This needs to
 * be implemented as part 1 of requirement 18.
 **/
BOOLEAN load_coins(struct ppd_system *, const char *);

/**
 * free all memory that has been allocated. If you are struggling to
 * find all your memory leaks, compile your program with the -g flag
 * and run it through valgrind. An important thing to think about here:
 * as malloc() returns a memory address to the first byte allocated, you
 * must pass each of these memory addresses to free, and no other 
 * memory addresses.
 **/
void system_free(struct ppd_system *);
/*
 *Both following methods aim to return a char * to resemble a price
 *they take in either a price stuct (two unsigned) or an int (no. of cents)
 *both will return a formatted string such as $3.05 
 */

/**
 * Convert the end part of an ID to a number
 **/ 
int get_id_val(struct ppd_node *);
/**
 * Functions for returning a formatted price string to print console
 **/ 
char * get_str_price(struct price);
char * get_str_int(int);
/**
 * Use ID number values comparitively to generate the next ID
 * All following functions are used for setting a new nodes attributes
 **/ 
void make_iD(struct ppd_list *, char *); 
BOOLEAN make_name(char *);
BOOLEAN make_description(char *);
BOOLEAN set_price(struct price *);

int get_valid_denom();
#endif
