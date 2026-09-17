#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

const char *wardNames[] = {"General Ward", "Paediatric Ward", "Surgical Ward", "ICU"};
const int bedCapacities[] = {20, 10, 10, 5};
const float baseFees[] = {1500.0, 2500.0, 4500.0, 5000.0};
const int consultationTimes[] = {15, 20, 30, 30};
const float wardRates[] = {3000.0, 6000.0, 12000.0, 25000.0};

#endif