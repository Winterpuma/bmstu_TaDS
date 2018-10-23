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
void output_student_file(FILE *f, struct Student stud);


struct StudentTable
{
    struct Student *ptr_first;
    int size;
    int size_max;
};

int load_table(FILE *f, struct StudentTable *tbl);
int add_to_table(struct StudentTable *tbl, const struct Student *stud);
int save_table(FILE *f, struct StudentTable *tbl);
int remove_from_table(struct StudentTable *tbl, int i);
void clear_table(struct StudentTable *tbl);
void output_stTable_console(struct StudentTable *tbl);
int cmp_stud(const void *a, const void *b);
void sort_stud_table(struct StudentTable *tbl);


struct Key
{
        int key;
        int id;
};

struct KeyTable
{
        struct Key* ptr_first;
        int n;
};

int create_key_table(struct StudentTable* arr_stud, struct KeyTable* arr_keys);
void clear_key_table(struct KeyTable* arr_keys);
void sort_key_table(struct KeyTable* arr_keys);
void print_key_table(const struct KeyTable* arr_keys);
int print_stud_table_by_key(const struct StudentTable* arr_stud, const struct KeyTable* arr_keys);
int cmp_key(const void *key1, const void *key2);

#endif // OPERATIONS_H
