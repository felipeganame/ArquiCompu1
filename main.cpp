#include <stdio.h>
#include <string.h>
#include <unistd.h> // para usleep
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>

#define PASSWORD "12345"
#define MAX_ATTEMPTS 3
#define SPEED_INCREMENT 100000

// Variable global para controlar la velocidad
int speed = 500000; // 500ms

// Función para introducir un tiempo de demora
void delay(unsigned long int microseconds) {
    usleep(microseconds);
}

// Función para chequear si una tecla ha sido presionada
int kbhit(void) {
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv) > 0;
}

// Función para obtener un carácter del teclado sin eco
char getch(void) {
    char c;
    system("stty -echo");
    c = getchar();
    system("stty echo");
    return c;
}

// Control de acceso mediante password
int control_acceso() {
    char input[6];
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS) {
        printf("Ingrese su password de 5 dígitos: ");
        scanf("%5s", input);

        if (strcmp(input, PASSWORD) == 0) {
            printf("Bienvenido al sistema\n");
            return 1;
        } else {
            printf("Password no válida\n");
            attempts++;
        }
    }

    printf("Demasiados intentos fallidos. El programa se abortará.\n");
    return 0;
}

// Función para obtener un tiempo aleatorio en milisegundos entre min y max
unsigned long int get_random_delay(unsigned long int min, unsigned long int max) {
    return min + (rand() % (max - min + 1));
}

// Función para mostrar el patrón de latido del corazón
void disp_heartbeat_pattern(int pattern) {
    for (int i = 7; i >= 0; i--) {
        if (pattern & (1 << i)) {
            printf("* ");
        } else {
            printf("- ");
        }
    }
}

