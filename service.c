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

    ret_val = (Service*)avlSearch(root, id);    /* void* becomes Service* */

    return ret_val;
}