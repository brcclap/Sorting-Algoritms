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

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
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
    quickSort(array, 0, num_elements - 1);
    writeArrayToFile("output.txt", array, num_elements);

    printf("Elements copied from file to array and written to another file successfully.\n");

    end_time = clock();

    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("CPU time used: %f seconds\n", cpu_time_used);

    return 0;
}