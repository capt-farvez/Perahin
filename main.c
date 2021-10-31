#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "perahin.h"

int search_batch(Data *data, char *name) {
    int i;
    for(i = 0; i <= data->len; i++) {
        if(strcasecmp(data->batches[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void add_student(Data *data)
{
    Student new;
    char batch_name[30];
    printf("Enter batch name: ");
    gets(batch_name);
    printf("Enter student ID: ");
    scanf("%d", &new.id);
    getchar();
    printf("Enter name: ");
    gets(&new.name);
    printf("Enter section (Two chacarters): ");
    gets(&new.section);
    printf("Enter blood group: ");
    gets(&new.bgroup);

    Marks marks = {0};
    new.marks = marks;

    int index = search_batch(data, batch_name);
    if(index == -1) {
        // New batch
        Batch batch;
        strcpy(batch.name, batch_name);
        batch.len = 1;
        batch.students[0] = new;
        data->batches[data->len] = batch;
        data->len++;
        printf("Added new student '%s' with student id '%d' into the new '%s' batch.\n", new.name, new.id, batch_name);
    } else {
        data->batches[index].students[data->batches[index].len] = new;
        data->batches[index].len++;
        data->len++;
        printf("Added new student '%s' with student id '%d' into the '%s' batch.\n", new.name, new.id, batch_name);
    }
}

void save(Data *data)
{
    FILE *file = fopen("data.txt", "w");
    int i;
    for(i = 0; i < data->len; i++)
    {
        fprintf(file, "%s,%d\n", data->batches[i].name, data->batches[i].len);
        int j;
        for(j = 0; j < data->batches[i].len; j++) {
            Student s = data->batches[i].students[j];
            fprintf(file, "%d,%s,%s,%s,%f,%f,%f,%f,%f,%f,%f,%f\n",
                    s.id, s.name, s.section, s.bgroup,
                    s.marks.cse103, s.marks.cse104, s.marks.cse105, s.marks.eee121, s.marks.eee122, s.marks.mth103, s.marks.chem111, s.marks.chem112);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        // perahin add
        if (strcmp(argv[1], "add") == 0)
        {
            Data data;
            data.len = 0;
            add_student(&data);
            save(&data);
        }
        else if (strcmp(argv[1], "edit") == 0)
        {
            // perahin edit <student id>
            printf("Not implemented yet!\n");
        }
        else if (strcmp(argv[1], "remove") == 0)
        {
            // perahin remove <student id>
            printf("Not implemented yet!\n");
        }
        else if (strcmp(argv[1], "view") == 0)
        {
            // perahin view <student id>
            printf("Not implemented yet!\n");
        }
        else if (strcmp(argv[1], "list") == 0)
        {
            // perahin list
            printf("Not implemented yet!\n");
        }
        else if (strcmp(argv[1], "marks") == 0)
        {
            // perahin marks add <student id>
            if (strcmp(argv[2], "add") == 0)
            {
                printf("Not implemented yet!\n");
            }
            else if (strcmp(argv[2], "edit") == 0)
            {
                // perahin marks edit <student id>
                printf("Not implemented yet!\n");
            }
            else
            {
                printf("Insufficient arguments were provided!\n");
            }
            printf("Not implemented yet!\n");
        }
        else
        {
            printf("Insufficient arguments were provided!\n");
        }
    }
    else
    {
        printf("Available commands:\n");
        printf("%-35s - Add new student in the database.\n", "perahin add");
        printf("%-35s - Remove a student from the database.\n", "perahin remove <student id>");
        printf("%-35s - View information about a student.\n", "perahin view <student id>");
        printf("%-35s - View all students information.\n", "perahin list");
        printf("%-35s - Add a student's marks.\n", "perahin marks add <student id>");
        printf("%-35s - Edit a student's marks.\n", "perahin marks edit <student id>");
    }
    return 0;
}
