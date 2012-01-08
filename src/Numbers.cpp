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

#include "Numbers.h"

/* Load these from a file eventually? */
string zeroTo29[] = {"cero", "uno", "dos", "tres", "cuatro", "cinco", "seis",
                     "siete", "ocho", "nueve", "diez", "once", "doce", "trece",
                     "catorce", "quince", "dieciséis", "diecisiete",
                     "dieciocho", "diecinueve", "veinte", "veintiuno",
                     "veintidós", "veintitrés", "veinticuatro", "veinticinco",
                     "veintiséis", "veintisiete", "veintiocho", "veintinueve"};

string tens[] = {"cero", "diez", "veinte", "treinta", "cuarenta",
                 "cincuenta", "sesenta", "setenta", "ochenta",
                 "noventa"};

string hundreds[] = {"cero", "ciento", "doscientos", "trescientos",
                     "cuatrocientos", "quinientos", "seiscientos",
                     "setecientos", "ochocientos", "novecientos"};

//string powersOfTen[] = {"uno", "diez", "cien", "mil", "diez mil",
//                        "cien mil", "millón", "diez millón", "cien millón",
//                        "mil millones", "diez mil millones", 
//                        "cien mil millones", "billón", "diez billón"};

string powersOfThousand[] = {"", "mil", "millón", "mil millones", "billón",
                             "mil billones", "trillón", "mil trillones"};

Number::Number()
       :numOfItems(10), numCorrect(0), \
        xmin(0), xmax(1000), currentNum(0), numWord("cero")
{
}

void Number::printNumber()
{
    cout << "Number contains: " << endl;
    cout << "\t numOfItems = " << numOfItems << endl;
    cout << "\t xmin = " << xmin << endl;
    cout << "\t xmax = " << xmax << endl;
    cout << "\t currentNum = " << currentNum << endl;
}

void Number::setNumber(usInt newnumOfItems, long newxmin, long newxmax)
{
    numOfItems = newnumOfItems;
    xmin = newxmin;
    xmax = newxmax;
}

void Number::getNewNumber(boost::random::mt19937_64 & gen)
{
    currentNum = randNum(gen);
    numWord = numConst(currentNum);
}

long Number::randNum(boost::random::mt19937_64 &gn)
{
#ifdef DEBUG
    cout << "Entered randNum" << endl;
#endif // DEBUG

    boost::random::uniform_int_distribution<long> dist(xmin, xmax);

#ifdef DEBUG
    long randomNum = dist(gn);
    cout << "dist(gn) = " << randomNum << endl;
    return randomNum;
#else

    return dist(gn);

#endif // DEBUG
}

void Number::incrNumCorrect()
{
    numCorrect++;
}

bool Number::inputsAreNotOkay()
{
    return !((xmax > xmin) && (numOfItems > 0));
}

void Number::setCustomOptions()
{
    bool changeOptions = true;
    usInt numItems = 10;
    long xmn = 0, xmx = 10;
    char * temp = NULL;

    do
    {
        temp = readline("How many items do you want to be quizzed over?\n>> ");
        numItems = atoi(temp);

        cout << "Enter a number range: xmin <= x <= xmax\n" \
             << "(enter 'max' for the largest value possible,\n" \
             << " and 'min' for the smallest value possible.)" << endl;

        temp = readline("min = ");

        if (!strcmp(temp,"min"))
            xmn = numeric_limits<long>::min() ;
        else
            xmn = atol(temp);

        temp = readline("max = ");

        if (!strcmp(temp,"max"))
            xmx = numeric_limits<long>::max();
        else
            xmx = atol(temp);

        cout << "You chose " << numItems << " numbers between " \
             << ltest::commaAdder(ltest::numToStr(labs(xmn)),ltest::sgn(xmn)) \
             << " and " \
             << ltest::commaAdder(ltest::numToStr(labs(xmx)),ltest::sgn(xmx)) \
             << "." << endl;

        temp = readline("Keep these options? (y for yes, r to reset)? ");

        if (temp[0] == 'y')
            changeOptions = false;
        else
            changeOptions = true;
    } while (this->inputsAreNotOkay() || changeOptions);

    this->setNumber(numItems,xmn,xmx);
    free(temp);
}

