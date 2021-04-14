//*********************
// Exercise  2
//
// Name: Matanel Pataki
//
// ID: 205951023
//*********************

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define BEST_TASK "best"
#define BUBBLE_TASK "bubble"
#define QUICK_TASK "quick"
#define BUFFER_SIZE 60

//Messages:
#define GET_STUDENTS_NUM_MSG "Enter number of students. Then enter\n"
#define GET_STUDENT_INFO_MSG "Enter student info. Then enter\n"
#define BAD_ID_ERR_MSG "ERROR: Id must have 10 digits and can not start with 0.\n"
#define BAD_GRADE_ERR_MSG "ERROR: Grade should be an integer between 0 and 100 (includes).\n"
#define BAD_AGE_ERR_MSG "ERROR: Age should be an integer between 18 and 120 (includes).\n"
#define BEST_STUDENT_IS_MSG "best student info is %ld,%d,%d\n"
typedef struct Student {
  int age, grade;
  long int id;
} Student;

void best_student (Student *start, Student *end)
{
  Student *best_student_p = start;
  while (start != end)
    {
      start++;
      if (((start->grade) / (start->age)) > ((best_student_p->grade) / (best_student_p->age)))
        {
          best_student_p = start;
        }
    }
  printf (BEST_STUDENT_IS_MSG, best_student_p->id, best_student_p->grade, best_student_p->age);
}

int get_digits_num (long id)
{
  int r = 1;
  if (id < 0) id = (id == INT_MIN) ? INT_MAX : -id;
  while (id > 9)
    {
      id /= 10;
      r++;
    }
  return r;
}

int check_student_info (long int id, int grade, int age)
{
  if (get_digits_num (id) != 10)//#todo: CAN I USE MATH FUNCTIONS?
    {
      return 1;
    }
  if (grade < 0 || grade > 100)
    {
      return 2;
    }
  if (age < 18 || age > 120)
    {
      return 3;
    }
  return 0;
}

int find_best_student ()
{
  int num_of_students, grade, age;
  long int id;

  char user_input[BUFFER_SIZE];
  printf (GET_STUDENTS_NUM_MSG);
  fgets (user_input, BUFFER_SIZE, stdin);
  sscanf (user_input, "%d", &num_of_students);
  int counter = 0;
  Student *students = malloc (sizeof (Student) * num_of_students); //#todo: TEST MALLOCK AND FREE EVERTSHING
  if (students == NULL)
    {
      return EXIT_FAILURE;
    }

  while (counter < num_of_students)
    {
      printf (GET_STUDENT_INFO_MSG);
      fgets (user_input, BUFFER_SIZE, stdin);
      sscanf (user_input, "%ld,%d,%d", &id, &grade, &age);
      switch (check_student_info (id, grade, age))
        {
          case 1:printf (BAD_ID_ERR_MSG);
          continue;
          case 2:printf (BAD_GRADE_ERR_MSG);
          continue;
          case 3:printf (BAD_AGE_ERR_MSG);
          continue;
        }

      students[counter].id = id;
      students[counter].grade = grade;
      students[counter].age = age;

      counter++;
    }

  best_student (students, students + num_of_students - 1);
  free (students);

}

int main (int argc, char *argv[])
{
  char *task = argv[1];

  if (strcmp (task, BEST_TASK) == 0) // best
    {
      find_best_student ();
    }

  if (strcmp (task, BUBBLE_TASK) == 0) // bubble
    {

    }

  if (strcmp (task, QUICK_TASK) == 0) // quick
    {

    }

  return 0;

}
