
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

static bool ReplaceWhitespaceNonBetweenDoubleQuote(string &strSubject)
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

int main(){
    string strEkko = " 1 \" 56 \" 012  \"  89 \" 3 \" ";
    printf("Input : %s\n", strEkko.c_str());

    ReplaceWhitespaceNonBetweenDoubleQuote(strEkko);
    printf("Output: %s\n", strEkko.c_str());

    return 0;
}
