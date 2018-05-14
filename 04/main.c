#include <stdio.h>
#include <string.h>
#include <zconf.h>

#define ARRLENGTH 64

//Prototypes
void main_loop();
void mms_write_console();


int main() {
    main_loop();
    return 0;
}

void main_loop() {
    char string[ARRLENGTH];

    mms_write_console();
    scanf("%31s", &string[0]);
    printf("Ihre Eingabe: %s\n", string);
}

void mms_write_console() {
    char user[128];
    getlogin_r(user, sizeof(user));

    char cwd[1024];
    getcwd(cwd, sizeof(cwd));

    char *dir, *ptr;
    ptr = strtok(cwd, "/");
    while(ptr != NULL){
        dir = ptr;
        ptr = strtok(NULL, "/");
    }
    printf("%s:%s $ ",user, dir);
}

void mms_chdir() {

}
