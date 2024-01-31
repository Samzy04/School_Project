#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct student
{
  char Student_name[20];
  int id;
  char subject[20];
  int subject_ID;
  int Grade;
  struct student*next;
} Student;

typedef struct subject
{
  int subjectId;
  char Subject_name[50];
} Subject;

typedef struct teacher
{
  char name [20];
  unsigned int id;
  char subject[20];
  struct teacher*next;
} Teacher;

int student_id = 1;
int teacher_id = 1;

int generateRandomGrade() {
    return rand() % 9 + 1;
}


Student* addStudent(Student**head) 
{
  Student* newStudent = malloc(sizeof(Student));
  printf("Enter Student name: ");
  scanf("%s",newStudent->Student_name);
  printf("Enter Student Subjet: ");
  scanf("%s",newStudent->subject);
  getchar();
  newStudent->id=student_id++;
  newStudent->Grade = generateRandomGrade();
  newStudent->next = *head;
  *head= newStudent;
  return *head;
}

Teacher* addTeacher(Teacher**teacherHead) 
{
  Teacher* newTeacher = malloc(sizeof(Teacher));
  printf("Enter Teacher name: ");
  scanf("%s",newTeacher->name);
  printf("Enter Teacher Subjet: ");
  scanf("%s",newTeacher->subject);
  getchar();
  newTeacher->id=teacher_id++;
  newTeacher->next = *teacherHead;
  *teacherHead= newTeacher;
  return *teacherHead;
}




void printStudentDetails(Student*head) {
  printf("\nStudent Details:\n");
  printf("ID\tName\tSubject\tGrade\n");
    while (head != NULL) {
        printf("%d\t%s\t%s\t%d\n", head->id, head->Student_name, head->subject, head->Grade);
        head = head->next;
  }
}
void printTeacher(Teacher*teacherHead) {
  printf("\nTeacher Details:\n");
  printf("ID\tName\tSubject\n");
  while(teacherHead!=NULL){
    printf("%d\t%s\t%s\n", teacherHead->id, teacherHead->name, teacherHead->subject);
    teacherHead = teacherHead->next;
  }
}


void findStudentsBySubject(Student* students, const char* subjectName) {
    printf("\nStudents studying subject %s:\n", subjectName);
    int found = 0;
    while (students != NULL) {
        if (strcmp(students->subject, subjectName) == 0) {
            printf("%d\t%s\t%s\n", students->id, students->Student_name, students->subject);
            found = 1;
        }
        students = students->next;
    }
    
    if (!found) {
        printf("No students found for subject %s\n", subjectName);
    }
}

void assignGradeToStudent(Student *head, int grade) {
    printf("\nStudents with grade %d:\n", grade);
    int found = 0;
    Student *student = head; 
    while (student != NULL) {
        if (student->Grade == grade) {
            printf("%d\t%s\t%s\t%d\n", student->id, student->Student_name, student->subject, student->Grade);
            found = 1;
        }
        student = student->next;
    }
    
    if (!found) {
        printf("No students found with grade %d\n", grade);
        return;
    }
    
    char choice;
    printf("Do you want to change the grade for these students? (y/n): ");
    scanf(" %c", &choice);
    
    if (choice == 'y' || choice == 'Y') {
        int newGrade;
        printf("Enter the new grade for these students: ");
        scanf("%d", &newGrade);
        
        student = head; 
        while (student != NULL) {
            if (student->Grade == grade) {
                student->Grade = newGrade;
                printf("%d\t%s\t%s\t%d\n", student->id, student->Student_name, student->subject, student->Grade);
            }
            student = student->next;
        }
    } else {
        printf("Grade not changed.\n");
    }
}



void findTeacherBySubject(Teacher* teachers, const char* subjectName) {
    printf("\nTeacher teaching subject %s:\n", subjectName);
    int found = 0;
    while (teachers != NULL) {
        if (strcmp(teachers->subject, subjectName) == 0) {
            printf("%d\t%s\t%s\n", teachers->id, teachers->name, teachers->subject);
            found = 1;
        }
        teachers = teachers->next;
    }
    
    if (!found) {
        printf("No Teacher found for subject %s\n", subjectName);
    }
}



int main() 
{
  srand(time(NULL));
  Student*head = NULL;
  Teacher*teacherHead = NULL;
  int number_of_students;
  int number_of_teachers;
  printf("Enter number of students: ");
  scanf("%d",&number_of_students);
  for(int i=0;i<number_of_students;i++){ 
    addStudent(&head);
   
  }
   printStudentDetails(head);
  printf("\nEnter number of teachers: ");
  scanf("%d",&number_of_teachers);
  for(int i=0;i<number_of_teachers;i++){ 
     addTeacher(&teacherHead);
  }
  printTeacher(teacherHead);
  char subjectNameToFind[20];
  printf("\nEnter subject name to find students: ");
  scanf("%s", subjectNameToFind);
  findStudentsBySubject(head, subjectNameToFind);
  char subjectNameToFindforTeacher[20];
  printf("\nEnter subject name to find teacher: ");
  scanf("%s", subjectNameToFindforTeacher);
  findTeacherBySubject(teacherHead, subjectNameToFindforTeacher);
  int gradeToFind;
  printf("\nEnter grade to find students: ");
  scanf("%d", &gradeToFind);
  assignGradeToStudent(head, gradeToFind);

  return 0;
}