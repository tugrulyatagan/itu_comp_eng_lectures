#include "person.h"

bool canNear(string,string);

bool Mother::canGetOnTheRaftWith(const Person &pp,const List &back)const{
	bool valid1=false,valid2=false; 
	if(!strcmp("Son", pp.getCharacter()))   valid1=true;
	if(!strcmp("Thief", pp.getCharacter())) valid2=true;
	if(valid1){
		cout<< "Mother can not get on the raft with son"<<endl;
		return false;
	}
	else if(valid2){
		cout<< "Mother can not get on the raft with Thief without Policeman presence\n";
		return false;
	}
	if(strcmp("Policeman",pp.getCharacter()))		valid1=true;
	if(!valid1){
		cout<<"Thief is left with a family member without policeman's presence.\n";
		return false;
	}

	for(Iter i=back.begin(); i!=back.end(); i++){
		for(Iter j=back.begin(); j!=back.end(); j++){
			if(!canNear(*i,*j)){			
				cout<<*i<<" is left with "<<*j<<" without Mother presence\n";
				return false;
			}
		}
	}
	return true;
}

bool Father::canGetOnTheRaftWith(const Person &pp,const List &back)const{
	bool valid1=false,valid2=false;
	if(!strcmp("Daughter", pp.getCharacter()))	valid1=true;
	if(!strcmp("Thief", pp.getCharacter()))		valid2=true;
	if(valid1){
		cout<< "Father is left with daughter without mother's presence"<<endl;
		return false;
	}
	else if(valid2){
		cout<< "Father can not get on the raft with Thief without Policeman presence"<<endl;
		return false;
	}
	if(!strcmp("Policeman",pp.getCharacter()))		valid1=true;
	if(!valid1){
		cout<<"Thief is left with a family member without policeman's presence.\n";
		return false;
	}

	for(Iter i=back.begin(); i!=back.end(); i++){
		for(Iter j=back.begin(); j!=back.end(); j++){
			if(!canNear(*i,*j)){
				cout<<*i<<" is left with "<<*j<<" without Father presence\n";
				return false;
			}
		}
	}
	return true;
}

bool Son::canGetOnTheRaftWith(const Person &pp,const List &back)const{
	bool valid1=false,valid2=false;
	if(!strcmp("Mother", pp.getCharacter()))	valid1=true;
	if(!strcmp("Thief", pp.getCharacter()))		valid2=true;
	if(!((valid1)&&(valid2))){
		cout<< "Son can not get on the raft with"<<pp.getCharacter()<<endl;
		return false;
	}
	if(strcmp("Policeman",pp.getCharacter()))		valid1=true;
	if(!valid1){
		cout<<"Thief is left with a family member without policeman's presence.\n";
		return false;
	}

	for(Iter i=back.begin(); i!=back.end(); i++){
		for(Iter j=back.begin(); j!=back.end(); j++){
			if(!canNear(*i,*j)) return false;
		}
	}
	return true;
}

bool Daughter::canGetOnTheRaftWith(const Person &pp,const List &back)const{
	bool valid1=false,valid2=false;
	if(!strcmp("Mother", pp.getCharacter()))	valid1=true;
	if(!strcmp("Thief", pp.getCharacter()))		valid2=true;
	if(!((valid1)&&(valid2))){
		cout<< "Daughter can not get on the raft with"<<pp.getCharacter()<<endl;
		return false;
	}
	if(strcmp("Policeman",pp.getCharacter()))		valid1=true;
	if(!valid1){
		cout<<"Thief is left with a family member without policeman's presence.\n";
		return false;
	}

	for(Iter i=back.begin(); i!=back.end(); i++){
		for(Iter j=back.begin(); j!=back.end(); j++){
			if(!canNear(*i,*j)) return false;
		}
	}
	return true;
}

bool Policeman::canGetOnTheRaftWith(const Person &pp,const List &back)const{
	//bool valid1 = strcmp("Son", pp.getCharacter());
	bool valid2 =false;
	if(!strcmp("Thief", pp.getCharacter()))		valid2=true;
	if(!valid2){
		cout<< "Thief is left with a family member without policeman's presence.\n";
		return false;
	}

	for(Iter i=back.begin(); i!=back.end(); i++){
		for(Iter j=back.begin(); j!=back.end(); j++){
			if(!canNear(*i,*j)) return false;
		}
	}
	return true;
}

bool Thief::canGetOnTheRaftWith(const Person &pp,const List &back) const{
	bool valid1 =false;
	if(!strcmp("Policeman", pp.getCharacter()))	valid1=true;
	//bool valid2 = strcmp("Thief", pp.getCharacter());
	if(valid1){
		cout<< "Thief can not get on the raft with"<<pp.getCharacter()<<endl;
		return false;
	}
	//valid1 = strcmp("Policeman",pp.getCharacter());

	for(Iter i=back.begin(); i!=back.end(); i++){
		for(Iter j=back.begin(); j!=back.end(); j++){
			if(!canNear(*i,*j)) return false;
		}
	}
	return true;
}

bool canNear(string s1,string s2){		//This function controls the game rules
	if(s1=="Father"){ 
		if((s2=="Daughter 1")||(s2=="Daughter 2")){	
			//cout<<"\n\n\n\n";
			return false;
		}
	}
	else if(s1=="Mother"){
		if((s2=="Son 1")||(s2=="Son 2")){
			//cout<<"\n\n\n\n";
			return false;
		}
	}
	return true;
}

