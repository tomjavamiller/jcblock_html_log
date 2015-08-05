/*
 *  \File CallLogFile.cpp
 *
 *  Copyright (C) 2015  Thomas Miller
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "CallLogFile.h"

#include <string>
#include <fstream>
#include <iostream>
#include <regex>

using namespace std;

CallEntry::CallEntry(const string& code, const string& adate, const string& time,const string& number,const string& name):
        myCode(code),
        myDate(adate),
        myTime(time),
        myNumber(number),
        myName(name)
{
}


CallLogFile::CallLogFile(const string& filename, int numLines)  throw (FileOpenException) {
    ifstream inFile(filename, std::ifstream::ate | std::ifstream::binary );
    if(inFile.fail())
    {
        throw FileOpenException(string("Error opening file: ") + filename);
    }
    else
    {
        smatch aMatch;
        //               1             2       3       4                5       6              7             8
        regex theRegex("(.)-DATE = (\\d\\d)(\\d\\d)(\\d\\d)--TIME = (\\d\\d)(\\d\\d)--NMBR = (.*?)--NAME = (.*?)--");
        int fileSize = inFile.tellg();
        if(fileSize > numLines * CallEntry::MAX_LOG_LINE)
        {
            // set cursor to approximately the start of the last numLines lines
            inFile.seekg(-numLines * CallEntry::MAX_LOG_LINE, inFile.end);
            // now move forward in the file until a return character is found (positioning to the start of the next entry).
            char temp[8]{" "};
            int num_read = 0;
            while(temp[0] != '\n' && ++num_read < CallEntry::MAX_LOG_LINE + 2) {
                inFile.read(temp, 1);
            }
        }
        else
            inFile.seekg(0, inFile.beg);

        string sLine;
        while(!inFile.eof()) {
            getline(inFile, sLine);
            if(sLine.length() < 1)
               continue;
            if(sLine.length() < (CallEntry::MAX_LOG_LINE + 2) && regex_search(sLine,aMatch,theRegex))
            {
                // first lets reconstruct the date and time strings

                // Start the date off with first 2 digits of the year: "20"
                auto aDate = string("20");
                // next append 2 digit year / 2 digit month / 2 digit day
                aDate.append(aMatch[4]).append("/").append( aMatch[2]).append("/").append(aMatch[3]);
                // create time
                auto aTime = string(aMatch[5]);
                aTime.append(":").append(aMatch[6]);

                // now create one entry and add to the storage:
                myEntries.push_back(CallEntry(aMatch[1],aDate,aTime,aMatch[7],aMatch[8]));
            }
            else
            {
                myEntries.push_back(CallEntry("Line too long/doesn't match format "s + sLine));
            }
        }
        // because all lines are not the max (MAX_LOG_LINE) in length, myEntries may have a few more entries.
        // therefore delete the extras from the beginning
        while(myEntries.size()>(unsigned)numLines)
        {
            myEntries.erase(myEntries.begin());
        }
        if(myEntries.size() < 1)
        {
            myEntries.push_back(CallEntry("No lines in file."));
        }
    }
}

CallLogFile::~CallLogFile() {
    myEntries.clear();
}
