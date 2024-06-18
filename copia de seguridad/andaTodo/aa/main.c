#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include "EasyPIO.h"
#include "func_assembly.h"

#define PASSWORD_LENGTH 5

// Function prototypes
void disp_binary(int);
void getPassword(char *password);
void menu();
void autoFantastico();
void choque();
// void ambulancia();
// void secuencia_formula1();
struct termios modifyTerminalConfig(void);
void restoreTerminalConfig(struct termios);
bool keyHit(int index);
void pinSetup(void);
void ledShow(unsigned char output);
int delay(int index);
void clearInputBuffer();
void turnOff();

const unsigned char led[] = {14, 15, 18, 23, 24, 25, 8, 7};
int delayTime[] = {100000, 100000, 100000, 100000};

int main(void) {
    pinSetup();
    char setPassword[5] = {'1', '2', '3', '4', '5'};
    char passwordInput[5];

    //Recibe la contrasenia y la chequea
    //si la recibe y es erronea tres veces cierra el programa
    for (int i = 0; i < 3; i++) {
        bool passwordFlag = true;
        getPassword(passwordInput);

        for (int j = 0; j < 5; j++) {
            if (setPassword[j] != passwordInput[j]) {
                passwordFlag = false;
                break;
            }
        }

        if (passwordFlag) {
            printf("Proyecto arquitectura de computadoras :)\n Autores: Vicente Monzo, Arnon Nahmias, Felipe Ganame\n\n");
            menu();
            printf("hasta luego!!\n");
            break;
        } else {
            printf("La clave no es correcta!\n\n");
        }
    }
}

void disp_binary(int i) {
    int t;
    for (t = 128; t > 0; t = t / 2)
        if (i & t) printf("1 ");
        else printf("0 ");
    fflush(stdout);
    printf("\r");
}

void getPassword(char *password) {
    struct termios oldattr = modifyTerminalConfig();

    printf("Ingrese su clave: ");
    for (int i = 0; i < PASSWORD_LENGTH; i++) {
        password[i] = getchar();
        printf("*");
        fflush(stdout);
    }

    restoreTerminalConfig(oldattr);
    printf("\n");
}

void menu() {
    int opcion;
    do {
        clearInputBuffer();
        printf("*****************************\n");
        printf("*                           *\n");
        printf("*  Seleccione una opcion:   *\n");
        printf("*  1: Auto Fantastico       *\n");
        printf("*  2: El Choque             *\n");
        printf("*  3: Ambulancia            *\n");
        printf("*  4: Formula 1             *\n");
        printf("*  0: Salir                 *\n");
        printf("*                           *\n");
        printf("*****************************\n");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                autoFantastico();
                break;
            case 2:
                choque();
                break;
            case 3:
                ambulancia();
                break;
            case 4:
                secuencia_formula1();
                break;
            case 0:
                break;
            default:
                printf("Seleccione una opcion valida\n");
        }
    } while (opcion != 0);
}

void autoFantastico() {
    printf("Presione esc para finalizar la secuencia\n");
    printf("Presione U para aumentar la velocidad\n");
    printf("Presione D para disminuir la velocidad\n");
    printf("Auto Fantastico:\n");

    unsigned char output;

    while (true) {
        output = 0x80;
        for (int i = 0; i < 8; i++) {
            ledShow(output);
            disp_binary(output);
            output = output >> 1;

            if (delay(0) == 0) {
                turnOff();
                return;
            }
        }
        output = 0x2;

        for (int i = 0; i < 6; i++) {
            ledShow(output);
            disp_binary(output);
            output = output << 1;

            if (delay(0) == 0) {
                turnOff();
                return;
            }
        }

    }
}

