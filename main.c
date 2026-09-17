#include <stdio.h>
#include <string.h>

int main() {
    int choice;

    do {

        printf("\n======================================================\n");
        printf("        SMART HOSPITAL & RESOURCE ALLOCATION SYSTEM     \n");
        printf("=======================================================\n");
        printf("1. Register a New Patient\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                break;
            case 2:
                printf("Exiting System. Good Bye!\n");
                break;
            default:
                printf("Invalid Choice! Please try again.\n");
        }
    } while(choice != 2);

    return 0;
}
