/****************************************************
* BLG 233E DATA STRUCTURES AND LABORATORY (11146)	*
* CRN: 11146										*
* HOMEWORK #3										*
* FAMILY TREE PROGRAM								*
* TUGRUL YATAGAN									*
* 040100117											*
****************************************************/
#include <iostream>
#include <fstream>
#include <string.h> // gcc
#include <cstdlib> // gcc
using namespace std;

#define NAME_LENGHT 30 // maksimum isim uzunlugu
#define MAX_CHILDREN 5 // maksimum cocuk sayisi
#define INPUT_NAME "family.txt" // girdi dosyasi

struct spouse{
	char *name;
	int birth;
};

struct individual{
	char *name;
	int birth;
	char gender;
	individual **children;
	spouse *wife;
	int ID;
	int PID;
};

struct family{
	individual *root;
	void createFamily(); // agaci dosyadan okuyarak olusturur
	bool printParent(individual *, char *, bool); // aranan kisinin ebeveynlerini rekursif bulur
	bool printChildren(individual *,char *, bool); // aranan kisinin cocuklarini rekursif bulur
	bool printCousins(individual *,char *, bool); // aranan kisinin kuzenlerini rekursif bulur
	bool printGrandchildren(individual *,char *, bool); // aranan kisinin torunlarini rekursif bulur
	bool printGrandparents(individual *,char *, bool); // aranan kisinin buyuk ebeveynlerini rekursif bulur
	bool printSiblings(individual *,char *, bool); // aranan kisinin kardeslerini bulur
	bool isSibling(char *, char *); // aranan kisilerin kardeslik durumunu kontrol eder. Gerekli rekursif fonksiyonlari cagirir
	void printFamily(); // tum agaci ekrana basar. Gerekli rekursif fonksiyonlari cagirir
	bool isPersonExist(individual *, char *, bool); // aranan kisinin agacta olup olmadigini kontrol eder
	void closeFamily(individual *); // agaci siler
};

namespace person{ // agac olusturulurken kullanilan rekursif fonsiyon ve sonuc degerini tutan isim uzayi
	bool findpersonrec(individual *, int, bool, individual **); // eklenecek kisinin yerini rekursif bulur
}

namespace sibling{ // kardes bulma rekursif fonksiyonu ve sonuc degerini tutan isim uzayi
	bool checkParent(individual *,char *, bool,  individual **); // kardes kontrolu yapmak icin aileyi bulur
}

namespace level{ // tum aileyi bastirirken kullanilan rekurisf fonksiyonlar  ve sonuc degerlerini tutan isim uzayi
	int findLayerNum(individual *, int, int *); // tum agaci bastirirken olsuturulacak katman sayisini bulur (en derin katmanin seviyesi)
	int printLayer(individual *, int, int); // tum agaci bastirirken olsuturulacak katmanlari basar
}


void family::createFamily(){
	ifstream input;
	input.open(INPUT_NAME, ios::in); // dosya okumak icin acilir
	if(input.is_open()){
		root = NULL;
		while(input.good()){
			individual *newind;
			spouse *newspouse;
			char *checkname = new char[NAME_LENGHT];
			input >> checkname; // isim bilgisi alinir
			if(strcmp(checkname,"spouse") != 0 && strcmp(checkname,"") != 0){ // dosyadan okunan isimse ve bos satir degilse
				newind = new individual;
				newind->name = checkname; // isim atanir
				input >> newind->birth;
				char g[sizeof("Female")]; // cinsiyet icin en fazla boyut olan "Female" boyutunda karakter dizini
				input >> g;
				if (strcmp(g, "Male") == 0)
					newind->gender = 'M';
				else // famale
					newind->gender = 'F';
				input >> newind->ID;
				input >> newind->PID;
				newind->children = new individual*[MAX_CHILDREN]; // cocuklari gosteren isaretci icin yer alinir
				for(int i = 0; i < MAX_CHILDREN; i++)
					newind->children[i] = NULL; // cocuklar NULL a esitlenir
				newind->wife = new spouse; // esi gosteren pointer icin bellekten yer alinir
				newind->wife->name = ""; // eslerin isim kontorlunde sorun cikmamasi icin bos karakter atanir
				if(root == NULL){
					root = newind; // root eklenir
					continue; // dongu basa gelir
				}

				individual *parent;
				person::findpersonrec(root, newind->PID, false, &parent); // cocugu aileye baglamak icin baglanilacak aile bulunur

				for(int c = 0 ; c < MAX_CHILDREN ; c++){ // baglanilcak cocuk secilir
					if(parent->children[c] == NULL){ // yer bos ise
						parent->children[c] = newind; // cocuk baglanilir
						break;
					}
				}
			}
			else if(strcmp(checkname,"spouse") == 0){ // dosyadan okunan es ise
				newspouse = new spouse; // es icin bellekten yer alinir
				int pairID;
				input >> checkname;
				newspouse->name = checkname;
				input >> pairID;
				input >> newspouse->birth;

				individual *person;
				person::findpersonrec(root, pairID, false, &person); // cocugu aileye baglamak icin baglanilacak aile bulunur 
				person->wife = newspouse; //es baglanir
			}
		}
		input.close();
	}
	else{
		cerr << "Input file can not be opened!" << endl;
		exit (EXIT_FAILURE); // dosya okuma basarisiz. program sonlanir
	}
}

