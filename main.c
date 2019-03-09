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
  char window_name[10];
  char window_id[4];
  struct flight *fptr;
  struct window_tag *next;
  struct window_tag *prev;
}window;

window* windowIAS(window **lpptr,)
{
	window *lptr,*ptr,*nptr;
	ptr=*lpptr;
	nptr=(window*)malloc(sizeof(window));
	nptr->data=d;
	nptr->next=ptr;
	lptr=nptr;
	return lptr;
}

flight* initialiseFlight(){
  flight *fptr;
  fptr = (flight*)malloc(sizeof(flight));
  fptr -> flight_id[0] = '\0';
  for (int i = 0; i < 60; i++) {
    /* code */
    fptr -> seats[i] = 0;
  }
  fptr -> noOfAllocSeats = 0;
  pptr = NULL;
  fptr -> next = NULL;
  return fptr;
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
