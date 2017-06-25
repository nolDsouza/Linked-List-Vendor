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

#include "ppd_utility.h"
#include "ppd_coin.h" 
/**
 * @file ppd_utility.c contains implementations of important functions for
 * the system. If you are not sure where to implement a new function, 
 * here is probably a good spot.
 **/

void read_rest_of_line(void)
{
    int ch;
    /* keep retrieving characters from stdin until we
     * are at the end of the buffer
     */
    while(ch = getc(stdin), ch!='\n' && ch != EOF)
        ;
    /* reset error flags on stdin */
    clearerr(stdin);
}

/**
 * @param system a pointer to a @ref ppd_system struct that holds all 
 * the data for the system we are creating
 **/

 /**
  * Allocating memory for system's linked list
  * Setting head to null, so it is currently the end and empty
  **/
BOOLEAN system_init(struct ppd_system * system)
{
    system->item_list = (struct ppd_list*) malloc(sizeof(struct ppd_list));
    system->item_list->head = NULL;
    return TRUE;
}

/**
 * loads the stock file's data into the system. This needs to be 
 * implemented as part of requirement 2 of the assignment specification.
 **/
BOOLEAN load_stock(struct ppd_system * system, const char * filename)
{
    FILE *fr; 
    char line[MAX_LINE + EXTRACHARS];

    system->stock_file_name = filename;
    /* FILE used to read/write/append with secoond parameter */
    fr = fopen(system->stock_file_name, "r");
    
    if (!fr) {
        printf("\nfopen failed - could not open file: %s\n", filename);
        return FALSE;
    }
    /* For every line in file, try to create a node from it */
    while (fgets(line, MAX_LINE+EXTRACHARS, fr)!= NULL ) { 
        struct ppd_node *temp;
        /* Create a new node, and allocate it to heap */
        temp = (struct ppd_node*) malloc(sizeof(struct ppd_node));    
        temp->data = create_stock(line);
        /* Insert node into linked-list */
        if (add_stock(temp, system->item_list))
            system->item_list->count++;
      
    }
    fclose(fr);
    return TRUE;
}

/**
 * loads the contents of the coins file into the system. This needs to
 * be implemented as part 1 of requirement 18.
 **/
BOOLEAN load_coins(struct ppd_system * system, const char * filename)
{
    FILE *fr; 
    char line[COINLEN + EXTRACHARS];
    enum denomination index = TEN_DOLLARS;

    system->coin_file_name = filename;
    fr = fopen(system->coin_file_name, "r");
    
    if (!fr) {
        printf("\nfopen failed - could not open coin file: %s\n", filename);
        return FALSE;
    }
    /* For every line in file, try to create a node from it */
    while (fgets(line, COINLEN+EXTRACHARS, fr)!= NULL ) { 
        set_coin(line, &system->cash_register[index]);
        system->cash_register[index].denom = index;
        index--;
    }
    fclose(fr);
    return TRUE;

}
/**
 * Functions to convert print integers (cents) and price_structs as
 * conventional price strings e.g. 2.05
 **/
char * get_str_price(struct price p) {
    static char price[PRICELEN];
    sprintf(price, "%d.%02d", p.dollars, p.cents);
    return price;
}

char * get_str_int(int figure) {
    static char price[PRICELEN];
    unsigned dollars=0, cents;
    /* figure is the number of cents */
    /* division rounds down so dollars doesn't need to be float */
    if (figure >= DOLLAR_MARK) 
        dollars = figure/DOLLAR_MARK;
    cents = figure-(dollars*DOLLAR_MARK);
    
    sprintf(price, "$%d.%02d", dollars, cents);

    return price;
}

/**
 * Function to convert part of an ID to integer, for comparisons 
 **/
int get_id_val(struct ppd_node *node) {
    char *str, *end;
    char tempString[IDLEN] = "";

    strcpy(tempString, node->data->id);
    str = tempString + 1;
   
    return strtol(str, &end, 10);

}

