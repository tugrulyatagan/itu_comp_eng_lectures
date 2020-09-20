#include <stdio.h>	// printf,scanf
#include <stdlib.h>	// malloc,free

void printMatrix(int *matrix, int size);	// matrix print function

void add(int *matrix1, int *matrix2, int *result, int size);
int sum(int *matrix1, int size);
void mult(int *matrix1, int *matrix2, int *result, int size);
void scale(int *matrix1, int number, int *result, int size);
void square(int *matrix1, int *result, int size);
void ITU(int *result, int size);

int main()
{
    int *matrix1, *matrix2, *result, *ITUmatrix = NULL;	// matrix pointers
    int size, index = 0;
    FILE *f;

    if((f=fopen("matrix1.txt","r"))==NULL)			// open first matrix
        printf("File could not be opened\n");
    else {
        fscanf(f,"%d", &size);	// read size
        matrix1 = malloc(sizeof(int)*size*size);	// allocate memory
        while(!feof(f)) {	// read file
            fscanf(f,"%d", &matrix1[index++]);
        }
        fclose(f);
    }

    index = 0;
    if((f=fopen("matrix2.txt","r"))==NULL)			// open second matrix
        printf("File could not be opened\n");
    else {
        fscanf(f,"%d", &size);	// read size
        matrix2 = malloc(sizeof(int)*size*size);	// allocate memory 
        while(!feof(f)) {	// read file
            fscanf(f,"%d", &matrix2[index++]);
        }
        fclose(f);
    }

    result = malloc(sizeof(int)*size*size);		// allocate result matrix
    

    char choice;
    while(1) {	// main user loop
        printf("(a) for add\n");
        printf("(s) for sum\n");
        printf("(m) for mult\n");
        printf("(c) for scale\n");
        printf("(u) for square\n");
        printf("(i) for ITU\n");
        printf("(q) for quit\n");
        printf("Enter your choice: ");

		scanf (" %c", &choice);
		
        if (choice == 'a') {	// add
            add(matrix1, matrix2, result, size);
            printf("Added matrix:\n");
            printMatrix(result,size);
        }
        else if (choice == 's') {	// sum
            int matrixSum;
            matrixSum = sum(matrix1, size);
            printf("Sum: %d\n",matrixSum);
        }
        else if (choice == 'm') {	//mult
            mult(matrix1, matrix2, result, size);
            printf("Multiplied matrix:\n");
            printMatrix(result,size);
        }
        else if (choice == 'c') {	// scale
			int number;
			printf("Enter number: ");
			scanf("%d",&number);
            scale(matrix1, number, result, size);
            printf("Matrix scaled with number %d:\n", number);
            printMatrix(result,size);
        }
        else if (choice == 'u') {	// square
            square(matrix1, result, size);
            printf("Square matrix:\n");
            printMatrix(result,size);
        }
        else if (choice == 'i') {	// ITU
			int ITUsize;
			printf("Enter size: ");
			scanf("%d",&ITUsize);
			if (ITUsize<11 || ITUsize>80){
				printf("Size can be in range 11 to 80.\n");
				continue;
			}
			if (!ITUmatrix){	// check matrix
				ITUmatrix = malloc(ITUsize*ITUsize*sizeof(int));	// allocate memory
			}
            ITU(ITUmatrix, ITUsize);
            printf("ITU matrix:\n");
			int i, j;
			for (i = 0; i < ITUsize; i++ ) {
				for (j = 0; j < ITUsize; j++) {
					printf("%d ",ITUmatrix[i*ITUsize+j]);
				}
				printf("\n");
			}
			printf("\n");
			if (ITUmatrix){
				free(ITUmatrix);	// deallocate ITU matrix
				ITUmatrix = NULL;
			}
        }
        else if (choice == 'q') {
            printf("Quited\n");
            break;
        }
        else {
            printf("Wrong paramater\n");
        }
    }

    free(matrix1);	// deallocate matrices
    free(matrix2);
    free(result);
    return 0;
}

void printMatrix(int *matrix, int size) {	// print function for matrices
    int i, j;
    for (i = 0; i < size; i++ ) {
        for (j = 0; j < size; j++) {
            printf("%d\t",matrix[i*size+j]);
        }
        printf("\n");
    }
    printf("\n");
}
