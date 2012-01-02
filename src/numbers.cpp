/*
 *  numbers.cpp
 *
 *  Description:
 *   Quiz of integer numbers.  This program constructs numbers into a specified
 *   language, quizzes the user, shows the correctness, and more.  Part of
 *   LanguageTest.cpp
 *
 *  Created by Añdy Eschbacher on 11/8/11.
 *
 */

#include "numbers.h"

/* Load these from a file eventually */
string zeroTo29[] = {"cero", "uno", "dos", "tres", "cuatro", "cinco", "seis",
                     "siete", "ocho", "nueve", "diez", "once", "doce", "trece",
                     "catorce", "quince", "dieciséis", "diecisiete",
                     "dieciocho", "diecinueve", "veinte", "veintiuno",
                     "veintidós", "veintitrés", "veinticuatro", "veinticinco",
                     "veintiséis", "veintisiete", "veintiocho", "veintinueve"};

string tens[] = {"cero", "diez", "veinte", "treinta", "cuarenta",
                 "cincuenta", "sesenta", "setenta", "ochenta",
                 "noventa"};

string hundreds[] = {"cero", "ciento","doscientos", "trescientos",
                     "cuatrocientos", "quinientos", "seiscientos",
                     "setecientos", "ochocientos", "novecientos"};

//string powersOfTen[] = {"uno", "diez", "ciento", "mil", "diez mil",
//                        "cien mil", "millón", "mil millones",
//                        "billón"};

string powersOfThousand[] = {"", "mil", "millón", "mil millones", "billón"};

long randNum(int lowLim, int upLim, boost::random::mt19937 &gn)
{
#ifdef DEBUG
    cout << "Entered randNum" << endl;
#endif // DEBUG

    boost::random::uniform_int_distribution<> dist(lowLim, upLim);

#ifdef DEBUG
    int randomNum = dist(gn);
    cout << "dist(gn) = " << randomNum << endl;
    return randomNum;
#else // not define DEBUG
    return dist(gn);
#endif // DEBUG
}

// Only handles positive numbers
vector<usInt> numDecomp(const long num)
{
    long tempNum = (num < 0 ? -1.0 : 1.0) * num;
    vector<usInt> numbers;

#ifdef DEBUG
    cout << "numConst values: " << endl;
#endif // DEBUG
    while (tempNum != 0 || num == 0)
    {
        if (num == 0)
        {
            numbers.push_back(0);
            break;
        }

        numbers.push_back(tempNum % 1000);
#ifdef DEBUG
        cout << tempNum % 1000 << endl;
#endif //DEBUG
        tempNum /= 1000;
    }

    return numbers;
}

string numConst(const long num)
{
    vector<usInt> nums = numDecomp(num);
    string wordString;
    if (num < -1)
        wordString = "negativos ";
    else if (num == -1)
        wordString = "negativos ";

    for (int ii = nums.size()-1; ii >= 0; ii--)
    {
        wordString += (auxConst(nums.at(ii)) + " " + powersOfThousand[ii]);
        if (ii > 0)
            wordString += " ";
    }
    
    if (wordString[wordString.length()-1] == ' ')
        wordString.erase(wordString.length()-1);

//    wordString = removeLeadingTrailingSpaces(wordString);

    return wordString;
}

string auxConst(const usInt var)
{
    string wrdStr;
    usInt tempVar = var;

    if ( tempVar >= 1000)
    {
        cerr << "Error: out of range." << endl;
        exit(0);
    }
    else if ( tempVar <= 1000 && tempVar >= 100 )
    {
        wrdStr += hundreds[tempVar / 100];
        
        tempVar = tempVar % 100;
    }
    
    if ( tempVar < 100 && tempVar >= 30 )
    {
        addSpace(wrdStr);
        
        wrdStr += tens[tempVar / 10];
        
        if ((var % 10) != 0)
            wrdStr += (" y " + zeroTo29[tempVar % 10]);
    }
    else if ( tempVar < 30 && !((tempVar == 0) xor (var == 0)) )
    {
        addSpace(wrdStr);
        
        wrdStr += zeroTo29[tempVar];
    }
    return wrdStr;
}

void addSpace(string & temp)
{
    if (!temp.empty())
        temp += " ";
}

string commaAdder(const string str, bool sign)
{
    string word(str);
    
    for (short jj = word.size() - 3;
         jj > 0;
         jj -= 3)
    {
        word.insert(jj,",");
    }

    if (!sign) word.insert(0,"-");
    
    return word;
}

