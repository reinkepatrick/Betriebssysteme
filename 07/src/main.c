#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define STDOUT 1
#define STDERR 2

void out(int dest, const char *content)
{
    write(dest, content, strlen(content));
}

void perror(const char *msg)
{
    out(STDERR, msg);
}

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        perror("Falsche Anzahl Argumente.\n");
        return EXIT_FAILURE;
    }

    //Datei öffnen
    int filedes = open(argv[1], O_RDONLY);

    if (filedes < 0)
    {
        perror("Datei konnte nicht geoeffnet werden.\n");
        return EXIT_FAILURE;
    }

    //Dateilänge bestimmen
    off_t filesize = lseek(filedes, 0, SEEK_END);

    if(filesize == 0)
    {
        perror("Datei ist leer.\n");
        return EXIT_FAILURE;
    }

    char *buffer = (char *)malloc((size_t)filesize + 10);
    char *ptr = buffer;

    //Datei einlesen
    lseek(filedes, 0, SEEK_SET);
    if(read(filedes, buffer, filesize) < 0)
    {
        perror("Fehler beim Lesen der Datei.");
        return EXIT_FAILURE;
    }
    if(close(filedes))
    {
        perror("Fehler beim schließen der Datei.");
        return EXIT_FAILURE;
    }

    //Erste Hälfte ausgeben
    out(STDOUT, "Zweite Haelfte:\n");
    ptr += (filesize / 2);  //+1 entfernt zeilenumbruch; kann evtl. weg
    out(STDOUT, ptr);

    //Zweite Hälfte ausgeben; Ausgabe mit strlen bis NULL
    out(STDOUT, "\nErste Haelfte:\n");
    char temp = *ptr;
    *ptr = NULL;
    out(STDOUT, buffer);
    *ptr = temp;

    //Neue Datei öffnen
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;
    filedes = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, mode);
    out(filedes, buffer);


    return EXIT_SUCCESS;
}
