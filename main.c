#include "hospital.h"

int patientCount = 0;
int currentQueueCount[4] = {0}; //4 use for It has only 4 ques only
int bedOccupancy[4][20] = {0};


char patientNames[MAX_PATIENTS][50]; // 100 rows for save the name of patients that's why i have used MAX_PATIENTS Constant.
int patientAges[MAX_PATIENTS], daysAdmitted[MAX_PATIENTS]; // Reason for add MAX_PATIENTS to create 100 rows for each patient.
short urgencyLevel[MAX_PATIENTS], specialtyID[MAX_PATIENTS], isAdmitted[MAX_PATIENTS], wardID[MAX_PATIENTS];


int main() {
    short choice;

    FILE *fLoad = fopen("beds_status.txt", "r");
    if (fLoad != NULL) {
        for (int w = 0; w < 4; w++) {
            for (int b = 0; b < bedCapacities[w]; b++) {
                fscanf(fLoad, "%d", &bedOccupancy[w][b]);
            }
        }
        fclose(fLoad);
    }

    do {

        printf(C_TITLE "\n=======================================================\n" );
        printf( T_BOLD T_ITALIC "      SMART HOSPITAL & RESOURCE ALLOCATION SYSTEM     \n" );
        printf( "=======================================================\n\n" C_RESET);

        printf(C_MENU "\t1. Register a New Patient\n" );
        printf("\t2. Print Patient Bill\n");
        printf("\t3. View Priority List\n");
        printf("\t4. View Analytics Reports\n");
        printf("\t5. Exit\n\n" C_RESET);

        printf(T_ITALIC  C_PROMPT "Enter your choice: "C_RESET);
        scanf("%hd", &choice);

        switch(choice) {
            case 1:

                printf(C_TITLE "\n\n - Patient Registration ---------------\n\n"C_RESET);

                if (patientCount >= MAX_PATIENTS) {
                    printf(C_RED "Maximum patient capacity reached!\n" C_RESET);
                    break;
                }

                printf(T_ITALIC  C_ORANGE "Enter Patient Name: "C_RESET);
                scanf(" %[^\n]s", patientNames[patientCount]);

                printf(T_ITALIC  C_ORANGE "\nEnter Patient Age: "C_RESET);
                scanf("%d", &patientAges[patientCount]);

                printf(T_ITALIC  C_ORANGE "\nEnter Urgency Level (1 = Normal, 2 = Urgent, 3 = Critical) : "C_RESET);
                scanf("%hd", &urgencyLevel[patientCount]);

                printf(T_ITALIC  C_ORANGE "\nSelect Specialty (1=General, 2=Paediatrics, 3=Cardiology, 4=Neurology): "C_RESET);
                scanf("%hd", &specialtyID[patientCount]);

                currentQueueCount[specialtyID[patientCount] - 1]++;

                printf(T_ITALIC  C_ORANGE "\nIs Admitted to Ward? (1 = Yes, 0 = No): "C_RESET);
                scanf("%hd", &isAdmitted[patientCount]);

                if (isAdmitted[patientCount] == 1) {
                    printf(T_ITALIC  C_ORANGE "\nSelect Ward ID (1=General, 2=Paediatric, 3=Surgical, 4=ICU): "C_RESET);
                    scanf("%hd", &wardID[patientCount]);

                    printf(T_ITALIC  C_ORANGE "\nEnter Days Admitted: "C_RESET);
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
                        printf("\n\nBed #%02d allocated successfully in %s.\n", bedAllocated, wardNames[wIndex]);
                    } else {
                        printf("\n\nSorry, no beds available in the selected ward!\n");
                    }
                } else {
                    wardID[patientCount] = 0;
                    daysAdmitted[patientCount] = 0;
                }

                patientCount++;
                printf(T_ITALIC C_GREEN "\n \t\t~ Patient Registered Successfully !!\n"C_RESET);



                FILE *fLog = fopen("patient_records.txt", "a");
                if (fLog != NULL) {
                    fprintf(fLog, "PATIENT - %d | Name: %s | Age: %d | Urgency: %d\n",
                            00000 + patientCount, patientNames[patientCount - 1],
                            patientAges[patientCount - 1], urgencyLevel[patientCount - 1]);
                    fclose(fLog);
                }

                break;


            case 2:
                printf(C_TITLE "\n\n- Print Patient Bill ---------------\n\n"C_RESET);
                if (patientCount == 0) {
                    printf(C_RED "\n \t\tNo patients registered yet!\n" C_RESET);
                    break;
                }

                int searchID;
                printf(C_PROMPT T_ITALIC "Enter Patient ID (maximum 100): " C_RESET);
                scanf("%d", &searchID);

                int index = searchID - 1;

                if (index < 0 || index >= patientCount) {
                    printf(C_RED "\n \t\tPatient ID not found!\n" C_RESET);
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

                printf(C_LBLUE "\n======================================================\n");
                printf("            SMART HOSPITAL ADMISSION & BILL           \n");
                printf("=======================================================\n" C_RESET);
                printf(C_ORANGE "Patient ID           : PATIENT - %d\n", searchID);
                printf("Patient Name         : %s\n", patientNames[index]);
                printf("Age                  : %s\n", ageStr);
                printf("Specialty            : %s\n", specNames[specIndex]);
                printf("Assigned Ward        : %s\n", wardStr);
                printf("Urgency Level        : %s\n", urgencyStr);
                printf("Base Consultation Fee: LKR %.2f\n", baseFee);
                printf("Emergency Surcharge  : LKR %.2f (%d%%)\n" , surcharge, surchargePct);

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
                    printf("Estimated Wait Time  : %.2f mins\n" C_RESET, waitTime);
                }
                printf(C_LBLUE "=======================================================\n" C_RESET );
                break;

          case 3:
                printf(C_TITLE "\n\n- Patient Priority List ---------------\n\n"C_RESET);

                if (patientCount == 0) {
                    printf(C_RED "\n \t\tNo patients registered yet!\n" C_RESET);
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

                    printf(C_ORANGE "Patient ID: PATIENT - %d | Name: %s \t| Urgency Level: %d\n" C_RESET,
                           1 + p, patientNames[p], urgencyLevel[p]);
                }

                break;



            case 4:

                printf(C_TITLE "\n\n- Analytics Reports ---------------\n\n"C_RESET);
                if (patientCount == 0) {
                    printf(C_RED "\t\t No patients!\n"C_RESET);
                    break;
                }

                int lvls[4] = {0}; // add new levles instead of header file array. It's Easy to handle

                float tRev = 0, tDisc = 0, maxB = 0; //tRev, tDisc, maxB meaning of this variables are total revenue, total discount, maximum bill I used shorter form cuz it's easy to find

                int maxIdx = 0;

                for (int i = 0; i < patientCount; i++) {
                    lvls[urgencyLevel[i]]++;

                    float baseFee = baseFees[specialtyID[i]-1];
                    float surcharge = (urgencyLevel[i] == 2) ? baseFee*0.2 : (urgencyLevel[i] == 3) ? baseFee*0.5 : 0; // use ternary form
                    float wardCost = (isAdmitted[i]) ? daysAdmitted[i] * wardRates[wardID[i]-1] : 0;
                    float discount = (patientAges[i] < 5 || patientAges[i] > 65) ? (baseFee+surcharge+wardCost)*0.15 : 0;
                    float finalbill = baseFee + surcharge + wardCost - discount;
                    tRev += finalbill;
                    tDisc += discount;

                    if (finalbill > maxB) { maxB = finalbill; maxIdx = i; }
                }

                printf(C_ORANGE "1. Patients: %d (Normal:%d, Urgent:%d, Critical:%d)\n", patientCount, lvls[1], lvls[2], lvls[3]);
                printf("2. Revenue: LKR %.2f | Discounts: LKR %.2f\n", tRev, tDisc);

                printf("3. Bed Occupancy:\n");


                for (int w = 0; w < 4; w++) {
                    int occupiedBeds = 0;
                    for (int b = 0; b < bedCapacities[w]; b++) {
                        if (bedOccupancy[w][b] == 1) {
                            occupiedBeds++;
                        }
                    }
                    float percentage = ((float)occupiedBeds / bedCapacities[w]) * 100;
                    printf("   - %s: %.1f%%\n", wardNames[w], percentage);
                }

                printf("4. Highest Bill: %s (LKR %.2f)\n" C_RESET, patientNames[maxIdx], maxB);

                break;

            case 5:

                FILE *fSave = fopen("beds_status.txt", "w");
                if (fSave != NULL) {
                    for (int w = 0; w < 4; w++) {
                        for (int b = 0; b < bedCapacities[w]; b++) {
                            fprintf(fSave, "%d ", bedOccupancy[w][b]);
                        }
                        fprintf(fSave, "\n");
                    }
                    fclose(fSave);
                }

                printf(T_ITALIC C_GREEN "\n \t\tData Saved. Shutting Down.......!\n"C_RESET);

                break;
            default:
                printf(C_RED "\n \t\tInvalid Choice #NUMBER! Please try again.\n"C_RESET);
        }
    } while(choice != 5);

    return 0;
}
