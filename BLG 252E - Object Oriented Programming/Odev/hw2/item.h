#ifndef ITEM_H
#define ITEM_H

enum basketSize {small, medium, large}; 
enum fruitType {standard, citrus, tropical};

class Item{
  protected:
	double price;
  public:
	virtual void calculate_price() = 0; // pure virtual
	virtual void print() const;
};


class Flower: public Item {
  protected:
	bool artificial;
	Flower(bool is_artificial);
	void calculate_price();
	void print() const;
};

class Rose: public Flower {
  protected:
	int ordered_roses;
  public:
	Rose(bool is_artificial,int amount);
	void calculate_price();
	void print() const;
};

class Daisy: public Flower{
  public:
	Daisy(bool is_artificial);
	void calculate_price();
	void print() const;
};


class Gourmet: public Item {
  protected:
	bool promotion;
	basketSize basket_size_values;
	Gourmet(basketSize bs);
	void print() const;
};

class FruitBasket: public Gourmet {
  protected:
	fruitType fruit_type_values;
	bool with_chocolate_sauce;
  public:
	FruitBasket(basketSize bs,fruitType ft,bool with_sauce);
	void calculate_price();
	void print() const;
};

class CookieBasket: public Gourmet{
  public:
	CookieBasket(basketSize bs);
	void calculate_price();
	void print() const;
};

#endif 
