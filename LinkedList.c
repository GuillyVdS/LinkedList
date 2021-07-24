/* This program presents the user with a menu with options to manipulate a linked list
 * Each time a string is added it needs to print any previously stored strings
bonus pts create a menu with 4 options.
Option 1 : add string, option 2: delete string, using string as identifyer, option 3: print all stored strings, 4: exit program
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define buffersize 100 // generic buffer size for program

/*Creates a new type of ListNode which stores a char pointer and a pointer
 to a new node. This will be used to create a linked list.*/
typedef struct node {
  char * value;
  struct node * next;
}ListNode;


//Creating prototypes for each function
void getCharInput(char * inputValue);
void pushToList(ListNode ** head, char * newvalue);
void printItemsInList(ListNode * head);
void removeItemFromList(ListNode ** head, char * valueToRemove);


/*Function used to retrieve character input from the command line. User input
will be stored at the address of inputValue */
void getCharInput(char * inputValue){
  if( fgets(inputValue, buffersize, stdin) != NULL)
  {
    /*Goes to the index of the newline character in inputValue and replaces it
    with a NULL character*/
    inputValue[strcspn ( inputValue, "\n" )] = 0;
  }
}

/*Function takes a node object head and a newvalue. It will iterate over the
linked list starting at head. Once it finds the next empty node it will stick
the newvalue in and create a new empty node for future operations*/
void pushToList(ListNode ** head_ptr, char * newvalue) {
      /*Checks if a node head object already exists. If this does not exist,
      a new head node will be created and memory will be assigned to it.  */
      if(*head_ptr == NULL){
        *head_ptr = (ListNode *)malloc(sizeof(ListNode));
        (*head_ptr)->value = (char *)malloc(strlen(newvalue) + 1) ;
        strcpy((*head_ptr)->value, newvalue);
        (*head_ptr)->next = NULL;
      }
      else{
        //Finds current last item in the list (by way of finding null pointer)
        ListNode * currentNode = *head_ptr;
        while (currentNode->next != NULL) {
            currentNode = currentNode->next;
        }

        /*Sets pointer to refer to new node in
        the list and sets value of new node*/
        currentNode->next = (ListNode *) malloc(sizeof(ListNode));
        currentNode->next->value = (char *)malloc(strlen(newvalue) + 1);
        strcpy(currentNode->next->value, newvalue);
        currentNode->next->next = NULL;
      }
  }

/*Iterates over each value in the list and checks if pointer is NULL,
 if it is not NULL it prints the value and moves the cursor to the next node*/
void printItemsInList(ListNode * head){
  ListNode * currentNode = head;

  while(currentNode != NULL){
    printf("%s\n", currentNode->value);
    currentNode = currentNode->next;
  }
}

//Finds specified item in list and removes it
void removeItemFromList(ListNode ** head_ptr, char * valueToRemove){
  ListNode * previousNode = NULL;
  //Sets a cursor to iterate over nodes, starting with head
  ListNode * currentNode = *head_ptr;

  /*Iterates over each node as long as it's value is not NULL,
   checks if the value matches the value passed into this function.*/
    while(currentNode != NULL){
      /*Checks if value in current node matches value passed into function
      only checks if first pass has been made*/
      if(strcmp(currentNode->value, valueToRemove) == 0)
      {
          /*Creates a node object named 'temp'
          and stores the next node pointer of currentNode*/
          ListNode * temp = currentNode->next;
          free(currentNode); //removes entire node
          if(previousNode != NULL)
          {
            previousNode->next = temp;

          }
          else{
            *head_ptr = temp;
          }
          currentNode = temp;
        }
        else{
        previousNode = currentNode;
        currentNode = currentNode->next;
      }
    }
  }

int main(){
  char status = 0;
  ListNode * head = NULL;

  char inputValue [buffersize] = {0};
  while(status != 'e'){
    printf("Please choose one of the following: (P)rint current list, (A)dd item to list, (R)emove item from list, (E)xit: ");
    fgets(inputValue, buffersize, stdin);

    switch(inputValue[0])
    {
      /*Calls the function to print the contents of the linked list.*/
      case 'P':
        printf("Printing current contents:\n");
        printItemsInList(head);
        break;
        /*Obtains user input through the getCharInput function and passes This
        into the pushToList function.*/
      case 'A':
        printf("Please enter new item: ");
        getCharInput(inputValue);
        pushToList(&head, inputValue);
        break;
        /*Obtains user input through the getCharInput function and passes this
        into the removeItemFromList function to check if value exists inside
        the linked list. If value is present it will be removed from the list.*/
      case 'R':
        printf("Please enter item to remove: ");
        getCharInput(inputValue);
        removeItemFromList(&head, inputValue);
        break;
        /*Closes program, the 0 indicates the program closed as expected.*/
      case 'E':
        printf("Terminating Program...\n");
        return 0;
        /*Default will fire when none of the cases apply,
         it will notify the user their input returned and error.*/
      default:
        printf("An error has occured.\n");
    }
    /*Memset is used to null the memory of inputValuetest, not doing this could
    cause future input to be corrupted by data already present in this memory.*/
    memset(inputValue,0,100);
  }
}
