#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generateRandomNumber()
{
    // elemente de la 0-4999
    return rand() % 5000;
}

int *createRandomList(int size)
{
    int *list = (int *)malloc(size * sizeof(int));
    if (list == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < size; i++)
    {
        list[i] = generateRandomNumber();
    }
    return list;
}

void printList(int *list, int size)
{
    printf("Generated List: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", list[i]);
    }
    printf("\n");
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

int main()
{
    srand(time(NULL));

    // nr elemente
    int size = 100000;

    int *randomList = createRandomList(size);

    writeArrayToFile("input.txt", randomList, size);

    free(randomList);

    return 0;
}