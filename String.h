
#ifndef STRING_H_
#define STRING_H_

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>

/**
 * This class stores a series of characters in order and has many methods
 * designed to make manipulation of these characters simple and easy.
 *
 * This String is immutable and is therefore inherently thread safe.
 */
class String
{

public:

// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------

	/**
	 * Creates a new String object designed to store and manipulate
	 * a series of characters.
	 *
	 * @param c_str The characters to be stored
	 */
	String(const char* c_str = '\0');

	/**
	 * This creates a new copy of the given String.
	 *
	 * @param toCopy The String to be copied
	 */
	String(const String& toCopy);

	/**
	 * Destructs the String.
	 */
	~String();

// -----------------------------------------------------------------------------
// String Information
// -----------------------------------------------------------------------------

	/**
	 * @return The total number of characters in the String.
	 */
	const unsigned int length() const;

	/**
	 * Note: The same result can be achieved using the operator[index].
	 *
	 * @param idx An integer between 0 and the length of the String
	 * @return The character at the given index location
	 */
	const char charAt(unsigned int idx) const;

	/**
	 * @param idx An integer between 0 and the length of the String
	 * @return The character at the given index location
	 */
	const char operator[](unsigned int idx) const;

	/**
	 * Returns whether the given String segment can be found in this String.<br>
	 * This includes correct capitalization.
	 *
	 * @param segment The String to be found within this String
	 * @return Whether the segment was found
	 */
	const bool contains(const String& segment) const;

	/**
	 * This first finds the given segment's location within this String and
	 * then returns the index of the first character.
	 *
	 * @param segment The first String to be found within this String
	 * @return The index location of the first matching character;
	 * 		   Will return -1 if no index was found
	 */
	const unsigned int indexOf(const String& segment) const;

	/**
	 * Return a vector containing the index locations of each occurrence of
	 * the given String.
	 *
	 * @param segment The String to be found within this String
	 * @return A vector<int> containing the indexes of the given String
	 */
	std::vector<int> indexesOf(const String& segment) const;

// -----------------------------------------------------------------------------
// String Manipulation
// -----------------------------------------------------------------------------

	/**
	 * @return Returns a copy of the String whose characters are all uppercased.
	 */
	const String toUppercase() const;

	/**
	 * @return Returns a copy of the String whose characters are all lowercased.
	 */
	const String toLowercase() const;

	/**
	 * Returns a String whose character at the given index has been removed.
	 *
	 * @param charIndex The index of the character to be removed
	 * @return The new resulting String;
	 * 		   Will return an empty String if the given index is out of bounds
	 */
	const String remove(unsigned int charIndex) const;

	/**
	 * Removes the first occurrence of the given String in this String.
	 *
	 * @param toRemove The String to be removed from this String
	 * @return A new String whose characters have been removed
	 */
	const String removeFirst(const String& toRemove) const;

	/**
	 * Removes all characters from between startIndex and endIndex.
	 *
	 * In this case, startIndex is considered "inclusive" while endIndex is
	 * considered "exclusive". By inclusive, this means that the character at
	 * startIndex will be removed. By exclusive, this means that the character
	 * is not removed at endIndex but rather at the index occurring before
	 * endIndex.
	 *
	 * As a general rule, startIndex cannot be larger than endIndex.
	 * They may, however, be equivalent in size in which the String which is
	 * returned will have no characters removed.
	 *
	 * @param startIndex The starting index
	 * @param endIndex The ending index
	 * @return A new String whose characters have been removed
	 */
	const String removeAll(size_t startIndex, size_t endIndex) const;

	/**
	 * Removes each of the given String occurrence from the String.
	 *
	 * @param toRemove The String to be removed
	 * @return A new String
	 */
	const String removeAll(const String& toRemove) const;

	/**
	 * Replaces the first occurrence of the given toReplace String with the
	 * given replacement String.
	 *
	 * @param toReplace The String to be replaced
	 * @param replacement The replacement
	 * @return A new String
	 */
	const String replaceFirst(const String& toReplace,
							  const String& replacement) const;

	/**
	 * Replaces all occurrences of the given toReplace String with the given
	 * replacement String.
	 *
	 * @param toReplace The String(s) to be replaced
	 * @param replacement The replacement
	 * @return A new String
	 */
	const String replaceAll(const String& toReplace,
							const String& replacement) const;

	/**
	 * Inserts the given String into this String at the given index location.
	 *
	 * @param idx The index location to be inserted at
	 * @param toInsert The String being inserted
	 * @return A new String containing the insertion
	 */
	const String insert(unsigned int idx, const String& toInsert) const;

	/**
	 * Returns a segment from this String.
	 *
	 * @param startIdx The first character of this String to be included.
	 * @param endIdx The character AFTER the last character of this String to
	 * 		  be included (exclusive).
	 * @return The substring
	 */
	const String substring(size_t startIdx, size_t endIdx) const;

