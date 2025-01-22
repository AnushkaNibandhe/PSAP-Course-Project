#include <stdio.h>

// Function prototypes
float calculateAccessoriesCost();
float calculateMenuCost();
float calculateHallRentCost();

int main() {
    int choice;
    float totalCost = 0;

    printf("Event Management System\n");
    printf("1. Accessories\n");
    printf("2. Menu\n");
    printf("3. Hall Renting\n");
    printf("4. Calculate Total Cost\n");
    printf("5. Exit\n");

    FILE *file = fopen("EventCost.txt", "w+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    do {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                totalCost += calculateAccessoriesCost();
                fprintf(file, "Accessories Cost: Rs. %.2f\n", totalCost);
                break;
            case 2:
                totalCost += calculateMenuCost();
                fprintf(file, "Menu Cost: Rs. %.2f\n", totalCost);
                break;
            case 3:
                totalCost += calculateHallRentCost();
                fprintf(file, "Hall Rent Cost: Rs. %.2f\n", totalCost);
                break;
            case 4:
                printf("\nTotal Cost: Rs. %.2f\n", totalCost);
                fprintf(file, "Total Cost: Rs. %.2f\n", totalCost);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 5);

    fclose(file);
    return 0;
}

// Function for Accessories Cost
float calculateAccessoriesCost() {
    int choice;
    float price = 0;

    printf("\nAccessories\n");
    printf("1. Wedding Combo (Garlands, Akshada, Bouquets): Rs. 200\n");
    printf("2. Bouquets: Rs. 150\n");
    printf("3. Confetti Machine: Rs. 4000\n");
    printf("4. Akshada: Rs. 2000\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            price = 200;
            break;
        case 2:
            price = 150;
            break;
        case 3:
            price = 4000;
            break;
        case 4:
            price = 2000;
            break;
        default:
            printf("Invalid choice!\n");
            return 0;
    }

    printf("Accessories Cost: Rs. %.2f\n", price);
    return price;
}

// Function for Menu Cost
float calculateMenuCost() {
    int choice, quantity;
    float price = 0;

    printf("\nMenu\n");
    printf("1. Veg Thali: Rs. 200\n");
    printf("2. Non-Veg Thali: Rs. 300\n");
    printf("3. South Indian: Rs. 300\n");
    printf("4. Punjabi: Rs. 300\n");
    printf("5. Italian: Rs. 350\n");
    printf("6. Oriental: Rs. 350\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    switch (choice) {
        case 1:
            price = 200;
            break;
        case 2:
            price = 300;
            break;
        case 3:
            price = 300;
            break;
        case 4:
            price = 300;
            break;
        case 5:
            price = 350;
            break;
        case 6:
            price = 350;
            break;
        default:
            printf("Invalid choice!\n");
            return 0;
    }

    float totalPrice = price * quantity;
    printf("Menu Cost: Rs. %.2f\n", totalPrice);
    return totalPrice;
}

// Function for Hall Renting Cost
float calculateHallRentCost() {
    int hallChoice;
    float duration, cost = 0;
    float hall1Rent = 1000.0, hall2Rent = 2000.0, hall3Rent = 5000.0;

    printf("\nHall Renting\n");
    printf("1. Hall 1 - Rs. %.2f per hour\n", hall1Rent);
    printf("2. Hall 2 - Rs. %.2f per hour\n", hall2Rent);
    printf("3. Hall 3 - Rs. %.2f per hour\n", hall3Rent);

    printf("Enter your choice: ");
    scanf("%d", &hallChoice);
    printf("Enter duration (in hours): ");
    scanf("%f", &duration);

    switch (hallChoice) {
        case 1:
            cost = hall1Rent * duration;
            break;
        case 2:
            cost = hall2Rent * duration;
            break;
        case 3:
            cost = hall3Rent * duration;
            break;
        default:
            printf("Invalid choice!\n");
            return 0;
    }

    printf("Hall Rent Cost: Rs. %.2f\n", cost);
    return cost;
}

