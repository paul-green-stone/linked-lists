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
    LIST_MISMATCH = -5
};

/* ================================ */

/**
 * \brief Prints a meaningful error message based on the returned value from `sList_` family of functions.
 * 
 * This function takes a returned value from a function belonging to the `sList_` family, which operates on a list,
 * and checks if the returned value indicates an error. If an error is detected, it prints a meaningful error message.
 * 
 * \param[in] code The value returned by a function from the `sList_` family.
 * 
 * \return none.
 */
extern void sList_perror(int error_code);

/* ================================================================ */

#endif /* listerrors_h */
