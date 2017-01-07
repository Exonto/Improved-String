
#include "String.h"

#include <cstring>
#include <sstream>
#include <vector>
#include <stdexcept>

String::String(const char* c_str /* Default of '\0' */)
{
	// Allocate memory for each character plus the null terminating bit
	this->c_str = new char[std::strlen(c_str) + 1];

	// Copies each character over from the given c_str including the null
	// terminating bit
	std::strcpy(this->c_str, c_str);
}

String::String(const String& toCopy)
{
	// Allocate memory for each character plus the null terminating bit
	this->c_str = new char[std::strlen(toCopy.c_str) + 1];

	// Copies each character over from the given c_str including the null
	// terminating bit
	std::strcpy(this->c_str, toCopy.c_str);
}

String::~String()
{
	delete [] this->c_str;
	this->c_str = NULL;
}

// -----------------------------------------------------------------------------
// String Information
// -----------------------------------------------------------------------------

const unsigned int String::length() const
{
	return std::strlen(this->c_str);
}

const char String::charAt(unsigned int idx) const
{
	return this->c_str[idx];
}

const char String::operator[](unsigned int idx) const
{
	return this->c_str[idx];
}

const unsigned int String::indexOf(const String& segment) const
{
	// Tracks the character being examined starting at the first
	char* sentry = this->c_str;
	String compareBuilder(""); // Builds a temporary string for comparing
	while ( (sentry - this->c_str) < this->length() &&
		     compareBuilder != segment)
	{
		// Compares the sentry's current character of this String with the
		// character of the given segment. It uses compareBuilder's current
		// length as an index to determine how far along in the comparison
		// it has gotten. If the two characters are equal, that character
		// is appended onto compareBuilder.
		if (*sentry == segment[compareBuilder.length()])
		{
			// Append another character to the builder
			compareBuilder += *sentry;

			++sentry;
		} else if (compareBuilder.length() > 0) {
			compareBuilder = "";
		} else {
			++sentry;
		}
	}

	// In the case that the segment could not be found, returns -1.
	if (compareBuilder != segment) return -1;

	// Takes the sentry's location and backs it up to the very first character
	// where the two comparisons meet. It then has the c_str's memory location
	// subtract to reveal the relative index location.
	return (sentry - compareBuilder.length()) - this->c_str;
}

std::vector<int> String::indexesOf(const String& segment) const
{
	std::vector<int> indexes;

	// Handles known cases of equality or inequality
	if (segment.length() > this->length()) return indexes;

	// Tracks the character being examined starting at the first
	char* sentry = this->c_str;
	String compareBuilder(""); // Builds a temporary string for comparing
	while ((sentry - this->c_str) < this->length())
	{
		// Compares the sentry's current character of this String with the
		// character of the given segment. It uses compareBuilder's current
		// length as an index to determine how far along in the comparison
		// it has gotten. If the two characters are equal, that character
		// is appended onto compareBuilder.
		if (*sentry == segment[compareBuilder.length()])
		{
			// Append another character to the builder
			compareBuilder += *sentry;

			// If a full match has been found, store the index location and
			// reset the comparison builder
			if (compareBuilder == segment)
			{
				indexes.push_back((sentry - compareBuilder.length()) - this->c_str + 1);
				compareBuilder = "";
			}

			++sentry;
		} else if (compareBuilder.length() > 0) {
			// Sentry must back up all the way to the index directly after the
			// first index where a potential match was found
			sentry -= compareBuilder.length() - 1;
			compareBuilder = "";
		} else {
			// Comparison not found, continue to the next character
			++sentry;
		}
	}
	return indexes;
}

const bool String::contains(const String& segment) const
{
	// Handles known cases of equality or inequality
	if (segment.length() > this->length()) return false;
	if (segment == *this) return true;

	// Tracks the character being examined starting at the first
	char* sentry = this->c_str;
	String compareBuilder(""); // Builds a temporary string for comparing
	while ( (sentry - this->c_str) < this->length() &&
		     compareBuilder != segment)
	{
		// Compares the sentry's current character of this String with the
		// character of the given segment. It uses compareBuilder's current
		// length as an index to determine how far along in the comparison
		// it has gotten. If the two characters are equal, that character
		// is appended onto compareBuilder.
		if (*sentry == segment[compareBuilder.length()])
		{
			// Append another character to the builder
			compareBuilder += *sentry;

			++sentry;
		} else if (compareBuilder.length() > 0) {
			// Sentry must back up all the way to the index directly after the
			// first index where a potential match was found
			sentry -= compareBuilder.length() - 1;
			compareBuilder = "";
		} else {
			++sentry;
		}
	}

	return compareBuilder == segment;
}

