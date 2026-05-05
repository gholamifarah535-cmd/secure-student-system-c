#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[30];
    char password[30];
} User;

typedef struct {
    char name[50];
    int age;
    float avg;
} Student;

// ---------- AUTH ----------
int login() {
    FILE *f = fopen("users.dat", "rb");
    User u;
    char user[30], pass[30];

    printf("Username: ");
    scanf("%s", user);
    printf("Password: ");
    scanf("%s", pass);

    while (fread(&u, sizeof(User), 1, f)) {
        if (strcmp(u.username, user) == 0 && strcmp(u.password, pass) == 0) {
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}

void registerUser() {
    FILE *f = fopen("users.dat", "ab");
    User u;

    printf("New username: ");
    scanf("%s", u.username);
    printf("New password: ");
    scanf("%s", u.password);

    fwrite(&u, sizeof(User), 1, f);
    fclose(f);

    printf("Account created.\n");
}

// ---------- STUDENTS ----------
void addStudent() {
    FILE *f = fopen("students.dat", "ab");
    Student s;

    printf("Name: ");
    scanf(" %[^\n]", s.name);
    printf("Age: ");
    scanf("%d", &s.age);
    printf("Average: ");
    scanf("%f", &s.avg);

    fwrite(&s, sizeof(Student), 1, f);
    fclose(f);
}

void displayStudents() {
    FILE *f = fopen("students.dat", "rb");
    Student s;

    while (fread(&s, sizeof(Student), 1, f)) {
        printf("\n%s | %d | %.2f\n", s.name, s.age, s.avg);
    }

    fclose(f);
}

void searchStudent() {
    FILE *f = fopen("students.dat", "rb");
    Student s;
    char name[50];

    printf("Search name: ");
    scanf(" %[^\n]", name);

    while (fread(&s, sizeof(Student), 1, f)) {
        if (strcmp(s.name, name) == 0) {
            printf("Found: %s %.2f\n", s.name, s.avg);
            break;
        }
    }

    fclose(f);
}

void deleteStudent() {
    FILE *f = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    Student s;
    char name[50];

    printf("Delete name: ");
    scanf(" %[^\n]", name);

    while (fread(&s, sizeof(Student), 1, f)) {
        if (strcmp(s.name, name) != 0) {
            fwrite(&s, sizeof(Student), 1, temp);
        }
    }

    fclose(f);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");
}

// ---------- MAIN ----------
int main() {
    int choice;

    do {
        printf("\n1. Register\n2. Login\n0. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            registerUser();
        }
        else if (choice == 2) {
            if (login()) {
                printf("Login success\n");

                int c2;
                do {
                    printf("\n1.Add 2.Show 3.Search 4.Delete 0.Exit\n");
                    scanf("%d", &c2);

                    switch(c2) {
                        case 1: addStudent(); break;
                        case 2: displayStudents(); break;
                        case 3: searchStudent(); break;
                        case 4: deleteStudent(); break;
                    }
                } while (c2 != 0);

            } else {
                printf("Login failed\n");
            }
        }

    } while (choice != 0);

    return 0;
}
