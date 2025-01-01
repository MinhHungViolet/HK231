string remove_spaces(string s) {
    if (s.length() == 0) {
        return "";
    } else if (s[0] == ' ') {
        return remove_spaces(s.substr(1));
    } else {
        return s[0] + remove_spaces(s.substr(1));
    }
}

bool isPalindrome(string str) {
    string s = remove_spaces(str);
    if (s.length() <= 1) {
        return true;
    } else if (s[0] != s[s.length() - 1]) {
        return false;
    } else {
        return isPalindrome(s.substr(1, s.length() - 2));
    }
}