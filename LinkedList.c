//create program using linked list which allows user to add a string which gets added to linked list
//each time a string is added it needs to print any previously stored strings
// bonus pts create a menu with 4 options.
//option 1 : add string, option 2: delete string, using string as identifyer, option 3: print all stored strings, 4: exit program


#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//creates a new type of ListNode which stores a char pointer and a pointer to a new node. This will be used to create a linked list.
typedef struct node {
  char * value;
  struct node * next;
}ListNode;

//creating prototypes for each function
void getCharInput(char * inputValue);
void pushToList(ListNode ** head, char * newvalue);
void printItemsInList(ListNode * head);
void removeItemFromList(ListNode ** head, char * valueToRemove);


/*function used to retrieve character input from the command line. User input
will be stored at the address of inputValue */
void getCharInput(char * inputValue){
  if( fgets(inputValue, 100, stdin) != NULL)
  {
    /*goes to the index of the newline character in inputValue and replaces it
    with a NULL character*/
    inputValue[strcspn ( inputValue, "\n" )] = 0;
  }
}

void pushToList(ListNode ** head_ptr, char * newvalue) {

      if(*head_ptr == NULL){
        //printf("creating\n" );
        *head_ptr = (ListNode *)malloc(sizeof(ListNode));

        (*head_ptr)->value = (char *)malloc(strlen(newvalue) + 1) ;
        strcpy((*head_ptr)->value, newvalue);
        (*head_ptr)->next = NULL;
      }
      else{
        //printf("searching\n" );
        //finds current last item in the list (by way of finding null pointer)
        ListNode * currentNode = *head_ptr;
        while (currentNode->next != NULL) {
            currentNode = currentNode->next;
        }

        //sets pointer to refer to new node in the list and sets value of new node
        currentNode->next = (ListNode *) malloc(sizeof(ListNode));
        currentNode->next->value = (char *)malloc(strlen(newvalue) + 1);
        strcpy(currentNode->next->value, newvalue);
        //currentNode->next->value = newvalue;
        currentNode->next->next = NULL;
      }
  }

//iterates over each value in the list and checks if pointer is NULL, if it is not NULL it prints the value and moves the cursor to the next node
void printItemsInList(ListNode * head){
  ListNode * currentNode = head;

  while(currentNode != NULL){
    printf("%s\n", currentNode->value);
    //printf("%p test\n", currentNode->value );
    currentNode = currentNode->next;
  }
}

//finds specified item in list and removes it
void removeItemFromList(ListNode ** head_ptr, char * valueToRemove){
  //printf("%s\n", valueToRemove );
  ListNode * previousNode = NULL;
  //sets a cursor to iterate over nodes, starting with head
  ListNode * currentNode = *head_ptr;

  //iterates over each node as long as it's value is not NULL, checks if the value matches the value passed into this function.
  //int i = 0;

    while(currentNode != NULL){

      if(strcmp(currentNode->value, valueToRemove) == 0) //checks if value in current node matches value passed into function only checks if first pass has been made
      {
          ListNode * temp = currentNode->next; //creates a node object named 'temp' and stores the next node pointer of currentNode
          //printf("%p TESTBEFORE\n", previousNode->next);
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

  char inputValuetest [100] = {0};

  while(status != 'e'){
    printf("Please choose one of the following: (P)rint current list, (A)dd item to list, (R)emove item from list, (E)xit: ");
    fgets(inputValuetest, 100, stdin);
    char inputValue [100] = {0};
    switch(inputValuetest[0])
    {
      case 'P':
        printf("Printing current contents:\n");
        printItemsInList(head);
        break;
      case 'A':
        printf("Please enter new item: ");
        getCharInput(inputValue);
        pushToList(&head, inputValue);
        break;
      case 'R':
        printf("Please enter item to remove: ");
        getCharInput(inputValue);
        removeItemFromList(&head, inputValue);
        break;
      case 'E': //closes program,
        printf("Terminating Program...\n");
        return 0;
      default:
        printf("An error has occured.\n");
    }
    memset(inputValuetest,0,100);
  }
}
