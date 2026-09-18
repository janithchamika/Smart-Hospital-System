# Smart Hospital & Resource Allocation System

This is a simple C programming project created for the CSC 1012 assignment. It simulates a hospital's patient registration, bed allocation, and billing system.

## Features
* **Patient Registration:** Adds patients to the system and allocates beds based on availability.
* **Billing System:** Calculates the final bill including base fees, emergency surcharges, ward costs, and age discounts.
* **Priority Sorting:** Sorts registered patients based on their urgency level (Critical > Urgent > Normal).
* **Analytics:** Shows total revenue, bed occupancy percentages, and the highest paying patient.
* **File Handling:** Saves bed statuses and patient records to text files automatically.

## Project Files
* `main.c` - Contains the main menu and all the functional logic.
* `hospital.h` - Contains global arrays, constants, and UI color codes.

## How to Run
1. Open your terminal or command prompt.
2. Compile the program using gcc:
   `gcc main.c -o hospital`
3. Run the compiled file:
   `./hospital` (Linux/Mac) or `hospital.exe` (Windows)