#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEATS 10

struct bus
 {
     int busnumber;
     char drivername[40];
     char destination[40];
     char departure time;
     int seats(MAX_SEATS);
 }

 void display menu()
 {
     printf("\n\n");
     printf("Bus reservation system\n");
     printf("1.Reserve a seat\n");
     printf("2.cancel bus reservation\n");
     printf("3.Display bus details\n");
     printf("4.exit\n");


 }

 void reserve seat(struct Bus*bus)
 {
     int seatnumber;
     printf("Enter seat number 1-10:");
     scanf("%d",&seatnumber);

     if(seat number<1\\seat number> MAX_SEAT) {
     printf("invalid seat number\n");

     return;
     }
     if(bus ->seat[seatnumber-1]==0){
         bus->seats[seat number-1]=1;
         printf("seat reserved successfully!\n");
     }
     else{
         printf("seat already reserved!\n");
     }
 }

 void cancel reservation(struct Bus*bus)
 {
     int seat number;
     printf("Enter seat number 1-10:");
     scanf("%d",&seat number);

     if (seat number<1\\seat number>MAX_SEAT);{
     printf("invalid seat number!\n");

     return;
     }
     if (bus->seats[seat number-1]==1){
         bus->seats[seat number-1]=0;
         printf("reservation cancelled successfully!\n");
      }
      else{
          printf("seat not reserved!\n");}
      }
}

void display bus details(struct bus*bus)
{
    printf("\nbus number:%d\n",bus->bus number);
    printf("drivers name:%s\n",bus->driver name);
    printf("from:%s\n",bus->from);
    printf("to:%s\n"bus->to);
    printf("departure time:%s\n",bus->departure time);
    printf("seats:");
    for (int i=0;i<MAX_SEATS;I++){
        printf("%d",bus->seats[i]);
    }
    printf("\n");
}

int main()
{
    struct bus;
    bus.bus number=1
    strcpy(bus.drivername);
    strcpy(bus.from);
    strcpy(bus.to);
    strcpy(bus.departure time,10:00 AM);
    strcpy(bus.seats,0,size of bus(bus seats));

    int choice;
    while (1)
    {
        display menu();
        printf("Enter your choice:");
        scanf("%d,&choice");

        switch (choice)
        {
            case 1:
             reserve seat(&bus);
             break;
            case 2:
             cancel reservation(&bus);
             break;
            case 3:
             display bus details(&bus);
             break;
            case 4:
             exit(0);
            default;
             printf("invalid choice!\n");

        }
    }
     return 0;
}




