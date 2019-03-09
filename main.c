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
  char window_id[3];
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
void addFlightServiceWindow(window **wpptr,char f_arr[][], int r, int c)
{
  window *temp,*ptr,*wptr;
  ptr = *wpptr;
  wptr = (window*)malloc(sizeof(window));
  wptr -> window_id[0] = f_arr[0][0];
  wptr -> window_id[1] = f_arr[0][1];
  wptr -> window_id[2] = f_arr[0][2];
  wptr -> fptr = NULL;
  for (int i = 0; i < r; i++) {
    nptr = initialiseFlight();
    nptr -> next = wptr -> fptr;
    strcpy(nptr -> flight_id,f_arr[i]);
    wptr -> fptr = nptr;
  }
  wptr -> next = ptr;
  if (!ptr) {
    ptr -> prev = wptr;
  }
  *wpptr = wptr;
  // return wptr;
}
void allocateBoardingPass(window **wpptr,char flight_id[], char ticket_id[]){
  char w_id[3], f_id[2];
  int flag = 0, w, wf;
  window *wptr;
  wptr = *wpptr;
  w_id[0] = ticket_id[0];
  w_id[1] = ticket_id[1];
  w_id[2] = ticket_id[2];
  f_id[0] = ticket_id[3];
  f_id[1] = ticket_id[4];
  while (wptr && flag == 0) {
    w = strcmp(w_id, wptr -> window_id);
    if (w == 0) {
      while (wptr -> fptr && flag == 0) {
        wf = strcmp(f_id, (wptr -> fptr) -> flight_id);
        if(wf == 0){
          flag = 1;
        }
        if (flag == 0) {
          wptr -> fptr = (wptr -> fptr) -> next;
        }
      }
    }
    if (flag == 0) {
      wptr = wptr -> next;
    }
  }
  if (flag == 0) {
    printf("We can't find a suitable flight on the provided Details \n");
  }
  else if (flag == 1) {
    
  }
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
