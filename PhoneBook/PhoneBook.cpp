// PhoneBook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <string>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include "ContactInfo.h"

using namespace std;

int firstFreePosition = 0;
int shortListedContactsCount = 0;
ContactInfo* phoneBook[1000];
ContactInfo* shortListedPhoneBook[1000];
ContactInfo* selectedContact = NULL;

// <summary>
// Provide simple UI to enter contact data
// Input: contactInfo* - pointer to object which contains contact data
// Output: The same object (modified)
//		   flag which marks if entered data are correct	
// </summary>
bool EnterContactData(ContactInfo* contactInfo)
{
	cout << "Name: ";
	cin >> contactInfo->Name;
	cout << "Family: ";
	cin >> contactInfo->Family;
	cout << "Personal ID: ";
	cin >> contactInfo->PersonalID;
	cout << "Phone: ";
	cin >> contactInfo->Phone;
	cout << "e-mail: ";
	cin >> contactInfo->EMail;

	if ((contactInfo->PersonalID.find_first_not_of("0123456789") != string::npos)
		|| (contactInfo->Phone.find_first_not_of("+0123456789") != string::npos)
		|| (contactInfo->EMail.find("@") == -1)) return false;
	return true;
}

// <summary>
// Add contact to phone book
// </summary>
void AddContact()
{
	cout << endl;

	char ch;
	ContactInfo* contactInfo = new ContactInfo();
	if (EnterContactData(contactInfo))
	{
		phoneBook[firstFreePosition] = contactInfo;
		firstFreePosition++;
	}
	else
	{
		cout << "Please enter correct data" << endl << "Press a key then enter to continue ...";
		cin >> ch;
	}
}

// <summary>
// Edt selected contact
// </summary>
void EditContact()
{
	char ch;
	ContactInfo* newContact = new ContactInfo();

	if (selectedContact != NULL)
	{
		if (EnterContactData(newContact))
		{
			*selectedContact = *newContact;
		}
		else
		{
			cout << "Please enter correct data" << endl << "Press a key then enter to continue ...";
			cin >> ch;
		}
	}
	else
	{
		cout << "No selected contact to edit.";
	};
}

// <summary>
// Remove selected contact from phone book
// </summary>
void DeleteContact()
{
	char ch;
	if (selectedContact != NULL)
	{
		for (int i = 0; i < firstFreePosition; i++)
		{
			if (selectedContact == phoneBook[i])
			{
				for (int j = i + 1; j < firstFreePosition; j++)
				{
					phoneBook[i] = phoneBook[j];
				}
				phoneBook[firstFreePosition] = NULL;
				delete selectedContact;
				selectedContact = NULL;
				firstFreePosition--;
				break;
			}
		}
	}
	else
	{
		cout << "No selected contact to delete." << endl;
	};
	cout << "Press a key then enter to continue ...";
	cin >> ch;
}

// <summary>
// View all contacts from given array as table. Method provides simple UI to select one of the listed contacts
// Input: contacts[] - array of contacts to view
//		  contactsCount - contacts count
// Output: Function returns selected contact or NULL if it's leaved with escape key
// </summary>
ContactInfo* ViewAllContacts(ContactInfo* contacts[], int contactsCount)
{
	int keyCode;
	int pointerPosition = 0;
	bool refreshMenu = true;

	while (1)
	{
		if (refreshMenu)
		{
			system("cls");
			cout << setw(2) << " " << left << setw(30) << "Name" << left << setw(30) << "Family" << left << setw(30) << "Personal ID" << left << setw(30) << "Phone" << setw(30) << left << "e-mail" << endl;

			string pointer = " ";
			for (int i = 0; i < contactsCount; i++)
			{
				if (i == pointerPosition) pointer = ">";
				else pointer = " ";

				cout << setw(2) << pointer << left << setw(30)
					<< contacts[i]->Name << left << setw(30)
					<< contacts[i]->Family << left << setw(30)
					<< contacts[i]->PersonalID << left << setw(30)
					<< contacts[i]->Phone << left << setw(30)
					<< contacts[i]->EMail << endl;
			}
			refreshMenu = false;

			cout << "Press arrow keys to navigate, enter to select, esc to leave without selection";
		}

		keyCode = _getch();
		switch (keyCode)
		{
			case 72:
			{
				pointerPosition--;
				refreshMenu = true;
			}; break;
			case 80:
			{
				pointerPosition++;
				refreshMenu = true;
			}; break;
			case 13:
			{
				return contacts[pointerPosition];
			}
			case 27:
			{
				return NULL;
			}
		}
		if (pointerPosition < 0) pointerPosition = contactsCount - 1;
		if (pointerPosition == contactsCount) pointerPosition = 0;
	}
	return NULL;
}

