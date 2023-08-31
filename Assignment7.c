#include <stdio.h>
#include <string.h>

struct Contact {
    char name[100];
    char phone[15];
    char address[200];
};

void addContact(FILE *file) {
    struct Contact contact;

    printf("Enter name: ");
    scanf(" %[^\n]", contact.name);
    printf("Enter phone number: ");
    scanf(" %s", contact.phone);
    printf("Enter address: ");
    scanf(" %[^\n]", contact.address);

    fprintf(file, "%s\n%s\n%s\n", contact.name, contact.phone, contact.address);

    printf("\nContact added successfully!\n");
}

void displayContacts(FILE *file) {
    struct Contact contact;
    int count = 1;

    printf("Contact List:\n");

    while (fscanf(file, " %[^\n]\n%s\n%[^\n]\n", contact.name, contact.phone, contact.address) == 3) {
        printf("%d. Name: %s\n   Phone: %s\n   Address: %s\n", count++, contact.name, contact.phone, contact.address);
    }
}

void searchContact(FILE *file) {
    char searchName[100];
    struct Contact contact;
    int found = 0;

    printf("Enter name to search for: ");
    scanf(" %[^\n]", searchName);

    while (fscanf(file, " %[^\n]\n%s\n%[^\n]\n", contact.name, contact.phone, contact.address) == 3) {
        if (strcmp(searchName, contact.name) == 0) {
            printf("\nContact found:\n");
            printf("Name: %s\nPhone: %s\nAddress: %s\n", contact.name, contact.phone, contact.address);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nContact not found.\n");
    }
}

int main() {
    FILE *file = fopen("contacts.txt", "a+"); // Open file for reading and appending

    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    printf("Welcome to the Contact Manager!\n");

    int choice;

    do {
        printf("1. Add a new contact\n");
        printf("2. Display all contacts\n");
        printf("3. Search for a contact\n");
        printf("4. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addContact(file);
                break;
            case 2:
                displayContacts(file);
                break;
            case 3:
                searchContact(file);
                break;
            case 4:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);

    fclose(file);

    return 0;
}
