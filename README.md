# Disk Scheduling Algorithms

_A C program that implements FCFS, SSTF, SCAN, C-SCAN, LOOK, C-LOOK scheduling algorithms._

- Category: C, Operating System

- Keyword: 
  - OS
  - Disk scheduling algorithms

- Date: April, 2022

## Table of Contents

- [Disk Scheduling Algorithms](#disk-scheduling-algorithms)
  * [Table of Contents](#table-of-contents)
  * [Description](#description)
    + [Features](#features)

## Description

The program will service a disk with 300 cylinders numbered 0 to 299. The program will service the requests (a list of 20 cylinder numbers) given in the file `request.bin`. This file contains (4 byte) integer values
representing requests ranging from 0 − 299. The program will take the initial position of the disk head as the first command line argument and the direction of the head as the second command line argument. It will then output the requests in the order in which they are serviced, and the total
amount of head movements required by each algorithm.

### Features

1. The program should take two command line arguments

   - First command line argument - initial position of the disk head (an integer value)

   - Second command line argument - direction of the head (LEFT or RIGHT)

2. Read the requests from the binary file (`requests.bin`), and store these requests in an integer array (for example: requests), after which you need to close the file.

3. The program should output the following:

   - Requests in the order in which they are serviced by each algorithm.

   - Total amount of head movement incurred by each algorithm while servicing all the requests.