void choque() {
    printf("Presione esc para finalizar la secuencia\n");
    printf("Presione U para aumentar la velocidad\n");
    printf("Presione D para disminuir la velocidad\n");
    printf("Choque:\n");

    unsigned char output, aux1, aux2;

    while (true) {
        aux1 = 0x80;
        aux2 = 0x1;
        for (int i = 0; i < 7; i++) {
            output = aux1 | aux2;
            ledShow(output);
            disp_binary(output);
            aux1 = aux1 >> 1;
            aux2 = aux2 << 1;

            if (delay(1) == 0) {
                turnOff();
                return;
            }
        }
    }
}
/*
void ambulancia() {
    printf("Presione esc para finalizar la secuencia\n");
    printf("Presione U para aumentar la velocidad\n");
    printf("Presione D para disminuir la velocidad\n");
    printf("Ambulancia:\n");

    unsigned char ambulancia[] = {0x0, 0xF, 0xF, 0xF0, 0xF0, 0x0, 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1};

    while (true) {
        for(int i = 0 ; i < 21 ; i++) {
            ledShow(ambulancia[i]);
            disp_binary(ambulancia[i]);
            if (delay(2) == 0) {
                turnOff();
                return;
            }
        }
    }
}

void secuencia_formula1() {
    printf("Presione esc para finalizar la secuencia\n");
    printf("Presione U para aumentar la velocidad\n");
    printf("Presione D para disminuir la velocidad\n");
    printf("Carrera de Formula 1:\n");

    unsigned char output = 0x0;

    while (true) {
        for (int i = 7; i >= 0; i--) { // asumimos que hay 8 LEDs
            output |= (0x1 << i); // enciende el i-ésimo LED y mantiene los LEDs anteriores encendidos
            ledShow(output);
            disp_binary(output);

            if (delay(3) == 0) { // espera un tiempo antes de encender el siguiente LED
                turnOff();
                return;
            }
        }

        if (delay(3) == 0) { // espera un tiempo antes de apagar todos los LEDs
            turnOff();
            return;
        }

        output = 0x0; // apaga todos los LEDs
        ledShow(output);
        disp_binary(output);

        for (int i = 0; i < 30; i++) {
            if (delay(3) == 0) { // verifica si se presiona una tecla para salir
                turnOff();
                return;
            }
        }
    }
}
*/
struct termios modifyTerminalConfig(void) {
    struct termios oldattr, newattr;

    //obtiene los atributos de la terminal
    tcgetattr(STDIN_FILENO, &oldattr);

    //copia los atributos ya existenes a los nuevos
    newattr = oldattr;

    //desabilita el modo canonico y echo
    newattr.c_lflag &= ~(ICANON | ECHO);

    //aplica los nuevos atributos a la terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

    return oldattr;
}

void restoreTerminalConfig(struct termios oldattr) {
    //restablece los atributos originales a la terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
}

bool keyHit(int index) {
    struct termios oldattr = modifyTerminalConfig();
    int ch, oldf;

    //setea el archivo descriptor del input estandar a que no se bloquee
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    //intenta leer un caracter de un input estandar
    ch = getchar();

    //cuando se presiona U
    if(ch == 117) { //ASCII para u
        if(delayTime[index] > 1000) {
            delayTime[index] = delayTime[index] - 1000;
        }
    }

    //cuando se presiona D
    if(ch == 100) {  //ASCII para d
        delayTime[index] = delayTime[index] + 1000;
    }

    restoreTerminalConfig(oldattr);

    // Restablece el archivo a modo descriptor
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    // si se presiona escape devuelve 1
    if (ch == 27) {
        ungetc(ch, stdin);
        return 1;
    }

    // si escape no se presiona devuelve 0
    return 0;
}

void pinSetup(void) {
    pioInit();

    for (int i = 0; i < 8; i++) {
        pinMode(led[i], OUTPUT);
    }
}

void ledShow(unsigned char output) {
    for (int j = 0; j < 8; j++) {
        digitalWrite(led[j], (output >> j) & 1);
    }
}

int delay(int index) {
    int i;
    for(i = delayTime[index]; i > 0; --i) {
        if(keyHit(index)) {
            return 0;
        }
    }
    return 1;
}

void clearInputBuffer() {
    printf("Presione ENTER para confirmar\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // desecha los caracteres
    }
}

void turnOff() {
    unsigned char off = 0x0;
    ledShow(off);
}