bool person::findpersonrec(individual *traverse, int ID, bool stop, individual **found){ // person isim uzayinda (cagirilacak birey, aranan ID, bitirme durumu)
	if(traverse && !stop){ // traverse NULL olmadigi ve sonuc bulunmadagi surece
		if(traverse->ID == ID){ // aranan ID bulunursa
			stop = true; // bulundu
			*found = traverse; // su anki individual sonuc olarak atanir
			return stop; // kisi bulunduktan sonra bitirme durumu donulur (bulundu)
		}
		for(int i = 0;  traverse->children[i]; i++) // diger cocuklari ara
			stop = findpersonrec(traverse->children[i], ID, stop, found); // su anki bireyin cocuklari icin fonksiyon sirayla cagirilir ve bitirme durumuna atanir
	}
	return stop;  // sonlanma durum bilgisi bir ust fonksiyon cagrisina donulur
}

bool family::printParent(individual *traverse, char *search, bool stop){ // (cagirilacak birey, aranan kisi, bitirme durumu)
	if(traverse && !stop){ // traverse NULL olmadigi ve sonuc bulunmadagi surece
		for(int j = 0; traverse->children[j]; j++){ // cocuk varsa
			if(strcmp(traverse->children[j]->name,search) == 0){ // su anki bireyin cocucugu aranan deger ise
				stop = true; // bulundu
				cout << search << "'s parent are: " << traverse->name << " and " << traverse->wife->name; // bulunan degerin ebeceynleri basilir
				return stop; // aile bulunduktan sonra bitirme durumu donulur (bulundu)
			}
		}
		for(int i = 0;  traverse->children[i]; i++) // diger cocuklari ara
			stop = printParent(traverse->children[i], search, stop); // su anki bireyin cocuklari icin fonksiyon sirayla cagirilir ve bitirme durumuna atanir
	}
	return stop; // sonlanma durum bilgisi bir ust fonksiyon cagrisina donulur
}

bool family::printChildren(individual *traverse, char *search, bool stop){ // (cagirilacak birey, aranan kisi, bitirme durumu)
	if(traverse && !stop){ // traverse NULL olmadigi ve sonuc bulunmadagi surece
		if(strcmp(traverse->name,search) == 0 || strcmp(traverse->wife->name,search) == 0 ){ // su anki birey veya esi aranan kisi ise
			for(int j = 0; traverse->children[j]; j++){ // aranan kisinin cocuklarini sirayla tara
				if(stop == false){ // ilk cocuk bulundugunda
					stop = true; // bulundu
					cout << search << "'s children are: "; // 1 kere ekrana basilir
				}
				cout << traverse->children[j]->name << "  "; // bulunan degerin cocuklari sirayla basilir
			}
			return stop; // tum cocuklar basildiktan sonra bitirme durumu donulur (bulundu)
		}
		for(int i = 0;  traverse->children[i]; i++) // diger cocuklari ara
			stop = printChildren(traverse->children[i], search, stop); // su anki bireyin cocuklari icin fonksiyon sirayla cagirilir ve bitirme durumuna atanir
	}
	return stop; // sonlanma durum bilgisi bir ust fonksiyon cagrisina donulur
}

