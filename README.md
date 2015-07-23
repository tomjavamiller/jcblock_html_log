# jcblock_html_log
<p>C++11 CGI generates HTML list of last part of the jcblock's call log with block button to add numbers to the blacklist. Created to be used with a tablet/smart phone on a home network (web browser pointing to Raspberry Pi's IP something like <code>192.168.0.xx/cgi-bin/callLogPage.cgi</code>)</p>
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
c++11 CGI HTML5 CGI Linux RASPBIAN apache regex jcblock RaspberryPi

# Reason
JCBlock has a hardware way to press # and the number is added to the blacklist but my modem does not support this and there is a device on Amazon that has a big red "BLOCK NOW" button (only $95) (sits in one spot in the house).  We keep the tablet by the phone and I always have my smart phone around.  So I thought, just have a simple HTML page with a red "block" button on each non- white or black listed call and so when I hear "This is your second and final notice..." or "I'm Microsoft tech support and your computer is sending error messages...", (I hang-up on them and) I can add this number to the blacklist by pressing the red button.

# Required
<ul>
   <li>Raspberry Pi with network connection</li>
   <li>jcblock (with original file format) (a lot of places but here is one <a href="https://github.com/rajraj/jcblock">link</a>)</li>
   <li>gcc 4.9 (or greater) <a href="https://solarianprogrammer.com/2015/01/13/raspberry-pi-raspbian-install-gcc-compile-cpp-14-programs/">link</a></li>
   <li>Apache web server <a href="https://www.raspberrypi.org/documentation/remote-access/web-server/apache.md">link</a></li>
   <li>gnu CGI library cgicc <a href="http://www.tutorialspoint.com/cplusplus/cpp_web_programming.htm">link</a></li>
</ul>

# Building/Running
<ol>
   <li>Good idea to run <code>sudo update</code></li>
   <li>Get JCBLock running on your pi (because this is a helper program for JCBlock)</li>
   <li>Install and have running the Apache web server as a daemon on startup</li>
   <li>Install the CGI library cgicc (to have a library available for the compilation)</li>
   <li>Download this project and put on your pi</li>
   <li>Copy the images to the apache www/images directory (This would be /var/www/images default apache installation)</li>
   <li>Compile the project (on your pi)</li>
      <ol>
        <li>On your pi go into the jcblock_html_log/src directory in the command line</li>
        <li>type <code>make</code> and return</li>
        <li>If you get any errors, I would suggest: read the errors and search the web for the errors and fix</li>
        <li>Test it.  After it compiles, run the executable by running: <code>/usr/lib/cgi-bin/callLogPage.cgi</code><br>
        You should see a bunch of HTML. Make sure it ends with &lt;/html&gt;</li>
        <li>Repeat for <code> make -f write_makefile</code>
      </ol>
   <li>Find your pi's IP address, so we can use it on your tablet/phone/computer.</li>
     <p>IP addresses on your LAN are most likely look like 192.168.0.xx (because of something called class C licensing) (get your "there's no place like 192.168.0.1" t-shirt now).  So to find it from the pi's command line try: <code>ifconfig wlan0 | grep "inet addr"</code> or <code>ifconfig | grep "192.168."</code> or do a web search on Linux current ip address. Then type this in a browser's address bar on a different device and apache will display something like: "This is the default web page for this server."</p>
     <p>Next, try: 192.168.0.xx/cgi-bin/callLogPage.cgi</p>
     <p>What about the <em>Dynamic</em> in DHCP?  Although the IP address are given dynamically, this hardly changes and my pi has had the same ip address on my LAN ever since I got it.  I would not worry about it so much.</p>
     <p>Optionally: add <code>&lt;a href="192.168.0.xx/cgi-bin/callLogPage.cgi?numLines=30"&gt;</code> to the /var/www/index.html document in case you forget the cgi-bin/callLogPage.cgi part. Change this web page all you want it is your own personal web server!
</ol>
   
