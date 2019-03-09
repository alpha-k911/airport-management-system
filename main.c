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
    scanf("%d", &fptr -> age);
    printf("Enter the weight of luggage: ");
    scanf("%d", &fptr -> luggage_weight);
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
void addFlightServiceWindow(window **wpptr,char f_arr[][6], int r, int c)
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

    if (ptr) {
        ptr -> prev = wptr;
    }
    else{
        wptr -> prev = NULL;
    }
    *wpptr = wptr;
    // return wptr;
}
void allocateBoardingPass(window **wpptr,char flight_id[], char ticket_id[]){
    char w_id[4], f_id[6];
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
    f_id[5] = '\0';
    w_id[3]='\0';
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
            strcpy(pptr -> ticket_id , ticket_id);
            if ((pptr -> age) > 60) {
                flag = 0;
                for (int i = 1; i < 60 && flag == 0; i++) {
                    f = wptr -> fptr;
                    if ((i % 2 == 0 || i % 3 == 0 ) && (f -> seats[i]) == 0) {
                        f -> seats[i] = 1;
                        flag = 1;
                        s = i;
                        f -> noOfAllocSeats = f -> noOfAllocSeats + 1;
                        pptr -> seat_no = i + 1;
                    }
                }
            }
            else if ((pptr -> age) < 15) {
                flag = 0;
                for (int i = 0; i < 60 && flag == 0; i++) {
                    f = wptr -> fptr;
                    if ((i % 6 == 0 || i % 5 == 0 ) && (f -> seats[i]) == 0) {
                        f -> seats[i] = 1;
                        flag = 1;
                        s = i;
                        f -> noOfAllocSeats = f -> noOfAllocSeats + 1;
                        pptr -> seat_no = i + 1;
                    }
                }
            }
            else{
                flag = 0;
                for (int i = 0; i < 60 && flag == 0; i++) {
                    f = wptr -> fptr;
                    if ((f -> seats[i]) == 0) {
                        f -> seats[i] = 1;
                        flag = 1;
                        s = i;
                        f -> noOfAllocSeats = f -> noOfAllocSeats + 1;
                        pptr -> seat_no = i + 1;
                    }
                }
            }
            // printf("seat alloted: %d", s);
            pptr -> next = pre_ptr;
            if (p != 1) {
                for (int q = 1; q < p; q++) {
                    temp = getPassengerDetails();
                    strcpy(temp -> ticket_id , ticket_id);
                    f = wptr -> fptr;
                    while ((f -> seats[s]) != 0) {
                        /* code */
                        s++;
                    }
                    // if ((f -> seats[s]) == 0) {
                    f -> noOfAllocSeats = f -> noOfAllocSeats + 1;
                    f -> seats[s] = 1;
                    temp -> seat_no = s + 1;
                    temp -> next = pptr;
                    pptr = temp;
                    // s++;
                    // }
                }
            }
            f = wptr -> fptr;
            f -> pptr = pptr;
        }
    }
}
void visitSeat(int i){
    i = i % 6;
    if (i == 0 || i == 5) {
        printf("Seat-Type: Window;\n");
    }
    else if (i == 1 || i == 4) {
        printf("Seat-Type: Middle;\n");
    }
    else {
        printf("Seat-Type: Aisle;\n");
    }
}
void visitPassenger(passenger *pptr){
    printf("Name:%s, ", pptr -> pass_name);
    printf("Age:%d, ", pptr -> age);
    printf("Luggage:%d, ", pptr -> luggage_weight);
    printf("Fine:%d, ", pptr -> fine);
    printf("Seat No:%d, ", pptr -> seat_no);
    visitSeat(pptr -> seat_no - 1);
}
void DisplayFlightData(window *wptr, char f[]){
    char w_id[4], f_id[6];
    flight *fl;
    passenger *pptr, *temp, *pre_ptr;
    int flag = 0, w, wf,s,i,p;
    // window *wptr;
    // wptr = *wpptr;
    f_id[0] = w_id[0] = f[0];
    f_id[1] = w_id[1] = f[1];
    f_id[2] = w_id[2] = f[2];
    f_id[3] = f[3];
    f_id[4] = f[4];
    f_id[5] = '\0';
    w_id[3]='\0';
    while (wptr && flag == 0) {
        w = strcmp(w_id, wptr -> window_id);
        if (w == 0) {
            while (wptr -> fptr && flag == 0) {
                fl = wptr -> fptr;
                wf = strcmp(f_id, fl -> flight_id);
                if(wf == 0){
                    flag = 1;
                }
                if (flag == 0) {
                    fl = wptr -> fptr;
                    wptr -> fptr = fl -> next;
                }
            }
        }
        if (flag == 0) {
            wptr = wptr -> next;
        }
    }
    fl = wptr -> fptr;
    pptr = fl -> pptr;
    while (pptr) {
        visitPassenger(pptr);
        pptr = pptr -> next;
    }
}
void DisplayPassengerDetails(window *wptr,char t[]){
  char w_id[4], f_id[6];
  flight *fl;
  passenger *pptr, *temp, *pre_ptr;
  int flag = 0, w, wf,s,i,p;
  // window *wptr;
  // wptr = *wpptr;
  f_id[0] = w_id[0] = t[0];
  f_id[1] = w_id[1] = t[1];
  f_id[2] = w_id[2] = t[2];
  f_id[3] = t[3];
  f_id[4] = t[4];
  f_id[5] = '\0';
  w_id[3]='\0';
  while (wptr && flag == 0) {
      w = strcmp(w_id, wptr -> window_id);
      if (w == 0) {
          while (wptr -> fptr && flag == 0) {
              fl = wptr -> fptr;
              wf = strcmp(f_id, fl -> flight_id);
              if(wf == 0){
                  flag = 1;
              }
              if (flag == 0) {
                  fl = wptr -> fptr;
                  wptr -> fptr = fl -> next;
              }
          }
      }
      if (flag == 0) {
          wptr = wptr -> next;
      }
  }
  fl = wptr -> fptr;
  pptr = fl -> pptr;
  while (pptr) {
    if (strcmp(pptr -> ticket_id,t) == 0) {
      visitPassenger(pptr);
    }
      pptr = pptr -> next;
  }
}
void DisplayAvailableSeats(window *wptr, char f[]){
  char w_id[4], f_id[6];
  flight *fl;
  passenger *pptr, *temp, *pre_ptr;
  int flag = 0, w, wf,s,i,p;
  // window *wptr;
  // wptr = *wpptr;
  f_id[0] = w_id[0] = f[0];
  f_id[1] = w_id[1] = f[1];
  f_id[2] = w_id[2] = f[2];
  f_id[3] = f[3];
  f_id[4] = f[4];
  f_id[5] = '\0';
  w_id[3]='\0';
  while (wptr && flag == 0) {
      w = strcmp(w_id, wptr -> window_id);
      if (w == 0) {
          while (wptr -> fptr && flag == 0) {
              fl = wptr -> fptr;
              wf = strcmp(f_id, fl -> flight_id);
              if(wf == 0){
                  flag = 1;
              }
              if (flag == 0) {
                  fl = wptr -> fptr;
                  wptr -> fptr = fl -> next;
              }
          }
      }
      if (flag == 0) {
          wptr = wptr -> next;
      }
  }
  fl = wptr -> fptr;
  for (int i = 0; i < 60; i++) {
    if( fl -> seats[i] == 0 ){
      printf("Seat No. %d", i);
      visitSeat(i);
    }
  }
}

