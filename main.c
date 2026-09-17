#include "hospital.h"

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
        printf("=======================================================\n\n");
        printf("\t1. Register a New Patient\n");
        printf("\t2. Print Patient Bill\n");
        printf("\t3. View Priority List\n");
        printf("\t4. View Analytics Reports\n");
        printf("\t5. Exit\n\n");
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
                printf("\n--- Print Patient Bill ---\n");

                if (patientCount == 0) {
                    printf("No patients registered yet!\n");
                    break;
                }

                int searchID;
                printf("Enter Patient ID (maximum 100): ");
                scanf("%d", &searchID);

                int index = searchID - 1;

                if (index < 0 || index >= patientCount) {
                    printf("Patient ID not found!\n");
                    break;
                }

                int specIndex = specialtyID[index] - 1; // to know and cal  general, surgical bla bla bla

                float baseFee = baseFees[specIndex];
                float surcharge = 0.0;
                int surchargePct = 0;
                char urgencyStr[30];

                if (urgencyLevel[index] == 1) {
                    strcpy(urgencyStr, "Level 1 (Normal)");
                } else if (urgencyLevel[index] == 2) {
                    strcpy(urgencyStr, "Level 2 (Urgent)");
                    surcharge = baseFee * 0.20;
                    surchargePct = 20;
                } else {
                    strcpy(urgencyStr, "Level 3 (Critical)");
                    surcharge = baseFee * 0.50;
                    surchargePct = 50;
                }

                float wardCost = 0.0;
                char wardStr[50];
                if (isAdmitted[index] == 1) {
                    int wIndex = wardID[index] - 1;
                    wardCost = daysAdmitted[index] * wardRates[wIndex];
                    sprintf(wardStr, "%s", wardNames[wIndex]);
                } else {
                    strcpy(wardStr, "Not Admitted (OPD)");
                }

                float grossTotal = baseFee + surcharge + wardCost;

                float discount = 0.0;
                char ageStr[50];
                if (patientAges[index] < 5 || patientAges[index] > 65) {
                    discount = grossTotal * 0.15;
                    sprintf(ageStr, "%d Years (15%% Subsidy Eligible)", patientAges[index]);
                } else {
                    sprintf(ageStr, "%d Years (No Subsidy)", patientAges[index]);
                }

                float finalPayable = grossTotal - discount;

                float waitTime = (currentQueueCount[specIndex] - 1) * consultationTimes[specIndex];
                if (waitTime < 0) waitTime = 0.0;

                const char* specNames[] = {"General Practice (OPD)", "Paediatrics", "Cardiology", "Neurology"};

                printf("\n======================================================\n");
                printf("            SMART HOSPITAL ADMISSION & BILL           \n");
                printf("=======================================================\n");
                printf("Patient ID           : PAT-%d\n", searchID);
                printf("Patient Name         : %s\n", patientNames[index]);
                printf("Age                  : %s\n", ageStr);
                printf("Specialty            : %s\n", specNames[specIndex]);
                printf("Assigned Ward        : %s\n", wardStr);
                printf("Urgency Level        : %s\n", urgencyStr);
                printf("Base Consultation Fee: LKR %.2f\n", baseFee);
                printf("Emergency Surcharge  : LKR %.2f (%d%%)\n", surcharge, surchargePct);

                if (isAdmitted[index] == 1) {
                    printf("Ward Stay Cost       : LKR %.2f (%d Days)\n", wardCost, daysAdmitted[index]);
                } else {
                    printf("Ward Stay Cost       : LKR 0.00\n");
                }

                printf("Gross Total Bill     : LKR %.2f\n", grossTotal);

                if (discount > 0) {
                    printf("Age Subsidy Discount : LKR -%.2f (15%%)\n", discount);
                } else {
                    printf("Age Subsidy Discount : LKR 0.00\n");
                }

                printf("Final Payable Amount : LKR %.2f\n", finalPayable);

                if (waitTime == 0) {
                    printf("Estimated Wait Time  : 0.00 mins (Immediate Attention)\n");
                } else {
                    printf("Estimated Wait Time  : %.2f mins\n", waitTime);
                }
                printf("=======================================================\n");
                break;

          case 3:
                printf("\n--- Patient Priority List ---\n");

                if (patientCount == 0) {
                    printf("No patients registered yet!\n");
                    break;
                }

                int order[MAX_PATIENTS];
                for (int i = 0; i < patientCount; i++) {
                    order[i] = i;
                }

                for (int i = 0; i < patientCount - 1; i++) {
                    for (int j = 0; j < patientCount - i - 1; j++) {

                        int p1 = order[j];
                        int p2 = order[j + 1];

                        if (urgencyLevel[p1] < urgencyLevel[p2]) {
                            order[j] = p2;
                            order[j + 1] = p1;
                        }
                    }
                }
                for (int i = 0; i < patientCount; i++) {
                    int p = order[i];

                    printf("Patient ID: PAT-%d | Name: %s | Urgency Level: %d\n",
                           1 + p, patientNames[p], urgencyLevel[p]);
                }

                break;



            case 4:

                printf("Exiting System. Good Bye!\n");

                break;
            case 5:
                printf("Exiting System. Good Bye!\n");
                break;
            default:
                printf("Invalid Choice! Please try again.\n");
        }
    } while(choice != 5);

    return 0;
}