bool family::printCousins(individual *traverse, char *search, bool stop){ // (cagirilacak birey, aranan kisi, bitirme durumu)
	if(traverse && !stop){ // traverse NULL olmadigi ve sonuc bulunmadagi surece
		for(int j = 0; traverse->children[j]; j++){ // su anki bireyin cocuklarini sirayla tara
			for(int k = 0; traverse->children[j]->children[k]; k++){ // su anki bireyin torunlarini sirayla tara
				if(strcmp(traverse->children[j]->children[k]->name,search) == 0){ // aranan kisi su anki bireyin torunu ise
					for(int m = 0; traverse->children[m]; m++){ // aranan kisinin dedesinin cocuklarini sirayla tara
						for(int n = 0; traverse->children[m]->children[n]; n++){ // aranan kisinin dedesinin torunlarini ekrana bas
							if(j != m ){ // aranan kisi ayni aileden degilse kuzenidir
								if(stop == false){ // ilk kez torun bulundugunda
									stop = true; // bulundu
									cout << search << "'s cousins are: "; // 1 kere ekrana basilir
								}
								cout << traverse->children[m]->children[n]->name << "  "; // bulunan degerin kendi ailesi haric dedesinin torunlari(kuzenleri) sirayla basilir
							}
						}
					}
					return stop; // tum torunlar basildiktan sonra bitirme durumu donulur (bulundu)
				}
			}
		}
		for(int i = 0;  traverse->children[i]; i++) // diger cocuklari ara
			stop = printCousins(traverse->children[i], search, stop); // su anki bireyin cocuklari icin fonksiyon sirayla cagirilir ve bitirme durumuna atanir
	}
	return stop; // sonlanma durum bilgisi bir ust fonksiyon cagrisina donulur
}

bool family::printGrandchildren(individual *traverse, char *search, bool stop){ // (cagirilacak birey, aranan kisi, bitirme durumu)
	if(traverse && !stop){ // traverse NULL olmadigi ve sonuc bulunmadagi surece
		if(strcmp(traverse->name,search) == 0  || strcmp(traverse->wife->name,search) == 0){ // su anki birey veya esi aranan kisi ise
			for(int j = 0; traverse->children[j]; j++){ // su anki bireyin cocuklarini sirayla tara
				for(int k = 0; traverse->children[j]->children[k]; k++){ // su anki bireyin torunlarini sirayla tara
					if(stop == false){ // ilk kez torun bulundugunda
						stop = true; // bulundu
						cout << search << "'s grand children are: "; // 1 kere ekrana basilir
					}
					cout << traverse->children[j]->children[k]->name << "  "; // bulunan degerin torunlari sirayla basilir
				}
			}
			return stop; // bitirme durumu donulur (bulundu)
		}
		for(int i = 0;  traverse->children[i]; i++) // diger cocuklari ara
			stop = printGrandchildren(traverse->children[i], search, stop); // su anki bireyin cocuklari icin fonksiyon sirayla cagirilir ve bitirme durumuna atanir
	}
	return stop; // sonlanma durum bilgisi bir ust fonksiyon cagrisina donulur
}

bool family::printGrandparents(individual *traverse, char *search, bool stop){ // (cagirilacak birey, aranan kisi, bitirme durumu)
	if(traverse && !stop){ // traverse NULL olmadigi ve sonuc bulunmadagi surece
		for(int j = 0; traverse->children[j]; j++){ // su anki bireyin cocuklarini sirayla tara
			for(int k = 0; traverse->children[j]->children[k]; k++){ // su anki bireyin torunlarini sirayla tara
				if(strcmp(traverse->children[j]->children[k]->name,search) == 0){ // aranan kisi su anki bireyin torunu ise
					stop = true; // bulundu
					cout << search << "'s grand parents are: " << traverse->name << " and " << traverse->wife->name; // aranan kisinin buyuk ebeveynleri basilir
					return stop; // bitirme durumu donulur (bulundu)
				}
			}
		}
		for(int i = 0;  traverse->children[i]; i++) // diger cocuklari ara
			stop = printGrandparents(traverse->children[i], search, stop); // su anki bireyin cocuklari icin fonksiyon sirayla cagirilir ve bitirme durumuna atanir
	}
	return stop; // sonlanma durum bilgisi bir ust fonksiyon cagrisina donulur
}

