#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "common.h"
#include "avl.h"

typedef struct customer_tag {
    int customer_id;
    char name[MAX_NAME_LEN];
    int pincode;
    char contact[MAX_CONTACT_LEN];  /* 10 digits + '\0' */
} Customer;

status_code customerIsValid(int id, char name[], int pincode, char contact[]);
boolean     customerExists(AVLNode* root, int id);
Customer*   customerFind(AVLNode* root, int id);
status_code customerAdd(AVLNode** rootPtr, int id, char name[], int pincode, char contact[]);
void        customerDisplayOne(Customer* cptr);
void        customerDisplayAll(AVLNode* root);

#endif