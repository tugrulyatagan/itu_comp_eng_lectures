//============================================================================
// Name			: 040100117.cpp
// Author		: Tugrul Yatagan
// Student Num	: 040100117
// Course		: BLG 312E Computer Operating Systems
// CRN			: 21661
// Lecturer		: Sima Uyar Etaner
// Date			: 11.04.2014
//============================================================================

#include <stdio.h>
#include <stdlib.h> // for malloc, free
#include <pthread.h> // for thread operations
#include <sys/sem.h> // for semaphore operations
#define SEMKEY 15 // random semaphore key value


typedef struct Queue { // queue implementation for orders
	int *content; // integer array for queue content
	int front; // front index number for queue
	int end; // end index number for queue
	int size; // size of queue
} Queue;

Queue orders_queue; // global orders queue data structure
int *orders; // global raw order array which is read from input
int next_order = 0; // next new order element for taking order from orders raw array
int s; // counter semaphore for synchronization two threads
FILE *output_file; // global output file pointer

void semCreate() {
	s = semget(SEMKEY, 1, 0700 | IPC_CREAT); // create semaphore
	semctl(s, 0, SETVAL, 0); // set default semaphore value = 0
}
void semSignal(int semid, int val) { // semaphore increment operation
	struct sembuf semaphore;
	semaphore.sem_num = 0;
	semaphore.sem_op = val; // increment semaphore
	semaphore.sem_flg = 1; // add sem_op to value
	semop(semid, &semaphore, 1); // make semaphore operation
}
void semWait(int semid, int val) { // semaphore decrement operation
	struct sembuf semaphore;
	semaphore.sem_num = 0;
	semaphore.sem_op = (-1 * val); // decrement semaphore
	semaphore.sem_flg = 1; // add sem_op to value
	semop(semid, &semaphore, 1);  // make semaphore operation
}

void QueueCreate(int size) { // create queue, allocate memory, initialize variables
	orders_queue.content = (int*) malloc((size+1) * sizeof(int)); // allocate memory for queue
	orders_queue.front = 0; // initialize variable
	orders_queue.end = 0; // initialize variable
	orders_queue.size = size; // assign size
}
void QueueDelete() { // delete queue
	free(orders_queue.content); // deallocate queue
}
int QueueIsEmpty() { // check queue is empty or not
	if (orders_queue.end == orders_queue.front) { // if end index equals front index
		return 1; // empty
	} else {
		return 0; // not empty
	}
}
int QueueDequeue() { // dequeue first element of the queue
	int result = orders_queue.content[orders_queue.front]; // take first element
	orders_queue.front++; // pass taken element
	return result;

}
void QueueEnqueue(int newOrder) { // enqueue new element to the end of the queue
	orders_queue.content[orders_queue.end] = newOrder; // assign new element
	orders_queue.end++; // to the end of the queue
}
int QueueHead() { // return next element in the queue in order
	return orders_queue.content[orders_queue.front]; //
}

int readFile(const char *filename) { // read input file to the raw orders array
	int line_number = 0, index;
	FILE *input_file = fopen(filename, "r"); // open input file for reading
	if (input_file != NULL) {
		char line[5];
		while (fgets(line, sizeof(line), input_file) != NULL) { // count number of lines
			line_number++;
		}
		rewind(input_file); // bring file cursor to the beginning of the file
		orders = (int*) malloc((line_number + 1) * sizeof(int)); // allocate array according to size

		for (index = 0; fgets(line, sizeof line, input_file) != NULL; index++) { // read file line by line
			orders[index] = line[0] - '0'; // assign elements to the raw orders array
		}
		fclose(input_file); // close input file
	} else {
		perror("Error opening input file");
		exit(-1);
	}
	return line_number; // return size
}

void* serverFunction(void *arg) { // server thread's function
	int k;
	for (k = 0; k < orders_queue.size - 1; k++) { // take orders in turn
		semWait(s, 1); // P(s) wait for server thread and decrement counter semaphore s
		int makeOrder = QueueHead(); // look order from queue
		if (makeOrder == 1) { // sleep according to order type for simulating server operation
			sleep(1);
		} else if (makeOrder == 2) {
			sleep(2);
		} else if (makeOrder == 3) {
			sleep(3);
		}
		QueueDequeue(); // take order from queue
		printf("Server: Type %d is ready to be served\n", makeOrder);
		fprintf(output_file, "Server: Type %d is ready to be served\n", makeOrder); // write result to the output file
	}
	pthread_exit(NULL); // when queue is finished, terminate server thread
}

void* cashierFunction(void *arg) { // cashier thread's function
	int k;
	for (k = 0; k < orders_queue.size - 1; k++) { // make orders in turn
		sleep(1); // sleep for simulating order taking operation
		QueueEnqueue(orders[next_order]); // add next order element to the queue
		printf("Cashier: Type %d is ordered\n", orders[next_order]);
		fprintf(output_file, "Cashier: Type %d is ordered\n", orders[next_order]); // write result to the output file
		next_order++; // prepare raw order array for next order index
		semSignal(s, 1); // V(s) increment counter semaphore s
	}
	pthread_exit(NULL); // when all orders taken, terminate cashier thread
}

int main(int argc, char *argv[]) { // take command line arguments
	if (argc != 3) { // check command line arguments number
		printf("Error, wrong command line arguments.\n");
		exit(-1);
	}

	int size = readFile(argv[1]); // read file and take size
	QueueCreate(size); // create queue for given size
	semCreate(); // create semaphore

	output_file = fopen(argv[2], "w"); // open output file for writing
	if (output_file == NULL) { // check for an error
		printf("Error opening output file!\n");
		exit(1);
	}

	pthread_t server, cahsier; // define server and cashier thread pointers
	int rc, i;

	rc = pthread_create(&cahsier, NULL, cashierFunction, (void *) i); // start cashier thread
	if (rc) { // check cashier thread for an error
		printf("Cashier thread creation error ...\n");
		exit(-1);
	}

	rc = pthread_create(&server, NULL, serverFunction, (void *) i); // start server thread
	if (rc) { // check server thread for an error
		printf("Server thread creation error ...\n");
		exit(-1);
	}

	pthread_join(cahsier, NULL); // wait for cashier thread to finish
	pthread_join(server, NULL); // wait for server thread to finish

	fclose(output_file); // close output file
	semctl(s, 0, IPC_RMID, 0); // remove semaphore
	QueueDelete(); // deallocate queue
	free(orders); // deallocate raw orders array

	printf("\nAll executions are completed. Exiting.\n");
	return 0;
}
