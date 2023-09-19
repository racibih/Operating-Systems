// list/list.c
// 
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_alloc() { 
  list_t* mylist =  (list_t *) malloc(sizeof(list_t)); 
  mylist->head = NULL;
  return mylist;
}

void list_free(list_t *l) {
  free(l);
}

void list_print(list_t *l) {
  
   node_t* cur_node = (node_t *) malloc(sizeof(node_t));
  cur_node = l->head;
  if(cur_node==NULL){
    printf("Empty List \n");

  }
    while (cur_node)
    {
        printf("%d \n", cur_node->value);
        cur_node = cur_node->next;
    }
 
    printf("\nCurrent List: \n");
}

char * listToString(list_t *l) {
  char* buf = (char *) malloc(sizeof(char) * 1024);
  char tbuf[20];

	node_t* curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    curr = curr->next;
    strcat(buf, tbuf);
  }
  strcat(buf, "NULL");
  return buf;
}

int list_length(list_t *l) { 
int count = 0; // Initialize count
    node_t* cur_node = l->head; // Initialize current
    while (cur_node != NULL) {
        count++;
        cur_node = cur_node->next;
    }
    return count;
} 

void list_add_to_back(list_t *l, elem value) {
  node_t* new_node = (node_t *) malloc(sizeof(node_t));
  new_node->value = value;
  new_node->next = NULL;

  if(l->head == NULL){
    node_t* head = new_node;
  }
    node_t* last_node = l->head;

  while(last_node){
    last_node = last_node->next;
  }
  last_node->next = new_node;
}
void list_add_to_front(list_t *l, elem value) {
     node_t* cur_node = (node_t *) malloc(sizeof(node_t));
     cur_node->value = value;
     cur_node->next = NULL;

     /* Insert to front */

     node_t* head = l->head;  // get head of list

     cur_node->next = l->head;
     l->head = cur_node;


}
void list_add_at_index(list_t *l, elem value, int index) {
   node_t* old_node = (node_t *) malloc(sizeof(node_t));
  node_t* head = l->head;
  node_t* curr_node = l->head;
  int count = 0;
  if(head->next==NULL){
    list_add_to_back(l,value);
  }
  while(curr_node){
    curr_node = curr_node->next;
    count++;
    if(count==index){
      break;
    }
  }
    old_node->value= curr_node->value;
    old_node->next= NULL;
    curr_node->value=value;
    curr_node->next= old_node;

}

elem list_remove_from_back(list_t *l) { return -1; }
elem list_remove_from_front(list_t *l) { 
       node_t* cur_node = (node_t *) malloc(sizeof(node_t));
        node_t* head = l->head;
        if(head==NULL){
          return;
        }
        cur_node = head;
        head = head->next;
        int removed = cur_node->value;
        free(cur_node);
  return removed; }
elem list_remove_at_index(list_t *l, int index) { 
         node_t* cur_node = (node_t *) malloc(sizeof(node_t));
        node_t* temp = l->head;
        node_t* head = l->head;
        int i;
        int val;
        if(index==0){
          head= head->next;
          temp->next=NULL;
          free(temp);
          return 0;
        }
      /*  int length = list_length(l);
         if(index>length){
          return;
        }*/

        else{
          for (i=0; i<index-1; i++){
          temp = temp->next; // previous node of node to be deleted
          
          }
          cur_node = temp->next; // node to be deleted
          temp->next = temp->next->next; 
          
          val = cur_node->value;
          cur_node->next = NULL;
          free(cur_node);
          return val;
        }
        
  }
bool list_is_in(list_t *l, elem value) { return false; }
elem list_get_elem_at(list_t *l, int index) {

  int count = 1;
  node_t* cur_node = (node_t *) malloc(sizeof(node_t));
  node_t* head = l->head;
  if(head->next == NULL){
    return 0;
  }
  
  node_t* last_node = l->head;
if(index > list_length(l) || last_node==NULL){
    return -1;
  }
  
  while(last_node !=NULL){
    last_node = last_node->next;
    count++;
    if(count==index){  
      break;
    }
  }
int num = last_node->value;
  
  return num;
  }
int list_get_index_of(list_t *l, elem value) { 
  
  
  return -1; }

