#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> 
#include <string.h>
#include <ctype.h>
#include "nn.h"

/* --- SYSTEM CONFIGURATION --- */
#define CALC_SCALE 100.0
#define CALC_AMP 50.0
#define MED_MAX_TEMP 108.0
#define MED_MAX_HR 220.0
#define MED_MAX_O2 100.0
#define FIT_MAX_WEIGHT 150.0 
#define FIT_MAX_HEIGHT 250.0 
#define FIT_MAX_CALS 5000.0
#define SPAM_MAX_LINKS 5.0
#define SPAM_MAX_CAPS 100.0 
#define SPAM_MAX_KEYWORDS 3.0 

/* --- UTILITIES --- */

void clear_screen() {
    printf("\n\n\n\n\n"); 
}

void flush_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Check for persistent brain files
int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

// Visual loading indicator
void progress_bar(int current, int total, const char* label) {
    if (current % (total / 50) != 0) return; 
    float pct = (float)current / total;
    int width = 25;
    int filled = (int)(width * pct);
    printf("\r%s [", label);
    for (int i = 0; i < width; i++) {
        if (i < filled) printf("=");
        else printf(" ");
    }
    printf("] %.0f%%", pct * 100);
    fflush(stdout); 
}

/* =============================================================
   APP 1: NEURO-CALC
   Precision Difference Engine & Neural Adder
   ============================================================= */
void app_calculator() {
    NeuralNetwork* nn_diff = NULL;
    NeuralNetwork* nn_add = NULL;

    printf("\n[ NEURO-CALC: INITIALIZING SYSTEM ]\n");

    // Load or Train: Difference Engine
    if (file_exists("brain_calc_diff.dat")) {
        printf(">> Precision Brain found. Loading...\n");
        nn_diff = load_network("brain_calc_diff.dat");
    } else {
        nn_diff = create_network(3, 8, 1);
        for(int i=0; i<80000; i++) {
            progress_bar(i, 80000, "Training Precision");
            double inputs[3], target[1];
            int a = rand() % 101;
            int b;
            int strategy = rand() % 3;
            if (strategy == 0) { b = a; target[0] = 0.0; } 
            else if (strategy == 1) { b = (a + 1) % 101; target[0] = 1.0; } 
            else { b = rand() % 101; if (b == a) b = (b + 1) % 101; target[0] = 1.0; }

            inputs[0] = (double)a / CALC_SCALE;
            inputs[1] = (double)b / CALC_SCALE;
            inputs[2] = fabs(inputs[0] - inputs[1]) * CALC_AMP; 
            train(nn_diff, inputs, target, 0.1);
        }
        printf("\n>> Saving 'brain_calc_diff.dat'...\n");
        save_network(nn_diff, "brain_calc_diff.dat");
    }

    // Load or Train: Neural Adder
    if (file_exists("brain_calc_add.dat")) {
        printf(">> Adder Brain found. Loading...\n");
        nn_add = load_network("brain_calc_add.dat");
    } else {
        nn_add = create_network(2, 8, 1);
        for(int i=0; i<40000; i++) {
            progress_bar(i, 40000, "Training Adder    ");
            double inputs[2], target[1];
            double a = (double)(rand() % 11); 
            double b = (double)(rand() % 11); 
            double sum = a + b; 
            inputs[0] = a / 20.0; inputs[1] = b / 20.0; target[0] = sum / 20.0; 
            train(nn_add, inputs, target, 0.1);
        }
        printf("\n>> Saving 'brain_calc_add.dat'...\n");
        save_network(nn_add, "brain_calc_add.dat");
    }

    // Calc Interface
    while(1) {
        printf("\n--- NEURO-CALC MENU ---\n");
        printf("[1] Difference Checker (Precision AI)\n");
        printf("[2] Neural Adder (AI Approximation)\n");
        printf("[3] Standard Calculator (CPU Logic)\n");
        printf("[4] Return to OS\n");
        printf("Calc > ");
        
        int mode;
        if (scanf("%d", &mode) != 1) { flush_input(); continue; }
        
        if (mode == 4) {
            printf(">> Exiting Neuro-Calc. Calculations saved.\n");
            break;
        }
        
        if (mode == 1) {
            printf("\n-- DIFFERENCE CHECKER --\nType '-1' to go back.\n");
            while(1) {
                double in1, in2;
                printf("Input Pair > ");
                scanf("%lf", &in1);
                if (in1 == -1) break;
                scanf("%lf", &in2);
                double n1 = in1 / CALC_SCALE;
                double n2 = in2 / CALC_SCALE;
                double diff = fabs(n1 - n2) * CALC_AMP;
                double input[3] = {n1, n2, diff};
                double* res = predict(nn_diff, input);
                printf(">> Verdict: %s (Confidence: %.1f%%)\n", res[0] > 0.8 ? "DIFFERENT" : "SAME", res[0]*100);
            }
        }
        else if (mode == 2) {
            printf("\n-- NEURAL ADDER --\nType '-1' to go back.\n");
            int first_run = 1; 
            
            while(1) {
                double a, b;
                printf("Add > ");
                scanf("%lf", &a);
                if (a == -1) break;
                scanf("%lf", &b);
                double input[2] = {a/20.0, b/20.0};
                double* res = predict(nn_add, input);
                printf(">> AI Estimate: %.2f (Actual: %.0f)\n", res[0] * 20.0, a+b);
                
                if (first_run) {
                    printf("(Note: It approximates! It's learning logic, not math.)\n");
                    first_run = 0;
                }
            }
        }
        else if (mode == 3) {
            printf("\n-- STANDARD CALCULATOR --\nType '0 0 0' to go back.\n");
            while(1) {
                double a, b; char op;
                printf("Expr (e.g. 5 + 5) > ");
                scanf("%lf %c %lf", &a, &op, &b);
                if (a == 0 && b == 0) break; 
                double ans = 0;
                if (op == '+') ans = a + b;
                else if (op == '-') ans = a - b;
                else if (op == '*') ans = a * b;
                else if (op == '/') ans = (b!=0)? a/b : 0;
                printf(">> Result: %.2f\n", ans);
            }
        }
    }
    if(nn_diff) free(nn_diff);
    if(nn_add) free(nn_add);
}

