#include<stdbool.h>

typedef struct {
	long long int id;
	char email[50];
    char username[50];
    char phone[50];
    char password[50];
    char status[10];
} User;
User users[100];
int userCount;
