#define PHONENUM_LENGTH 15

struct Phone_number{
	char phonenum[PHONENUM_LENGTH];
	Phone_number *next;
};