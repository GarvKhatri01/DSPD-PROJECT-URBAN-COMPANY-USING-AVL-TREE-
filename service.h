#ifndef SERVICE_H
#define SERVICE_H

#include "common.h"
#include "avl.h"

typedef struct service_tag {
    int service_id;
    char name[MAX_SERVICE_NAME_LEN];
    float base_price;
} Service;                          /* no 'next' pointer now, the tree does the linking */

status_code serviceIsValid(int id, char name[], float base_price);
boolean     serviceExists(AVLNode* root, int id);
Service*    serviceFind(AVLNode* root, int id);
status_code serviceAdd(AVLNode** rootPtr, int id, char name[], float base_price);
void        serviceDisplayOne(Service* sptr);
void        serviceDisplayAll(AVLNode* root);

#endif