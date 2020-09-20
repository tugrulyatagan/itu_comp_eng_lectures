#include "container.h"
#include "people.h"
#include "game.h"
#include <iostream>

using namespace std;

int main(){
	Container <Operator> operators(3);
	Container <NonOperator> non_operators(5);
	
	Mother m("Mother");
	Father f("Father");
	Daughter d1("Daughter1"), d2("Daughter2");
	Son s1("Son1"), s2("Son2");
	Police p("Police");
	Thief t("Thief");

		operators.addToArray(m);
		operators.addToArray(f);
		operators.addToArray(p);

		non_operators.addToArray(d1);
		non_operators.addToArray(d2);
		non_operators.addToArray(s1);
		non_operators.addToArray(s2);
		non_operators.addToArray(t);

		Game game;
		game.addToLeft(m), game.addToLeft(f), game.addToLeft(p),game.addToLeft(d1);
		 game.addToLeft(d2), game.addToLeft(s1), game.addToLeft(s2),game.addToLeft(t);

	cout << "INITIAL CASE\n";
	cout << "------------------------------------------------------------\n";
	cout << "Operators:\n" ;

	for(int i=0; i<3; i++){	
		  Operator temp = operators.getArray(i);
		  cout << temp.getName() << " is on the " << temp.getPlace() << endl; 
	}

	cout << endl << "Non-operators:\n";

	for(int i=3; i<6; i++){
		  NonOperator temp = non_operators.getArray(i);
		  cout << temp.getName() << " is on the " << temp.getPlace() << endl; 
	}
	cout << endl << "The raft is on the left carrying noone\n";
	cout << "------------------------------------------------------------\n\n";

	game.letsTry(operators, non_operators);
	getchar();

 return 0;

}

