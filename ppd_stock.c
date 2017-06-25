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

/**
 * This function coverts a line from text into a new node
 **/
struct ppd_stock * create_stock(char *line) {
    char *tok, *end, *data_strings[NUM_ATTRIBUTES];
    int count = 0;
    struct ppd_stock * data; 
    /* Allocating memory for ppd_stock, 
                         the node will be allocated externally */
    data = (struct ppd_stock *)malloc(sizeof(struct ppd_stock));
    tok = strtok(line, DELIMITER);
	
    while(tok!=NULL)
    {
    	data_strings[count] = tok; 
        tok = strtok(NULL, DELIMITER);
        count++;
    }
     /* data_strings is an array of char pointers, each index
        corresponds to one token, which is one attribute */ 
    strcpy(data->id, data_strings[ID_REF]);
    strcpy(data->name, data_strings[NAME_REF]);
    strcpy(data->desc, data_strings[DESC_REF]);
    /* Price needs to be further modified, so this is abstracted */
    create_price(data_strings[PRICE_REF], &data->price);
    data->on_hand = strtol(data_strings[QUANT_REF], &end, 0);

    if(!data)
        return NULL; 
    return data;
}
/** 
 * This function will convert a string 7.6 into two unsigned
 * integers which make up the price struct
 **/
BOOLEAN create_price(char *line, struct price *p) {
    char *ptr, *end;
    int dollars, cents;
    /* get first token, which is for doollars */
    ptr = strtok(line, DOT);
    if (!ptr) {
        printf("Error incorrect dollar format");
        return FALSE;
    }
    /* Try to convert into a number */
    dollars = strtol(ptr, &end, 0);
    if(*end) {
    	printf("Error non numeric dollar input\n");
        return FALSE;
    }
    /* Hardcoded the next token, seeing as there should only be 1 */
    ptr = strtok(NULL, "");
    if (!ptr) {
        printf("Error incorrect cents format");
        return FALSE;
    }

    cents = strtol(ptr, &end, 0);
    if(*end)
    {
    	printf("Error non numeric cents input\n");
        return FALSE;
    }

    if (dollars >= MAX_PRICE) {
        printf("Error too expensive, keep prices under $9.95\n");
        return FALSE;
    }

    if (cents % MIN_DENOM) {
        printf("Error, make sure input is divisible by 5\n");
        return FALSE;
    }
    /* Assigning numbers to price struct */
    p->dollars = dollars;
    p->cents = cents;

    return TRUE;
}

/**
 * Two functions work together to insert nodes in an alphabetical
 * order. add_stock will choose the position, then insert_stock
 * will add the node to the list 
 **/
BOOLEAN add_stock(struct ppd_node *node, struct ppd_list *list) {
    /* Temp is traversal node */
    struct ppd_node *temp;
    int position = 0;

    temp = list->head;

    /* loop does not execute for entry at beginning 
        strcmp returns negative if temp is alphabetically ordered
        after current node */
    while(temp!=NULL && strcmp(temp->data->name, node->data->name) < 0) {
        temp= temp->next;
        position++;
    }

    return insert_stock(node, list, position);
}
/**
 * Function has to return int seeing as it is the return od add_stock
 * It will insert a node at position n
 **/
BOOLEAN insert_stock(struct ppd_node *node, 
                            struct ppd_list *list, int n) {
    struct ppd_node *temp = list->head;
    int i = 0;
    /* beggining case */
    if (n==0) {
        node->next=list->head;
        list->head=node;
        return TRUE;
    }
    /* move to the n-1 position */
    for (i = 0; i<n-1;i++) {
        temp = temp->next;
    }

    node->next = temp->next;
    temp->next = node;

    return TRUE;
}
/**
 * This function will get user input
 * If that input is a node ID, pointer to that node is returned
 */

struct ppd_node * select_node(struct ppd_list *list) {
    char input[IDLEN + EXTRACHARS], count = 0;
    struct ppd_node *traverser = list->head;

    if(!traverser) {
        printf("list is empty\n");
        return NULL;
    }

    if (fgets (input, IDLEN+EXTRACHARS, stdin)==NULL )
        return NULL;

    if (input[strlen(input)-1]!='\n') {
            printf("\nError: buffer overflow. ");
            read_rest_of_line();
            return select_node(list);
    }

    if (strcspn(input, "\n") == 0)
        return NULL;

    input[strcspn(input, "\n")] = 0;

    count++;
    while(strcmp(input, traverser->data->id)) {
        /*checking traverser is not at the end of the list */
        if(traverser->next == NULL) {
            printf("invalid id please try again:\n");
            return select_node(list);
        }
        else 
            /*move to next node */
            traverser = traverser->next;
            count++;
    } 
    return traverser;
}

 /**
  * @file ppd_stock.c this is the file where you will implement the 
  * interface functions for managing the stock list.
  **/
