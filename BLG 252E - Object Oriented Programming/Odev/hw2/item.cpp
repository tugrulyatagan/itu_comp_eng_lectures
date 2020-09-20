#include <iostream>
#include "item.h" 
using namespace std;

void Item::print() const{
	cout << endl;
}

Flower::Flower(bool is_artificial){
	artificial = is_artificial; 
}
void Flower::calculate_price(){
	if (artificial)
		price *= 1.5;
}
void Flower::print() const{
	Item::print();
}

Rose::Rose(bool is_artificial,int amount): Flower(is_artificial){ // invokes flower's constructer
	if (amount < 0)
		amount = 0;
	ordered_roses = amount;
}
void Rose::calculate_price(){
	if (ordered_roses >= 10)
		price = ordered_roses * 8;
	else
		price = ordered_roses * 10;
	Flower::calculate_price();
}
void Rose::print() const{
	cout << ordered_roses << " roses ";
	if (artificial)
		cout << "<artificial> - ";
	else
		cout << "<fresh> - ";
	cout << price << " TL";
	Flower::print();
}

Daisy::Daisy(bool is_artificial): Flower(is_artificial){
	; // Daisy's constructer only invokes flower's constructer
}
void Daisy::calculate_price(){
	price = 20;
	Flower::calculate_price();
}
void Daisy::print() const{
	cout << "A bunch of daisies - " << price << " TL";
	Flower::print();
}
Gourmet::Gourmet(basketSize bs){
	promotion = false;
	basket_size_values = bs; 
}
void Gourmet::print() const{
	if (promotion)
		cout << endl << "Promotion: a bunch of daisies for free";
	Item::print();
}

FruitBasket::FruitBasket(basketSize bs,fruitType ft,bool with_sauce): Gourmet(bs){ // invokes gourmet's constructer
	fruit_type_values = ft;
	with_chocolate_sauce = with_sauce;
}
void FruitBasket::calculate_price(){ 
	if (fruit_type_values == standard)
		price = 25;
	else if (fruit_type_values == citrus)
		price = 40;
	else if (fruit_type_values == tropical)
		price = 50;
	if (basket_size_values == medium)
		price *= 2;
	else if (basket_size_values == large)
		price *= 3;
	if (with_chocolate_sauce)
		price += 20;

	if (price >= 80)
		promotion = 1;
}
void FruitBasket::print() const{
	if (fruit_type_values == standard)
		cout << "Satandart ";
	else if (fruit_type_values == citrus)
		cout << "Citrus ";
	else if (fruit_type_values == tropical)
		cout << "Tropical ";
	cout << "fruit basket ";
	if (with_chocolate_sauce)
		cout << "with chocalate sauce ";
	if (basket_size_values == small)
		cout << "<small>  ";
	else if (basket_size_values == medium)
		cout << "<medium> ";
	else if (basket_size_values == large)
		cout << "<large> ";

	cout << "- " << price << " TL";
	Gourmet::print();
}

CookieBasket::CookieBasket(basketSize bs): Gourmet(bs) { // invokes gourmet's constructer
	; // CookieBasket's constructer only invokes gourmet's constructer
}
void CookieBasket::calculate_price(){
	if (basket_size_values == small)
		price = 30;
	else if (basket_size_values == medium)
		price = 50;
	else if (basket_size_values == large){
		price = 70;
		promotion = 1;
	}
}
void CookieBasket::print() const{
	cout << "A basket of cookies ";
	if (basket_size_values == small)
		cout << "<small> - " << price << " TL" ;
	else if (basket_size_values == medium)
		cout << "<medium> - " << price << " TL" ;
	else if (basket_size_values == large)
		cout << "<large> - " << price << " TL" ;
	Gourmet::print();
}
