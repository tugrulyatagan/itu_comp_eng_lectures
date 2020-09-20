#include <iostream>
using namespace std;

typedef struct node
{
    int data;
    struct node *right;
    struct node *down;
}node;



int main (int argc, const char * argv[])
{
    int row, col;
    int i = 0;
    

    cin >> row >> col;
    
    int **arr = new int *[row];
    while(i < row)
    {
        arr[i] = new int[col];
        i++;
    }
    
    int j = 0;
    i = 0;
    
    while(i < row)
    {
        while(j < col)
        {
            cin >> arr[i][j];
            j++;
        }
        j = 0;
        i++;
    }
    


    node *parent = NULL, *child = NULL;
    node *first = NULL;
    for(int i=0;i<row;i++){
        node *head = NULL;
        for(int j=0;j<col;j++){
            node *newnode = new node;
            newnode->data = arr[i][j];
            newnode->right = newnode->down = NULL;
            if(head == NULL){
                head = newnode;
                if(first == NULL)
                    first = head;
            }
            else
                child->right = newnode;
                
            if(parent != NULL){
                parent->down = newnode;
                parent = parent->right;
            }
            child = newnode;
        }
        parent = head;
    }
    




    node *curr_ver_node = first;
    while(curr_ver_node != NULL){
        node *curr_hor_node = curr_ver_node;
        while(curr_hor_node != NULL){
            cout << curr_hor_node->data << " ";
            curr_hor_node = curr_hor_node->right;
        }
        cout << endl;
        curr_ver_node = curr_ver_node->down;
    }
	getchar();
    
    return 0;
}
