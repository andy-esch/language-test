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

/* need a 'number constructor' function that takes into account sign and magnitude */

int numbers()
{
    boost::random::mt19937 gen;
    gen.seed(std::time(0));
    int num, tempNum, numOfItems, lower, upper;
    bool isCorrect = false;
    std::string wrdStr, response;
    /* Load these from a file eventually */
    std::string numbers[] = {"cero", "uno", "dos", "tres", "cuatro", "cinco",
                             "seis", "siete", "ocho", "nueve", "diez",
                             "once", "doce", "trece", "catorce", "quince",
                             "dieciséis", "diecisiete", "dieciocho",
                             "diecinueve"};

    std::string tens[] = {"cero", "diez", "veinte", "treinta", "cuarenta",
                          "cincuenta", "sesenta", "setenta", "ochenta",
                          "noventa"};

    std::string hundreds[] = {"cero", "cien","doscientos", "trescientos",
                              "cuatrocientos", "quinientos", "seiscientos",
                              "setecientos", "ochocientos", "novecientos"};

    std::string powersOfTen[] = {"uno", "diez", "cien", "mil", "diez mil",
                                 "cien mil", "millón", "mil millones",
                                 "billón"};
    
    std::cout << "How many items do you want to be quizzed over?" << std::endl;
    std::cin >> numOfItems; /* do check to make sure well-formed number */
    std::cout << "Enter a number range (two integers): ";
    std::cin >> lower >> upper;
    
    for (int ii = 1; ii <= numOfItems; ii++)
    {
        num = randNum(lower,upper,gen);
        tempNum = num;
            //      wrdStr = numConstructor(num);
//        std::cout << "num = " << num << std::endl;
//        std::cout << "tempNum / 1000 = " << num / 1000 << std::endl;
//        tempNum -= (tempNum / 1000) * 1000;
//        std::cout << "tempNum / 100 = " << tempNum / 100 << std::endl;
//        tempNum -=(tempNum / 100) * 100;
//        std::cout << "tempNum / 10 = " << tempNum / 10 << std::endl;
//        tempNum -= (tempNum / 10) * 10;
//        std::cout << "tempNum % 10 = " << tempNum % 10 << std::endl;
//        std::cout << std::endl;
//        tempNum = num;

        if ( tempNum < 10000 && tempNum >= 1000 )
        {
            wrdStr += (numbers[tempNum / 1000] + " mil ");
            tempNum -= (tempNum / 1000) * 1000;
        }

        if ( tempNum < 1000 && tempNum >= 100 )
        {
            wrdStr += (hundreds[tempNum / 100] + " ");
            tempNum -= (tempNum / 100) * 100;
        }

        if ( tempNum < 100 && tempNum >= 20 )
        {
            wrdStr += tens[tempNum / 10];
            if ((num % 10) != 0)
                wrdStr += (" " + numbers[num % 10]);
        }
        else if ( tempNum < 20 )
            wrdStr += numbers[tempNum];

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