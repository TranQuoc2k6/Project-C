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
    int studentId;
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
    char choice[100];
    while (1) {
        printf("Go back(b) or Exit(0)?: ");
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
    printf("|===============|====================|============================|====================|==============|\n");
    printf("|       ID      |        Name        |           Email            |       Phone        |   NO.Course  |\n");
    printf("|===============|====================|============================|====================|==============|\n");
    for (int i = 0; i < size; i++) {
        printf("| %-13d | %-18s | %-26s | %-18s | %-12d |\n",
            student[i].studentId,
            student[i].name,
            student[i].email,
            student[i].phone,
            i + 1);
        printf("|---------------|--------------------|----------------------------|--------------------|--------------|\n");
    }
    selectDisplay();
}

void addStudent(struct Student student[], int *size) {
    if (*size > 100) {
        printf("CANNOT ADD MORE STUDENTS. LIMIT REACHED !!!\n");
        return;
    }

    struct Student newStudent;
    printf("\n\t\t\t\t\t*** ADD A NEW STUDENT ***\n");

    newStudent.studentId = *size + 1;
    printf("- ID: %d\n\n", newStudent.studentId);

    printf("- Enter Name: ");
    fgets(newStudent.name, sizeof(newStudent.name), stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0';

    printf("- Enter Day of Birth (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &newStudent.dateOfBirth.day, &newStudent.dateOfBirth.month, &newStudent.dateOfBirth.year);
    getchar();

    printf("- Enter Gender (1 for Male, 0 for Female): ");
    int g;
    scanf("%d", &g);
    getchar();
    newStudent.gender = (g == 1);

    printf("- Enter Email: ");
    fgets(newStudent.email, sizeof(newStudent.email), stdin);
    newStudent.email[strcspn(newStudent.email, "\n")] = '\0';

    printf("- Enter Phone: ");
    fgets(newStudent.phone, sizeof(newStudent.phone), stdin);
    newStudent.phone[strcspn(newStudent.phone, "\n")] = '\0';

    printf("- Enter Password: ");
    fgets(newStudent.password, sizeof(newStudent.password), stdin);
    newStudent.password[strcspn(newStudent.password, "\n")] = '\0';

    student[*size] = newStudent;
    (*size)++;

    printf("STUDENT ADDED SUCCESSFULLY !!!\n");
    selectDisplay();
}

void updateStudent(struct Student student[], int size) {
    char nameNew[20];
    char emailNew[30];
    char phoneNew[20];

    int inputIdUpdate;
    printf("\n\t\t\t\t\t*** EDIT A STUDENT ***\n");
    int flag = 0;
    while (flag == 0) {
        printf("- Enter the ID to update:");
        scanf("%d", &inputIdUpdate);
        getchar();
        for (int i = 0; i < size; i++) {
            if (student[i].studentId == inputIdUpdate) {
                flag = 1;

                printf("STUDENT INFORMATITONS\n");
                printf("------------------------\n");
                printf("ID: %d\n", student[i].studentId);
                printf("NAME: %s\n", student[i].name);
                printf("EMAIL: %s\n", student[i].email);
                printf("PHONE: %s\n", student[i].phone);
                printf("------------------------\n\n");

                printf("- Enter name update:");
                fgets(nameNew, 20, stdin);
                nameNew[strcspn(nameNew, "\n")] = '\0';
                strcpy(student[i].name, nameNew);

                printf("- Enter email update:");
                fgets(emailNew, 30, stdin);
                emailNew[strcspn(emailNew, "\n")] = '\0';
                strcpy(student[i].email, emailNew);

                printf("- Enter phone update:");
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

void deleteStudent(struct Student student[], int *size) {
    if (*size == 0) {
        printf("CANNOT DELETE MORE STUDENTS. LIMIT REACHED !!!\n");
        return;
    }

    printf("\n\t\t\t\t\t*** DELETE A STUDENT ***\n");
    int idStudentDelete;
    int flag = 0;
    do {
        printf("- Enter ID delete:");
        scanf("%d", &idStudentDelete);
        getchar();

        for (int i = 0; i < *size; i++) {
            if (idStudentDelete == student[i].studentId) {
                flag = 1;

                printf("STUDENT INFORMATITONS\n");
                printf("------------------------\n");
                printf("ID: %d\n", student[i].studentId);
                printf("NAME: %s\n", student[i].name);
                printf("EMAIL: %s\n", student[i].email);
                printf("PHONE: %s\n", student[i].phone);
                printf("------------------------\n\n");

                int inputSelection;

                do {
                    printf("Do you agree to delete the student?( 1 for Yes, 0 for No ):");
                    scanf("%d", &inputSelection);
                    getchar();
                    switch (inputSelection) {
                        case 1:
                            for (int j = i; j < *size - 1; j++) {
                                student[j] = student[j + 1];
                            }
                            (*size)--;
                            printf("DELETE SUCCESSFULLY !!!\n\n");
                            return;
                        case 0:
                            printf("DELETE STUDENT FAILED !!!\n\n");
                            return;
                        default:
                            printf("INVALID SELECTION. PLEASE TRY AGAIN !!!\n\n");
                            break;
                    }
                }while (1);
            }
        }
        if (flag == 0) {
            printf("STUDENT ID DOES NOT EXIST. PLEASE TRY AGAIN !!!\n\n");
        }
    }while (1);

}


void extractLastName(char fullName[], char lastName[]) {
    int len = strlen(fullName);
    int pos = len - 1;

    while (pos >= 0 && fullName[pos] != ' ') {
        pos--;
    }

    if (pos < 0) {
        strcpy(lastName, fullName);
    } else {
        strcpy(lastName, fullName + pos + 1);
    }
}

void sortStudent(struct Student student[], int size) {
    int choice;
    do {
        clearScreen();
        menuSortStudent();
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                char lastName1[50], lastName2[50];

                for (int i = 0; i < size - 1; i++) {
                    for (int j = i + 1; j < size; j++) {
                        extractLastName(student[i].name, lastName1);
                        extractLastName(student[j].name, lastName2);

                        int cmp = strcmp(lastName1, lastName2);

                        if (cmp > 0 || (cmp == 0 && strcmp(student[i].name, student[j].name) > 0)) {
                            struct Student tmp = student[i];
                            student[i] = student[j];
                            student[j] = tmp;
                        }
                    }
                }

                displayStudents(student, size);
                break;
            case 2:
                char lastName3[50], lastName4[50];

                for (int i = 0; i < size - 1; i++) {
                    for (int j = i + 1; j < size; j++) {
                        extractLastName(student[i].name, lastName3);
                        extractLastName(student[j].name, lastName4);

                        int cmp = strcmp(lastName3, lastName4);

                        if (cmp < 0 || (cmp == 0 && strcmp(student[i].name, student[j].name) < 0)) {
                            struct Student tmp = student[i];
                            student[i] = student[j];
                            student[j] = tmp;
                        }
                    }
                }
                displayStudents(student, size);
                break;
            case 0:
                break;
            default:
                printf("INVALID SELECTION. PLEASE TRY AGAIN !!!\n\n");
                break;
        }
    }while (choice != 0);
}


void stduentAdmin(struct Student student[], int *size) {
    int choiceMenuStudent;
    do {
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
                deleteStudent(student, size);
                break;
            case 6:
                clearScreen();
                sortStudent(student, *size);
                break;
            case 0:
                break;
            default:
                printf("INVALID SELECTION. PLEASE TRY AGAIN !!!\n\n");
                break;
        }
    }while (choiceMenuStudent != 0);
}

void choiceAdmin(struct Student student[], int *size) {
    int choiceMenuAdmin;
    do {
        clearScreen();
        menuAdmin();
        scanf("%d", &choiceMenuAdmin);
        getchar();
        switch (choiceMenuAdmin) {
            case 1:
                clearScreen();
                stduentAdmin(student, size);
                break;
            case 2:
                clearScreen();
                break;
            case 3:
                clearScreen();
                break;
            case 4:
                clearScreen();
                break;
            case 5:
                clearScreen();
                break;
            case 6:
                clearScreen();
                break;
            case 0:
                break;
            default:
                printf("INVALID SELECTION. PLEASE TRY AGAIN !!!\n\n");
                break;
        }
    }while (choiceMenuAdmin != 0);
}

int main(void) {
    int choice;
    struct Student student[100] = {
        {
            1,
            "CNTT6",
            "Tran Anh Quoc",
            {2,11,2006},
            1,
            "qatran2k6@gmail.com",
            "0393130688",
            "Qatran2006@"
        },
        {
            2,
            "CNTT1",
            "Duong Thi Bich",
            {3,2,2007},
            0,
            "bichduong2007@gmail.com",
            "0356840817",
            "bichduong07"
        },
        {
            3,
            "CNTT4",
            "Tran Quoc Anh",
            {3,8,2009},
            1,
            "Quocanhtran09@gmail.com",
            "0367390153",
            "quocanhtran09"
        },
        {
            4,
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
            choiceAdmin(student, &size);
            break;
        case 2:
            clearScreen();
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
            printf("INVALID SELECTION. PLEASE TRY AGAIN !!!\n\n");
            break;
    }
    }while (choice != 0);

    return 0;
}