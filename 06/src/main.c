#include <stdio.h>
#include <pthread.h>
#include <dirent.h>
#include "../include/miniz.h"
#include "../include/queue.h"

typedef struct Job {
    const char *name;
} Job;

static Queue queue;

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        printf("Falsche Anzahl Argumente\n");
        return EXIT_FAILURE;
    }

    DIR *dir = opendir(argv[1]);
    
    if (dir != NULL){
        queue = queue_create();
    } else {
        printf("Fehler beim öffnen des Verzeichnis\n");
    }

    return EXIT_SUCCESS;
}
