#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROUTES 9
#define MAX_BOOKINGS 120
#define MAX_SEAT_NAME_LENGTH 50  // Define the maximum length of a seat name

// Structure to represent a bus route
struct BusRoute {
    int routeID;
    char origin[50];
    char destination[50];
    char departureTime[10];
    int totalSeats;
    char seatNames[40][MAX_SEAT_NAME_LENGTH];
};

// Structure to represent a user reservation
struct Reservation {
    int routeID;
    int numSeats;
    char userName[50];
    char ticketID[10];
};

// Structure to represent an employee
struct Employee {
    char username[50];
    char password[50];
};

// Arrays to store bus routes, reservations, and employees
struct BusRoute routes[MAX_ROUTES];
struct Reservation bookings[MAX_BOOKINGS];
struct Employee employees[MAX_ROUTES];

int routeCount = 0;
int bookingCount = 0;
int employeeCount = 0;

// Function to add a new bus route
void addRoute(int routeID, char origin[], char destination[], char departureTime[], int totalSeats) {
    routes[routeCount].routeID = routeID;
    strcpy(routes[routeCount].origin, origin);
    strcpy(routes[routeCount].destination, destination);
    strcpy(routes[routeCount].departureTime, departureTime);
    routes[routeCount].totalSeats = totalSeats;
    routeCount++;
}

// Function to display available routes
void displayRoutes() {
    printf("Available Bus Routes:\n");
    for (int i = 0; i < routeCount; i++) {
        printf("Route %d: %s to %s, Departure Time: %s, Total Seats: %d\n",
               routes[i].routeID, routes[i].origin, routes[i].destination,
               routes[i].departureTime, routes[i].totalSeats);
    }
}

// Function to handle employee login
int employeeLogin(char username[], char password[]) {
    for (int i = 0; i < employeeCount; i++) {
        if (strcmp(employees[i].username, username) == 0 && strcmp(employees[i].password, password) == 0) {
            return 1; // Login successful
        }
    }
    return 0; // Login failed
}

// Function to create an employee account
void createEmployeeAccount(char username[], char password[]) {
    strcpy(employees[employeeCount].username, username);
    strcpy(employees[employeeCount].password, password);
    employeeCount++;
}
// Function to handle payment
float calculatePayment(int numSeats) {
    float pricePerSeat = 150.0;  // Change this to your desired price per seat
    return numSeats * pricePerSeat;
}
// Function to reserve seats
void reserveSeats(int routeID, int numSeats, char userName[]) {
    for (int i = 0; i < routeCount; i++) {
        if (routes[i].routeID == routeID) {
            if (routes[i].totalSeats - numSeats >= 0) {
                // Calculate the total cost using the payment function
                float totalCost = calculatePayment(numSeats);

                // Assign seat names to the reserved seats
                int seatsReserved = 0;
                for (int j = 0; j < routes[i].totalSeats && seatsReserved < numSeats; j++) {
                    if (routes[i].seatNames[j][0] == '\0') {
                        strcpy(routes[i].seatNames[j], userName);
                        seatsReserved++;
                    }
                }

                // Update the totalSeats and create the reservation
                routes[i].totalSeats -= numSeats;
                strcpy(bookings[bookingCount].userName, userName);
                bookings[bookingCount].routeID = routeID;
                bookings[bookingCount].numSeats = numSeats;
                sprintf(bookings[bookingCount].ticketID, "T%d", bookingCount + 1);
                bookingCount++;

                printf("Reservation successful. Your Ticket ID: %s\n", bookings[bookingCount - 1].ticketID);
                printf("Total Cost: $%.2f\n", totalCost);
            } else {
                printf("Not enough seats available for your request.\n");
            }
            return;
        }
    }
    printf("Route not found.\n");
}

