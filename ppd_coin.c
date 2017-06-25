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
#include "ppd_coin.h"


 /**
  * @file ppd_coin.c implement functions here for managing coins in the
  * "cash register" contained in the @ref ppd_system struct.
  **/

BOOLEAN set_coin(char *line, struct coin *coin) {
    char *ptr, *end;
    int count;
    /* get first token, which is for dollars */
    ptr = strtok(line, COIN_DELIM);

    ptr = strtok(NULL, "\n");
    if (!ptr) {
        printf("Error incorrect count format");
        return FALSE;
    }
    count = strtol(ptr, &end, 0);
    if(*end)
    {
    	printf("Error non numeric coin quantity\n");
        return FALSE;
    }
    /* Assigning numbers to price struct */
    coin->count = count;

    return TRUE;
}

int get_denom_value(enum denomination denom) {
	switch (denom) {
		case FIVE_CENTS: return 5;
		case TEN_CENTS: return 10;
		case TWENTY_CENTS: return 20;
		case FIFTY_CENTS: return 50;
		case ONE_DOLLAR: return 100;
		case TWO_DOLLARS: return 200;
		case FIVE_DOLLARS: return 500;
		case TEN_DOLLARS: return 1000;
		default: return 0;
	}
}

BOOLEAN check_denoms(int input) {
	enum denomination i;

	for (i=FIVE_CENTS; i<=TEN_DOLLARS; i++) {
		if (get_denom_value(i) == input) {
			return TRUE;
		}
	}
	return FALSE;
}

BOOLEAN check_change(int objective, struct coin *cashRegister) {
	enum denomination change = TEN_DOLLARS;
	int check_change = cashRegister[change].count;


	while (objective > 0 && check_change > 0) {
		if (get_denom_value(change) <= objective) {
			objective -= get_denom_value(change);
			check_change--;
		}
		else {
			change--;
			check_change = cashRegister[change].count;
		}
	}
	if (objective == 0) {
		return TRUE;
	}
	return FALSE;
}

BOOLEAN get_change(int objective, struct coin *cashRegister) {
	enum denomination change = TEN_DOLLARS;

	while (objective > 0 && cashRegister[change].count > 0) {

		if (get_denom_value(change) <= objective) {

			if (get_denom_value(change) >= 100) {
				printf("$%d ", (get_denom_value(change)/100));
			}
			else
				printf("%dc ", get_denom_value(change));

			objective -= get_denom_value(change);
			cashRegister[change].count--;
		}
		else {
			change--;
		}
	
	}
	printf("\n");
	
	return TRUE;

}