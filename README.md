# Linked Lists 🚋-🚋-🚋

A collection of linked list data types

# Singly-linked list 🚋-🚋

A singly-linked list. The simplest linked list, in which elements are linked by a single pointer. This structure allows the list to be traversed from its first element to its last.

## ✏️ Description

The linked list data structure is designed as a pointer to an incomplete type, which prevents direct modification of it and its elements, such as `list->head = node`. Users can only access and modify the list through a specified interface, ensuring controlled and secure manipulation of the list content.

## 🛠️ Usage

### Initialization

Before creating a list, it's important to determine the type of data the list will hold. Depending on whether the list contains statically or dynamically allocated data, or any other complex user data, the appropriate destruction or cleanup mechanism should be employed.

#### 1️⃣ Static Data

If the list contains statically allocated data, the list should not attempt to destroy it when the list itself is being destroyed:

```C
/* ... */
 
int array[] = {0, 2, 4, 6, 8}; // Array of statically allocated integers

sList_t list = NULL;
int result = sList_new(&list, NULL, how_to_print, how_to_compare);

if (result == 0) {
  for (size_t i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
    /*
      Even though we store statically-allocated integer variables in the list,
      what we actually hold are their memory addresses. Consequently,
      this allows users to alter the value of these integers
      by directly modifying them through their corresponding array indices
    */
    sList_insert_first(list, &array[i]);
  }

  /* ... */
}

sList_destroy(&list); // It's save to call it on NULL

/* ... */
```

#### 2️⃣ Dynamically Allocated Data

For dynamically allocated data, users should free the memory by calling `free` when removing elements from the list to prevent memory leaks:

```C
/* ... */

size_t size = 5;

sList_t list = NULL;
int result = sList_new(&list, free, how_to_print, how_to_compare);

if (result == 0) {
  for (size_t i = 0; i < size; i++) {
    int* value = NULL;

    if (value = malloc(sizeof(int)) != NULL) {
      *value = i * i;

      /*
        There exists no legal method to modify data residing in the list's nodes
        externally beyond its defined interface because the data is located in the
        heap space, and one must possess a valid pointer to gain access to it.
        Owing to encapsulation principles, although we may state that the list holds
        data internally, all intricate implementation aspects remain concealed from
        our view as external consumers.
      */
      sList_insert_first(list, value);
    }
  }

  /* ... */
}

sList_destroy(&list);

/* ... */
```

#### 3️⃣ Complex User Data

In the case of complex user data, a user-defined function should be called to handle data deletions properly, ensuring that any associated resources are released in a controlled manner:

```C
typedef struct person {

    char* first_name;
    char* last_name;

    unsigned int age;
} Person;

void Person_destroy(void* data) {

    Person* person = (Person*) data;

    if (person == NULL) {
        return ;
    }

    free(person->first_name);
    free(person->last_name);

    free(person);

    person = NULL;
}

void Person_print(void* data, FILE* f) {

    /* Assume data is never NULL, just for the sake of simplicity */
    Person* p = (Person*) data;

    fprintf(f, "%s %s - %u", p->first_name, p->last_name, p->age);
}

/* ... */

sList_t list = NULL;
int result = sList_new(&list, Person_destroy, Person_print, Person_match);

// Adding individuals to the list
if (result == 0) {

    for (size_t i = 0; i < 10; i++) {
            /* See `examples` for more details */ 
            sList_insert_last(list, Person_new());
    }
}

sList_destroy(&list);

/* ... */
```


### Insertion

Data can be inserted in the list in four distinct ways:

#### 1️⃣ `sList_insert_last`

```C
/* ... */

/* The same hypothetical function for individual creation */
sList_insert_last(list, Person_new()); // Insert data at the end of the list

/* ... */
```

Time complexity of the function is $O(1)$

#### 2️⃣ `sList_insert_first`

```C
/* ... */

  sList_insert_first(list, Person_new()); // Insert data at the beginning of the list

/* ... */
```

Time complexity of the function is $O(1)$

#### 3️⃣ `sList_insert_after`

The `sList_insert_after` function is used to insert a new node with specified data after a given node. The function takes a node as an indicator, specifying the node after which the new node should be inserted. 

