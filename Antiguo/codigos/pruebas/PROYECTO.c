#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sqlite3.h>
#include <curl/curl.h>
#include <nfc/nfc.h>

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
nfc_device *pnd;
nfc_context *context;
sqlite3 *db;

// Prototipos de funciones
void init_nfc();
void close_nfc();
int read_nfc(char *uid);
int verify_fingerprint(const char *rut, const char *fingerprint);
void init_database();
int verify_professor(const char *rut, const char *clave);
void record_attendance(const char *rut, int is_entry);
void send_attendance_email();
char* get_current_time();
char* get_current_date();

// Inicializar NFC
void init_nfc() {
    nfc_init(&context);
    if (context == NULL) {
        printf("Error inicializando libnfc\n");
        exit(EXIT_FAILURE);
    }
    
    pnd = nfc_open(context, NULL);
    if (pnd == NULL) {
        printf("Error abriendo dispositivo NFC\n");
        nfc_exit(context);
        exit(EXIT_FAILURE);
    }
    
    if (nfc_initiator_init(pnd) < 0) {
        printf("Error inicializando modo iniciador\n");
        nfc_close(pnd);
        nfc_exit(context);
        exit(EXIT_FAILURE);
    }
}

// Cerrar NFC
void close_nfc() {
    nfc_close(pnd);
    nfc_exit(context);
}

// Leer tarjeta NFC
int read_nfc(char *uid) {
    nfc_target nt;
    if (nfc_initiator_select_passive_target(pnd, NULL, 0, &nt) > 0) {
        sprintf(uid, "%02x%02x%02x%02x", 
                nt.nti.nai.abtUid[0], nt.nti.nai.abtUid[1],
                nt.nti.nai.abtUid[2], nt.nti.nai.abtUid[3]);
        return 1;
    }
    return 0;
}

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
    
    curl = curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        struct curl_slist *recipients = NULL;
        curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.universidad.cl:587");
        curl_easy_setopt(curl, CURLOPT_USERNAME, "sistema-asistencia@universidad.cl");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "securepassword");
        curl_easy_setopt(curl, CURLOPT_MAILFROM, "sistema-asistencia@universidad.cl");
        recipients = curl_slist_append(recipients, "admin@universidad.cl");
        curl_easy_setopt(curl, CURLOPT_EMAILS_EMAILS, recipients);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_READDATA, fp);
        
        res = curl_perform();
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
    init_nfc();
    init_database();
    
    // Proceso del profesor (inicio)
    printf("Sistema de Asistencia\n");
    printf("Profesor: Escanee su tarjeta NFC\n");
    char nfc_uid[9];
    while (!read_nfc(nfc_uid)) {
        usleep(100000); // Espera 100ms
    }
    
    char clave[50];
    printf("Ingrese su clave: ");
    scanf("%s", clave);
    
    if (!verify_professor(nfc_uid, clave)) {
        printf("Credenciales inválidas\n");
        close_nfc();
        sqlite3_close(db);
        return 1;
    }
    
    printf("Profesor autenticado. Sistema listo.\n");
    
    // Bucle principal
    while (1) {
        printf("\nEsperando estudiante...\n");
        while (!read_nfc(nfc_uid)) {
            usleep(100000);
        }
        
        // Obtener datos del estudiante
        sqlite3_stmt *stmt;
        const char *sql = "SELECT nombre, apellido FROM personal WHERE rut = ?;";
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
            }
            sqlite3_finalize(stmt);
        }
        
        // Verificar huella
        char fingerprint[256];
        printf("Por favor, coloque su dedo en el lector de huellas\n");
        // Simulación: en un sistema real, aquí se leería el sensor
        scanf("%s", fingerprint);
        
        if (verify_fingerprint(nfc_uid, fingerprint)) {
            printf("Huella verificada. Registrando asistencia...\n");
            record_attendance(nfc_uid, 1); // Entrada
        } else {
            printf("Huella no válida.\n");
            continue;
        }
        
        // Registro de salida
        printf("Para registrar salida, escanee nuevamente\n");
        while (!read_nfc(nfc_uid)) {
            usleep(100000);
        }
        record_attendance(nfc_uid, 0); // Salida
        printf("Salida registrada.\n");
        
        // Finalización por profesor
        printf("Profesor, para finalizar escanee su tarjeta\n");
        while (!read_nfc(nfc_uid)) {
            usleep(100000);
        }
        
        printf("Ingrese su clave: ");
        scanf("%s", clave);
        
        if (verify_professor(nfc_uid, clave)) {
            printf("Sesión finalizada. Enviando reporte por correo...\n");
            send_attendance_email();
            break;
        }
    }
    
    close_nfc();
    sqlite3_close(db);
    return 0;
}