// =============================================================
// APP 2: DOC-AI (v4.0 - Balanced Logic & Explainability)
// =============================================================
void app_doctor() {
    NeuralNetwork* nn = NULL;
    printf("\n[ LOADING DOC-AI (v4.0)... ]\n");
    
    if (file_exists("brain_doc_v4.dat")) {
        printf(">> Medical Brain found. Loading instantly...\n");
        nn = load_network("brain_doc_v4.dat");
    } else {
        printf(">> Training Balanced Medical Logic...\n");
        nn = create_network(3, 8, 1);
        
        for(int i=0; i<80000; i++) {
            progress_bar(i, 80000, "Studying Cases   ");
            double inputs[3], target[1];
            
            double temp, hr, o2;
            int condition = 0;

            
            if (i % 2 == 0) {
                // GENERATE HEALTHY PATIENT
                temp = 97.0 + ((double)rand() / RAND_MAX * 2.0); // 97-99 F
                hr   = 60.0 + ((double)rand() / RAND_MAX * 40.0); // 60-100 BPM
                o2   = 95.0 + ((double)rand() / RAND_MAX * 5.0);  // 95-100 %
                condition = 0; // Safe
            } else {
                // GENERATE RANDOM/SICK PATIENT
                temp = 95.0 + ((double)rand() / RAND_MAX * 12.0);
                hr   = 0.0 + ((double)rand() / RAND_MAX * 200.0);
                o2   = 70.0 + ((double)rand() / RAND_MAX * 30.0);
                
                // Classify the random patient
                if (hr < 30.0) condition = 2;       
                else if (o2 < 90.0) condition = 2;  
                else if (o2 < 95.0) condition = 1;
                else if (temp > 104.0 || temp < 95.0) condition = 2; 
                else if (temp > 100.4) condition = 1;
                else if (hr > 120.0 || hr < 50.0) condition = 1; 
                if (hr > 110.0 && temp > 101.0) condition = 2; 
                if (hr > 120.0 && temp < 97.0) condition = 2;
            }

            target[0] = (double)condition / 2.0;
            inputs[0] = temp / MED_MAX_TEMP; inputs[1] = hr / MED_MAX_HR; inputs[2] = o2 / MED_MAX_O2;
            train(nn, inputs, target, 0.1);
        }
        printf("\n>> Saving 'brain_doc_v4.dat'...\n");
        save_network(nn, "brain_doc_v4.dat");
    }

    printf("\n--- DOC-AI DIAGNOSTICS ---\n");
    int unit_choice = 0;
    printf("Select Temperature Unit:\n");
    printf("[1] Fahrenheit (F)\n");
    printf("[2] Celsius (C)\n");
    printf("Select > ");
    if (scanf("%d", &unit_choice) != 1) { flush_input(); return; }

    printf("\nINSTRUCTIONS: Enter Temp, Heart Rate, Oxygen %%.\n");
    
    double t_in, hr, o2;
    while(1) {
        printf("\nVitals > ");
        if (scanf("%lf", &t_in) != 1) { flush_input(); continue; }
        if (t_in == -1) break;
        scanf("%lf %lf", &hr, &o2);

        // --- SAFETY CHECKS & UNIT CONVERSION ---
        double temp_f = t_in;
        if (unit_choice == 2) { 
            if (t_in > 60.0) { printf("   [!] ALERT: Boiling Temp. Assuming F.\n"); temp_f = t_in; } 
            else { temp_f = (t_in * 9.0/5.0) + 32.0; printf("   (Converted %.1fC -> %.1fF)\n", t_in, temp_f); }
        } else {
            if (t_in < 50.0) { printf("   [!] ALERT: Frozen Temp. Assuming C.\n"); temp_f = (t_in * 9.0/5.0) + 32.0; printf("   (Auto-Corrected to %.1fF)\n", temp_f); }
        }
        
        if (o2 > 100.0) o2 = 100.0; // Clamp oxygen

        // --- AI PREDICTION ---
        double input[3] = {temp_f/MED_MAX_TEMP, hr/MED_MAX_HR, o2/MED_MAX_O2};
        double* res = predict(nn, input);
        double risk = res[0] * 100.0;

        printf("   AI Risk Analysis: %.1f%%\n", risk);

        // --- EXPLAINABILITY ENGINE (The "Why") ---
        int issues_found = 0;
        
        // 1. OXYGEN ANALYSIS
        if (o2 <= 0) { printf("   > [CRITICAL] No Oxygen detected.\n"); issues_found++; }
        else if (o2 < 90.0) { printf("   > [CRITICAL] Hypoxia (Low Oxygen).\n"); issues_found++; }
        else if (o2 < 95.0) { printf("   > [WARNING]  Oxygen is slightly low.\n"); issues_found++; }
        else printf("   > [  OK   ]  Oxygen levels normal.\n");

        // 2. HEART ANALYSIS
        if (hr <= 0) { printf("   > [CRITICAL] No Pulse.\n"); issues_found++; }
        else if (hr < 50.0) { printf("   > [WARNING]  Bradycardia (Low Heart Rate).\n"); issues_found++; }
        else if (hr > 120.0) { printf("   > [WARNING]  Tachycardia (High Heart Rate).\n"); issues_found++; }
        else printf("   > [  OK   ]  Heart Rate normal.\n");

        // 3. TEMP ANALYSIS
        if (temp_f > 103.0) { printf("   > [CRITICAL] Severe Fever.\n"); issues_found++; }
        else if (temp_f > 100.4) { printf("   > [WARNING]  Mild Fever.\n"); issues_found++; }
        else if (temp_f < 95.0) { printf("   > [CRITICAL] Hypothermia.\n"); issues_found++; }
        else printf("   > [  OK   ]  Temperature normal.\n");

        // --- FINAL VERDICT ---
        printf("   -----------------------------\n");
        printf("   >> STATUS: ");
        if (risk > 75.0 || issues_found >= 2) {
            printf("[!!!] CRITICAL CONDITION\n");
            printf("   >> ACTION: CALL EMERGENCY SERVICES.\n");
        }
        else if (risk > 35.0 || issues_found > 0) {
            printf("[ ! ] WARNING / ABNORMAL\n");
            printf("   >> ACTION: Monitor closely.\n");
        }
        else {
            printf("[ OK ] STABLE\n");
            printf("   >> ACTION: Patient is healthy.\n");
        }
    }
    if(nn) free(nn);
}