```C
/* ... */

int Person_match(void* data1, void* data2) {

    Person* person1 = (Person*) data1;
    Person* person2 = (Person*) data2;
    
    /*
      The function should return 0 when two pieces of data are equal. `strcmp` returns 0 on success,
      and when we combine its result with another successfull `strcmp` call, the 1 will be returned.
      By definition we need 0, so we negate the result to tell pieces of data are equal.
    */
    return !((strcmp(person1->first_name, person2->first_name) == 0) && (strcmp(person1->last_name, person2->last_name) == 0) && !(person1->age == person2->age));
}

/* ... */

sList_t list = NULL;
int result = sList_new(&list, Person_destroy, how_to_print, Person_compare);

/* Let's say the person is John Doe */
Person* john = Person_new();

/* First traversion happens here */
sNode_t node = NULL;
result = sList_find(list, &john, &node);

if (result == 0) { 
   /* If the node is in the list, the operation is constant */
   result = sList_insert_after(list, node, Person_new());
}

/* ... */
```

Every node contains a reference to the list it belongs to, making insertion after the node (`sList_insert_after`) a constant operation. However, searching for a node with specified data still requires traversal.

#### ⚠️ Warning!

It is important to note that even if two linked lists contain nodes with the same data, the nodes themselves belong to different lists. This means that calling the `sList_find` function on one list and obtaining a node with the given data does not guarantee that data can be inserted into another list using the `sList_insert_after` function. The node must belong to the same list in order for data to be properly inserted.

#### 4️⃣ `sList_insert_before`

The `sList_insert_before` function is almost identical to the `sList_insert_after` function, with the only difference being that the data is inserted before the given node. The same rules and considerations apply to the `sList_insert_before` function as they do to the `sList_insert_after` function, except it traverses the list in order to find a proper position to insert a node.

### 🖼️ Printing

The function `sList_printTo` is used to output the content of a given list to the given stream. This function requires the user to provide a function that handles the data stored in each node of the list.

```C
void Person_print(void* data, FILE* f) {

    /* Assume data is never NULL, just for the sake of simplicity */
    Person* p = (Person*) data;

    fprintf(f, "%s %s - %u", p->first_name, p->last_name, p->age);
}

/* ... */

sList_t list = NULL;
int result = sList_new(&list, Person_destroy, Person_print, Person_compare);

sList_printTo(list, "\n", stdout);
```

### ⛏️ Data Extraction

#### 1️⃣ `sList_next`

According to the implementation, a list is a pointer to an incomplete type, which means one cannot directly access its members or its node data. In other words, there is no way to manually set a list size, access the list head element, or retrieve node data manually. However, there are situations where it is necessary to retrieve data stored in the list's nodes for processing. This can be achieved using the `sList_next` function, which, upon invocation, gets the data stored in the next list node. Consider an example:

```C
/* ... */

/* Imagine the list contains some people */

size_t size = sList_size(list);

for (size_t i = 0; i < size; i++) {

   void* data = NULL;
   Person* person = NULL;

   /* Get data from the next node and store it in `data` */
   sList_next(list, &data);

   person = (Person*) data;

   /* Manually changing a book's title */
   free(person->first_name);
   person->first_name = strdup("Mr. Cool Name");
}
```

Notice that the `sList_next` function stores data in the generic `void*` pointer. You must cast this pointer according to whatever your list contains. While working with data in the list, the list itself remains untouched; its internal details are protected/hidden and can be modified only via methods defined here.

#### 2️⃣ `sList_foreach`

Another way to modify the content of a list is to apply a specific function to each data element stored in the list's nodes. This can be achieved by invoking the `sList_foreach` function, which takes the list and a pointer to the function you want to apply. The function you want to apply must return 0 on success. `sList_foreach` will return the count of nodes that were impacted by the specified function, specifically those for which the function returned 0. 

```C

/* ... */

int double_odds(void* data) {

    int* node_data = (int*) data;

    if (*node_data % 2) {
        *node_data *= 2;

        return 0;
    }

    return -1;
}

int nodes = sList_foreach(list, double_odds);

printf("Number of nodes that were impacted: %d\n", nodes);

/* ... */

```

### 🏥 Error Handling

There are times when a function fails, and one needs to find out what exactly happened. For such cases, there is a function named `sList_error` that takes a value returned from one of the functions in the `sList_` family and returns a string describing the error.

```C
/* ... */

int* a = NULL;

/* Let's say you want to store an integer value in the list but forgot to allocate memory for it */
int result = sList_insert_last(&list, a);

if (result != 0) {

   printf("Error has occurred: %s\n", sList_error(result));
}
```