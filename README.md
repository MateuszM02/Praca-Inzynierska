# Praca-Inzynierska
Here is my Engineering thesis on Boost vs STL libraries comparison in C++
The project is split into 2 folders:
1. src is for all methods that are compared using Boost, STL and own implementation,
2. tests is for tests which measure methods execution time on multiple examples.
   
Each of those folders will have 10 subfolders, with each subfolder defining different method.
Each method will be tested on 3-5 different classes defined in that subfolder.

The methods will be:
1. Random shuffle - shuffles given data structure in pseudorandom order using pseudorandom generator.
2. Partition - unstably moves elements matching predicate before elements which don't.
3. Merge - merges 2 sorted data structures into one sorted structure.
4. Binary search - looks for element in structure and returns true only if it is present, otherwise returns false.
5. Sorting - unstable sort of data structure.
6. Partial sort - unstable sort of first k elements that leave rest of elements in unspecified order.
7. N-th element - moves n-th smallest element to n-th position in data structure. All elements before it are smaller and all after are bigger. Doesn't sort or keep order of those 2 subgroups.
8. Copy if - copies all elements matching predicate to new data structure.
9. Remove if - removes all elements matching predicate from given data structure.
10. Generate - fills data structure with successive results of calls to the operator()().

In the future this repository will also have document describing results of tests done for each method.
