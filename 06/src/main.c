#include <stdio.h>
#include <pthread.h>
#include <dirent.h>
#include "../include/miniz.h"
#include "../include/queue.h"

typedef struct Job
{
    const char *content;
    const char *path;
} Job;

typedef struct
{
    Queue queue;
    pthread_mutex_t mutex;
    int empty;
} Jobs;

typedef struct
{
    Jobs jobs;
    const char *path;
} Args;

struct dirent *ent;

void* reader_thread(void *arg)
{
    printf("Reader gestartet.\n");

    /*
    Args *reader_arg = (Args *) arg;

    DIR *dir = opendir(reader_arg->path);
    if (dir != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
            queue_insert(NULL, NULL);
    }
    else
    {
        printf("Fehler beim öffnen des Verzeichnis\n");
    }
    */
    return (void *)NULL;
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Falsche Anzahl Argumente\n");
        return EXIT_FAILURE;
    }

    //Init Queue
    Jobs jobs;
    jobs.queue = queue_create();
    pthread_mutex_init(&jobs.mutex, NULL);

    //Arguments for Threads
    Args args;
    args.jobs = jobs;
    args.path = argv[1];

    //
    pthread_t reader, compress;
    if(pthread_create(&reader, NULL, &reader_thread, &args) != 0) 
    {
        printf("Fehler beim Erstellen des Readers\n");
        return EXIT_FAILURE;
    }

    pthread_join(reader, NULL);

    return EXIT_SUCCESS;
}
