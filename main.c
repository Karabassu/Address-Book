//karabassu sangur
//address Book
#include <stdio.h>
#include "contact.h"
int main() 
{
    int choice;

    AddressBook addressBook;	// Data type --> variable(addressBook)
    initialize(&addressBook); 	// Initialize the structure address(&address) book
    do 
    {
	//print the list of operations of addressbook
	printf("\nAddress Book Menu:\n");
	printf("1. Create contact\n");
	printf("2. Search contact\n");
	printf("3. Edit contact\n");
	printf("4. Delete contact\n");
	printf("5. List all contacts\n");
	printf("6. Save and Exit\n");
	printf("Enter your choice: ");
	
	
	scanf("%d", &choice);
	char ch;
	//check whether the input is character or digit
	if (choice == ch) //Verifying choice is an integer or character
	{
		//if input choice is character then print error msg 
        printf("Invalid input. Try again.\n");

		// Clear input buffer to prevent infinite loop
        while (getchar() != '\n'); // Clear input buffer
        continue;  // Skip to And skip following line and go back to startin of loop
    }
	switch (choice) 
	{
		//address of addressBook variable of structure AddressBook
	    case 1:
		createContact(&addressBook);  //func. call -->Contact.h(declaration)-->Contact.c(definition)
		break;
	    case 2:
		searchContact(&addressBook);	//func. call -->Contact.h(declaration)-->Contact.c(definition)
		break;
	    case 3:
		editContact(&addressBook);		//func. call -->Contact.h(declaration)-->Contact.c(definition) L:213
		break;
	    case 4:
		deleteContact(&addressBook);
		break;
	    case 5:
		listContacts(&addressBook);
		break;
	    case 6:
		printf("Saving and Exiting...\n");
		saveContactsToFile(&addressBook);
		break;
	    default:
		printf("Invalid choice. Please try again.\n");
	}
    }
	while (choice != 6);
    return 0;
}
