/* ********************
*GUESS THE NUMBER     *
*Tugrul YATAGAN       *
*040100117            *
**********************/

#include <iostream> //including standard c++ libraries
#include <cstdlib>
#include <ctime>

#define UPPER_LIMIT 100 //defining global lowest limit
#define LOWER_LIMIT 1 //defining global highest limit

using namespace std;

int main(){
	
	string choice;
	int step; //decleration of step count integer variables, in both situation steps are counted
	int random_number; //decleration of random number integer variables, in both situation random numbers are used
	
	cout << "Please insert \"Q\" for quit." << endl;
	
	while(true) //loop works while loop is not terminated
	{	
		srand(time(NULL)); 
		random_number = LOWER_LIMIT + rand() % UPPER_LIMIT; // generating random variable in range universal limits	
		cout << "Would you like to guess or should computer guess? \"(H)uman\"/\"(C)omputer\": "; //user chooses who will guess
		cin >> choice;//taking the choice from user
		
		step = 1;
	
		if((choice == "H") || (choice == "h")) //user chooses human guess option
		{ 
			int users_guess = 0; //declerating and initailing users guess integer variables
	
			cout << "Please insert \"-1\" for quit." << endl; //stating that "-1" terminates the loop
				
			while(users_guess != random_number) //loop works while user doesn't find the computers random number
			{ 
				cout << "Guess my number: "; //taking the guess from user
				cin >> users_guess; 
								
				if(cin.fail()) //if user inserts non-integer input
				{
					cin.clear(); // clear previous 
					cin.ignore(10000,'\n'); //ignores 10000 character of non-integer input
					
					cout << "Please insert only integer number!" << endl;
				}
				
				else if(users_guess == -1) //if users insert "-1" loop is terminated
				{
					break;
				}
				
				else if(!cin.fail()) //if user inserts integer number
				{	
					if((users_guess < LOWER_LIMIT) || (users_guess > UPPER_LIMIT)) //control the range of users guess
					{
						cout << "Please insert integer number between " << LOWER_LIMIT << " and " << UPPER_LIMIT << endl;
					}
					
					else if(users_guess > random_number) //comparing the users guess and random number
					{
						cout << "Nope, my number is less then " << users_guess << endl; //giving redirection
						step = step +1; // add 1 to step number for 1 guess
					}
					
					else if(users_guess < random_number) //comparing the users guess and random number
					{
						cout << "Nope, my number is greater then " << users_guess << endl; //giving redirection
						step = step +1; // add 1 to step number for 1 guess
					}
				}
			}
			
			if(users_guess == random_number) //if user finds the random number
			{
				if(step == 1) //if user finds the random number in firt try
				{
					cout << "Congrats! You've found it in 1 guess! My number is " << random_number << endl; //output to user for first guess is true
				}
				else if(step > 1) //if user finds the random number after first try
				{
					cout << "Congrats! You've found it in " << step << " guesses! " << "My number is " << random_number << endl; //output to user correct steps number
				}
			}			
		}
		
		
		
		else if((choice == "C") || (choice == "c")) //user chooses computer guess option
		{ 
			int comp_guess, low_limit, up_limit; //decleration of computer guess, low limit and up limit integer variables
			string users_clue; //decleration of users clue variables and key letters
			bool more = true; //decleration of boolean variable "more" for ending loop
			
			low_limit = LOWER_LIMIT; //equalizing low limit to universal lowest limit
			up_limit = UPPER_LIMIT; //equalizing up limit to universal highest limit
	
			comp_guess = random_number; //random variable assign to computer guess for first computer guess
	
			while(more) //loop works while computer guess is not true
			{
				cout << "I guess " << comp_guess << endl; //computers guess
				cout << "Am I right? \"(Y)es\"/\"(L)ower\"/\"(H)igher\": "; //taking clue about guess from user
				cin >> users_clue; //taking clue from user
				
				if((users_clue == "Y") || (users_clue == "y")) //if computer finds the users number
				{
					more = false; //boolen "more" assign false for terminate the loop
				}
				
				else if((users_clue == "L") || (users_clue == "l")) //user tells the computers guess lower than users number
				{
					if(comp_guess == LOWER_LIMIT + 1) //limitation to users lowest input according to global lowest limit
					{
						cout << "Please hold integer number between " << LOWER_LIMIT << " and " << UPPER_LIMIT << endl; 
						break; //loop terminates when user cross the lowest limit 
					}
					else if(comp_guess - low_limit  == 1) //if the difference between low limit and new up limit equals to 1, something went wrong
					{
						cout << "Are you kidding me?" << endl;
						break; //loop terminates when user inserts inconsistent clue
					}
					else
					{
						up_limit = comp_guess; //uptdating up limit
						comp_guess = low_limit + 1 + rand() % (up_limit - low_limit - 1); /* uptdating the computer guess's up limit according to users clue,
						increase 1 lower limit of generating random number and reduce 1 upper limit of generating random number for not to generate same number*/
						step = step + 1; // add 1 to step number for 1 guess
					}
				}
				
				else if((users_clue == "H") || (users_clue == "h")) //users tells the computers guess higher than users number
				{
					if(comp_guess == UPPER_LIMIT - 1) //limitation to users highest input  according to global highest limit
					{
						cout << "Please hold integer number between " << LOWER_LIMIT << " and " << UPPER_LIMIT << endl;
						break; //loop terminates when user cross the highest limit
					}
					else if(up_limit - comp_guess  == 1) //if the difference between up limit and new low limit equals to 1, something went wrong
					{
						cout << "Are you kidding me?" << endl;
						break; //loop terminates when user inserts inconsistent clue
					}
					else
					{
						low_limit = comp_guess; //uptdating low limit 
						comp_guess = comp_guess + 1 + rand() % (up_limit - comp_guess - 1); /* uptdating the computer guess's low limit according to users clue,
						increase 1 lower limit of generating random number and reduce 1 upper limit of generating random number for not to generate same number*/
						step = step + 1; // add 1 to step number for 1 guess
					}
				}
	
				else if((users_clue == "q") || (users_clue == "Q")) //if users insert "Q" or "q" loop is terminated
				{
					break;
				}
				
				else //if user does not insert defined letter
				{
					cout << "Please insert defined letter!" << endl; 
				}
			}
	
			if((users_clue == "Y") || (users_clue == "y")) //if computer finds the users number
			{
				if(step == 1)
				{
					cout << "Haha! I've found it! It took me 1 guess." << endl; //output to user for first guess is true
				}
				else if(step > 1)
				{
					cout << "Haha! I've found it! It took me " << step << " guesses." << endl; //output to user for correct step's number
				}		
			}	
		}
		
		
		else if((choice == "q") || (choice == "Q")) //if users insert "Q" or "q" main loop is terminated
		{
			break;
		}
		
		else //if user does not insert defined letter
		{
			cout << "Please insert defined letter!" << endl;
		}	
	}
	return 0; //program succesfuly ends
}
