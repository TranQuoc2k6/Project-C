#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

// Ham kiem tra tinh hop li cua du lieu nhap
int validateUserInput(User newUser) {
    if (newUser.id == 0 ||strlen(newUser.username) == 0 || strlen(newUser.password) == 0 || strlen(newUser.email) == 0 || strlen(newUser.phone) == 0) {
        printf("\nThong tin nguoi dung trong\n");
        return 0;
    }
// Kiem tra do dai toi thieu và toi da
    long long int id = newUser.id;
    int idLength = 0;
    if(id == 0){
        idLength = 1; 
    } else {
        while (id > 0) {
            id /= 10;
            idLength++;
        }
    }
    if (idLength < 2 || idLength > 12) { 
        printf("\nID khong hop le\n");
        return 0;
    }
    if (strlen(newUser.username) < 2 || strlen(newUser.username) > 50) {
        printf("\nTen nguoi dung khong hop le\n");
        return 0;
    }
    if (strlen(newUser.email) < 5 || strlen(newUser.email) > 30) {
        printf("\nEmail khong hop le\n");
        return 0;
    }
    if (strlen(newUser.phone) < 10 || strlen(newUser.phone) > 15) {
        printf("\nSo dien thoai khong hop le\n");
        return 0;
    }
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == newUser.id || strcmp(users[i].username, newUser.username) == 0 || strcmp(users[i].email, newUser.email) == 0) {
            printf("\nID, ten nguoi dung hoac email da ton tai\n");
            return 0;
        }
    }
    return 1;
}

//Hien thi danh sach menu quan li nguoi dung
void displayMenu() {
	system("cls");
    printf("\n*** Quan ly tai khoan nguoi dung ***\n\n");
    printf("[1] Hien thi danh sach nguoi dung\n");
    printf("[2] Them nguoi dung moi\n");
    printf("[3] Tim kiem nguoi dung theo ten\n");
    printf("[4] ID nguoi dung muon xem\n");
    printf("[5] Mo khoa (khoa) tai khoan nguoi dung\n");
    printf("[6] Sap xep danh sach nguoi dung\n");
    printf("[7] Thoat\n");
    printf("Lua chon cua ban: ");
}

// Ham hien thi danh sach thong tin nguoi dung
void displayUsers() {
    if (userCount == 0) {
        printf("\nDanh sach nguoi dung trong!\n");
        return;
    }
    printf("\nDanh sach nguoi dung:\n");
    printf("+--------------------+--------------------+--------------------------+-------------------+------------------+------------+\n");
    printf("|        ID          | Ten nguoi dung     | Email                    | So dien thoai     | Mat khau         | Trang thai |\n");
    printf("+--------------------+--------------------+--------------------------+-------------------+------------------+------------+\n");
    for (int i = 0; i < userCount; i++) {
        printf("| %-18lld | %-18s | %-24s | %-17s | %-16s | %-10s |\n", 
            users[i].id,        
            users[i].username,
            users[i].email,
            users[i].phone,
            users[i].password,
            users[i].status);
    }
    printf("+--------------------+--------------------+--------------------------+-------------------+------------------+------------+\n");
}

// Ham them nguoi moi 
void addUsers() {
    if (userCount >= 100) {
        printf("\nKhong the them nguoi dung moi, danh sach da day\n");
        return;
    }

    User newUser;
    printf("\nNhap ID: ");
    scanf("%lld", &newUser.id);
    getchar(); 

    printf("Nhap ten nguoi dung: ");
    fgets(newUser.username, sizeof(newUser.username), stdin);
    newUser.username[strcspn(newUser.username, "\n")] = '\0'; 

    printf("Nhap email nguoi dung: ");
    fgets(newUser.email, sizeof(newUser.email), stdin);
    newUser.email[strcspn(newUser.email, "\n")] = '\0';

    printf("Nhap so dien thoai nguoi dung: ");
    fgets(newUser.phone, sizeof(newUser.phone), stdin);
    newUser.phone[strcspn(newUser.phone, "\n")] = '\0';

    // Gan mat khau mac dinh va trang thai
    strcpy(newUser.password, newUser.phone);
    strcpy(newUser.status, "open");

    // Kiem tra du lieu dau vao
    if (validateUserInput(newUser)) {
        users[userCount] = newUser; 
        userCount++;
        printf("\nThem nguoi dung thanh cong!\n");
        
        saveUsersToFile("users.txt");
    }
}

