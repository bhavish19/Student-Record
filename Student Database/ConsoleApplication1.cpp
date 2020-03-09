// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
//#include "Studh.h"

namespace MHXBHA001 {
	using namespace std;

	struct StudentRecord
	{
		string Name;
		string Surname;
		string StudentNumber;
		string ClassRecord;
	};


	StudentRecord add(string name, string surname, string studentno, string classrecord) {
		return { name, surname, studentno, classrecord };
	}

	int main()
	{
		vector<StudentRecord> Database;
		for (;;) {
			char c;
			cout << " 0: Add Student \n 1: Read Database \n 2: Save Database \n 3: Display given student data \n 4: Grade student \n Enter a number (or q to quit) and press return...\n";
			cin >> c;
			if (c == '0') {
				string n, s, no, cr, x;
				bool exist = false;
				int index;
				cout << "Enter Name of Student: ";
				cin >> n;
				cout << "Enter Surname of Student: ";
				cin >> s;
				cout << "Enter Student Number: ";
				cin >> no;
				cout << "Enter Class Record Marks each separated by a space: ";
				getline(cin, x);
				getline(cin, cr);

				for (size_t i = 0; i < Database.size(); i++)
				{
					if (no == Database.at(i).StudentNumber) {
						exist = true;
						index = i;
					}
				}

				if (exist)
				{
					Database.erase(Database.begin() + index);
					Database.push_back(add(n, s, no, cr));
				}
				else
				{
					Database.push_back(add(n, s, no, cr));
				}

				cout << "STUDENT ADDED \n\n";
			}
			if (c == '1') {
				string line;
				ifstream in("database.txt");
				while (getline(in, line)) {
					string n, s, no, x, cr;
					istringstream is(line);
					is >> n;
					is >> s;
					is >> no;
					while (!is.eof()) {
						is >> x;
						cr += x + " ";
					}

					Database.push_back(add(n, s, no, cr));

				}
				in.close();
				cout << "DATABASE READ \n\n";
			}
			if (c == '2') {
				remove("database.txt");
				ofstream out("database.txt");
				for (size_t i = 0; i < Database.size(); i++)
				{
					out << Database.at(i).Name << " " << Database.at(i).Surname << " " << Database.at(i).StudentNumber << " " << Database.at(i).ClassRecord << endl;
				}
				out.close();
				cout << "DATABASE SAVED \n\n";
			}
			if (c == '3') {
				string no;
				cout << "Enter Student Number: ";
				cin >> no;
				bool found = false;
				for (size_t i = 0; i < Database.size(); i++)
				{
					if (Database.at(i).StudentNumber == no)
					{
						cout << Database.at(i).Name << " " << Database.at(i).Surname << "\t" << Database.at(i).StudentNumber << "\t" << Database.at(i).ClassRecord << endl << endl;
						found = true;
					}
				}
				if (!found)
				{
					cout << "STUDENT NOT FOUND IN DATABASE \n\n";
				}
			}
			if (c == '4') {
				string no;
				int mark, total = 0, count = 0;
				cout << "Enter Student Number: ";
				cin >> no;
				for (size_t i = 0; i < Database.size(); i++)
				{
					if (Database.at(i).StudentNumber == no) {
						istringstream grade(Database.at(i).ClassRecord);

						do
						{
							grade >> mark;
							total += mark;
							count++;
						} while (!grade.eof());
					}
				}
				double avg = total / count;
				cout << "Grade Student: " << avg << endl << endl;
			}
			if (c == 'q') break;
		}
		return 0;
	}
}
