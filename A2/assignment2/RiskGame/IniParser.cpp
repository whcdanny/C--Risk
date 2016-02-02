#include "IniParser.h"
#include <fstream>

/** INI-like file parser
  * Algorithm taken from the library
*/
IniParser::IniParser(string fileName)
{
	string line;
	ifstream stream(fileName);

	if (!stream.is_open() || !stream.good())
	{
		throw Exception::FILE_NOT_FOUND;
	}

    //Read all lines
	map<string, string> *currentSection = NULL;
    while (stream.good())
    {
		getline(stream, line);
		if (!stream.good() && !stream.eof())
			throw Exception::FILE_UNREADABLE;
		
		//If line is non-empty and sensitive to space
		if (!line.empty())
		{
			//Check whether start of a section
			if (line[0] == '[')
			{
				//Check for closing bracket
				string::size_type endPos = line.find(']');
				if (endPos == string::npos)
					throw Exception::MALFORMED_SECTION;

				string sectionName = line.substr(1, endPos-1);

				//Check if section is already declared
				if (_sections.find(sectionName) != _sections.end())
					throw Exception::MALFORMED_SECTION;
				
				//Create a new section
				_sections[sectionName];

				//Set a current section
				currentSection = &(_sections)[sectionName];
			}
			else //Content of the section
			{
				//Key-value is not in a section
				if (currentSection == NULL)
					throw Exception::MALFORMED_SECTION;
				
				string::size_type eqPos = line.find('=');

				//Check if "=" sign is found
				string key, data;
				if (eqPos == string::npos || eqPos == 0)
				{
					//Check if key has already declared within section
					if (currentSection->find(line) != currentSection->end())
						throw Exception::MALFORMED_KEY_VALUE;

					key = line;
					data = line;
				} else {

					key = line.substr(0, eqPos);
					data = line.substr(eqPos + 1, string::npos);
				
					//Check if key has already declared within section
					if (currentSection->find(key) != currentSection->end())
						throw Exception::MALFORMED_KEY_VALUE;
				}
				//Add key-value pair to the section
				(*currentSection)[key] = data;
            } //Line type
        } //non-empty line
	} //end Reading stream

	stream.close();
}

set<string> IniParser::getSectionsName()
{
	set<string> sectionsName;
	for (map<string, map<string, string>>::iterator it = _sections.begin(); it != _sections.end(); ++it)
	{
		sectionsName.insert(it->first);
	}
	return sectionsName;
}

map<string, string> IniParser::getSection(string sectionName)
{
	return _sections[sectionName];
}

string IniParser::getValueInSection(string section, string key)
{
	if (_sections.find(section) != _sections.end()
		&& _sections[section].find(key) != _sections[section].end())
	{
		return _sections[section][key];
	}
	return "";
}
