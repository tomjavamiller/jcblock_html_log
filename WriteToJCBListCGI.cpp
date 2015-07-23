/**
 * \file WriteToJCBListCGI.cpp
 *
 * \brief Writes a filter line to the JC Block's blacklist.dat or whitelist.dat files
 * using the passed in parameters.
 *
 * Uses the following parameters: 
 *    num  - the 10 digit or less telephone number to filter on
 *    name - a caller id text field to filter on (only used when num is not used)
 *    file - the file to write to.  Either "black" (default) or "white"
 *    desc - the description string.
 *
 *   an example in the browser's address: "?num=1112223333&desc=spam%20call"
 *   Note: the cgicc library will convert the %20 to a space for us.
 *
 * And then writes to the file specified and creates a little HTML page
 * that automatically go to the previous page in a few seconds 
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
 */
#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <time.h>
#include <iomanip>

#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

using namespace std;

/**
 * Returns a string of the CGI element named element_name.  
 * If none found returns def_str as a string.
 * \param element_name the name of the element to get
 * \param def_str the string to return if element is not found
 * \return the CGI element.
 */
auto getElement(const char* element_name, const char* def_str) {
using namespace cgicc;
	   auto formData = Cgicc();
	   auto fi = formData.getElement(element_name);
            if( fi != (*formData).end()  && !fi->isEmpty() ) {
	      return fi->getValue();
	   }
	  return string(def_str);
}

/**
 * Returns a the date string in MMDDYY format. This is the format that JCBlock uses.
 * \return current date as string in MMDDYY format.
 */
auto getDate()
{
//  gcc 5 and greater:
//  auto now = chrono::system_clock::now();
//  auto in_time_t = chrono::system_clock::to_time_t(now);
//  cout << std::put_time(localtime(&in_time_t), "%m%d%y") << endl;

    auto now = time(0);
    auto tstruct = *localtime(&now);
    char buf[8];
    strftime(buf, sizeof(buf), "%m%d%y", &tstruct);
    return std::string(buf);
}

/**
 * Adds a jcblock "filter" line to the end of the filename file. 
 *
 * jcblock has a blacklist.dat and a whitelist.dat and is formated
 * with 19 charaters filter field turminated with question mark.  
 * Followed by a date field MMDDYY 14 charaters
 * Followed by a description fild
 * \param numberOrName the number or name to filter on.
 * \param description the description to write to the file.
 * \param filename this is the file name and full path to one 
 *        of the filter lists ("whitelist.dat" or "blacklist.dat")
 */
void addToFile(const string& numberOrName, const string& description, const string& filename)
{
    stringstream ss;
    ofstream outfile;

    outfile.open(filename, std::ios_base::app);
    ss << setw(19) << left << string(numberOrName).append("?")
       << setw(14) << left << getDate()
       << description << endl;
    cout << "<pre>" << ss.str() << "</pre>";
    outfile << ss.str();
    outfile.close();
}

/** 
 * Prints the top part of the HTML document to standard out.
 */
void printHTML_top() {
	cout << "Content-type: text/html\n\n"
			"<html>\n"
			"<head>\n"
            "<title>Add Number to List</title>\n"
			"</head>\n"
			"<body>\n"
			"<center><h2>Adding To List</h2></center>\n";
}

/**
 * Prints the ending HTML document with script to go back after a set time.
 */
void printHTML_end() {
       // add a automatch back after a little while
	   cout << "<img src=\"/robot.jpg\" />\n"
               "<script>\n"
		    	   "setTimeout(function(){\n"
                       "  window.history.back()\n"
                       "}, 5000);\n"  // go back in 5 seconds.
	          "</script>\n";
       cout << "</body>\n</html>";
}


int main(int argc, char *argv[])
{
      // get the URL paramters example: "?num=1112223333&desc=spam%20call" note: cgi library will unencode the %20
      auto numberOrName = getElement("num", getElement("name","").c_str());  // get name as the default of num
      auto list = getElement("file","black");
      auto desc = getElement("desc","spam");

      printHTML_top();

      printf("<p>Adding %s to %s list with description: %s </p>\n", numberOrName.c_str(), list.c_str(), desc.c_str());

      // add to file either white or black list: 
      addToFile(numberOrName, desc, (list == "white") ? "/usr/local/jcblock/whitelist.dat"s : "/usr/local/jcblock/blacklist.dat"s);

      printHTML_end();
}
