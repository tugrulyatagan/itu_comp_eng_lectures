#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <unistd.h>
#include <sys/time.h>
#include <list>

#define CHANNEL_DELAY 2*270
using namespace std;

struct frame {
	int id;
	bool sending_frame;
	bool receiving_frame;
	bool sending_ack;
	bool receiving_ack;
	bool error;
};

frame *data;
int dataSize;
int sending_frame_counter;
int receiving_frame_counter;
struct timeval tvalStart, tvalCurrent;
list<int> errorframe;
int error_counter;
float channel;

bool *data0;
bool *data5;
bool *data10;

void printTimeDiff() {
	gettimeofday(&tvalCurrent, NULL);
	cout << (((tvalCurrent.tv_sec - tvalStart.tv_sec) * 1000000L + tvalCurrent.tv_usec) - tvalStart.tv_usec) / 1000 << " ms" << endl;
}

void *function_A_stopAndWait(void *arg){
	while (sending_frame_counter != dataSize){
		if (data[sending_frame_counter].error != true){
			data[sending_frame_counter].sending_frame = true;
			cout << "Frame " << sending_frame_counter << " is sent to B at ";
			printTimeDiff();
			usleep(CHANNEL_DELAY/2 * 1000);
			data[sending_frame_counter].receiving_frame = true;
			sending_frame_counter++;
			usleep(CHANNEL_DELAY/2 * 1000);
		}
		else{
			data[sending_frame_counter].sending_frame = true;
			cout << "Frame " << sending_frame_counter << " is sent to B at ";
			printTimeDiff();
			usleep(CHANNEL_DELAY/2 * 1000);
			data[sending_frame_counter].receiving_frame = true;
			data[sending_frame_counter].error = false;
			usleep(CHANNEL_DELAY/2 * 1000);
			usleep(10 * 1000);
			cout << "TIMEOUT: " << sending_frame_counter << " at ";
			printTimeDiff();
			cout << "RESEND: ";
		}
	}
}

void *function_B_stopAndWait(void *arg)
{
	usleep(CHANNEL_DELAY * 1000);
	while (receiving_frame_counter != dataSize){
		while (data[receiving_frame_counter].receiving_frame == false);
		data[receiving_frame_counter].sending_ack = true;
		usleep(CHANNEL_DELAY * 1000);
		receiving_frame_counter++;
	}
}

void stopAndWait(bool errorArray[], int size){
	sending_frame_counter = 0;
	receiving_frame_counter = 0;
	error_counter = 0;

	data = new frame[size];
	dataSize = size;

	gettimeofday (&tvalStart, NULL);
	for (int a = 0; a < dataSize; a++){
		data[a].id = a;
		data[a].sending_frame = false;
		data[a].receiving_frame = false;
		data[a].sending_ack = false;
		data[a].receiving_ack = false;
		data[a].error = false;
		data[a].error = errorArray[a];
	}
	void *ret_join;
	pthread_t thread[2];
	int rc = pthread_create(&thread[0], NULL, function_A_stopAndWait, NULL);
	if (rc) {
		cout << "Error:unable to create thread," << rc << endl;
		exit(-1);
	}
	rc = pthread_create(&thread[1], NULL, function_B_stopAndWait, NULL);
	if (rc) {
		cout << "Error:unable to create thread," << rc << endl;
		exit(-1);
	}
	pthread_join(thread[0], (void **)&ret_join);
	pthread_join(thread[1], (void **)&ret_join);
}


void *AtoB_selective(void *arg) {
	long frame_index = (long) arg;
	if (data[frame_index].error == false) {
		usleep(270 * 1000);
		data[frame_index].receiving_frame = true;
	} else {
		cout << "Error occurred!" << endl;
		error_counter++;
		sending_frame_counter--;
	}
}

void *BtoA_selective(void *arg) {
	long ack_index = (long) arg;
	usleep(270 * 1000); /// 300
	if (data[ack_index].error == true) {
		usleep((CHANNEL_DELAY/channel) * 1000);
		errorframe.push_back(data[ack_index].id);
	}
}

void *function_A_selective(void *arg) {
	while (sending_frame_counter != dataSize) {
		if (errorframe.empty()) {
			if (sending_frame_counter + error_counter < dataSize) {
				pthread_t t;
				int rc = pthread_create(&t, NULL, AtoB_selective, (void *) sending_frame_counter + error_counter);
				if (rc) {
					cout << "Error:unable to create thread," << rc << endl;
					exit(-1);
				}
				data[sending_frame_counter + error_counter].sending_frame =true;
				cout << "Frame " << sending_frame_counter + error_counter << " is sent to B at ";
				printTimeDiff();
				sending_frame_counter++;
				usleep((CHANNEL_DELAY/channel) * 1000);
			}
		} else {
			int error = errorframe.front();
			errorframe.pop_front();
			data[error].error = false;
			pthread_t t;
			int rc = pthread_create(&t, NULL, AtoB_selective, (void *) error);
			if (rc) {
				cout << "Error:unable to create thread," << rc << endl;
				exit(-1);
			}
			data[sending_frame_counter].sending_frame = true;
			cout << "FRAME " << error << " is REsent to B at ";
			printTimeDiff();

			sending_frame_counter++;
			error_counter--;
			usleep((CHANNEL_DELAY/channel) * 1000);
		}
	}
}

