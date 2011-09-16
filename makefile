# *****************************************************
# Parameters to control Makefile operation
# Configured for my computer -- we should learn a more general way to make makefiles
CXX = g++ #-mp-4.4

OBJECTS = functions.o wordData.o listDicts.o
HEADERS = functions.h wordData.h wordSet.h listDicts.h
# ****************************************************

ltest: LanguageTest.o $(OBJECTS)
	$(CXX) $^ -o ltest

LanguageTest.o: LanguageTest.cpp

$(OBJECTS): %.o: %.cpp
	$(CXX) -c $< -o $@

.PHONY: clean
clean:
ifneq ("$(shell ls | grep '.*\.o')","")
	@echo "--->  Cleaning object files \n\t\c"
	rm $(shell ls | grep ".*\.o")
else
	@echo "--->  No object files to remove"
endif