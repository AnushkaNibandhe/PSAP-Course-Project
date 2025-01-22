#include <stdio.h>
#include <string.h>

#define MAX_HALLS 3
#define MAX_SLOTS 3
#define FILENAME "hall_availability.txt"

// Structure for hall availability
typedef struct {
    int hallNumber;
    char date[11];   // Format: DD-MM-YYYY
    char slot[10];   // Morning, Afternoon, Evening
    int isAvailable; // 1 if available, 0 if not
} Hall;

// Function prototypes
void initializeHalls();
void checkAvailability();
int bookHall(float *hallCost);
void calculateAccessoriesCost(float *extrasCost);
void calculateMenuCost(float *menuCost);
void updateFile(Hall halls[], int count);

int main() {
    int choice;
    float totalCost = 0, hallCost = 0, extrasCost = 0, menuCost = 0;
    int hallBooked = 0; // Tracks if a hall has been booked

    printf("Welcome to the Event Management System\n");

    do {
        printf("\n----- Main Menu -----\n");
        printf("1. Hall Renting (Check Availability)\n");
        printf("2. Accessories\n");
        printf("3. Menu\n");
        printf("4. Calculate Total Cost\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                hallBooked = bookHall(&hallCost);
                break;
            case 2:
                if (hallBooked) {
                    calculateAccessoriesCost(&extrasCost);
                } else {
                    printf("Please book a hall first before selecting accessories.\n");
                }
                break;
            case 3:
                if (hallBooked) {
                    calculateMenuCost(&menuCost);
                } else {
                    printf("Please book a hall first before selecting a menu.\n");
                }
                break;
            case 4:
                if (!hallBooked) {
                    printf("Please book a hall and select options first to calculate total cost.\n");
                } else {
                    totalCost = hallCost + extrasCost + menuCost;
                    printf("\n----- Summary -----\n");
                    printf("Hall Cost: Rs. %.2f\n", hallCost);
                    printf("Accessories Cost: Rs. %.2f\n", extrasCost);
                    printf("Menu Cost: Rs. %.2f\n", menuCost);
                    printf("Total Cost: Rs. %.2f\n", totalCost);
                }
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 5);

    return 0;
}

// Initialize hall availability in file
void initializeHalls() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file for initialization.\n");
        return;
    }

    Hall halls[MAX_HALLS * MAX_SLOTS] = {
        {1, "01-01-2025", "Morning", 1}, {1, "01-01-2025", "Afternoon", 1}, {1, "01-01-2025", "Evening", 1},
        {2, "01-01-2025", "Morning", 1}, {2, "01-01-2025", "Afternoon", 1}, {2, "01-01-2025", "Evening", 1},
        {3, "01-01-2025", "Morning", 1}, {3, "01-01-2025", "Afternoon", 1}, {3, "01-01-2025", "Evening", 1}
    };

    for (int i = 0; i < MAX_HALLS * MAX_SLOTS; i++) {
        fwrite(&halls[i], sizeof(Hall), 1, file);
    }

    fclose(file);
    printf("Hall availability initialized.\n");
}

// Check hall availability
void checkAvailability() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file. Initializing availability.\n");
        initializeHalls();
        return;
    }

    Hall hall;
    printf("\n----- Hall Availability -----\n");
    while (fread(&hall, sizeof(Hall), 1, file)) {
        printf("Hall %d - Date: %s, Slot: %s - %s\n",
               hall.hallNumber, hall.date, hall.slot,
               hall.isAvailable ? "Available" : "Not Available");
    }

    fclose(file);
}

// Book a hall
int bookHall(float *hallCost) {
    FILE *file = fopen(FILENAME, "r+");
    if (file == NULL) {
        printf("Error opening file. Initializing availability.\n");
        initializeHalls();
        return 0;
    }

    int hallChoice, found = 0;
    char date[11], slot[10];
    Hall halls[MAX_HALLS * MAX_SLOTS];
    int index = 0;

    checkAvailability(); // Show current availability
    printf("\nEnter the date (DD-MM-YYYY): ");
    scanf("%s", date);
    printf("Enter the time slot (Morning/Afternoon/Evening): ");
    scanf("%s", slot);
    printf("Enter the hall number you want to book (1-3): ");
    scanf("%d", &hallChoice);

    float hallRent[] = {10000.0, 20000.0, 50000.0};

    while (fread(&halls[index], sizeof(Hall), 1, file)) {
        if (halls[index].hallNumber == hallChoice &&
            strcmp(halls[index].date, date) == 0 &&
            strcmp(halls[index].slot, slot) == 0 &&
            halls[index].isAvailable) {
            halls[index].isAvailable = 0;
            *hallCost = hallRent[hallChoice - 1];
            found = 1;
            break;
        }
        index++;
    }

    if (found) {
        rewind(file);
        updateFile(halls, index + 1);
        printf("Hall %d successfully booked for %s (%s).\n", hallChoice, date, slot);
    } else {
        printf("Sorry, the selected hall is not available.\n");
        *hallCost = 0;
    }

    fclose(file);
    return found;
}

// Update the hall availability file
void updateFile(Hall halls[], int count) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file for updating.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fwrite(&halls[i], sizeof(Hall), 1, file);
    }

    fclose(file);
}

// Calculate accessories cost
void calculateAccessoriesCost(float *extrasCost) {
    int choice;
    char moreExtras;

    printf("\nExtras\n");
    printf("1. Wedding Combo (Garlands, Akshada, Bouquets): Rs. 200\n");
    printf("2. Bouquets: Rs. 150\n");
    printf("3. Confetti Machine: Rs. 4000\n");
    printf("4. Akshada: Rs. 2000\n");

    do {
        printf("Enter your choice (0 to stop): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: *extrasCost += 200; break;
            case 2: *extrasCost += 150; break;
            case 3: *extrasCost += 4000; break;
            case 4: *extrasCost += 2000; break;
            case 0: break;
            default:
                printf("Invalid extras choice! Try again.\n");
        }

        if (choice != 0) {
            printf("Do you want to add more extras? (y/n): ");
            scanf(" %c", &moreExtras);
        } else {
            moreExtras = 'n';
        }
    } while (moreExtras == 'y');
}

// Calculate menu cost
void calculateMenuCost(float *menuCost) {
    int choice, quantity;
    float price = 0;

    printf("\nEvent Management Menu\n");
    printf("1. Veg Thali: Rs. 200\n");
    printf("2. Non-Veg Thali: Rs. 300\n");
    printf("3. South Indian: Rs. 300\n");
    printf("4. Punjabi: Rs. 300\n");
    printf("5. Italian: Rs. 350\n");
    printf("6. Oriental: Rs. 350\n");
    printf("Enter your choice (0 to skip): ");
    scanf("%d", &choice);

    if (choice != 0) {
        printf("Enter quantity: ");
        scanf("%d", &quantity);

        switch (choice) {
            case 1: price = 200; break;
            case 2: price = 300; break;
            case 3: price = 300; break;
            case 4: price = 300; break;
            case 5: price = 350; break;
            case 6: price = 350; break;
            default:
                printf("Invalid menu choice!\n");
                return;
        }
        *menuCost = price * quantity;
    }
}

