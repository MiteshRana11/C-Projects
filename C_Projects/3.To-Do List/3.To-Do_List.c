#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Task{
    int id;
    char task[100];
};

void addTask();
void viewTasks();
void deleteTask();

int main(){

    int choice;

    while(1){

        printf("\n===== TODO LIST MANAGER =====\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Delete Task\n");
        printf("4. Exit\n");

        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice){

            case 1:
                addTask();
                break;

            case 2:
                viewTasks();
                break;

            case 3:
                deleteTask();
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
}

void addTask(){

    FILE *fp;
    struct Task t;

    fp=fopen("tasks.txt","a");

    printf("Enter Task ID: ");
    scanf("%d",&t.id);

    printf("Enter Task Description: ");
    scanf(" %[^\n]",t.task);

    fwrite(&t,sizeof(t),1,fp);

    fclose(fp);

    printf("Task added successfully\n");
}

void viewTasks(){

    FILE *fp;
    struct Task t;

    fp=fopen("tasks.txt","r");

    if(fp==NULL){
        printf("No tasks available\n");
        return;
    }

    printf("\nID\tTask\n");
    printf("----------------------------\n");

    while(fread(&t,sizeof(t),1,fp)){
        printf("%d\t%s\n",t.id,t.task);
    }

    fclose(fp);
}

void deleteTask(){

    FILE *fp,*temp;
    struct Task t;
    int id,found=0;

    fp=fopen("tasks.txt","r");
    temp=fopen("temp.txt","w");

    printf("Enter Task ID to delete: ");
    scanf("%d",&id);

    while(fread(&t,sizeof(t),1,fp)){

        if(t.id==id){
            found=1;
            printf("Task deleted\n");
        }
        else{
            fwrite(&t,sizeof(t),1,temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("tasks.txt");
    rename("temp.txt","tasks.txt");

    if(!found)
        printf("Task not found\n");
}