// Ham tim kiem nguoi dung theo ten
void searchUserByName() {
    char searchName[50];
    printf("\nNhap ten nguoi dung muon tim kiem: ");
    getchar(); 
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0';
    
    int flag = 0;
    printf("\nKet qua tim kiem:\n");
    printf("+--------------------+--------------------+--------------------------+-------------------+\n");
    printf("|        ID          | Ten nguoi dung     | Email                    | So dien thoai     |\n");
    printf("+--------------------+--------------------+--------------------------+-------------------+\n");
    for (int i = 0; i < userCount; i++) {
        if (strstr(users[i].username, searchName) != NULL) {
            printf("| %-18lld | %-18s | %-24s | %-17s |\n",
            	users[i].id,        
                users[i].username,
                users[i].email,
                users[i].phone);
            flag = 1;
        }
    }
    printf("+--------------------+--------------------+--------------------------+-------------------+");
    if (!flag) {
        printf("\nKhong tim thay nguoi dung nao!\n");
    } else {
        printf("\nDa tim thay nguoi dung\n");
    }
}

void searchUserById() {
	long long int searchId;
	printf("\nNhap ID nguoi dung muon tim kiem: ");
	scanf("%lld", &searchId);
	char searchIdStr[20]; 
    sprintf(searchIdStr, "%lld", searchId);
    
	int flag = 0;
    printf("\nKet qua tim kiem:\n");
    printf("+--------------------+--------------------+--------------------------+-------------------+\n");
    printf("|        ID          | Ten nguoi dung     | Email                    | So dien thoai     |\n");
    printf("+--------------------+--------------------+--------------------------+-------------------+\n");
    for (int i = 0; i < userCount; i++) {
    	char userIdStr[20];
        sprintf(userIdStr, "%lld", users[i].id);
        if (strstr(userIdStr, searchIdStr) != NULL) {
            printf("| %-18lld | %-18s | %-24s | %-17s |\n",
            	users[i].id,        
                users[i].username,
                users[i].email,
                users[i].phone );
            flag = 1;
        }
    }
    printf("+--------------------+--------------------+--------------------------+-------------------+\n");
    if (!flag) {
        printf("\nKhong tim thay ID nguoi dung nao!\n");
    } else {
        printf("\nDa tim thay ID nguoi dung\n");
    }
}

// Ham menu
void mainMenu() {
	loadUsersFromFile("users.txt");
    int choice;
    while(1) {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
            	system("cls");
                displayUsers();
                printf("\nNhan Enter de quay lai menu chinh\n");
        		getchar(); 
                break;
            case 2:
            	system("cls");
                addUsers();
                printf("\nNhan Enter de quay lai menu chinh\n");
                break;
            case 3:
            	system("cls");
                searchUserByName();
                printf("\nNhan Enter de quay lai menu chinh\n");
        		getchar(); 
                break;
            case 4:
            	system("cls");
                searchUserById();
                printf("\nNhan Enter de quay lai menu chinh\n");
        		getchar(); 
                break;
            case 5:
            	system("cls");
            	statusUsers();
            	printf("\nNhan Enter de quay lai menu chinh\n");
        		getchar(); 
                break;
            case 6:
            	system("cls");
            	childMenu();
                printf("\nNhan Enter de quay lai menu chinh\n");
                getchar();
                break;
            case 7:
                printf("\n  Thoat chuong trinh\n");
                printf("--->>Nhan Enter de thoat\n");
                printf(" \n======== Thank You ========\n");
                printf("======== See You Again =======");
        		getchar();
                return;
            default:
            	system("cls");
                printf("\nLua chon khong hop le. Vui long chon lai\n");
        }
        	getchar();
    }
}

