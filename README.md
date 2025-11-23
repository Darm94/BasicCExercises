# C Programming Exercises — Strings & Arguments

A small collection of C programming exercises designed to strengthen understanding of **pointers**, **string operations**, and **command-line arguments**.  
These exercises reimplement core C standard library functions and demonstrate how to manipulate strings manually using **pointer arithmetic**.
[UPDATE excercise 3 added]
>the third excercise is based on C memory management, string operations, and dynamic data structures.

---

##  Overview

This repository contains two main exercises:

### (1) Print Command-Line Arguments
A simple program that prints all arguments passed to `main()` using `argc` and `argv`.
This helped to understand how arguments are handled in C programs and the structure of the `argv` array and the role of `argc`.

**Example:**
```bash
$ ./args_example Hello world 123
Argument 0: ./args_example
Argument 1: Hello
Argument 2: world
Argument 3: 123
```

### (2) Strings Functions
This exercise constist to reimplements standard C string functions to try to think about and understand how they work internally.

**Implemented functions**

- **`mystrcpy()`** and **`mystrcpy2()`** → copy strings manually using pointer arithmetic  (and is Cleanest version that i tryed after)
- **`mystrcat()`** and **`mystrcat2()`** → concatenate two strings  (and is Cleanest version that i tryed after)
- **`mystrlen()`** → calculate string length  
- **`mystrcmp()`** → compare two strings using ASCII scale  (here i implemented directly the cleanest version i was able to write)

I wrote using function that mimics the behavior of its standard library counterpart (`strcpy`, `strcat`, `strlen`, `strcmp`),  
but operates using explicit pointer logic (`*ptr`) instead of array indexing and sometime pointer increase annotation (`ptr++`) .

**Output of the example written in the main:**

```--CONCAT
Hello: Part 2
--COMPARE
String 1 equals String 3
String 1 not equal to String 4
--STRING LENGTH
Length of string_1: 5
Length of string_5: 7
=================================
Now My Functions: 

--CONCAT
Hello: Part 2
--CONCAT SHORTER FUN
Hello: Part 2
--COMPARE
String 1 equals String 3
String 1 not equal to String 4
--STRING LENGTH
Length of string_1: 5
Length of string_5: 7
   --BYE TO THE NEXT EXERCISE!---
```
## (3) Memory Functions & Dynamic Matrices

This exercise focuses on **dynamic memory allocation in C** and on the use of standard functions such as `malloc`, `calloc`, `realloc`, and `free`.  
The goal was to understand how memory is managed and to reimplement some of these functions manually, to see what they really do behind the scenes.

### Implemented Custom Functions

- **`my_memset()`** → manual implementation of `memset`, sets each byte to a specific value  
- **`my_memcpy()`** → manual implementation of `memcpy`, copies bytes from one block to another  
- **`my_calloc()`** → manual implementation of `calloc`, allocates and initializes to zero  
- **`my_realloc()`** → simplified version of `realloc`, allocates a new block, copies old data, and frees the old memory

These were tested against their standard counterparts to understand their behavior with different data types (especially the effect of `memset` on `int` arrays when the value is greater than 0).

---

### Dynamic Matrices Implementations

In the last part, two different implementations of a **matrix structure** are compared.

#### (a) Single Pointer Matrix (`int*`)
In this approach, the matrix is stored in a **contiguous block of memory** using a single pointer.  
All elements are placed sequentially in memory, and the index of a cell `[r][c]`

```
index = (r * columns) + c;
```

I was ispired on this approach by the pyxel access logic we studied during first 2D lessons in C#


**Pros**
- Continuos memory in the heap → faster access if cached(?)
- Simple to allocate and free in just one block (only one `malloc` and one `free`)

**Cons**
- Harder to handle as a "matrix of rows" (you need manual index calculations)

#### (b) Double Pointer Matrix (`int**`)
Here, the matrix is an **array of pointers**, where each pointer represents a row.  
Each row is allocated separately, resulting in a structure like this:

```
matrix.data -> [ * * * * *... ] // n_rows pointers every element is a pointer (*)
each element -> malloc(m_columns * sizeof(int))
```
Thats the more typical approach for matrix in C (according to university courses)

**Pros**
- Each row can have a different length (flexible structure)
- Access syntax like `matrix.data[row][col]` is very natural

**Cons**
- Multiple allocations → can be more slower and exposed to memory overhead
- int he heap the allocations are not contiguos so also the Rows are not contiguous → can be less efficient

---

### Example Output
================ MALLOC dyn. array of size 3: ================


num[0] = 1

num[1] = 0

num[2] = 0


================ MY_MEMSET (setting each byte to 100) ================

num[0] = 1684300900

num[1] = 1684300900

num[2] = 1684300900


