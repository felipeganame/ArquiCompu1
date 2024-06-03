#include <stdio.h>
#include <string.h>
#include <unistd.h> // for usleep
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>

#define PASSWORD "12345"
#define MAX_ATTEMPTS 3
#define SPEED_INCREMENT 100000

// Global variable to control the speed
int speed = 500000; // 500ms

// Function to introduce a delay
void delay(unsigned long int microseconds) {
    usleep(microseconds);
}

// Function to check if a key has been pressed
int kbhit(void) {
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv) > 0;
}

// Function to get a character from the keyboard without echoing
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
        printf("Ingrese su password de 5 digitos: ");
        scanf("%5s", input);

        if (strcmp(input, PASSWORD) == 0) {
            printf("Bienvenido al sistema\n");
            return 1;
        } else {
            printf("Password no valida\n");
            attempts++;
        }
    }

    printf("Demasiados intentos fallidos. El programa se abortara.\n");
    return 0;
}

// Function to get a random time in milliseconds between min and max
unsigned long int get_random_delay(unsigned long int min, unsigned long int max) {
    return min + (rand() % (max - min + 1));
}

//genera un secuencia en donde se preden de izq a der las luces una por una hasta que todas queden prendidas
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

//funcion que permite generar el efecto choque, de izq a der y luego der a izq
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
            // Do nothing, just wait
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
        unsigned long int random_delay = get_random_delay(1000, 5000); // Random delay between 1 and 5 seconds
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

//sirenas
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



// Menu principal
void mostrar_menu() {
    printf("\nSeleccione una secuencia de luces:\n");
    printf("1. Autofantastico\n");
    printf("2. Choque\n");
    printf("3. Carrera de Formula 1\n");
    printf("4. Sirenas de emergencia\n");
    printf("0. Salir\n");
}

int main() {
    // Inicializar el generador de numeros aleatorios
    srand(time(NULL));

    if (!control_acceso()) {
        return 0;
    }

    int opcion;

    while (1) {
        mostrar_menu();
        printf("Ingrese su opcion: ");
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
            case 0:
                printf("Saliendo del programa...\n");
                return 0;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                break;
        }
    }
}
