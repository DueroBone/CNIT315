// By: Duel Mood
// TA: Anthony Smith
// Lab time: 11:30am on Tuesdays

#include <stdio.h>

// Define constants
#define PI 3.14159f
#define PIVOT_TIP_SPEET 15.0f
#define FARM_WIDTH 2640.0f
#define true 1

int main() {
    int numIterations = 0; // To count number of runs of the program
    while (true) {
        // Ask if the user wants to continue first
        printf("Do you want to continue? (y/n): ");
        char choice;
        scanf(" %c", &choice);
        if (choice == 'n' || choice == 'N') {
            break;
        }
        numIterations++;

        // Initialize variables
        float pivotDiameter, farmFeet, wateredFeet, gallonsUsed, pivotRadius, timeTaken;
        float farmX, farmY = FARM_WIDTH;
        farmFeet = farmX * farmY;

        // Get the pivot diameter and verify it
        while (true) {
            printf("Enter the diameter of the pivot: ");
            scanf(" %f", &pivotDiameter);
            if (pivotDiameter <= 1000.0f || pivotDiameter > 2640.0f) {
                printf("Invalid input. Please try again\n");
            } else {
                break; // Correct input, continue on
            }
        }

        // Calculate
        pivotRadius = pivotDiameter / 2.0f;
        wateredFeet = PI * pivotRadius * pivotRadius;
        gallonsUsed = wateredFeet * 0.14f;
        timeTaken = 2 * PI * pivotRadius / PIVOT_TIP_SPEET;

        // Output the results
        printf("A total of %.2f square feet of the farm will be watered.\n", wateredFeet);
        printf("A total of %.2f gallons of water will be used.\n", gallonsUsed);
        printf("It will take %.2f hours to complete the circle.\n\n", timeTaken);
    }

    printf("You have completed %d iterations.\n", numIterations);
    printf("Program has ended...");

    return 0;
}