// -----------------------------------------------------------------------------
// String Manipulation
// -----------------------------------------------------------------------------

const String String::toUppercase() const
{
	// Create a char array to store the uppercase letters
	char uppercase[this->length() + 1];

	// Points to the character in the existing String
	char* c = this->c_str;
	while (c < this->c_str + this->length())
	{
		// Takes the uppercased character and adds it to the array
		uppercase[c - this->c_str] = std::toupper(*c);

		++c;
	}

	// Manually insert null terminating byte at the end
	uppercase[this->length()] = '\0';

	// Returns a copy of this String
	return String(uppercase);
}

const String String::toLowercase() const
{
	// Create a char array to store the uppercase letters
	char uppercase[this->length() + 1];

	// Points to the character in the existing String
	char* c = this->c_str;
	while (c < this->c_str + this->length())
	{
		// Takes the uppercased character and adds it to the array
		uppercase[c - this->c_str] = std::tolower(*c);

		++c;
	}

	// Manually append null terminating byte
	uppercase[this->length()] = '\0';

	// Returns a copy of this String
	return String(uppercase);
}

const String String::remove(unsigned int charIndex) const
{
	String removedChar("");

	removedChar += this->substring(0, charIndex);
	removedChar += this->substring(charIndex + 1, this->length());

	return removedChar;
}

const String String::removeFirst(const String& toRemove) const
{
	int indexOf = this->indexOf(toRemove);

	return this->removeAll(indexOf, indexOf + toRemove.length());
}

const String String::removeAll(size_t startIndex, size_t endIndex) const
{
	// This represents an illegal case where the starting index is greater than
	// the ending index. This results in incorrect/unexpected behavior.
	if (startIndex > endIndex)
	{
		throw std::range_error("The startIndex is greater than the endIndex");
	}

	// Simply appends every part of the string which has not been removed
	String substr = this->substring(0, startIndex) +
			  this->substring(endIndex, this->length());

	return substr;
}

const String String::removeAll(const String& toRemove) const
{
	String removed("");

	// Finds the index locations at every occurrence of toRemove
	std::vector<int> indexes = this->indexesOf(toRemove);

	int segmentLength = toRemove.length();
	int prevIndex = 0; // Marks the starting index of the next substring

	// Builds the string by appending every non removed segment from this
	// String
	for (size_t listIdx = 0; listIdx < indexes.size(); listIdx++)
	{
		removed += this->substring(prevIndex, indexes.at(listIdx));

		prevIndex = indexes.at(listIdx) + segmentLength;
	}
	removed += this->substring(prevIndex, this->length());

	return removed;
}

const String String::replaceFirst(const String& toReplace,
								  const String& replacement) const
{
	int indexOf = this->indexOf(toReplace);
	String replaced(this->removeFirst(toReplace));

	return replaced.insert(indexOf, replacement);
}

const String String::replaceAll(const String& toReplace,
								const String& replacement) const
{
	// Removes all Strings to be replaced
	String replaced(this->c_str);
	std::vector<int> indexes = this->indexesOf(toReplace);

	for(unsigned int listIdx = 0; listIdx < indexes.size(); listIdx++)
	{
		replaced = replaced.replaceFirst(toReplace, replacement);
	}

	return replaced;
}

const String String::insert(unsigned int idx, const String& toInsert) const
{
	String inserted(this->substring(0, idx));
	inserted += (toInsert + this->charAt(idx));
	inserted += this->substring(
					inserted.length() - toInsert.length(),
					this->length());

	return inserted;
}

const String String::substring(size_t startIdx, size_t endIdx) const
{
	// Error Handling
	if (startIdx < 0 || startIdx > this->length())
	{
		std::cerr << "The starting index was out of bounds at: \'" <<
								startIdx <<
								"\'";
		return String("");
	} else if (endIdx < 0 || endIdx > this->length()) {
		std::cerr << "The ending index was out of bounds at: \'" <<
								endIdx <<
								"\'";
		return String("");
	} else if (startIdx > endIdx) {
		std::cerr << "The starting index is larger than the ending index.";
		return String("");
	}

	// The String to be returned
	String substr("");

	// Note: StartIndex is Inclusive and EndIndex is Exclusive
	const size_t stringLength = (endIdx - startIdx) + 1;
	char* substrBuilder = new char[stringLength];
	for (size_t substrIter = startIdx; substrIter < endIdx; substrIter++)
	{
		substrBuilder[substrIter - startIdx] = this->c_str[substrIter];
	}
	substrBuilder[stringLength - 1] = '\0';

	substr = substrBuilder;

	delete [] substrBuilder;
	substrBuilder = NULL;

	return substr;
}

