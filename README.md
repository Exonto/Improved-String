This open source project was built by Tyler J. Syme
Contact me at "tylersyme@gmail.com" if you have any questions regarding this project
--------------------------------------------------------------------------------------------

This is (what I consider to be) a more powerful version of the C++ std::string.
I built this with the intention of using it in college with the goal of speeding up basic 
string operations which would otherwise, needlessly use up my time. 
I have run this code through valgrind (http://valgrind.org/) and have confirmed that no
memory leaks exist within the code.

This class itself includes many of the useful operations I was missing, such as:
* Uppercasing and lowercasing Strings
* Finding the first/all indexes of a substring
* Removing characters or whole substrings
* Replacing characters or whole substrings
* Inserting Strings
* Splitting Strings
* Trimming Strings of unwanted whitespace
* Comparing two Strings while ignoring letter case
* Appending ints, doubles, floats etc. onto Strings using the '+' or '+=' operator

Also includes expected overloaded operators and output/input stream compatability.

It is also largely immutable except in the case of the '+=' or '=' operator which will 
change the object. All other methods create new String objects rather than changing the 
original.

Warning: While the code has been tested, it has not been peer reviewed and should not be
used for any serious project outside of academia. Please report any bugs via my email shown
above. Thank you.
