#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Global variables
int main_exit;

// Structure definitions
struct date {
    int month, day, year;
};

struct account {
    char name[60];
    int acc_no, age;
    char address[60];
    char citizenship[15];
    double phone;
    char acc_type[10];
    float amt;
    struct date dob;
    struct date deposit;
    struct date withdraw;
};

// Function prototypes
void menu();
void new_acc();
void edit();
void delete_acc();
void view_acc_details();
void deposit();
void withdraw();

// Function to clear the input buffer
void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to display menu
void menu() {
    int choice;
    printf("\n\n\t\t\tCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM");
    printf("\n\n\t\t\t      WELCOME TO THE MENU\n\n");
    printf("\t1. Create new account\n");
    printf("\t2. Update information of existing account\n");
    printf("\t3. Delete existing account\n");
    printf("\t4. View account details\n");
    printf("\t5. Deposit\n");
    printf("\t6. Withdraw\n");
    printf("\t7. Exit\n\n");
    printf("\tEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            new_acc();
            break;
        case 2:
            edit();
            break;
        case 3:
            delete_acc();
            break;
        case 4:
            view_acc_details();
            break;
        case 5:
            deposit();
            break;
        case 6:
            withdraw();
            break;
        case 7:
            exit(0);
        default:
            printf("\nInvalid choice! Please enter a valid option.\n");
            menu();
    }
}

// Function to create a new account
void new_acc() {
    FILE *ptr;
    struct account user;
    ptr = fopen("record.dat", "ab+");
    if (ptr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    printf("\n\n\t\t\tADD RECORD\n\n");
    printf("Enter today's date (mm/dd/yyyy): ");
    scanf("%d/%d/%d", &user.deposit.month, &user.deposit.day, &user.deposit.year);

    // Input account details
    printf("Enter the account number: ");
    scanf("%d", &user.acc_no);
    printf("Enter the name: ");
    clear_buffer();
    fgets(user.name, sizeof(user.name), stdin);
    user.name[strcspn(user.name, "\n")] = '\0';  // Remove trailing newline
    printf("Enter the date of birth (mm/dd/yyyy): ");
    scanf("%d/%d/%d", &user.dob.month, &user.dob.day, &user.dob.year);
    // Input other details similarly

    // Write account details to file
    fwrite(&user, sizeof(user), 1, ptr);
    fclose(ptr);
    printf("\nAccount created successfully!\n");
    printf("\nEnter any key to return to main menu: ");
    clear_buffer();
    getchar();
    menu();
}

// Function to edit account information
void edit() {
    FILE *ptr;
    int found = 0;
    struct account user;
    int account_no;
    ptr = fopen("record.dat", "rb+");
    if (ptr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    printf("\n\n\t\t\tEDIT ACCOUNT\n\n");
    printf("Enter account number of the customer: ");
    scanf("%d", &account_no);
    rewind(ptr);
    while (fread(&user, sizeof(user), 1, ptr) == 1) {
        if (user.acc_no == account_no) {
            printf("\nAccount Found!\n");
            printf("Enter new name: ");
            clear_buffer();
            fgets(user.name, sizeof(user.name), stdin);
            user.name[strcspn(user.name, "\n")] = '\0';  // Remove trailing newline
            fseek(ptr, -sizeof(user), SEEK_CUR);
            fwrite(&user, sizeof(user), 1, ptr);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Account not found!\n");
    }
    fclose(ptr);
    printf("\nEnter any key to return to main menu: ");
    clear_buffer();
    getchar();
    menu();
}

// Function to delete an account
void delete_acc() {
    FILE *ptr, *tmp;
    struct account user;
    int account_no;
    ptr = fopen("record.dat", "rb");
    if (ptr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    tmp = fopen("temp.dat", "wb");
    if (tmp == NULL) {
        printf("Error creating temporary file!\n");
        exit(1);
    }
    printf("\n\n\t\t\tDELETE ACCOUNT\n\n");
    printf("Enter account number of the customer to delete: ");
    scanf("%d", &account_no);
    rewind(ptr);
    while (fread(&user, sizeof(user), 1, ptr) == 1) {
        if (user.acc_no != account_no) {
            fwrite(&user, sizeof(user), 1, tmp);
        }
    }
    fclose(ptr);
    fclose(tmp);
    remove("record.dat");
    rename("temp.dat", "record.dat");
    printf("\nAccount deleted successfully!\n");
    printf("\nEnter any key to return to main menu: ");
    clear_buffer();
    getchar();
    menu();
}

// Function to view account details
void view_acc_details() {
    FILE *ptr;
    struct account user;
    int account_no;
    ptr = fopen("record.dat", "rb");
    if (ptr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    printf("\n\n\t\t\tVIEW ACCOUNT DETAILS\n\n");
    printf("Enter account number of the customer: ");
    scanf("%d", &account_no);
    rewind(ptr);
    while (fread(&user, sizeof(user), 1, ptr) == 1) {
        if (user.acc_no == account_no) {
            printf("\nAccount Found!\n");
            printf("Name: %s\n", user.name);
            // Print other details similarly
            fclose(ptr);
            printf("\nEnter any key to return to main menu: ");
            clear_buffer();
            getchar();
            menu();
            return;
        }
    }
    printf("Account not found!\n");
    fclose(ptr);
    printf("\nEnter any key to return to main menu: ");
    clear_buffer();
    getchar();
    menu();
}

// Function to deposit money into an account
void deposit() {
    FILE *ptr;
    int found = 0;
    struct account user;
    int account_no;
    float amount;
    ptr = fopen("record.dat", "rb+");
    if (ptr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    printf("\n\n\t\t\tDEPOSIT AMOUNT\n\n");
    printf("Enter account number of the customer: ");
    scanf("%d", &account_no);
    rewind(ptr);
    while (fread(&user, sizeof(user), 1, ptr) == 1) {
        if (user.acc_no == account_no) {
            printf("\nAccount Found!\n");
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            user.amt += amount;
            fseek(ptr, -sizeof(user), SEEK_CUR);
            fwrite(&user, sizeof(user), 1, ptr);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Account not found!\n");
    }
    fclose(ptr);
    printf("\nEnter any key to return to main menu: ");
    clear_buffer();
    getchar();
    menu();
}

// Function to withdraw money from an account
void withdraw() {
    FILE *ptr;
    int found = 0;
    struct account user;
    int account_no;
    float amount;
    ptr = fopen("record.dat", "rb+");
    if (ptr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    printf("\n\n\t\t\tWITHDRAW AMOUNT\n\n");
    printf("Enter account number of the customer: ");
    scanf("%d", &account_no);
    rewind(ptr);
    while (fread(&user, sizeof(user), 1, ptr) == 1) {
        if (user.acc_no == account_no) {
            printf("\nAccount Found!\n");
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            if (amount > user.amt) {
                printf("Insufficient balance!\n");
            } else {
                user.amt -= amount;
                fseek(ptr, -sizeof(user), SEEK_CUR);
                fwrite(&user, sizeof(user), 1, ptr);
                found = 1;
            }
            break;
        }
    }
    if (!found) {
        printf("Account not found!\n");
    }
    fclose(ptr);
    printf("\nEnter any key to return to main menu: ");
    clear_buffer();
    getchar();
    menu();
}

// Main function
int main() {
    menu();
    return 0;
}
