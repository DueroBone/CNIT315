// By: Duel Mood
// TA: Anthony Smith
// Lab time: 11:30am on Tuesdays

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

// Gets time taken since the last call to this function, and updates the prevTime to the current time
double getElapsedTime(struct timespec *prevTime)
{
    struct timespec currentTime;
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &currentTime);

    double elapsedTime = (currentTime.tv_sec - prevTime->tv_sec) +
                         (currentTime.tv_nsec - prevTime->tv_nsec) / 1e9;
    *prevTime = currentTime;
    return elapsedTime;
}

// https://www.geeksforgeeks.org/dsa/sorting-algorithms/

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// An optimized version of Bubble Sort
void bubbleSort(int arr[], int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped by inner loop,
        // then break
        if (swapped == false)
            break;
    }
}

void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {

        // Assume the current position holds
        // the minimum element
        int min_idx = i;

        // Iterate through the unsorted portion
        // to find the actual minimum
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
            {

                // Update min_idx if a smaller element is found
                min_idx = j;
            }
        }

        // Move minimum element to its
        // correct position
        swap(&arr[i], &arr[min_idx]);
    }
}

void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        int j = i - 1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int linearSearch(int arr[], int n, int x)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == x)
        {
            return i; // Return the index of the found element
        }
    }
    return -1; // Return -1 if the element is not found
}

// https://www.geeksforgeeks.org/dsa/binary-search/
int binarySearch(int arr[], int n, int x)
{
    int low = 0;
    int high = n - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        // Check if x is present at mid
        if (arr[mid] == x)
            return mid;

        // If x greater, ignore left half
        if (arr[mid] < x)
            low = mid + 1;

        // If x is smaller, ignore right half
        else
            high = mid - 1;
    }

    // If we reach here, then element was not present
    return -1;
}

// Takes in a sorting function and an array, and returns the time (s) taken to sort the array
double sortTime(void (*func)(int[], int), int arr[], int n)
{
    struct timespec startTime;

    getElapsedTime(&startTime); // Reset the timer
    func(arr, n);
    return getElapsedTime(&startTime);
}

// Takes in a searching function and an array, and returns the time (s) taken to search for an element in the array
double searchTime(int (*func)(int[], int, int), int arr[], int n, int x)
{
    struct timespec startTime;

    getElapsedTime(&startTime); // Reset the timer
    func(arr, n, x);
    return getElapsedTime(&startTime);
}

// Generates an array of n random integers, from 0 to int max value
int *generateRandomArray(int n)
{
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
    }

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand();
    }
    return arr;
}

void main()
{
    int lengths[] = {10, 50, 100, 500, 1000, 5000, 10000, 15000, 20000, 30000, 40000, 50000, 100000};
    int numLengths = 13;

    // Print CSV header
    printf("Size,Bubble Sort,Selection Sort,Insertion Sort,Linear Search,Binary Search");

    for (int i = 0; i < numLengths; i++)
    {
        // Generate a random array of the current length
        int *arr = generateRandomArray(lengths[i]);
        int *arrCopy = (int *)malloc(lengths[i] * sizeof(int));
        if (arrCopy == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
        }
        printf("\n%d", lengths[i]);

        // Sort the array using each sorting algorithm and measure the time taken
        memcpy(arrCopy, arr, lengths[i] * sizeof(int));
        printf(",%.9f", sortTime(bubbleSort, arrCopy, lengths[i]));

        memcpy(arrCopy, arr, lengths[i] * sizeof(int));
        printf(",%.9f", sortTime(selectionSort, arrCopy, lengths[i]));

        memcpy(arrCopy, arr, lengths[i] * sizeof(int));
        printf(",%.9f", sortTime(insertionSort, arrCopy, lengths[i]));

        // Search for an element in the sorted array and measure the time taken
        int x = arr[0]; // Search for the first element in the unsorted array
        printf(",%.9f", searchTime(linearSearch, arrCopy, lengths[i], x));
        printf(",%.9f", searchTime(binarySearch, arrCopy, lengths[i], x));

        free(arr);
        free(arrCopy);
    }
    printf("\n"); // Flush the stdout buffer
}