/* File : strutils.cpp
 * Last modified September 2011
 * -----------------------------------
 * Invalid conversions raise an ErrorException, 
 * which can be caught and handled by students
 */


#include <sstream>
#include <string>
#include "genlib.h"

/*
 * Function: IntegerToString
 * Usage: s = IntegerToString(n);
 */

std::string IntegerToString(int num) {
    std::stringstream result;
    result << num;
    return result.str();
}

/*
 * Function: RealToString
 * Usage: s = RealToString(d);
 */

std::string RealToString(double num) {
    std::stringstream result;
    result << num;
    return result.str();
}

/*
 * Function: StringToInteger
 * Usage: n = StringToInteger(s);
 */

int StringToInteger(std::string str)
{
    int returnVal;
    std::istringstream result(str);
    std::string rest;

    if ((result >> returnVal).fail()) {
	Error("Not a valid number!");
    }
    result >> rest;
    if (rest != "") {
	Error("Extra characters not allowed");
    }
    return returnVal;
}

/*
 * Function: StringToReal
 * Usage: d = StringToReal(s);
 */

double StringToReal(std::string str) {
    double returnVal;
    std::istringstream result(str);
    std::string rest;

    if ((result >> returnVal).fail()) {
	Error("Not a valid number!");
    }
    result >> rest;
    if (rest != "") {
	Error("Extra characters not allowed");
    }
    return returnVal;
}

/*
 * Function: ConvertToLowerCase
 * Usage: s = ConvertToLowerCase(s);
 */

std::string ConvertToLowerCase(std::string str)
{
    const int length = str.length();
    for(int i=0; i < length; i++) {
	    str[i] = tolower(str[i]);
	}
    return str;
}

/*
 * Function: ConvertToUpperCase
 * Usage: s = ConvertToUpperCase(s);
 */

std::string ConvertToUpperCase(std::string str) {
    const int length = str.length();
    for(int i=0; i < length; i++) {
	    str[i] = toupper(str[i]);
	}
    return str;
}

