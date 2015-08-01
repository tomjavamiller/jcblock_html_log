/*
 * \file CallLogPageCGI.h
 *
 * \brief Reads in the last numLines of callerID.dat file
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
 */

#ifndef JCBLOCK_HTML_LOG_SRC_CALLLOGPAGECGI_H_
#define JCBLOCK_HTML_LOG_SRC_CALLLOGPAGECGI_H_

#include <string>

/**
 * \Class CallLogPageCGI
 * Reads in the last numLines of /usr/local/jcblock/callerID.dat file
 *        and displays in a HTML table with (block) and (add) buttons
 *        to add number to the blacklist or whitelist.
 */
class CallLogPageCGI {
    /** The number of lines to display */
    int numLines = 10;
    /** Prints the top part of the HTML document to standard out. */
    void printHTML_top() const;
    /** Prints the end part of the HTML document to standard out. */
    void printHTML_end() const;
    /** Prints the call log data in HTML table format. */
    void printHTML_table();

public:
    /**
     * The installed path of jcblock
     * If jcblock was installed different from /usr/local/jcblock/ ,
     * change the setting in CallLogPageCGI.cpp.
     */
    static const std::string JCBLOCK_INSTALLED_DIR;

    /**
     * \Return string of the CGI parameter given in the URL example:
     */
    std::string getElement(const char* element);
    /** Constructor Set the numLines setting from the URL parameter */
    CallLogPageCGI();
    /** The main method to print the page. */
    void printHTML();
};

#endif /* JCBLOCK_HTML_LOG_SRC_CALLLOGPAGECGI_H_ */
