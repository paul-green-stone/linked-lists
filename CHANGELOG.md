# Changelog

All notable changes will be documented in this file.

## [Unreleased 0.1.0] 2024-04-10

### Added

- Implemented `Node_new` and `Node_destroy` (*static*) functions for handling node creation and deletion
- Implemented a `sList_new` function for creating a new singly linked list
- Implemented a `sList_destroy` function for destroying a singly linked list
- Implemented a `sList_insert_last` function that inserts data in the end of the list
- Implemented a `sList_remove_first` function for deleting the first element from the list
- Implemented a `sList_size` function that returns a list size (number of elements in the list)

- Added a test for `sList_new`, `sList_destroy`, `sList_insert_last`, `sList_size` functions.

## [Unreleased 0.2.0] 2024-04-11

### Added

- Implemented a `sList_printTo` function for displaying a list content. A user can specify a stream to output

- Added a test for the `sList_printTo` function

### Changed

Updated test suites to handle different list operations

- Added a separate test case for creating a new list and adding data to it (one case, two operations)
- Implemented a test case for verifying the output of list operations
- Added a separate test case for destroying a list

## [Unreleased 0.3.0] 2024-04-13

### Added

- Implemented a `sList_clear` function that clears the list, i.e., deletes all its elements
- Implemented a `sList_insert_first` function that inserts data at the beginning of the list
- Added a macro `sList_print` that invokes `sList_printTo` with `stdout` by default

- Added a test for the `sList_clear` function
- Added a test for the `sList_insert_first` function, which includes both data insertion and validation of the expected output

- Added a mechanism for files deletion after they have been populated with list data and read into a buffer

### Fixed

- Fixed a bug that caused the test for the `sList_printTo` function to fail due to incorrect handling of the last element addition after reading from a file
- 
## [Unreleased 0.3.1] 2024-04-19

### Fixed

- Implemented separate test cases for different operations, organizing them into individual directories. Enhanced test suite structure for better readability and management

## [Unreleased 0.4.0] 2024-04-20

### Added

- Implemented an `sList_find` function that looks for a node with the given data in the given list

- Added a test for `sList_remove_last` function
- Added a test for `sList_insert_last` function
- Added a test for `sList_remove_last` function
- Added a test for `sList_find` function

## [Unreleased 0.5.0] 2024-04-29

### Added

- Implemented a `sList_insert_after` function that inserts a new node with the given data after a specified node
- Implemented a `sList_insert_before` function that inserts a new node with the given data before a specified node
- Implemented a `sList_delete_node` function that removes a node from a list
- Implemented a `sList_foreach` function that applies a given function to every node in the list
- Implemented a `sList_next` function that retrieves the next node's data
- Implemented a `sList_head` function that retrieves the list head
- Implemented a `sList_tail` function that retrieves the list tail
- Implemented a `sNode_data` function that retrieves the node's data

- Added documentation to list API
- Added tests for all the funtions added in version `0.5.0`.

### Fixed

- The `sList_find` function now checks for the presence of the "match" method
- The `sList_foreach` function returns a negative value on failure to avoid confusing the user. A positive return value indicates the number of nodes to which the provided function has been applied

## [Release 1.0.0] 2024-05-07

### Added

- Implemented a `sList_error` function that returns a string describing the error
- Added a simple showcase for how to use a linked list data structure

## [Release 2.0.0] 2024-05-17

### Added

- A complete redesign of `sList_next` function
- A list now maintains a pointer to the node whose data will be returned upon invoking `sList_next`
- Added a `sList_reset` function that sets the current position back to the first node in the list
- `sList_find` now returns `NOT_FOUND` if the given data is not in the list

- Updated `README`
- 