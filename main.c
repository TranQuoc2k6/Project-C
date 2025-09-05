#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void clearScreen() {
    for (int i = 0; i < 100; i++) {
        printf("\n");
    }
}

void startProgram() {
    printf("\n*** Student Management System Using C ***\n\n");
    printf("\t    CHOOSE YOUR ROLE\n");
    printf("\t =======================\n");
    printf("\t [1] Admin.\n");
    printf("\t [2] Student.\n");
    printf("\t [3] Teacher.\n");
    printf("\t [0] Exit the Program.\n");
    printf("\t =======================\n");
    printf("\t Enter The Choice:");
}

void menuAdmin() {
    printf("\n*** Student Management System Using C ***\n\n");
    printf("\t      STUDENT ADMIN\n");
    printf("\t =======================\n");
    printf("\t [1] Students management.\n");
    printf("\t [2] Classrooms management.\n");
    printf("\t [3] Teacher management.\n");
    printf("\t [4] User Guideline.\n");
    printf("\t [5] About Us.\n");
    printf("\t [0] Exit the Program.\n");
    printf("\t =======================\n");
    printf("\t Enter The Choice:");
}

void menuStudent() {
    printf("\n*** Student Management System Using C ***\n\n");
    printf("\t      STUDENT MENU\n");
    printf("\t =======================\n");
    printf("\t [1] Add A New student.\n");
    printf("\t [2] Show All student.\n");
    printf("\t [3] Search A student.\n");
    printf("\t [4] Edit A student.\n");
    printf("\t [5] Delete A student.\n");
    printf("\t [6] Sort All student.\n");
    printf("\t [0] Exit the Program.\n");
    printf("\t =======================\n");
    printf("\t Enter The Choice:");
}

void menuSortStudent() {
    printf("\n*** Student Management System Using C ***\n\n");
    printf("\t      STUDENT SORT\n");
    printf("\t =======================\n");
    printf("\t [1] A --> Z.\n");
    printf("\t [2] Z --> A.\n");
    printf("\t [0] Exit the Program.\n");
    printf("\t =======================\n");
    printf("\t Enter The Choice:");
}



struct Date {
    int day;
    int month;
    int year;
};

struct Student {
    char studentId[20];
    char classroomId[10];
    char name[20];
    struct Date dateOfBirth;
    bool gender;
    char email[30];
    char phone[20];
    char password[20];
};

struct Classroom {
    char classroomId[10];
    char teacherId[10];
    char classroomName[10];
    struct Student students[100];
};

struct Teacher {
    char teacherId[20];
    char classroomId[10];
    char Name[20];
    struct Date dateOfBirth;
    bool gender;
    char Email[30];
    char Phone[20];
    char password[20];
    struct Classroom classrooms[100];
};

void selectDisplay() {
    while (1) {
        printf("Go back(b) or Exit(0)?: ");
        char choice[100];
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = '\0';
        if (strcmp(choice, "b") == 0) {
            return;
        }else if (strcmp(choice, "0") == 0) {
            printf("\n=============== Thank  You ================\n");
            printf("============== See You Soon ===============\n");
            printf("___________________________________________\n");
            exit(0);
        }else {
            printf("INVALID SELECTION. PLEASE TRY AGAIN !!!\n\n");
        }
    }
}

void displayStudents(struct Student student[], int size) {
    printf("\n\t\t\t\t\t*** ALL STUDENT ***\n");
    printf("|===============|===========|====================|============================|====================|==============|\n");
    printf("|       ID      |   Class   |        Name        |           Email            |       Phone        |   NO.Course  |\n");
    printf("|===============|===========|====================|============================|====================|==============|\n");
    for (int i = 0; i < size; i++) {
        printf("| %-13s | %-9s | %-18s | %-26s | %-18s | %-12d |\n",
            student[i].studentId,
            student[i].classroomId,
            student[i].name,
            student[i].email,
            student[i].phone,
            i + 1);
        printf("|---------------|-----------|--------------------|----------------------------|--------------------|--------------|\n");
    }
    selectDisplay();
}