// <summary>
// Searching text in all fields in all records in phone book
// Input: UI to enter searched text
// Output: Short list with contacts which contained searched text (global variable)
// </summary>
void SearchContact()
{
	string searchedText = "";
	cout << "Please enter text we searching for ..." << endl;
	cin >> searchedText;

	for (int i = 0; i < 1000; i++) shortListedPhoneBook[i] = NULL;
	shortListedContactsCount = 0;

	for (int i = 0; i < firstFreePosition; i++)
	{
		if (phoneBook[i]->Contains(searchedText))
		{
			shortListedPhoneBook[shortListedContactsCount] = phoneBook[i];
			shortListedContactsCount++;
		}
	}

	selectedContact = ViewAllContacts(shortListedPhoneBook, shortListedContactsCount);
}

// <summary>
// Save complete phone book in text file
// Output: Updated file
// </summary>
void SaveChanges()
{
	char ch;
	ofstream outfile;

	try
	{
		outfile.open("C:/PhoneBook/PhoneBook.txt", ios::out);
		if (outfile.is_open())
		{
			for (int i = 0; i < firstFreePosition; i++)
			{
				outfile << phoneBook[i]->ToString() << endl;
			}
			outfile.flush();
			outfile.close();

			cout << "Phone book is updated" << endl;
		}
	}
	catch (exception* ex)
	{
		cout << "File write error: " << ex << endl;
	}

	cout << "Press a key then enter to continue ...";
	cin >> ch;
}

// <summary>
// Initialize phone book: 
//		- initialize phone book arrays (phone book and short listed contacts array)
//		- load data from file
//		- create contacts and fill phone book array
// Output: Updated file
// </summary>
void InitPhoneBook()
{
	ifstream infile;
	string currentLine;

	for (int i = 0; i < 1000; i++) phoneBook[i] = NULL;
	for (int i = 0; i < 1000; i++) shortListedPhoneBook[i] = NULL;
	firstFreePosition = 0;

	try
	{
		infile.open("C:/PhoneBook/PhoneBook.txt", ios::out);
		if (infile.is_open())
		{
			do
			{
				getline(infile, currentLine);
				if (currentLine != "")
				{
					ContactInfo* contact = new ContactInfo();
					contact->FromString(currentLine);
					phoneBook[firstFreePosition] = contact;
					firstFreePosition++;
				}
			} while (currentLine != "");
		};
	}
	catch (exception* ex)
	{
		cout << "File read error: " << ex << endl;
	}
}

int main()
{
	InitPhoneBook();

	while (true)
	{
		wprintf(L"Main menu:\r\n\r\n");
		wprintf(L"1. Add contact\r\n");
		wprintf(L"2. Edit selected contact\r\n");
		wprintf(L"3. Delete selected contact\r\n");
		wprintf(L"4. Search contact(s)\r\n");
		wprintf(L"5. View all contacts\r\n");
		wprintf(L"6. Save changes\r\n");
		wprintf(L"0. Close application\r\n\r\n");

		if (selectedContact != NULL)
		{
			cout << "Selected contact:" << endl
				<< "Name		: " << selectedContact->Name << endl
				<< "Family		: " << selectedContact->Family << endl
				<< "Personal ID	: " << selectedContact->PersonalID << endl
				<< "Phone		: " << selectedContact->Phone << endl
				<< "e-mail		: " << selectedContact->EMail << endl << endl;
		}

		wprintf(L"Please select option ");
		char ch;
		cin >> ch;

		switch (ch)
		{
			case '1': AddContact(); break;
			case '2': EditContact(); break;
			case '3': DeleteContact(); break;
			case '4': SearchContact(); break;
			case '5': selectedContact = ViewAllContacts(phoneBook, firstFreePosition); break;
			case '6': SaveChanges(); break;
			case '0': return(0);
		}
		system("cls");
	}
}