bool family::printSiblings(individual *traverse, char *search, bool stop){ // (cagirilacak birey, aranan kisi, bitirme durumu)
	if(traverse && !stop){ // traverse NULL olmadigi ve sonuc bulunmadagi surece
		for(int j = 0; traverse->children[j]; j++){ // su anki bireyin cocuklarini sirayla tara
			if(strcmp(traverse->children[j]->name,search) == 0){ // su anki bireyin cocugu aranan kisi ise
				for(int k = 0; traverse->children[k]; k++){ // su anki bireyin cocuklarini sirayla tara
					if(j != k){ // aranan kisi kendisi degilse kardesidir
						if(stop == false){ // ilk kez cocuk bulundugunda
							cout << search << "'s siblings are: "; // 1 kez ekrana basar
							stop = true; // bulundu
						}
						cout << traverse->children[k]->name << "  "; // aranan kisinin ailesinin cocuklarini(kardesleri) ekrana basar
					}
				}
				return stop; // bitirme durumu donulur (bulundu)
			}
		}
		for(int i = 0;  traverse->children[i]; i++) // diger cocuklari ara
			stop = printSiblings(traverse->children[i], search, stop); // su anki bireyin cocuklari icin fonksiyon sirayla cagirilir ve bitirme durumuna atanir
	}
	return stop; // sonlanma durum bilgisi bir ust fonksiyon cagrisina donulur
}

bool family::isSibling(char *ptr1, char *ptr2){ // (aranacak 1.kisi, 2.kisi)
	using namespace sibling; // bu fonksiyon kapsamina sibling isim uzayini dahil et 
	individual *family1, *family2; 
	if(!checkParent(root, ptr1, false, &family1)) // 1.kisinin ebeveynini bul
		return 0; // 1.kisi bulunamadiysa
	if(!checkParent(root, ptr2, false, &family2)) // 2.kisinin ebeveynini bul
		return 0; // 2.kisi bulunamadiysa
	return (family1 == family2); // 1.kisinin ve 2.kisinin ebeveynlerini kiysala
}

bool sibling::checkParent(individual *traverse, char *search, bool stop, individual **result){ // sibling isim uzayinda (cagirilacak birey, aranan kisi, bitirme durumu)
	if(traverse && !stop){ // traverse NULL olmadigi ve sonuc bulunmadagi surece
		for(int j = 0; traverse->children[j]; j++){ // su anki bireyin cocuklarini sirayla tara
			if(strcmp(traverse->children[j]->name,search) == 0){ // su anki bireyin cocugu aranan kisi ise
				stop = true; // bulundu
				*result = traverse; // su anki birey sonuc olarak atanir
				return stop; // bitirme durumu donulur (bulundu)
			}
		}
		for(int i = 0;  traverse->children[i]; i++) // diger cocuklari ara
			stop = checkParent(traverse->children[i], search, stop, result); // su anki bireyin cocuklari icin fonksiyon sirayla cagirilir ve bitirme durumuna atanir
	}
	return stop; // sonlanma durum bilgisi bir ust fonksiyon cagrisina donulur
}

void family::printFamily(){
	using namespace level; // bu fonksiyon kapsamina level isim uzayini dahil et 
	int max_layer = 0; // findLayerNum() rekursif fonksiyonunun sonuc ifadesi sifirlanir
	findLayerNum(root, 0, &max_layer); // agactaki katman sayisi bulunur
	for(int layer = 1; layer < max_layer; layer++ ){ // agactaki katman sayisi kadar
		printLayer(root, layer, 0); // katmanlar ekrana bastirilir
		cout << endl;
	}
}

int level::findLayerNum(individual *traverse, int current, int *max_layer){ // level isim uzayinda (cagirilacak birey, su anki kat)
	current++; // yeni fonsiyon cagrildiginda su anki kat 1 artirilir.
	if(current > *max_layer) // su anki kat en buyuk kattan buyuk ise
		*max_layer = current; // en derin kat su anki kat olur
	if(traverse){ // traverse NULL degil ise
		for(int i = 0;  traverse->children[i]; i++) // diger cocuklari ara
			current = findLayerNum(traverse->children[i], current, max_layer); // su anki bireyin cocuklari icin fonksiyon sirayla cagirilir ve kat bilgisi atanir. alt kata(cocuklara) inilir
	}
	current--; // fonsiyon sonlandiginda su anki kat 1 azaltilir. 
	return current; // kat bilgisi bir ust fonksiyon cagrisina donulur. ust kata cikilir
}

