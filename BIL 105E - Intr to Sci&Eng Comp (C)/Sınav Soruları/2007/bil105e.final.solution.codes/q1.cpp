#include <iostream>
#include <fstream>
using namespace std;

struct SPolynomial {
    double coefficient;
    unsigned int exponent; 
} ;
typedef struct SPolynomial Polynomial;
struct SNode {
    Polynomial term;
    struct SNode *next;
} ;
typedef struct SNode Node;
typedef struct SNode* PNode;

void insert(PNode &head,double coeff,int exp){
     if (exp<0) return;
     if (!head){
        head= new Node;
        head->term.coefficient= coeff;
        head->term.exponent= exp;
        head->next= 0L;
        return;
     }
     if (head->term.exponent<exp){
        PNode q= head;
        head= new Node;
        head->term.coefficient= coeff;
        head->term.exponent= exp;
        head->next= q;
        return;
     }
     PNode p=head,r=head;
     while (p){
         if (p->term.exponent<exp){
            PNode q= new Node;
            q->term.exponent= exp;
            q->term.coefficient= coeff;
            r->next= q;
            q->next= p;
            return;
         }
         else
         if (p->term.exponent==exp){
            p->term.coefficient+=coeff;
            return;  
         }
         r=p;
         p=p->next;
     }
     if (!p){
            PNode q= new Node;
            q->term.exponent= exp;
            q->term.coefficient= coeff;
            q->next= r->next;
            r->next= q;
     }
}

void DeletePolynomial(PNode &head){
     PNode p=head,q=head;
     while (p){
	      q=p->next;
		  delete p;
          p=q;		  
	 }
}

bool loadPolynomialFromFile(char *filename,PNode &head){
     fstream infile(filename,ios::in);
     if (infile.fail()) return false;
     do{    
       double coeff;
       int exp;
       infile >> coeff ;
       if (infile.eof()) break;
       infile >> exp ;
       insert(head,coeff,exp);
     }while (!infile.eof());   
     return true;
}

void printPolynomial(PNode &head){
     if (!head) return;
     PNode p= head;
     while (p){    
        if (p->term.exponent==1)
        cout << p->term.coefficient << "x+" ;
        else
        if (p->term.exponent==0)
        cout << p->term.coefficient ;
        else
        cout << p->term.coefficient << "x^" << p->term.exponent << "+" ;
        p= p->next;
     }
     cout << endl ;
}

PNode add(PNode p1,PNode p2){
     PNode head=0L;
     while (p1){
           insert(head,p1->term.coefficient,p1->term.exponent);
           p1= p1->next;
     }
     while (p2){
           insert(head,p2->term.coefficient,p2->term.exponent);
           p2= p2->next;
     }
     return head;
}

int main(int argc,char *argv[]){
    if (argc<3){
	   cout << "Usage:" << endl ;	   
	   cout << argv[0] << " filename filename" << endl ;
	   exit(0);
	}
    PNode poly1=0L,poly2=0L;
    loadPolynomialFromFile(argv[1],poly1);
    printPolynomial(poly1);
    loadPolynomialFromFile(argv[2],poly2);
    printPolynomial(poly2);
    PNode poly= add(poly1,poly2);
    printPolynomial(poly);   
	DeletePolynomial(poly1);
	DeletePolynomial(poly2);
	DeletePolynomial(poly);
    return 0;
}