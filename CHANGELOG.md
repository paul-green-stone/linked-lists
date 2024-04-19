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

- Implemented separate test cases for different operations, organizing them into individual directories. Enhanced test suite structure for better readability and management.

## [Unreleased 0.4.0] 2024-04-20

### Added

- Implemented an `sList_find` function that looks for a node with the given data in the given list

- Added a test for `sList_remove_last` function
- Added a test for `sList_insert_last` function
- Added a test for `sList_remove_last` function
- Added a test for `sList_find` function
