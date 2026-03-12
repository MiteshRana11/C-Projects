#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char name[50];
    char author[50];
};

void addBook();
void viewBooks();
void searchBook();

int main() {
    int choice;

    while(1) {
        printf("\n===== LIBRARY MANAGEMENT SYSTEM =====\n");
        printf("1. Add Book\n");
        printf("2. View Books\n");
        printf("3. Search Book\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addBook();
                break;
            case 2:
                viewBooks();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid Choice!\n");
        }
    }
}

void addBook() {
    struct Book b;
    FILE *fp;

    fp = fopen("books.dat", "ab");

    printf("Enter Book ID: ");
    scanf("%d", &b.id);

    printf("Enter Book Name: ");
    scanf(" %[^\n]", b.name);

    printf("Enter Author Name: ");
    scanf(" %[^\n]", b.author);

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);

    printf("Book Added Successfully!\n");
}

void viewBooks() {
    struct Book b;
    FILE *fp;

    fp = fopen("books.dat", "rb");

    if(fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("\nID\tName\tAuthor\n");
    printf("----------------------------\n");

    while(fread(&b, sizeof(b), 1, fp)) {
        printf("%d\t%s\t%s\n", b.id, b.name, b.author);
    }

    fclose(fp);
}

void searchBook() {
    struct Book b;
    FILE *fp;
    int id, found = 0;

    printf("Enter Book ID to search: ");
    scanf("%d", &id);

    fp = fopen("books.dat", "rb");

    while(fread(&b, sizeof(b), 1, fp)) {
        if(b.id == id) {
            printf("Book Found!\n");
            printf("ID: %d\n", b.id);
            printf("Name: %s\n", b.name);
            printf("Author: %s\n", b.author);
            found = 1;
            break;
        }
    }

    if(!found)
        printf("Book Not Found!\n");

    fclose(fp);
}