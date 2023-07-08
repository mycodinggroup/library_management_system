#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

typedef struct {
    char title[100];
    char author[100];
    int year;
    int isAvailable;
} Book;

typedef struct {
    Book books[MAX_BOOKS];
    int count;
} Library;

void initializeLibrary(Library *library) {
    library->count = 0;
}

void addBook(Library *library) {
    if (library->count >= MAX_BOOKS) {
        printf("Library is full. Cannot add more books.\n");
        return;
    }

    Book newBook;

    printf("Enter the title of the book: ");
    scanf(" %[^\n]s", newBook.title);

    printf("Enter the author of the book: ");
    scanf(" %[^\n]s", newBook.author);

    printf("Enter the year of publication: ");
    scanf("%d", &newBook.year);

    newBook.isAvailable = 1;

    library->books[library->count] = newBook;
    library->count++;

    printf("Book added successfully.\n");
}

void displayBooks(Library *library) {
    if (library->count == 0) {
        printf("No books in the library.\n");
        return;
    }

    printf("Books in the library:\n");
    for (int i = 0; i < library->count; i++) {
        printf("Title: %s\n", library->books[i].title);
        printf("Author: %s\n", library->books[i].author);
        printf("Year: %d\n", library->books[i].year);
        printf("Availability: %s\n", library->books[i].isAvailable ? "Available" : "Not Available");
        printf("---------------\n");
    }
}

int searchBook(Library *library, char *title) {
    for (int i = 0; i < library->count; i++) {
        if (strcmp(library->books[i].title, title) == 0) {
            return i;
        }
    }

    return -1;
}

void borrowBook(Library *library) {
    char title[100];

    printf("Enter the title of the book to borrow: ");
    scanf(" %[^\n]s", title);

    int index = searchBook(library, title);
    if (index == -1) {
        printf("Book not found in the library.\n");
        return;
    }

    if (library->books[index].isAvailable) {
        library->books[index].isAvailable = 0;
        printf("Book '%s' borrowed successfully.\n", title);
    } else {
        printf("Book '%s' is not available.\n", title);
    }
}

void returnBook(Library *library) {
    char title[100];

    printf("Enter the title of the book to return: ");
    scanf(" %[^\n]s", title);

    int index = searchBook(library, title);
    if (index == -1) {
        printf("Book not found in the library.\n");
        return;
    }

    if (!library->books[index].isAvailable) {
        library->books[index].isAvailable = 1;
        printf("Book '%s' returned successfully.\n", title);
    } else {
        printf("Book '%s' is already available.\n", title);
    }
}

int main() {
    Library library;
    initializeLibrary(&library);

    int choice;

    while (1) {
        printf("\nLibrary Management System\n");
        printf("-------------------------\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Borrow Book\n");
        printf("4. Return Book\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(&library);
                break;
            case 2:
                displayBooks(&library);
                break;
            case 3:
                borrowBook(&library);
                break;
            case 4:
                returnBook(&library);
                break;
            case 5:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
