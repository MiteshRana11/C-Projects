//import the header files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Create a Function for Genrate a Random Number's
int genrateRandomNumber(int n)
{
    srand(time(NULL));
    return rand() % n;
}

//Create a Function for Chek the Condtion Who is greate (R,P,S)
int greter(char char1, char char2)
{
    if (char1 == char2)
    {
        return -1;
    }
    else if ((char1 == 'R') && (char2 == 'S'))
    {
        return 1;
    }
    else if ((char2 == 'R') && (char1 == 'S'))
    {
        return 0;
    }
    else if ((char1 == 'P') && (char2 == 'R'))
    {
        return 1;
    }
    else if ((char2 == 'P') && (char1 == 'R'))
    {
        return 0;
    }
    else if ((char1 == 'S') && (char2 == 'P'))
    {
        return 1;
    }
    else if ((char2 == 'S') && (char1 == 'P'))
    {
        return 0;
    }
}

int main()
{
    int playerScore = 0, compScore = 0, temp;
    char playerChar, compChar;
    char dict[] = {'R', 'P', 'S'};
    printf("\t\t\t\t\t***********************************************\n\n\t\t\t\t\t  Welcome To The Rock, Paper And Scissor Game\n\n\t\t\t\t\t***********************************************\n");
    printf("Condition's is --> \nThis Game Plays Between The User and CPU. \nTotal Three Rounds in This Game. \nThis Game is OnlY For Fun\n");
    for (int i = 0; i < 3; i++)
    {

        printf("\nUser Turn -->\n");
        printf("Chose Your Option\n1. R For Rock\n2. P For Paper\n3. S For Scissor\nYou Want Enter The Value Between The 1 To 3: \n");
        scanf("%d", &temp);
        getchar();
        playerChar = dict[temp - 1];
        printf("You Choose %c\n", playerChar);

        printf("Cumputers Turn --> \n");
        printf("Chose Your Option\n1. R For Rock\n2. P For Paper\n3. S For Scissor\n");
        temp = genrateRandomNumber(3) + 1;
        compChar = dict[temp - 1];
        printf("CPU Choose %c\n", compChar);

        // Compare the score
        if (greter(compChar, playerChar) == 1)
        {
            compScore += 1;
            printf("CPU Got One Point...\n");
        }
        else if (greter(compChar, playerChar) == -1)
        {
            compScore += 1;
            playerScore += 1;
            printf("It's Draw\n");
        }
        else
        {
            playerScore += 1;
            printf("You Got One Point...\n");
        }
        printf("Score is --> You: %d CPU: %d\n", playerScore, compScore);
        
    }
    
    if (playerScore > compScore)
    {
        printf("****** Congrutalations, You Won The Game ******\n");
    }
    else if (playerScore < compScore)
    {
        printf("****** Sorry, CPU Won The Game ******\n");
        printf(" Try Again......\n");
    }
    else
    {
        printf("It's a Draw!\n");
    }
    return 0;
}
