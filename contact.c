#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>
int validatePhone(const char *phone);
int validateEmail(const char *email);


void listContacts(AddressBook *addressBook) 
{
    /* Define the logic for print the contacts */
        printf("\n---------------------------------- --hhhello--\n\n");
        // Iterate through each contact in the address book
        for (int i = 0; i < addressBook->contactCount; i++) 
        {
            printf("--------------------> ");
            printf("Contact %d ", i + 1);
            printf("<---------------------\n");
            
            // Print contact details
            printf("Name: %s\n", addressBook->contacts[i].name);
            printf("Phone: %s\n", addressBook->contacts[i].phone);
            printf("Email: %s\n\n", addressBook->contacts[i].email);
        }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);//-->populate.c
    //After performing function back to function call main.c (line)

    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveContactsToFile(AddressBook *addressBook) 
{
    // Open the file in write mode ("w")
    FILE *file = fopen("contacts.csv", "w");
    // Check if file opening failed
    if (file == NULL) 
    {
        printf("Error opening file!\n");
        return;   // Exit function if file cannot be opened
    }

    // Write each contact to the file
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        // Write contact details in CSV format (name, phone, email)
        if (fprintf(file, "%s,%s,%s\n",
                    addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,
                    addressBook->contacts[i].email) < 0) 
        {
            printf("Error writing to file!\n");
            break;  // Stop writing if error occurs
        }
    }
    // Close the file
    fclose(file);
    // Confirm successful save
    printf("Contacts saved to contacts.csv successfully! \n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void createContact(AddressBook *addressBook) 
{
    // Prompt user for contact name
    printf("Enter contact name: ");
    scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].name);

    // Prompt user for contact phone number
    printf("Enter contact phone: ");
    scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].phone);

    // Check if phone number already exists
    int phoneExists = 0;
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].phone, addressBook->contacts[addressBook->contactCount].phone) == 0) //strcmp ret val is 1 for unique 0 for same number
        {
            phoneExists = 1;  //if both read number and previous stored number are equal return 0 ,then phone exist = 1 else vice-versa; 
            break;
        }
    }
    // Validate phone number and ensure uniqueness
    while (!(validatePhone(addressBook->contacts[addressBook->contactCount].phone)) || phoneExists) //phoneExists contains 1 for a unique number and 0 for Duplicate  //Short circuit happens
    {
        if (phoneExists) 
        {
            printf("Phone number already exists!. \nPlease enter a different phone number: ");
        } 
        else 
        {
            printf("Invalid phone number!. \nPlease enter a valid phone number: ");
        }
        scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].phone);       // previous scan line 77

        // Re-check if phone number already exists
        phoneExists = 0;
        for (int i = 0; i < addressBook->contactCount; i++) 
        {
            if (strcmp(addressBook->contacts[i].phone, addressBook->contacts[addressBook->contactCount].phone) == 0) 
            {
                phoneExists = 1;
                break;
            }
        }
    }
    // Prompt user for contact email
    printf("Enter contact email: ");
    scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].email);
 
    // Validate email address
    while (!validateEmail(addressBook->contacts[addressBook->contactCount].email))  //-->success fun back to main() line :39
    {
        printf("Invalid email. Please enter a valid email (example@example.com): ");
        scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].email);
    }
    // Increment contact count
    addressBook->contactCount++;
    printf("Contact created successfully!\n"); 
}