// Function to display available seats for a route
void displayAvailableSeats(int routeID) {
    for (int i = 0; i < routeCount; i++) {
        if (routes[i].routeID == routeID) {
            printf("Available Seats for Route %d: %s to %s\n", routeID, routes[i].origin, routes[i].destination);
            for (int j = 0; j < routes[i].totalSeats; j++) {
                if (routes[i].seatNames[j][0] == '\0') {
                    printf("Seat %d: Available\n", j + 1);
                } else {
                    printf("Seat %d: Reserved by %s\n", j + 1, routes[i].seatNames[j]);
                }
            }
            return;
        }
    }
    printf("Route not found.\n");
}

// Function to cancel a reservation
void cancelReservation(char ticketID[]) {
    for (int i = 0; i < bookingCount; i++) {
        if (strcmp(bookings[i].ticketID, ticketID) == 0) {
            for (int j = 0; j < routeCount; j++) {
                if (routes[j].routeID == bookings[i].routeID) {
                    routes[j].totalSeats += bookings[i].numSeats;
                    break;
                }
            }
            printf("Reservation with Ticket ID %s canceled.\n", ticketID);
            for (int j = i; j < bookingCount - 1; j++) {
                bookings[j] = bookings[j + 1];
            }
            bookingCount--;
            return;
        }
    }
    printf("Reservation with Ticket ID %s not found.\n", ticketID);
}

// Function to display booking history
void displayBookingHistory() {
    printf("Booking History:\n");
    for (int i = 0; i < bookingCount; i++) {
        printf("Ticket ID: %s, Route ID: %d, Seats: %d, User: %s\n",
               bookings[i].ticketID, bookings[i].routeID, bookings[i].numSeats, bookings[i].userName);
    }
}

// Function to save data to files
void saveDataToFile() {
    // Save bus routes data to a file
    FILE *routesFile = fopen("routes.txt", "w");
    if (routesFile) {
        for (int i = 0; i < routeCount; i++) {
            fprintf(routesFile, "%d %s %s %s %d\n", routes[i].routeID, routes[i].origin, routes[i].destination, routes[i].departureTime, routes[i].totalSeats);
        }
        fclose(routesFile);
    } else {
        printf("Error: Could not save bus routes data to file.\n");
    }

    // Save reservations data to a file
    FILE *bookingsFile = fopen("reservations.txt", "w");
    if (bookingsFile) {
        for (int i = 0; i < bookingCount; i++) {
            fprintf(bookingsFile, "%d %d %s %s\n", bookings[i].routeID, bookings[i].numSeats, bookings[i].userName, bookings[i].ticketID);
        }
        fclose(bookingsFile);
    } else {
        printf("Error: Could not save reservations data to file.\n");
    }

    // Save employee data to a file
    FILE *employeesFile = fopen("employees.txt", "w");
    if (employeesFile) {
        for (int i = 0; i < employeeCount; i++) {
            fprintf(employeesFile, "%s %s\n", employees[i].username, employees[i].password);
        }
        fclose(employeesFile);
    } else {
        printf("Error: Could not save employee data to file.\n");
    }
}
// Function to load data from files
void loadDataFromFile() {
    // Load bus routes data from a file
    FILE *routesFile = fopen("routes.txt", "r");
    if (routesFile) {
        while (fscanf(routesFile, "%d %s %s %s %d", &routes[routeCount].routeID, routes[routeCount].origin, routes[routeCount].destination, routes[routeCount].departureTime, &routes[routeCount].totalSeats) == 5) {
            routeCount++;
        }
        fclose(routesFile);
    } else {
        printf("Warning: Could not load bus routes data from file.\n");
    }

    // Load reservations data from a file
    FILE *bookingsFile = fopen("reservations.txt", "r");
    if (bookingsFile) {
        while (fscanf(bookingsFile, "%d %d %s %s", &bookings[bookingCount].routeID, &bookings[bookingCount].numSeats, bookings[bookingCount].userName, bookings[bookingCount].ticketID) == 4) {
            bookingCount++;
        }
        fclose(bookingsFile);
    } else {
        printf("Warning: Could not load reservations data from file.\n");
    }

    // Load employee data from a file
    FILE *employeesFile = fopen("employees.txt", "r");
    if (employeesFile) {
        while (fscanf(employeesFile, "%s %s", employees[employeeCount].username, employees[employeeCount].password) == 2) {
            employeeCount++;
        }
        fclose(employeesFile);
    } else {
        printf("Warning: Could not load employee data from file.\n");
    }
}

