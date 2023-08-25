#ifndef _PASTEVENTS_H_
#define _PASTEVENTS_H_

#define MAX_HISTORY_SIZE 15
#define MAX_COMMAND_LENGTH 100


 

void initialiseHistory();
void displayHistory();
void addtoHistory(char *argc);
void purge();

// Define a structure to represent a command history entry
// typedef struct DequeNode
// {
//     char *command;
//     struct DequeNode *next;
//     struct DequeNode *prev;
// } DequeNode;

// typedef struct Deque
// {
//     DequeNode *front;
//     DequeNode *rear;
//     int size;
// } Deque;


// // Define a circular buffer for storing command history

// int historySize = 0;  // Current number of commands in history
// int historyIndex = 0; // Index for the next command to be added
// void addToHistory(char *command);
// void past(char **argc);
// void purge();
// void execute(char *index);
// void initialiseHistory();
// void displayHistory(Deque *commandDeque);
// void deDeque(Deque *commandDeque);
// void enDeque(char *command, Deque *commandDeque);
// DequeNode *createDequeNode(char *command);

// Deque *createDeque();
#endif