#include <stdio.h>

typedef struct ticket_tag{
  char ticket_id[10];
  int noOfPassengers;
}ticket;

typedef struct passenger_tag{
  char pass_name[20];
  struct ticket tic;
  int age;
  int luggage_weight;
  int fine;
  int seat_no;
  int noOfpassAssociated;
  struct passenger_tag *next;
}passenger;

typedef struct flight_tag{
  char flight_id[6];
  char seats[60];
  int noOfAllocSeats;
  struct passenger *pptr;
  struct flight_tag *next;
}flight;

typedef struct window_tag{
  char window_id[4];
  struct flight *fptr;
  struct window_tag *next;
  struct window_tag *prev;
}window;


flight* initialiseFlight(){
  flight *fptr;
  fptr = (flight*)malloc(sizeof(flight));
  fptr -> flight_id[0] = '\0';
  for (int i = 0; i < 60; i++) {
    fptr -> seats[i] = 0;
  }
  fptr -> noOfAllocSeats = 0;
  fptr -> pptr = NULL;
  fptr -> next = NULL;
  return fptr;
}
window* windowIAS(window **wpptr,char f_arr[][], int r, int c)
{
  window *temp,*ptr,*wptr;
  ptr = *wpptr;
  wptr = (window*)malloc(sizeof(window));
  wptr -> fptr = NULL;
  for (int i = 0; i < r; i++) {
    nptr = initialiseFlight();
    nptr -> next = wptr -> fptr;
    strcpy(nptr -> flight_id,f_arr[i]);
    wptr -> fptr = nptr;
  }
  ptr 
  nptr->data=d;
  nptr->next=ptr;
  lptr=nptr;
  return lptr;
}
node_type* iaS(node_type **lpptr,int d)
{
	node_type *lptr,*ptr,*nptr;
	ptr=*lpptr;
	nptr=(node_type*)malloc(sizeof(node_type));
	nptr->data=d;
	nptr->next=ptr;
	lptr=nptr;
	return lptr;
}node_type* iaS(node_type **lpptr,int d)
{
	node_type *lptr,*ptr,*nptr;
	ptr=*lpptr;
	nptr=(node_type*)malloc(sizeof(node_type));
	nptr->data=d;
	nptr->next=ptr;
	lptr=nptr;
	return lptr;
}
int main(int argc, char const *argv[]) {
  /* code */

  return 0;
}
