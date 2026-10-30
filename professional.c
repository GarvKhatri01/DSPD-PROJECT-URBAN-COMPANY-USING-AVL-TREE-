#include "professional.h"

static int countDigitsPro(int n) {
    int digits  = 0;

    while (n > 0) {
        digits++;
        n = n / 10;
    }

    return digits;
}

static boolean allDigitsPro(char s[]) {
    boolean allDigits = TRUE;
    int i =0;

    while (s[i] != '\0' && allDigits == TRUE) {
        if (s[i] < '0' || s[i] > '9') {
            allDigits = FALSE;
        }
        i++;
    }

    return allDigits;
}

 //count must be 1..5, every id must exist in the service tree, no repeats 
static boolean servicesAreValid(AVLNode* serviceRoot, int svc_ids[], int svc_count) {
    boolean isValid = TRUE;
    int i,j;


    if (svc_ids == NULL || svc_count < 1 || svc_count > MAX_SERVICES_PER_PROFESSIONAL) {
        isValid = FALSE;
    }

    i = 0;
    while (i < svc_count && isValid == TRUE) {
        if (serviceExists(serviceRoot, svc_ids[i]) == FALSE) {
            isValid = FALSE;
        }

        j = 0;
        while (j < i && isValid == TRUE) {         //compare service id with others 
            if (svc_ids[j] == svc_ids[i]) {
                isValid = FALSE;
            }
            j++;
        }

        i++;
    }

    return isValid;
}



status_code professionalRegister(AVLNode** proRootPtr, AVLNode* serviceRoot, int id,
                                 char name[], int pincode, char contact[],int svc_ids[], int svc_count) {
    status_code ret_val;
    Professional* pro;
    int i;

    ret_val = FAILURE;

    if (id > 0 && name != NULL && name[0] != '\0'
        && countDigitsPro(pincode) == PINCODE_DIGITS
        && contact != NULL && strlen(contact) == 10
        && allDigitsPro(contact) == TRUE
        && servicesAreValid(serviceRoot, svc_ids, svc_count) == TRUE
        && professionalExists(*proRootPtr, id) == FALSE) {

        pro = (Professional*)malloc(sizeof(Professional));

        if (pro != NULL) {
            pro->professional_id = id;
            strncpy(pro->name, name, MAX_NAME_LEN - 1);
            pro->name[MAX_NAME_LEN - 1] = '\0';
            pro->pincode = pincode;
            strncpy(pro->contact, contact, MAX_CONTACT_LEN - 1);
            pro->contact[MAX_CONTACT_LEN - 1] = '\0';
            pro->availability = AVAILABLE;          /* new professionals start free */

            pro->service_count = svc_count;
            for (i = 0; i < svc_count; i++) {
                pro->service_ids[i] = svc_ids[i];
            }

            *proRootPtr = avlInsert(*proRootPtr, id, pro);
            ret_val = SUCCESS;
        }
    }

    return ret_val;
}


Professional* professionalFind(AVLNode* root, int id) {
    return (Professional*)avlSearch(root, id);
}

boolean professionalExists(AVLNode* root, int id) {
    boolean isfound = FALSE;

    if (professionalFind(root, id) != NULL) {
        isfound = TRUE;
    }

    return isfound;
}

boolean professionalOffers(Professional* pro, int svc_id) {
    boolean isoffer = FALSE;
    
    int i =0;
    while (i < pro->service_count && !isoffer) {
        if (pro->service_ids[i] == svc_id) {
           isoffer = TRUE;
        }
        i++;
    }

    return isoffer;
}

boolean professionalIsAvailable(Professional* pro) {
    boolean isAvail = FALSE;

    if (pro->availability == AVAILABLE) {
        isAvail = TRUE;
    }

    return isAvail;
}

void professionalSetAvailability(Professional* pro, AvailabilityStatus status) {
    pro->availability = status;
}

void professionalDisplayOne(Professional* pro) {
    

    printf("%-6d %-20s %d  %s  %s  Services:",
           pro->professional_id, pro->name, pro->pincode, pro->contact,
           (pro->availability == AVAILABLE) ? "Available" : "Busy");


    for (int i = 0; i < pro->service_count; i++) {
        printf(" %d", pro->service_ids[i]);
    }
    printf("\n");
}


void professionalDisplayAll(AVLNode* root) {
    if (root != NULL) {
        professionalDisplayAll(root->left);
        professionalDisplayOne((Professional*)root->data);
        professionalDisplayAll(root->right);
    }
}




