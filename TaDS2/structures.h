#ifndef OPERATIONS_H
#define OPERATIONS_H

#define LEN_NAME 20
#define LEN_STREET 30
#define MALLOC_STEP 10

struct Student
{
    char name[LEN_NAME];
    int sex; // 0-female 1-male
    int age;
    int average_grade;
    int admission_year;
    int house_type; // 0-home 1-hostel

    union
    {
        struct {
            char street[LEN_STREET];
            int house_num;
            int appartment_num;
        } home_adress;

        struct {
            int hostel_num;
            int room_num;
        } hostel;

    } adress;

};

int input_student(struct Student *stud);
void output_student_console(struct Student stud);
void output_student_file(FILE *f, struct Student *stud);

struct StudentTable
{
    struct Student *ptr_first;
    int size;
    int size_max;
};

int load_table(FILE *f, struct StudentTable *tbl);
int add_to_table(struct StudentTable *tbl, const struct Student *stud);
//int load_table(struct StudentTable *tbl, FILE *f);
int save_table(struct StudentTable *tbl, FILE *f);


#endif // OPERATIONS_H
