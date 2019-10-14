# Linear-Hashing-Database
Implementation of the paper [Linear Hashing: A New Tool For File And Table Addressing' to handle duplicate elimination](http://infolab.cs.unipi.gr/pre-eclass/courses/db/db-post/readings/Litwin-VLDB80.pdf)

Linear hashing (LH) is a dynamic data structure which implements a hash table and grows or shrinks one bucket at a time. It is the first in a number of schemes known as dynamic hashing such as Larson's Linear Hashing with Partial Extensions, Linear Hashing with Priority Splitting, Linear Hashing with Partial Expansions and Priority Splitting, or Recursive Linear Hashing. 

To run:

##### Compile:

g++ -std=c++11 lnrHsh.cpp

##### Run: 

./a.out inputFile number_of_buffers buffer_size
  
where number of buffers is >= 2.

Eg: ./a.out input.txt 4 16 > result.txt

##### Verify:

diff result.txt output.txt
