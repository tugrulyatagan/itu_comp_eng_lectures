#define NAME_LENGTH 30
#include "number.h"

struct Phone_node {
	char name[NAME_LENGTH];
	Phone_number *number_head, *number_tail;
	Phone_node *left;
	Phone_node *right;
};