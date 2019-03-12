#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct passenger_tag{
    char pass_name[20];
    char ticket_id[9];
    int age;
    int luggage_weight;
    int fine;
    int seat_no;
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
    fptr -> next = NULL;
    return fptr;
}
passenger* getPassengerDetails(){
    passenger *fptr;
    fptr = initialisePassenger();
    printf("Enter Name of Passenger: ");
    scanf("%s", fptr -> pass_name);
    printf("Enter age: ");
    scanf("%d", &fptr -> age);
    printf("Enter the weight of luggage: ");
    scanf("%d", &fptr -> luggage_weight);
    if (fptr -> luggage_weight > 15) {
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
void addFlightServiceWindow(window **wpptr,char f_arr[][6], int r)
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
        // printf("1\n");
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
    // printf("SUCCESS\n");
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

        else if ((60 - (f -> noOfAllocSeats)) >= p)
        {
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
                if (flag == 0) {
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
                    if (flag == 0) {
                        printf("Sorry no seats left to allocate\n");
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
                if (flag == 0) {
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
                    if (flag == 0) {
                        printf("Sorry no seats left to allocate\n");
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
                if (flag == 0) {
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
                    if (flag == 0) {
                        printf("Sorry no seats left to allocate\n");
                    }
                }
            }
            pptr -> next = pre_ptr;
            if (p != 1) {
                for (int q = 1; q < p; q++) {
                    temp = getPassengerDetails();
                    strcpy(temp -> ticket_id , ticket_id);
                    f = wptr -> fptr;
                    while ((f -> seats[s]) != 0) {
                        s++;
                    }
                    f -> noOfAllocSeats = f -> noOfAllocSeats + 1;
                    f -> seats[s] = 1;
                    temp -> seat_no = s + 1;
                    temp -> next = pptr;
                    pptr = temp;
                }
            }
            f = wptr -> fptr;
            f -> pptr = pptr;
        }
        else{
            printf("Sorry for inconvenience caused, no seats are left according to your requirement \n");
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
    char flight[6];
    for (int i = 0; i < 5; i++) {
        /* code */
        flight[i] = pptr -> ticket_id[i];
    }
    // strcpy(flight, pptr -> ticket_id);
    flight[5] = '\0';
    printf("Flight:%s", flight);
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
    if (flag == 1) {
      /* code */
        fl = wptr -> fptr;
        pptr = fl -> pptr;
        printf("Flight Data for Flight: %s\n", f);
        while (pptr) {
            visitPassenger(pptr);
            pptr = pptr -> next;
        }
    }
    else{
        printf("We can't find any Flight on provided Flight ID.....\n");
    }
}
void DisplayPassengerDetails(window *wptr,char t[]){
    char w_id[4], f_id[6];
    flight *fl;
    passenger *pptr, *temp, *pre_ptr;
    int flag = 0, w, wf,s,i,p;
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
    if (flag == 1) {
        fl = wptr -> fptr;
        pptr = fl -> pptr;
        printf("Passenger details for Ticket ID: %s\n", t);
        while (pptr) {
            if (strcmp(pptr -> ticket_id,t) == 0) {
                visitPassenger(pptr);
            }
            pptr = pptr -> next;
        }
    }
    else{
        printf("We can't find any details on provided Ticket ID.....\n");
    }
}
void DisplayAvailableSeats(window *wptr, char f[]){
  char w_id[4], f_id[6];
  flight *fl;
  passenger *pptr, *temp, *pre_ptr;
  int flag = 0, w, wf,s,i,p;
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
      printf("Seat No. %d, ", i+1);
      visitSeat(i);
    }
  }
}

int main(int argc, char const *argv[]) {
    int inp,choice,l=1,r,check;
    window *win = NULL;
    char f[10][6],t[9],fli[6],tfli[6],tic[9];
    flight *fl;
    // for (int i = 0; i < 3; i++) {
    //   /* code */
    //   scanf("%s", f[i]);
    // }
    strcpy(f[0],"IND10\0");
    strcpy(f[1],"IND11\0");
    strcpy(f[2],"IND12\0");
    strcpy(t,"IND12001\0");
    // printf("%s\n",t);
    addFlightServiceWindow(&win,f,3);
    strcpy(f[0],"JET10\0");
    strcpy(f[1],"JET11\0");
    strcpy(f[2],"JET12\0");
    strcpy(t,"JET12001\0");
    addFlightServiceWindow(&win,f,3);
        printf("==========AIRPORT MANAGEMENT SYSTEM=========\n");
    while (l) {
        printf("============================================\n");
        printf("1.addFlightServiceWindow(Flight_IDs)\n2.allocateBoardingPass(Flight_ID, Ticket_ID)\n3.DisplayFlightData(Flight_ID)\n4.DisplayPassengerDetails(Ticket_ID)\n5.DisplayAvailableSeats(Flight_ID)\n");
        printf("============================================\n");
        printf("6.ExIt\n");
        printf("============================================\n");
        printf("Enter your choice>>> ");
        scanf("%d",&choice );
        printf("============================================\n");
        switch (choice) {
            case 1 : printf("Enter no of flights: ");
                    scanf("%d", &r);
                    for (int i = 0; i < r; i++) {
                        printf("Enter the Flight ID (e.g. IND11):  ");
                      scanf("%s", f[i]);
                    }
                    addFlightServiceWindow(&win,f,r);
                    break;
            case 2 : printf("Enter the Flight ID and Ticket ID (e.g. IND11 IND11056): ");
                    scanf("%s", &fli);
                    scanf("%s", &tic);
                    for (int i = 0; i < 5; i++) {
                        tfli[i] = tic[i];
                    }
                    tfli[5] = '\0';
                    check = strcmp(tfli,fli);
                    if (check == 0 && strlen(fli) == 5 && strlen(tic) == 8) {
                        allocateBoardingPass(&win,fli,tic);
                    }
                    else{
                        printf("Enter proper Flight ID and Ticket ID....\n");
                    }
                    break;
            case 3 : printf("Enter the Flight ID for Details (e.g. IND11): ");
                    scanf("%s", &fli);
                    if (strlen(fli) == 5) {
                        DisplayFlightData(win,fli);
                    }
                    else{
                        printf("Enter proper Flight ID....\n");
                    }
                    break;

            case 4 : printf("Enter the Ticket ID for Details (e.g. IND11078): ");
                    scanf("%s", &tic);
                    if (strlen(tic) == 8) {
                        DisplayPassengerDetails(win,tic);
                    }
                    else{
                        printf("Enter proper Ticket ID....\n");
                    }
                    break;
            case 5 : printf("Enter the Flight ID for Details (e.g. IND11): ");
                    scanf("%s", &fli);
                    if (strlen(fli) == 5) {
                        DisplayAvailableSeats(win,fli);
                    }
                    else{
                        printf("Enter proper Flight ID....\n");
                    }
                    break;
            case 6 : l = 0;
                    break;
            default : printf("Enter a proper Choice....\n");
                    break;
        }
    }
    return 0;
}
