#ifndef PERAHIN_H_INCLUDED
#define PERAHIN_H_INCLUDED

typedef struct
{
    float cse103;
    float cse104;
    float cse105;
    float eee121;
    float eee122;
    float mth103;
    float chem111;
    float chem112;
} Marks;

typedef struct
{
    int id;
    char name[80];
    char section[3];
    char bgroup[4];
    float cgpa;
    Marks marks;
} Student;

typedef struct
{
    char name[30];
    Student students[255];
    int len;
} Batch;

typedef struct
{
    Batch batches[100];
    int len;
} Data;

float cgpa_count(Marks marks);

#endif // PERAHIN_H_INCLUDED
