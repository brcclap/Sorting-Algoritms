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

int getMax(int arr[], int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

void countSort(int arr[], int n, int exp)
{
    int output[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(int arr[], int n)
{
    int max = getMax(arr, n);

    for (int exp = 1; max / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
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
    radixSort(array, num_elements);
    writeArrayToFile("output.txt", array, num_elements);

    printf("Elements copied from file to array and written to another file successfully.\n");

    end_time = clock();

    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("CPU time used: %f seconds\n", cpu_time_used);

    return 0;
}