/* =============================================================
   APP 3: FIT-BOT (v2.1)
   Metabolic Analysis & TDEE Calculator
   ============================================================= */
void app_fitness_ai() {
    NeuralNetwork* nn = NULL;
    printf("\n[ LOADING FIT-BOT (v2.1)... ]\n");
    
    if (file_exists("brain_fit_v2.dat")) {
        printf(">> Fitness Brain found. Loading...\n");
        nn = load_network("brain_fit_v2.dat");
    } else {
        printf(">> Training Metabolic Logic...\n");
        nn = create_network(3, 8, 1);
        for(int i=0; i<80000; i++) {
            progress_bar(i, 80000, "Calibrating      ");
            double inputs[3], target[1];
            double weight = 40.0 + (rand() % 100);
            double height = 140.0 + (rand() % 70);
            double cals = 1200 + (rand() % 2800);
            
            double h_m = height / 100.0;
            double bmi = weight / (h_m * h_m);
            
            if (bmi < 18.5) target[0] = 0.0;      
            else if (bmi > 25.0) target[0] = 1.0; 
            else target[0] = 0.5;                 

            inputs[0] = weight / FIT_MAX_WEIGHT; 
            inputs[1] = height / FIT_MAX_HEIGHT; 
            inputs[2] = cals / FIT_MAX_CALS;
            train(nn, inputs, target, 0.1);
        }
        printf("\n>> Saving 'brain_fit_v2.dat'...\n");
        save_network(nn, "brain_fit_v2.dat");
    }

    printf("\n--- FIT-BOT PLANNER ---\n");
    printf("INSTRUCTIONS: Enter Weight(kg), Height(cm), Daily Calories.\n");
    printf("Example: 75 180 2200\n");
    printf("Type '-1' to exit.\n");
    
    double w, h, c;
    while(1) {
        printf("\nStats > ");
        if (scanf("%lf", &w) != 1) { flush_input(); continue; }
        
        if (w == -1) {
            printf(">> Exiting Fit-Bot. Keep moving!\n");
            break;
        }

        scanf("%lf %lf", &h, &c);

        if (h < 120.0) {
            printf("   [!] WARNING: %.0f cm is extremely short (Child/Dwarfism).\n", h);
        }
        if (w > 200.0) {
            printf("   [!] WARNING: %.0f kg is dangerously high.\n", w);
        }

        double h_m = h / 100.0;
        double bmi = w / (h_m * h_m);
        double ideal_w = 22.0 * (h_m * h_m);
        double weight_diff = w - ideal_w;
        double bmr = (10.0 * w) + (6.25 * h) - (5.0 * 25.0) + 5.0;
        double maintenance_cals = bmr * 1.2; 
        double calorie_diff = c - maintenance_cals;

        double input[3] = {w/FIT_MAX_WEIGHT, h/FIT_MAX_HEIGHT, c/FIT_MAX_CALS};
        double* res = predict(nn, input);
        double score = res[0];

        printf("--------------------------------------------------\n");
        printf(">> MEDICAL REPORT:\n");
        printf("   BMI:           %.1f ", bmi);
        
        if (bmi < 18.5) printf("(Underweight)\n");
        else if (bmi < 25.0) printf("(Healthy)\n");
        else if (bmi < 30.0) printf("(Overweight)\n");
        else printf("(Obese)\n");

        printf("   Ideal Weight:  %.1f kg ", ideal_w);
        if (weight_diff > 0) printf("(Lose %.1f kg)\n", weight_diff);
        else printf("(Gain %.1f kg)\n", fabs(weight_diff));

        printf("   Maintenance:   %.0f kcal/day\n", maintenance_cals);
        printf("   Your Intake:   %.0f kcal/day ", c);

        if (calorie_diff < -500) printf("(Starvation Zone [!])\n");
        else if (calorie_diff < 0) printf("(Deficit)\n");
        else if (calorie_diff > 500) printf("(Surplus [!])\n");
        else printf("(Maintenance)\n");

        printf("--------------------------------------------------\n");
        printf(">> AI VERDICT: ");

        if (score < 0.3) {
            printf("BULK NEEDED.\n");
            printf("   You are undereating by %.0f kcal.\n", fabs(calorie_diff));
            printf("   PLAN: Eat %.0f kcal (+500 surplus). Focus on Protein.\n", maintenance_cals + 500);
        } 
        else if (score > 0.7) {
            printf("CUT NEEDED.\n");
            printf("   You are overeating for your height.\n");
            printf("   PLAN: Target %.0f kcal (-500 deficit). 30min Cardio daily.\n", maintenance_cals - 500);
        } 
        else {
            printf("OPTIMAL HEALTH.\n");
            printf("   PLAN: Keep doing what you are doing!\n");
        }
    }
    if(nn) free(nn);
}

