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
#include <string.h> 
#include <stdlib.h> 
#include "ppd_shared.h" 
/**
 * @file ppd_coin.h defines the coin structure for managing currency in the
 * system. You should declare function prototypes for managing coins here
 * and implement them in ppd_coin.c
 **/
#ifndef PPD_COIN
#define PPD_COIN
#define COIN_DELIM ","
#define CHANGE_LEN 25 
struct ppd_system;
/**
 * enumeration representing the various types of currency available in
 * the system. 
 **/
enum denomination
{
    FIVE_CENTS, TEN_CENTS, TWENTY_CENTS, FIFTY_CENTS, ONE_DOLLAR, 
    TWO_DOLLARS, FIVE_DOLLARS, TEN_DOLLARS
};

enum value
{
    a = 5, b = 8, c=9
};
/**
 * represents a coin type stored in the cash register. Each demonination
 * will have exactly one of these in the cash register.
 **/
struct coin
{
    /**
     * the denomination type
     **/
    enum denomination denom;
    /**
     * the count of how many of these are in the cash register
     **/
    unsigned count;
};
int get_denom_value(enum denomination);
BOOLEAN check_denoms(int);
BOOLEAN set_coin(char *, struct coin *);
BOOLEAN check_change(int, struct coin *);
BOOLEAN get_change(int, struct coin *);
#endif
