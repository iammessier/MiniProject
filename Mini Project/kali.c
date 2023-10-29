#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure of the employee
struct emp {
    char name[50];
    float salary;
    int age;
    int id;
};

struct emp e;

// size of the structure
size_t size = sizeof(e);

FILE *fp, *ft;

// Function to add the records
void addrecord (){
    system("clear"); // Use "clear" for Unix-like systems, or "cls" for Windows

    fseek(fp, 0, SEEK_END);
    char another = 'y';

    while (another == 'y') {
        printf("\nEnter Name : ");
        scanf("%s", e.name);

        printf("\nEnter Age : ");
        scanf("%d", &e.age);

        printf("\nEnter Salary : ");
        scanf("%f", &e.salary);

        printf("\nEnter EMP-ID : ");
        scanf("%d", &e.id);

        fwrite(&e, size, 1, fp);

        printf("\nWant to add another record (Y/N) : ");
        fflush(stdin);
        scanf(" %c", &another);
    }
}

// Function to delete the records
void deleterecord (){
    system("clear"); // Use "clear" for Unix-like systems, or "cls" for Windows
    char empname[50];
    char another = 'y';

    while (another == 'y') {
        printf("\nEnter employee name to delete : ");
        scanf("%s", empname);

        ft = fopen("temp.txt", "wb");
        rewind(fp);

        while (fread(&e, size, 1, fp) == 1) {
            if (strcmp(e.name, empname) != 0)
                fwrite(&e, size, 1, ft);
        }

        fclose(fp);
        fclose(ft);
        remove("data.txt");
        rename("temp.txt", "data.txt");
        fp = fopen("data.txt", "rb+");

        printf("\nWant to delete another record (Y/N) : ");
        fflush(stdin);
        scanf(" %c", &another);
    }
}

// Function to display the record
void displayrecord() {
    system("clear"); // Use "clear" for Unix-like systems, or "cls" for Windows
    rewind(fp);

    printf("===============================================================================\n");
    printf("NAME\t\t\tAGE\t\tSALARY\t\t\tID\n");
    printf("===============================================================================\n");

    while (fread(&e, size, 1, fp) == 1)
        printf("%-20s\t%d\t%.2f\t\t%d\n", e.name, e.age, e.salary, e.id);

    printf("===============================================================================\n");

    printf("\n\n\n\t");
    system("pause"); // Use "pause" for Windows, or "getchar()" for Unix-like systems
}

// Function to modify the record
void modifyrecord() {
    system("clear"); // Use "clear" for Unix-like systems, or "cls" for Windows
    char empname[50];
    char another = 'y';

    while (another == 'y') {
        printf("\nEnter employee name to modify : ");
        scanf("%s", empname);

        rewind(fp);

        while (fread(&e, size, 1, fp) == 1) {
            if (strcmp(e.name, empname) == 0) {
                printf("\nEnter new name: ");
                scanf("%s", e.name);
                printf("\nEnter new age: ");
                scanf("%d", &e.age);
                printf("\nEnter new salary: ");
                scanf("%f", &e.salary);
                printf("\nEnter new EMP-ID: ");
                scanf("%d", &e.id);

                fseek(fp, -size, SEEK_CUR);
                fwrite(&e, size, 1, fp);
                break;
            }
        }

        printf("\nWant to modify another record (Y/N) : ");
        fflush(stdin);
        scanf(" %c", &another);
    }
}

// Function to search for a record
void searchrecord() {
    system("clear"); // Use "clear" for Unix-like systems, or "cls" for Windows
    char empname[50];
    char another = 'y';

    while (another == 'y') {
        printf("\nEnter employee name to search : ");
        scanf("%s", empname);

        rewind(fp);
        int found = 0;

        while (fread(&e, size, 1, fp) == 1) {
            if (strcmp(e.name, empname) == 0) {
                printf("Record Found!\n");
                printf("Name: %s\n", e.name);
                printf("Age: %d\n", e.age);
                printf("Salary: %.2f\n", e.salary);
                printf("EMP-ID: %d\n", e.id);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Record not found!\n");
        }

        printf("\nWant to search another record (Y/N) : ");
        fflush(stdin);
        scanf(" %c", &another);
    }
}

// Function to calculate and display the average salary
void averageSalary() {
    rewind(fp);
    float totalSalary = 0.0;
    int count = 0;

    while (fread(&e, size, 1, fp) == 1) {
        totalSalary += e.salary;
        count++;
    }

    if (count > 0) {
        float avgSalary = totalSalary / count;
        printf("Average Salary: %.2f\n", avgSalary);
    } else {
        printf("No records found to calculate average salary.\n");
    }
}

// Driver code
int main() {
    int choice;

    // opening the file
    fp = fopen("data.txt", "rb+");

    // showing an error if the file is unable to open.
    if (fp == NULL) {
        fp = fopen("data.txt", "wb+");
        if (fp == NULL) {
            printf("\nCannot open file...");
            exit(1);
        }
    }

    printf("\n\n\n\n==================================");
    printf("\nEMPLOYEE RECORD MANAGEMENT SYSTEM\n");
    printf("==================================");
    printf("\nDeveloper: @Jay_Nahata 0801CS221067");
    printf("\n\n");

    while (1) {
        printf("1. ADD RECORD\n");
        printf("2. DELETE RECORD\n");
        printf("3. DISPLAY RECORDS\n");
        printf("4. MODIFY RECORD\n");
        printf("5. SEARCH RECORD\n");
        printf("6. CALCULATE AVERAGE SALARY\n");
        printf("7. EXIT\n");
        printf("ENTER YOUR CHOICE...\n");
        fflush(stdin);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addrecord();
                break;

            case 2:
                deleterecord();
                break;

            case 3:
                displayrecord();
                break;

            case 4:
                modifyrecord();
                break;

            case 5:
                searchrecord();
                break;

            case 6:
                averageSalary();
                break;

            case 7:
                fclose(fp);
                exit(0);
                break;

            default:
                printf("\nINVALID CHOICE...\n");
        }
    }

    return 0;
}
