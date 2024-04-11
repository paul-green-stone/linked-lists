# Changelog

All notable changes will be documented in this file.

## [Unreleased 0.1.0] 2024-04-10

### Added

- Implemented `Node_new` and `Node_destroy` (*static*) functions for handling node creation and deletion
- Implemented a `sList_new` function for creating a new singly linked list
- Implemented a `sList_destroy` function for destroying a singly linked list
- Implemented a `sList_insert_last` function that insert data in the end of the list
- Implemented a `sList_remove_first` function for deleting the first element from the list
- Implemented a `sList_size` function that returns a list size (number of elements in the list)

- Added a test for `sList_new`, `sList_destroy`, `sList_insert_last`, `sList_size` functions.

## [Unreleased 0.2.0] 2024-04-11

### Added

- Implemented a `sList_printTo` function for displaying a list content. A user can specify a stream to output

- Added a test for `sList_printTo` function

### Changed

Updated test suites to handle different list operations

- Added a separate test case for creating a new list and adding data to it (one case, two operations)
- Implemented a test case for verifying the output of list operations
- Added a separate test case for destroying a list
