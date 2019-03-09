#include <stdio.h>

// typedef struct ticket_tag{
//   char ticket_id[10];
//   int noOfPassengers;
// }ticket;

typedef struct passenger_tag{
  char pass_name[20];
  // struct ticket tic;
  char ticket_id[10];
  int age;
  int luggage_weight;
  int fine;
  int seat_no;
  // int noOfpassAssociated;
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

passenger* initialisePassenger(){
  passenger *fptr;
  fptr = (passenger*)malloc(sizeof(passenger));
  fptr -> pass_name[0] = '\0';
  fptr -> ticket_id[0] = '\0';
  fptr -> age = 0;
  fptr -> luggage_weight = 0;
  fptr -> fine = 0;
  fptr -> seat_no = 0;
  // fptr -> noOfpassAssociated = 0;
  fptr -> next = NULL;
  return fptr;
}
passenger* getPassenerDetails(){
  passenger *fptr;
  // char name[20];
  fptr = initialisePassenger();
  printf("Enter Name of Passenger: ");
  scanf("%s", fptr -> pass_name);
  printf("Enter age: ");
  scanf("%d", fptr -> age);
  printf("Enter the weight of luggage: ");
  scanf("%d", fptr -> luggage);
  if (fptr -> luggage > 15) {
    /* code */
    fptr -> fine = 100 * ( (fptr -> luggage) - 15 );
  }
  return fptr;
}
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
  passenger *pass, *temp, *pre_ptr;
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
    pre_ptr = (wptr -> fptr) -> pptr;
    printf("No of Passengers: ");
    scanf("%d", &p);
    if (p > 4 || p < 1) {
      printf("Enter proper no. of passengers (0<p<5)\n");
    }
    else{
      pass = getPassengerDetails();
      if ((pptr -> age) > 60) {
        for (int i = 0; i < 60; i++) {
          if ((((wptr -> fptr) -> seats[i]) % 2 == 0 || ((wptr -> fptr) -> seats[i]) % 3 == 0 ) && ((wptr -> fptr) -> seats[i]) == 0) {
            (wptr -> fptr) -> seats[i] = 1;
            pptr -> seat_no = i + 1;
          }
        }
      }
      else if ((pptr -> age) < 15) {
        for (int i = 0; i < 60; i++) {
          if ((((wptr -> fptr) -> seats[i]) % 6 == 0 || ((wptr -> fptr) -> seats[i]) % 5 == 0 ) && ((wptr -> fptr) -> seats[i]) == 0) {
            (wptr -> fptr) -> seats[i] = 1;
            pptr -> seat_no = i + 1;
          }
        }
      }
      else{
        for (int i = 0; i < 60; i++) {
          if (((wptr -> fptr) -> seats[i]) == 0) {
            (wptr -> fptr) -> seats[i] = 1;
            pptr -> seat_no = i + 1;
          }
        }
      }
      int s = i;
      pass -> next = pre_ptr;
      if (p != 1) {
        for (int q = 1; q < p; q++) {
          temp = getPassengerDetails();
          if (((wptr -> fptr) -> seats[s]) == 0) {
            (wptr -> fptr) -> seats[s] = 1;
            temp -> seat_no = s + 1;
            temp -> next = pass;
            pass = temp;
          }
        }
      }
      wptr -> fptr -> pptr = pass;
    }
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
