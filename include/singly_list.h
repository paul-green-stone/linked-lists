#ifndef singly_list_h
#define singly_list_h

#include "lists.h"

#define sList_print(list) (sList_printTo(list, stdout))

/* ================================================================ */

/**
 * \brief Creates a new instance of a singly-linked list.
 * 
 * This function creates a new instance of a singly-linked list and initializes
 * it with the provided user-defined functions. The `destroy` function is used
 * to free the memory occupied by the data stored in each node when the list is
 * destroyed. The `print` function is used to print the contents of the list,
 * and the `match` function is used to compare the data in the list with a
 * user-defined key.
 * 
 * \param[out] list A pointer to a list to store a new list.
 * \param[in] destroy A user-defined function to free the memory occupied by the
 *                data stored in each node when the list is destroyed. For example, if the list contains data dynamically allocated
using `malloc`, destroy should be set to `free` to free the data as the linked list is destroyed. For structured data containing several dynamically allocated members, destroy should be set to a user-defined function that calls `free` for each dynamically allocated member as well as for the structure itself
 * \param[in] print A user-defined function to print the contents of the list.
 * \param[in] match A user-defined function to compare the data in the list with a
 *                user-defined key.
 * 
 * \return 0 on success, a non-zero value otherwise.
 */
extern int sList_new(sList_t* list, void (*destroy)(void* data), void (*print)(void* data, FILE* file), int (*match)(void* data_1, void* data_2));

/* ================================ */

/**
 * \brief Destroys a singly-linked list and frees its associated memory.
 * 
 * This function destroys a singly-linked list by deallocating the memory
 * occupied by each node and calling the user-defined `destroy` function on
 * each node's data. It takes a pointer to the list to be destroyed as input.
 * 
 * \param[in] list A pointer to the singly-linked list to be destroyed.
 * 
 * \remark The `destroy` function should be implemented by the user and will be
 *         responsible for freeing the memory occupied by the data stored in each node.
 * 
 * \return 0 on success, a non-zero value otherwise.
 */
extern int sList_destroy(sList_t* list);

/* ================================ */

/**
 * \brief Inserts a new node with the given data at the end of a singly-linked list.
 * 
 * This function inserts a new node with the provided data at the end of the
 * singly-linked list. The newly inserted node becomes the last node in the list.
 * 
 * \param[in] list A singly-linked list to insert the new node into.
 * \param[in] data A pointer to the data to be stored in the new node.
 * 
 * \return 0 on success, or a non-zero value otherwise.
 */
extern int sList_insert_last(const sList_t list, void* data);

/* ================================ */

/**
 * \brief Inserts a new node with the given data at the beginning of a specified singly-linked list.
 *
 * This function inserts a new node with the provided data at the beginning of the
 * specified singly-linked list. The newly inserted node becomes the first node in the list.
 *
 * \param[in] list A singly-linked list to insert the new node into.
 * \param[in] data A pointer to the data to be stored in the new node.
 *
 * \return 0 on success, or a non-zero value otherwise.
 */
extern int sList_remove_first(const sList_t list, void** data);

/* ================================ */

/**
 * \brief Removes the last node from a given singly-linked list and stores the data in `data`.
 * 
 * This function removes the last node from the specified singly-linked list and stores data in `data`.
 * It is the responsibility of the caller to destroy the data to prevent memory leaks.
 * 
 * \param[in] list A pointer to the singly-linked list from which the last node will be removed.
 * \param[out] data A pointer to the data to be stored from the node.
 * 
 * \return 0 on success, a non-zero value otherwise.
 * 
 * \remark The caller is responsible for destroying the data to prevent memory leaks.
 */
extern int sList_remove_last(const sList_t list, void** data);

/* ================================ */

/**
 * \brief Returns the size of a given singly-linked list.
 *
 * This function returns the size of the specified singly-linked list.
 *
 * \param[in] list A singly-linked list.
 *
 * \return The size of the list, or -1 otherwise.
 */
extern ssize_t sList_size(const sList_t list);

/* ================================ */

/**
 * \brief Outputs the content of a given singly-linked list.
 *
 * This function traverses the specified singly-linked list and calls the provided `print` function
 * for every node in the list. The `print` function is responsible for outputting the content of each node.
 *
 * \param[in] list A singly-linked list to be printed.
 * \param[in] d A delimiter to be used when printing the nodes. Defaults to ` -> ` if `NULL` is specified.
 * 
 * \return 0 on success, or a non-zero value otherwise.
 */
extern int sList_printTo(const sList_t list, const char* delimiter, FILE* file);

/* ================================ */


/**
 * \brief Inserts a new node with the given data at the beginning of a specified singly-linked list.
 *
 * This function inserts a new node with the provided data at the beginning of the
 * specified singly-linked list. The newly inserted node becomes the first node in the list.
 * It returns 0 on success or an error code if the insertion fails.
 *
 * \param[in] list A singly-linked list to insert the new node into.
 * \param[in] data A pointer to the data to be stored in the new node.
 *
 * \return 0 on success, or a non-zero value otherwise.
 */
