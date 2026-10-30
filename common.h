#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>    
#include <stdlib.h>  
#include <string.h> 

#define MAX_SERVICES_PER_PROFESSIONAL 5    
#define MAX_NAME_LEN 50
#define MAX_CONTACT_LEN 11   
#define PINCODE_DIGITS 6    
#define MAX_SERVICE_NAME_LEN 50   

typedef enum {FALSE,TRUE} boolean;

typedef enum {FAILURE,SUCCESS} status_code;

typedef enum {PENDING,ASSIGNED,COMPLETED,CANCELLED} RequestStatus;

typedef enum {AVAILABLE,BUSY} AvailabilityStatus;

typedef struct {
    int day;    
    int month;  
    int year;   

} Date;

typedef struct {
    int hour;   
    int minute; 
} Time;

typedef struct {
    Date date;  
    Time time;  
} DateTime;

#endif
