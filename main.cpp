#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <boost/lexical_cast.hpp>

using namespace std;
using boost::lexical_cast;
using boost::bad_lexical_cast;

bool isValidNumber(string &str) {
    bool flag = true;
    double num = 0.0;
    try {
        num = lexical_cast<double>(str);
        str = lexical_cast<string>(num);
    }
    catch (bad_lexical_cast &e) {
        flag = false;
    }
    return flag;
}
vector<string> split(string str, string delimiters) {
    vector<string> vecStrings;
    size_t pos = 0;
    std::string token;

    while ((pos = str.find(delimiters)) != std::string::npos) {
        token = str.substr(0, pos);
        vecStrings.push_back(token);
        str.erase(0, pos + delimiters.length());
    }

    if (vecStrings.size() == 0 && str.length() > 0)
        vecStrings.push_back(str);
    return vecStrings;
}

bool parse(string equation, const int row) {
    // char *szEquation = equation.trimmed().toUtf8().data();
    string Operators("+-*/%=");
    vector<string> pieces;

    // Split the stream into string tokens
    pieces = split(equation, Operators);

    // Check for numbers.
    for (vector<string>::iterator iter = pieces.begin(); iter != pieces.end(); ++iter) {
        string token = *iter;
        if (isValidNumber(token))
            cout << "Number: " << token << endl;
    }

    /*
    char *szEquation = equation;
    // QString regexNumbers("([+|-])*[0-9]+(\.*[0-9]*)");

    int i = 0;
    while (szEquation[i] != '\0') {
        char szBuffer[255] = {0};

        if (isNumber(szEquation))

        // Check to handle numbers first
        // It's a number if it starts with a digit, decimal point, or the first two characters are a sign and a number or decimal
        //  (+|-)*[0-9]*\.[0-9]+
        if (((szEquation[i] == '-' && isdigit(szEquation[i + 1])) || (szEquation[i] == '-' && szEquation[i + 1] == '.')) ||
                isdigit(szEquation[i]) ||
                szEquation[i] == '.') {
            char num[255] = {0};
            bool decimalFound = false;
            bool firstNonZeroFound = false;

            // if you see the sign then add and advance
            if (szEquation[i] == '-') {
                num[i] = szEquation[i];
                i++;
            }

            // remove leading zeroes
            string strPtr(szEquation);
            strPtr.erase(0, min(strPtr.find_first_not_of('0'), strPtr.size() - 1));
            szEquation = (char *)strPtr.data();

            while (szEquation[i] != '\0') {

                // immediately end with bad equation if a second decimal is found
                if (szEquation[i] == '.') {
                    if (decimalFound)
                        return false;
                    decimalFound = true;

                    // it's possible there is no zero before the decimal...
                    if (!firstNonZeroFound)
                        firstNonZeroFound = true;
                    num[i] = szEquation[i];
                }

                else if (isdigit(szEquation[i])) {

                    // ignore digits before the first usable number
                    // e.g.: 00023.88 => 23.88
                    while (szEquation[i] != '\0' && !firstNonZeroFound) {

                        // case of "0." -- in this circumstance we want to accept a leading zero
                        if ((szEquation[i] == '0' && szEquation[i + 1] == '.') || szEquation[i] != '0') {
                            firstNonZeroFound = true;
                        }
                        else
                            i++;
                    }
                    num[i] = szEquation[i];
                }
                else {
                    if (strchr(Operators, szEquation[i])) {

                        // the number has ended
                        strcpy(num, szBuffer);
                        break;
                    }

                    // it's something else making it a bad number
                    return false;
                }
                i++;
            }
            strcpy(szBuffer, num);
        }

        // Check to see if it's a potential variable (must start out as alphabetic)...
        else if (isalpha(szEquation[i])) {
            char *szVariable = NULL;

            // it's a potential variable...
        }

        // invalid string which nullifies the whole thing
        else
            return false;
        cout << "Value successfully save after parsing: " << szBuffer << endl;

        // it passed parsing tests so now go do searches in the rows.
    }
        */

    return true;
}

int main(char **argv, int argc) {

    cout << endl << "test removal of leading zeroes" << endl;
    (!parse("009", 0)) ? cout << "0 failed" << endl : cout << "0 passed" << endl;
    (!parse("009.1", 0)) ? cout << "0 failed" << endl : cout << "0 passed" << endl;
    (!parse("009.", 0)) ? cout << "0 failed" << endl : cout << "0 passed" << endl;
    (!parse("0", 0)) ? cout << "0 failed" << endl : cout << "0 passed" << endl;
    (!parse("00", 0)) ? cout << "00 failed" << endl : cout << "00 passed" << endl;
    (!parse("0.0", 0)) ? cout << "0.0 failed" << endl : cout << "0.0 passed" << endl;
    (!parse("0000.0", 0)) ? cout << "0000.0 failed" << endl : cout << "0000.0 passed" << endl;


    cout << endl << "test integers" << endl;
    (!parse("23", 0)) ? cout << "23 failed" << endl : cout << "23 passed" << endl;
    (!parse("-23", 0)) ? cout << "-23 failed" << endl : cout << "-23 passed" << endl;

    cout << endl << "test doubles without signs" << endl;
    (!parse("23.", 0)) ? cout << "23. failed" << endl : cout << "23. passed" << endl;
    (!parse("23.1", 0)) ? cout << "23.0 failed" << endl : cout << "23.0 passed" << endl;
    (!parse("23.0001", 0)) ? cout << "23.0000 failed" << endl : cout << "23.0000 passed" << endl;
    (!parse(".23", 0)) ? cout << ".23 failed" << endl : cout << ".23 passed" << endl;
    (!parse("0.23", 0)) ? cout << "0.23 failed" << endl : cout << "0.23 passed" << endl;
    (!parse("0000.23", 0)) ? cout << "0000.23 failed" << endl : cout << "0000.23 passed" << endl;
    (!parse("0.23000", 0)) ? cout << "0.23000 failed" << endl : cout << "0.23000 passed" << endl;

    cout << endl << "test doubles with signs" << endl;
    (!parse("-23.", 0)) ? cout << "-23. failed" << endl : cout << "-23. passed" << endl;
    (!parse("-23.0", 0)) ? cout << "-23.0 failed" << endl : cout << "-23.0 passed" << endl;
    (!parse("-23.0000", 0)) ? cout << "-23.0000 failed" << endl : cout << "-23.0000 passed" << endl;
    (!parse("-.23", 0)) ? cout << "-.23 failed" << endl : cout << "-.23 passed" << endl;
    (!parse("-0.23", 0)) ? cout << "-0.23 failed" << endl : cout << "-0.23 passed" << endl;
    (!parse("-0000.23", 0)) ? cout << "-0000.23 failed" << endl : cout << "-0000.23 passed" << endl;
    (!parse("-0.23000", 0)) ? cout << "-0.23000 failed" << endl : cout << "-0.23000 passed" << endl;
    return 0;
}
