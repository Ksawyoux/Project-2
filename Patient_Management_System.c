#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME_LENGTH 50
#define MAX_SSN_LENGTH 12
#define MAX_TASK_LENGTH 50
#define MAX_QUEUE_SIZE 100

typedef struct
{
    int day;
    int month;
    int year;
} DateOfBirth;

typedef struct
{
    char name[MAX_NAME_LENGTH];
    char gender[10];
    char ssn[MAX_SSN_LENGTH];
    DateOfBirth dob;
} Patient;

typedef struct
{
    Patient patient;
    char task[MAX_TASK_LENGTH];
    int priority;
    time_t timestamp;
} QueueElement;

typedef struct
{
    QueueElement elements[MAX_QUEUE_SIZE];
    int size;
} PriorityQueue;

void initializePriorityQueue(PriorityQueue *pq)
{
    pq->size = 0;
}

int isSSNDuplicate(PriorityQueue *pq, const char *ssn)
{
    for (int i = 0; i < pq->size; i++)
    {
        if (strcmp(pq->elements[i].patient.ssn, ssn) == 0)
        {
            return 1; // Duplicate SSN found
        }
    }
    return 0; // No duplicate SSN
}

void upheap(PriorityQueue *pq, int index)
{
    QueueElement temp = pq->elements[index];
    int parentIndex;

    while (index > 0)
    {
        parentIndex = (index - 1) / 2;
        if (pq->elements[parentIndex].priority > temp.priority ||
            (pq->elements[parentIndex].priority == temp.priority &&
             difftime(pq->elements[parentIndex].timestamp, temp.timestamp) > 0))
        {
            pq->elements[index] = pq->elements[parentIndex];
            index = parentIndex;
        }
        else
        {
            break;
        }
    }
    pq->elements[index] = temp;
}

void downheap(PriorityQueue *pq, int index)
{
    QueueElement temp = pq->elements[index];
    int childIndex, rightChild;

    while ((childIndex = 2 * index + 1) < pq->size)
    {
        rightChild = childIndex + 1;
        if (rightChild < pq->size && (pq->elements[rightChild].priority < pq->elements[childIndex].priority ||
                                      (pq->elements[rightChild].priority == pq->elements[childIndex].priority &&
                                       difftime(pq->elements[rightChild].timestamp, pq->elements[childIndex].timestamp) < 0)))
        {
            childIndex = rightChild;
        }

        if (pq->elements[childIndex].priority < temp.priority ||
            (pq->elements[childIndex].priority == temp.priority &&
             difftime(pq->elements[childIndex].timestamp, temp.timestamp) < 0))
        {
            pq->elements[index] = pq->elements[childIndex];
            index = childIndex;
        }
        else
        {
            break;
        }
    }
    pq->elements[index] = temp;
}

void newPatient(PriorityQueue *pq)
{
    if (pq->size == MAX_QUEUE_SIZE)
    {
        printf("Queue is full. Cannot add new patient.\n");
        return;
    }

    QueueElement element;
    printf("Enter patient name: ");
    fgets(element.patient.name, MAX_NAME_LENGTH, stdin);
    element.patient.name[strcspn(element.patient.name, "\n")] = '\0';

    printf("Enter gender (male/female): ");
    fgets(element.patient.gender, sizeof(element.patient.gender), stdin);
    element.patient.gender[strcspn(element.patient.gender, "\n")] = '\0';

    printf("Enter SSN: ");
    fgets(element.patient.ssn, MAX_SSN_LENGTH, stdin);
    element.patient.ssn[strcspn(element.patient.ssn, "\n")] = '\0';

    if (isSSNDuplicate(pq, element.patient.ssn))
    {
        printf("Error: Duplicate SSN detected.\n");
        return;
    }

    printf("Enter date of birth (day month year): ");
    scanf("%d %d %d", &element.patient.dob.day, &element.patient.dob.month, &element.patient.dob.year);
    getchar(); // Clear the buffer

    printf("Enter patient task (surgery, X-ray scan, blood test, physical examination): ");
    fgets(element.task, MAX_TASK_LENGTH, stdin);
    element.task[strcspn(element.task, "\n")] = '\0';

    if (strcmp(element.task, "surgery") == 0)
    {
        element.priority = 1;
    }
    else if (strcmp(element.task, "X-ray scan") == 0)
    {
        element.priority = 2;
    }
    else if (strcmp(element.task, "blood test") == 0)
    {
        element.priority = 3;
    }
    else if (strcmp(element.task, "physical examination") == 0)
    {
        element.priority = 4;
    }
    else
    {
        printf("Invalid task. Setting priority to lowest.\n");
        element.priority = 5;
    }

    element.timestamp = time(NULL); // Set the current time as timestamp
    pq->elements[pq->size] = element;
    pq->size++;
    upheap(pq, pq->size - 1);

    printf("Patient added successfully.\n");
}