void searchContact(AddressBook *addressBook) 
{
    int choice;
    char search_the_contact[50];     // Search query string

    // Display search options
    printf("Search contact by:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) 
    {
        case 1:    // Search by name
            printf("Enter contact name: ");
            scanf(" %[^\n]", search_the_contact);
            int count = 0;

            // Iterate through contacts and search for matching name
            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strcmp(addressBook->contacts[i].name, search_the_contact) == 0) //return 0 for equal matcehs
                {
                    // Display matching contact details
                    printf("\nContact %d found:\n", count + 1);
                    printf("Name: %s\n", addressBook->contacts[i].name);
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    count++;
                }
            }
            if (count == 0) 
            {
                printf("\nContact not found.\n");
            } 
            else if (count > 1) 
            {
                printf("%dMultiple contacts found with the same name.\n",count);
            }
            break;
        case 2:   // Search by phone
            printf("Enter contact phone: ");
            scanf(" %[^\n]", search_the_contact);

            // Iterate through contacts and search for matching phone
            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strcmp(addressBook->contacts[i].phone, search_the_contact) == 0) 
                {
                    printf("\nContact found:\n");
                    printf("Name: %s\n", addressBook->contacts[i].name);
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    return;    // Exit function after finding contact
                }
            }
            printf("\nContact not found.\n");
            break;
        case 3:  // Search by email
            printf("Enter contact email: ");
            scanf(" %[^\n]", search_the_contact);

            // Iterate through contacts and search for matching email
            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strcmp(addressBook->contacts[i].email, search_the_contact) == 0) 
                {
                    printf("\nContact found:\n");
                    printf("Name: %s\n", addressBook->contacts[i].name);
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    return;  // Exit function after finding contact
                }
            }
            printf("\nContact not found.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            getchar();
    }
} //return back to function call -->main 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void editContact(AddressBook *addressBook) 
{
    int choice;
    char search_the_contact[50];        //array to store Name , Phone , Email
    
    //Ask the user to search the contact  by name, number or eamil.id
    printf("Search contact to edit by:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) 
    {
        case 1:
            printf("Enter contact name: ");
            scanf(" %[^\n]", search_the_contact);   //store name to search_the_contact array
            break;
        case 2:
            printf("Enter contact phone: ");
            scanf(" %[^\n]", search_the_contact);   //store phone to search_the_contact array
            break;
        case 3:
            printf("Enter contact email: ");
            scanf(" %[^\n]", search_the_contact);   //store email to search_the_contact array
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            getchar();  // to consume char 
            return;
    }

    int found = 0;      //
    int indices[100];   // Store indices of matching contacts
    int count = 0;      // Count of matching contacts

    // Search for contacts
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if ((choice == 1 && strcmp(addressBook->contacts[i].name, search_the_contact) == 0) ||
            (choice == 2 && strcmp(addressBook->contacts[i].phone, search_the_contact) == 0) ||
            (choice == 3 && strcmp(addressBook->contacts[i].email, search_the_contact) == 0)) //i th contact name 
            
            {
                found = 1;
                indices[count] = i; //i=0
                count++;            //count =n for multiple contact
            }//here
    }

    if (found) //found=1
    {
        if (count == 1) //
        {
            // Only one contact found, edit it
            int index = indices[0];             //
            printf("\nContact found:\n");
            printf("Name: %s\n", addressBook->contacts[index].name);    //
            printf("Phone: %s\n", addressBook->contacts[index].phone);  //
            printf("Email: %s\n", addressBook->contacts[index].email);  //

            // Ask user what they want to edit
            printf("\nWhat do you want to edit?\n");
            printf("1. Name\n");
            printf("2. Phone\n");
            printf("3. Email\n");
            printf("Enter your choice: ");
            int editChoice;
            scanf("%d", &editChoice);

            // Edit contact
            switch (editChoice) 
            {
                case 1:
                    printf("Enter new name: ");
                    char newName[50];
                    scanf(" %[^\n]", newName);
                    if (strlen(newName) > 0) 
                    {
                        strcpy(addressBook->contacts[index].name, newName);  //Overwrite name
                    }
                    break;
                case 2:
                    printf("Enter new phone: ");
                    char newPhone[15];
                    scanf(" %[^\n]", newPhone);
                    // Check if phone number already exists
                    int phoneExists = 0;
                    for (int i = 0; i < addressBook->contactCount; i++) 
                    {
                        if (i != index && strcmp(addressBook->contacts[i].phone, newPhone) == 0) 
                        {
                            phoneExists = 1;
                            break;
                        }
                    }
                    while (!validatePhone(newPhone) || phoneExists) 
                    {
                        if (phoneExists) 
                        {
                            printf("Phone number already exists!. \nPlease enter a different phone number: ");
                        } 
                        else 
                        {
                            printf("Invalid phone number. Please enter a valid phone number: ");
                        }
                        scanf(" %[^\n]", newPhone);
                        phoneExists = 0;
                        for (int i = 0; i < addressBook->contactCount; i++) 
                        {
                            if (i != index && strcmp(addressBook->contacts[i].phone, newPhone) == 0) 
                            {
                                phoneExists = 1;
                                break;
                            }
                        }
                    }
                    strcpy(addressBook->contacts[index].phone, newPhone);
                    break;
                case 3:
                    printf("Enter new email: ");
                    char newEmail[50];
                    scanf(" %[^\n]", newEmail);
                    if (strlen(newEmail) > 0) {
                        while (!validateEmail(newEmail)) 
                        {
                            printf("Invalid email. Enter again: ");
                            scanf(" %[^\n]", newEmail);
                        }
                        strcpy(addressBook->contacts[index].email, newEmail);
                    }
                    break;
                default:
                    printf("Invalid choice.\n");
                    getchar();
                    return;
            }
            printf("Contact updated successfully!\n");
        } 
        else 
        {
            // Multiple contacts found, display options and ask user to select
            printf("\nMultiple contacts found:\n");
            /*for (int i = 0; i < count; i++) 
            {
                printf("%d. %s (%s)\n", i + 1, addressBook->contacts[indices[i]].name, addressBook->contacts[indices[i]].phone);
            }*/
            for (int i = 0; i < count; i++) 
            {
            printf("\nSelect contact to edit %d. \n", i + 1);
            
            printf("Name: %s\n", addressBook->contacts[indices[i]].name);
            printf("Phone: %s\n", addressBook->contacts[indices[i]].phone);
            printf("Email: %s\n", addressBook->contacts[indices[i]].email);
            }

            int selectChoice;
            printf("Enter the number which contact to edit: ");
            scanf("%d", &selectChoice);

            if (selectChoice >= 1 && selectChoice <= count) 
            {
                int index = indices[selectChoice - 1];

                printf("Contact selected:\n");
                printf("Name: %s\n", addressBook->contacts[index].name);
                printf("Phone: %s\n", addressBook->contacts[index].phone);
                printf("Email: %s\n", addressBook->contacts[index].email);

                // Ask user what they want to edit
                printf("What do you want to edit?\n");
                printf("1. Name\n");
                printf("2. Phone\n");
                printf("3. Email\n");
                printf("Enter your choice: ");
                int editChoice;
                scanf("%d", &editChoice);

                // Edit contact
                switch (editChoice) 
                {
                    case 1:
                        printf("Enter new name: ");
                        char newName[50];
                        scanf(" %[^\n]", newName);
                        if (strlen(newName) > 0) 
                        {
                            strcpy(addressBook->contacts[index].name, newName);
                        }
                        break;
                    case 2:
                        printf("Enter new phone: ");
                        char newPhone[15];
                        scanf(" %[^\n]", newPhone);
                        // Check if phone number already exists
                        int phoneExists = 0;
                        for (int i = 0; i < addressBook->contactCount; i++) 
                        {
                            if (i != index && strcmp(addressBook->contacts[i].phone, newPhone) == 0) 
                            {
                                phoneExists = 1;
                                break;
                            }
                        }
                        while (!validatePhone(newPhone) || phoneExists) 
                        {
                            if (phoneExists) 
                            {
                                printf("Phone number already exists!. \nPlease enter a different phone number: ");
                            } 
                            else 
                            {
                                printf("Invalid phone number!. \nPlease enter a valid phone number: ");
                            }
                            scanf(" %[^\n]", newPhone);
                            phoneExists = 0;
                            for (int i = 0; i < addressBook->contactCount; i++) 
                            {
                                if (i != index && strcmp(addressBook->contacts[i].phone, newPhone) == 0) 
                                {
                                    phoneExists = 1;
                                    break;
                                }
                            }
                        }
                        strcpy(addressBook->contacts[index].phone, newPhone);
                        break;
                    case 3:
                        printf("Enter new email: ");
                        char newEmail[50];
                        scanf(" %[^\n]", newEmail);
                        if (strlen(newEmail) > 0) 
                        {
                            while (!validateEmail(newEmail)) 
                            {
                                printf("Invalid email. Enter again: ");
                                scanf(" %[^\n]", newEmail);
                            }
                            strcpy(addressBook->contacts[index].email, newEmail);
                        }
                        break;
                    default:
                        printf("Invalid choice.\n");
                        getchar();
                        return;
                }
                printf("Contact updated successfully!\n");
            } 
            else 
            {
                printf("Invalid choice.\n");
            }
        }
    } 
    else 
    {
        printf("Contact not found.\n");
    }
}

