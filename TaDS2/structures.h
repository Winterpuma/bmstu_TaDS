#ifndef OPERATIONS_H
#define OPERATIONS_H

#define LEN_NAME 20
#define LEN_STREET 30

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

int load_table();
int save_table();
int input_student(struct Student *stud);
void output_student(struct Student *stud);

#endif // OPERATIONS_H
