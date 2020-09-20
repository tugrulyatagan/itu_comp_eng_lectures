/********************************************
* BLG 252E OBJECT ORIENTED PROGRAMMING		*
* CRN: 20919								*
* HOMEWORK 1								*
* mp3 FILE ID TAG APPLICATION				*
* TUGRUL YATAGAN							*
* 040100117									*
********************************************/
#include <iostream>
#include <string.h> // for gcc
#include <fstream>

using namespace std;

class Tag{
	char *tag;
	char *title;
	char *artist;
	char *album;
	char *year;
	char *comment;
 public:
	Tag(); // constructer
	Tag(const Tag &); // copy constructer
	void print() const; // print class to the screen
	void readTag(char*); // read tag from file
	void writeTag(char*); // write tag to the file
	void setTitle(const char*); // allocate title tag
	void setArtist(const char*); // allocate artist tag
	void setAlbum(const char*); // allocate album tag
	void setYear(const char*); // allocate year tag
	void setComment(const char*); // allocate comment tag
	~Tag(); // destructer
};

Tag::Tag(){ // constucter
	tag = new char[3 + 1]; // allocate TAG 
	strcpy(tag,"TAG");
	title = NULL; // initilize class variables
	artist = NULL;
	album = NULL;
	year = NULL;
	comment = NULL;
}

Tag::Tag(const Tag &in){ // copy constructer
	tag = new char[3 + 1]; // +1 for NULL character
	strcpy(tag, in.tag);

	title = new char[strlen(in.title) + 1];
	strcpy(title, in.title);

	artist  = new char[strlen(in.artist) + 1];
	strcpy(artist, in.artist);

	album  = new char[strlen(in.album) + 1];
	strcpy(album, in.album);

	year  = new char[strlen(in.year) + 1];
	strcpy(year, in.year);

	comment  = new char[strlen(in.comment) + 1];
	strcpy(comment, in.comment);
}

Tag::~Tag(){ // deconstructer
 	delete [] tag; // deallocate memory
	delete [] title;
	delete [] artist;
	delete [] album;
	delete [] comment;
	tag = NULL; // reset for deallocated memory
	title = NULL;
	artist = NULL;
	album = NULL;
	comment = NULL;
}

void Tag::setTitle(const char* in_title){
	int i = 0;
	for (; in_title[i] != NULL && i < 30; i++); // find lenght of title and limit to 30
	title = new char[i + 1]; // allocate memory
	strncpy(title, in_title, i); // copy limited size of string
	if(title[i] != NULL) title[i] = NULL; // ensure that the string end with ending character 
}

void Tag::setArtist(const char* in_artist){
	int i = 0;
	for (; in_artist[i] != NULL && i < 30; i++);
	artist = new char[i + 1];
	strncpy(artist, in_artist,i);
	if(artist[i] != NULL) artist[i] = NULL;
}

void Tag::setAlbum(const char* in_album){
	int i = 0;
	for (; in_album[i] != NULL && i < 30; i++);
	album = new char[i + 1];
	strncpy(album, in_album, i);
	if(album[i] != NULL) album[i] = NULL;
}

void Tag::setYear(const char* in_year){
	int i = 0;
	for (; in_year[i] != NULL && i < 4; i++);
	year = new char[i + 1];
	strncpy(year, in_year, i);
	if(year[i] != NULL) year[i] = NULL;
}

void Tag::setComment(const char* in_comment){
	int i = 0;
	for (; in_comment[i] != NULL && i < 30; i++);
	comment = new char[i + 1];
	strncpy(comment, in_comment, i);
	if(comment[i] != NULL) comment[i] = NULL;
}

void Tag::print() const{
	if (title != NULL){ // control for tag
		cout << title;
		cout << endl << '\t' << "artist: ";
		cout << artist;
		cout << endl << '\t' << "album: ";
		cout << album;
		cout << endl << '\t' << "comment: ";
		cout << comment;
		cout << endl;
	}
	else
		cout << "Tag cant print" << endl;
}

void Tag::readTag(char* filename){
	ifstream mp3file(filename, ios::in|ios::binary); // open binary file for reading
	if (mp3file.is_open()){ // check if file open succesfuly
		mp3file.seekg (-128, ios::end); // move cursor to 128 bytes before ending 
		mp3file.read (tag, 3); // read tag
		if (tag != NULL){ // check if tag is correct
			char buffer[30] = ""; // buffer string

			mp3file.read(buffer, 30); // read title
			setTitle(buffer); // set title

			mp3file.read(buffer, 30); // read artist
			setArtist(buffer); // set artist

			mp3file.read(buffer, 30); // read album
			setAlbum(buffer); // set album

			mp3file.read(buffer, 4); // read year
			setYear(buffer); // set year

			mp3file.read(buffer, 30); // read comment
			setComment(buffer); // set comment
		}
		else
			cout << "mp3 tag couldnt read. tag is broken" << endl;
	}
	else 
		cout << "Unable to open mp3 file" << endl;
	mp3file.close(); // close file
}

void Tag::writeTag(char* filename){
	ofstream mp3file (filename, ios::app | ios::out | ios::binary); // open binary file for writing write information to end of file
	if (mp3file.is_open()){ // check if file open succesfuly
		mp3file.write(tag, 3); // write tag
		mp3file.write(title, 30); // write title
		mp3file.write(artist, 30); // write artist
		mp3file.write(album, 30); // write album
		mp3file.write(year, 4); // write year
		mp3file.write(comment, 30); // write comment
		mp3file.write("0", 1); // write genre default is 0
	}
	else 
		cout << "Unable to write mp3 file";
	mp3file.close(); // close file
}


int main()
{
	Tag tag1;
	tag1.setTitle("staring at the sun");
	tag1.setArtist("offspring");
	tag1.setAlbum("americana");
	tag1.setYear("1998");
	tag1.setComment("no comment");
	Tag *tag2 = new Tag(tag1);
	Tag tag3(*tag2);
	delete tag2;
	tag3.writeTag("2.mp3");
	Tag tag4;
	tag4.readTag("1.mp3");
	Tag tag5;
	tag5.readTag("3.mp3");
	Tag tag6;
	tag6.readTag("2.mp3");
	Tag *tag7 = &tag5;
	tag4.print();
	tag6.print();
	tag7->print();
	return 0;
}

