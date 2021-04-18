//*********************
// Exercise  2
//
// Name: Matanel Pataki
//
// ID: 205951023
//
// A program to store and sort students information (id, grade, age).
//*********************

// Includes:
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Messages:
#define GET_STUDENTS_NUM_MSG "Enter number of students. Then enter\n"
#define GET_STUDENT_INFO_MSG "Enter student info. Then enter\n"
#define BAD_ID_ERR_MSG "ERROR: Id must've 10 digits and can't start with 0.\n"
#define BAD_GRADE_ERR_MSG "ERROR: Grade should between 0-100 (includes).\n"
#define BAD_AGE_ERR_MSG "ERROR: Age should be between 18 and 120 (includes).\n"
#define BEST_STUDENT_IS_MSG "best student info is: %ld,%d,%d\n"
#define USAGE_ERR_MSG "USAGE: Please choose a task (best\\bubble\\quick).\n"
#define BAD_STUDENT_NUM_ERR_MSG "ERROR: Please enter a natural number.\n"

// Values:
#define BEST_TASK "best"
#define BUBBLE_TASK "bubble"
#define QUICK_TASK "quick"
#define BUFFER_SIZE 60
#define GRADE_MIN 0
#define GRADE_MAX 100
#define AGE_MIN 18
#define AGE_MAX 120
#define ID_NUM_OF_DIGITS 10
#define ONE_DIGIT_NUM 9
#define TEN 10
#define NUM_OF_WANTED_COMMAS 3

typedef struct Student
/// A struct to represent a student in a university.
{
  int age, grade;
  long int id;
  float rank; //will help choose the best student
} Student;

void best_student (Student *start, Student *end)
/// This function will go through the students one by one and will print
/// the best one (best = grade/age is the highest).
/// \param start is a pointer to the start of the students array.
/// \param end s a pointer to the end of the students array.
{
  Student *best_student_p = start;
  while (start != end)
    {
      start++; //pointer arithmetics, will move a whole index in the array
      if (start->rank > best_student_p->rank)
        {
          best_student_p = start;
        }
    }
  printf (BEST_STUDENT_IS_MSG,
          best_student_p->id, best_student_p->grade, best_student_p->age);
}

void swap_students (Student *student1, Student *student2)
/// This function will swap two given student position in the student array.
/// \param student1 is a pointer to the first student.
/// \param student2 is a pointer to the second student.
{
  Student temp;
  temp = *student1;
  *student1 = *student2;
  *student2 = temp;
}

void bubble_sort (Student *start, Student *end)
/// This function will use bubble sort to sort the students array by grade.
/// \param start is a pointer to the start of the students array.
/// \param end s a pointer to the end of the students array.
{
  for (int i = 0; i < end - start; i++)
    {
      for (Student *j = start; j != end - i; j++)
        {
          if (j->grade > (j + 1)->grade)
            {
              swap_students (j, j + 1);
            }
        }
    }
}

Student *partition (Student *start, Student *end)
/// This function is the helper for the quick-sort function.
/// For more info: https://www.youtube.com/watch?v=PgBzjlCcFvc.
/// \param start is a pointer to the start of the students array.
/// \param end s a pointer to the end of the students array.
/// \return the pivot point (the partition).
{
  Student *pivot = start - 1;
  for (Student *j = start; j != end; j++)
    {
      if (j->age <= end->age)
        {
          pivot++;
          swap_students (j, pivot);
        }
    }
  swap_students (end, pivot + 1);
  return (pivot + 1);
}

void quick_sort (Student *start, Student *end)
/// A recursive function that sort the students array by age.
/// For more info: https://www.youtube.com/watch?v=PgBzjlCcFvc.
/// \param start is a pointer to the start of the students array.
/// \param end s a pointer to the end of the students array.
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
/// This function return the number of digits in an long.
/// \param id is the representation of a student's ID.
/// \return an int, the num of digits.
{
  int r = 1;
  while (id > ONE_DIGIT_NUM)
    {
      id /= TEN;
      r++;
    }
  return r;
}

int check_student_info (long id, int grade, int age)
/// This function check the validity of the student info.
/// \param id is the representation of a student's ID.
/// \param grade is the representation of a student's grade.
/// \param age is the representation of a student's age.
/// \return 1 - problem with id, 2 - problem with grade, 3 - problem with age.
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
  return 0; //no problem found.
}

