#include "../includes_usr/fileIO.h"
#include "../includes_usr/datastructures.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char* filename) {
	books.clear();
	ifstream file;
	file.open(filename);
	if (!file.is_open()){
		return COULD_NOT_OPEN_FILE;
	}

	string line;
	string token;

	stringstream ss;

	while (getline(file, line)){
		book myBooks;
		ss.str(line);

		getline(ss, token, ',');
		myBooks.book_id = stoi(token);

		getline(ss, myBooks.title, ',');

		getline(ss, myBooks.author, ',');

		getline(ss, token, ',');
		myBooks.state = static_cast<book_checkout_state>(std::stoi(token));
		getline(ss, token, ',');
		myBooks.loaned_to_patron_id = stoi(token);

		books.push_back(myBooks);
		ss.clear();






	}
	if(books.size() == 0){
		return NO_BOOKS_IN_LIBRARY;
	}

	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename) {
	fstream file;
	file.open(filename, ios_base::out);
	if (!file.is_open()){
		return COULD_NOT_OPEN_FILE;
	}
	if(books.empty()){
		return NO_BOOKS_IN_LIBRARY;
	}
	string data;
	for (int i = 0; i < books.size(); ++i){
		data = to_string(books[i].book_id) + "," + books[i].title + "," + books[i].author + "," + to_string(books[i].state) + "," + to_string(books[i].loaned_to_patron_id);
		file << data << endl;

	}
	if (file.is_open()){
		file.close();
	}
	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename) {
	patrons.clear();
	ifstream file;
	file.open(filename, ios::in);
	if (!file.is_open()){
		return COULD_NOT_OPEN_FILE;
	}
	string line;
	string token;

	stringstream ss;

	while (getline(file, line)){
		patron myPatrons;
		ss.str(line);

		getline(ss, token, ',');
		myPatrons.patron_id = stoi(token);

		getline(ss, token, ',');
		myPatrons.name = token;

		getline(ss, token, ',');
		myPatrons.number_books_checked_out = stoi(token);

		patrons.push_back(myPatrons);
		ss.clear();

	}
	if(patrons.empty()){
		return NO_PATRONS_IN_LIBRARY;
	}


	return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename) {
	fstream file;
	file.open(filename, ios_base::out);
	if (!file.is_open()){
		return COULD_NOT_OPEN_FILE;
	}
	if(patrons.empty()){
		return NO_PATRONS_IN_LIBRARY;
	}
	string data;
	for (int i = 0; i < patrons.size(); ++i){
		data = to_string(patrons[i].patron_id) + "," + patrons[i].name + "," + to_string(patrons[i].number_books_checked_out);
		file << data << endl;
	}
	if (file.is_open()){
		file.close();
	}
	return SUCCESS;

}
