/**
 * \file CallLogFile.h
 *
 * \brief reads in n number of lines of the jcblock callerid log into CallEntry objects.
 *
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
 *
 */

#ifndef CALLLOGFILE_H_
#define CALLLOGFILE_H_

#include <string>
#include <vector>

using namespace std;


/**
 * \Class CallEntry holds the information for one callerid.dat line representing one call.
 */
class CallEntry {
public:
    /**
     * Constructor: taking all the values
     * \param code one character string in ('W','B','-') for white listed, black listed, neither
     * \param adate string of the date in MMDDYY format
     * \param time string of the time in HHMM format
     * \param number string of 10 digit phone number
     * \param name the caller id string for the name
     */
    CallEntry(const string& code, const string& adate, const string& time, const string& number, const string& name);

    /**
     * Constructor: for Error conditions
     */
    CallEntry(const string& error) : CallEntry("B", "9999/99/99", "99:99", "ERROR", error) {};

    /** \return bool true iff this call entry was in the blacklist or whitelist */
    const inline bool isInList() const { return (myCode != "-"); };
    /** \return the call entry's code (either 'W', 'B', '-') */
    const string getCode() const { return myCode; }
    /** \return the call entry's date in MMDDYY format */
    const string getDate() const { return myDate; }
    /** \return the call entry's time in HHMM format */
    const string getTime() const { return myTime; }
    /** \return the call entry's phone number */
    const string getNumber() const { return myNumber; }
    /** \return the call entry's callerid name */
    const string getName() const { return myName; }

    static const int MAX_LOG_LINE = 74;
private:
    string myCode;
    string myDate;
    string myTime;
    string myNumber;
    string myName;
};

class FileOpenException : public exception {
    string myWhat;
public:
    FileOpenException(const string what) : myWhat(what) {}
    virtual const char* what() const throw() { return myWhat.c_str(); }
    virtual ~FileOpenException() throw() {
    }
};

/**
 * \Class CallLogFile reads in n number of most recent lines of the jcblock's callerid log into CallEntry objects.
 */
class CallLogFile {
public:
    /**
     * reads in n number of lines of the jcblock callerid log into CallEntry objects.
     * \Param filename the full path and filename of the callerid.dat file
     * \Param numLines the number of lines to read in
     */
    CallLogFile(const string& filename, const int numLines=10) throw(FileOpenException);
    /**
     * Destructor cleans up the CallEntry storage.
     */
    virtual ~CallLogFile();

    /** \Return vector<CallEntry> a vector of the callerid log entries. */
    auto getAll() { return myEntries; }

private:
    /** Holds the CallEntry objects */
    vector<CallEntry> myEntries;
};

#endif /* CALLLOGFILE_H_ */
