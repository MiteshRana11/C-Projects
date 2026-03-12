#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accNo;
    char name[50];
    float balance;
};

void createAccount();
void depositMoney();
void withdrawMoney();
void checkAccount();
void viewAccounts();

int main()
{
    int choice;

    while(1)
    {
        printf("\n===== BANK MANAGEMENT SYSTEM =====\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Account Details\n");
        printf("5. View All Accounts\n");
        printf("6. Exit\n");

        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                createAccount();
                break;

            case 2:
                depositMoney();
                break;

            case 3:
                withdrawMoney();
                break;

            case 4:
                checkAccount();
                break;

            case 5:
                viewAccounts();
                break;

            case 6:
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
}

void createAccount()
{
    FILE *fp;
    struct Account acc;

    fp = fopen("accounts.txt","a");

    printf("Enter Account Number: ");
    scanf("%d",&acc.accNo);

    printf("Enter Name: ");
    scanf("%s",acc.name);

    printf("Enter Initial Balance: ");
    scanf("%f",&acc.balance);

    fwrite(&acc,sizeof(acc),1,fp);

    fclose(fp);

    printf("Account Created Successfully!\n");
}

void depositMoney()
{
    FILE *fp,*temp;
    struct Account acc;
    int accNo,found=0;
    float amount;

    fp = fopen("accounts.txt","r");
    temp = fopen("temp.txt","w");

    printf("Enter Account Number: ");
    scanf("%d",&accNo);

    printf("Enter Amount to Deposit: ");
    scanf("%f",&amount);

    while(fread(&acc,sizeof(acc),1,fp))
    {
        if(acc.accNo==accNo)
        {
            acc.balance += amount;
            found=1;
            printf("Deposit Successful!\n");
        }

        fwrite(&acc,sizeof(acc),1,temp);
    }

    fclose(fp);
    fclose(temp);

    remove("accounts.txt");
    rename("temp.txt","accounts.txt");

    if(!found)
        printf("Account not found!\n");
}

void withdrawMoney()
{
    FILE *fp,*temp;
    struct Account acc;
    int accNo,found=0;
    float amount;

    fp = fopen("accounts.txt","r");
    temp = fopen("temp.txt","w");

    printf("Enter Account Number: ");
    scanf("%d",&accNo);

    printf("Enter Amount to Withdraw: ");
    scanf("%f",&amount);

    while(fread(&acc,sizeof(acc),1,fp))
    {
        if(acc.accNo==accNo)
        {
            if(acc.balance >= amount)
            {
                acc.balance -= amount;
                printf("Withdrawal Successful!\n");
            }
            else
            {
                printf("Insufficient Balance!\n");
            }

            found=1;
        }

        fwrite(&acc,sizeof(acc),1,temp);
    }

    fclose(fp);
    fclose(temp);

    remove("accounts.txt");
    rename("temp.txt","accounts.txt");

    if(!found)
        printf("Account not found!\n");
}

void checkAccount()
{
    FILE *fp;
    struct Account acc;
    int accNo,found=0;

    fp = fopen("accounts.txt","r");

    printf("Enter Account Number: ");
    scanf("%d",&accNo);

    while(fread(&acc,sizeof(acc),1,fp))
    {
        if(acc.accNo==accNo)
        {
            printf("\nAccount Found\n");
            printf("Account No: %d\n",acc.accNo);
            printf("Name: %s\n",acc.name);
            printf("Balance: %.2f\n",acc.balance);
            found=1;
            break;
        }
    }

    fclose(fp);

    if(!found)
        printf("Account not found!\n");
}

void viewAccounts()
{
    FILE *fp;
    struct Account acc;

    fp = fopen("accounts.txt","r");

    if(fp==NULL)
    {
        printf("No accounts available\n");
        return;
    }

    printf("\nAccountNo\tName\tBalance\n");
    printf("---------------------------------\n");

    while(fread(&acc,sizeof(acc),1,fp))
    {
        printf("%d\t%s\t%.2f\n",acc.accNo,acc.name,acc.balance);
    }

    fclose(fp);
}