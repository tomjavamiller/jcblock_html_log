/*
 * CallLogFile.cpp
 *
 *
 */

#include "CallLogFile.h"

#include <string>
#include <fstream>
#include <iostream>
#include <regex>

#define MAX_LOG_LINE 74

using namespace std;
CallEntry::CallEntry(const string& code, const string& adate, const string& time,const string& number,const string& name):
myCode(code),
myDate(adate),
myTime(time),
myNumber(number),
myName(name)
{

}

CallEntry::~CallEntry() {}

CallLogFile::CallLogFile(const string& filename, int numLines)  throw (FileOpenException) {
	ifstream inFile(filename, std::ifstream::ate | std::ifstream::binary );
	if(inFile.fail())
	{
		throw FileOpenException(string("Error opening file: ") + filename);
	}
	else
	{
		smatch aMatch;
		regex theRegex("(.)-DATE = (\\d\\d)(\\d\\d)(\\d\\d)--TIME = (\\d\\d)(\\d\\d)--NMBR = (.*?)--NAME = (.*?)--");
		int fileSize = inFile.tellg();
		if(fileSize > numLines * MAX_LOG_LINE)
		{
			// set cursor to approximately the start of the last numLines lines
			inFile.seekg(-numLines * MAX_LOG_LINE, inFile.end);
			char temp[8]{" "};
			while(temp[0] != '\n') {
				inFile.read(temp, 1);
			}
		}
		else
			inFile.seekg(0, inFile.beg);

		string sLine;
		while(!inFile.eof()) {
			getline(inFile, sLine);
			if(regex_search(sLine,aMatch,theRegex))
			{
                             auto aDate = string("20");
                             aDate.append(aMatch[4]).append("/").append( aMatch[2]).append("/").append(aMatch[3]);
                             auto aTime = string(aMatch[5]);
                             aTime.append(":").append(aMatch[6]);
				CallEntry anEntry(aMatch[1],aDate,aTime,aMatch[7],aMatch[8]);
				myEntries.push_back(anEntry);
			}
		}
	}

}

CallLogFile::~CallLogFile() {
	  myEntries.clear();
}


