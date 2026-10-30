#ifndef PROFESSIONAL_H
#define PROFESSIONAL_H

#include "common.h"
#include "avl.h"
#include "service.h"

typedef struct professional_tag {
    int professional_id;
    char name[MAX_NAME_LEN];
    int pincode;
    char contact[MAX_CONTACT_LEN];
    AvailabilityStatus availability;
    int service_ids[MAX_SERVICES_PER_PROFESSIONAL];   /* the "at most 5" rule */
    int service_count;
} Professional;

status_code   professionalRegister(AVLNode** proRootPtr, AVLNode* serviceRoot, int id,
                                   char name[], int pincode, char contact[],
                                   int svc_ids[], int svc_count);
Professional* professionalFind(AVLNode* root, int id);
boolean       professionalExists(AVLNode* root, int id);
boolean       professionalOffers(Professional* pro, int svc_id);
boolean       professionalIsAvailable(Professional* pro);
void          professionalSetAvailability(Professional* pro, AvailabilityStatus status);
void          professionalDisplayServices(Professional* pro, AVLNode* serviceRoot);
void          professionalDisplayOne(Professional* pro);
void          professionalDisplayAll(AVLNode* root, AVLNode* serviceRoot);

#endif