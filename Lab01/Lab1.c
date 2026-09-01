// By: Duel Mood
// TA: Anthony Smith
// Lab time: 11:30am on Tuesdays


#include <stdio.h>

int main()
{
    int numType1, numType2;

    const int priceType1 = 20;
    const int priceType2 = 35;
    const int volumeType1 = 1 * 1 * 1;
    const int volumeType2 = 1 * 2 * 2;

    const int shippingContainerVolume = 40 * 8 * 8;
    printf("The shipping container has a volume of %d cubic feet.\n", shippingContainerVolume);

    // Ask user for number of Type 1 boxes
    printf("Enter the number of Type 1 boxes: ");
    scanf("%d", &numType1);

    // Calculate how many Type 2 boxes could fit in the remaining space
    int volumeAfterType1 = shippingContainerVolume - (numType1 * volumeType1);
    int numCouldFitType2 = volumeAfterType1 / volumeType2;
    printf("You could fit %d more type two boxes.\n", numCouldFitType2);

    // Ask user for number of Type 2 boxes
    printf("Enter the number of Type 2 boxes: ");
    scanf("%d", &numType2);

    // Calculate total volume used and remaining volume
    int totalVolumeUsed = (numType1 * volumeType1) + (numType2 * volumeType2);
    int totalVolumeRemaining = shippingContainerVolume - totalVolumeUsed;
    printf("There is %d remaining cubic feet in the container.\n\n", totalVolumeRemaining);

    if (totalVolumeRemaining < 0)
    {
        printf("The container is overfilled by %d cubic feet.\nPlease try again.", -totalVolumeRemaining);
        return 1;
    }

    // Calculate the shipping cost
    int shippingCost = (numType1 * priceType1) + (numType2 * priceType2);
    printf("Subtotal shipping cost of $%d\n", shippingCost);

    int freeSpaceDiscount = 2 * totalVolumeRemaining;
    printf("Discount of $%d\n", freeSpaceDiscount);

    int finalCost = shippingCost - freeSpaceDiscount;
    printf("Final shipping cost of $%d\n\n", finalCost);

    printf("Program has ended...");
    return 0;
}