void *function_B_selective(void *arg) {
	usleep((CHANNEL_DELAY/channel) * 1000);
	while (receiving_frame_counter != dataSize) {
		if (data[receiving_frame_counter].error == false) {
			while (data[receiving_frame_counter].receiving_frame == false);
			pthread_t t;
			int rc = pthread_create(&t, NULL, BtoA_selective, (void *) receiving_frame_counter);
			if (rc) {
				cout << "Error:unable to create thread," << rc << endl;
				exit(-1);
			}
			data[receiving_frame_counter].sending_ack = true;
			receiving_frame_counter++;
		} else {
			pthread_t t;
			int rc = pthread_create(&t, NULL, BtoA_selective, (void *) receiving_frame_counter);
			if (rc) {
				cout << "Error:unable to create thread," << rc << endl;
				exit(-1);
			}
			receiving_frame_counter++;
		}
		usleep((CHANNEL_DELAY/channel) * 1000);
	}
}

void selective(bool errorArray[], int size, int chnl){
	sending_frame_counter = 0;
	receiving_frame_counter = 0;
	error_counter = 0;

	void *ret_join;

	data = new frame[size];
	dataSize = size;
	channel = chnl;
	gettimeofday (&tvalStart, NULL);
	for (int a = 0; a < dataSize; a++) {
		data[a].id = a;
		data[a].sending_frame = false;
		data[a].receiving_frame = false;
		data[a].sending_ack = false;
		data[a].receiving_ack = false;
		data[a].error = false;
		data[a].error = errorArray[a];
	}
	pthread_t thread[2];
	int rc = pthread_create(&thread[0], NULL, function_A_selective, NULL);
	if (rc) {
		cout << "Error:unable to create thread," << rc << endl;
		exit(-1);
	}
	rc = pthread_create(&thread[1], NULL, function_B_selective, NULL);
	if (rc) {
		cout << "Error:unable to create thread," << rc << endl;
		exit(-1);
	}

	pthread_join(thread[0], (void **)&ret_join);
	pthread_join(thread[1], (void **)&ret_join);
}

int main() {
	int option;
	cout << "Enter option 1 or 2: ";
	cin >> option;

	if (option == 1){
		bool errorData[10] = {0,0,1,0,0,0,0,0,0,0};

		cout << "Test 1-Stop and Wait:" << endl << "--------------------" << endl;
		stopAndWait(errorData,10);
		cout << endl;

		cout << "Test 2-Selective Repeat with windows size 4:" << endl << "-----------------------" << endl;
		selective(errorData,10,4);
		cout << endl;

		cout << "Test 3-Selective Repeat with windows size 2:" << endl << "-----------------------" << endl;
		selective(errorData,10,2);
		cout << endl;
	}
	else if (option == 2){
		srand (time(NULL));
		data0 = new bool[1000];
		data5 = new bool[1000];
		data10 = new bool[1000];
		for (int i=0; i < 1000; i++){
			data0[i] = 0;
			data5[i] = (rand() % 100) < 5;
			data10[i] = (rand() % 100) < 10;
		}

		// No error
		cout << "Stop and Wait with no error data:" << endl << "-------------" << endl;
		stopAndWait(data0,1000);
		cout << endl;

		cout << "Selective Repeat with no error data:" << endl << "-------------" << endl;
		selective(data0,1000,4);
		cout << endl;

		// %5 error
		cout << "Stop and Wait with %5 error data:" << endl << "-------------" << endl;
		stopAndWait(data5,1000);
		cout << endl;

		cout << "Selective Repeat with %5 error data:" << endl << "-------------" << endl;
		selective(data5,1000,4);
		cout << endl;

		// %10 error
		cout << "Stop and Wait with %10 error data:" << endl << "-------------" << endl;
		stopAndWait(data10,1000);
		cout << endl;

		cout << "Selective Repeat with %10 error data:" << endl << "-------------" << endl;
		selective(data10,1000,4);
		cout << endl;
	}
	else{
		cout << "Wrong parameter!" << endl;
	}
	cout << "Program terminated successfully" << endl;
	return 0;
}
