/*
 *  numbers.cpp
 *  
 *  Description:
 *
 *
 *  Created by Peter Eschbacher on 11/8/11.
 *
 */

    // There may be problems for num < 0 with uniform_int_dist...
#include "numbers.h"

int randNum(int lrange, int urange, boost::random::mt19937 &gn)
{
    boost::random::uniform_int_distribution<> dist(lrange, urange);
    return dist(gn);
}

std::string numConstructor(int magnitude)
{
    bool sign = (magnitude >= 0);
    /* insert if statements here */
        
}

unsigned short getPower(const long rawInt)
{
    long temp = rawInt;
    unsigned short mag = 0;
    std::cout << std::setw(9) << "temp" << std::setw(3) << "  mag" << std::endl;
    std::cout << std::setw(9) << temp << "  " << std::setw(3) << mag << std::endl;
    while (temp >= 10)
    {
        mag++;
        temp /= 10;
        std::cout << std::setw(9) << temp << "  " << std::setw(3) << mag << std::endl;
    }
    return mag;
}

bool inputsAreNotOkay(int numOfItems, int xMin, int xMax)
{
    return !((xMax > xMin) && (numOfItems > 0));
}

/* need a 'number constructor' function that takes into account sign and magnitude */

int numbers()
{
    boost::random::mt19937 gen;
    gen.seed(std::time(0));
    int num, tempNum, numOfItems = 0, xmin = 0, xmax = 100;
    bool isCorrect = false;
    std::string wrdStr, response;
    /* Load these from a file eventually */
    std::string numbers[] = {"cero", "uno", "dos", "tres", "cuatro", "cinco",
                             "seis", "siete", "ocho", "nueve", "diez",
                             "once", "doce", "trece", "catorce", "quince",
                             "dieciséis", "diecisiete", "dieciocho",
                             "diecinueve", "veinte", "veintiuno", "veintidós",
                             "veintitrés", "veinticuatro", "veinticinco",
                             "veintiséis", "veintisiete", "veintiocho",
                             "veintinueve"};

    std::string tens[] = {"cero", "diez", "veinte", "treinta", "cuarenta",
                          "cincuenta", "sesenta", "setenta", "ochenta",
                          "noventa"};

    std::string hundreds[] = {"cero", "ciento","doscientos", "trescientos",
                              "cuatrocientos", "quinientos", "seiscientos",
                              "setecientos", "ochocientos", "novecientos"};

    std::string powersOfTen[] = {"uno", "diez", "cien", "mil", "diez mil",
                                 "cien mil", "millón", "mil millones",
                                 "billón"};
    {
        bool changeOptions = true;
        while (inputsAreNotOkay(numOfItems, xmin, xmax) || changeOptions)
        {
            char charOption = 'y';

            std::cout << "How many items do you want to be quizzed over?" << std::endl;
            std::cin >> numOfItems; /* do check to make sure well-formed number */

            std::cout << "Enter a number range: xmin <= x <= xmax " << std::endl;

            std::cout << "xmin = ";
            std::cin >> xmin;

            std::cout << "xmax = ";
            std::cin >> xmax;
            
            std::cout << "You chose " << numOfItems << " numbers between " \
                      << xmin << " and " << xmax << "." << std::endl;
            std::cout << "Keep these options? (y for yes, r for reset) ";
            std::cin >> charOption;
            if (charOption == 'y')
                changeOptions = false;
            else
                changeOptions = true;
        }
    }

    std::cin.clear();
    std::cin.ignore(10,'\n');
    
    for (int ii = 1; ii <= numOfItems && !std::cin.eof(); ii++)
    {
        num = randNum(xmin,xmax,gen);
        tempNum = num;

        /* put all these ifs in a function? */
        // Special cases
        if (num == 100)
        {
            wrdStr = "cien";
            tempNum = 0;
        }
        
        if ( tempNum < 10000 && tempNum >= 1000 )
        {
            wrdStr += (numbers[tempNum / 1000] + " mil");
            tempNum -= (tempNum / 1000) * 1000;
        }

        if ( tempNum < 1000 && tempNum >= 100 )
        {
            if (wrdStr != "")
                wrdStr += " ";
            wrdStr += (hundreds[tempNum / 100]);
            tempNum -= (tempNum / 100) * 100;
        }

        if ( tempNum < 100 && tempNum >= 30 )
        {
            if (wrdStr != "")
                wrdStr += " ";
            wrdStr += tens[tempNum / 10];
            if ((num % 10) != 0)
                wrdStr += (" y " + numbers[num % 10]);
        }
        else if ( tempNum < 30 && !((tempNum == 0) xor (num == 0)) )
        {
            if (wrdStr != "")
                wrdStr += " ";
            wrdStr += numbers[tempNum];
        }

        std::cout << "What is " << num << " in Spanish?" << std::endl;
        getline(std::cin,response);
        isCorrect = (response == wrdStr);

        if ( isCorrect )
        {
            std::cout << "You're right!" << std::endl;
        }
        else
        {
            std::cout << "You're wrong! The correct response is: '" \
                      << wrdStr << "'" << std::endl;
        }
        
        isCorrect = false;
        wrdStr = "";
    }

//    if num < 21, pull raw number
//    if num < 31, construct num[20] - ending (e) + num[x] where 1 <= x <= 9
//    if num > 30, construct num[(x / 10) * 10 /* int math */] - ending + num[x] where 1 <= x <= 9
//    if num > 100, do similar things, possibly embedded from above but including 'cieta y'

    return 0;
}