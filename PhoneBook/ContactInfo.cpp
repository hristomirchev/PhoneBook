#include "stdafx.h"
#include "ContactInfo.h"
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

// <summary>
// Default constructor
// </summary>
ContactInfo::ContactInfo()
{
}

// <summary>
// Initializing constructor
// </summary>
ContactInfo::ContactInfo(string name, string family, string id, string phone, string email)
{
	Name = name;
	Family = family;
	PersonalID = id;
	Phone = phone;
	EMail = email;
}

// <summary>
// Destructor
// </summary>
ContactInfo::~ContactInfo()
{
}

// <summary>
// Check if any of the object's fields contains specific string
// Input: searched string
// Output: true if any the object's fields contains searched string; otherwise - false
// </summary>
bool ContactInfo::Contains(string str)
{
	int pos = ToLower(Name).find(ToLower(str));
	if (pos > -1) return true;
	pos = ToLower(Family).find(ToLower(str));
	if (pos > -1) return true;
	pos = ToLower(PersonalID).find(ToLower(str));
	if (pos > -1) return true;
	pos = ToLower(Phone).find(ToLower(str));
	if (pos > -1) return true;
	pos = ToLower(EMail).find(ToLower(str));
	if (pos > -1) return true;

	return false;
}

// <summary>
// Store all object's fields in single string
// Output: String which contains object's properties
// </summary>
string ContactInfo::ToString()
{
	return "Name: " + Name + ";Family: " + Family + ";ID: " + PersonalID + ";Phone: " + Phone + ";e-mail: " + EMail;
}

// <summary>
// Initialize all object's fields from string
// Input: String which contains object's properties
// </summary>
void ContactInfo::FromString(string contactData)
{
	Name = GetField(&contactData);
	Family = GetField(&contactData);
	PersonalID = GetField(&contactData);
	Phone = GetField(&contactData);
	EMail = GetField(&contactData);
}

// <summary>
// Extracts field value from string. 
// Note: If the string contains more then one property, the method extracts first value.
// Input: String which contains object's properties
// Output: - Object's field property
//		   - Modified input string where the first property and its value are removed
// </summary>
string ContactInfo::GetField(string* contactData)
{
	int pos = contactData->find(";");
	string field = *contactData;
	if (pos == -1) return field.substr(field.find(":") + 1);

	field = field.substr(field.erase(pos).find(":") + 1);
	*contactData = contactData->substr(pos + 1);
	return field;
}

// <summary>
// Convert string to lowercase
// Input: String which will be lowercased
// Output: Lowercased input string
// </summary>
string ContactInfo::ToLower(string source)
{
	int i = 0;
	while (source[i])
	{
		source[i] = tolower(source[i]);
		i++;
	}
	return source;
}