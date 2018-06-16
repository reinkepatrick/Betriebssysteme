#include <stdio.h>
#include <pthread.h>
#include <dirent.h>
#include <string.h>
#include "../include/miniz.h"
#include "../include/queue.h"

typedef struct job
{
    char *content;
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
    char *path;
    DIR *dir;
} Args;

char *read_file(const char *path)
{
    char *buffer = "";
    FILE *file = fopen(path, "r");

    if (file == NULL)
        return buffer;

    buffer = malloc(ftell(file));
    fread(buffer, 1, ftell(file), file);
    fclose(file);
    return buffer;
}

void *reader_thread(void *arg)
{
    printf("Reader gestartet.\n");

    Args *reader_arg = (Args *)arg;

    if (reader_arg->dir != NULL)
    {
        struct dirent *ent;
        while ((ent = readdir(reader_arg->dir)) != NULL)
        {
            //auf dateiendung prüfen
            char *extension = strrchr(ent->d_name, '.');
            if (extension != 0 && strcmp(extension, ".") && strcmp(extension, ".DS_Store") && strcmp(extension, ".compr"))
            {
                //neuen Job erstellen
                Job *job = (Job *)malloc(sizeof(Job));
                job->path = strcat(strdup(reader_arg->path), ent->d_name);
                job->content = read_file(job->path);
                printf("%s\n", job->content);

                //sperren - hinzufügen - entsperren
                pthread_mutex_lock(&reader_arg->jobs.mutex);
                queue_insert(reader_arg->jobs.queue, job);
                pthread_mutex_unlock(&reader_arg->jobs.mutex);
            }
        }
    }
    else
    {
        printf("Fehler beim öffnen des Verzeichnis\n");
    }
    pthread_exit((void *)NULL);
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
    DIR *dir = opendir(argv[1]);

    if (dir == NULL)
        return EXIT_FAILURE;

    //Arguments for Threads
    Args args;
    args.jobs = jobs;
    args.path = (char *)argv[1];
    args.dir = dir;

    //Threads starten
    pthread_t reader, compress;
    if (pthread_create(&reader, NULL, &reader_thread, &args) != 0)
    {
        printf("Fehler beim Erstellen des Readers\n");
        return EXIT_FAILURE;
    }

    pthread_join(reader, NULL);

    return EXIT_SUCCESS;
}
