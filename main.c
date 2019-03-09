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
//d;kfks
dknk;
typedef struct flight_tag{
  char flight_id[3];
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
int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}