extern int sList_insert_first(const sList_t list, void* data);

/* ================================ */

/**
 * \brief The function removes all the nodes from the list
 * 
 * \param[in] list to clear
 * 
 * \return 0 on success, or a non-zero value otherwise.
*/
extern int sList_clear(const sList_t list);

/* ================================ */

/**
 * \brief Searches for a node with the given data in the provided singly-linked list.
 *
 * This function searches for a node with the given data in the specified singly-linked list.
 * It utilizes a `match` method provided in the `sList_new` function to determine if a node matches the given data.
 *
 * \param[in] list A singly-linked list to be searched.
 * \param[in] data A pointer to the data to be searched for.
 * \param[out] node A pointer to a `sNode_t` type to store the found node.
 *
 * \return 0 on success, non-zero value otherwise.
 */
extern int sList_find(const sList_t list, void* data, sNode_t* node);

/* ================================ */

/**
 * \brief Inserts data after the specified node in the given singly-linked list.
 *
 * This function inserts data after the specified node in the provided singly-linked list.
 *
 * \param[in] list A pointer to the singly-linked list in which the data will be inserted.
 * \param[in] node The node after which the data will be inserted.
 * \param[in] data A pointer to the data to be inserted.
 *
 * \return 0 on success, a non-zero value otherwise.
 */
extern int sList_insert_after(const sList_t list, const sNode_t node, void* data);

/* ================================ */

/**
 * \brief Inserts data before the specified node in the given singly-linked list.
 *
 * This function inserts data before the specified node in the provided singly-linked list.
 *
 * \param[in] list A singly-linked list in which the data will be inserted.
 * \param[in] node The node before which the data will be inserted.
 * \param[in] data A pointer to the data to be inserted.
 *
 * \return 0 on success, a non-zero value otherwise.
 */
extern int sList_insert_before(const sList_t list, const sNode_t node, void* data);

/* ================================ */

/**
 * \brief Deletes a node from the provided singly-linked list and stores the data stored in `data`.
 *
 * This function deletes a node from the specified singly-linked list and puts the data stored in `data`.
 * It is the responsibility of the caller to free the data to prevent memory leaks.
 *
 * \param[in] list A singly-linked list from which the node will be deleted.
 * \param[in] node A node to be deleted.
 * \param[out] data A pointer that stores data from the node.
 *
 * \return 0 on success, a non-zero value otherwise.
 */
extern int sList_delete_Node(const sList_t list, sNode_t node, void** data);

/* ================================ */

/**
 * \brief Traverses the given singly-linked list and applies a specified function to every node's data.
 *
 * This function traverses the specified singly-linked list and applies the provided function to the data of each node.
 * The function should be defined by the caller and takes the data of each node as an argument.
 *
 * \param[in] list A singly-linked list to be traversed.
 * \param[in] func A function pointer to the function to be applied to each node's data.
 *
 * \return Upon successful execution, the function returns the total number of nodes to which it has been applied; a negative value otherwise.
 */
extern int sList_foreach(const sList_t list, int (*func)(void* data));

/* ================================ */

/**
 * \brief This iterator, when called, returns the data of the next node.
 * 
 * This iterator, when called, returns the data of the next node.
 * Upon the initial call, the function necessitates a list for tracking.
 * The function remembers the last list it was called with, and subsequent calls can omit the list by specifying `NULL`.
 * it will reset its configuration and begin iterating from the start of the list.
 * 
 * \param[in] list list to iterate over.
 * \param[out] data A pointer that stores data in the next list node.
 * 
 * \return 0 on success, a non-zero value otherwise.
 */
extern int sList_next(const sList_t list, void** data);

/* ================================ */

/**
 * \brief The function retrieves the list head node
 * 
 * \param[in] list list to retrieve a head node from
 * \param[out] node node to store the list head
 * 
 * \return 0 on success, a non-zero value otherwise.
*/
extern int sList_head(const sList_t list, sNode_t* node);

/* ================================ */

/**
 * \brief The function retrieves the list tail node
 * 
 * \param[in] list list to retrieve a tail node from
 * \param[out] node node to store the list tail
 * 
 * \return 0 on success, a non-zero value otherwise.
*/
extern int sList_tail(const sList_t list, sNode_t* node);

/* ================================ */

/**
 * \brief The function gets data stored in the given `node` and places it in the `data`
 * 
 * \param[in] node node to retrieve data from
 * \param[out] data data destination
 * 
 * \return 0 on success, a non-zero value otherwise.
*/
extern int sNode_data(const sNode_t node, void** data);

/* ================================================================ */

#endif /* singly_list_h */