int main() {
    addRoute(1, "NAIROBI", "THIKA", "10:00 AM", 40);
    addRoute(2, "NAIROBI", "KISUMU", "02:00 PM", 40);
    addRoute(3, "NAIROBI", "BOMET", "04:00 PM", 40);

    createEmployeeAccount("admin", "1234");
    createEmployeeAccount("brian", "****");

    int choice;
    char username[50], password[50];
    int loggedIn = 0;

    printf("Welcome to the Bus Reservation System\n");

    do {
        if (!loggedIn) {
            printf("Please log in to continue:\n");
            printf("Username: ");
            scanf("%s", username);
            printf("Password: ");
            scanf("%s", password);

            loggedIn = employeeLogin(username, password);

            if (!loggedIn) {
                printf("Login failed. Please try again.\n");
                continue;
            }
        }
        printf("\nBus Reservation System Menu\n");
printf("1. Display Available Routes\n");
printf("2. Add a Route\n");
printf("3. Reserve Seats\n");
printf("4. Cancel Reservation\n");
printf("5. Display Booking History\n");
printf("6. Logout\n");
printf("7. Save Data to Files\n");
printf("8. Load Data from Files\n");
printf("9. Exit\n");
printf("10. View Available Seats for a Route\n");
printf("Enter your choice: ");
scanf("%d", &choice);


        switch (choice) {
            case 1:
                displayRoutes();
                break;
            case 2:
                if (loggedIn) {
                    int routeID, totalSeats;
                    char origin[50], destination[50], departureTime[10];
                    printf("Enter Route ID, Origin, Destination, Departure Time, Total Seats: ");
                    scanf("%d %s %s %s %d", &routeID, origin, destination, departureTime, &totalSeats);
                    addRoute(routeID, origin, destination, departureTime, totalSeats);
                    printf("Route added successfully.\n");
                } else {
                    printf("Permission denied. Please login as an employee.\n");
                }
                break;
            case 3:
                if (loggedIn) {
                    int routeID, numSeats;
                    char userName[50];
                    printf("Enter Route ID, Number of Seats, and Your Name: ");
                    scanf("%d %d %s", &routeID, &numSeats, userName);
                    reserveSeats(routeID, numSeats, userName);
                   } else {
                    printf("Permission denied. Please login as an employee.\n");
                }
               
                break;
            case 4:
                if (loggedIn) {
                    char ticketID[10];
                    printf("Enter Ticket ID to cancel: ");
                    scanf("%s", ticketID);
                    cancelReservation(ticketID);
                } else {
                    printf("Permission denied. Please login as an employee.\n");
                }
                break;
            case 5:
                displayBookingHistory();
                break;
            case 6:
                printf("Logged out!Thankyou For Using The bus Reservation System.\n");
                loggedIn = 0;
                break;
             case 7:
        // Save data to files
        if (loggedIn) {
            saveDataToFile();
            printf("Data saved to files.\n");
        } else {
            printf("Permission denied. Please log in as an employee.\n");
        }
        break;
    case 8:
        // Load data from files
        if (loggedIn) {
            loadDataFromFile();
            printf("Data loaded from files.\n");
        } else {
            printf("Permission denied. Please log in as an employee.\n");
        }
        break;
    case 9:
        // Exit the program
        printf("Exiting the Bus Reservation System. Goodbye!\n");
        exit(0);
        break;
            case 10:
                if (loggedIn) {
                    int routeID;
                    printf("Enter Route ID to view available seats: ");
                    scanf("%d", &routeID);
                    displayAvailableSeats(routeID);
                } else {
                    printf("Permission denied. Please login as an employee.\n");
                }
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);

    return 0;
}
 
