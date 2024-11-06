#include "contact.h"
#include <string.h>


void populateAddressBook(AddressBook *addressBook) //Dreference
{
    // Open the CSV file in read mode ("r")
    FILE* file = fopen("contacts.csv", "r");

    if (file == NULL) // Check if file opening failed return 0 if not open
    {
        printf("Error opening file!\n");
        return;      // Exit function if file cannot be opened
    }
    
    char line[100]; //line array   Buffer to store each line from the file

    // Read file line by line
    while (fgets(line, sizeof(line), file)) //array name , condition ,file location [One line of file if true]
    {
        // Tokenize the line using comma (,) as delimiter
        char* token = strtok(line, ","); //passing array you name line up to delimiter (Delimiter ",") strtok returns starting address of the file

        // Check if tokenization succeeded
        if (token != NULL) // Fail if file contains 0 contents
        {
            // Copy name from token to address book
            strcpy(addressBook->contacts[addressBook->contactCount].name, token);

            // Tokenize next field (phone)
            token = strtok(NULL, ","); //return address Pointing starting of contact number (1234567890) now token contains (1234567890)

            // Check if phone token is valid
            if (token != NULL) //True
            {
                // Copy phone from token to address book
                strcpy(addressBook->contacts[addressBook->contactCount].phone, token);

                // Tokenize next field (email)
                token = strtok(NULL, "\n");// Up to new line Other address will be updated(change) when it reaches to newline

                // Check if email token is valid
                if (token != NULL) 
                {
                    // Copy email from token to address book
                    strcpy(addressBook->contacts[addressBook->contactCount].email, token);

                    // Increment contact count
                    addressBook->contactCount++;
                }
            }
        }
    }
    // Close the file
    fclose(file); // back to contact.c (fun call ) line 32
}

/* void populateAddressBook(AddressBook* addressBook)
{
    //find the no. of elements in the contact array
    int size = sizeof(dummyContacts) / sizeof(dummyContacts[0]);

    //copy dummy contact elements into the contacts array
    for(int i=0;i< size;i++)
    {
        addressBook->contacts[addressBook->contactCount++] = dummyContacts[i];
    }

    addressBook->contactCount = size;
} */


/* int validum(char *num)
{
    int flag = 0;
    printf("Enter the number : ");
    scanf("%s",num);
    while(num!='\0')
    {
        for(int i=0;num[i]!='\0';i++)
        {
            if(num[i]>='0' && num[i]<='9');
            {
                flag = 1;
            }
        }
    }
    return flag;
} */