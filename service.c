#include "service.h"

status_code serviceIsValid(int id, char name[], float base_price) {
    status_code ret_val = FAILURE;

    if (id > 0 && name != NULL && name[0] != '\0' && base_price > 0) {
        ret_val = SUCCESS;
    }

    return ret_val;
}

Service* serviceFind(AVLNode* root, int id) {
    Service* ret_val;

    ret_val = (Service*)avlSearch(root, id);    // void* becomes service*

    return ret_val;
}

boolean serviceExists(AVLNode* root, int id) {
    boolean isfound = FALSE;

    if (serviceFind(root, id) != NULL) {
        isfound = TRUE;
    }

    return isfound;
}

status_code serviceAdd(AVLNode** rootPtr, int id, char name[], float base_price) {
    status_code ret_val = FAILURE;
    Service* svc;
    

    if (serviceIsValid(id, name, base_price) == SUCCESS
        && serviceExists(*rootPtr, id) == FALSE) {

        svc = (Service*)malloc(sizeof(Service));

        if (svc != NULL) {
            svc->service_id = id;
            strncpy(svc->name, name, MAX_SERVICE_NAME_LEN - 1);
            svc->name[MAX_SERVICE_NAME_LEN - 1] = '\0';
            svc->base_price = base_price;

            *rootPtr = avlInsert(*rootPtr, id, svc);
            ret_val = SUCCESS;
        }
    }

    return ret_val;
}

void serviceDisplayOne(Service* sptr) {
    printf("%-6d %-25s Rs. %.2f\n", sptr->service_id, sptr->name, sptr->base_price);
}

void serviceDisplayAll(AVLNode* root) {
    
    if (root != NULL) {
        serviceDisplayAll(root->left);
        serviceDisplayOne((Service*)root->data);
        serviceDisplayAll(root->right);
    }
}