================ Dynamic Matrix with Struct and Functions ================

[1][1][1][1]

[1][1][1][1]

...


================ Dynamic Matrix using Pointer-to-Pointer Strategy ================

[0][0][0][0]

[0][0][0][0]

[0][0][0][0]


#### (c) Conclusions
In my opinion both of these approaches are convenient depending on the situation, although approach (b) is more flexible and easier to handle with array-like access (matrix[0][5]) causing much less confusion. For both of them I decided to rely on a struct which in my opinion is the best way to manage the data related to the matrix without going crazy.

---

### Matrix Functions Overview

The matrix management logic has been organized into specific helper functions declared in `matrix_functions.h` and implemented in `matrix_functions.c`.  
These functions make it easier to create, initialize, modify, print, and free both types of dynamic matrices.

#### **Functions for `int_matrix` (single-pointer version)**

| Function | Description |
|-----------|-------------|
| **`create_int_matrix(int n_rows, int m_columns)`** | Allocates a contiguous block of memory for `n_rows * m_columns` integers and initializes the structure fields. |
| **`int_matrix_get_pointer()`** | Returns a pointer to a specific element in the matrix (calculated using row and column indices). |
| **`int_matrix_get_value()`** | Returns the value stored in the matrix at a given row and column position. |
| **`int_matrix_get_size()`** | Returns the total number of elements (rows × columns). |
| **`initiate_int_matrix()`** | Initializes all matrix elements with a specific value. |
| **`int_matrix_set()`** | Sets a specific cell to a new value. |
| **`int_matrix_print()`** | Prints all elements of the matrix in a readable grid format. |

---

#### **Functions for `int_matrix_array` (double-pointer version)**

| Function | Description |
|-----------|-------------|
| **`create_int_matrix_array(int n_rows, int m_columns)`** | Dynamically allocates a 2D matrix using an array of row pointers. Each row is allocated separately and initialized to 0. |
| **`int_matrix_array_print()`** | Prints the matrix in a multi-line format (each row on a new line). |
| **`destroy_int_matrix_array()`** | Frees all allocated memory correctly — first every row, then the array of row pointers. Prevents memory leaks. |

---

Main differences:
In create_int_matrix_array i decide to put the initialization inside  instead to do it in a separate function, just to try a different approach.
For int_matrix_matrix i thought that were usless the access function like get gets and set function cause using the "array notation"(matrix[0][3]) we can do it way better faster.
Instead for int_matrix i needed a function to do a clean and complete heap liberation cause for Int_matrix_array it needed to free every pointer in the pointer array.


### Example Usage

```c
int_matrix matrix = create_int_matrix(5, 4);
initiate_int_matrix(matrix, 1);
int_matrix_set(matrix, 0, 3, 2);
int_matrix_print(matrix);

int_matrix_array matrix_array = create_int_matrix_array(5, 4);
matrix_array.data[0][3] = 2;
matrix_array.data[1][2] = 9;
int_matrix_array_print(matrix_array);

destroy_int_matrix_array(matrix_array);
```

## (4) Generic Containers — Vector, List, Dictionary (Hash Map)

This exercise implements three **generic data structures in C** using `void*`:
- **`aiv_vector`** – dynamic array with index access, push, set/delete, and multiple sorting algorithms via user-provided comparator.
- **`aiv_list`** – **doubly linked list** with O(1) tail append, get/set/remove by index, and a simple debug printer.
- **`aiv_dict`** – **hash map** with separate chaining (linked lists in buckets), supporting put/get/contains/remove and a debug printer for integer keys/values.

All containers are **generic**: they store pointers to user-managed data (`void*`). Comparisons and value interpretation are delegated to the caller (via comparator functions or explicit casts).

---

### Files
- `main.c` — showcases the three structures with small demos (push/print/sort/remove/lookup).
- `aiv_vector.h/.c` — vector and sorting algorithms (bubble variants + quicksort).
- `aiv_list.h/.c` — doubly linked list core ops and utilities.
- `aiv_dict.h/.c` — hash map with configurable hash function (default DJB variant).

---

### API Overview

