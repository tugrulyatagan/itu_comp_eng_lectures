//============================================================================
// Name			: 040100117.cpp
// Author		: Tugrul Yatagan
// Student Num	: 040100117
// Course		: BLG 312E Computer Operating Systems HW3
// CRN			: 21661
// Lecturer		: Sima Uyar Etaner
// Date			: 02.05.2014
//============================================================================

#include <stdio.h>
#include <stdlib.h> // malloc, free
#include <pthread.h> // thread operations
#include <unistd.h> // fork
#include <sys/wait.h> // wait

#include <sys/sem.h> // semaphore operations
#define THREADSEMKEY 15 // random semaphore key value for thread sync
#define PROCSEMKEY 16 // semaphore key value for thread process sync
#define FILESEMKEY 17 // semaphore key value for file mutex

typedef struct Queue { // queue implementation for orders
	int *content; // integer array for queue content
	int front; // front index number for queue
	int end; // end index number for queue
	int size; // size of queue
} Queue;

int **orders; // global raw order array which is read from input
int *sizes;
int next_order = 0; // next new order element for taking order from orders raw array
int service_number; // number of process (service)
int my_service_index; // index of current process (service)

Queue orders_queue; // global orders queue data structure
char *output_file_name; // global output file pointer

int server_semaphore = 0; // counting semaphore for synchronization two threads
int area_semaphore = 0; // counting semaphore for synchronization processes
int file_mutex = 0; // file mutex

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
	orders_queue.content = (int*) malloc((size + 1) * sizeof(int)); // allocate memory for queue
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

void readFile(const char *filename) { // read input file to the raw orders array
	int index, service_index;
	FILE *input_file = fopen(filename, "r"); // open input file for reading
	if (input_file != NULL) {
		char line[5];
		while (fgets(line, sizeof(line), input_file) != NULL) { // count sizes
			service_index = (line[0] - '0') - 1;
			sizes[service_index] += 1;
		}

		for (index = 0; index < service_number; index++) {
			orders[index] = (int*) malloc((sizes[index] + 1) * sizeof(int)); // allocate array according to size
		}
		int *curent_sizes = (int*) calloc((service_number + 1), sizeof(int)); // allocate array according to size

		rewind(input_file); // bring file cursor to the beginning of the file
		while (fgets(line, sizeof line, input_file) != NULL) { // read file line by line
			service_index = (line[0] - '0') - 1;
			orders[service_index][curent_sizes[service_index]] = (line[2] - '0');
			curent_sizes[service_index]++;
		}
		free(curent_sizes);
		fclose(input_file); // close input file
	} else {
		perror("Error opening input file");
		exit(-1);
	}
}

void* serverFunction(void *arg) { // server thread's function
	int k;
	for (k = 0; k < orders_queue.size; k++) { // take orders in turn
		semWait(server_semaphore, 1); // P(server_semaphore) wait for server thread and decrement counter semaphore s
		semWait(area_semaphore, 1); // P(area_semaphore) decrement area semaphore
		int makeOrder = QueueHead(); // look order from queue
		if (makeOrder == 1) { // sleep according to order type for simulating server operation
			sleep(1);
		} else if (makeOrder == 2) {
			sleep(2);
		} else if (makeOrder == 3) {
			sleep(3);
		}
		QueueDequeue(); // take order from queue
		printf("Server  %d: Type %d is ready to be served\n", my_service_index + 1, makeOrder);

		semWait(file_mutex, 1); // start critical section for writing to file
		FILE *output_file = fopen(output_file_name, "a+"); // open output file for writing
		fprintf(output_file, "Server  %d: Type %d is ready to be served\n",my_service_index + 1, makeOrder); // write result to the output file
		fclose(output_file); // close output file
		semSignal(file_mutex, 1); // stop critical section for writing to file

		semSignal(area_semaphore, 1); // S(area_semaphore) increment area semaphore
	}
	pthread_exit(NULL); // when queue is finished, terminate server thread
}

