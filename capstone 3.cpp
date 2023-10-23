#include <stdio.h>
#include <string.h>

#define MAX_SEATS 10

typedef struct
 {
    char name[50];
    char password;
    int seatNumber;
} 
Reservation;

Reservation reservations[MAX_SEATS];
int numReservations = 0;

void displayMenu()
 {
    printf("\n----- Bus Reservation System -----\n");
    printf("1. View Available Seats\n");
    printf("2. Make a Reservation\n");
    printf("3. Cancel a Reservation\n");
    printf("4. View Reservations\n");
    printf("5. Exit\n");
    
    printf("Enter your choice: ");
}

void viewAvailableSeats() 
{
    printf("\nAvailable Seats:\n");
    for (int i = 0; i < MAX_SEATS; i++) {
        if (reservations[i].seatNumber == 0)
         {
            printf("Seat %d is available\n", i + 1);
        }
    }
}

void makeReservation()
 {
    int seatNumber;
    char name[50];

    printf("Enter your name: ");
    scanf("%s", name);

    viewAvailableSeats();
    printf("Enter the seat number you want to reserve: ");
    scanf("%d", &seatNumber);

    if (seatNumber < 1 || seatNumber > MAX_SEATS) {
        printf("Invalid seat number. Please try again.\n");
        return;
    }

    if (reservations[seatNumber - 1].seatNumber != 0) {
        printf("Sorry, seat %d is already reserved. Please choose another seat.\n", seatNumber);
        return;
    }

    Reservation newReservation;
    strcpy(newReservation.name, name);
    newReservation.seatNumber = seatNumber;

    reservations[seatNumber - 1] = newReservation;
    numReservations++;

    printf("Reservation successful!\n");
}

void cancelReservation() {
    int seatNumber;

    viewAvailableSeats();
    printf("Enter the seat number you want to cancel: ");
    scanf("%d", &seatNumber);

    if (seatNumber < 1 || seatNumber > MAX_SEATS) {
        printf("Invalid seat number. Please try again.\n");
        return;
    }

    if (reservations[seatNumber - 1].seatNumber == 0) {
        printf("Seat %d is not reserved.\n", seatNumber);
        return;
    }

    reservations[seatNumber - 1].seatNumber = 0;
    numReservations--;

    printf("Reservation for seat %d canceled successfully.\n", seatNumber);
}

void viewReservations() {
    printf("\nCurrent Reservations:\n");
    for (int i = 0; i < MAX_SEATS; i++) {
        if (reservations[i].seatNumber != 0) {
            printf("Seat %d: %s\n", i + 1, reservations[i].name);
        }
    }
}

int main() {
    int choice;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewAvailableSeats();
                break;
            case 2:
                makeReservation();
                break;
            case 3:
                cancelReservation();
                break;
            case 4:
                viewReservations();
                break;
            case 5:
                printf("Exiting program. Thank you!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

}