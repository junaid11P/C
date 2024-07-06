#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BOOKS 100
#define MAX_USERS 50
#define MAX_BORROWED_BOOKS 5

typedef struct {
    char title[100];
    char author[100];
    char ISBN[13];
    int available;
} Book;

typedef struct {
    char name[100];
    int ID;
    char borrowed_books[MAX_BORROWED_BOOKS][13];
    int num_borrowed;
} User;

Book library[MAX_BOOKS];
User users[MAX_USERS];
int num_books = 0;
int num_users = 0;

void add_book() {
    if (num_books >= MAX_BOOKS) {
        printf("Library is full. Cannot add more books.\n");
        return;
    }
    Book new_book;
    printf("Enter title: ");
    scanf("%s", new_book.title);
    printf("Enter author: ");
    scanf("%s", new_book.author);
    printf("Enter ISBN: ");
    scanf("%s", new_book.ISBN);
    new_book.available = 1;
    library[num_books++] = new_book;
    printf("Book added successfully.\n");
}

void remove_book() {
    char ISBN[13];
    printf("Enter ISBN of the book to remove: ");
    scanf("%s", ISBN);
    for (int i = 0; i < num_books; i++) {
        if (strcmp(library[i].ISBN, ISBN) == 0) {
            library[i] = library[num_books - 1];
            num_books--;
            printf("Book removed successfully.\n");
            return;
        }
    }
    printf("Book not found.\n");
}

void search_book_by_title() {
    char title[100];
    printf("Enter title of the book to search: ");
    scanf("%s", title);
    for (int i = 0; i < num_books; i++) {
        if (strcmp(library[i].title, title) == 0) {
            printf("Book found: %s by %s (ISBN: %s)\n", library[i].title, library[i].author, library[i].ISBN);
            return;
        }
    }
    printf("Book not found.\n");
}

void add_user() {
    if (num_users >= MAX_USERS) {
        printf("User limit reached. Cannot add more users.\n");
        return;
    }
    User new_user;
    printf("Enter name: ");
    scanf("%s", new_user.name);
    printf("Enter ID: ");
    scanf("%d", &new_user.ID);
    new_user.num_borrowed = 0;
    users[num_users++] = new_user;
    printf("User added successfully.\n");
}

void search_user_by_ID() {
    int ID;
    printf("Enter user ID to search: ");
    scanf("%d", &ID);
    for (int i = 0; i < num_users; i++) {
        if (users[i].ID == ID) {
            printf("User found: %s (ID: %d)\n", users[i].name, users[i].ID);
            return;
        }
    }
    printf("User not found.\n");
}

void borrow_book() {
    int user_ID;
    char ISBN[13];
    printf("Enter user ID: ");
    scanf("%d", &user_ID);
    printf("Enter ISBN of the book to borrow: ");
    scanf("%s", ISBN);

    User *user = NULL;
    for (int i = 0; i < num_users; i++) {
        if (users[i].ID == user_ID) {
            user = &users[i];
            break;
        }
    }

    if (user == NULL) {
        printf("User not found.\n");
        return;
    }

    if (user->num_borrowed >= MAX_BORROWED_BOOKS) {
        printf("User has already borrowed the maximum number of books.\n");
        return;
    }

    Book *book = NULL;
    for (int i = 0; i < num_books; i++) {
        if (strcmp(library[i].ISBN, ISBN) == 0 && library[i].available) {
            book = &library[i];
            break;
        }
    }

    if (book == NULL) {
        printf("Book not available or not found.\n");
        return;
    }

    strcpy(user->borrowed_books[user->num_borrowed++], ISBN);
    book->available = 0;
    printf("Book borrowed successfully.\n");
}

void return_book() {
    int user_ID;
    char ISBN[13];
    printf("Enter user ID: ");
    scanf("%d", &user_ID);
    printf("Enter ISBN of the book to return: ");
    scanf("%s", ISBN);

    User *user = NULL;
    for (int i = 0; i < num_users; i++) {
        if (users[i].ID == user_ID) {
            user = &users[i];
            break;
        }
    }

    if (user == NULL) {
        printf("User not found.\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < user->num_borrowed; i++) {
        if (strcmp(user->borrowed_books[i], ISBN) == 0) {
            strcpy(user->borrowed_books[i], user->borrowed_books[--user->num_borrowed]);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("User did not borrow this book.\n");
        return;
    }

    Book *book = NULL;
    for (int i = 0; i < num_books; i++) {
        if (strcmp(library[i].ISBN, ISBN) == 0) {
            book = &library[i];
            break;
        }
    }

    if (book == NULL) {
        printf("Book not found in the library.\n");
        return;
    }

    book->available = 1;
    printf("Book returned successfully.\n");
}

void list_borrowed_books() {
    int user_ID;
    printf("Enter user ID: ");
    scanf("%d", &user_ID);

    User *user = NULL;
    for (int i = 0; i < num_users; i++) {
        if (users[i].ID == user_ID) {
            user = &users[i];
            break;
        }
    }

    if (user == NULL) {
        printf("User not found.\n");
        return;
    }

    printf("Books borrowed by %s (ID: %d):\n", user->name, user->ID);
    for (int i = 0; i < user->num_borrowed; i++) {
        printf("- %s\n", user->borrowed_books[i]);
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Remove Book\n");
        printf("3. Search Book by Title\n");
        printf("4. Add User\n");
        printf("5. Search User by ID\n");
        printf("6. Borrow Book\n");
        printf("7. Return Book\n");
        printf("8. List Borrowed Books\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_book();
                break;
            case 2:
                remove_book();
                break;
            case 3:
                search_book_by_title();
                break;
            case 4:
                add_user();
                break;
            case 5:
                search_user_by_ID();
                break;
            case 6:
                borrow_book();
                break;
            case 7:
                return_book();
                break;
            case 8:
                list_borrowed_books();
                break;
            case 9:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
