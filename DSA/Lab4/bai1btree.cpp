/// BEGIN STUDENT CODE
string toString() {
    stringstream ss;
    ss << "[" << "(" << numEntries << ")";
    for (int i = 0; i < numEntries; i++) {
        ss << entries[i].toString();
    }
    ss << "]";
    return ss.str();
}
/// END STUDENT CODE