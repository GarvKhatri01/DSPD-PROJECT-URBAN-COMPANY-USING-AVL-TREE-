#include "customer.h"

static int countDigitsCust(int n) {
    int digits  = 0;

    while (n > 0) {
        digits++;
        n = n / 10;
    }

    return digits;
}

static boolean allDigitsCust(char s[]) {
    boolean alldigits = TRUE;
    int i = 0;

    while (s[i] != '\0' && alldigits == TRUE) {

        if (s[i] < '0' || s[i] > '9') {
            alldigits = FALSE;
        }
        i++;
    }

    return alldigits;
}

status_code customerIsValid(int id, char name[], int pincode, char contact[]) {

    status_code isValid= FAILURE;

   

    if (id > 0 && name != NULL && name[0] != '\0'
        && countDigitsCust(pincode) == PINCODE_DIGITS
        && contact != NULL && strlen(contact) == 10
        && allDigitsCust(contact) == TRUE) {
            isValid = SUCCESS;
    }

    return isValid;
}

Customer* customerFind(AVLNode* root, int id) {

    return (Customer*)avlSearch(root, id);
}

boolean customerExists(AVLNode* root, int id) {
    boolean isfound = FALSE;

    if (customerFind(root, id) != NULL) {
        isfound = TRUE;
    }

    return isfound;
}

status_code customerAdd(AVLNode** rootPtr, int id, char name[], int pincode, char contact[]) {
    status_code ret_val = FAILURE;
    Customer* cust;


    if (customerIsValid(id, name, pincode, contact) == SUCCESS
        && customerExists(*rootPtr, id) == FALSE) {

        cust = (Customer*)malloc(sizeof(Customer));

        if (cust != NULL) {

            cust->customer_id = id;
            strncpy(cust->name, name, MAX_NAME_LEN - 1);
            cust->name[MAX_NAME_LEN - 1] = '\0';
            cust->pincode = pincode;
            strncpy(cust->contact, contact, MAX_CONTACT_LEN - 1);
            cust->contact[MAX_CONTACT_LEN - 1] = '\0';

            *rootPtr = avlInsert(*rootPtr, id, cust);
            ret_val = SUCCESS;
        }
    }

    return ret_val;
}

void customerDisplayOne(Customer* cptr) {
    printf("%-6d %-20s %d  %s\n", cptr->customer_id, cptr->name,
           cptr->pincode, cptr->contact);
}

void customerDisplayAll(AVLNode* root) {
    if (root != NULL) {
        customerDisplayAll(root->left);
        customerDisplayOne((Customer*)root->data);
        customerDisplayAll(root->right);
    }
}