void Number::loadOptions()
{
    int option;
    char * opt = NULL;

    cout << "Pick a specific quiz or make your own.\n" \
         << "\t1: 0 to 10 (20 times)\n" \
         << "\t2: 0 to 100 (30 times)\n" \
         << "\t3: 0 to 1000 (30 times)\n" \
         << "\t4: -1000 to 1000 (20 times)\n" \
         << "\t5: -1E6 to 1E6 (10 times)\n" \
         << "\t6: -1E8 to 1E8 (10 times)\n" \
         << "\t7: -1E13 to 1E13 (5 times)\n" \
         << "\t8: custom\n" \
         << "\t9: exit to main screen" << endl;

    opt = readline(">> ");
    option = atoi(opt);

    switch (option)
    {
        case 1:
            this->setNumber(20,0,10);
            break;
        case 2:
            this->setNumber(30,0,100);
            break;
        case 3:
            this->setNumber(30,0,1000);
            break;
        case 4:
            this->setNumber(20,-1000,1000);
            break;
        case 5:
            this->setNumber(10,-100000,100000);
            break;
        case 6:
            this->setNumber(10,-100000000,100000000);
            break;
        case 7:
            this->setNumber(5,-10000000000000,10000000000000);
            break;
        case 8:
            this->setCustomOptions();
            break;
        case 9:
            exitToMain = true;
            break;
        default:
            this->setNumber(20,0,10);
            break;
    }
#ifdef DEBUG
    this->printNumber();
#endif // DEBUG
    free(opt);
}

/* Construct numbers of length -LONG_MAX to LONG_MAX in words */
string Number::numConst(const long num)
{
    vector<usInt> nums = ltest::numDecomp(num);
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

    boost::algorithm::trim_right(wordString);

    return wordString;
}

/* Construct a number between zero and 999 in words */
string Number::auxConst(const usInt var)
{
    string wrdStr;
    usInt tempVar = var;

    if ( tempVar >= 1000 )
    {
        cerr << "Error: out of range." << endl;
        exit(0);
    }
    else if ( tempVar < 1000 && tempVar >= 100 )
    {
        wrdStr += hundreds[tempVar / 100];

        tempVar %= 100;
    }

    if ( tempVar < 100 && tempVar >= 30 )
    {
        ltest::addSpace(wrdStr);

        wrdStr += tens[tempVar / 10];

        if ((var % 10) != 0)
            wrdStr += (" y " + zeroTo29[tempVar % 10]);
    }
    else if ( tempVar < 30 && !((tempVar == 0) xor (var == 0)) )
    {
        ltest::addSpace(wrdStr);

        wrdStr += zeroTo29[tempVar];
    }
    return wrdStr;
}

usInt getPower(const long rawInt)
{
    long temp = rawInt;
    unsigned short mag = 0;
    cout << setw(9) << "temp" << setw(3) << "  mag\n" \
         << setw(9) << temp << "  " << setw(3) << mag << endl;

    while (temp >= 10)
    {
        mag++;
        temp /= 10;
        cout << setw(9) << temp << "  " << setw(3) << mag << endl;
    }

    return mag;
}

int numbers(Account & acct)
{
    boost::random::mt19937_64 gen;
    gen.seed(time(0));
    Number nm;
    bool isCorrect = false;
    string response;

    nm.loadOptions();

    for (usInt ii = 0; ii < nm.getnumOfItems() && !exitToMain; ii++)
    {
        nm.getNewNumber(gen);

        cout << "What is " << ltest::commaAdder(ltest::numToStr(labs(nm.getCurrNum())), \
                                                ltest::sgn(nm.getCurrNum())) \
             << " in Spanish?" << endl;

/* TODO: change response to char * to address memory leak? */
        response = readline(">> ");
        isCorrect = (response == nm.getNumWord());

        if (ltest::exitProg(response.c_str(),exitToMain)) break;
        else if ( isCorrect )
        {
            if (acct.getVerbose())
                cout << "You're right!" << endl;
            nm.incrNumCorrect();
        }
        else // if wrong
        {
            cout << "You're wrong! The correct response is: '" \
                 << nm.getNumWord() << "'" << endl;

            /* Shows first error -- doesn't work with accented words */
            cout << response << '\n' \
                 << ltest::printWhitespace(wordCompare::findFirstError(nm.getNumWord(),response)-1) \
                 << "^\n" \
                 << nm.getNumWord() << endl;

            cout.setf(std::ios::fixed);
            cout.precision(0);
            /* Calculates word differences */
            cout << "You are off by: " \
                 << wordCompare::levenshtein(nm.getNumWord(), response)-1 \
                 << " letters.  And your response is " \
                 << wordCompare::lcsPercent(nm.getNumWord(),response) \
                 << "% correct." << endl;
        }

        isCorrect = false;
    }

    cout << "You got " << nm.getNumCorrect() << " correct out of " \
         << nm.getnumOfItems() << " (" \
         << ltest::frac(nm.getNumCorrect(),nm.getnumOfItems()) * 100.0 \
         << "%)." << endl;

    return 0;
}

// EOF