int main(int argc, char const *argv[]) {
    /* code */
    window *win = NULL;
    char f[3][6],t[9];
    flight *fl;

    // for (int i = 0; i < 3; i++) {
    //   /* code */
    //   scanf("%s", f[i]);
    // }
    f[0][0]='I';
    f[0][1]='N';
    f[0][2]='N';
    f[0][3]='1';
    f[0][4]='0';
    f[0][5]='\0';
    f[1][0]='I';
    f[1][1]='N';
    f[1][2]='N';
    f[1][3]='1';
    f[1][4]='1';
    f[1][5]='\0';
    f[2][0]='I';
    f[2][1]='N';
    f[2][2]='N';
    f[2][3]='1';
    f[2][4]='2';
    f[2][5]='\0';


    t[0]='I';
    t[1]='N';
    t[2]='N';
    t[3]='1';
    t[4]='2';
    t[5]='0';
    t[6]='0';
    t[7]='1';
    t[8]='\0';

    // t[3]='1';
    // t[4]='1';
    // t[5]='\0';
    // t[0]='I';
    // t[1]='N';
    // t[2]='N';
    // t[3]='1';
    // t[4]='2';
    // t[5]='\0';

    // strcpy("IND01",f[0]);
    // strcpy("IND02",f[1]);
    // strcpy("IND03",f[2]);
    printf("%s\n",f[0]);

    addFlightServiceWindow(&win,f,3,5);
    allocateBoardingPass(&win,f[2],t);
    f[0][0]='A';
    f[0][1]='N';
    f[0][2]='N';
    f[0][3]='1';
    f[0][4]='0';
    f[0][5]='\0';
    f[1][0]='A';
    f[1][1]='N';
    f[1][2]='N';
    f[1][3]='1';
    f[1][4]='1';
    f[1][5]='\0';
    f[2][0]='A';
    f[2][1]='N';
    f[2][2]='N';
    f[2][3]='1';
    f[2][4]='2';
    f[2][5]='\0';
    t[0]='A';
    addFlightServiceWindow(&win,f,3,5);
    printf("%s  %s\n",f[2],t );
    allocateBoardingPass(&win,f[2],t);
    fl = win -> fptr;
    t[0]='I';
    f[2][0]='I';
    // printf("%d\n", fl -> noOfAllocSeats);
    // DisplayFlightData(win,f[2]);
    // DisplayPassengerDetails(win,t);
    DisplayAvailableSeats(win,f[2]);
    return 0;
}