//string numCommaed(vector<usInt> & nums)
//{
//    string commaString;
//
//    commaString = (nums.at(nums.size()-1) + "");
//    cout << "nums.at(nums.size()-1) = " << nums.at(nums.size()-1) << endl;
//    cout << "commaString = " << commaString << endl;
//
//    for (int ii = nums.size() - 2; ii >= 0; ii--)
//    {
//        commaString += ("," + nums.at(ii));
//        cout << "nums.at(" << ii << ") = " << nums.at(ii) << endl;
//        cout << "commaString = " << commaString << endl;
//    }
//
//
//    return commaString;
//}

usInt getPower(const long rawInt)
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
    for (usInt ii = 0; ii < ltest::min<size_t>(ans.size(),cmp.size()); ii++)
    {
        if (ans.at(ii) == cmp.at(ii))
            errorPos++;
        else
            break;
    }

    return errorPos;
}

int reduce(int num, int mag)
{
    return (num/mag)*mag;
}

/* need a 'number constructor' function that takes into account sign and magnitude */
string numConstructor(const long num)
{
    string wrdStr;
    long tempNum = num;
    
    if (num < 0)
    {
#ifdef DEBUG
        cout << num << " is negative" << endl;
#endif // DEBUG
        tempNum *= -1.0;
        if (tempNum != 1)
            wrdStr += "negativos";
        else if (tempNum == 1)
            wrdStr += "negativo";
    }

    // Special cases
    if (abs(num) == 100)
    {
        wrdStr = "cien";
        tempNum = 0;
    }

    /* Extract 1E4 to 1E5 portion?
     *  134,000 / 1E3 = 134 --> construct number from this
     *
     *  How about splitting up number into regions abc,def,ghi
     *  Where each has same behaviors but ends in different suffices, such as:
     *  987,123,456,789 = (nine hundred eighty seven) billion
     *                    (one hundred twenty three) million
     *                    (four hundred fifty six) thousand
     *                    (seven hundred eighty nine)
     */

/* TODO: Replace this arduous algorithm with something leaner
 by using reduce() as a member function */
    if ( tempNum < 1000000 && tempNum >= 30000 )
    {
        if (!wrdStr.empty())
            wrdStr += " ";
        wrdStr += tens[tempNum / 10000];
#ifdef DEBUG
        cout << "wrdStr = '" << wrdStr << "' (" << tempNum << ")" << endl;
#endif
        tempNum -= (tempNum / 10000) * 10000;
#if DEBUG
        cout << "tempNum is now: " << tempNum << endl;
#endif // DEBUG
        if ((tempNum / 1000) != 0)
            wrdStr += (" y " + zeroTo29[tempNum / 1000]);
        wrdStr += " mil";
        tempNum -= (tempNum / 1000) * 1000;
    }
    else if ( tempNum < 30000 && tempNum >= 1000 )
    {
        if (!wrdStr.empty())
            wrdStr += " ";
        wrdStr += (zeroTo29[tempNum / 1000] + " mil");
#ifdef DEBUG
        cout << "wrdStr = '" << wrdStr << "' (" << tempNum << ")" << endl;
#endif
        tempNum -= (tempNum / 1000) * 1000;
    }

    if ( tempNum < 1000 && tempNum >= 100 )
    {
        if (!wrdStr.empty())
            wrdStr += " ";
        wrdStr += hundreds[tempNum / 100];
#ifdef DEBUG
        cout << "wrdStr = '" << wrdStr << "' (" << tempNum << " -> ";
#endif
        tempNum -= (tempNum / 100) * 100;
#ifdef DEBUG
        cout << tempNum << ")" << endl;
#endif
    }

    if ( tempNum < 100 && tempNum >= 30 )
    {
        if (!wrdStr.empty())
            wrdStr += " ";
        wrdStr += tens[tempNum / 10];
        if ((num % 10) != 0)
            wrdStr += (" y " + zeroTo29[tempNum % 10]);
#ifdef DEBUG
        cout << "wrdStr = '" << wrdStr << "' (" << tempNum << ")" << endl;
#endif
    }
    else if ( tempNum < 30 && !((tempNum == 0) xor (num == 0)) )
    {
        if (!wrdStr.empty())
            wrdStr += " ";
        wrdStr += zeroTo29[tempNum];
#ifdef DEBUG
        cout << "wrdStr = '" << wrdStr << "' (" << tempNum << ")" << endl;
#endif
    }

    return wrdStr;
}

