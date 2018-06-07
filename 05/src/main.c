#include <stdio.h>
#include <pthread.h>
#include "../include/lists.h"

//Liststuff
typedef struct Job
{
    LIST_NODE_HEADER(struct Job);
    char name[64];
    float time;
    int prio;
} Job;

typedef struct
{
    LIST_HEADER(Job);
    int prio;
} JobList;

void addJob(JobList *jobs, char name[64], float time, int prio)
{
    Job *job = LIST_NEW_NODE(Job);
    strcpy(job->name, name);
    job->time = time;
    job->prio = prio;
    jobs->prio += prio;
    List_append(&*jobs, job);
}

int compareTime(Job *job1, Job *job2, void *dummy)
{
    return (int)job1->time - job2->time;
}

int comparePrio(Job *job1, Job *job2, void *dummy)
{
    return job2->prio - job1->prio;
}

int comparePrioAndTime(Job *job1, Job *job2, void *dummy)
{
    return (int)(job1->time / job1->prio) - (job2->time / job2->prio);
}
//Liststuff End

void firstComeFirstServe(JobList *jobs)
{
    Job *job = jobs->head;
    float avgResidenceTime = 0.0, currentTime = 0.0;
    int count = jobs->count;
    while (job != NULL)
    {
        currentTime += job->time;
        avgResidenceTime += (job->time * count--);
        printf("%s wurde abgearbeitet. Aktuelle Zeit: %.0f)\n", job->name, currentTime);
        job = job->next;
    }
    printf("Mittlere Verweilzeit: %.3f\n\n", avgResidenceTime / jobs->count);
}

void shortestJobFirst(JobList *jobs)
{
    List_sort(&*jobs, (ListNodeCompareFunction)compareTime, NULL);
    firstComeFirstServe(jobs);
}

void prioScheduling(JobList *jobs)
{
    List_sort(&*jobs, (ListNodeCompareFunction)comparePrio, NULL);
    firstComeFirstServe(jobs);
}

void constRoundRobin(JobList *jobs)
{
    List_sort(&*jobs, (ListNodeCompareFunction)compareTime, NULL);
    int count = jobs->count;
    float residenceTime = 0.0, sumResidenceTime = 0.0;
    Job *outerJob = jobs->head;
    Job *innerJob;

    while (outerJob != NULL)
    {
        float prevTime, workingTime = outerJob->time;
        innerJob = outerJob;
        printf("\nEs wird an den folgenden Jobs gearbeitet: \n");
        while (innerJob != NULL)
        {
            if (innerJob->time - workingTime == 0.0)
            {
                residenceTime += ((innerJob->time - prevTime) * count--);
                sumResidenceTime += residenceTime;
                prevTime = innerJob->time;
            }
            printf("  Es wurde %.0f Minuten an %s gearbeitet.\n", residenceTime, innerJob->name);
            innerJob = innerJob->next;
        }
        printf("  %s wurde abgearbeitet.\n", outerJob->name);
        outerJob = outerJob->next;
    }
    printf("\nMittlere Verweilzeit: %.3f\n\n", sumResidenceTime / jobs->count);
}

void prioRoundRobin(JobList *jobs)
{
    List_sort(&*jobs, (ListNodeCompareFunction)comparePrioAndTime, NULL);
    Job *outerJob = jobs->head;
    while (outerJob != NULL)
    {
    }
}

int main()
{
    JobList jobs;
    List_init(&jobs);
    jobs.prio = 0;

    addJob(&jobs, "A", 30.0, 2);
    addJob(&jobs, "B", 20.0, 1);
    addJob(&jobs, "C", 25.0, 5);
    addJob(&jobs, "D", 28.0, 4);
    addJob(&jobs, "E", 18.0, 3);

    printf("First Come First Serve\n");
    firstComeFirstServe(&jobs);

    printf("Shortest Job First\n");
    shortestJobFirst(&jobs);

    printf("Prio Scheduling\n");
    prioScheduling(&jobs);

    printf("Round Robin Konstant\n");
    constRoundRobin(&jobs);

    printf("Round Robin mit Prioritäten\n");
    prioRoundRobin(&jobs);

    return EXIT_SUCCESS;
}
