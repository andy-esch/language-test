# *****************************************************
# Parameters to control Makefile operation

vpath %.cpp src
vpath %.h include

CXX = g++ -std=c++0x
CXXFLAGS = -I include -L/opt/local/lib -I/opt/local/include -lboost_system -lboost_chrono -lreadline
DEBUGFLAGS = -Weffc++ -Wall -Wc++0x-compat #-DDEBUG
OPTIM = -O3 -funroll-loops
CMAKE_COMMAND = /opt/local/bin/cmake

OBJECTS = Account.o \
          programPrefs.o \
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

HEADERS = functions.h \
          Flashcard.h \
          listDicts.h \
          testResults.h \
          Hint.h \
          programPrefs.h wordCompare.h SmartPicker.h WordData.h Account.h \
		  flcrd_quiz.h numbers.h

TESTS = SmartPicker_test

# ****************************************************

mkcln: ltest #clean

ltest: LanguageTest.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OPTIM) $^ -o ltest

LanguageTest.o: LanguageTest.cpp

$(OBJECTS): %.o: %.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Building CPP object file" $@
	$(CXX) $(DEBUGFLAGS) $(OPTIM) -I include -c $< -o $@

SmartPicker_test: ./testing/SmartPicker_test.cpp
	$(CXX) $(CXXFLAGS) -I include $< -o $@ -lboost_unit_test_framework

#proto: main_prototype.o $(PROTO_OBJECTS)
#	$(CXX) $(CXXFLAGS) $^ -o proto

#$(PROTO_OBJECTS): %.o: %.cpp
#	$(CXX) -I include -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJECTS) LanguageTest.o
