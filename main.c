#include <stdio.h>
#include <string.h>

typedef struct {
    float cse103;
    float cse104;
    float cse105;
    float eee121;
    float eee122;
    float mth103;
    float chem111;
    float chem112;
} Marks;

typedef struct {
    int id;
    char name[80];
    char section[2];
    char bgroup[3];
    float cgpa;
    Marks marks;
} Student;

void add_student() {
    Student new;
    printf("Enter student ID: ");
    scanf("%d", &new.id);
    getchar();
    printf("Enter name: ");
    gets(&new.name);
    printf("Enter section (Two chacarters): ");
    gets(&new.section);
    printf("Enter blood group: ");
    gets(&new.bgroup);
}




int main(int argc, char *argv[]) {
    if(argc > 1) {
    // perahin add
    if(strcmp(argv[1], "add") == 0) {
        add_student();
    } else if(strcmp(argv[1], "edit") == 0) {
        // perahin edit <student id>
        printf("Not implemented yet!\n");
    } else if(strcmp(argv[1], "view") == 0) {
        // perahin view <student id>
        printf("Not implemented yet!\n");
    } else if(strcmp(argv[1], "list") == 0) {
        // perahin list
        printf("Not implemented yet!\n");
    } else if(strcmp(argv[1], "marks") == 0) {
        // perahin marks add <student id>
        if(strcmp(argv[2], "add") == 0) {
            printf("Not implemented yet!\n");
        } else if(strcmp(argv[2], "edit") == 0) {
        // perahin marks edit <student id>
        printf("Not implemented yet!\n");
        } else {
            printf("Insufficient arguments were provided!\n");
        }
        printf("Not implemented yet!\n");
    } else {
        printf("Available commands:\n");
        printf("%-30s - Add new student in the database.\n", "perahin add");
        printf("%-30s - View information about a student.\n", "perahin view <student id>");
    }
    } else {
        printf("Available commands:\n");
        printf("%-30s - Add new student in the database.\n", "perahin add");
        printf("%-30s - View information about a student.\n", "perahin view <student id>");
        printf("%-30s - View all students information.\n", "perahin list");
        printf("%-30s - Add a student's marks.\n", "perahin marks add <student id>");
        printf("%-30s - Edit a student's marks.\n", "perahin marks edit <student id> ");
        
    }
    return 0;
}