
# Priority based Scheduler using C

The features of scheduler are as below:
1. It features a priority array, which consists of pointers to linked lists of tasks.
2. The tasks are represented with help of struct blocks containing parameters such as task name, state, priority, execution time.
3. For each task, there can be three states possible - READY, RUNNING and BLOCKED.
4. When a task is created at a particular priority, it is inserted at the head of the linked list at that priority. 
5. The scheduler runs in a while(1) loop and breaks if there is no task left at any priority, in any state.
6. The scheduler starts executing tasks from the highest priority with the head of the list to be executed first.
7. The task execution is simulated simply by using delays equal to the task execution time, created using the sleep() function.
8. Once executed, the task is removed from the list and head of the list now points to the task next to the one which just executed. 
9. Every fourth task that arrives for execution, gets into blocked state.
10. A pointer variable keeps track of blocked task and the current task pointer moves to the next task. 
11. A variable "blockedCount" keeps record of how many times a blocked task is revisited.
12. When it is equal to 2 the task's state changes to READY and gets executed.
13. A scheduler is said to complete its cycle when it executes all the READY tasks and revisits the BLOCKED tasks in next cycle.

## Priority_Array_Structure

![Priority_Array_Structure](https://raw.githubusercontent.com/Lalit2612/Priority-Based-Scheduler/refs/heads/master/Example_image.jpg)


## Output Demo
![Task_Creation_Log](https://raw.githubusercontent.com/Lalit2612/Priority-Based-Scheduler/refs/heads/master/Task_Creation_Log.jpg)

![First_Scheduler_Cycle](https://raw.githubusercontent.com/Lalit2612/Priority-Based-Scheduler/refs/heads/master/First_Scheduler_Cycle.jpg)

![Second_Scheduler_Cycle](https://raw.githubusercontent.com/Lalit2612/Priority-Based-Scheduler/refs/heads/master/Second_Scheduler_Cycle.jpg)
