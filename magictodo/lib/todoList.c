#include "todoList.h"

static const short STR_SIZE = 1025;
static short start = 1;

static void flush() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static void error(FILE *input) {
    printf("Corrupted input file\n");
    fclose(input);
}

static void saveToFile() {
    if(pq == NULL){
        return;
    }
    FILE *output = NULL;
    output = fopen("task.dat", "w");
    if (output != NULL) {
        fprintf(output, "%ld\n", pq->length);
        for (long pri = pq->length; pq->length != 0; --pri) {
            fprintf(output, "%s%ld\n", (char *) extractMaxPQ(pq), pri);
        }
        fflush(output);
        fclose(output);
    } else {
        printf("Can't save tasks to file\n");
    }


}

static void loadFromFile() {
    FILE *input = NULL;
    input = fopen("task.dat", "r");
    if (input != NULL) {
        size_t length;
        if (fscanf(input, "%ld", &length) != 1) {
            error(input);
            return;
        }
        while (fgetc(input) != '\n');
        for (int i = 0; i < length; ++i) {
            char desc[STR_SIZE];
            int priority;
            if (fgets(desc, STR_SIZE - 1, input) == NULL) {
                error(input);
                return;
            }
            if (fscanf(input, "%d", &priority) != 1) {
                error(input);
                return;
            }
            while (fgetc(input) != '\n');
            if (insertPQ(pq, priority, desc) == 0) {
                printf("Problem with memory allocation");
                saveToFile();
                destroyPQ(pq);
                exit(666);
            }
        }
        fclose(input);
    } else {
        if (!start) {
            printf("Can't read tasks from file\n");
        }
    }
}


static void addNewTask() {
    flush();
    char input[STR_SIZE];
    int priority;
    printf("Enter description (1024 symbols):\n");
    fgets(input, STR_SIZE, stdin);
    flush();
    printf("Enter task priority:\n");
    scanf("%d", &priority);
    if (insertPQ(pq, priority, input) == 0){
        printf("Problem with memory allocation");
        saveToFile();
        destroyPQ(pq);
        exit(666);
    }
}

static void getTask() {
    char *temp = extractMaxPQ(pq);
    if (temp == NULL) {
        printf("No tasks today, bro!\n");
    } else {
        printf("Here's your task, stranger!\n-------------------------\n");
        printf("%s", temp);
        printf("-------------------------\n");
    }
    free(temp);
}

int init() {
    if (pq != NULL) {
        destroyPQ(pq);
    }
    pq = createPQ(sizeof(char) * STR_SIZE);
    if (start) {
        loadFromFile();

    }
    return menu();
}

int menu() { //TODO Починить стек вызовов (Починился?)
    while (1) {
        if (!start) {
            flush();
        } else {
            start = 0;
        }
        printf("Please choose action\n(1)\tAdd new task\n(2)\tGet task\n(3)\tClear all\n(4)\tLoad from file\n(5)\tSave to file\n(6)\tNumber of tasks\n(0)\tExit\n");
        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addNewTask();
                continue;
            case 2:
                getTask();
                continue;
            case 3:
                return 1;
            case 4:
                loadFromFile(); //Предположим, что мы не хотим чистить
                continue;
            case 5:
                saveToFile();
                continue;
            case 6:
                printf("Stored tasks: %ld\n", getLengthPQ(pq));
                continue;
            case 0:
                saveToFile();
                destroyPQ(pq);
                return 0;
            default:
                printf("Incorrect input\n");
                flush();
                continue;
        }
    }


}
