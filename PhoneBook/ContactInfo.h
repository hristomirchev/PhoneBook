#pragma once

#include <string>
using namespace std;

class ContactInfo
{
private:
	string GetField(string* contactData);
	string ToLower(string source);

public:
	string Name;
	string Family;
	string PersonalID;
	string Phone;
	string EMail;

	ContactInfo();
	ContactInfo(string name, string family, string id, string phone, string email);
	~ContactInfo();

	bool Contains(string str);
	string ToString();
	void FromString(string contactData);
};