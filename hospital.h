#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

#define C_RED     "\033[0;31m"
#define C_GREEN   "\033[0;32m"
#define C_LGREEN  "\033[1;32m"
#define C_YELLOW  "\033[0;33m"
#define C_LYELLOW "\033[93m"
#define C_LBLUE   "\033[1;36m"
#define C_ORANGE  "\033[38;5;208m"
#define C_RESET   "\033[0m"

#define C_TITLE  "\033[1;34m"  
#define C_MENU   "\033[1;37m"  
#define C_PROMPT "\033[1;35m"

#define T_BOLD      "\033[1m"
#define T_ITALIC    "\033[3m"
#define T_UNDERLINE "\033[4m"

const char *wardNames[] = {"General Ward", "Paediatric Ward", "Surgical Ward", "ICU"};
const int bedCapacities[] = {20, 10, 10, 5};
const float baseFees[] = {1500.0, 2500.0, 4500.0, 5000.0};
const int consultationTimes[] = {15, 20, 30, 30};
const float wardRates[] = {3000.0, 6000.0, 12000.0, 25000.0};

#endif

