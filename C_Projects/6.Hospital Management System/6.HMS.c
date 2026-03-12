#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
};

void addPatient();
void viewPatients();
void searchPatient();
void deletePatient();

int main() {

    int choice;

    while(1) {

        printf("\n===== HOSPITAL MANAGEMENT SYSTEM =====\n");
        printf("1. Add Patient\n");
        printf("2. View Patients\n");
        printf("3. Search Patient\n");
        printf("4. Delete Patient\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                addPatient();
                break;

            case 2:
                viewPatients();
                break;

            case 3:
                searchPatient();
                break;

            case 4:
                deletePatient();
                break;

            case 5:
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

void addPatient() {

    FILE *fp;
    struct Patient p;

    fp = fopen("patients.txt","a");

    printf("\nEnter Patient ID: ");
    scanf("%d",&p.id);

    printf("Enter Name: ");
    scanf("%s",p.name);

    printf("Enter Age: ");
    scanf("%d",&p.age);

    printf("Enter Disease: ");
    scanf("%s",p.disease);

    fwrite(&p,sizeof(p),1,fp);

    fclose(fp);

    printf("\nPatient Added Successfully!\n");
}

void viewPatients() {

    FILE *fp;
    struct Patient p;

    fp = fopen("patients.txt","r");

    if(fp == NULL)
    {
        printf("No records found!\n");
        return;
    }

    printf("\nID\tName\tAge\tDisease\n");
    printf("------------------------------------\n");

    while(fread(&p,sizeof(p),1,fp))
    {
        printf("%d\t%s\t%d\t%s\n",p.id,p.name,p.age,p.disease);
    }

    fclose(fp);
}

void searchPatient() {

    FILE *fp;
    struct Patient p;
    int id,found=0;

    fp = fopen("patients.txt","r");

    printf("\nEnter Patient ID to search: ");
    scanf("%d",&id);

    while(fread(&p,sizeof(p),1,fp))
    {
        if(p.id == id)
        {
            printf("\nPatient Found\n");
            printf("ID: %d\n",p.id);
            printf("Name: %s\n",p.name);
            printf("Age: %d\n",p.age);
            printf("Disease: %s\n",p.disease);
            found=1;
            break;
        }
    }

    if(!found)
        printf("Patient not found!\n");

    fclose(fp);
}

void deletePatient() {

    FILE *fp,*temp;
    struct Patient p;
    int id,found=0;

    fp = fopen("patients.txt","r");
    temp = fopen("temp.txt","w");

    printf("\nEnter Patient ID to delete: ");
    scanf("%d",&id);

    while(fread(&p,sizeof(p),1,fp))
    {
        if(p.id == id)
        {
            found=1;
            printf("Patient record deleted.\n");
        }
        else
        {
            fwrite(&p,sizeof(p),1,temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("patients.txt");
    rename("temp.txt","patients.txt");

    if(!found)
        printf("Patient not found!\n");
}