void print_students (int num_of_students, Student *students)
/// This function will go through the student's array and will print is one
/// student at a time according to the order in the array.
/// \param num_of_students  is the representation of a students array's length.
/// \param students is a pointer for the students array.
{
  for (int i = 0; i < num_of_students; i++)
    {
      printf ("%ld,%d,%d\n", students[i].id,
              students[i].grade, students[i].age);
    }

}

int check_user_string (const char *user_input)
/// This function checks the chars of the user input string for non-numbers
/// param user_input is a string for the users input;
/// \return 1 - problem with id, 2 - problem with grade, 3 - problem with age
///         0 - problem with num of commas, -1 - all good.
{
  int comma_counter = 1;
  if (user_input[0] == '0')
    {
      return comma_counter;
    }
  for (size_t i = 0; user_input[i] != '\0'; i++)
    {
      if (user_input[i] == '\n')
        {
          continue;
        }
      if (user_input[i] == ',') //char == ','
        {
          comma_counter++;
          continue;
        }
      if (user_input[i] < '0' || '9' < user_input[i]) //if char not a digit
        {
          return comma_counter;
        }
    }
  if (comma_counter != NUM_OF_WANTED_COMMAS)
    {
      return 0;
    }
  return -1;
}

int get_user_input (char *task)
/// This function is getting the input from the user using the console.
/// If the given info is not valid, the function will keep asking for info.
/// \param task is the current task being preformed (quick/bubble/quick)
/// \return the right exit-code.
{
  // Variables declarations:
  int num_of_students, grade, age;
  int long id;
  char user_input[BUFFER_SIZE];
  int counter = 0;


  // Getting the total amount of students:
  printf (GET_STUDENTS_NUM_MSG);
  fgets (user_input, BUFFER_SIZE, stdin);
  sscanf (user_input, "%d", &num_of_students);

  // if the number of students is invalid, ask again:
  while (num_of_students <= 0)
    {
      printf (BAD_STUDENT_NUM_ERR_MSG);
      printf (GET_STUDENTS_NUM_MSG);
      fgets (user_input, BUFFER_SIZE, stdin);
      sscanf (user_input, "%d", &num_of_students);
    }

  // Dynamic memory allocation for the students array:
  Student *students = malloc (sizeof (Student) * num_of_students);
  if (students == NULL) // in case malloc failed.
    {
      return EXIT_FAILURE;
    }

  // A while loop to get all the students info for the array:
  while (counter < num_of_students)
    {
      printf (GET_STUDENT_INFO_MSG);
      fgets (user_input, BUFFER_SIZE, stdin);

      switch (check_user_string (user_input))
        {
          case 0 :
          case 1 :printf (BAD_ID_ERR_MSG);
          continue;
          case 2:printf (BAD_GRADE_ERR_MSG);
          continue;
          case 3:printf (BAD_AGE_ERR_MSG);
          continue;
        }

      sscanf (user_input, "%ld,%d,%d", &id, &grade, &age);

      // Checking for the students info validity:
      switch (check_student_info (id, grade, age))
        {
          case 1:printf (BAD_ID_ERR_MSG);
          continue;
          case 2:printf (BAD_GRADE_ERR_MSG);
          continue;
          case 3:printf (BAD_AGE_ERR_MSG);
          continue;
        }

      // Saving the student's info in it's struct:
      students[counter].id = id;
      students[counter].grade = grade;
      students[counter].age = age;
      students[counter].rank = (float) grade / (float) age;

      counter++;
    }

  // Determining with task to preform, according to user input:
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

  // Freeing the allocated memory in the heep:
  free (students);

  return EXIT_SUCCESS;

}

int main (int argc, char *argv[])
{
  char *task = argv[1];

  // Making sure the program got the right arguments:
  if (argc != 2 || (strcmp (task, BEST_TASK) != 0
                    && strcmp (task, BUBBLE_TASK) != 0
                    && strcmp (task, QUICK_TASK) != 0))
    {
      printf (USAGE_ERR_MSG);
      return EXIT_FAILURE;
    }

  return get_user_input (task);
}
