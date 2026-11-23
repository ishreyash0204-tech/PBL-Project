#include <stdio.h>
#include <math.h>

#define TARGET_PERCENTAGE 75.0

void analyzeSubject(char subjectName[], int total, int attended) {
    float currentPct = ((float)attended / total) * 100.0;
    float target = TARGET_PERCENTAGE / 100.0;

    printf("\n--------------------------------------------------\n");
    printf("Subject    : %s\n", subjectName);
    printf("Attendance : %d / %d (%.2f%%)\n",
           attended, total, currentPct);

    if (currentPct >= TARGET_PERCENTAGE) {
        int bunkable = (int)floor(
            (attended - (target * total)) / target
        );

        printf("Status     : SAFE (Eligible for exams)\n");

        if (bunkable > 0) {
            printf("Advice     : You can miss %d upcoming class(es).\n",
                   bunkable);
        } else {
            printf("Advice     : On the border! Do not miss the next class.\n");
        }
    }
    else {
        int needed = (int)ceil(
            ((target * total) - attended) / (1.0 - target)
        );

        printf("Status     : SHORTAGE (Below %.0f%%)\n",
               TARGET_PERCENTAGE);

        printf("Advice     : You must attend the next %d class(es) "
               "in a row to reach %.0f%%.\n",
               needed, TARGET_PERCENTAGE);
    }

    printf("--------------------------------------------------\n");
}

int main() {
    int numSubjects;
    int grandTotal = 0;
    int grandAttended = 0;

    printf("=== MY ATTENDANCE CHECKER ===\n");
    printf("Target Requirement: %.0f%%\n\n", TARGET_PERCENTAGE);

    printf("How many subjects do you want to check? ");
    if (scanf("%d", &numSubjects) != 1 || numSubjects <= 0) {
        printf("Invalid number of subjects!\n");
        return 1;
    }

    for (int i = 0; i < numSubjects; i++) {
        char subjectName[100];
        int total, attended;

        printf("\n--- Subject %d ---\n", i + 1);

        printf("Subject Name: ");
        scanf(" %99[^\n]", subjectName);

        printf("Total Classes Conducted: ");
        if (scanf("%d", &total) != 1) {
            printf("Invalid input! Restart the program.\n");
            return 1;
        }

        printf("Classes You Attended: ");
        if (scanf("%d", &attended) != 1) {
            printf("Invalid input! Restart the program.\n");
            return 1;
        }

        if (total <= 0 || attended < 0 || attended > total) {
            printf("Invalid numbers entered! Please try again.\n");
            i--;
            continue;
        }

        grandTotal += total;
        grandAttended += attended;

        analyzeSubject(subjectName, total, attended);
    }

    // Overall Semester Summary
    if (grandTotal > 0) {
        float overallPct =
            ((float)grandAttended / grandTotal) * 100.0;

        printf("\n==================================================\n");
        printf("OVERALL ATTENDANCE : %d / %d (%.2f%%)\n",
               grandAttended, grandTotal, overallPct);

        printf("OVERALL STATUS     : %s\n",
               (overallPct >= TARGET_PERCENTAGE)
               ? "SAFE"
               : "SHORTAGE");

        printf("==================================================\n");
    }

    return 0;
}