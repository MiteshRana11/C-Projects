#include <stdio.h>

float add(float a, float b){
    return a+b;
}

float subtract(float a, float b){
    return a-b;
}

float multiply(float a, float b){
    return a*b;
}

float divide(float a, float b){
    return a/b;
}

int modulus(int a, int b){
    return a%b;
}

int main(){

    int choice;
    float num1,num2;

    while(1){

        printf("\n===== SIMPLE CALCULATOR =====\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Division\n");
        printf("5. Modulus\n");
        printf("6. Exit\n");

        printf("Enter choice: ");
        scanf("%d",&choice);

        if(choice==6){
            printf("Exiting calculator...\n");
            break;
        }

        printf("Enter two numbers: ");
        scanf("%f %f",&num1,&num2);

        switch(choice){

            case 1:
                printf("Result = %.2f\n", add(num1,num2));
                break;

            case 2:
                printf("Result = %.2f\n", subtract(num1,num2));
                break;

            case 3:
                printf("Result = %.2f\n", multiply(num1,num2));
                break;

            case 4:
                if(num2!=0)
                    printf("Result = %.2f\n", divide(num1,num2));
                else
                    printf("Division by zero not allowed\n");
                break;

            case 5:
                printf("Result = %d\n", modulus((int)num1,(int)num2));
                break;

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}