#### Vector (`aiv_vector`)
```c
aiv_vector_t aiv_vector_new();                        // items=NULL, count=0, capacity=10 (initial hint)
void           aiv_vector_destroy(aiv_vector_t* v);   // frees internal array, resets fields
void           aiv_vector_add(aiv_vector_t* v, void* item);     // append (current impl uses realloc each time)
void*          aiv_vector_at(aiv_vector_t* v, size_t index);    // NULL if out-of-bounds
void           aiv_vector_set(aiv_vector_t* v, size_t index, void* item);
void           aiv_vector_delete(aiv_vector_t* v, size_t index); // shift left + shrink via realloc

// Sorting (require int (*cmp)(void*,void*), returning <0 / 0 / >0):
void aiv_vector_sort_bubble(aiv_vector_t* v, int (*cmp)(void*,void*));
void aiv_vector_sort_bubble2(aiv_vector_t* v, int (*cmp)(void*,void*)); // early-exit
void my_aiv_vector_sort_bubble(aiv_vector_t* v, int (*cmp)(void*,void*)); // personal variant
void aiv_vector_sort_quick(aiv_vector_t* v, int (*cmp)(void*,void*));     // average O(n log n)

// Debug helper for int* vectors:
void aiv_vector_print_int(aiv_vector_t* v);
```
Complexity (typical): access O(1); append amortized O(1) (see “Improvements”); delete O(n); bubble O(n²); quicksort avg O(n log n).

#### List (aiv_list)


```
aiv_list_t aiv_list_new();
void       aiv_list_destroy(aiv_list_t* list);
void       aiv_list_add(aiv_list_t* list, void* item);      // append at tail O(1)
bool       aiv_list_is_empty(aiv_list_t* list);

size_t     aiv_list_get_size(aiv_list_t* list);
void*      aiv_list_get_item_at(aiv_list_t* list, size_t index);  // O(n)
bool       aiv_list_set_item_at(aiv_list_t* list, size_t index, void* item); // O(n)
bool       aiv_list_remove_item(aiv_list_t* list, void* item); // identity-based match
bool       aiv_list_remove_item_at(aiv_list_t* list, size_t index);
void       aiv_list_print(aiv_list_t* list); // debug helper for int*
```
Complexity (typical): append O(1); indexed access/removal O(n).

#### Dictionary (aiv_dict)

```
aiv_dict_t aiv_dict_new(); // default buckets + DJB-like hash
aiv_dict_t aiv_dict_new_with_params(size_t buckets, size_t (*hash)(void*, size_t));

void   aiv_dict_put(aiv_dict_t* d, void* key, size_t key_size, void* value);
// NOTE: key is copied (size = key_size). Value pointer is stored as-is (no deep copy).

void*  aiv_dict_get(aiv_dict_t* d, void* key, size_t key_size);
bool   aiv_dict_contains_key(aiv_dict_t* d, void* key, size_t key_size);
bool   aiv_dict_remove(aiv_dict_t* d, void* key, size_t key_size);

size_t aiv_dict_get_size(aiv_dict_t* d);                      // number of stored pairs
size_t aiv_dict_get_hashmap_elements_size(aiv_dict_t* d);     // bucket count
void   aiv_dict_destroy(aiv_dict_t* d);                       // frees keys + nodes, not user values

// Debug printer for integer keys/values:
void   aiv_dict_debug_print_ints(aiv_dict_t* d);
```
Notes: collisions handled with linked lists per bucket; key comparison = key_size + memcmp.

### Demos (excerpt from main.c)

#### Vector
```
int array[5] = {3, 5, 2, 1, 4};
aiv_vector_t v = aiv_vector_new();
for (int i = 0; i < 5; ++i) aiv_vector_add(&v, &array[i]);

puts("=== BUBBLE SORT 2 ===");
aiv_vector_print_int(&v);
puts("=== NOW order ===");
aiv_vector_sort_bubble2(&v, compare_int);
aiv_vector_print_int(&v);

puts("=== Deletion (index 4 and 3) ===");
aiv_vector_delete(&v, 4);
aiv_vector_delete(&v, 3);
aiv_vector_print_int(&v);
aiv_vector_destroy(&v);
```
#### List
```
aiv_list_t list = aiv_list_new();
int a = 10, b = 20, c = 30;
aiv_list_add(&list, &a);
aiv_list_add(&list, &b);
aiv_list_add(&list, &c);

printf("Head: %d | Tail: %d\n", *(int*)list.head->data, *(int*)list.tail->data);
printf("Size: %llu\n", aiv_list_get_size(&list));

int nv = 99;
aiv_list_set_item_at(&list, 1, &nv);
aiv_list_remove_item_at(&list, 1);
aiv_list_remove_item(&list, &c);
aiv_list_destroy(&list);

```

