
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

/**
 * Using string::find, needs to transform between size_t and iterator.
 * Able to print size_t, easy to trace.
 */
static bool ReplaceWhitespaceNonBetweenDoubleQuoteV1(string &strSubject)
{
    printf("ReplaceWhitespace enter\n");
	string::iterator startPos = strSubject.begin();
	string::iterator endPos = startPos;
	size_t doubleQuoteStart = 0, doubleQuoteEnd = 0, lastDoubleQuoteEnd = 0;

	doubleQuoteStart = strSubject.find('"');
	while (string::npos != doubleQuoteStart) {
	    doubleQuoteEnd = strSubject.find('"', doubleQuoteStart + 1);
	    if (string::npos == doubleQuoteEnd) {
	        // Unpaired double quote
	        break;
	    }

        printf("   doubleQuoteStart: %zu\n", doubleQuoteStart);
        printf("     lastDoubleQuoteEnd: %zu, diff: %zu\n", lastDoubleQuoteEnd, doubleQuoteStart - lastDoubleQuoteEnd);
        printf("   doubleQuoteEnd: %zu\n", doubleQuoteEnd);

        endPos = next(startPos, doubleQuoteStart - lastDoubleQuoteEnd);
        printf("   before replace from %zu to %zu\n", lastDoubleQuoteEnd, doubleQuoteEnd);
	    replace(startPos, endPos, ' ', '*');
        printf("      result: %s\n\n", strSubject.c_str());

	    startPos = next(endPos, doubleQuoteEnd - doubleQuoteStart);
	    lastDoubleQuoteEnd = doubleQuoteEnd;
	    doubleQuoteStart = strSubject.find('"', doubleQuoteEnd + 1);
	}

    printf("After while: %s\n", strSubject.c_str());
	replace(startPos, strSubject.end(), ' ', '*');
    printf("After all: %s\n", strSubject.c_str());
	return true;
}

/**
 * Using only iterator, refactoring from version 1.
 */
static bool ReplaceWhitespaceNonBetweenDoubleQuoteV2(string &strSubject)
{
	const string::iterator kSubjectEnd = strSubject.end();
	string::iterator doubleQuoteStart = strSubject.begin();
	string::iterator doubleQuoteEnd = doubleQuoteStart;
	string::iterator lastDoubleQuoteEnd = doubleQuoteStart;

	doubleQuoteStart = find(doubleQuoteStart, kSubjectEnd, '"');
	while (kSubjectEnd != doubleQuoteStart) {
		doubleQuoteEnd = find(doubleQuoteStart + 1, kSubjectEnd, '"');
		if (kSubjectEnd == doubleQuoteEnd) {
			// Unpaired double quote
			break;
		}

		replace(lastDoubleQuoteEnd, doubleQuoteStart, ' ', '*');

		lastDoubleQuoteEnd = doubleQuoteEnd;
		doubleQuoteStart = find(doubleQuoteEnd + 1, kSubjectEnd, '"');
	}

	replace(lastDoubleQuoteEnd, kSubjectEnd, ' ', '*');
	return true;
}

/**
 * Iterate whole string by myself. Keep last double-quote position.
 */
static bool ReplaceWhitespaceNonBetweenDoubleQuoteV3(string &strSubject)
{
	const string::iterator kSubjectEnd = strSubject.end();
	string::iterator lastDoubleQuote = kSubjectEnd;
	string::iterator lastReplacementEnd = strSubject.begin();

	for (string::iterator current = strSubject.begin(); kSubjectEnd != current; current++) {
		if ('\"' != *current) {
			continue;
		}

		if (lastDoubleQuote == kSubjectEnd) {
			lastDoubleQuote = current;
		} else {
			replace(lastReplacementEnd, lastDoubleQuote, ' ', '*');

			lastReplacementEnd = current;
			lastDoubleQuote = kSubjectEnd;
		}
	}

	replace(lastReplacementEnd, kSubjectEnd, ' ', '*');
	return true;
}

int main(){
    string strEkko = " 1 \" 56 \" 012  \"  89 \" 3 \" ";
    printf("Input : %s\n", strEkko.c_str());

    ReplaceWhitespaceNonBetweenDoubleQuoteV1(strEkko);
    // ReplaceWhitespaceNonBetweenDoubleQuoteV2(strEkko);
    // ReplaceWhitespaceNonBetweenDoubleQuoteV3(strEkko);
    printf("Output: %s\n", strEkko.c_str());

    return 0;
}
