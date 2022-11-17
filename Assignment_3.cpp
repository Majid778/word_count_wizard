#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <list>
#include <stack>
#include <vector>
#include <iterator>
#include <algorithm>
#include <filesystem>
#include "Hashtable.h"

using namespace std;

void help()
{
	cout << "countCollisons : Return the total number of collisions"<<endl;
	cout << "countWords :    Return the total number of words"<<endl;
	cout << "countUniqueWords :    Return the total number of unique words"<<endl;
	cout << "findFreq <word> :    Finds the frequency of a word"<<endl;
	cout << "exit :    Exits the program"<<endl;
	return;
}

int main()
{
	string path,user_input, Hashselection = "";
	
	cout<<"Welcome to Word Count Wizard"<<endl;
	cout<<"Please enter the path of the file you would like to analyse"<<endl;
	getline(cin, path);//File path input
	ifstream infile;
	infile.open(path);
	while(!infile.is_open()){//Error checking for file
		cout<<"Could not open file! Please try again..."<<endl;
		getline(cin, path);
		infile.open(path);
	}
	
	do{ //Menu for selecting the Hash Function
		cout<<"Please enter the Hash function you would like to use"<<endl;
		cout<<"1. Cyclic"<<endl;
		cout<<"2. Polynomial"<<endl;
		cout<<"3. Summation"<<endl;
		getline(cin, Hashselection);
		if(Hashselection == "1") cout<<"Selected Cyclic Shift Hash Function"<<endl;
		else if(Hashselection == "2") cout<<"Selected Polynomial Hash Function"<<endl;
		else if(Hashselection == "3") cout<<"Selected Summation Hash Function"<<endl;
		else if(Hashselection == ""){cout<<"Default: Cyclic Shift Hash Function"<<endl; Hashselection = "1";}
		else if(Hashselection != "1" && Hashselection != "2" && Hashselection != "3" && Hashselection != "3" && Hashselection != "") cout<<"Invalid input. Please try again."<<endl; //Invalid input message
	}while(Hashselection != "1" && Hashselection != "2" && Hashselection != "3");//loop if there is an invalid input

	HashTable Word_Count_Wizard = HashTable(309621, stoi(Hashselection));//Initalizing the Hashtable
	
	string line, capsword, word = "";
	while(!infile.eof())
	{
		getline(infile,line);
		std::replace_if(line.begin(), line.end(), ::isdigit, ' ');//replacing all digits with a space
		std::replace_if(line.begin(), line.end(), ::ispunct, ' ');//replacing punctuation marks with a space
		stringstream sstr(line);
		while(sstr>>capsword)
		{
			for(char i: capsword)//Loop of lower case each letter of the word
			{
				word += tolower(i);
			}
			Word_Count_Wizard.insert(word);//inserting each word into the hashtable
			word = "";//resetting the word
		}
	}

	cout << "==================================================" << endl;//Menu displaying all the details of the text file
	cout << "===================* ANALYSIS *===================" << endl;
	cout << "File name: " << path << endl;
	cout << "Number of Words = " << Word_Count_Wizard.count_words() << endl;
	cout << "Number of Unique Words = " << Word_Count_Wizard.count_unique_words() << endl;
	cout << "Number of Collisions = " << Word_Count_Wizard.count_collisions() << endl;
	cout << "Avg. Number of Collisions Per Entry = " << double(Word_Count_Wizard.count_collisions()) / Word_Count_Wizard.getSize() << endl;
	cout << "==================================================" << endl;
	cout << "==================================================" << endl;
	
	help();//Display help menu

	do{//Menu of commands
	    string command, argument1;
	    ifstream file_in;
    	cout << ">";
		getline(cin, user_input);
		stringstream sstr(user_input);
		getline(sstr, command, ' ');
		getline(sstr, argument1);
		try {
			if (command == "findFreq") { word = "";for(char i: argument1){word += tolower(i);} cout << "The frequency for " << argument1 << " is: " << Word_Count_Wizard.find_freq(word) << endl;}
			else if (command == "insert") {Word_Count_Wizard.insert(argument1);}
			else if (command == "countCollisions") cout << "The number of collisons are: " << Word_Count_Wizard.count_collisions() << endl;
			else if (command == "countWords") cout << "The number of words are: " << Word_Count_Wizard.count_words() << endl;
			else if (command == "countUniqueWords") cout << "The number of unique words are: " << Word_Count_Wizard.count_unique_words() << endl;
			else if (command == "help")	help();
			else if (command == "exit")	 { cout<< "Exiting..."<<endl ; break;}
			else cout << "Invalid command! Please try again." << endl;
		}
		catch (exception &e)
		{
			cout << "The Exception is: " << e.what() << endl;
		}
	}while(true);
	
	return 0;
}