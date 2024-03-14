#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100001

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

void bubbleSort(int arr[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    clock_t start_time, end_time;
    double cpu_time_used;
    int *array = (int *)malloc(MAX_SIZE * sizeof(int));
    int num_elements;
    start_time = clock();

    num_elements = readFromFileToArray("input.txt", array);
    if (num_elements == -1)
    {
        printf("Error reading from file\n");
        return 1;
    }
    bubbleSort(array, num_elements);
    writeArrayToFile("output.txt", array, num_elements);

    printf("Elements copied from file to array and written to another file successfully.\n");

    end_time = clock();

    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("CPU time used: %f seconds\n", cpu_time_used);

    return 0;
}