#ifndef listerrors_h
#define listerrors_h

#include "lists.h"

/* ================================================================ */

enum ListErrorCodes {
    NO_ERROR = 0,
    NULL_NODE = -1,
    NULL_LIST = -2,
    MISSING_METHOD = -3,
    MISSING_DATA = -4,
    LIST_MISMATCH = -5,
    NOT_FOUND = -6
};

/* ================================ */

/**
 * \brief Returns the string describing the error that just occurred based on the provided code.
 * 
 * This function takes a returned value from a function belonging to the `sList_` family, which operates on a list,
 * and checks if the returned value indicates an error. If an error is detected, it returns a meaningful error message.
 * 
 * \param[in] code the value returned by a function from the `sList_` family.
 * 
 * \return a string containing the error description.
 */
extern char* sList_error(int error_code);

/* ================================================================ */

#endif /* listerrors_h */