	/**
	 * Will split a String into several String segments. The String will be
	 * split at every occurrence of the regex. The regex itself will not
	 * be included in the returned segments but will be omitted.
	 * If two or more regexes are adjacent to each other, they will both
	 * be omitted together.
	 * If a regex is located at either the beginning or end of the String such
	 * as with the colons in ":IgnoresTheseColons:", it will be omitted.
	 *
	 * @example
	 * String s("This:Will:Split");
	 * s.split(":"); // Returns a vector with [This],[Will],[Split]
	 *
	 * @example
	 * String s("This::Will::Split");
	 * s.split(":"); // Returns a vector with [This],[Will],[Split]
	 *
	 * @param regex The String identifier which marks each location to be split
	 * @return A vector list containing each segment
	 */
	std::vector<String> split(const String& regex) const;

	/**
	 * Splits the String into two segments occurring at the given index
	 * location. The index indicates the first character of the second half
	 * of the split. See the example shown below.
	 *
	 * @example
	 * String s("SplitHere");
	 * s.split(5); // Returns a vector with [Split],[Here]
	 *
	 * @example
	 * String s("SplitHere");
	 * s.split(0); // Returns a vector with [],[SplitHere]
	 *
	 * @example
	 * String s("SplitHere");
	 * s.split(9); // Returns a vector with [SplitHere],[]
	 *
	 * @param idx The index at which the String will be split
	 * @return A vector<String> which always contains exactly two elements
	 */
	std::vector<String> split(unsigned int idx) const;

	/**
	 * Returns a new String which has been trimmed of extra whitespace on both
	 * the left and right hand sides.
	 *
	 * Whitespace includes spaces, tabs, vertical tabs, newlines, carriage
	 * returns, and feeds.
	 *
	 * @return A new String which has been trimmed
	 */
	const String trim() const;

	/**
	 * Converts this String into an std::string.
	 *
	 * @return The resulting conversion
	 */
	const std::string toStdString() const;

// -----------------------------------------------------------------------------
// Operators
// -----------------------------------------------------------------------------

	/**
	 * Re-allocates the String's internal c string and sets it equal to the
	 * given String.
	 *
	 * @param toEqual The String to be copied by this String
	 * @return This String
	 */
	String& operator=(const String& toEqual);

	template <class T>
	String& operator=(const T& toEqual)
	{
		delete [] this->c_str;
		this->c_str = NULL;

		// Use a string stream to transfer the information to the c_str
		std::stringstream equalStream;

		equalStream << toEqual;
		this->c_str = new char[equalStream.str().size() + 1];

		// Copies the characters from the stream into the internal cstring
		std::strcpy(this->c_str, equalStream.str().c_str());

		return *this;
	}

	/**
	 * Returns the resulting String after appending the given String to this
	 * String.
	 *
	 * @param toAppend The String to be appended onto the end
	 * @return The resulting appended String
	 */
	const String operator+(const String& toAppend) const;
	const String operator+(char toAppend) const;

	template <class T>
	const String operator+(T toAppend) const
	{
		std::stringstream appendStream;

		appendStream << this->c_str << toAppend;

		return String(appendStream.str().c_str());
	}

	/**
	 * Appends the given String to this String.
	 *
	 * @param toAppend The String to be appended onto the end
	 * @return This String after append
	 */
	String& operator+=(const String& toAppend);

	template <class T>
	String& operator+=(const T toAppend)
	{
		return (*this = (*this + toAppend));
	}

// -----------------------------------------------------------------------------
// Comparison Operators
// -----------------------------------------------------------------------------

	/**
	 * Returns whether the given String has the same characters as this String.
	 *
	 * @param toCompare The String being compared
	 * @return True if they are the same; False if they are not the same
	 */
	bool operator==(const String& toCompare) const;

	/**
	 * Compares two strings while ignoring any differences between uppercase and
	 * lowercase letters.
	 *
	 * @param toCompare The other String being compared
	 * @return Whether both Strings are equivalent while ignoring letter cases
	 */
	bool equalsIgnoreCase(const String& toCompare) const;

	/**
	 * Returns whether the given String does not have the same characters as
	 * this String.
	 *
	 * @param toCompare The String being compared
	 * @return True if they are not the same; False if they are the same
	 */
	bool operator!=(const String& toCompare) const;


	/**
	 * Allows an output stream to take in a String object as input and output
	 * its characters.
	 *
	 * @param os The output stream
	 * @param str The String to be output
	 * @return The output Stream resulting from adding the given String's
	 * characters
	 */
	friend std::ostream& operator<<(std::ostream& os, const String& str);

	/**
	 * Allows an input stream to take in a String object as output and input
	 * outside characters into it. The behavior is identical to that of an input
	 * operation on a std::string object.
	 *
	 * @param is The input stream
	 * @param str The String acting as an input
	 * @return The input stream
	 */
	friend std::istream& operator>>(std::istream& is, String& str);

private:
	char* c_str; // Dynamically stores every character in the String

};



#endif
