#include <iostream>
#include <cstring>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <regex>

using namespace std;
using boost::lexical_cast;
using boost::bad_lexical_cast;

void test(const string str);
void pass(const string str);
void fail(const string str);
void print(const string str);
bool isValidNumber(string &str);
bool isValidVariable(string &str);
void Tokenize(const string &str, vector<string> &tokens, const string &delimiters);
bool parse(const string equation, const int row);
void testNumbers();
void testVariables();
void testEquations();

void test(const string str) {
    (!parse(str, 0)) ? fail(str) : pass(str);
}

void pass(const string str) {
    cout << str << " passed" << endl;
}
void fail(const string str) {
    cout << str << " failed" << endl;
}
void print(const string str) {
    cout << endl << str << endl;
}

bool isValidNumber(string &str) {
    bool bPassed = true;
    double num = 0.0;
    try {
        num = lexical_cast<double>(str);
        str = lexical_cast<string>(num);

        // Append a .0 on the end of the string if there isn't a decimal.
        if (str.find_first_of('.') == string::npos)
            str += ".0";
    }
    catch (bad_lexical_cast &e) {
        bPassed = false;
    }
    return bPassed;
}

bool isValidVariable(string &str) {
    smatch match;

    // This case should NEVER happen but just in case
    if (str.empty())
        return false;
    regex regexPattern("^[a-zA-Z][a-zA-Z0-9_]*$");
    if (!regex_match(str, match, regexPattern))
        return false;
    return true;
}
void Tokenize(const string &str, vector<string> &tokens, const string &delimiters) {

    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);

    // Find first "non-delimiter".
    string::size_type pos = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos) {

        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));

        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);

        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

bool parse(const string equation, const int row) {
    string Operators("+-*/%=() ");
    vector<string> pieces;

    // Split the stream into string tokens
    Tokenize(equation, pieces, Operators);

    // Check for numbers.
    for (vector<string>::iterator iter = pieces.begin(); iter != pieces.end(); ++iter) {
        string token = *iter;
        if (isValidNumber(token)) {
        }
        else if (isValidVariable(token)) {
        }
        else {
            cout << "ERROR: \"" << token << "\" is neither a number or a Variable.";
            return false;
        }
    }
    return true;
}

void testNumbers() {
    vector<string> strs = {
        "009",
        "009.1",
        "009.",
        "0",
        "00",
        "0.0",
        "0000.0",
        "23",
        "-23",
        "23.",
        "23.1",
        "23.0001",
        ".23",
        "0.23",
        "0000.23",
        "0.23000",
        "-23.",
        "-23.0",
        "-23.0000",
        "-.23",
        "-0000.23",
        "-0.23000",
    };
    print("Testing Valid cases of Numbers");
    for (vector<string>::iterator iter = strs.begin(); iter != strs.end(); ++iter)
        test(*iter);
}

void testVariables() {
    vector<string> valid = {
        "Albacore",
        "Albacore1",
        "Albacore1_",
        "Alba_core1",
        "A_lbacore1",
        "Alb23_acore1",
        "Albac_23ore1_"
    };
    vector<string> invalid = {
        "_Albac_23ore1_",
        "23Albac_23ore1_",
        "23_Albac_23ore1_"
    };

    print("Testing Valid cases of Variables");
    for (vector<string>::iterator iter = valid.begin(); iter != valid.end(); ++iter)
        test(*iter);

    print("Testing Invalid cases of Variables");
    for (vector<string>::iterator iter = invalid.begin(); iter != invalid.end(); ++iter)
        test(*iter);
}

void testEquations() {
    vector<string> eqs = {
        "a=v_x / (t1-t0)",
        "x_f - x_i = v_0*(t1 - t0) + 0.5*a*sq(t1 - t0)"
    };

    print("Testing Invalid cases of Variables");
    for (vector<string>::iterator iter = eqs.begin(); iter != eqs.end(); ++iter)
        test(*iter);
}

int main(char **argv, int argc) {
    testNumbers();
    testVariables();
    testEquations();
    return 0;
}
