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

#include "ppd_options.h"

/**
 * @file ppd_options.c this is where you need to implement the main 
 * options for your program. You may however have the actual work done
 * in functions defined elsewhere. 
 * @note if there is an error you should handle it within the function
 * and not simply return FALSE unless it is a fatal error for the 
 * task at hand. You want people to use your software, afterall, and
 * badly behaving software doesn't get used.
 **/

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true as this particular function should never fail.
 **/
BOOLEAN display_items(struct ppd_system * system)
{
    struct ppd_node *ptr = system->item_list->head;
    int name_format;
    /* !ptr means the head points to null */
    if (!ptr) {
        printf("Error: list is empty\nreturning to main menu...");
        return FALSE;
    }
    /* setting name format to get maximum padding required for names */
    name_format = strlen(ptr->data->name);
   
    while(ptr->next != NULL)
    {       
        ptr = ptr->next;
        if (name_format < strlen(ptr->data->name))
            name_format = strlen(ptr->data->name);
    }
    printf("\nItems menu\n\n");
    /* Variable padding indicated with '*' */
    printf("%-5s | %-*s | Available | Price\n", "ID", name_format, "Name");

    /* Now traverse list and print information */
    ptr = system->item_list->head;
    while(ptr != NULL)
    {        
        printf("%s | %-*s | %-9d | $%2s\n", 
        ptr->data->id, name_format, ptr->data->name, ptr->data->on_hand,
        get_str_price(ptr->data->price));
        ptr = ptr->next;
    }
    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true when a purchase succeeds and false when it does not
 **/
 /**
 * This function will select a node from the system Item list
 * It will then convert that selected node's price into variable sale
 * It will then loop getting user input the sum of all inputs 
 * exceeds the sale price or return false if input is ctrl-d or enter
 **/
BOOLEAN purchase_item(struct ppd_system * system)
{
    int sale, deposit;
    struct ppd_node *selected;
    printf("Purchase Items\n--------------\n");
    printf("Please enter the id of the item you wish to purchase: ");
    selected = select_node(system->item_list);
    if (!selected)
        return FALSE;
    printf("You have selected \"%s  %s\" ", 
        selected->data->name, selected->data->desc);
    sale = ((selected->data->price.dollars*100) 
        + selected->data->price.cents); 
    printf("This will cost you : %s", get_str_int(sale));
    printf(".\nPlease hand over the money - type in the value of "
        "each note/coin in cents.\n"
        "Press enter on a new and empty line to cancel this purchase:");

   while (sale > 0) {
        deposit = get_valid_denom();
        if (!deposit)
            return FALSE;
        sale -= (int) deposit;
        if (sale > 0)
            printf("You still need to give us %s:", get_str_int(sale)); 
    }
    if (sale < 0) {
        if (check_change(-sale, system->cash_register)) {
            printf("Thank you. Here is your %s, and your change of %s: ",
                selected->data->name, get_str_int(-sale)); 
            get_change(-sale, system->cash_register);
            printf("Please come back soon.\n"); 
        }
    }
    else
        printf("Thank you.\nPlease come back soon.\n");
    selected->data->on_hand--;
    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true when a save succeeds and false when it does not
 **/
BOOLEAN save_system(struct ppd_system * system)
{
    FILE *fw; 
    struct ppd_node *temp = system->item_list->head;
    enum denomination i;
    /* using the same file name taht was passed as an arguement */
    fw = fopen(system->stock_file_name, "w");
    /* printing all data to one line */

    if (!fw) {
        return FALSE;
    }

    while (temp != NULL) {
        fprintf(fw, "%s|%s|%s|%s|%d\n", temp->data->id, temp->data->name,
            temp->data->desc, get_str_price(temp->data->price), 
            temp->data->on_hand);

        temp = temp->next;
    }

    fw = fopen(system->coin_file_name, "w");

    for (i=TEN_DOLLARS-1; i>FIVE_CENTS; i--) {
        fprintf(fw, "%d,%d\n", get_denom_value(i), 
            system->cash_register[i].count);
    }

    fclose(fw);
    return abort_program(system);
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true when adding an item succeeds and false when it does not
 **/

 /**
 * This is a long function seeing as it requires 3 inputs 
 * There are seperate function which set the attributes of a 
 * new node struct. Then insert to system Item list
 **/
BOOLEAN add_item(struct ppd_system * system)
{
    /* Allocating space for a new node */
    struct ppd_node *new_node = malloc(sizeof(struct ppd_node));
    new_node->data = malloc(sizeof(struct ppd_stock));
    /* Setting each attribute */
    make_iD(system->item_list, new_node->data->id);

    if (!make_name(new_node->data->name)) {
        free(new_node->data);
        free(new_node);
        return FALSE;
    }

    if (!make_description(new_node->data->desc)) {
        free(new_node->data);
        free(new_node);
        return FALSE;
    }

    if (!set_price(&new_node->data->price)) {
        free(new_node->data);
        free(new_node);
        return FALSE;
    }

    new_node->data->on_hand = DEFAULT_STOCK_LEVEL;
    
    /* Insert node */
    if (add_stock(new_node, system->item_list))
        system->item_list->count++;
    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true when removing an item succeeds and false when it does not
 **/
BOOLEAN remove_item(struct ppd_system * system)
{
    /* temp is the node selected to remove, traverser will scan the list */
    struct ppd_node *temp, *traverser = system->item_list->head;

    puts("Enter the id to remove: ");
    temp = select_node(system->item_list);
    /* user elected to quit function in this case e.g. ctrl-d */
    if (!temp) 
        return FALSE;
    /* No need to validate temp exists, select_node() does this */
    if (traverser == temp) {
        system->item_list->head = temp->next;
    }
    else {
        while(traverser != NULL) {
            if (traverser->next == temp) {
                traverser->next = temp->next;
            }
            traverser = traverser->next;
        }
    }
    /* free node now or it's reference will be lost */
    printf("\"%s - %s %s\" has been removed\nfrom the system.\n",
    temp->data->id, temp->data->name, temp->data->desc);
    free(temp->data);
    free(temp);
    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true as this function cannot fail.
 **/

/**
 * Funtiion simply iterates over all nodes and sets on_hand to 20
  **/ 
BOOLEAN reset_stock(struct ppd_system * system)
{
    struct ppd_node *traverser = system->item_list->head;

    if (!traverser) {
        printf("Error: list is empty\nreturning to main menu...");
        return FALSE;
    }

    while (traverser != NULL) {
        traverser->data->on_hand = DEFAULT_STOCK_LEVEL;
        traverser = traverser->next;
    }
    
    printf("All stock has been reset to the default"
        "level of %d\n", DEFAULT_STOCK_LEVEL);
    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true as this function cannot fail.
 **/
BOOLEAN reset_coins(struct ppd_system * system)
{
    enum denomination i;
    if (!system->coin_from_file) {
        printf("functionality not available\n");
        return FALSE;
    }
    
    for (i = FIVE_CENTS; i < NUM_DENOMS; i++) {
        system->cash_register[i].count = DEFAULT_COIN_COUNT;
    }

    printf("All coins have been reset to the default"
    "level of %d\n", DEFAULT_COIN_COUNT);
    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true as this function cannot fail
 **/
BOOLEAN display_coins(struct ppd_system * system)
{
    if (!system->coin_from_file) {
        printf("functionality not available\n");
        return FALSE;
    }
    printf("Coins Summary\n---------\n"
        "Denomination | Count\n\n"
        "5 cents %6s %d\n"
        "10 cents %5s %d\n"
        "20 cents %5s %d\n"
        "50 cents %5s %d\n"
        "1 dollar %5s %d\n"
        "2 dollar %5s %d\n"
        "5 dollar %5s %d\n"
        "10 dollar %4s %d\n",
        "|", system->cash_register[FIVE_CENTS].count, 
        "|", system->cash_register[TEN_CENTS].count, 
        "|", system->cash_register[TWENTY_CENTS].count,
        "|", system->cash_register[FIFTY_CENTS].count,  
        "|", system->cash_register[ONE_DOLLAR].count,
        "|", system->cash_register[TWO_DOLLARS].count, 
        "|", system->cash_register[FIVE_DOLLARS].count, 
        "|", system->cash_register[TEN_DOLLARS].count);

    return TRUE;
}
/**
 * Implemented this function so that it could be part of the menu array
 */
BOOLEAN abort_program(struct ppd_system * system) {
    system_free(system);
    /* this is hopefully the only way to close program */
    exit(EXIT_SUCCESS); 
}