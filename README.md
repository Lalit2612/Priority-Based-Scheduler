
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

![Priority_Array_Structure](https://raw.githubusercontent.com/Lalit2612/Priority-Based-Scheduler/refs/heads/master/Priority_Array_Structure.png)


## Output Demo

Task Print Hello World is created with priority 1 and is added to scheduler.
Task Print My Name is created with priority 3 and is added to scheduler.
Task LED Blink is created with priority 2 and is added to scheduler.
Task Servo rotate is created with priority 3 and is added to scheduler.
Task Temperature Task is created with priority 2 and is added to scheduler.
Task LCD Task is created with priority 3 and is added to scheduler.
Task LDR Task is created with priority 1 and is added to scheduler.
Task Door Task is created with priority 2 and is added to scheduler.

The task LCD Task is now in RUNNING state for 10 seconds
The task LCD Task has completed its execution and is now in READY state
The task being removed now is LCD Task

The task Servo rotate is now in RUNNING state for 2 seconds
The task Servo rotate has completed its execution and is now in READY state
The task being removed now is Servo rotate

The task Print My Name is now in RUNNING state for 5 seconds
The task Print My Name has completed its execution and is now in READY state
The task being removed now is Print My Name

The task Door Task is now in BLOCKED state.

The task Temperature Task is now in RUNNING state for 7 seconds
The task Temperature Task has completed its execution and is now in READY state
The task being removed now is Temperature Task

The task LED Blink is now in RUNNING state for 6 seconds
The task LED Blink has completed its execution and is now in READY state
The task being removed now is LED Blink

The task Door Task is blocked at priority 2
The task LDR Task is now in RUNNING state for 8 seconds
The task LDR Task has completed its execution and is now in READY state
The task being removed now is LDR Task

The task Print Hello World is now in BLOCKED state.

The task Print Hello World is blocked at priority 1
The scheduler has completed its cycle

There is no READY task at priority 3
Task Door Task is now in READY state

The task Door Task is now in RUNNING state for 9 seconds
The task Door Task has completed its execution and is now in READY state
The task being removed now is Door Task

There is no READY task at priority 1
The task Print Hello World is blocked at priority 1
The scheduler has completed its cycle

There is no READY task at priority 3
There is no READY task at priority 2
Task Print Hello World is now in READY state

The task Print Hello World is now in RUNNING state for 5 seconds
The task Print Hello World has completed its execution and is now in READY state
The task being removed now is Print Hello World

The scheduler has completed its cycle

Process returned 0 (0x0)   execution time : 52.159 s
Press any key to continue.