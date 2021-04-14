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
#define GRADE_MIN 0
#define GRADE_MAX 100
#define AGE_MIN 18
#define AGE_MAX 120
#define ID_NUM_OF_DIGITS 10
#define USAGE_ERR_MSG "USAGE: Please choose a one valid task (best\\bubble\\quick)\n"
#define ONE_DIGIT_NUM 9
#define TEN 10
typedef struct Student {
  int age, grade;
  long int id;
  float rank;
} Student;

void best_student (Student *start, Student *end)
{
  Student *best_student_p = start;
  while (start != end)
    {
      start++;
      if (start->rank > best_student_p->rank)
        {
          best_student_p = start;
        }
    }
  printf (BEST_STUDENT_IS_MSG,
          best_student_p->id, best_student_p->grade, best_student_p->age);
}

void bubble_sort (Student *start, Student *end)
{
  Student temp;
  for (int i = 0; i < end - start; i++)
    {
      for (Student *j = start; j != end - i; j++)
        {
          if (j->grade > (j + 1)->grade)
            {
              temp = *j;
              *j = *(j + 1);
              *(j + 1) = temp;
            }
        }
    }
}

Student *partition (Student *start, Student *end)
{
  Student temp;
  Student *pivot = start - 1;
  for (Student *j = start; j != end; j++)
    {
      if (j->age <= end->age)
        {
          pivot++;
          temp = *j;
          *j = *pivot;
          *pivot = temp;
        }
    }
  temp = *end;
  *end = *(pivot + 1);
  *(pivot + 1) = temp;
  return (pivot + 1);
}

void quick_sort (Student *start, Student *end)
{
  if (end <= start)
    {
      return;
    }
  Student *pivot = partition (start, end);
  quick_sort (start, pivot - 1);
  quick_sort (pivot + 1, end);

}

int get_digits_num (long id)
{
  int r = 1;
  while (id > ONE_DIGIT_NUM)
    {
      id /= TEN;
      r++;
    }
  return r;
}

int check_student_info (long int id, int grade, int age)
{
  if (get_digits_num (id) != ID_NUM_OF_DIGITS)
    {
      return 1;
    }
  if (grade < GRADE_MIN || grade > GRADE_MAX)
    {
      return 2;
    }
  if (age < AGE_MIN || age > AGE_MAX)
    {
      return 3;
    }
  return 0;
}

void print_students (int num_of_students, Student *students)
{
  for (int i = 0; i < num_of_students; i++)
    {
      printf ("%ld,%d,%d\n", students[i].id,
              students[i].grade, students[i].age);
    }
}
int get_user_input (char *task)
{
  int num_of_students, grade, age;
  long int id;

  char user_input[BUFFER_SIZE];
  printf (GET_STUDENTS_NUM_MSG);
  fgets (user_input, BUFFER_SIZE, stdin);
  sscanf (user_input, "%d", &num_of_students);
  int counter = 0;
  Student *students = malloc (sizeof (Student) * num_of_students);
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
      students[counter].rank = (float) grade / (float) age;

      counter++;
    }

  if (strcmp (task, BEST_TASK) == 0) // best
    {
      best_student (students, students + num_of_students - 1);
    }

  if (strcmp (task, BUBBLE_TASK) == 0) // bubble
    {
      bubble_sort (students, students + num_of_students - 1);
      print_students (num_of_students, students);
    }

  if (strcmp (task, QUICK_TASK) == 0) // quick
    {
      quick_sort (students, students + num_of_students - 1);
      print_students (num_of_students, students);
    }
  free (students);
  return EXIT_SUCCESS;

}

int main (int argc, char *argv[])
{
  char *task = argv[1];
  if (argc != 2 || strcmp (task, BEST_TASK) != 0
                   && strcmp (task, BUBBLE_TASK) != 0
                   && strcmp (task, QUICK_TASK) != 0)
    {
      printf (USAGE_ERR_MSG);
      return EXIT_FAILURE;
    }
  return get_user_input (task);
}