//Ham mo khoa (khoa) tai khoan nguoi dung
void statusUsers() {
    long long searchId;
    int flag = 0;
    printf("\nNhap ID nguoi dung muon khoa (Mo khoa): ");
    scanf("%lld", &searchId);
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == searchId) {
            flag = 1;
            printf("\nNguoi dung hien tai dang o trang thai: %s\n", users[i].status);
            if (strcmp(users[i].status, "open") == 0) {
                printf("Ban co muon khoa nguoi dung nay? (Y or N): ");
                char confirm;
                getchar();
                scanf("%c", &confirm);
                if (confirm == 'y' || confirm == 'Y') {
                    strcpy(users[i].status, "locked");
                    printf("\nTai khoan nguoi dung da bi khoa thanh cong\n");
                } else {
                    printf("\nHuy thao tac khoa tai khoan\n");
                }
            } else if (strcmp(users[i].status, "locked") == 0) {
                printf("Ban co muon mo khoa nguoi dung nay? (Y or N): ");
                char confirm;
                getchar(); 
                scanf("%c", &confirm);
                if (confirm == 'y' || confirm == 'Y') {
                    strcpy(users[i].status, "open");
                    printf("\nTai khoan nguoi dung da duoc mo khoa thanh cong\n");
                } else {
                    printf("\nHuy thao tac mo khoa tai khoan\n");
                }
            }
            saveUsersToFile("users.txt");
            break;
        }
    }
    if (!flag) {
        printf("\nID nguoi dung khong ton tai!\n");
    }
}

// Ham xap xep nguoi dung
void bubbleSortByName(int ascending) {
		for (int i = 0; i < userCount - 1; i++) {
        	for (int j = 0; j < userCount - i - 1; j++) {
            	int compareResult = strcmp(users[j].username, users[j + 1].username) > 0;
        		//Dao nguoc dieu kien neu sap xep tu z den a
        		if (!ascending) {
                	compareResult = !compareResult;
            	}
            	// Doi cho neu khong dung thu tu
            	if (compareResult) {
                	User temp = users[j];
                	users[j] = users[j + 1];
                	users[j + 1] = temp;
            	}
        	}
    	}
    	printf("\nDanh sach nguoi dung da duoc sap xep thanh cong\n");
    	saveUsersToFile("users.txt");
    	displayUsers(); 
}

//Ham menu con
void childMenu() {
	int childChoice;
	printf("\n=== Sap xep danh sach nguoi dung theo ten ===\n");
	printf("[1] Sap xep tu A - Z\n");
	printf("[2] Sap xep tu Z - A\n");
	printf("[0] Quay lai man hinh chinh\n");
	printf("\nLua chon cua ban: ");
	scanf("%d", &childChoice);
	if (childChoice == 1) {
        bubbleSortByName(1);
        printf("\nDa sap xep danh sach theo ten tu A - Z.\n");
    } else if (childChoice == 2) {
    	bubbleSortByName(0);
        printf("\nDa sap xep danh sach theo ten tu Z - A.\n");
	} else if (childChoice == 0) {
        printf("\nQuay lai menu chinh.\n");
    } else {
        printf("\nLua chon khong hop le. Vui long chon lai.\n");
    }
}

// Ham doc du lieu tu file
void loadUsersFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("\nKhong the mo file '%s'. Vui long kiem tra lai.\n", filename);
        return;
    }
    userCount = 0; 
    while (fscanf(file, "%lld, %s, %s, %s, %s, %s\n",
                  &users[userCount].id,
                  users[userCount].username,
                  users[userCount].email,
                  users[userCount].phone,
                  users[userCount].password,
                  users[userCount].status) == 6) {
        userCount++;
        if (userCount >= 100) {
            printf("\nDa dat gioi han toi da (100 nguoi dung).\n");
            break;
        }
    }

    fclose(file);
    printf("\nDa tai thanh cong %d nguoi dung tu file '%s'.\n", userCount, filename);
    
    if (userCount == 0) {
    printf("\nKhong co nguoi dung trong danh sach. Vui long kiem tra file du lieu.\n");
    return;
	}
	if (file == NULL) {
    printf("\nLoi: File du lieu khong ton tai hoac khong the mo.\n");
    return;
	}
}

// Ham ghi du lieu nguoi dung vao file
void saveUsersToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("\nKhong the ghi vao file '%s'. Vui long kiem tra quyen truy cap.\n", filename);
        return;
    }
    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%lld, %s, %s, %s, %s, %s\n",
                users[i].id,
                users[i].username,
                users[i].email,
                users[i].phone,
                users[i].password,
                users[i].status);
    }
    fclose(file);
    printf("\nDa luu danh sach nguoi dung vao file '%s'.\n", filename);
}