int level::printLayer(individual *traverse, int layer, int current){ // level isim uzayinda (cagirilacak birey, bastirilacak kat, su anki kat )
	current++; // yeni fonsiyon cagrildiginda su anki kat 1 artirilir. alt kata inilmistir
	if(traverse){
		if(current == layer){ // su anki kat bastirilacak kat ise
			cout <<  traverse->name; // su anki kisi ekrana bastirilir
			if(traverse->wife->name != "") // esi varsa
				cout << "-" << traverse->wife->name;
			cout << "  ";
		}
		for(int i = 0;  traverse->children[i]; i++) // diger cocuklari ara
			current = printLayer(traverse->children[i], layer, current); // su anki bireyin cocuklari icin fonksiyon sirayla cagirilir ve kat bilgisi atanir. alt kata(cocuklara) inilir
	}
	current--; // fonsiyon sonlandiginda su anki kat 1 azaltilir.
	return current; // kat bilgisi bir ust fonksiyon cagrisina donulur. ust kata(ileye) cikilir
}

bool family::isPersonExist(individual *traverse, char *search, bool stop){
	if(traverse && !stop){ // traverse NULL olmadigi ve sonuc bulunmadagi surece
		if(strcmp(traverse->name,search) == 0 || strcmp(traverse->wife->name,search) == 0){ // su anki birey aranan kisi ise
			stop = true; // bulundu
			return stop; // aranan kisi bulunduktan sonra bitirme durumu donulur (bulundu)
		}
		for(int i = 0;  traverse->children[i]; i++) // diger cocuklari ara
			stop = isPersonExist(traverse->children[i], search, stop); // su anki bireyin cocuklari icin fonksiyon sirayla cagirilir ve bitirme durumuna atanir
	}
	return stop; // sonlanma durum bilgisi bir ust fonksiyon cagrisina donulur
}

void family::closeFamily(individual *traverse){ //(cagirilacak birey) bellekten dinamik alinan degiskenler iade edilir 
	for(int i = 0; traverse->children[i]; i++) // diger cocuklari ara
		closeFamily(traverse->children[i]);  // su anki bireyin cocuklari icin fonksiyon sirayla cagirilir
	delete traverse->wife; // su anki bireyin esi silinir
	delete traverse; // su anki birey silinir
}


