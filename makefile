# *****************************************************
# Parameters to control Makefile operation

vpath %.cpp src
vpath %.h include

CXX = g++ -std=c++0x
CXXFLAGS = -I include -L/opt/local/lib -I/opt/local/include -lboost_system -lboost_chrono
DEBUGFLAGS = -Weffc++ -Wall -DDEBUG
OPTIM = -O3 -funroll-loops

OBJECTS = Account.o \
          cmdLineInput.o \
		  Flashcard.o \
		  flcrd_quiz.o \
		  functions.o \
		  Hint.o \
		  listDicts.o \
		  numbers.o \
		  SmartPicker.o \
		  testResults.o \
		  wordCompare.o \
		  WordData.o

HEADERS = functions.h Flashcard.h listDicts.h testResults.h Hint.h \
		  cmdLineInput.h wordCompare.h SmartPicker.h WordData.h Account.h \
		  flcrd_quiz.h numbers.h

# ****************************************************

mkcln: ltest #clean

ltest: LanguageTest.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o ltest

LanguageTest.o: LanguageTest.cpp

$(OBJECTS): %.o: %.cpp
	$(CXX) $(DEBUGFLAGS) -I include -c $< -o $@

#proto: main_prototype.o $(PROTO_OBJECTS)
#	$(CXX) $(CXXFLAGS) $^ -o proto

#$(PROTO_OBJECTS): %.o: %.cpp
#	$(CXX) -I include -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJECTS) LanguageTest.o
