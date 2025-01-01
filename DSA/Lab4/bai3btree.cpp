/// BEGIN STUDENT CODE
/// ======================================================
// You may need some helping functions here

bool search(const K& key, Node*& outNodePtr, int& outEntryIdx) {
    // Start searching from the root node
    Node* currentNode = root;

    while (currentNode) {
        // Find the position to insert the key
        int low = 0;
        int high = currentNode->numEntries - 1;
        int mid;

        while (low <= high) {
            mid = (low + high) / 2;
            if (key == currentNode->entries[mid].key) {
                // Key found
                outNodePtr = currentNode;
                outEntryIdx = mid;
                return true;
            } else if (key < currentNode->entries[mid].key) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        // Key not found, move to the appropriate child node
        if (key < currentNode->entries[0].key) {
            currentNode = currentNode->firstPtr;
        } else {
            currentNode = currentNode->entries[high].rightPtr;
        }
    }

    // Key not found in the tree
    outNodePtr = nullptr;
    outEntryIdx = -1;
    return false;
}

/// END STUDENT CODE