/* =============================================================
   APP 4: SPAM-GUARD
   Batch Context Processor with Weighted Risk Logic
   ============================================================= */
void app_spam_filter() {
    NeuralNetwork* nn = NULL;
    printf("\n[ LOADING SPAM-GUARD (BATCH PROCESSOR)... ]\n");
    
    if (file_exists("brain_spam_v2.dat")) {
        printf(">> Security Brain found. Loading...\n");
        nn = load_network("brain_spam_v2.dat");
    } else {
        printf(">> Training Logic Model...\n");
        nn = create_network(3, 8, 1);
        
        for(int i=0; i<80000; i++) {
            progress_bar(i, 80000, "Learning Nuance  ");
            double inputs[3], target[1];
            double links = rand() % 6;       
            double caps = rand() % 101;      
            double keywords = rand() % 6;    
            
            double risk_score = 0;
            risk_score += (links * 15.0);        
            risk_score += (keywords * 20.0);     
            if (caps > 50.0) risk_score += (caps * 0.5); 
            
            int is_spam = (risk_score > 50.0) ? 1 : 0;
            target[0] = (double)is_spam;
            inputs[0] = links/SPAM_MAX_LINKS; 
            inputs[1] = caps/SPAM_MAX_CAPS; 
            inputs[2] = keywords/SPAM_MAX_KEYWORDS;
            train(nn, inputs, target, 0.1);
        }
        printf("\n>> Saving 'brain_spam_v2.dat'...\n");
        save_network(nn, "brain_spam_v2.dat");
    }

    printf("\n--- FULL-TEXT EMAIL SCANNER ---\n");
    printf("INSTRUCTIONS:\n");
    printf("1. Paste the ENTIRE email below.\n");
    printf("2. Type 'END' on a new line to run the scan.\n");
    printf("3. Type 'QUIT' to exit.\n");
    flush_input(); 

    char full_email[10000] = ""; 
    char line_buffer[256];

    while(1) {
        strcpy(full_email, ""); 
        printf("\n[ PASTE EMAIL BELOW -> TYPE 'END' WHEN DONE ]\n");
        printf("--------------------------------------------------\n");

        while(1) {
            if (fgets(line_buffer, 256, stdin) == NULL) break;
            line_buffer[strcspn(line_buffer, "\n")] = 0;

            if (strcmp(line_buffer, "END") == 0) break; 
            if (strcmp(line_buffer, "QUIT") == 0) {
                if(nn) free(nn);
                printf(">> Exiting Spam-Guard. Stay secure.\n");
                return; 
            }

            if (strlen(full_email) + strlen(line_buffer) < 9999) {
                strcat(full_email, line_buffer);
                strcat(full_email, " "); 
            }
        }

        if (strlen(full_email) < 2) continue;

        printf("--------------------------------------------------\n");
        printf(">> SCANNING FULL CONTENT...\n");

        int len = strlen(full_email);
        int caps_count = 0;
        for(int i=0; i<len; i++) {
            if (isupper(full_email[i])) caps_count++;
            full_email[i] = toupper(full_email[i]); 
        }
        
        double caps = ((double)caps_count / len) * 100.0;
        double links = 0; 
        double keywords = 0;

        char *ptr = full_email;
        while ((ptr = strstr(ptr, "HTTP"))) { links++; ptr++; }
        ptr = full_email;
        while ((ptr = strstr(ptr, "WWW"))) { links++; ptr++; }
        ptr = full_email;
        while ((ptr = strstr(ptr, ".COM"))) { links++; ptr++; }

        if (strstr(full_email, "FREE")) keywords++;
        if (strstr(full_email, "WINNER")) keywords++;
        if (strstr(full_email, "CASH")) keywords++;
        if (strstr(full_email, "URGENT")) keywords++;
        if (strstr(full_email, "CLICK")) keywords++;
        if (strstr(full_email, "PRIORITY")) keywords++;
        if (strstr(full_email, "OFFER")) keywords++;
        if (strstr(full_email, "SELECTED")) keywords++;
        if (strstr(full_email, "CREDIT")) keywords++;
        if (strstr(full_email, "$")) keywords++;
        if (strstr(full_email, "RISK")) keywords++;
        if (strstr(full_email, "BANK")) keywords++;

        printf("   [Total Stats: %.0f Links, %.0f%% Caps, %.0f Keywords]\n", links, caps, keywords);

        double input[3] = {links/SPAM_MAX_LINKS, caps/SPAM_MAX_CAPS, keywords/SPAM_MAX_KEYWORDS};
        double* res = predict(nn, input);

        double probability = res[0] * 100.0;
        printf("   >> FINAL VERDICT: ");
        
        if (res[0] > 0.8) printf("[!!!] SPAM DETECTED (%.1f%%)\n", probability);
        else if (res[0] > 0.4) printf("[ ? ] SUSPICIOUS (%.1f%%)\n", probability);
        else printf("[ OK ] SAFE (%.1f%%)\n", probability);
    }
}