#### Dictionary
```
// DJB-like hash already available in aiv_dict.c; you can also pass a custom one:
aiv_dict_t dict = aiv_dict_new_with_params(8, djb33x_hash);

int k1=4,v1=2, k2=8,v2=6, k3=5,v3=1, k4=6,v4=8;
aiv_dict_put(&dict, &k1, sizeof(int), &v1);
aiv_dict_put(&dict, &k2, sizeof(int), &v2);
aiv_dict_put(&dict, &k3, sizeof(int), &v3);
aiv_dict_put(&dict, &k4, sizeof(int), &v4);

printf("Hashmap buckets: %llu\n", aiv_dict_get_hashmap_elements_size(&dict));
printf("Pairs count:    %llu\n", aiv_dict_get_size(&dict));
aiv_dict_debug_print_ints(&dict);

int q = 8;
int* pv = (int*)aiv_dict_get(&dict, &q, sizeof(int));
if (pv) printf("Get(%d) = %d\n", q, *pv);

aiv_dict_remove(&dict, &k1, sizeof(int));
aiv_dict_destroy(&dict);

```
#### Sample Output (abridged)
```
=== VECTOR PART ===
vector2[0] = 3
...
=== NOW order ===
vector2[0] = 1
...
=== LIST PART ===
Head: 10 | Tail: 30
Size: 3
...
=== DICT PART ===
Hashmap buckets: 8
Pairs count:    4
[0] --> (k:...,v:...) ...
Get(8) = 6
After remove:
Pairs count:    3
```
---

### Vector — Design & Rationale

The vector stores `void*` items in a resizable array. Core goals:
- **Generic**: store any pointer type; ordering is delegated to a user comparator.
- **Simple API**: push (`add`), indexed access (`at`), bounded set (`set`), delete (shift+shrink), and sorting (bubble variants + quicksort).

#### Comparator contract
All sorting functions expect `int (*cmp)(void*, void*)` returning:
- `< 0` if `a < b`, `0` if equal, `> 0` if `a > b`.  
This keeps the vector type-agnostic and lets users define order (e.g., ints, structs, etc.).

---

### Sorting Choices

#### 1) `aiv_vector_sort_bubble2` — **Bubble Sort with early-exit**
> _“Inspired by lesson pseudo-code”_ — the classic bubble pass with a `swapped` flag.

- **Idea**: keep swapping adjacent out-of-order elements; if a full pass does no swaps, the array is sorted.
- **Why this variant**: the `while (swapped)` pattern is the cleanest way to encode the **early termination** optimization for nearly-sorted inputs.
- **Key properties**:
  - Best case (already sorted): **O(n)** (one pass, `swapped` stays 0 after first pass).
  - Average/worst case: **O(n²)**.
  - **Stable** (adjacent swaps preserve relative order of equals).
- **Where the image goes**:  
  _I will place the lesson pseudo-code image here once added:_  
  `![bubble-pseudocode](./docs/bubble_lesson_pseudocode.png)`

#### 2) `my_aiv_vector_sort_bubble` — **Bubble Sort (control-flow variant)**
> _“Inspired by lesson + forum discussions”_ — functionally similar, but the outer loop is an infinite `while(1)` broken when no swaps happen.

- **Why keep both**: they are equivalent in complexity and correctness, but show two styles:
  - **State-driven loop** (`while (swapped)`) vs **sentinel loop** (`while(1) { if(!swapped) break; }`).
  - Useful to compare readability and control-flow patterns.
- **Properties**: same as above — stable, O(n²) average/worst, O(n) best.

#### 3) `aiv_vector_sort_quick` — **Quicksort with median-ish pivot**
> _Short explain of the inner recursion (`quicksort_internal`)_

- **Partitioning**:
  - Select pivot as the **middle element**: `items[(left + right) / 2]`.  
    (A simple strategy that often avoids worst-case on already sorted inputs compared to choosing `items[left]`.)
  - Move `i` forward while `cmp(items[i], pivot) < 0`.  
    Move `j` backward while `cmp(items[j], pivot) > 0`.
  - When `i <= j`, **swap**, then increment `i` and decrement `j`.
- **Recursion split**:
  - After the partition loop finishes, the array is split into two subranges:
    - `left..j` and `i..right`.
  - Recurse on each **only if non-empty**:
    ```c
    if (left < j)  quicksort_internal(items, left, j, cmp);   // left partition
    if (i < right) quicksort_internal(items, i, right, cmp);  // right partition
    ```
- **Why this approach**:
  - **In-place** (no extra arrays), **average O(n log n)**, usually faster than bubble for non-trivial sizes.
  - **Not stable** (swaps can reorder equals), which is acceptable here.
- **Footnotes**:
  - Worst-case **O(n²)** (e.g., adversarial data), but rare in practice with a center pivot.
  - The two inner `while` loops together scan each element at most once per partition → **linear work per partition**.

---

### Update & Delete Operations

#### `aiv_vector_set`
```c
void aiv_vector_set(aiv_vector_t *vector, size_t index, void *item) {
    if (index >= vector->count) {
        // out of vector range -> Nothing to do
        return;
    }
    vector->items[index] = item;
}

#### Comparator & Hash

-Comparator must return <0 / 0 / >0 to indicate order. The examples cast void* to int*.
-Hash is configurable via aiv_dict_new_with_params; default is a DJB-style function (djb33x_hash).

