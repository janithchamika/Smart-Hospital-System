#include <stdio.h>
#include <string.h>


#define MAX_PATIENTS 100

const char *wardNames[] = {"General Ward", "Paediatric Ward", "Surgical Ward", "ICU"};
const int bedCapacities[] = {20, 10, 10, 5};

int patientCount = 0;
int currentQueueCount[4] = {0}; //4 use for It has only 4 ques only
int bedOccupancy[4][20] = {0};


char patientNames[MAX_PATIENTS][50]; // 100 rows for save the name of patients that's why i have used MAX_PATIENTS Constant.
int patientAges[MAX_PATIENTS], daysAdmitted[MAX_PATIENTS]; // Reason for add MAX_PATIENTS to create 100 rows for each patient.
short urgencyLevel[MAX_PATIENTS], specialtyID[MAX_PATIENTS], isAdmitted[MAX_PATIENTS], wardID[MAX_PATIENTS];


int main() {
    short choice;

    do {

        printf("\n======================================================\n");
        printf("        SMART HOSPITAL & RESOURCE ALLOCATION SYSTEM     \n");
        printf("=======================================================\n");
        printf("1. Register a New Patient\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%hd", &choice);

        switch(choice) {
            case 1:

                printf("\n - Patient Registration ---------------\n");

                if (patientCount >= MAX_PATIENTS) {
                    printf("Maximum patient capacity reached!\n");
                    break;
                }

                printf("Enter Patient Name: ");
                scanf(" %[^\n]s", patientNames[patientCount]);

                printf("Enter Patient Age: ");
                scanf("%d", &patientAges[patientCount]);

                printf("Enter Urgency Level (1 = Normal, 2 = Urgent, 3 = Critical) : ");
                scanf("%hd", &urgencyLevel[patientCount]);

                printf("Select Specialty (1=General, 2=Paediatrics, 3=Cardiology, 4=Neurology): ");
                scanf("%hd", &specialtyID[patientCount]);

                currentQueueCount[specialtyID[patientCount] - 1]++;

                printf("Is Admitted to Ward? (1 = Yes, 0 = No): ");
                scanf("%hd", &isAdmitted[patientCount]);

                if (isAdmitted[patientCount] == 1) {
                    printf("Select Ward ID (1=General, 2=Paediatric, 3=Surgical, 4=ICU): ");
                    scanf("%hd", &wardID[patientCount]);

                    printf("Enter Days Admitted: ");
                    scanf("%d", &daysAdmitted[patientCount]);

                    int wIndex = wardID[patientCount] - 1;  // I get only the number it's like a index to save
                    int bedAllocated = -1;

                    for (int b = 0; b < bedCapacities[wIndex]; b++) {
                        if (bedOccupancy[wIndex][b] == 0) {
                            bedOccupancy[wIndex][b] = 1;
                            bedAllocated = b + 1; // to remember the bed number.
                            break;
                        }
                    }

                    if (bedAllocated != -1) {
                        printf("Bed #%02d allocated successfully in %s.\n", bedAllocated, wardNames[wIndex]);
                    } else {
                        printf("Sorry, no beds available in the selected ward!\n");
                    }
                } else {
                    wardID[patientCount] = 0;
                    daysAdmitted[patientCount] = 0;
                }

                patientCount++;
                printf("\n ~ Patient Registered Successfully !!\n");

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
