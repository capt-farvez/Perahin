#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "perahin.h"

int search_batch(Data *data, char *name) {
    int i;
    for(i = 0; i < data->len; i++) {
        if(strcasecmp(data->batches[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int search_student(Data *data, int batch, int id) {
    int i;
    for(i = 0; i < data->batches[batch].len; i++) {
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
    printf("  Student ID |          Student Name          | Section | CGPA |\n");
    int i;
    for(i = 0; i < data->len; i++) {
        Batch batch = data->batches[i];
        printf("%-13s|                                |         |      |\n", batch.name);

        int j;
        for(j = 0; j < batch.len; j++) {
            Student student = batch.students[j];
            printf("%12d | %-30s |%5s    | %.2f |\n", student.id, student.name, student.section, cgpa_count(student.marks));
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
        printf("Sorry, there is no student associated with id '%d' is present in the '%s' batch.\n", id, batch_name);
        return;
    }

    int i;
    Student student = data->batches[batch].students[student_index];
    for(i = student_index; i < data->batches[batch].len - 1; i++) {
        data->batches[batch].students[i] = data->batches[batch].students[i + 1];
    }

    data->batches[batch].len--;
    if(data->batches[batch].len == 0) {
        // Whole batch is empty now; so remove the batch itself.
        for(i = batch; i < data->len - 1; i++) {
            data->batches[i] = data->batches[i + 1];
        }
        data->len--;
    }

    printf("Student '%s' associated with id '%d' has been removed from the batch '%s'\n", student.name, student.id, batch_name);
}

void view_student(Data *data, char *batch_name, int id){
    int batch= search_batch(data , batch_name);
    if(batch== -1){
        printf("Sorry, there is no batch named '%s' is present.\n", batch_name);
        return;
    }
    int student_index= search_student(data, batch, id);
    if(student_index == -1){
        printf("Sorry, there is no student associated with id '%d' is present in the '%s' batch.\n", id, batch_name);
        return;
    }
    Student s = data->batches[batch].students[student_index];
    printf("%-12s: %d\n", "ID", s.id);
    printf("%-12s: %s\n", "Name", s.name);
    printf("%-12s: %s\n", "Section", s.section);
    printf("%-12s: %s\n", "Blood Group", s.bgroup);

    return;
}

void get_marks(Marks *marks, char *name) {
    printf("==============================================================\n");
    printf("॥                    Marks Assignation                       ॥\n");
    printf("==============================================================\n");
    printf("\nCurrently no marks are assigned for '%s'\n", name);
    printf("Please input the marks\n");
    printf("Marks for CSE 103 : ");
    scanf("%f", &marks->cse103);
    printf("Marks for CSE 104 : ");
    scanf("%f", &marks->cse104);
    printf("Marks for CSE 105 : ");
    scanf("%f", &marks->cse105);
    printf("Marks for EEE 121 : ");
    scanf("%f", &marks->eee121);
    printf("Marks for EEE 122 : ");
    scanf("%f", &marks->eee122);
    printf("Marks for Math 103 : ");
    scanf("%f", &marks->mth103);
    printf("Marks for CHEM 111 : ");
    scanf("%f", &marks->chem111);
    printf("Marks for CHEM 112 : ");
    scanf("%f", &marks->chem112);
    printf("The marks were assigned succesfully!\n");
}

void edit_marks_selectively(Marks *marks) {
    printf("==============================================================\n");
    printf("॥                      Marks Updation                        ॥\n");
    printf("==============================================================\n");
    int selection;
    do {
        printf("\nPlease select which course you want to edit:\n");
        printf("\t1. CSE 103\n\t2. CSE 104\n\t3. CSE 105\n\t4. EEE 121\n\t5. EEE 122\n\t6. Math 103\n\t7. CHEM 111\n\t8. CHEM 112\n\t9. Quit\n");
        printf("Selection: ");
        scanf("%d", &selection);
        switch(selection) {
        case 1:
            printf("Marks for CSE 103 : ");
            scanf("%f", &marks->cse103);
            break;
        case 2:
            printf("Marks for CSE 104 : ");
            scanf("%f", &marks->cse104);
            break;
        case 3:
            printf("Marks for CSE 105 : ");
            scanf("%f", &marks->cse105);
            break;
        case 4:
            printf("Marks for EEE 121 : ");
            scanf("%f", &marks->eee121);
            break;
        case 5:
            printf("Marks for EEE 122 : ");
            scanf("%f", &marks->eee122);
            break;
        case 6:
            printf("Marks for Math 103 : ");
            scanf("%f", &marks->mth103);
            break;
        case 7:
            printf("Marks for CHEM 111 : ");
            scanf("%f", &marks->chem111);
            break;
        case 8:
            printf("Marks for CHEM 112 : ");
            scanf("%f", &marks->chem112);
            break;
        }
    } while(selection != 9);
    printf("The mark updation was succesful!\n");
}

void add_edit_marks(Data *data, char *batch_name, int id) {
    int batch = search_batch(data, batch_name);
    if(batch == -1) {
        printf("Sorry, there is no batch named '%s' is present.\n", batch_name);
        return;
    }
    int student_index = search_student(data, batch, id);
    if(student_index == -1) {
        printf("Sorry, there is no student associated with id '%d' is present in the '%s' batch.\n", id, batch_name);
        return;
    }

    Marks marks = data->batches[batch].students[student_index].marks;
    if(marks.cse103 == 0 && marks.cse104 == 0 && marks.cse105 == 0 && marks.eee121 == 0 && marks.eee122 == 0 && marks.mth103 == 0 && marks.chem111 == 0 && marks.chem112 == 0) {
        get_marks(&marks, data->batches[batch].students[student_index].name);
    } else {
        edit_marks_selectively(&marks);
    }
    data->batches[batch].students[student_index].marks = marks;
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
                remove_student(&data, argv[2], atoi(argv[3]));
                save_data(&data);
            } else {
                printf("Insufficient arguments were provided!\nPlease invoke this command following way:\n\tperahin remove <batch> <student id>\n");
            }
        }
        else if (strcmp(argv[1], "view") == 0)
        {
            // perahin view <batch> <student id>
            if(argc == 4) {
                view_student(&data, argv[2], atoi(argv[3]));

            } else {
                printf("Insufficient arguments were provided!\nPlease invoke this command following way:\n\tperahin view <batch> <student id>\n");
            }
        }
        else if (strcmp(argv[1], "list") == 0)
        {
            // perahin list
            show_global_student_list(&data);
        }
        else if (strcmp(argv[1], "marks") == 0)
        {
            // perahin marks <batch> <student id>
            if(argc == 4) {
                add_edit_marks(&data, argv[2], atoi(argv[3]));
                save_data(&data);
            } else {
                printf("Insufficient arguments were provided!\nPlease invoke this command following way:\n\tperahin marks <batch> <student id>\n");
            }
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
        printf("%-35s - Remove a student from the database.\n", "perahin remove <batch> <student id>");
        printf("%-35s - View information about a student.\n", "perahin view <student id>");
        printf("%-35s - View all students information.\n", "perahin list");
        printf("%-35s - Add a student's marks.\n", "perahin marks add <student id>");
        printf("%-35s - Edit a student's marks.\n", "perahin marks edit <student id>");
    }
    return 0;
}
