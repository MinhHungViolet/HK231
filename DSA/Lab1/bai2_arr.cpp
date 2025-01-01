#include <iostream>
#include <vector>
using namespace std;

int longestSublist(vector<string>& words) {
    int maxLen = 0;
    int currLen = 0;
    char currChar = '\0';
    
    for (int i = 0; i < words.size(); i++) {
        if (words[i].empty()) {
            maxLen = max(maxLen, currLen);
            currLen = 0;
            currChar = '\0';
        } else if (words[i][0] == currChar) {
            currLen++;
        } else {
            maxLen = max(maxLen, currLen);
            currLen = 1;
            currChar = words[i][0];
        }
    }
    
    maxLen = max(maxLen, currLen);
    return maxLen;
}
