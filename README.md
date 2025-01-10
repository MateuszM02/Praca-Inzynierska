# Praca-Inzynierska
Here is my Engineering thesis on Boost vs STL libraries comparison in C++
The project is split into 2 folders:
1. src is for all methods that are compared using Boost, STL and own implementation,
2. tests is for tests which measure methods execution time on multiple examples.
   
Each of those folders will have 10 subfolders, with each subfolder defining different method.
Each method will be tested on 3-5 different classes defined in that subfolder.

The methods will be:
1. MinMax - finds pair minimum and maximum value in Container.
2. Accumulate - calculates result of operation (default is sum) applied to all elements.
3. Merge - merges 2 sorted data structures into one sorted structure.
4. Sorting - unstable sort of data structure.
5. Transform - transform one collection into another (like std::set<std::pair<int, int>> into std::vector<Point2D>)
6. Adjacent filter - return structure of initial elements where each adjacent pair meets certain condition
7. N-th element - moves n-th smallest element to n-th position in data structure. All elements before it are smaller and all after are bigger. Doesn't sort or keep order of those 2 subgroups.
8. Regex - returns vector of all substrings matching pattern.
9. Remove Erase if - removes all elements matching predicate from given data structure.
10. Generate - fills data structure with successive results of calls to the operator()().

In the future this repository will also have document describing results of tests done for each method.