void setCustomOptions(usInt & numOfItems, int & xmin, int & xmax)
{
    bool changeOptions = true;
    while (inputsAreNotOkay(numOfItems, xmin, xmax) || changeOptions)
    {
        char charOption = 'y';

        // TODO: Change this line to something like option = readint(">> ");
        numOfItems = atoi(readline("How many items do you want to be quizzed over?\n>> "));

        cout << "Enter a number range: xmin <= x <= xmax " << endl;

        // TODO: Change this line to something like option = readint(">> ");
        xmin = atoi(readline("xmin = "));
        xmax = atoi(readline("xmax = "));

        cout << "You chose " << numOfItems << " numbers between " \
             << xmin << " and " << xmax << "." << endl;
        ltest::takeInput(charOption,"Keep these options? (y for yes, r for reset) ");

        if (charOption == 'y')
            changeOptions = false;
        else
            changeOptions = true;
    }
}

//void loadOptions(Number & num);
void loadOptions(usInt & numOfItems, int & xmin, int & xmax)
{
    int option;
    char * opt;
    cout << "Pick a specific quiz or make your own." << endl;
    cout << "\t1: 1 to 10 (20 times)" << endl;
    cout << "\t2: 1 to 100 (30 times)" << endl;
    cout << "\t3: 1 to 1000 (30 times)" << endl;
    cout << "\t4: -1000 to 1000 (20 times)" << endl;
    cout << "\t5: -1E6 to 1E6 (10 times)" << endl;
    cout << "\t6: custom" << endl;
    cout << "\t7: exit to main screen" << endl;

    // TODO: Change this line to something like option = readint(">> ");
    // currently this is a memory leak apparently.
    opt = readline(">> ");
    option = atoi(opt);

    switch (option)
    {
        case 1:
            numOfItems = 20;
            xmin = 1;
            xmax = 10;
            break;
        case 2:
            numOfItems = 30;
            xmin = 1;
            xmax = 100;
            break;
        case 3:
            numOfItems = 30;
            xmin = 1;
            xmax = 1000;
            break;
        case 4:
            numOfItems = 20;
            xmin = -1000;
            xmax = 1000;
            break;
        case 5:
            numOfItems = 10;
            xmin = -100000;
            xmax = 100000;
            break;
        case 6:
            setCustomOptions(numOfItems, xmin, xmax);
            break;
        case 7:
            cin.std::ios::setstate(std::ios::eofbit);
            break;
        default:
            numOfItems = 20;
            xmin = 1;
            xmax = 10;
            break;
    }
    free(opt);
}

int numbers(Account & acct)
{
    boost::random::mt19937 gen;
    gen.seed(time(0));
    usInt numOfItems = 0;
    long num;
    int xmin = 0, xmax = 100;
    unsigned short numCorrect = 0;
    bool isCorrect = false;
    string wrdStr, response;
    vector<usInt> vectorTemp;

    loadOptions(numOfItems,xmin,xmax);

    for (usInt ii = 1; ii <= numOfItems && !cin.eof(); ii++)
    {
        num = randNum(xmin,xmax,gen);
        vectorTemp = numDecomp(num);

#ifdef DEBUG
        cout << "num = " << num << endl;
#endif // DEBUG

//        wrdStr = numConstructor(num);
        wrdStr = numConst(num);

        cout << "What is " << commaAdder(ltest::numToStr(abs(num)),ltest::sgn(num)) << " in Spanish?" << endl;

/* TODO: change response to char * to address memory leak? */
        response = readline(">> ");
        isCorrect = (response == wrdStr);

        if (ltest::exitProg(response.c_str(),cin.eof())) break;
        else if ( isCorrect )
        {
            if (acct.getVerbose())
                cout << "You're right!" << endl;
            numCorrect++;
        }
        else // if wrong
        {
            cout << "You're wrong! The correct response is: '" \
                 << wrdStr << "'" << endl;

            /* Shows first error -- doesn't work with accented words */
            cout << response << endl;
            cout << ltest::printWhitespace(findFirstError(wrdStr,response)-2) \
                 << "^" << endl;
            cout << wrdStr << endl;

            /* Calculates word differences */
            cout << "You are off by: " << wordCompare::levenshtein(wrdStr, response)-1 \
                 << " letters." << endl;
            cout << "And your response is " << wordCompare::lcsPercent(wrdStr,response) \
                 << "% correct" << endl;
        }

        isCorrect = false;
        wrdStr.clear();
    }
    cout << "You got " << numCorrect << " correct out of " << numOfItems \
         << " (" \
         << static_cast<double> (numCorrect) / static_cast<double> (numOfItems) * 100.0 \
         << "%)." << endl;

    cin.clear(cin.rdstate()); // ugh, this doesn't seem to be clearing the eofbit...
    return 0;
}

// EOF
