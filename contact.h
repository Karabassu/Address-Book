#ifndef CONTACT_H
#define CONTACT_H
#include<stdio.h>

#define MAX_CONTACTS 100

typedef struct Contact
{
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct 
{
    Contact contacts[MAX_CONTACTS]; //contact structure Taken as an array of structure with size max== contact macro  already defined 
    
    int contactCount;               //count for number of contact count
}AddressBook;   //strct name addressBook variable for structure AddressBook main L:9

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);


int validum(char *num);
//int valemail(str);
#endif
