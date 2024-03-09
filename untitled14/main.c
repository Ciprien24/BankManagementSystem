#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
int i, j ;
int main_exit;
//Function prototypes
void closed();
void fordelay(int j);
void menu();
void new_acc();
void edit();
void transcat();
void see();
void erase();
void view_list();
struct date{
    int month, day, year;
};
struct{
    char name[60];
    int acc_no, age;
    char adress[60];
    char citizenship[15];
    double phone;
    char acc_type[10];
    float amt;
    struct date dob;
    struct date deposit;
    struct date withdraw;


}add, upd, check, rem, transaction;
unsigned int sec = 0;
clock_t stopclock = CLOCKS_PER_SEC;

void main(){
    char pass[15], password[15] = 'iamlearning';
    int i = 0 ;
    printf("\n\n\t Enter the passworkd to login: ");
    printf("\033[8m");
    scanf("%s", pass);
    printf("\033c");
    if(strcmp(pass,password)==0){
        printf("\n\n Password match ! Loading");
        system ("clear");
        fordelay(5);
        menu();

    }
    else{
        printf("\033c");
        printf("\n\n Wrong Password ! ! !");
        login_try :
        printf("\n Enter 1 to try again and 0 to exit :");
        scanf("%d", &main_exit);
        if (main_exit == 1){
            system("clear");
            main();
        }
        else if(main_exit==0){
            closed();
        }
    }

}
void menu(){
    int choice;
    printf("\033c");
    system ("clear");
    printf ("\n");
    printf("\33[1;31m");
    printf("\n\n\t\t\t COSTUMER ACCOUNT BANKING MANAGEMENT SYSTEM");
    printf("\n\n\n\t\t       \033[1;32m WELCOME TO THE MENU   ");
    printf("\033[0m");
    printf("\033[1;33m");
    printf("\n\n\t\t 1.Create new account \n\t2.updateinformation of existing account \n\t3.For transaction \n\t4.check the details of existing account \n\t5.Remove existing account \n\t6.View costumer's list \n\t7.Exit \n\n\n\n\t\t Enter your choice :  ");
scanf("%d", &choice);
system("clear");
printf("\033c");
switch( choice){
    case 1:new_acc();
    break;
    case 2:edit();
    break;
    case 3:transcat();
    break;
    case 4: see();
    break ;
    case 5:erase();
    break;
    case 6:view_list();
    break;
    case 7:closed();
    break;
}
}
void fordelay(int j) {
    while (sec < j) {


        if (clock() > stopclock) {
            stopclock += 1000000;
            printf(".");
            fflush(stdout);
            sec++;
        }
    }
}
void new_acc(){
    int choice;
    FILE *ptr;
    ptr = fopen("record.dat", "a+");
    account_no:
    system("clear");
    printf("\t\t\t       ADD RECORD");
    printf("\n\n\n Enter today's date (mm/dd/yyyy) :");
    scanf("%d%d%d",&add.deposit.month,&add.deposit.day,&add.deposit.year );
    printf("Enter the account number:");
    while(fscanf(ptr, "%d %s %d/%d/%d %d %s %s %s %lf %s %f %d/%d/%d \n ", &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.adress, add.citizenship, &add.phone, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day,&add.deposit.year)!=EOF)
    {
        if(check.acc_no==add.acc_no)
        {
            printf("Account no .already in use !");
            goto account_no;
        }
    }
add.acc_no = check.acc_no;
    printf("\n Enter the name: ");
    scanf("%s", add.name);
    printf("\n Enter the date of birth (mm/dd/yyyy)");
    scanf("%d/%d/%d", &add.dob.month,&add.dob.day, &add.dob.year);
    printf("\n Enter the age :");
    scanf("%d", &add.age);
    printf("\n Enter the address: ");
    scanf("%s", add.adress);
    printf("\n Enter the citizenship number : ");
    scanf("%s", &add.citizenship);
    printf("\n Enter phone number :");
    scanf("%lf", &add.amt);
    printf("\n Type of account : \n\t #Saving \n\t #Current \n\t #Fixed(for 1 year) \n\t #Fixed2(for 2 years) \n\t #Fixed3(for 3 years)" );
    scanf("%s", add.acc_type);

    fprintf(ptr, "%d %s %d/%d/%d %d %s %s %s %lf %s %f %d/%d/%d \n ", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.adress, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day,add.deposit.year);
    fclose(ptr);
    printf("\n Account created successfully !!");
    add_invalid:
    printf("\n\n\n\t : Enter 1 to go to main menu");
    scanf("%d",&main_exit);
    system("clear");
    if(main_exit==1)
    {
        menu();

    }
    else if(main_exit==0) {
        closed();
    }
    else
    {
        printf("\n Invalid !");
        goto add_invalid;
    }

}
void edit(){
    int choice, test = 0;
    FILE *old, *newrec;
    old = fopen("record.dat","w");
    newrec = fopen("new.dat","w");
    printf("\n Enter the account no of the costumer whose info you want to change : \n");
    scanf("%d",&upd.acc_no);
    while(fscanf(ptr, "%d %s %d/%d/%d %d %s %s %s %lf %s %f %d/%d/%d \n ", &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year, &add.age, add.adress, add.citizenship, &add.phone, add.acc_type, &add.amt, &add.deposit.month, &add.deposit.day,&add.deposit.year)!=EOF)
    {
if(add.acc_no == upd.acc_no){
test = 1;
printf("\n Which information do you want to change ?? : \n 1.Address \n 2.Phone \n\n Enter your choice :");
scanf("%d",&choice);
system("clear");
if(choice == 1){
    printf("Enter Address : ");
    scanf("%s",&upd.adress);
    fprintf(newrec,"%d %s %d/%d/%d %d %s %s %s %lf %s %f %d/%d/%d \n ", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, upd.adress, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day,add.deposit.year);
    system ("clear");
    printf("changes saved !");
}
else if(choice == 2){
    printf("Enter the new phone number: ");
    scanf("%lf",&upd.phone);
    fprintf(newrec,"%d %s %d/%d/%d %d %s %s %s %lf %s %f %d/%d/%d \n ", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.adress, add.citizenship, &upd.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day,add.deposit.year);
    system("clear");
    printf("Changes saved!");
}
else{
    fprintf(newrec,"%d %s %d/%d/%d %d %s %s %s %lf %s %f %d/%d/%d \n ", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.adress, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day,add.deposit.year);

}
}
        fclose(old);
        fclose(newrec);
        remove("record.dat");
        rename("new.dat","record.dat");
        if(test !=1){
            system("clear");
            printf("\n Record not found !!!");
            edit_invalid:
            printf("\n Enter 0 to try again and 1 to return to menu :");
            scanf("%d", &main_exit);
            system("clear");
            if(main_exit==1){
                menu();

            }
        else if(main_exit==2)
            {
            closed();

            }
        }
    }
}
