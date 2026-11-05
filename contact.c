#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
extern int Search[MAX_CONTACTS];

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    switch(sortCriteria)
    {
        case 1 : printf("Sorting by name : \n");
        
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if (strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)
                {
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
            
            
        }
        printf("Index No\tName\t\tPhone\t\tEmail\n");
        for(int i=0;i<addressBook->contactCount;i++)
            {
                printf("%5d.\t   %-17s %-15s%-30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            }
        break;
        case 2 : printf("Sorting by phone : \n");
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if (strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone)>0)
                {
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
            
        }
        printf("Index No\tName\t\tPhone\t\tEmail\n");
            for(int i=0;i<addressBook->contactCount;i++)
            {
                printf("%5d.\t   %-17s %-15s%-30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            }
        break;
        case 3 : printf("Sorting by email : \n");
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if (strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0)
                {
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
           
        }
         printf("Index No\tName\t\tPhone\t\tEmail\n");
            for(int i=0;i<addressBook->contactCount;i++)
            {
                printf("%5d.\t   %-17s %-15s%-30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            }


        break;
        default:
        printf("Enter the valid  sorting criteria");
    }
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    static int count;
    int i=0;
	char name[50],phone[11],email[50];
    count =1;
    name_input:
    printf("Enter name : ");
    scanf(" %[^\n]",name);
    if (name[0]>='0' && name[0] <='9' )
    {
        printf("enter valid name\n");
        if ((count++)%3==0)
           return ;
        goto name_input;
    }
    if(strlen(name) < 3)
    {
        printf("Name should be atleast 3 characters\n");
    }
    count = 1;
    phone_input:
    printf("Enter phone : ");
    scanf(" %[^\n]",phone);
    if(strlen (phone) != 10)
    {
         printf("Phone number should be 10 digits\n");
         if (count++ % 3==0)
            return ;
            goto phone_input;
    }
    if (phone[0]<'6' || phone[0] >'9')
    {
        printf("Starting number start in between  6 to 9\n");
        if ((count++)%3==0)
           return ;
       goto phone_input;
    }
    for(i=0;i<10;i++)
    {
        if (phone[i]< '0' || phone[i]> '9')
        {
            printf("enter only digits ");
             if (count++%3==0)
             return ;
             goto phone_input;
        }
    }
    
    i=0;
    while(i < addressBook->contactCount)
    {
        if(strcmp(addressBook->contacts[i].phone,phone))
        
            i++;
        else
        {
             printf("Already contact in your list\n");
             if (count++%3==0)
             return ;
             goto phone_input;
        }
           
    }
    count=1;
    email_input:
    printf("Enter email : ");
    scanf(" %[^\n]",email);
    if(strlen(email)<10)
    {
        printf("invalid email");
             if (count++%3==0)
             return ;
             goto email_input;
    }
    if (strcmp((email+(strlen(email)-4)),".com"))
    {
        printf("email must end with .com\n");
             if (count++%3==0)
             return ;
             goto email_input;
    }
    int atcount=0,atadd=-1,dotadd=-1;
    for(i=0;email[i]!='\0';i++)
    {
        if (email[i]=='@' || email[i]== '.')
        {
            if (email[i]=='@')
              atadd= i; 
            else
              dotadd=i;
            atcount++;
        }
    }
    
    if(atadd > dotadd)
    {
        printf("@ should be first than .\nexample:- example@gmail.com\n");
        if (count++%3==0)
             return ;
             goto email_input;
    }
    else if(atadd+1 == dotadd)
    {
        printf("Atleast one char between @ and .\n"); 
        if (count++%3==0)
             return ;
             goto email_input;    
    }
    else if (atcount == 2)
    {
        i=1;
        while(atadd+i < dotadd)
        {
            if (email[atadd+i] < 'a' || email[atadd+i] > 'z')
            {
                printf("Must be lower case in beetween @ and .\n");
             if (count++%3==0)
             return ;
             goto email_input;
            }
            i++;
        }
        if (email[0] >='0' && email[0] <= '9')
        {
            printf("first character should not be digit\n");
             if (count++%3==0)
             return ;
             goto email_input;
        }
        for (i=0;i<atadd;i++)
        {
          if (!(email[i] >= 'a'  && email[i] <= 'z' || email[i]>='0'  && email[i]<='9' ))
            {
             printf("invalid email");
             if (count++%3==0)
             return ;
             goto email_input;
            }
        }
         i=0;
    while(i < addressBook->contactCount)
    {
        if(strcmp(addressBook->contacts[i].email,email))
        
            i++;
        else
        {
             printf("email is already there in your previous list\n");
             if (count++%3==0)
             return ;
             goto email_input;
        }
    }
    }
    else{
        printf("@ and . must and should one time\n");
        if (count++%3==0)
             return ;
             goto email_input;
    }
    strcpy(addressBook->contacts[addressBook->contactCount].name,name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    strcpy(addressBook->contacts[addressBook->contactCount++].email,email);  
    printf("Contact successfully added\n");  
}

void searchContact(AddressBook *addressBook) 
{
    char name[50],phone[10],email[50];
    int i,count=0,j=0;

     int sortchoice;

                printf("Select sort criteria:\n");
                printf("1. Search by name\n");
                printf("2. Search by phone\n");
                printf("3. Search by email\n");
                printf("4. Exit\n");
                printf("Enter your choice : ");
                scanf("%d",&sortchoice);
    
    switch(sortchoice)
    {
        case 1:
        {
            printf("Enter name to search : ");
            scanf(" %[^\n]",name);
            for(i=0;i<addressBook->contactCount;i++)
            {
                   if (!(strcmp(addressBook->contacts[i].name,name)))
                   {
                        Search[j++]=i;
                        printf("%d.\t%s\t%s\t%s\n",count+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        count++;
                   }
            }
            Search[j]='\0';
            if (count == 0)
              printf("Name not found\n");
            break;
        }
        case 2:
        {
            printf("Enter Phone number to search : ");
            scanf(" %[^\n]",phone);
            for(i=0;i<addressBook->contactCount;i++)
            {
                if (!(strcmp(addressBook->contacts[i].phone,phone)))
                {
                    Search[j++]=i;
                    printf("%d.\t%s\t%s\t%s\n",count+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    count++;
                }
            }
            Search[j]='\0';
            if (count == 0)
              printf("phone number not found\n");
            break;
        }
        case 3:
        {
            printf("Enter email to search : ");
            scanf(" %[^\n]",email);
            for(i=0;i<addressBook->contactCount;i++)
            {
                if (!(strcmp(addressBook->contacts[i].email,email)))
                {
                    Search[j++]=i;
                    printf("%d.\t%s\t%s\t%s\n",count+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    count++;
                }
            }
            Search[j]='\0';
            if (count == 0)
              printf("Email not found");
            break;
        }
        case 4 :
        {
            return ;
        }
    }
}

void editContact(AddressBook *addressBook)
{
    int serialnum,choice,i=0;
	searchContact(addressBook);
    if (Search[0]=='\0')
        return ;
    printf("Select contact to edit : ");
    scanf("%d",&serialnum);
    while (Search[i++]!='\0');
    if(serialnum>=i || serialnum<=0)
    {
        printf("Select valid contact");
        return ;
    }
    printf("1. Edit name\n2. Edit phone no\n3. Edit email\n4. Exit\nEnter your choice: ");
    scanf("%d",&choice);
     int count =1;
    char name[50],phone[10],email[50];
    switch(choice)
    {
        case 1 :
        {
            name_input:
                printf("Enter name : ");
                scanf(" %[^\n]",name);
                if (name[0]>='0' && name[0] <='9')
                {
                     printf("enter valid name\n");
                        if ((count++)%3==0)
                             return ;
                         goto name_input;
                }
                if(strlen(name) < 3)
                {
                    printf("Name should be atleast 3 characters\n");
                }
            strcpy(addressBook->contacts[Search[serialnum-1]].name,name);
            break;
        }
        case 2 :
        {
              phone_input:
              printf("Enter phone : ");
              scanf(" %[^\n]",phone);
              if(strlen (phone) != 10)
              {
                printf("Phone number should be 10 digits\n");
                     if (count++ % 3==0)
                      return ;
                     goto phone_input;
              }
              if (phone[0]<'6' || phone[0] >'9')
               {
                     printf("Starting number start in between  6 to 9\n");
                       if ((count++)%3==0)
                       return ;
                    goto phone_input;
               }
            for(i=0;i<10;i++)
            {
                if (phone[i]< '0' || phone[i]> '9')
                {
                    printf("enter only digits ");
                    if (count++%3==0)
                    return ;
                   goto phone_input;
                }
            }
    
            i=0;
            while(i < addressBook->contactCount)
            {
                if(strcmp(addressBook->contacts[i].phone,phone))
                   i++;
                else
                {
                   printf("Already contact in your list\n");
                   if (count++%3==0)
                   return ;
                   goto phone_input;
                }
           
            }
            strcpy(addressBook->contacts[Search[serialnum-1]].phone,phone);
            break;
        }
        case 3 :
        {
            email_input:
             printf("Enter email : ");
    scanf(" %[^\n]",email);
    if(strlen(email)<10)
    {
        printf("invalid email");
             if (count++%3==0)
             return ;
             goto email_input;
    }
    if (strcmp((email+(strlen(email)-4)),".com"))
    {
        printf("email must end with .com\n");
             if (count++%3==0)
             return ;
             goto email_input;
    }
    int atcount=0,atadd=-1,dotadd=-1;
    for(i=0;email[i]!='\0';i++)
    {
        if (email[i]=='@' || email[i]== '.')
        {
            if (email[i]=='@')
              atadd= i; 
            else
              dotadd=i;
            atcount++;
        }
    }
    
    if(atadd > dotadd)
    {
        printf("@ should be first than .\nexample:- example@gmail.com\n");
        if (count++%3==0)
             return ;
             goto email_input;
    }
    else if(atadd+1 == dotadd)
    {
        printf("Atleast one char between @ and .\n"); 
        if (count++%3==0)
             return ;
             goto email_input;    
    }
    else if (atcount == 2)
    {
        i=1;
        while(atadd+i < dotadd)
        {
            if (email[atadd+i] < 'a' || email[atadd+i] > 'z')
            {
                printf("Must be lower case in beetween @ and .\n");
             if (count++%3==0)
             return ;
             goto email_input;
            }
            i++;
        }
        if (email[0] >='0' && email[0] <= '9')
        {
            printf("first character should not be digit\n");
             if (count++%3==0)
             return ;
             goto email_input;
        }
        for (i=0;i<atadd;i++)
        {
          if (!(email[i] >= 'a'  && email[i] <= 'z' || email[i]>='0'  && email[i]<='9' ))
            {
             printf("invalid email");
             if (count++%3==0)
             return ;
             goto email_input;
            }
        }
         i=0;
    while(i < addressBook->contactCount)
    {
        if(strcmp(addressBook->contacts[i].email,email))
        
            i++;
        else
        {
             printf("email is already there in your previous list\n");
             if (count++%3==0)
             return ;
             goto email_input;
        }
    }
    }
    else{
        printf("@ and . should be only one time\n");
        if (count++%3==0)
             return ;
             goto email_input;
    }
            strcpy(addressBook->contacts[Search[serialnum-1]].email,email);
            break;
        }
        case 4 :
        {
            break;
        }
        default :
    {
        printf("Enter correct choice");
    }
    }   
}

void deleteContact(AddressBook *addressBook)
{
	searchContact(addressBook);
    if(Search[0]== '\0')
    {
        printf("Contact not found\n");
        return ;
    }
    int i,select;
    printf("Select contact to delete : ");
    scanf("%d",&select);
    for(i=Search[select-1];i<addressBook->contactCount-1;i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }
    // addressBook->contacts[i]='\0';
    addressBook->contactCount--;
    printf("\nContact deleted successfully\n");
}