/**
 * use get_id_val to find the last made ID no., then create the next one
 **/
void make_iD(struct ppd_list *list, char *id) {
    int temp;
    struct ppd_node *scanner = list->head;

    temp = get_id_val(list->head);

    while(scanner!=NULL) {
        
        if (temp < get_id_val(scanner)) 
            temp = get_id_val(scanner);
        scanner = scanner->next;
    }
    temp++;
    sprintf(id, "I%04d", temp);
}

/**
 * Following functions will get user input to assign name, desc, price
 **/
BOOLEAN make_name(char * name) {
    
    printf("\nEnter the item name:\n");
      
    if (fgets(name, NAMELEN+EXTRACHARS, stdin) == NULL )  
        return FALSE;
    if ( name[strlen(name)-1]!='\n') {
        printf("\nError: buffer overflow. ");
        read_rest_of_line();
        return make_name(name);
    }
    if (strcspn(name, "\n") == 0)
        return FALSE;

    name[strcspn(name, "\n")] = 0;

    return TRUE;
}

BOOLEAN make_description(char * description) {
    
    printf("\nEnter the description:\n");
      
    if (fgets(description, DESCLEN+EXTRACHARS, stdin) == NULL )  
        return FALSE;
    if ( description[strlen(description)-1]!='\n') {
        printf("\nError: buffer overflow. ");
        read_rest_of_line();
        return make_description(description);
    }
    if (strcspn(description, "\n") == 0)
        return FALSE;

    description[strcspn(description, "\n")] = 0;

    return TRUE;
}

BOOLEAN set_price(struct price *price) {
    static char input[PRICELEN];

    printf("\nEnter a price, including dollars and cents:\n");
    /* Not abstracting these validations, they don't necessarilly 
       have to respond the same, and second parameter cannot be variable */
    if (fgets(input, PRICELEN+EXTRACHARS, stdin) == NULL )  
        return FALSE;
    if ( input[strlen(input)-1]!='\n') {
        printf("\nError: buffer overflow. ");
        read_rest_of_line();
        return set_price(price);
    }
    if (strcspn(input, "\n") == 0)
        return FALSE;
    /* Checking input is somewat in the right format, but the set_price()
        function will do most validation seeing as it was pre-written */
    if (strcspn(input, ".") == 0) {
        printf("Error: incorrect format, please try again\n");
        return set_price(price);
    }
    
    input[strcspn(input, "\n")] = 0;
    
    if (create_price(input, price) == FALSE)
        return set_price(price);

    return TRUE;
}

int get_valid_denom() {
    char input[MAX_DEPOSIT + EXTRACHARS], *end; 
    static int deposit;

    if (fgets(input, MAX_DEPOSIT + EXTRACHARS, stdin)== NULL)
        return 0;

    if(input[strlen(input)-1]!='\n') {
        printf("Error: buffer overflow\n");
        read_rest_of_line();
        return get_valid_denom();
    }

    if (strcspn(input, "\n") == 0)
        return 0;

    input[strcspn(input, "\n")] = 0;

    deposit = (int) strtol(input, &end, 0);
    if (*end || deposit < 0) {
        printf("Error: that is not a valid number\n");
        return get_valid_denom();
    }

    if (!check_denoms(deposit)) {
        printf("Error: "
        "%s is not a valid denomination of money\n", get_str_int(deposit));
        return get_valid_denom();
    }

    return deposit;
}
/**
 * @param system a pointer to a @ref ppd_system struct that holds all 
 * the data for the system we are creating
 **/

 /**
 * Free all allocated memory that was allocated initially and not freed
 * This time head will traverse the list, and temp will 
 * free the left behind node
 **/
void system_free(struct ppd_system * system)
{
   struct ppd_node *temp;

   while (system->item_list->head != NULL)
    {
       temp = system->item_list->head;
       system->item_list->head = system->item_list->head->next;
       free(temp->data);
       free(temp);
    }
    /* finally free the list structure from init_system() */
    free(system->item_list);
}
