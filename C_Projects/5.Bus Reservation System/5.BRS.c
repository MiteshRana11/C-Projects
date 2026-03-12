#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Booking {
    int seatNo;
    char name[50];
};

int seats[20] = {0};

void viewSeats();
void bookTicket();
void viewBookings();
void cancelTicket();

int main()
{
    int choice;

    while(1)
    {
        printf("\n===== BUS RESERVATION SYSTEM =====\n");
        printf("1. View Seats\n");
        printf("2. Book Ticket\n");
        printf("3. View Bookings\n");
        printf("4. Cancel Ticket\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                viewSeats();
                break;

            case 2:
                bookTicket();
                break;

            case 3:
                viewBookings();
                break;

            case 4:
                cancelTicket();
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
}

void viewSeats()
{
    printf("\nSeat Status\n");

    for(int i=0;i<20;i++)
    {
        if(seats[i]==0)
            printf("Seat %d : Available\n",i+1);
        else
            printf("Seat %d : Booked\n",i+1);
    }
}

void bookTicket()
{
    FILE *fp;
    struct Booking b;
    int seat;

    fp=fopen("booking.txt","a");

    printf("Enter Seat Number (1-20): ");
    scanf("%d",&seat);

    if(seat<1 || seat>20)
    {
        printf("Invalid seat number\n");
        return;
    }

    if(seats[seat-1]==1)
    {
        printf("Seat already booked\n");
        return;
    }

    printf("Enter Passenger Name: ");
    scanf("%s",b.name);

    b.seatNo=seat;
    seats[seat-1]=1;

    fwrite(&b,sizeof(b),1,fp);

    fclose(fp);

    printf("Ticket Booked Successfully!\n");
}

void viewBookings()
{
    FILE *fp;
    struct Booking b;

    fp=fopen("booking.txt","r");

    if(fp==NULL)
    {
        printf("No bookings yet\n");
        return;
    }

    printf("\nSeat\tPassenger\n");
    printf("----------------------\n");

    while(fread(&b,sizeof(b),1,fp))
    {
        printf("%d\t%s\n",b.seatNo,b.name);
    }

    fclose(fp);
}

void cancelTicket()
{
    FILE *fp,*temp;
    struct Booking b;
    int seat,found=0;

    fp=fopen("booking.txt","r");
    temp=fopen("temp.txt","w");

    printf("Enter seat number to cancel: ");
    scanf("%d",&seat);

    while(fread(&b,sizeof(b),1,fp))
    {
        if(b.seatNo==seat)
        {
            seats[seat-1]=0;
            found=1;
            printf("Booking cancelled\n");
        }
        else
        {
            fwrite(&b,sizeof(b),1,temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("booking.txt");
    rename("temp.txt","booking.txt");

    if(!found)
        printf("Seat booking not found\n");
}