void* cashierFunction(void *arg) { // cashier thread's function
	int k;
	for (k = 0; k < orders_queue.size; k++) { // make orders in turn
		sleep(1); // sleep for simulating order taking operation
		QueueEnqueue(orders[my_service_index][next_order]); // add next order element to the queue
		printf("Cashier %d: Type %d is ordered\n", my_service_index + 1, orders[my_service_index][next_order]);

		semWait(file_mutex, 1); // start critical section for writing to file
		FILE *output_file = fopen(output_file_name, "a+"); // open output file for writing
		fprintf(output_file, "Cashier %d: Type %d is ordered\n",my_service_index + 1, orders[my_service_index][next_order]); // write result to the output file
		fclose(output_file); // close output file
		semSignal(file_mutex, 1); // stop critical section for writing to file

		next_order++; // prepare raw order array for next order index
		semSignal(server_semaphore, 1); // V(server_semaphore) increment counter semaphore s
	}
	pthread_exit(NULL); // when all orders taken, terminate cashier thread
}

int main(int argc, char *argv[]) { // take command line arguments
	if (argc != 5) { // check command line arguments number
		printf("Error, wrong command line arguments.\n");
		exit(-1);
	}
	output_file_name = argv[2]; // take output file name from command line
	service_number = atoi(argv[3]); // take service number from command line
	int cooking_area = atoi(argv[4]); // take coking area from command line
	orders = (int**) malloc((service_number + 1) * sizeof(int*)); // create orders matrix
	sizes = (int*) calloc((service_number + 1), sizeof(int));

	readFile(argv[1]); // read file and take raw orders

	FILE *output_file = fopen(output_file_name, "w"); // open output file for writing
	if (output_file == NULL) { // check for an error
		printf("Error opening output file!\n");
		exit(1);
	}
	fclose(output_file); // close output file

	area_semaphore = semget(PROCSEMKEY, 1, 0644 | IPC_CREAT); // create semaphore for synchronization processes
	semctl(area_semaphore, 0, SETVAL, cooking_area); // set default semaphore value = 0

	file_mutex = semget(FILESEMKEY, 1, 0644 | IPC_CREAT); // create mutex for file
	semctl(file_mutex, 0, SETVAL, 1); // set default semaphore value = 1

	int *children = (int*) malloc((service_number + 1) * sizeof(int));
	int i = 0, k = 0, f = 1;

	for (k = 0; k < service_number; k++) { // for number of service
		if (f > 0) {
			f = fork();
		}
		if (f == -1) {
			printf("Fork error.\n");
			exit(-1);
		}
		if (f == 0) { // child
			break;
		} else { // parent
			children[k] = f; // take index of child
		}
	}

	if (f == 0) { // child
		my_service_index = k;
		QueueCreate(sizes[k]); // create queue for given size

		server_semaphore = semget(THREADSEMKEY, 1, 0700 | IPC_CREAT); // create semaphore for synchronization two threads
		semctl(server_semaphore, 0, SETVAL, 0); // set default semaphore value = 0

		pthread_t server, cahsier; // define server and cashier thread pointers
		int rc;
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

		QueueDelete(); // deallocate queue
		semctl(server_semaphore, 0, IPC_RMID, 0); // remove server semaphore
		//printf("Child %d: All executions are completed. Exiting.\n", k + 1);
	} else { // parent
		int l;
		for (l = 0; l < service_number; l++) {
			wait(NULL);
		}
		semctl(area_semaphore, 0, IPC_RMID, 0); // remove area semaphore
		semctl(file_mutex, 0, IPC_RMID, 0); // remove file mutex
		printf("\nParent: All executions are completed. Exiting.\n");
		FILE *output_file = fopen(output_file_name, "a+"); // open output file for writing
		fprintf(output_file, "\nParent: All executions are completed. Exiting.\n"); // write exit message to the output file
		fclose(output_file); // close output file
	}
	for (k = 0; k < service_number; k++) { // deallocate memory for all process
		free(orders[k]);
	}
	free(sizes);
	free(children);
	free(orders_queue.content);
	return 0;
}