void addStudent(struct Student student[], int *size) {
    if (*size > 100) {
        printf("Cannot add more students. Limit reached!\n");
        return;
    }
    struct Student newStudent;

    printf("\n\t\t\t\t\t*** ADD A NEW STUDENT ***\n");

    printf("Enter ID: ");
    fgets(newStudent.studentId, sizeof(newStudent.studentId), stdin);
    newStudent.studentId[strcspn(newStudent.studentId, "\n")] = '\0';

    printf("Enter Classroom ID: ");
    fgets(newStudent.classroomId, sizeof(newStudent.classroomId), stdin);
    newStudent.classroomId[strcspn(newStudent.classroomId, "\n")] = '\0';

    printf("Enter Name: ");
    fgets(newStudent.name, sizeof(newStudent.name), stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0';

    printf("Enter Day of Birth (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &newStudent.dateOfBirth.day, &newStudent.dateOfBirth.month, &newStudent.dateOfBirth.year);
    getchar();

    printf("Enter Gender (1 for Male, 0 for Female): ");
    int g;
    scanf("%d", &g);
    getchar();
    newStudent.gender = (g == 1);

    printf("Enter Email: ");
    fgets(newStudent.email, sizeof(newStudent.email), stdin);
    newStudent.email[strcspn(newStudent.email, "\n")] = '\0';

    printf("Enter Phone: ");
    fgets(newStudent.phone, sizeof(newStudent.phone), stdin);
    newStudent.phone[strcspn(newStudent.phone, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(newStudent.password, sizeof(newStudent.password), stdin);
    newStudent.password[strcspn(newStudent.password, "\n")] = '\0';

    student[*size] = newStudent;
    (*size)++;

    printf("Student added successfully!\n");
    selectDisplay();
}

void updateStudent(struct Student student[], int size) {
    char classroomIdNew[10];
    char nameNew[20];
    char emailNew[30];
    char phoneNew[20];

    char inputIdUpdate[20];
    printf("\n\t\t\t\t\t*** EDIT A STUDENT ***\n");
    int flag = 0;
    while (flag == 0) {
        printf("Enter the ID to update:");
        fgets(inputIdUpdate, sizeof(inputIdUpdate), stdin);
        inputIdUpdate[strcspn(inputIdUpdate, "\n")] = '\0';
        for (int i = 0; i < size; i++) {
            if (strcmp(student[i].studentId, inputIdUpdate) == 0) {
                flag = 1;
                printf("Enter classroom update:");
                fgets(classroomIdNew, 10, stdin);
                classroomIdNew[strcspn(classroomIdNew, "\n")] = '\0';
                strcpy(student[i].classroomId, classroomIdNew);

                printf("Enter name update:");
                fgets(nameNew, 20, stdin);
                nameNew[strcspn(nameNew, "\n")] = '\0';
                strcpy(student[i].name, nameNew);

                printf("Enter email update:");
                fgets(emailNew, 30, stdin);
                emailNew[strcspn(emailNew, "\n")] = '\0';
                strcpy(student[i].email, emailNew);

                printf("Enter phone update:");
                fgets(phoneNew, 20, stdin);
                phoneNew[strcspn(phoneNew, "\n")] = '\0';
                strcpy(student[i].phone, phoneNew);

                printf("UPDATED SUCCESSFULLY !!!\n\n");
                selectDisplay();
            }
        }
        if (flag == 0) {
            printf("STUDENT ID DOES NOT EXIST. PLEASE TRY AGAIN !!!\n\n");
        }
    }
}


void sortStudent(struct Student student[], int size) {
    int choice;
    menuSortStudent();
    scanf("%d", &choice);

    // for (int i = 0; i < size; i++) {
    //     if
    // }
}


void choiceStudent(struct Student student[], int *size) {
    int choiceMenuStudent;
    int keepRunning = 1;
    while (keepRunning) {
        clearScreen();
        menuStudent();
        scanf("%d", &choiceMenuStudent);
        getchar();
        switch (choiceMenuStudent) {
            case 1:
                clearScreen();
                addStudent(student, size);
                break;
            case 2:
                clearScreen();
                displayStudents(student, *size);
                break;
            case 3:
                clearScreen();

                break;
            case 4:
                clearScreen();
                updateStudent(student, *size);
                break;
            case 5:
                clearScreen();
                break;
            case 6:
                clearScreen();
                sortStudent(student, *size);
                break;
            case 0:
                keepRunning = 0;
                break;
            default:
                printf("INVALID SELECTION. PLEASE TRY AGAIN !!!");
                break;
        }
    }

}


int main(void) {
    int choice;
    struct Student student[100] = {
        {
            "017206004502",
            "CNTT6",
            "Tran Anh Quoc",
            {2,11,2006},
            1,
            "qatran2k6@gmail.com",
            "0393130688",
            "Qatran2006@"
        },
        {
            "020207056395",
            "CNTT1",
            "Duong Thi Bich",
            {3,2,2007},
            0,
            "bichduong2007@gmail.com",
            "0356840817",
            "bichduong07"
        },
        {
            "014204995680",
            "CNTT4",
            "Tran Quoc Anh",
            {3,8,2009},
            1,
            "Quocanhtran09@gmail.com",
            "0367390153",
            "quocanhtran09"
        },
        {
            "057205963816",
            "CNTT3",
            "Tran Bich Anh",
            {6,9,2008},
            0,
            "bichanh8@gmail.com",
            "0939752955",
            "tranbichanh69908"
        }
    };

    int size = 4;
    do {
        clearScreen();
        startProgram();
        scanf("%d", &choice);
        getchar();
    switch (choice) {
        case 1:
            clearScreen();
            menuAdmin();
            break;
        case 2:
            clearScreen();
            choiceStudent(student, &size);
            break;
        case 3:
            clearScreen();
            break;

        case 0:
            printf("\n=============== Thank  You ================\n");
            printf("============== See You Soon ===============\n");
            printf("___________________________________________\n");
            break;

        default:
            printf("INVALID SELECTION. PLEASE TRY AGAIN !!!");
            break;
    }
    }while (choice != 0);

    return 0;
}