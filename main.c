#include <stdio.h>
#include <string.h>
// typedef struct ticket_tag{
//   char ticket_id[10];
//   int noOfPassengers;
// }ticket;

typedef struct passenger_tag{
  char pass_name[20];
  // struct ticket tic;
  char ticket_id[9];
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
  char window_id[4];
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
passenger* getPassengerDetails(){
  passenger *fptr;
  // char name[20];
  fptr = initialisePassenger();
  printf("Enter Name of Passenger: ");
  scanf("%s", fptr -> pass_name);
  printf("Enter age: ");
  scanf("%d", fptr -> age);
  printf("Enter the weight of luggage: ");
  scanf("%d", fptr -> luggage_weight);
  if (fptr -> luggage_weight > 15) {
    /* code */
    fptr -> fine = 100 * ( (fptr -> luggage_weight) - 15 );
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
void addFlightServiceWindow(window **wpptr,char f_arr[][5], int r, int c)
{
  window *temp,*ptr,*wptr;
  flight *nptr;
  ptr = *wpptr;
  wptr = (window*)malloc(sizeof(window));
  wptr -> window_id[0] = f_arr[0][0];
  wptr -> window_id[1] = f_arr[0][1];
  wptr -> window_id[2] = f_arr[0][2];
  wptr -> fptr = NULL;
  for (int i = 0; i < r; i++) {
    printf("1\n");
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
  flight *f;
  passenger *pptr, *temp, *pre_ptr;
  int flag = 0, w, wf,s,i,p;
  window *wptr;
  wptr = *wpptr;
  f_id[0] = w_id[0] = ticket_id[0];
  f_id[1] = w_id[1] = ticket_id[1];
  f_id[2] = w_id[2] = ticket_id[2];
  f_id[3] = ticket_id[3];
  f_id[4] = ticket_id[4];
  while (wptr && flag == 0) {
    w = strcmp(w_id, wptr -> window_id);
    if (w == 0) {
      while (wptr -> fptr && flag == 0) {
        f = wptr -> fptr;
        wf = strcmp(f_id, f -> flight_id);
        if(wf == 0){
          flag = 1;
        }
        if (flag == 0) {
          f = wptr -> fptr;
          wptr -> fptr = f -> next;
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
    f = wptr -> fptr;
    pre_ptr = f -> pptr;
    printf("No of Passengers: ");
    scanf("%d", &p);
    if (p > 4 || p < 1) {
      printf("Enter proper no. of passengers (0<p<5)\n");
    }
    else{
      pptr = getPassengerDetails();
      if ((pptr -> age) > 60) {
        for (int i = 0; i < 60; i++) {
          f = wptr -> fptr;
          if (((f -> seats[i]) % 2 == 0 || (f -> seats[i]) % 3 == 0 ) && (f -> seats[i]) == 0) {
            f -> seats[i] = 1;
            pptr -> seat_no = i + 1;
          }
        }
      }
      else if ((pptr -> age) < 15) {
        for (int i = 0; i < 60; i++) {
          f = wptr -> fptr;
          if (((f -> seats[i]) % 6 == 0 || (f -> seats[i]) % 5 == 0 ) && (f -> seats[i]) == 0) {
            f -> seats[i] = 1;
            pptr -> seat_no = i + 1;
          }
        }
      }
      else{
        for (int i = 0; i < 60; i++) {
          f = wptr -> fptr;
          if ((f -> seats[i]) == 0) {
            f -> seats[i] = 1;
            pptr -> seat_no = i + 1;
          }
        }
      }
      s = i;
      pptr -> next = pre_ptr;
      if (p != 1) {
        for (int q = 1; q < p; q++) {
          temp = getPassengerDetails();
          f = wptr -> fptr;
          if ((f -> seats[s]) == 0) {
            f -> seats[s] = 1;
            temp -> seat_no = s + 1;
            temp -> next = pptr;
            pptr = temp;
          }
        }
      }
      f = wptr -> fptr;
      f -> pptr = pptr;
    }
  }
}
// node_type* iaS(node_type **lpptr,int d)
// {
// 	node_type *lptr,*ptr,*nptr;
// 	ptr=*lpptr;
// 	nptr=(node_type*)malloc(sizeof(node_type));
// 	nptr->data=d;
// 	nptr->next=ptr;
// 	lptr=nptr;
// 	return lptr;
// }node_type* iaS(node_type **lpptr,int d)
// {
// 	node_type *lptr,*ptr,*nptr;
// 	ptr=*lpptr;
// 	nptr=(node_type*)malloc(sizeof(node_type));
// 	nptr->data=d;
// 	nptr->next=ptr;
// 	lptr=nptr;
// 	return lptr;
// }
int main(int argc, char const *argv[]) {
  /* code */
  window *win = NULL;
  char f[3][6];
  // for (int i = 0; i < 3; i++) {
  //   /* code */
  //   scanf("%s", f[i]);
  // }
  f[0][0]='I';
  f[0][1]='I';
  f[0][2]='I';
  f[0][3]='1';
  f[0][4]='0';
  f[0][5]='\0';
  f[1][0]='I';
  f[1][1]='I';
  f[1][2]='I';
  f[1][3]='1';
  f[1][4]='1';
  f[1][5]='\0';
  f[2][0]='I';
  f[2][1]='I';
  f[2][2]='I';
  f[2][3]='1';
  f[2][4]='2';
  f[2][5]='\0';

  // strcpy("IND01",f[0]);
  // strcpy("IND02",f[1]);
  // strcpy("IND03",f[2]);
  printf("%s",f[0]);
  addFlightServiceWindow(&win,f,3,5);
  return 0;
}
