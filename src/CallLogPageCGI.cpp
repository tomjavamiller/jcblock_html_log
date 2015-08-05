/******************************************************************************
 * \file CallLogPageCGI.cpp
 *
 * \brief Reads in the last numLines of /usr/local/jcblock/callerID.dat file
 *        and displays in a HTML table with (block) and (add) buttons
 *        to add number to the blacklist or whitelist.
 *
 *   Copyright (C) 2015  Thomas Miller
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
 ******************************************************************************/
#include <string>
#include <fstream>
#include <iostream>
#include <regex>

#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h> 

#include "CallLogPageCGI.h"
#include "CallLogFile.h"

using namespace std;

const string CallLogPageCGI::JCBLOCK_INSTALLED_DIR = "/usr/local/jcblock/"s;

string CallLogPageCGI::getElement(const char* element) {
    using namespace cgicc;
    auto formData = Cgicc();
    auto fi = formData.getElement(element);
    if( fi != (*formData).end()  && !fi->isEmpty() ) {
        return fi->getValue();
    }
    return string();
}

CallLogPageCGI::CallLogPageCGI() {
    string strNumLines = getElement("numLines");
    if( strNumLines.size() > 0 ) {
        numLines = stoi(strNumLines);
        if(numLines < 5)
            numLines = 5;
    }
}

/**
 * Prints the top part of the HTML document to standard out.
 * Including style formatting for buttons and layout.
 */
void CallLogPageCGI::printHTML_top() const {
    cout << "Content-type: text/html\n\n"
            "<html>\n"
            "<head>\n"
            "<meta charset=\"utf-8\">\n"
            "<title>Call Log</title>\n"
            "<style>"
            "table, th, td {\n"
            "   border: 1px solid black;\n"
            "   border-collapse: collapse;\n"
            "}\n"
            "th, td {"
            "padding: 5px;"
            "}\n"
            ".lHalf {"
            "   float:left;"
            "   width:50%;"
            "}\n"
            ".rHalf {"
            "   float:right;"
            "   text-align:right;"
            "   width:50%;"
            "}\n"
            ".redbtn {"
            "  background-color:red;"
            "  color:white;"
            "  border-radius:28px;"
            "}\n"
            ".grnbtn {"
            "  background-color:green;"
            "  color:white;"
            "  border-radius:28px;"
            "}\n"
            "</style>\n"
            "</head>\n"
            "<body>\n"
            "<center><h2><img src='/robot_banner.jpg' /></h2></center>\n";

    cout << "<table style=\"width:100%\">\n"
            "<tr>\n"
            "       <th>Code</th>\n"
            "            <th>Date</th>\n"
            "            <th>Time</th>\n"
            "            <th>Telephone</th>\n"
            "            <th>Name</th>\n"
            "</tr>\n";
}

void CallLogPageCGI::printHTML_table() {
    const string filename(JCBLOCK_INSTALLED_DIR + "callerID.dat");

    try {
        auto theCallLogFile = CallLogFile(filename,numLines);

        for( auto aCallEntry : theCallLogFile.getAll()) {
            cout << "<tr>";
            cout << "<td>" << aCallEntry.getCode() << "</td>";
            cout << "<td>" << aCallEntry.getDate() << "</td>";
            cout << "<td>" << aCallEntry.getTime() << "</td>";
            cout << "<td>";
            if(!aCallEntry.isInList()) {
                cout << "<div class='lHalf'>" << aCallEntry.getNumber() << "</div>";
                cout << "<div class='rHalf'>"
                        "<button class='redbtn' onclick=\"blockNum('"<< aCallEntry.getNumber() << "')\" title='Add number to black list.'>Block</button>"
                        "<button class='grnbtn' onclick=\"addNum('"<< aCallEntry.getNumber() << "', '" << aCallEntry.getName() << "')\" title='Add number to white list.'>Add</button>"
                        "</div>";
            } else
                cout << aCallEntry.getNumber();
            cout << "</td>";
            cout << "<td>";
            if(!aCallEntry.isInList()) {
                cout << "<div class='lHalf'>" << aCallEntry.getName() << "</div>";
                cout << "<div class='rHalf'>"
                        "<button class='redbtn' onclick=\"blockName('"<< aCallEntry.getName() << "')\" title='Add name to black list.'>Block</button>"
                        "<button class='grnbtn' onclick=\"addName('"<< aCallEntry.getName() << "')\" title='Add name to white list.'>Add</button>"
                        "</div>";
            } else
                cout << aCallEntry.getName();
            cout << "</td>"
                    "</tr>\n";
        }

    }
    catch(FileOpenException& e)
    {
        cout << "caught exception: " << e.what() << endl;
    }
}

void CallLogPageCGI::printHTML_end() const {
    cout << "</table>\n"
            "<script>\n"
            "function blockNum(num) {\n"
            "   var desc = (prompt('Blocking number: '+num+'\\nPlease enter a description', 'spam call'));\n"
            "   if(desc != null) {\n"
            "      window.location = '/cgi-bin/WriteToJCBList.cgi?num=' + num + '&desc=' + encodeURIComponent(desc);\n"
            "   }"
            "}\n"
            "function blockName(name) {\n"
            "   var desc = (prompt('Blocking name: '+name+'\\nPlease enter a description', 'spam call'));\n"
            "   if(desc != null) {\n"
            "      window.location = '/cgi-bin/WriteToJCBList.cgi?name=' + name + '&desc=' + encodeURIComponent(desc);\n"
            "   }"
            "}\n"
            "function addNum(num,desc) {\n"
            "   desc = (prompt('White listing number: '+num+'\\nPlease enter a description', desc));\n"
            "   if(desc != null) {\n"
            "      window.location = '/cgi-bin/WriteToJCBList.cgi?num=' + num + '&file=white&desc=' + encodeURIComponent(desc);\n"
            "   }"
            "}\n"
            "function addName(name) {\n"
            "   desc = (prompt('White listing name: '+name+'\\nPlease enter a description', name));\n"
            "   if(desc != null) {\n"
            "      window.location = '/cgi-bin/WriteToJCBList.cgi?name=' + name + '&file=white&desc=' + encodeURIComponent(desc);\n"
            "   }"
            "}\n"
            "</script>\n"
            "</body>\n</html>";
}

void CallLogPageCGI::printHTML() {
    printHTML_top();
    printHTML_table();
    printHTML_end();
}

/**
 * The entry point for this CGI page.
 */
int main(int argc, char *argv[])
{
    // create a CallLogPageCGI and call printHTML.
    CallLogPageCGI().printHTML();
}
