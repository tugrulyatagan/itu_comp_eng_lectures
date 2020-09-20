#include <iostream>
#include <fstream>
using namespace std;

struct SEquation {
    unsigned int N;
    double **A;
    double *B; 
    double *x; 
} ;

typedef struct SEquation Equation;

void New(Equation &eqn,unsigned int N){
     eqn.N=N;
     eqn.A= new double*[N];
     eqn.A[0]= new double [N*N];
     for (int i=1;i<N;++i) 
         eqn.A[i]=eqn.A[i-1]+N;
     eqn.B= new double [N];
     eqn.x= new double [N];
}

void Delete(Equation &eqn){
     if (eqn.A==0L) return;
     delete[] eqn.A[0];
     delete[] eqn.A;
     delete[] eqn.B;
     delete[] eqn.x;
}

bool loadEquationFromFile(char *filename,Equation &eqn){
     fstream infile(filename,ios::in);
     if (infile.fail()) return false;
     unsigned int N;
     infile >> N ;
     New(eqn,N);
     double d;       
     for (int i=0;i<N;++i)    
         for (int j=0;j<N;++j){
             infile >> d ;
             eqn.A[i][j]=d;
         } 
     for (int i=0;i<N;++i){
             infile >> d ;
             eqn.B[i]=d;
     }    
     return true;
}

void printEquation(Equation &eqn){
     for (int i=0,j;i<eqn.N;++i){    
         for (j=0;j<i;++j)
             cout << eqn.A[i][j] << "*x(" << (i+1) << "," << (j+1) <<")+\t" ;
         cout << eqn.A[i][j] << "*x(" << (i+1) << "," << (j+1) <<") =\t" << eqn.B[i] << endl ;
     } 
     cout << endl ;
}

void printSolution(Equation &eqn){
     for (int i=0;i<eqn.N;++i)
         cout << "x(" << (i+1) << ")=" << eqn.x[i] << endl ;
}

bool solveEquation(Equation &eqn){
     for (int i=0;i<eqn.N;++i){  
         double sum=0.0;  
         for (int j=0;j<i;++j)
             sum+= eqn.A[i][j]*eqn.x[j];
         if (eqn.A[i][i]==0.0) return false;
         eqn.x[i]=(eqn.B[i]-sum)/eqn.A[i][i];
     }  
     return true;
}

int main(int argc,char *argv[]){
    if (argc<2){
	   cout << "Usage:" << endl;
	   cout << argv[0] << " filename" << endl ;
	   exit(0); 
	}
    Equation eqn;
    loadEquationFromFile(argv[1],eqn);
    printEquation(eqn);   
    solveEquation(eqn);   
    printSolution(eqn);  
    Delete(eqn); 
    return 0;
}