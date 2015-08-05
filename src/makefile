# Make file for the callLogPage.cgi
# stand alone command:
#sudo g++-4.9 -std=c++11 -std=c++1y -lcgicc  -o /usr/lib/cgi-bin/callLogPage.cgi
CC=g++-4.9
CFLAGS=-c -Wall -std=c++11 -std=c++1y
LDFLAGS=-lcgicc
SOURCES=CallLogPageCGI.cpp CallLogFile.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=callLogPage.cgi

all: $(SOURCES) $(EXECUTABLE) deploy

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS)

deploy:
	sudo cp $(EXECUTABLE) /usr/lib/cgi-bin/$(EXECUTABLE)

