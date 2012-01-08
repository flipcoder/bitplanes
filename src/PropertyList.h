
#ifndef _PROPERTYLIST_H
#define _PROPERTYLIST_H

#include <map>
#include <string>

class PropertyList
{
	public:

		// A group type, which is a map of string->string associations
		typedef std::map<std::string, std::string> Group;

	private:

		// List of groups associated by name, string->Group association
		std::map<std::string, Group> m_GroupList;

		// Remove unacceptable characters from s as defined by `badchars` in .cpp
		static void cutCmdString(std::string& s);

		// Remove quotes surrounding given string
		static void cutQuotedString(std::string& s);

		// cut all characters contained in `chars` surrounding data in string `s`
		static void cutAdjacentChars(std::string& s, std::string chars);

		// Used for getting parsable string representation of strings with spaces using quotes
		// Otherwise returns the given string unaffected.
		static std::string getStringRep(const std::string& s);

		// The main line parsing method
		// Line is given as `s`, and current group as `group`
		void parseLine(const std::string& s, std::string& group);

		// Returns the integer representation of the string `s`
		// This assumes the string `s` is parsable as an integer
		int stringToInt(const std::string& s) const;
		float stringToFloat(const std::string& s) const;

	public:

		// Accepts a filename as `fn` and reads datafile into memory
		// Returns true on success, otherwise false
		bool open(const char* fn);

		// Saves the file under filename `fn`
		// Returns true on success, otherwise false
		bool save(const char* fn);

		bool getStringValue(const char* _group, const char* _prop, std::string& value);
		bool getIntValue(const char* _group, const char* _prop, int& value);
		bool getFloatValue(const char* _group, const char* _prop, float& value);
	
		void setStringValue(const char* _group, const char* _prop, const std::string& value);
		void setIntValue(const char* _group, const char* _prop, const int value);
		void setFloatValue(const char* _group, const char* _prop, const float value);

		// Removes properties and gruops from the PropertyList
		void removeProperty(const char* _group, const char* _prop);
		void removeGroup(const char* _group);

		// Returns if property list is empty
		bool isEmpty()
		{
			return m_GroupList.empty();
			//return (m_GroupList.size()==0);
		}

		// returns number of groups contained in PropertyList
		unsigned int groupCount()
		{
			return m_GroupList.size();
		}

		// Clears Property List
		void clear()
		{
			m_GroupList.clear();
		}

		// Checks if a group exists with the given name `_group`
		bool isGroup(const char* _group)
		{
			return (m_GroupList.find(_group)!=m_GroupList.end());
		}
};

#endif
