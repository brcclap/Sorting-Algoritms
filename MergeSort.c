#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100

int readFromFileToArray(const char *filename, int array[])
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    int num_elements = 0;
    while (fscanf(file, "%d", &array[num_elements]) != EOF && num_elements < MAX_SIZE)
    {
        num_elements++;
    }

    fclose(file);
    return num_elements;
}

void writeArrayToFile(const char *filename, int array[], int num_elements)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < num_elements; i++)
    {
        fprintf(file, "%d ", array[i]);
    }

    fclose(file);
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// l is for left index and r is right index of the sub-array of arr to be sorted
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for large l and r
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Merge the sorted halves
        merge(arr, l, m, r);
    }
}

// Function to print an array
void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int main()
{
    clock_t start_time, end_time;
    double cpu_time_used;
    int array[MAX_SIZE];
    int num_elements;
    start_time = clock();

    num_elements = readFromFileToArray("input.txt", array);
    if (num_elements == -1)
    {
        printf("Error reading from file\n");
        return 1;
    }

    mergeSort(array, 0, num_elements - 1);

    writeArrayToFile("output.txt", array, num_elements);

    printf("Elements copied from file to array and written to another file successfully.\n");

    end_time = clock();

    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("CPU time used: %f seconds\n", cpu_time_used);

    return 0;
}