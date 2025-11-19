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
