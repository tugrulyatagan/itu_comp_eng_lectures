#include<iostream>
using namespace std;

//------------------------------------------------------------------------------------------
//------------------------ ArrayIndexOutofBounds Class Definition --------------------------
//------------------------------------------------------------------------------------------
class ArrayIndexOutofBounds{
   int index, size, source;
   public:
      ArrayIndexOutofBounds(int ind=-1, int sz=-1, int src=-1){
         index  = ind;
         size   = sz;
		 source = src;
      };
      int getIndex()   const { return index;  };
      int getSize()    const { return size;   };      
      int getSource()  const { return source; };      
};
// Global Variable
static int arrayNum = 0;
//------------------------------------------------------------------------------------------
//------------------------------ TArray Class Declaration --------------------------------
//------------------------------------------------------------------------------------------
template <class T>
class TArray {
      static const int ARRAYSIZE = 10;

      int size;
      T *ia;
      int arrayID;

   public :
      // Constructors
      // Default Constructor
      TArray ( int size = ARRAYSIZE );
      
      // Constructor with Parameters
      TArray ( const T*, int );
      
      // Copy Constructor
      TArray ( const TArray& );

	  // Destructor
      ~TArray();

	  // [] operator is defined to reach array elements
      T& operator[] ( int ) const;

	  // Accessor methods for array elements
      // getSize() and getArrayID() functions defined as inline
      int getSize()    const { return size; };
      int getArrayID() const { return arrayID; };

	  void getArray()  const;
};

//------------------------------------------------------------------------------------------
//----------------------------- Default Constructor Definition -----------------------------
//------------------------------------------------------------------------------------------
template <class T>
TArray<T>::TArray<T> ( int size ){
   arrayID = ++arrayNum;
   this->size = size;

   cout << "Constructor : " << "TArray ( int size ) " << "is called." << endl;  
   cout << "\t" << "Source size = " << getSize() << endl;
   cout << "\t" << "Source array ID = " << getArrayID() << endl;
   
   ia = new T[size];
   for( int i=0; i < size; i++) {
      ia[i] = 0;
   };
};

//------------------------------------------------------------------------------------------
//-------------------------- Parametrized Constructor Definition ---------------------------
//------------------------------------------------------------------------------------------
template <class T>
TArray<T>::TArray<T> ( const T *src, int sz){
   arrayID = ++arrayNum;
   size = sz;

   cout << "Constructor : " << "TArray ( const T *src, int sz) " << "is called." << endl;  
   cout << "\t" << "Source size = " << getSize() << endl;
   cout << "\t" << "Source array ID = " << getArrayID() << endl;


   ia = new T[size];
   for( int i=0; i < size; i++) {
      ia[i] = (src != NULL) ? src[i] : 0;
   };
};

//------------------------------------------------------------------------------------------
//------------------------------ Copy Constructor Definition -------------------------------
//------------------------------------------------------------------------------------------
template <class T>
TArray<T>::TArray<T>( const TArray& src) {
   arrayID = ++arrayNum;
   size = src.getSize();

   cout << "Constructor : " << "TArray ( const TArray& src) " << "is called." << endl; 
   cout << "\t" << "Source size = " << src.getSize() << endl;
   cout << "\t" << "Source array ID = " << src.getArrayID() << endl;
   
   ia = new T [getSize()];
   for( int i=0; i < size; i++) {
      //ia[i] = src.ia[i];
      // or
      ia[i] = src[i];
   };
};

//------------------------------------------------------------------------------------------
//--------------------------------- Destructor Definition ----------------------------------
//------------------------------------------------------------------------------------------
template <class T>
TArray<T>::~TArray<T>() {
         cout << endl;
         cout << "Destructor is called." << endl;
         cout << "\t" << "Source size = " << getSize() << endl;
         cout << "\t" << "Source array ID = " << getArrayID() << endl;

         delete[] ia;
      };
      
