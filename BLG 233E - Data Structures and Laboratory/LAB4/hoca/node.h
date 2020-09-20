// node.h
// Phone_node struct definition

#define NAME_LENGTH 30 // replace all subsequent occurrences of the symbolic constant NAME_LENGTH with 30
#define PHONENUM_LENGTH 15 // replace all subsequent occurrences of symbolic constant PHONENUM_LENGTH with 15

// Phone_node struct definition
struct Phone_node
{
	char *name;	// name data stored in this Phone_node
	char *phonenum; // phonenum data stored in this Phone_node
	Phone_node *next; // pointer to another object of the same type
};