void deleteContact(AddressBook *addressBook)
{
    char name[50];
    printf("Enter contact name to delete: ");
    scanf(" %[^\n]", name);
    

    int found = 0;
    int indexes[100];
    int count = 0;
    
    // Search for the contact
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0) 
        {
            found = 1;
            indexes[count] = i;
            count++;
        }
    }

    if (found) 
    {
        if (count == 1) 
        {
            // Display contact details
            printf("\nContact found:\n");
            printf("Name: %s\n", addressBook->contacts[indexes[0]].name);
            printf("Phone: %s\n", addressBook->contacts[indexes[0]].phone);
            printf("Email: %s\n", addressBook->contacts[indexes[0]].email);

            // Ask user if they want to delete
            char choice;
            printf("Do you want to delete this contact? (y/n): ");
            scanf(" %c", &choice);

            if (choice == 'y' || choice == 'Y') 
            {
                // Delete contact
                for (int i = indexes[0]; i < addressBook->contactCount - 1; i++) 
                {
                    addressBook->contacts[i] = addressBook->contacts[i + 1];
                }
                addressBook->contactCount--;
                printf("Contact deleted successfully!\n");
            } 
            else 
            {
                printf("Deletion cancelled.\n");
            }
        } 
        else 
        {
            // Display all similar contacts
            printf("Multiple contacts found with the same name:\n");
            for (int i = 0; i < count; i++)
            {
                printf("Contact %d:\n", i + 1);
                printf("Name: %s\n", addressBook->contacts[indexes[i]].name);
                printf("Phone: %s\n", addressBook->contacts[indexes[i]].phone);
                printf("Email: %s\n\n", addressBook->contacts[indexes[i]].email);
            }

            // Ask user which contact to delete
            int selectChoice;
            printf("Enter the number of the contact you want to delete: ");
            scanf("%d", &selectChoice);

            if (selectChoice >= 1 && selectChoice <= count) 
            {
                int index = indexes[selectChoice - 1];

                // Display selected contact details
                printf("Contact selected:\n");
                printf("Name: %s\n", addressBook->contacts[index].name);
                printf("Phone: %s\n", addressBook->contacts[index].phone);
                printf("Email: %s\n", addressBook->contacts[index].email);

                // Ask user if they want to delete
                char choice;
                printf("Do you want to delete this contact? (y/n): ");
                scanf(" %c", &choice);

                if (choice == 'y' || choice == 'Y')
                {
                    // Delete contact
                    for (int i = index; i < addressBook->contactCount - 1; i++) 
                    {
                        addressBook->contacts[i] = addressBook->contacts[i + 1];
                    }
                    addressBook->contactCount--;
                    printf("Contact deleted successfully!\n");
                }
                else 
                {
                    printf("Deletion cancelled.\n");
                }
            } 
            else 
            {
                printf("Invalid choice.\n");
            }
        }
    } 
    else
    {
        printf("Contact not found.\n");
    }
}

