// Example: Operating and maintaining a LIFO queue

#include <stdio.h>
#include <stdlib.h>


// Global declarations:

struct Node    // self-referential structure
{  
   char Data[50];
   struct Node *Next;
};

typedef struct Node QUEUENODE;
typedef QUEUENODE * QUEUENODEPTR;


QUEUENODEPTR startPtr = NULL;  // points to the front of queue


// Function prototypes:
void add();
void remove();
void display();


//------------------------------------------------------------
int main()
{
   int choice;

   while (1)
   {
   printf ("\n\nWELCOME TO LIFO QUEUE SIMULATION PROGRAM\n");
   printf ("   1. Add new item to queue\n"
           "   2. Remove item from queue\n"
           "   3. Display all items in queue\n"
           "   4. Exit program\n");
   printf("\nEnter your choice: ");
   scanf("%d", &choice);

      switch(choice)
      {
         case 1:
           add();
           break;

         case 2:
            remove();
            break;

         case 3:
            display();
            break;

         case 4:
            printf("\nBye!\n");
            return 0;
            break;

         default:
            printf("\nInvalid choice.\n");
            break;
      }
   }
}


//------------------------------------------------------------
void add()
{
   QUEUENODEPTR newPtr;

   newPtr = new Node;

   if (newPtr == NULL)
   {
      printf("\nNo memory is available!\n");
      return;
   }

   printf("Enter a name: ");
   scanf("%s", newPtr->Data);

   // Add the new node to the front of queue:
   newPtr->Next = startPtr;
   startPtr = newPtr;
           
   printf("\n%s has been added.\n", newPtr->Data);
}


//------------------------------------------------------------
void remove()
{
   QUEUENODEPTR tempPtr;

   if (startPtr == NULL)
   {
      printf("\nQueue is already empty!\n");
      return;
   }


   // Remove the front node from queue:
   tempPtr = startPtr;
   startPtr = tempPtr->Next;

   printf("\n%s has been removed.\n", tempPtr->Data);

   delete tempPtr;
}


//------------------------------------------------------------
void display()
{
   QUEUENODEPTR currentPtr;

   if (startPtr == NULL)
   {
      printf("\nQueue is empty, nothing to display!\n");
      return;
   }

   printf("\n");

   // Display all nodes of queue:
   currentPtr = startPtr;
   while (currentPtr != NULL)
   {
         printf("%s - ", currentPtr->Data);
         currentPtr = currentPtr->Next;
   }
}

//------------------------------------------------------------
