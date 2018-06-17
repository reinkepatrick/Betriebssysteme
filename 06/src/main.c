#include <stdio.h>
#include <pthread.h>
#include <dirent.h>
#include <string.h>
#include "../include/miniz.h"
#include "../include/queue.h"

#define THREADS 1

typedef struct job
{
    char *content;
    const char *path;
} Job;

typedef struct
{
    Queue queue;
    pthread_mutex_t mutex;
    pthread_cond_t is_empty;
    int empty;
    int done;
} Jobs;

typedef struct
{
    int id;
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
                job->content = read_file(job->path); //maybe empty :(
                printf("%s eingelesen und hinzugefügt\n", job->path);

                //sperren - hinzufügen - entsperren
                pthread_mutex_lock(&reader_arg->jobs.mutex);
                queue_insert(reader_arg->jobs.queue, job);
                reader_arg->jobs.empty = 0;
                pthread_mutex_unlock(&reader_arg->jobs.mutex);
                pthread_cond_signal(&reader_arg->jobs.is_empty);
            }
        }
        reader_arg->jobs.done = 1;
    }
    else
    {
        printf("Fehler beim öffnen des Verzeichnis\n");
    }

    pthread_exit((void *)NULL);
}

void *compress_thread(void *arg)
{
    Args *args = (Args *)arg;
    printf("Compression %d gestartet\n", args->id);

    while (1)
    {
        //printf("while");
        pthread_mutex_lock(&args->jobs.mutex);
        while (args->jobs.empty == 1)
        {
            pthread_cond_wait(&args->jobs.is_empty, &args->jobs.mutex);
        }
        int done = args->jobs.done;
        Job *job = queue_head(args->jobs.queue);
        queue_delete(args->jobs.queue);
        pthread_mutex_unlock(&args->jobs.mutex);
        if (job != NULL)
        {
            printf("Compression-Thread %d komprimiert %s", args->id, job->path);
        }
        else if (done == 1)
        {
            break;
        }
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
    pthread_cond_init(&jobs.is_empty, NULL);
    jobs.empty = 1;
    jobs.done = 0;
    DIR *dir = opendir(argv[1]);

    if (dir == NULL)
        return EXIT_FAILURE;

    //Arguments for Reader
    Args r_args;
    r_args.jobs = jobs;
    r_args.path = (char *)argv[1];
    r_args.dir = dir;

    //Reader starten
    pthread_t reader, compress[THREADS];
    if (pthread_create(&reader, NULL, &reader_thread, &r_args) != 0)
    {
        printf("Fehler beim Erstellen des Readers\n");
        return EXIT_FAILURE;
    }

    //Compression Threads starten
    for (int i = 0; i < THREADS; i++)
    {
        Args c_args;
        c_args.jobs = jobs;
        c_args.id = i;

        if (pthread_create(&compress[i], NULL, &compress_thread, &c_args) != 0)
        {
            printf("Fehler beim Erstellen des Compr\n");
            return EXIT_FAILURE;
        }
    }

    //auf beenden der Threads warten
    pthread_join(reader, NULL);
    printf("Reader wurde erfolgreich beendet.\n");
    for (int i = 0; i < THREADS; i++)
    {
        pthread_join(compress[i], NULL);
        printf("%d Compression wurde erfolgreich beendet.\n", i);
    }

    return EXIT_SUCCESS;
}
