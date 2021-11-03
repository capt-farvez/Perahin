#include <stdio.h>
#include <stdlib.h>
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

int search_student(Data *data, int batch, int id) {
    int i;
    for(i = 0; i <= data->batches[batch].len; i++) {
        if(data->batches[batch].students[i].id == id) {
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
        printf("Added new student '%s' with student id '%d' into the '%s' batch.\n", new.name, new.id, batch_name);
    }
}

void save_data(Data *data)
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

void retrieve_data(Data *data)
{
    FILE *file = fopen("data.txt", "r");
    if(!file) {
        data->len = 0;
        return;
    }

    data->len = 0;
    char batch_info[80];
    int batch_count = 0;

    while(fgets(batch_info, sizeof batch_info, file)) {
        Batch batch;
        char *b_name = strtok(batch_info, ",");
        char *b_total = strtok(NULL, ",");
        strcpy(batch.name, b_name);
        batch.len = atoi(b_total);

        int j;
        char student_line[1024];
        for(j = 0; j < batch.len; j++) {
            Student student;
            Marks marks;

            fgets(student_line, sizeof student_line, file);
            int segment = 1;
            char *temp = strtok(student_line, ",");
            do {
                switch(segment) {
                    case 1: // Student ID
                        student.id = atoi(temp);
                        break;
                    case 2: // Name
                        strcpy(student.name, temp);
                        break;
                    case 3: // Section
                        strcpy(student.section, temp);
                        break;
                    case 4: // Blood Group
                        strcpy(student.bgroup, temp);
                        break;
                    case 5:
                        marks.cse103 = atof(temp);
                        break;
                    case 6:
                        marks.cse104 = atof(temp);
                        break;
                    case 7:
                        marks.cse105 = atof(temp);
                        break;
                    case 8:
                        marks.eee121 = atof(temp);
                        break;
                    case 9:
                        marks.eee122 = atof(temp);
                        break;
                    case 10:
                        marks.mth103 = atof(temp);
                        break;
                    case 11:
                        marks.chem111 = atof(temp);
                        break;
                    case 12:
                        marks.chem112 = atof(temp);
                        break;
                }
                segment++;
                temp = strtok(NULL, ",");
            } while(segment != 13);

            student.marks = marks;
            batch.students[j] = student;
        }
        data->batches[batch_count++] = batch;
    }
    data->len = batch_count;
}

void show_global_student_list(Data *data)
{
    printf("  Student ID |          Student Name          | Section | Blood Group |\n");
    int i;
    for(i = 0; i < data->len; i++) {
        Batch batch = data->batches[i];
        printf("%-13s|                                |         |             |\n", batch.name);

        int j;
        for(j = 0; j < batch.len; j++) {
            Student student = batch.students[j];
            printf("%12d | %-30s |%5s    |%9s    |\n", student.id, student.name, student.section, student.bgroup);
        }
    }
}

void remove_student(Data *data, char *batch_name, int id) {
    int batch = search_batch(data, batch_name);
    if(batch == -1) {
        printf("Sorry, there is no batch named '%s' is present.\n", batch_name);
        return;
    }
    int student_index = search_student(data, batch, id);
    if(student_index == -1) {
        printf("Sorry, there is no student associated with id '%s' is present in the '%s' batch.\n", id, batch_name);
        return;
    }
}

int main(int argc, char *argv[])
{
    Data data;
    retrieve_data(&data);

    if (argc > 1)
    {
        // perahin add
        if (strcmp(argv[1], "add") == 0)
        {
            add_student(&data);
            save_data(&data);
        }
        else if (strcmp(argv[1], "edit") == 0)
        {
            // perahin edit <student id>
            printf("Not implemented yet!\n");
        }
        else if (strcmp(argv[1], "remove") == 0)
        {
            // perahin remove <batch> <student id>
            if(argc == 4) {
                //
            } else {
                printf("Insufficient arguments were provided!\nPlease invoke this command following way:\n\tperahin remove <batch> <student id>\n");
            }
        }
        else if (strcmp(argv[1], "view") == 0)
        {
            // perahin view <batch> <student id>
            printf("Not implemented yet!\n");
        }
        else if (strcmp(argv[1], "list") == 0)
        {
            // perahin list
            show_global_student_list(&data);
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