std::vector<String> String::split(const String& regex) const
{
	unsigned int regexLen = regex.length();

	std::vector<int> regexes = this->indexesOf(regex);
	std::vector<String> segments;

	unsigned int prevIndex = 0;
	// Loops over each regex and substrings all characters between each regex
	for(unsigned int idx = 0; idx < regexes.size(); idx++)
	{
		// Protects against adjacent regexes and regexes located at the
		// end of the String
		if (prevIndex != regexes[idx] &&
			prevIndex != this->length())
		{
			// Stores the substring segment between two regexes
			segments.push_back(this->substring(prevIndex, regexes[idx]));
		}

		prevIndex = regexes[idx] + regexLen;
	}

	// If the last regex index is not the very last character, then add a
	// substring from the previous regex to the end of the String
	if (prevIndex != this->length())
	{
		segments.push_back(this->substring(prevIndex, this->length()));
	}

	return segments;
}

std::vector<String> String::split(unsigned int idx) const
{
	std::vector<String> split;

	split.push_back(this->substring(0, idx));
	split.push_back(this->substring(idx, this->length()));

	return split;
}

const String String::trim() const
{
	String trimmed(this->c_str);

	int charIndex = 0;
	char charAt = trimmed[charIndex];

	// Handles left-hand side of the String
	while (std::isspace(charAt))
	{
		// Because the first element is always removed, charIndex does not need
		// to increment. It may remain at 0 and so always remove the first char.
		trimmed = trimmed.remove(charIndex);

		charAt = trimmed[charIndex];
	}
	charIndex = trimmed.length() - 1;
	charAt = trimmed[charIndex];

	// Handles right-hand side of the String
	while(std::isspace(charAt))
	{
		trimmed = trimmed.remove(charIndex--);

		charAt = trimmed[charIndex];
	}

	return trimmed;
}

const std::string String::toStdString() const
{
	return std::string(this->c_str);
}

// -----------------------------------------------------------------------------
// Operators
// -----------------------------------------------------------------------------

String& String::operator=(const String& toEqual)
{
	if (*this != toEqual)
	{
		delete [] this->c_str;
		this->c_str = new char[toEqual.length() + 1];
		std::strcpy(this->c_str, toEqual.c_str);
	}

	return *this;
}

const String String::operator+(const String& toAppend) const
{
	// The c_string which will be appended to and returned as a String
	char* appended = new char[this->length() +
							  toAppend.length() + 1];

	std::strcpy(appended, this->c_str);
	std::strcat(appended, toAppend.c_str);

	String stringAppended(appended);

	delete [] appended;
	appended = NULL;

	return stringAppended;
}

const String String::operator+(char toAppend) const
{
	// The c_string which will be appended to and returned as a String
	char* appended = new char[this->length() + 1 + 1];

	std::strcpy(appended, this->c_str);
	appended[this->length()] = toAppend;
	appended[this->length() + 1] = '\0';

	String stringAppended(appended);

	delete [] appended;
	appended = NULL;

	return stringAppended;
}

String& String::operator+=(const String& toAppend)
{
	return (*this = (*this + toAppend));
}

// -----------------------------------------------------------------------------
// Comparison Operators
// -----------------------------------------------------------------------------

bool String::operator==(const String& toCompare) const
{
	return std::strcmp(this->c_str, toCompare.c_str) == 0;
}

bool String::equalsIgnoreCase(const String& toCompare) const
{
	return this->toLowercase() == toCompare.toLowercase();
}

bool String::operator!=(const String& toCompare) const
{
	return !(this->operator ==(toCompare));
}

std::ostream& operator <<(std::ostream& os, const String& str)
{
	os << str.c_str; //Outputs strPtr's array as a whole

	return os;
}

std::istream& operator>>(std::istream& is, String& str)
{
	is.clear(); // Removes any previous errors

	// Reads in each character from the stream until some whitespace is found
	std::vector<char> chars;

	// Ignores all initial whitespace
	while (is.good() && std::isspace(is.peek()))
	{
		is.ignore();
		std::cout << "Skipping" << std::endl;
	}

	// Continues storing each subsequent character until whitespace is found
	while (is.good() && std::isspace(is.peek()) == false)
	{
		chars.push_back(is.get());
	}
	chars.push_back('\0');

	str = &chars[0];

	return is;
}
