/*
 * File: genlib.h
 * -----------------------------------------------------
 * This header file is included in Assignment 1 to 
 * provide a few common definitions. 
 *
 */

#ifndef _genlib_h
#define _genlib_h

#include <string>
#include <exception>

/*
 * Class: ErrorException
 * ---------------------
 * This exception is raised by calls to the Error function, which
 * makes it possible for clients to respond to error conditions
 * without having their programs bomb completely.
 */

class ErrorException : public std::exception {
public:
    ErrorException(std::string msg = "unspecified custom error");
    virtual ~ErrorException() throw ();
    virtual const char* what() const throw ();
    //virtual std::string getMessage();
private:
    std::string msg;
};

/*
 * Function: Error
 * Usage: Error(msg);
 * ------------------
 * Error is used to signal an error condition in a program.  It first
 * throws an ErrorException.  If that isn't caught, it outputs the
 * error message string to the cerr stream and then exits the program
 * with a status code indicating failure.
 */

void Error(std::string str);

#endif
