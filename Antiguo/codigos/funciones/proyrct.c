#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 100
#define MAX_RUT 10
#define MAX_NAME 50

typedef struct {
    char rut[MAX_RUT];
    char name[MAX_NAME];
    int attendance;
} Student;

typedef struct {
    char code[7];
    char name[50];
} Teacher;

// PROTOTIPOS DE FUNCIONES
void initialize_file();
int check_class_code(const char *input_code, char *teacher_name);
int find_student(const char *input_rut, Student *student);
void update_attendance(const char *rut, const char *name);
void display_attendance(const char *rut);
int is_numeric(const char *input);
void login();
void run_attendance_system();

int main() {
    initialize_file();
    login();
    run_attendance_system();

    printf("\nCerrando programa de asistencia...\n");
    return 0;
}

// DEFINICIONES DE FUNCIONES

void initialize_file() {
    FILE *student_file = fopen("student.txt", "r");
    if (student_file == NULL) {
        printf("Error: No se encontró el archivo student.txt!\n");
        exit(1);
    }

    FILE *attendance_file = fopen("attendance.txt", "a+");
    if (attendance_file == NULL) {
        printf("Error al crear el archivo de asistencia!\n");
        fclose(student_file);
        exit(1);
    }

    fseek(attendance_file, 0, SEEK_END);
    if (ftell(attendance_file) == 0) {
        printf("Creando archivo de asistencia inicial...\n");
        rewind(student_file);
        char line[MAX_LINE];
        while (fgets(line, MAX_LINE, student_file)) {
            char rut[MAX_RUT];
            char name[MAX_NAME];
            if (sscanf(line, "%s %[^\n]", rut, name) == 2) {
                fprintf(attendance_file, "%s %s 0\n", rut, name);
            }
        }
    }

    fclose(student_file);
    fclose(attendance_file);
}

int check_class_code(const char *input_code, char *teacher_name) {
    Teacher teachers[] = {
        {"123456", "Lastenia Salinas"},
        {"654321", "Bruno Faundez"},
        {"121212", "Maria Jose Perez J."},
        {"",},{},{},{},{},{},{},{},{},{},{},
    };
    int num_teachers = sizeof(teachers) / sizeof(teachers[0]);

    for (int i = 0; i < num_teachers; i++) {
        if (strcmp(input_code, teachers[i].code) == 0) {
            strcpy(teacher_name, teachers[i].name);
            return 1;
        }
    }
    return 0;
}

int find_student(const char *input_rut, Student *student) {
    FILE *file = fopen("student.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo de estudiantes!\n");
        return 0;
    }

    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, file)) {
        char rut[MAX_RUT];
        char name[MAX_NAME];
        if (sscanf(line, "%s %[^\n]", rut, name) == 2) {
            if (strcmp(rut, input_rut) == 0) {
                strcpy(student->rut, rut);
                strcpy(student->name, name);
                fclose(file);
                return 1;
            }
        }
    }
    fclose(file);
    return 0;
}

void update_attendance(const char *rut, const char *name) {
    FILE *file = fopen("attendance.txt", "r+");
    if (file == NULL) {
        printf("Error al abrir el archivo de asistencia!\n");
        return;
    }

    Student students[100];
    int student_count = 0;
    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, file)) {
        if (sscanf(line, "%s %[^0-9] %d", students[student_count].rut, 
                   students[student_count].name, 
                   &students[student_count].attendance) == 3) {
            student_count++;
        }
    }

    rewind(file);

    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].rut, rut) == 0) {
            students[i].attendance++;
            strcpy(students[i].name, name);
        }
        fprintf(file, "%s %s %d\n", students[i].rut, students[i].name, 
                students[i].attendance);
    }
    fclose(file);
}

void display_attendance(const char *rut) {
    FILE *file = fopen("attendance.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo de asistencia!\n");
        return;
    }

    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, file)) {
        char file_rut[MAX_RUT];
        char name[MAX_NAME];
        int attendance;
        if (sscanf(line, "%s %[^0-9] %d", file_rut, name, &attendance) == 3) {
            if (strcmp(file_rut, rut) == 0) {
                printf("Asistencia para RUT %s (%s): %d\n", rut, name, attendance);
                fclose(file);
                return;
            }
        }
    }
    fclose(file);
    printf("RUT no encontrado en attendance.txt!\n");
}

int is_numeric(const char *input) {
    for (int i = 0; input[i]; i++) {
        if (input[i] < '0' || input[i] > '9') {
            return 0;
        }
    }
    return 1;
}

void login() {
    char input_code[10];
    char teacher_name[50];
    printf("\nIntroduzca código de acceso: ");
    scanf("%s", input_code);

    if (!is_numeric(input_code)) {
        printf("Error: El código debe contener solo números!\n");
        exit(1);
    }

    if (!check_class_code(input_code, teacher_name)) {
        printf("Código de clase inválido!\n");
        exit(1);
    }

    printf("Bienvenido/a docente %s\n", teacher_name);
}

void run_attendance_system() {
    int option;
    printf("\n¿Desea iniciar la clase? (1 sí / 0 no): ");
    scanf("%d", &option);
    if (option != 1) {
        printf("Programa terminado.\n");
        exit(0);
    }
    
    char input_rut[MAX_RUT];
    while (1) {
        printf("\nIngresa RUT (o 999999 para salir): ");
        scanf("%s", input_rut);
        if (!is_numeric(input_rut)) {
            printf("Error: El RUT debe contener solo números!\n");
            continue;
        }

        if (strcmp(input_rut, "999999") == 0) {
            break;
        }

        Student student;
        if (find_student(input_rut, &student)) {
            printf("RUT encontrado: %s, Nombre: %s\n", student.rut, student.name);
            update_attendance(input_rut, student.name);
            display_attendance(input_rut);
        } else {
            printf("RUT no encontrado!\n");
        }
    }
}    