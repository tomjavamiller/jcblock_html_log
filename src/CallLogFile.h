/**
 * \file CallLogFile.h
 *
 * \brief reads in n number of lines of the jcblock call log into CallEntry objects.
 */

#ifndef CALLLOGFILE_H_
#define CALLLOGFILE_H_

#include <string>
#include <vector>

using namespace std;

class CallEntry {
public:
	CallEntry(const string& code, const string& adate, const string& time,const string& number,const string& name);
	virtual ~CallEntry();

    const inline bool isInList() const { return (myCode != "-"); };
	const string& getCode() const { return myCode; }
	const string& getDate() const { return myDate; }
	const string& getTime() const { return myTime; }
	const string& getNumber() const { return myNumber; }
	const string& getName() const { return myName; }
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

class CallLogFile {
public:
	// Constructor reads in only numLines
	CallLogFile(const string& filename, const int numLines=10) throw(FileOpenException);
	virtual ~CallLogFile();

	const long size();
	const CallEntry get(const long num) const;
	auto getAll() { return myEntries; }

private:
	vector<CallEntry> myEntries;
};

#endif /* CALLLOGFILE_H_ */
