# jcblock_html_log
<p>C++11 CGI generates HTML list of last part of the jcblock's call log with block button to add numbers to the blacklist. Created to be used with a tablet/smart phone on a home network (web browser pointing to Raspberry Pi's IP something like 192.168.0. ? /cgi-bin/callLogPage.cgi)</p>
<articale><h2>Example table:</h2>
<table style="width:100%">
<tr>
<th>Code</th>
	    <th>Date</th>
	    <th>Time</th>
	    <th>Telephone</th>
	    <th>Name</th>
</tr>
<tr><td>-</td><td>2015/07/20</td><td>12:09</td><td>6692312023&nbsp;&nbsp;&nbsp;&nbsp;(Block) (Add)</td><td>INFO SURVEY &nbsp;&nbsp;&nbsp;&nbsp;(Block) (Add)</td></tr>
<tr><td>W</td><td>2015/07/20</td><td>13:39</td><td>1112223333</td><td>GOOD PERSON</td></tr>
<tr><td>B</td><td>2015/07/20</td><td>14:17</td><td>5156508111</td><td>SENIOR EASE</td></tr>
   </table>
   <articale>
# Technologies Used
c++11 CGI HTML5 CGI linux RASPBIAN apache regex jcblock RaspberryPi

# Required
<ul>
   <li>Raspberry Pi with network connection</li>
   <li>jcblock (with original file format) (a lot of places but here is one <a href="https://github.com/rajraj/jcblock">link</a>)</li>
   <li>gcc 4.9 (or greater) <a href="https://solarianprogrammer.com/2015/01/13/raspberry-pi-raspbian-install-gcc-compile-cpp-14-programs/">link</a></li>
   <li>Apache web server <a href="https://www.raspberrypi.org/documentation/remote-access/web-server/apache.md">link</a></li>
   <li>gnu CGI library cgicc <a href="http://www.tutorialspoint.com/cplusplus/cpp_web_programming.htm">link</a></li>
</ul>

# Reason
JCBlock has a hardware way to press # and the number is added to the blacklist but my modem does not support this and there is a device on Amazon that has a big red "BLOCK NOW" button (only $95) (sits in one spot in the house).  We keep the tablet by the phone and I always have my smart phone around.  So I thought, just have a simple HTML page with a red "block" button on each non- white or black listed call and so when I hear "This is your second and final notice..." or "I'm Microsoft tech support and your computer is sending error messages...", (I hangup on them and) I can add this number to the blacklist by pressing the red button.
