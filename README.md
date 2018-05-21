# MPI
This program creates three processes using MPI to do the following:

1. All processes create two random integer in the range 51 to 100 for variables: na, and nb.

2. The processes with the rank one creates an array: a of type integer with the size: na. This process fills array: a with random integers in the range 0 to 99. This process sorts the array and prints it. This process sends array: a to the process with the rank: 0.

3. The processes with the rank two creates an array: a of type integer with the size: nb. This process fills array: b with random integers in the range 0 to 99. This process sorts the array and prints it. This process sends array: b to the process with the rank: 0.

4. The process with the rank zero creates an array: a of type integer with the size: na, creates an array: b of type integer with the size: nb, and creates an array: c of type integer with the size: na+nb. This process receives a sorted array from process with the rank 1 into its array: a. This process receives a sorted array from process with the rank 2 into its array: b. This process merges arrays: a, and b into arrays c. This process prints array: c. 
