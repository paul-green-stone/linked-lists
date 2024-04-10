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
