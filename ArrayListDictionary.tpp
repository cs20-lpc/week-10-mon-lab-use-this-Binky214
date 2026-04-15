// value to count comparisons
template <typename Key, typename Val>
unsigned ArrayListDictionary<Key, Val>::numComps = 0;

// constructor: initializes dictionary with given size
template <typename Key, typename Val>
ArrayListDictionary<Key, Val>::ArrayListDictionary(int i)
: list(new ArrayList<Record>(i)) { } // create dynamic ArrayList

// copy constructor: creates deep copy
template <typename Key, typename Val>
ArrayListDictionary<Key, Val>::ArrayListDictionary(const ArrayListDictionary<Key, Val>& copyObj) {
    copy(copyObj); // use helper function
}

// assignment operator: handles assigning one object to another
template <typename Key, typename Val>
ArrayListDictionary<Key, Val>& ArrayListDictionary<Key, Val>::operator=(const ArrayListDictionary<Key, Val>& rightObj) {
    if (this != &rightObj) { // avoid self-assignment
        clear();             // clear current contents
        delete list;         // free old memory (important fix)
        copy(rightObj);      // copy new data
    }
    return *this; // allow chaining
}

// destructor: frees allocated memory
template <typename Key, typename Val>
ArrayListDictionary<Key, Val>::~ArrayListDictionary() {
    delete list; // delete ArrayList object
}

// iterative binary search
template <typename Key, typename Val>
Val ArrayListDictionary<Key, Val>::binSearchIter(const Key& target, int left, int right) const {
    while (left <= right) { // loop while search space is valid
        int mid = (left + right) / 2; // find middle index

        numComps++; // count comparison

        // check if middle element matches target
        if (list->getElement(mid).k == target) {
            return list->getElement(mid).v; // return value if found
        }
        // if target is larger, search right half
        else if (list->getElement(mid).k < target) {
            left = mid + 1;
        }
        // if target is smaller, search left half
        else {
            right = mid - 1;
        }
    }

    throw -1; // not found
}

// recursive binary search
template <typename Key, typename Val>
Val ArrayListDictionary<Key, Val>::binSearchRec(const Key& target, int left, int right) const {
    if (left > right) { // base case: not found
        throw -1;
    }
     
    int mid = (left + right) / 2; // find middle

    numComps++; // count comparison

    // check if match
    if (list->getElement(mid).k == target) {
        return list->getElement(mid).v;
    }
    // search right half
    else if (list->getElement(mid).k < target) {
        return binSearchRec(target, mid + 1, right);
    }
    // search left half
    else {
        return binSearchRec(target, left, mid - 1); // fixed order
    }
}

// clears the dictionary contents
template <typename Key, typename Val>
void ArrayListDictionary<Key, Val>::clear() {
    list->clear(); // clear underlying list
}

// copies another dictionary (deep copy)
template <typename Key, typename Val>
void ArrayListDictionary<Key, Val>::copy(const ArrayListDictionary<Key, Val>& copyObj) {
    list = new ArrayList<Record>(*copyObj.list); // copy construct list
}

// finds value associated with a key
template <typename Key, typename Val>
Val ArrayListDictionary<Key, Val>::find(const Key& k) const {
    numComps = 0; // reset comparison counter

    try {
        return seqSearchRec(k, 0); // call recursive sequential search
        // return binSearchIter(k, 0, list->getLength() - 1);
        // return binSearchRec(k, 0, list->getLength() - 1);
    }
    catch (...) { // catch any error (that's what the ... means)
        throw string("find: error, unsuccessful search, target key not found");
    }
}

// returns number of comparisons made
template <typename Key, typename Val>
unsigned ArrayListDictionary<Key, Val>::getNumComps() {
    return numComps;
}

// inserts a new key-value pair
template <typename Key, typename Val>
void ArrayListDictionary<Key, Val>::insert(const Key& k, const Val& v) {
    list->append(Record(k, v)); // add to end of list
}

// removes a key-value pair by key
template <typename Key, typename Val>
void ArrayListDictionary<Key, Val>::remove(const Key& k) {
    bool flag = false; // track if key was found

    // loop through list
    for (int i = 0; i < list->getLength(); i++) {
        if (list->getElement(i).k == k) { // match found
            list->remove(i); // remove element
            flag = true;
            break;
        }
    }

    if (!flag) { // if not found
        throw string("remove: error, unable to find record with matching key to remove");
    }
}

// iterative sequential search
template <typename Key, typename Val>
Val ArrayListDictionary<Key, Val>::seqSearchIter(const Key& target) const {
    for (int i = 0; i < list->getLength(); i++) {
        numComps++; // count comparison

        if (list->getElement(i).k == target) { // match found
            return list->getElement(i).v;
        }
    }

    throw -1; // not found
}

// recursive sequential search
template <typename Key, typename Val>
Val ArrayListDictionary<Key, Val>::seqSearchRec(const Key& target, int i) const {
    if (i >= list->getLength()) { // base case: end of list
        throw -1;
    }

    numComps++; // count comparison

    if (list->getElement(i).k == target) { 
        return list->getElement(i).v; // return value if found
    }

    return seqSearchRec(target, i + 1); // check next element
}

// returns number of elements in dictionary
template <typename Key, typename Val>
int ArrayListDictionary<Key, Val>::size() const {
    return list->getLength();
}
