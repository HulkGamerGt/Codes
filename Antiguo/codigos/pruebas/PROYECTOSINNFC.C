#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sqlite3.h>
#include <curl/curl.h>

// Estructuras de datos
typedef struct {
    char nombre[50];
    char apellido[50];
    char rut[12];
    char clave[20]; // Para profesor
    char fingerprint[256]; // Representación simulada de huella
} Persona;

typedef struct {
    char rut[12];
    char hora_entrada[20];
    char hora_salida[20];
    char fecha[11];
} Asistencia;

// Variables globales
sqlite3 *db;

// Prototipos de funciones
void init_database();
void populate_test_data();
int read_nfc(char *uid);
int verify_fingerprint(const char *rut, const char *fingerprint);
int verify_professor(const char *rut, const char *clave);
void record_attendance(const char *rut, int is_entry);
void send_attendance_email();
char* get_current_time();
char* get_current_date();

// Inicializar base de datos
void init_database() {
    if (sqlite3_open("attendance.db", &db)) {
        printf("Error abriendo base de datos: %s\n", sqlite3_errmsg(db));
        exit(EXIT_FAILURE);
    }
    
    const char *sql = "CREATE TABLE IF NOT EXISTS personas ("
                     "rut TEXT PRIMARY KEY, "
                     "nombre TEXT, "
                     "apellido TEXT, "
                     "clave TEXT, "
                     "fingerprint TEXT);"
                     "CREATE TABLE IF NOT EXISTS asistencias ("
                     "rut TEXT, "
                     "fecha TEXT, "
                     "hora_entrada TEXT, "
                     "hora_salida TEXT, "
                     "FOREIGN KEY(rut) REFERENCES personas(rut));";
    
    char *err_msg = 0;
    if (sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK) {
        printf("Error SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
    
    // Poblar datos de prueba
    populate_test_data();
}

// Poblar base de datos con datos de prueba
void populate_test_data() {
    const char *sql = "INSERT OR IGNORE INTO personas (rut, nombre, apellido, clave, fingerprint) VALUES "
                     "('12345678-9', 'Juan', 'Perez', 'clave123', NULL), "
                     "('98765432-1', 'Ana', 'Gomez', NULL, 'huella_ana'), "
                     "('11111111-1', 'Carlos', 'Alvarez', NULL, 'huella_carlos');";
    
    char *err_msg = 0;
    if (sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK) {
        printf("Error insertando datos de prueba: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
}

// Leer RUT manualmente (simulación de NFC)
int read_nfc(char *uid) {
    printf("Ingrese RUT manualmente: ");
    if (scanf("%11s", uid) == 1) {
        // Validar formato básico de RUT (XX.XXX.XXX-X o sin puntos/guion)
        if (strlen(uid) >= 9 && (uid[9] == '-' || uid[10] == '-' || uid[11] == '\0')) {
            return 1;
        }
    }
    printf("RUT inválido. Intente nuevamente.\n");
    return 0;
}

// Verificar huella dactilar (simulada)
int verify_fingerprint(const char *rut, const char *fingerprint) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT fingerprint FROM personas WHERE rut = ?;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, rut, -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const char *stored_fingerprint = (const char*)sqlite3_column_text(stmt, 0);
            int result = strcmp(fingerprint, stored_fingerprint) == 0;
            sqlite3_finalize(stmt);
            return result;
        }
        sqlite3_finalize(stmt);
    }
    return 0;
}

// Verificar credenciales del profesor
int verify_professor(const char *rut, const char *clave) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT clave FROM personas WHERE rut = ? AND clave IS NOT NULL;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, rut, -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const char *stored_clave = (const char*)sqlite3_column_text(stmt, 0);
            int result = strcmp(clave, stored_clave) == 0;
            sqlite3_finalize(stmt);
            return result;
        }
        sqlite3_finalize(stmt);
    }
    return 0;
}

// Registrar asistencia
void record_attendance(const char *rut, int is_entry) {
    sqlite3_stmt *stmt;
    char *current_time = get_current_time();
    char *current_date = get_current_date();
    
    if (is_entry) {
        const char *sql = "INSERT OR IGNORE INTO asistencias (rut, fecha, hora_entrada) "
                         "VALUES (?, ?, ?);";
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, rut, -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, current_date, -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 3, current_time, -1, SQLITE_STATIC);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        }
    } else {
        const char *sql = "UPDATE asistencias SET hora_salida = ? "
                         "WHERE rut = ? AND fecha = ? AND hora_salida IS NULL;";
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, current_time, -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, rut, -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 3, current_date, -1, SQLITE_STATIC);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        }
    }
    
    free(current_time);
    free(current_date);
}

// Obtener hora actual
char* get_current_time() {
    time_t rawtime;
    struct tm *timeinfo;
    char *buffer = malloc(20);
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 20, "%H:%M:%S", timeinfo);
    return buffer;
}

// Obtener fecha actual
char* get_current_date() {
    time_t rawtime;
    struct tm *timeinfo;
    char *buffer = malloc(11);
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 11, "%Y-%m-%d", timeinfo);
    return buffer;
}

