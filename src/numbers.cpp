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


Number::Number()
       :numOfItems(10), xmin(0), xmax(1000), currentNum(0)
{
}

void Number::setNumber(usInt newnumOfItems, long newxmin, long newxmax)
{
    numOfItems = newnumOfItems;
    xmin = newxmin;
    xmax = newxmax;
}

long randNum(long lowLim, long upLim, boost::random::mt19937_64 &gn)
{
#ifdef DEBUG
    cout << "Entered randNum" << endl;
#endif // DEBUG

    boost::random::uniform_int_distribution<long> dist(lowLim, upLim);

#ifdef DEBUG
    long randomNum = dist(gn);
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

string commaAdder(const string str, const bool sign)
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

bool inputsAreNotOkay(Number & num)
{
    return !((num.getxmax() > num.getxmin()) && (num.getnumOfItems() > 0));
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

void setCustomOptions(Number & num)
{
    bool changeOptions = true;
    usInt numItems;
    long xmn, xmx;
    char * temp;

    while (inputsAreNotOkay(num) || changeOptions)
    {
        char charOption = 'y';

        // TODO: Change this line to something like option = readint(">> ");
        temp = readline("How many items do you want to be quizzed over?\n>> ");
        numItems = atoi(temp);

        cout << "Enter a number range: xmin <= x <= xmax " << endl;

        // TODO: Change this line to something like option = readint(">> ");
        temp = readline("xmin = ");
        xmn = atol(temp);
        temp = readline("xmax = ");
        xmx = atol(temp);

        cout << "You chose " << numItems << " numbers between " \
             << commaAdder(ltest::numToStr(xmn),ltest::sgn(xmn)) << " and " \
             << commaAdder(ltest::numToStr(xmx),ltest::sgn(xmx)) << "." << endl;
        ltest::takeInput(charOption,"Keep these options? (y for yes, r for reset) ");

        if (charOption == 'y')
            changeOptions = false;
        else
            changeOptions = true;
    }

    num.setNumber(numItems,xmn,xmx);
    free(temp);
}

//void loadOptions(Number & num);
void loadOptions(Number & num)
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
            num.setNumber(20,0,10);
            break;
        case 2:
            num.setNumber(30,0,100);
            break;
        case 3:
            num.setNumber(30,0,1000);
            break;
        case 4:
            num.setNumber(20,-1000,1000);
            break;
        case 5:
            num.setNumber(10,-100000,100000);
            break;
        case 6:
            setCustomOptions(num);
            break;
        case 7:
            cin.std::ios::setstate(std::ios::eofbit);
            break;
        default:
            num.setNumber(20,0,10);
            break;
    }
    free(opt);
}

int numbers(Account & acct)
{
    boost::random::mt19937_64 gen;
    gen.seed(time(0));
    Number nm;
    usInt numCorrect = 0;
    long num;
    bool isCorrect = false;
    string answer, response;
    vector<usInt> vectorTemp;
    

    loadOptions(nm);

    for (usInt ii = 1; ii <= nm.getnumOfItems() && !cin.eof(); ii++)
    {
        num = randNum(nm.getxmin(),nm.getxmax(),gen);
        vectorTemp = numDecomp(num);

#ifdef DEBUG
        cout << "num = " << num << endl;
#endif // DEBUG

        answer = numConst(num);

        cout << "What is " << commaAdder(ltest::numToStr(abs(num)),ltest::sgn(num)) << " in Spanish?" << endl;

/* TODO: change response to char * to address memory leak? */
        response = readline(">> ");
        isCorrect = (response == answer);

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
                 << answer << "'" << endl;

            /* Shows first error -- doesn't work with accented words */
            cout << response << endl;
            cout << ltest::printWhitespace(findFirstError(answer,response)-2) \
                 << "^" << endl;
            cout << answer << endl;

            /* Calculates word differences */
            cout << "You are off by: " << wordCompare::levenshtein(answer, response)-1 \
                 << " letters." << endl;
            cout << "And your response is " << wordCompare::lcsPercent(answer,response) \
                 << "% correct" << endl;
        }

        isCorrect = false;
        answer.clear();
// TODO: Does the following clear empty the whole vector?
        vectorTemp.clear();
    }
    cout << "You got " << numCorrect << " correct out of " << nm.getnumOfItems() \
         << " (" \
         << static_cast<double> (numCorrect) / static_cast<double> (nm.getnumOfItems()) * 100.0 \
         << "%)." << endl;

    cin.clear(cin.rdstate()); // ugh, this doesn't seem to be clearing the eofbit...
    return 0;
}

// EOF
