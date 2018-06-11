#include <stdio.h>
#include <string.h>
#include <zconf.h>
#include <stdlib.h>

#define TOKEN_DELIM " \n"

//Prototypes
void mms_main_loop();
void mms_write_console();
char *mms_read_line();
char **mms_tokenize(char *);
char *mms_env(char *);
void mms_launch(char **args);
int mms_execute(char **args);
void mms_cd(char **args);
void mms_set(char **args);

int main() {
    mms_main_loop();
    return 0;
}

void mms_main_loop() {
    char *string;
    char **args;
    int status;

    do {
        mms_write_console();
        string = mms_read_line();
        args = mms_tokenize(string);
        status = mms_execute(args);
    } while (status);
}

void mms_write_console() {
    char user[32];
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

char *mms_read_line() {
    char *string = NULL;
    size_t bufsize = 0;
    getline(&string, &bufsize, stdin);
    return string;
}

char **mms_tokenize(char *input) {
    int index = 0;
    char **tokens = malloc(64 * sizeof(char *));
    char *token = strtok(input, TOKEN_DELIM);
    while (token != NULL) {

        if(strncmp(token, "$", 1) == 0) {
            token = mms_env(token);
        }

        tokens[index++] = token;
        token = strtok(NULL, TOKEN_DELIM);
    }
    tokens[index] = NULL;
    return tokens;
}

char *mms_env(char *token) {
    char *env = strtok(token, "$");
    char *var = getenv(strtok(env, "/"));

    char *ret = malloc(strlen(var) * sizeof(char *));
    strcpy(ret, var);

    env = strtok(NULL, "");
    if(env != NULL) {
        ret = strcat(ret, "/");
        ret = strcat(ret, env);
    }
    return ret;
}

void mms_launch(char **args) {
    pid_t pid = fork();
    if (pid == 0) {
        execvp(args[0], args);
    } else if (pid < 0) {
        printf("Forking Error\n");
    } else {
        int status;
        do {
            waitpid(pid, &status, NULL);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

int mms_execute(char **args) {
    if (strcmp(args[0], "cd") == 0) {
        mms_cd(args);
    } else if (strcmp(args[0], "exit") == 0) {
        return 0;
    } else if (strcmp(args[0], "set") == 0) {
        mms_set(args);
    } else {
        mms_launch(args);
    }
    return 1;
}

void mms_cd(char **args) {
    if (args[1] == NULL) {
        printf("Keinen Pfad angegeben\n");
    } else {
        if (chdir(args[1]) != 0) {
            printf("cd error");
        }
    }
}

void mms_set(char **args) {
    int index = 1;
    char str[2];
    while(args[index] != NULL) {
        sprintf(str, "%d", index);
        setenv(str, args[index++], 1);
    }
}