/* =============================================================
   APP 5: SYSTEM GUIDE (v2.0)
   Full Documentation
   ============================================================= */
void app_guide() {
    int page = 0;
    while(1) {
        clear_screen();
        printf("========================================\n");
        printf("      CORTEX SYSTEM MANUAL (v2.0)       \n");
        printf("========================================\n");
        printf("[1] Neuro-Calc Protocols\n");
        printf("[2] Doc-AI Triage Logic\n");
        printf("[3] Fit-Bot Metabolism Engine\n");
        printf("[4] Spam-Guard Batch Scanner\n");
        printf("[5] About Cortex Neural Net\n");
        printf("[6] Back to Main Menu\n");
        printf("----------------------------------------\n");
        printf("SELECT > ");
        
        if (scanf("%d", &page) != 1) { flush_input(); continue; }
        
        if (page == 6) {
            printf(">> Closing Guide. Returning to OS...\n");
            break;
        }
        
        printf("\n");
        if (page == 1) {
            printf("[ NEURO-CALC DOCUMENTATION ]\n");
            printf("----------------------------\n");
            printf("1. DIFFERENCE CHECKER: Uses 'Feature Amplification'.\n");
            printf("   It scales the gap between numbers to detect tiny\n");
            printf("   differences (e.g. 10 vs 11) that other AIs miss.\n\n");
            printf("2. NEURAL ADDER: Demonstrates 'Approximate Logic'.\n");
            printf("   It was never programmed to add. It LEARNED to add\n");
            printf("   by seeing thousands of examples. '2+2=3.99' is proof\n");
            printf("   of learning, not a bug.\n");
        }
        else if (page == 2) {
            printf("[ DOC-AI DOCUMENTATION ]\n");
            printf("------------------------\n");
            printf("PURPOSE: Rapid Triage for Emergency Rooms.\n\n");
            printf("SAFETY FEATURES:\n");
            printf("* Unit Auto-Detect: Prevents mixing Celsius/Fahrenheit.\n");
            printf("* Cardiac Override: Flags '0 BPM' as Cardiac Arrest.\n");
            printf("* Hypoxia Check: Flags '0%% Oxygen' as Respiratory Failure.\n");
            printf("\nNOTE: This AI prioritizes 'False Positives' (Safety)\n");
            printf("over 'False Negatives' (Missed Danger).\n");
        }
        else if (page == 3) {
            printf("[ FIT-BOT DOCUMENTATION ]\n");
            printf("-------------------------\n");
            printf("PURPOSE: Metabolic Analysis & Diet Planning.\n\n");
            printf("CORE FUNCTIONS:\n");
            printf("* TDEE Calc: Calculates 'Maintenance Calories' based on\n");
            printf("  your specific height/weight physics.\n");
            printf("* Sanity Check: Warns if input height/weight is medically\n");
            printf("  impossible (e.g. 20cm height).\n");
            printf("* Report Card: Gives a full breakdown, not just one word.\n");
        }
        else if (page == 4) {
            printf("[ SPAM-GUARD DOCUMENTATION ]\n");
            printf("----------------------------\n");
            printf("MODE: Batch Context Processor.\n\n");
            printf("HOW TO USE:\n");
            printf("1. Paste the WHOLE email (Subject + Body).\n");
            printf("2. Type 'END' on a new line to trigger the scan.\n\n");
            printf("THE LOGIC:\n");
            printf("It uses a 'Weighted Risk System'. Caps Lock alone is safe.\n");
            printf("Links alone are safe. But Caps + Links + 'Money' keywords\n");
            printf("trigger the Neural Alarm.\n");
        }
        else if (page == 5) {
            printf("[ SYSTEM ARCHITECTURE ]\n");
            printf("-----------------------\n");
            printf("KERNEL:   Cortex Neural Engine (nn.c)\n");
            printf("LAYERS:   Input -> Hidden (8 Neurons) -> Output\n");
            printf("LEARNING: Backpropagation (Gradient Descent)\n");
            printf("MEMORY:   Persistent .dat storage (Instant-Load)\n\n");
            printf("Use this OS responsibly. AI is a tool, not a replacement\n");
            printf("for professional advice.\n");
        }

        printf("\n----------------------------------------\n");
        printf("Press Enter to return...");
        flush_input(); getchar();
    }
}

/* =============================================================
   MAIN HUB: CORTEX OS KERNEL
   ============================================================= */
int main() {
    srand(time(NULL));
    int choice;
    while(1) {
        clear_screen();
        printf("========================================\n");
        printf("      CORTEX NEURAL OS (v8.0)           \n");
        printf("========================================\n");
        printf("[1] Neuro-Calc  (Math & Neural Adder)\n");
        printf("[2] Doc-AI      (Medical Triage)\n");
        printf("[3] Fit-Bot     (Diet & Workout)\n");
        printf("[4] Spam-Guard  (Auto-Text Scanner)\n");
        printf("[5] Guide       (User Manual)\n");
        printf("[6] Shut Down\n");
        printf("----------------------------------------\n");
        printf("SELECT > ");
        
        if (scanf("%d", &choice) != 1) { flush_input(); continue; }

        if (choice == 1) app_calculator();
        else if (choice == 2) app_doctor();
        else if (choice == 3) app_fitness_ai();
        else if (choice == 4) app_spam_filter();
        else if (choice == 5) app_guide();
        else if (choice == 6) {
            printf("\n[ SYSTEM SHUTDOWN ]\n");
            printf("Thank you for using Cortex OS. Goodbye.\n");
            break;
        }
    }
    return 0;
}