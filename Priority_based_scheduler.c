//Include the necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//Define the maximum priorities
#define MAX_PRIORITIES 3

//Enum object for contanining task states
typedef enum{
    READY=0,
    RUNNING,
    BLOCKED
}taskCurrState;

//Task Control Block
typedef struct{
    char taskName[20];
    int taskPriority;
    int taskState;
    int taskExecutionTime;
    struct taskCtrlBlk* nextTask;
}taskCtrlBlk;

//A pointer to array of pointers to linked list of type taskCtrlBlk
taskCtrlBlk **tcb;

/*
    A function which simulates task execution and task state switching
    taskCtrlBlk *t => Pointer to the recently executed task
    Returns => A variable of type taskCurrState
*/
taskCurrState executeTask(taskCtrlBlk *t){
    //A static variable to preserve executionCount value
    static int executionCount;

    //Check for every third task coming for execution will be blocked
    if(executionCount >0 && executionCount%3 == 0){
        t->taskState = BLOCKED;
        printf("\nThe task %s is now in BLOCKED state.\n", t->taskName);
        executionCount = 0;
    }

    //If the task is not blocked execute it
    if(t->taskState != BLOCKED){
        printf("\nThe task %s is now in RUNNING state for %d seconds", t->taskName, t->taskExecutionTime);

        //The delay simulate task execution
        sleep(t->taskExecutionTime);

        //Change the task state to READY again and increment the execution count
        t->taskState = READY;
        printf("\nThe task %s has completed its execution and is now in READY state", t->taskName);
        executionCount++;
    }

    //Return the task state
    return (t->taskState);
}

/*
    A function which removes the exeuted task from the list at a given priority
    taskCtrlBlk **b   => Pointer to the priority array
    taskCtrlBlk  *t   => Pointer to the recently executed task
    int currPriority  => The priority of the recently executed task
    taskCtrlBlk *prev => Pointer to the task which was last blocked
    Returns => Nothing
*/
void removeTask(taskCtrlBlk **b, taskCtrlBlk *t, int currPriority, taskCtrlBlk *prev){
    printf("\nThe task being removed now is %s\n", t->taskName);

    //If there was no blocked task previously
    if (prev == NULL){
    b[currPriority] = t->nextTask;
    }
    //Else remove the current task from the middle of previous and next task
    else{
        prev->nextTask = t->nextTask;
    }
    free(t);
}

/*
  A function which simulates scheduler behavior by calling for execution
  and removing them once executed
  taskCtrlBlk **b    => Pointer to the priority array
  int max_priorities => The maximum available priority levels
  Returns => Nothing
*/
void runScheduler(taskCtrlBlk **b, int max_priorities){
    int i;

    //Variables for pointing to current executing task and previous blocked task
    taskCtrlBlk *currTaskPtr, *prevTaskPtr;

    //The shceduler must always run
    while(1){
        //Static variable to preserve number of cycles for executing blocked tasks
        static int blockedCount;
        //Run from highest priority level down to zero
        for(i=max_priorities-1; i>=0; i--){
            //To count ready tasks at given priority
            int readyCount = 0;

            currTaskPtr = b[i];
            prevTaskPtr = NULL;
            //For a given priority run till either there is no READY task
            while(currTaskPtr != NULL){
                //This block is executed if the current task is in blocked state
                if(currTaskPtr->taskState == BLOCKED){
                    blockedCount++;
                    //If blockCycles is equal to 2, change the blocked task to READY
                    if(blockedCount == 2){
                        currTaskPtr->taskState = READY;
                        blockedCount = 0;
                        printf("\nTask %s is now in READY state\n", currTaskPtr->taskName);
                    }
                }
                //If the task is ready, increment the readyCount and change task state to RUNNING
                if(currTaskPtr->taskState == READY){
                    readyCount++;
                    currTaskPtr->taskState = RUNNING;
                    taskCurrState state = executeTask(currTaskPtr);
                    //After execution, if the task is READY state remove it from the list
                    if(state != BLOCKED){
                        removeTask(b, currTaskPtr, i, prevTaskPtr);
                        if(currTaskPtr->nextTask == NULL)
                            currTaskPtr = b[i];
                        else
                            currTaskPtr = currTaskPtr->nextTask;
                    }
                    //Else simply switch to the next task and the blocked task becomes the previous task
                    else{
                        prevTaskPtr = currTaskPtr;
                        currTaskPtr = currTaskPtr->nextTask;
                    }
                }
                else{
                    prevTaskPtr = currTaskPtr;
                    currTaskPtr = currTaskPtr->nextTask;
                }
            }
            //If there is no task at current priority, move to next priority after informing the user
            if(readyCount == 0){
                printf("\nThere is no READY task at priority %d", i+1);
            }
            if(prevTaskPtr != NULL){
                printf("\nThe task %s is blocked at priority %d", prevTaskPtr->taskName, i+1);
            }
        }
        //Once all READY tasks at all priority are executed, one scheduler cycle is complete
        printf("\nThe scheduler has completed its cycle\n");

        //If there are no blocked task, the scheduler exits
        if(blockedCount == 0 && prevTaskPtr == NULL){
            break;
        }
    }
}

/*
    A function to simulate task creation, assigning name and priority
    char *s => String literal for receiving task name
    int num_priority => Integer for receiving task priority
    int exetime => Integer for receiving the task's time of execution
    Returns => Nothing
*/
void createTask(char* s, int num_priority, int exeTime){
    //Create a task control block for new task
    taskCtrlBlk *newTask = (taskCtrlBlk *)malloc(sizeof(taskCtrlBlk));
    if(newTask==NULL){
        printf("\nNew Task Creation Failed\n");
    }

    //Temporary variable for swapping
    taskCtrlBlk *temp;

    //Ask the user for the priority of the new task
    if(num_priority < 1 || num_priority > MAX_PRIORITIES){
        printf("\nPlease enter a valid priority between 1 and %d", MAX_PRIORITIES);
        free(newTask);
        return;
    }

    //Assign the priority to the new task
    newTask->taskPriority = num_priority;

    //Assign the name to the new task
    strcpy(newTask->taskName, s);

    //Assign the execution time for the task
    newTask->taskExecutionTime = exeTime;

    //The new task will pre-empt the already running task, so it will be in READY state
    newTask->taskState = READY;

    //At the decided priority level, insert the new task at the head of the linked list
    temp = tcb[num_priority-1];
    tcb[num_priority-1] = newTask;
    newTask->nextTask = temp;

    //Log the task creation
    printf("Task %s is created with priority %d and is added to scheduler.\n", s,num_priority);

}

int main(){
    //Create the priority array
    tcb = (taskCtrlBlk **)calloc(MAX_PRIORITIES, sizeof(taskCtrlBlk *));

    //Three tasks at priority 3, two tasks at priority 2 and one task at priority 1
    createTask("Print Hello World", 1, 5);
    createTask("Print My Name", 3, 5);
    createTask("LED Blink", 2, 6);
    createTask("Servo rotate", 3, 2);
    createTask("Temperature Task", 2, 7);
    createTask("LCD Task", 3, 10);
    createTask("LDR Task", 1, 8);
    createTask("Door Task", 2, 9);

    //Run the scheduler
    runScheduler(tcb, MAX_PRIORITIES);

    //Free the tcb array
    free(tcb);
}