// Genera una secuencia en donde se encienden de izquierda a derecha las luces una por una hasta que todas queden encendidas
void autofantastico() {
    int leds[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    int num_leds = sizeof(leds) / sizeof(leds[0]);

    printf("Auto fantástico en ejecución. Presiona 'q' para salir.\n");
    while (1) {
        for (int i = 0; i < num_leds; i++) {
            printf("\n");
            for (int j = 0; j < num_leds; j++) {
                if (j <= i) {
                    printf("* ");
                } else {
                    printf("- ");
                }
            }
            fflush(stdout);
            delay(speed);

            if (kbhit()) {
                char c = getch();
                if (c == 'q') {
                    printf("\nSaliendo de Auto fantástico...\n");
                    return;
                } else if (c == 'u' && speed > SPEED_INCREMENT) {
                    speed -= SPEED_INCREMENT;
                } else if (c == 'd') {
                    speed += SPEED_INCREMENT;
                }
            }
        }
    }
}

// Función que permite generar el efecto choque, de izquierda a derecha y luego derecha a izquierda
void choque() {
    int leds[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    int num_leds = sizeof(leds) / sizeof(leds[0]);

    printf("Loop en ejecución. Presiona 'q' para salir.\n");
    while (1) {
        // Prender LEDs del 1 al 8
        for (int i = 0; i < num_leds; i++) {
            printf("\n");
            for (int j = 0; j < num_leds; j++) {
                if (j == i) {
                    printf("* ");
                } else {
                    printf("- ");
                }
            }
            fflush(stdout);
            delay(speed);

            if (kbhit()) {
                char c = getch();
                if (c == 'q') {
                    printf("\nSaliendo del loop...\n");
                    return;
                } else if (c == 'u' && speed > SPEED_INCREMENT) {
                    speed -= SPEED_INCREMENT;
                } else if (c == 'd') {
                    speed += SPEED_INCREMENT;
                }
            }
        }

        // Prender LEDs del 8 al 1
        for (int i = num_leds - 1; i >= 0; i--) {
            printf("\n");
            for (int j = 0; j < num_leds; j++) {
                if (j == i) {
                    printf("* ");
                } else {
                    printf("- ");
                }
            }
            fflush(stdout);
            delay(speed);

            if (kbhit()) {
                char c = getch();
                if (c == 'q') {
                    printf("\nSaliendo del loop...\n");
                    return;
                } else if (c == 'u' && speed > SPEED_INCREMENT) {
                    speed -= SPEED_INCREMENT;
                } else if (c == 'd') {
                    speed += SPEED_INCREMENT;
                }
            }
        }
    }
}

void secuencia_formula1() {
    int leds[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    int num_leds = sizeof(leds) / sizeof(leds[0]);

    printf("Carrera de Formula 1. Presiona cualquier tecla para iniciar la secuencia o 'q' para salir.\n");

    while (1) {
        // Esperar por entrada del usuario para iniciar la secuencia
        while (!kbhit()) {
            // No hacer nada, solo esperar
        }

        char c = getch();
        if (c == 'q') {
            printf("\nSaliendo de la carrera de Formula 1...\n");
            return;
        }

        // Encender luces una por una
        for (int i = 0; i < num_leds; i++) {
            printf("\n");
            for (int j = 0; j < num_leds; j++) {
                if (j <= i) {
                    printf("* ");
                } else {
                    printf("- ");
                }
            }
            fflush(stdout);
            delay(speed);

            if (kbhit()) {
                char c = getch();
                if (c == 'q') {
                    printf("\nSaliendo de la carrera de Formula 1...\n");
                    return;
                }
            }
        }

        // Esperar un tiempo aleatorio antes de apagar todas las luces
        unsigned long int random_delay = get_random_delay(1000, 5000); // Retardo aleatorio entre 1 y 5 segundos
        delay(random_delay);

        // Apagar todas las luces
        printf("\n");
        for (int i = 0; i < num_leds; i++) {
            printf("- ");
        }
        fflush(stdout);

        // Esperar un poco antes de permitir reiniciar la secuencia
        delay(1000);

        printf("\nPresiona cualquier tecla para reiniciar la secuencia o 'q' para salir.\n");
    }
}

// Sirenas
void sirenasEmergencia() {
    int leds[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    int num_leds = sizeof(leds) / sizeof(leds[0]);

    printf("Luces de ambulancia en ejecución. Presiona 'q' para salir.\n");
    while (1) {
        // Parpadeo de luces en grupos
        for (int i = 0; i < 2; i++) {
            // Encender los primeros cuatro LEDs
            printf("\n");
            for (int j = 0; j < num_leds; j++) {
                if (j < 4) {
                    printf("* ");
                } else {
                    printf("- ");
                }
            }
            fflush(stdout);
            delay(speed / 2); // Parpadeo rápido

            if (kbhit()) {
                char c = getch();
                if (c == 'q') {
                    printf("\nSaliendo de luces de ambulancia...\n");
                    return;
                } else if (c == 'u' && speed > SPEED_INCREMENT) {
                    speed -= SPEED_INCREMENT;
                } else if (c == 'd') {
                    speed += SPEED_INCREMENT;
                }
            }

            // Encender los últimos cuatro LEDs
            printf("\n");
            for (int j = 0; j < num_leds; j++) {
                if (j >= 4) {
                    printf("* ");
                } else {
                    printf("- ");
                }
            }
            fflush(stdout);
            delay(speed / 2); // Parpadeo rápido

            if (kbhit()) {
                char c = getch();
                if (c == 'q') {
                    printf("\nSaliendo de luces de ambulancia...\n");
                    return;
                } else if (c == 'u' && speed > SPEED_INCREMENT) {
                    speed -= SPEED_INCREMENT;
                } else if (c == 'd') {
                    speed += SPEED_INCREMENT;
                }
            }
        }
    }
}

void heartbeat_sequence() {
    int heartbeat_pattern[] = {0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF, 0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01};

    int quit_flag = 0; // Variable para indicar si se debe salir de la secuencia

    while (!quit_flag) {
        for (int i = 0; i < sizeof(heartbeat_pattern) / sizeof(heartbeat_pattern[0]); i++) {
            printf("\rLEDs: ");
            disp_heartbeat_pattern(heartbeat_pattern[i]);
            fflush(stdout);
            delay(speed);

            // Comprobar si se ha presionado la tecla 'q'
            if (kbhit()) {
                char c = getch();
                if (c == 'q') {
                    quit_flag = 1; // Salir de la secuencia
                    break;
                }
            }
        }
    }
}

// Menú principal
void mostrar_menu() {
    printf("\nSeleccione una secuencia de luces:\n");
    printf("1. Autofantastico\n");
    printf("2. Choque\n");
    printf("3. Carrera de Formula 1\n");
    printf("4. Sirenas de emergencia\n");
    printf("5. Secuencia de latido\n");
    printf("0. Salir\n");
}

int main() {
    // Inicializar el generador de números aleatorios
    srand(time(NULL));

    if (!control_acceso()) {
        return 0;
    }

    int opcion;

    while (1) {
        mostrar_menu();
        printf("Ingrese su opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                autofantastico();
                break;
            case 2:
                choque();
                break;
            case 3:
                secuencia_formula1();
                break;
            case 4:
                sirenasEmergencia();
                break;
            case 5:
                heartbeat_sequence();
                break;
            case 0:
                printf("Saliendo del programa...\n");
                return 0;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
                break;
        }
    }
}
