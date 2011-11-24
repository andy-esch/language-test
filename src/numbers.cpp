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

/* Load these from a file eventually */
string zeroTo29[] = {"cero", "uno", "dos", "tres", "cuatro", "cinco",
    "seis", "siete", "ocho", "nueve", "diez",
    "once", "doce", "trece", "catorce", "quince",
    "dieciséis", "diecisiete", "dieciocho",
    "diecinueve", "veinte", "veintiuno", "veintidós",
    "veintitrés", "veinticuatro", "veinticinco",
    "veintiséis", "veintisiete", "veintiocho",
    "veintinueve"};

string tens[] = {"cero", "diez", "veinte", "treinta", "cuarenta",
    "cincuenta", "sesenta", "setenta", "ochenta",
    "noventa"};

string hundreds[] = {"cero", "ciento","doscientos", "trescientos",
    "cuatrocientos", "quinientos", "seiscientos",
    "setecientos", "ochocientos", "novecientos"};

string powersOfTen[] = {"uno", "diez", "ciento", "mil", "diez mil",
    "cien mil", "millón", "mil millones",
    "billón"};

int randNum(int lowLim, int upLim, boost::random::mt19937 &gn)
{
    boost::random::uniform_int_distribution<> dist(lowLim, upLim);
    return dist(gn);
}

unsigned short getPower(const long rawInt)
{
    long temp = rawInt;
    unsigned short mag = 0;
    cout << setw(9) << "temp" << setw(3) << "  mag" << endl;
    cout << setw(9) << temp << "  " << setw(3) << mag << endl;
    while (temp >= 10)
    {
        mag++;
        temp /= 10;
        cout << setw(9) << temp << "  " << setw(3) << mag << endl;
    }
    return mag;
}

bool inputsAreNotOkay(int numOfItems, int xMin, int xMax)
{
    return !((xMax > xMin) && (numOfItems > 0));
}

int findFirstError(string ans, string cmp)
{
    int errorPos = 0;
    for (int ii = 0; ii < ans.size(); ii++)
    {
        if (ans[ii] == cmp[ii])
            errorPos++;
        else
            break;
    }

    return errorPos;
}

/* need a 'number constructor' function that takes into account sign and magnitude */
string numConstructor(int num)
{
    string wrdStr;

    if (num < 0)
    {
        num = -1.0 * num;
        if (num != 1)
            wrdStr += "negativos";
        else if (num == 1)
            wrdStr += "negativo";
    }

    int tempNum = num;

    // Special cases
    if (num == 100)
    {
        wrdStr = "cien";
        tempNum = 0;
    }

    if ( tempNum < 10000 && tempNum >= 1000 )
    {
        wrdStr += (zeroTo29[tempNum / 1000] + " mil");
        tempNum -= (tempNum / 1000) * 1000;
    }

    if ( tempNum < 1000 && tempNum >= 100 )
    {
        if (!wrdStr.empty())
            wrdStr += " ";
        wrdStr += (hundreds[tempNum / 100]);
        tempNum -= (tempNum / 100) * 100;
    }

    if ( tempNum < 100 && tempNum >= 30 )
    {
        if (!wrdStr.empty())
            wrdStr += " ";
        wrdStr += tens[tempNum / 10];
        if ((num % 10) != 0)
            wrdStr += (" y " + zeroTo29[num % 10]);
    }
    else if ( tempNum < 30 && !((tempNum == 0) xor (num == 0)) )
    {
        if (!wrdStr.empty())
            wrdStr += " ";
        wrdStr += zeroTo29[tempNum];
    }

    return wrdStr;
}

void setCustomOptions(int & numOfItems, int & xmin, int & xmax)
{
    bool changeOptions = true;
    while (inputsAreNotOkay(numOfItems, xmin, xmax) || changeOptions)
    {
        char charOption = 'y';
        
        cout << "How many items do you want to be quizzed over?" << endl;
        cin >> numOfItems; /* do check to make sure well-formed number */
        
        cout << "Enter a number range: xmin <= x <= xmax " << endl;
        
        cout << "xmin = ";
        cin >> xmin;
        
        cout << "xmax = ";
        cin >> xmax;
        
        cout << "You chose " << numOfItems << " numbers between " \
        << xmin << " and " << xmax << "." << endl;
        cout << "Keep these options? (y for yes, r for reset) ";
        cin >> charOption;
        if (charOption == 'y')
        changeOptions = false;
        else
        changeOptions = true;
        }
}

void loadOptions(int & numOfItems, int & xmin, int & xmax)
{
    unsigned short option;
    cout << "Pick a specific quiz or make your own." << endl;
    cout << "\t1: 1 to 10 (20 times)" << endl;
    cout << "\t2: 1 to 100 (30 times)" << endl;
    cout << "\t3: 1 to 1000 (30 times)" << endl;
    cout << "\t4: -1000 to 1000 (30 times)" << endl;
    cout << "\t5: custom" << endl;
    cout << "\t6: exit to main screen" << endl;
    
    cin >> option;
    switch (option) {
        case 1:
            numOfItems = 20;
            xmin = 1;
            xmax = 10;
            break;
        case 2:
            numOfItems = 30;
            xmin = 1;
            xmax = 100;
        case 3:
            numOfItems = 30;
            xmin = 1;
            xmax = 1000;
        case 4:
            numOfItems = 30;
            xmin = -1000;
            xmax = 1000;
        case 5:
            setCustomOptions(numOfItems, xmin, xmax);
            break;
        case 6:
            std::cin.std::ios::setstate(std::ios::eofbit);
            break;
        default:
            numOfItems = 20;
            xmin = 1;
            xmax = 10;
            break;
    }
}

int numbers()
{
    boost::random::mt19937 gen;
    gen.seed(time(0));
    int num, tempNum, numOfItems = 0, xmin = 0, xmax = 100;
    unsigned short numCorrect = 0;
    bool isCorrect = false;
    string wrdStr, response;
    
    loadOptions(numOfItems,xmin,xmax);

    cin.clear();
    cin.ignore(10,'\n');
    
    for (int ii = 1; ii <= numOfItems && !cin.eof(); ii++)
    {
        num = randNum(xmin,xmax,gen);

        wrdStr = numConstructor(num);

        cout << "What is " << num << " in Spanish?" << endl;
        getline(cin,response);
        if (cin.eof()) break;
        isCorrect = (response == wrdStr);

        if ( isCorrect )
        {
            cout << "You're right!" << endl;
            numCorrect++;
        }
        else
        {
            cout << "You're wrong! The correct response is: '" \
                 << wrdStr << "'" << endl;
            cout << response << endl;
            cout << whitespace(findFirstError(wrdStr,response)-2) \
                 << "^" << endl;
            cout << wrdStr << endl;
            cout << "You are off by: " << levenshtein(wrdStr, response)-1 \
                 << " letters." << endl;
            cout << "And your response is " << lcsPercent(wrdStr,response) \
                 << "% correct" << endl;
        }

        isCorrect = false;
        wrdStr.clear();
    }
    cout << "You got " << numCorrect << " correct out of " << numOfItems \
         << " (" \
         << static_cast<double> (numCorrect) / static_cast<double> (numOfItems) * 100.0 \
         << "%)." << endl;

    return 0;
}
