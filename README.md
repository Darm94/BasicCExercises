# C Programming Exercises — Strings & Arguments

A small collection of C programming exercises designed to strengthen understanding of **pointers**, **string operations**, and **command-line arguments**.  
These exercises reimplement core C standard library functions and demonstrate how to manipulate strings manually using **pointer arithmetic**.

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