int main(){
	cout << "TREE FAMILY PROGRAM" << endl;
	cout << "BLG 233E Data Structures and Laboratory (11146)" << endl;
	cout << "Assignment #3" << endl;
	cout << "TUGRUL YATAGAN" << endl;
	cout << "040100117" << endl;
	family F; // agac tanimlanir
	F.createFamily(); // agac olusturulur
	bool finish = false;
	char choice;
	while(!finish){ // kullanici uygulamayi bitirmemis ise
		cout << endl << "Options:" << endl;
		cout << "	(1) Print Parent" << endl;
		cout << "	(2) Print Children" << endl;
		cout << "	(3) Print Cousins" << endl;
		cout << "	(4) Print Grand Children" << endl;
		cout << "	(5) Print Grand Parents" << endl;
		cout << "	(6) Print Siblings" << endl;
		cout << "	(7) Check Sibling" << endl;
		cout << "	(8) Print Family" << endl;
		cout << "	(0) Exit" << endl;
		cout << "Enter Options: ";
		cin >> choice; // secenek
		cout << endl;
		char parameterName[NAME_LENGHT]; // kullanicidan alinacak parametre
		
		switch(choice){
			case '1':
				cout << "Enter name: ";
				cin.ignore(1000, '\n');
				cin.getline(parameterName,NAME_LENGHT);
				if(!F.isPersonExist(F.root, parameterName, false)){ // eger aranan kisi agacta degil ise
					cout << parameterName << " is not in the tree!" << endl;
					break;
				}
				if(!F.printParent(F.root, parameterName, false)) // eger varsa ebeveynler agacta aranir ve ekrana bastirilir
					cout << parameterName << " has no parent in the tree."; // eger ebeveyn yoksa
				cout << endl;
				break;
			case '2':
				cout << "Enter name: ";
				cin.ignore(1000, '\n');
				cin.getline(parameterName, NAME_LENGHT);
				if(!F.isPersonExist(F.root, parameterName, false)){ // eger aranan kisi agacta degil ise
					cout << parameterName << " is not in the tree!" << endl;
					break;
				}
				if(!F.printChildren(F.root, parameterName, false)) // cocuklar agacta aranir ve eger varsa ekrana bastirilir
					cout << parameterName << " has no child in the tree."; // eger cocuk yoksa
				cout << endl;
				break;
			case '3':
				cout << "Enter name: ";
				cin.ignore(1000, '\n');
				cin.getline(parameterName, NAME_LENGHT);
				if(!F.isPersonExist(F.root, parameterName, false)){ // eger aranan kisi agacta degil ise
					cout << parameterName << " is not in the tree!" << endl;
					break;
				}
				if(!F.printCousins(F.root, parameterName, false)) // kuzenler agacta aranir ve eger varsa ekrana bastirilir
					cout << parameterName << " has no cousin in the tree."; // eger kuzen yoksa
				cout << endl;
				break;
			case '4':
				cout << "Enter name: ";
				cin.ignore(1000, '\n');
				cin.getline(parameterName, NAME_LENGHT);
				if(!F.isPersonExist(F.root, parameterName, false)){ // eger aranan kisi agacta degil ise
					cout << parameterName << " is not in the tree!" << endl;
					break;
				}
				if(!F.printGrandchildren(F.root, parameterName, false)) // torunlar agacta aranir ve eger varsa ekrana bastirilir
					cout << parameterName << " has no grand child in the tree."; // eger torun yoksa
				cout << endl;
				break;
			case '5':
				cout << "Enter name: ";
				cin.ignore(1000, '\n');
				cin.getline(parameterName, NAME_LENGHT);
				if(!F.isPersonExist(F.root, parameterName, false)){ // eger aranan kisi agacta degil ise
					cout << parameterName << " is not in the tree!" << endl;
					break;
				}
				if(!F.printGrandparents(F.root, parameterName, false)) // buyuk ebeveynler agacta aranir ve eger varsa ekrana bastirilir
					cout << parameterName << " has no grand parent in the tree."; // buyuk ebeveynler yoksa
				cout << endl;
				break;
			case '6':
				cout << "Enter name: ";
				cin.ignore(1000, '\n');
				cin.getline(parameterName, NAME_LENGHT);
				if(!F.isPersonExist(F.root, parameterName, false)){ // eger aranan kisi agacta degil ise
					cout << parameterName << " is not in the tree!" << endl;
					break;
				}
				if(!F.printSiblings(F.root, parameterName, false))  // kardesler agacta aranir ve eger varsa ekrana bastirilir
					cout << parameterName << " has no sibling in the tree."; // kardes yoksa
				cout << endl;
				break;
			case '7':
				char parameterName2[NAME_LENGHT];
				cout << "Enter name 1: ";
				cin.ignore(1000, '\n');
				cin.getline(parameterName, NAME_LENGHT);
				if(!F.isPersonExist(F.root, parameterName, false)){ // eger aranan kisi agacta degil ise
					cout << parameterName << " is not in the tree!" << endl;
					break;
				}
				cout << "Enter name 2: ";
				cin.getline(parameterName2, NAME_LENGHT);
				if(!F.isPersonExist(F.root, parameterName2, false)){ // eger aranan kisi agacta degil ise
					cout << parameterName2 << " is not in the tree!" << endl;
					break;
				}
				if(F.isSibling(parameterName, parameterName2)) // iki parametrenin aileleri agacta aranir ve eger aynilarsa
					cout << "They are sibling." << endl; // paratreler kardestir
				else
					cout << "They are not sibling." << endl; // paratreler kardes degildir
				break;
			case '8':
				F.printFamily(); // tum agac ekrana bastirilir
				break;
			case '0':
				finish = true; // kullanici cikmak istiyorsa
				break;
			default:
				cout << "You have made an invalid choice!" << endl << "Try again:" ; // tanimlanmayan secenek girilmisse
				break;
		}
	}
	F.closeFamily(F.root); // agaci siler
	cout << "Tree succesfuly removed." << endl;
	return 0; // program basariyla sonlandi
}
