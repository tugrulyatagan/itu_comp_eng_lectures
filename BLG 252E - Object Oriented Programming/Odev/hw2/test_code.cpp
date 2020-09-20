#include <iostream>
#include "item.h"
using namespace std;

// max. 5 orders are allowed per session
#define MAX_ORDER_PER_SESSION 5

int main(){
    // an array of pointers to ordered items
    Item *orders[MAX_ORDER_PER_SESSION];
    int item_count = 0;
    bool continue_shopping = true;
    char category, subcategory;
    // ask for order information in a loop until the user ends shopping or max limit is reached
    while(continue_shopping && item_count < MAX_ORDER_PER_SESSION){
        cout << "-------------------------------------------------------------------------" << endl;
        cout << "Select category ([f] for flower, [g] for gourmet, [e] to end shopping): ";
        cin >> category;
        switch(category){
            case 'f':
                bool is_artificial;
                cout << endl << "Fresh flower[0] or artificial flower[1]?: ";
                cin >> is_artificial;
                cout << endl << "Select subcategory ([r] for rose, [d] for daisy): ";
                cin >> subcategory;
                switch(subcategory){
                    case 'r':
                        int amount;
                        cout << endl << "Amount?: ";
                        cin >> amount;
                        orders[item_count++] = new Rose(is_artificial,amount);
                        break;
                    case 'd':
                        orders[item_count++] = new Daisy(is_artificial);
                        break;
                    default:
                        cout << endl << "Wrong choice!" << endl;
                }
                break;
            case 'g':
                int selected_size;
                cout << endl << "Size? ([0] for small/ [1] for medium / [2] for large): ";
                cin >> selected_size;
                cout << endl << "Select subcategory ([f] for fruitbasket, [c] for cookiebasket): ";
                cin >> subcategory;
                switch(subcategory){
                    case 'f':
                        int selected_type;
                        cout << endl << "Type? ([0] for standard mix/ [1] for citrus mix / [2] for tropical mix): ";
                        cin >> selected_type;
                        bool with_sauce;
                        cout << endl << "Chocolate sauce? ([0] for no/ [1] for yes): ";
                        cin >> with_sauce;
                        orders[item_count++] = new FruitBasket(basketSize(selected_size),fruitType(selected_type),with_sauce);
                        break;
                    case 'c':
                        orders[item_count++] = new CookieBasket(basketSize(selected_size));
                        break;
                    default:
                        cout << endl << "Wrong choice!" << endl;
                }
                break;
            case 'e':
                cout << endl << "Ending the shopping session" << endl;
                continue_shopping = false;
                break;
            default:
                cout << endl << "Wrong choice!" << endl;
        }
        cout << endl;
    }

    // Calculating price and checking promotions for the ordered itens and printing out
    if(item_count > 0){
        cout << endl << "ORDER LIST" << endl;
        cout << "-------------------------------------------------------------------------" << endl;
    }
    for(int i=0; i<item_count; i++){
        orders[i]->calculate_price();
        orders[i]->print();
        cout << endl;
    }

    // giving allocated space back
    for(int i=0; i<item_count; i++)
        delete orders[i];
    return 0;
}
