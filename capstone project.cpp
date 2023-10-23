#include <stdio.h>
#include <stdlib.h>

#define MAX_BUSES 10
#define MAX_PASSENGERS 50

struct Bus {
    int id;
    char route[50];
    char departure_time[10];
    int capacity;
    int reserved_seats;
};

struct Reservation {
    int bus_id;
    int num_seats;
};

struct Bus buses[MAX_BUSES];
struct Reservation reservations[MAX_PASSENGERS];
int num_buses = 0;
int num_reservations = 0;

void displayMenu() {
    printf("\n*** Bus Reservation System ***\n");
    printf("1. Add Bus\n");
    printf("2. List Buses\n");
    printf("3. Reserve Seat\n");
    printf("4. View Reservations\n");
    printf("5. Cancel Reservation\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

void addBus() {
    if (num_buses < MAX_BUSES) {
        // Code to add a new bus to the system
        // Update the 'buses' array and increment 'num_buses'
    } else {
        printf("Maximum number of buses reached.\n");
    }
}

void listBuses() {
    // Code to list available buses
}

void reserveSeat() {
    // Code to reserve seats on a bus
}

void viewReservations() {
    // Code to display user's reservations
}

void cancelReservation() {
    // Code to cancel a reservation
}

int main() {
    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addBus();
                break;
            case 2:
                listBuses();
                break;
            case 3:
                reserveSeat();
                break;
            case 4:
                viewReservations();
                break;
            case 5:
                cancelReservation();
                break;
            case 6:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
