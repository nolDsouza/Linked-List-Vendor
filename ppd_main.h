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
#include <stdlib.h>
#include "ppd_coin.h"
#include "ppd_shared.h"
#include "ppd_stock.h"

#define EXTRACHARS 2
#define TRAILS 4  
/* Max line for reading one line from stock text file */ 
#define MAX_LINE IDLEN + NAMELEN + DESCLEN + PRICELEN + TRAILS
/* Minimal input to make easier input validation */ 
#define MENU_INPUT 1


#ifndef PPD_MAIN
#define PPD_MAIN
/**
 * @file ppd_main.h this file holds the rest of the application together.
 * From these header files, main() can call all functions refered to 
 * in the header files included. You might also want to insert here
 * any functions for handling and validation of command line arguments
 **/

#endif