int validatePhone(const char *phone) 
{
    // Check if phone number has exactly 10 digits
    if (strlen(phone) == 10)
    {
        // Iterate through each character in the phone number
        for (int i = 0; i < 10; i++) 
        {
            // Check if character is not a digit
            if (!(isdigit(phone[i]))) //return 0 if i th num != digit // return type of isdigit is 1 for true nad 0 for false  
            {
                // Return 0 (invalid) if non-digit character found
                return 0; //return 0 if i th num != digit (if out of 10 num any 1 num is character)
            }
        }
        // If all characters are digits, return 1 (valid)
        return 1; //return 1 all num == digit(all 10 digits are number)
    }
    // Return 0 (invalid) if phone number length is not 10
    return 0;
}

int validateEmail(const char *email) 
{
    int at = 0;  // Count of '@' symbols
    int dot = 0;   // Count of '.' symbols 
    int len = strlen(email);     // Length of email string
    
    // Iterate through each character in the email
    for (int i = 0; i < len; i++)       //Validation for upper and lower case
    {
        // Reject email with uppercase letters
        if(email[i]>='A' && email[i]<='Z' ) //Validation for upper and lower case
        {
        // Return 0 (invalid) if uppercase letter found 
        return 0;
        }
        // Count '@' symbols
        else if (email[i] == '@')
        {
            at++;
        } 
        else if (email[i] == '.')
        {
            dot++;
        } 
        // Count '.' symbols 
    }
    if (at == 1 && dot== 1 && strcmp(email + len - 4, ".com") == 0)
    {
        return 1;
    }
        return 0;
    // Validate email conditions: Exactly one '@' symbol and at least one '.' symbol
    // Presence of ".com" (case-sensitive)at the end of the string.
    /*if (at == 1 && dot >= 1 &&strstr(email, ".com") != NULL && strcmp(email + len - 4, ".com") == 0)
    {
        // Return 1 (valid) if conditions met
        return 1;
    }*/
    // Return 0 (invalid) if conditions not met
    
}