//------------------------------------------------------------------------------------------
//--------------------------------- Operator [] Definition----------------------------------
//------------------------------------------------------------------------------------------
template <class T>
T& TArray<T>::operator[] ( int index ) const {
   // if index is out of bounds, then an exception occurs
   if( (index >= size) || (index<0) ) {
      ArrayIndexOutofBounds ex(index, size, arrayID);
      throw ex;
   }
   return ia[index];
};

//------------------------------------------------------------------------------------------
//----------------------------- getArray() Function Definition------------------------------
//------------------------------------------------------------------------------------------
template <class T>
void TArray<T>::getArray() const { 
         cout << endl;
		 cout << "Array Information : " << endl;
         cout << "\t" << "Source size = " << getSize() << endl;
         cout << "\t" << "Source array ID = " << getArrayID() << endl;
		 cout << "\t" << "Array Elements : " ;
		  
		 for( int i=0, arraySize = getSize(); i < arraySize; i++) cout <<  ia[i] << " ";
         cout << endl;
};

//------------------------------------------------------------------------------------------
//------------------------------------ main() Function -------------------------------------
//------------------------------------------------------------------------------------------
int main(){
   cout << endl;
   cout << "------------------------------------------------" << endl;
   cout << endl;   
   // Default constructor is called with default value of parameter size = ARRAYSIZE
   TArray<int> ia1;
   ia1.getArray();
   cout << endl;
   cout << "------------------------------------------------" << endl;
   cout << endl;
      
   cout << endl;   
   cout << "------------------------------------------------" << endl;
   cout << endl;
   // Default constructor is called with value of parameter size = 5
   TArray<float> ia2(5);
   for(int i=0, sz = ia2.getSize(), j=sz; i<sz; ) {
      // ia2 is an TArray instance. [] is used with its re-definition
      ia2[i++] = static_cast<float>(1) / j--; 
   };   
   ia2.getArray();
   cout << endl;   
   cout << "------------------------------------------------" << endl;
   cout << endl;

   cout << endl;   
   cout << "------------------------------------------------" << endl;
   cout << endl;
   // ar is an array of ints
   char ar[] = "AHMET CAGATAY TALAY";
   // ia3 is constructed from array ar
   TArray<char> ia3(ar, static_cast<int>(strlen(ar))+1);
   ia3.getArray();
   cout << endl;   
   cout << "------------------------------------------------" << endl;
   cout << endl;

   cout << endl;   
   cout << "------------------------------------------------" << endl;
   cout << endl;
   
   // copy constructor is called. ia4 has the same values of ia3.
   // Since new memory allocated for ia4.ia[], it contains the same values wtih ia3.ia[]
   // But not at the same memory location
   TArray<char> ia4 = ia3;
   ia4.getArray();
   cout << endl;   
   cout << "------------------------------------------------" << endl;
   cout << endl;

   // ar1 is an array of strings
   char *ar1[] = {"Cagatay", "Talay"};
   // ia5 is constructed from array ar1
   TArray<char *> ia5(ar1, 2);
   ia5.getArray();
   cout << endl;   
   cout << "------------------------------------------------" << endl;
   cout << endl;


   // Try to access an array element out of array bounds
   try{
      ia4[ia4.getSize()];
      //ia4[-1];
	  cout << endl;   
      cout << "------------------------------------------------" << endl;
      cout << endl;
   }
   catch(ArrayIndexOutofBounds ex){
      cout << "ArrayIndexOutofBounds Exception : "   << endl;
      cout << "\t" << "Requested Index : " << ex.getIndex()  << endl;
      cout << "\t" << "Max Array Index : " << ex.getSize()-1 << endl; 
      cout << "\t" << "Source Array ID : " << ex.getSource() << endl; 
      cout << endl;
      cout << "------------------------------------------------" << endl;   
   }
   return 0;
};
//------------------------------------------------------------------------------------------