// Enviar correo con reporte
void send_attendance_email() {
    CURL *curl;
    CURLcode res;
    FILE *fp = tmpfile();
    
    // Obtener datos de asistencia
    sqlite3_stmt *stmt;
    const char *sql = "SELECT p.nombre, p.apellido, p.rut, a.fecha, a.hora_entrada, a.hora_salida "
                     "FROM personas p JOIN asistencias a ON p.rut = a.rut "
                     "WHERE a.fecha = ? ORDER BY p.apellido, p.nombre;";
    
    char *current_date = get_current_date();
    
    fprintf(fp, "Subject: Reporte de Asistencia %s\n", current_date);
    fprintf(fp, "To: admin@universidad.cl\n");
    fprintf(fp, "From: sistema-asistencia@universidad.cl\n\n");
    fprintf(fp, "Reporte de Asistencia - Fecha: %s\n\n", current_date);
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, current_date, -1, SQLITE_STATIC);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            fprintf(fp, "Nombre: %s %s\n", 
                   sqlite3_column_text(stmt, 0), sqlite3_column_text(stmt, 1));
            fprintf(fp, "RUT: %s\n", sqlite3_column_text(stmt, 2));
            fprintf(fp, "Fecha: %s\n", sqlite3_column_text(stmt, 3));
            fprintf(fp, "Entrada: %s\n", sqlite3_column_text(stmt, 4));
            fprintf(fp, "Salida: %s\n\n", 
                   sqlite3_column_text(stmt, 5) ? (const char*)sqlite3_column_text(stmt, 5) : "No registrada");
        }
        sqlite3_finalize(stmt);
    }
    
    free(current_date);
    rewind(fp);
    
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        struct curl_slist *recipients = NULL;
        // Configurar según tu servidor SMTP
        curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.universidad.cl:587");
        curl_easy_setopt(curl, CURLOPT_USERNAME, "sistema-asistencia@universidad.cl");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "securepassword");
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "sistema-asistencia@universidad.cl");
        recipients = curl_slist_append(recipients, "admin@universidad.cl");
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_READDATA, fp);
        
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            printf("Error enviando correo: %s\n", curl_easy_strerror(res));
        }
        
        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }
    
    fclose(fp);
    curl_global_cleanup();
}

int main() {
    init_database();
    
    // Proceso del profesor (inicio)
    printf("Sistema de Asistencia\n");
    printf("Profesor: Ingrese su RUT\n");
    char nfc_uid[12];
    while (!read_nfc(nfc_uid)) {
        while (getchar() != '\n'); // Limpiar buffer
    }
    
    char clave[50];
    printf("Ingrese su clave: ");
    scanf("%49s", clave);
    while (getchar() != '\n'); // Limpiar buffer
    
    if (!verify_professor(nfc_uid, clave)) {
        printf("Credenciales inválidas\n");
        sqlite3_close(db);
        return 1;
    }
    
    printf("Profesor autenticado. Sistema listo.\n");
    
    // Bucle principal
    while (1) {
        printf("\nEsperando estudiante...\n");
        while (!read_nfc(nfc_uid)) {
            while (getchar() != '\n'); // Limpiar buffer
        }
        
        // Obtener datos del estudiante
        sqlite3_stmt *stmt;
        const char *sql = "SELECT nombre, apellido FROM personas WHERE rut = ?;";
        char nombre[50], apellido[50];
        
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, nfc_uid, -1, SQLITE_STATIC);
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                strcpy(nombre, (const char*)sqlite3_column_text(stmt, 0));
                strcpy(apellido, (const char*)sqlite3_column_text(stmt, 1));
                
                printf("\nEstudiante detectado:\n");
                printf("Nombre: %s %s\n", nombre, apellido);
                printf("RUT: %s\n", nfc_uid);
                printf("Hora: %s\n", get_current_time());
            } else {
                printf("Estudiante no encontrado.\n");
                sqlite3_finalize(stmt);
                continue;
            }
            sqlite3_finalize(stmt);
        }
        
        // Verificar huella
        char fingerprint[256];
        printf("Por favor, ingrese huella (simulada): ");
        scanf("%255s", fingerprint);
        while (getchar() != '\n'); // Limpiar buffer
        
        if (verify_fingerprint(nfc_uid, fingerprint)) {
            printf("Huella verificada. Registrando asistencia...\n");
            record_attendance(nfc_uid, 1); // Entrada
        } else {
            printf("Huella no válida.\n");
            continue;
        }
        
        // Registro de salida
        printf("Para registrar salida, ingrese RUT nuevamente\n");
        while (!read_nfc(nfc_uid)) {
            while (getchar() != '\n'); // Limpiar buffer
        }
        record_attendance(nfc_uid, 0); // Salida
        printf("Salida registrada.\n");
        
        // Finalización por profesor
        printf("Profesor, para finalizar ingrese su RUT\n");
        while (!read_nfc(nfc_uid)) {
            while (getchar() != '\n'); // Limpiar buffer
        }
        
        printf("Ingrese su clave: ");
        scanf("%49s", clave);
        while (getchar() != '\n'); // Limpiar buffer
        
        if (verify_professor(nfc_uid, clave)) {
            printf("Sesión finalizada. Enviando reporte por correo...\n");
            send_attendance_email();
            break;
        }
    }
    
    sqlite3_close(db);
    return 0;
}