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


char status = 's';

void pushToList(ListNode ** head, char * newvalue);
void printItemsInList(ListNode * head);
void removeItemFromList(ListNode ** head, char * valueToRemove);

void pushToList(ListNode ** head_ptr, char * newvalue) {

      if(*head_ptr == NULL){
        //printf("creating\n" );
        *head_ptr = (ListNode *)malloc(sizeof(ListNode));

        (*head_ptr)->value = (char *)malloc(sizeof(10)) ;
        memcpy((*head_ptr)->value, newvalue, strlen(newvalue));
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
        currentNode->next->value = newvalue;
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

    //printf("testOne\n" );
    //printf("%s\n", head->value );
    //iterates over each node as long as it's value is not NULL, checks if the value matches the value passed into this function.
    int i = 0;



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
  char status = 'i';
  ListNode * head = NULL;
  char * inputValue;
/*
  ListNode * head = (ListNode *)malloc(sizeof(ListNode));
  if(head == NULL){
    return 1;
  }
  head->value = (char *)malloc(sizeof(10)) ;
  memcpy(head->value, "MEMTEST", strlen("MEMTEST"));
  head->next = NULL;*/

/*
  while(status != 'e'){
    char status = 'i';
    printf("Please choose one of the following: (P)rint current list, (A)dd item to list, (R)emove item from list, (E)xit.\n");
    scanf(" %c" , &status);
    char * inputValue;
    switch(status)
    {
      case 'P':
        printf("Printing current contents:\n");
        printItemsInList(head);
        break;
      case 'A':
        printf("Please enter new item:\n");
        scanf("%s", inputValue);
        pushToList(&head, inputValue);
        break;
      case 'R':
        //char * valueToRemove;
        printf("Please enter item to remove:\n");
        scanf("%s", inputValue);
        printf("%s\n", inputValue );
        removeItemFromList(&head, inputValue);
        break;
      case 'E': //closes program
        printf("Terminating Program...\n");
        return 0;
    }
  }*/





  pushToList(&head, "WOOF\0"); //& used to pass memory address of head into the function so the function can alter the variable at the location in the parent scope
  pushToList(&head, "WOOF\0"); //will need to fix second value, currently program will delete first value if it matches strcmp, if second value matches it will again delete said value and thus delete the head value.
  pushToList(&head, "BARK\0");
  pushToList(&head, "BARK\0");
  pushToList(&head, "WOOF\0");
  pushToList(&head, "WOOF\0");
  pushToList(&head, "WOOF\0");
  pushToList(&head, "BARK\0");
  pushToList(&head, "BARK\0");
  printf("----\n");
  printItemsInList(head);
  removeItemFromList(&head, "WOOF");
  printf("----\n");
  //printf("%s\n", head->value);
  printItemsInList(head);
  pushToList(&head, "MAOW\0");
  pushToList(&head, "MAOW\0");
  printf("----\n");
  removeItemFromList(&head, "BARK");
  printItemsInList(head);






  /*
  printf("Please enter string: ");
  char * string;
  scanf("%s\0" , string);
  printf("%s\n", string );
*/

}