void processPatient(PriorityQueue *pq)
{
    if (pq->size == 0)
    {
        printf("No patients in the queue.\n");
        return;
    }

    QueueElement patient = pq->elements[0];
    printf("Processing patient: %s, Task: %s\n", patient.patient.name, patient.task);

    pq->elements[0] = pq->elements[--pq->size];
    downheap(pq, 0);
}

void updatePatient(PriorityQueue *pq)
{
    if (pq->size == 0)
    {
        printf("No patients in the queue.\n");
        return;
    }

    char ssn[MAX_SSN_LENGTH];
    printf("Enter SSN of the patient to update: ");
    fgets(ssn, MAX_SSN_LENGTH, stdin);
    ssn[strcspn(ssn, "\n")] = '\0';

    for (int i = 0; i < pq->size; i++)
    {
        if (strcmp(pq->elements[i].patient.ssn, ssn) == 0)
        {
            printf("Enter new priority (1-Critical, 2-High, 3-Medium, 4-Low): ");
            scanf("%d", &pq->elements[i].priority);
            getchar(); // Clear the buffer

            // Update the task based on the new priority
            switch (pq->elements[i].priority)
            {
            case 1:
                strcpy(pq->elements[i].task, "surgery");
                break;
            case 2:
                strcpy(pq->elements[i].task, "X-ray scan");
                break;
            case 3:
                strcpy(pq->elements[i].task, "blood test");
                break;
            case 4:
                strcpy(pq->elements[i].task, "physical examination");
                break;
            default:
                strcpy(pq->elements[i].task, "general care");
                printf("No specific task for this priority level. Defaulting to 'general care'.\n");
                break;
            }

            pq->elements[i].timestamp = time(NULL); // Update timestamp for new priority
            upheap(pq, i);
            downheap(pq, i);

            printf("Patient priority and task updated successfully.\n");
            return;
        }
    }

    printf("Patient not found with SSN: %s\n", ssn);
}

void displayPatients(PriorityQueue *pq)
{
    if (pq->size == 0)
    {
        printf("No patients in the queue.\n");
        return;
    }

    printf("Patients in the queue:\n");
    for (int i = 0; i < pq->size; i++)
    {
        QueueElement patient = pq->elements[i];
        struct tm *timeinfo = localtime(&patient.timestamp);
        char formattedTime[20];
        strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d %H:%M:%S", timeinfo);

        printf("Name: %s, Gender: %s, DOB: %02d/%02d/%04d, SSN: %s, Task: %s, Priority: %d, Timestamp: %s\n",
               patient.patient.name, patient.patient.gender, patient.patient.dob.day, patient.patient.dob.month, patient.patient.dob.year,
               patient.patient.ssn, patient.task, patient.priority, formattedTime);
    }
}

int main()
{
    PriorityQueue pq;
    initializePriorityQueue(&pq);

    int choice;
    do
    {
        printf("\nHospital Management System\n");
        printf("1. Add New Patient\n");
        printf("2. Process Next Patient\n");
        printf("3. Update Patient Priority\n");
        printf("4. Display All Patients\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar(); // Clear newline character left in input buffer

        switch (choice)
        {
        case 1:
            newPatient(&pq);
            break;
        case 2:
            processPatient(&pq);
            break;
        case 3:
            updatePatient(&pq);
            break;
        case 4:
            displayPatients(&pq);
            break;
        case 5:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
