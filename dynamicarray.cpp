#include <iostream>
#include <cmath>
using namespace std;

class DynamicArray {
    private:
        int capacity;
        int cursize;
        int *values;

        void resize(bool increase) {
            int newCapacity;
            int loopSize;
            if (increase) {
                //double the capacity so we don't have to do this operation often
                newCapacity = capacity * 2;
                loopSize = cursize;
            } else {
                //halve the capacity
                newCapacity = ceil(capacity / 2);
                loopSize = newCapacity;
            }

            int* newValues = new int[newCapacity]();

            for (int i = 0; i < loopSize; i++) {
                newValues[i] = values[i];
            }

            capacity = newCapacity;
            values = newValues;
        }

        void testAddResize() {
            if (capacity == cursize) {
                resize(true);
            }
        }

        void testRemoveResize() {
            //resize if we're at less than a quarter capacity
            float ratio = float(cursize) / capacity;
            if (ratio < 0.25) {
                resize(false);
            }
        }

        int findValue(int x) {
            for (int i = 0; i < cursize; i++) {
                if (values[i] == x) {
                    return i;
                }
            }

            return -1;
        }

    public:
        DynamicArray() {
            capacity = 1;
            cursize = 0;
            values = new int[capacity]();
        }

        void append(int x) {
            testAddResize();
            values[cursize] = x;
            cursize++;
        }

        int get(int i) {
            if (i < 0 || i >= cursize) {
                throw std::out_of_range("Index out of bounds");
            }
            return values[i];
        }

        void set(int i, int x) {
            if (i < 0 || i >= cursize) {
                throw std::out_of_range("Index out of bounds");
            }
            values[i] = x;
        }

        int size() {
            return cursize;
        }

        int get_capacity() {
            return capacity;
        }

        int pop_back() {
            int index = cursize - 1;
            if (index < 0 || capacity <= 0) {
                throw std::out_of_range("Index out of bounds");
            }

            int returnValue = values[index];
            set(index, 0);
            cursize--;

            testRemoveResize();

            return returnValue;
        }

        int pop(int i) {
            if (i < 0 || i >= cursize) {
                throw std::out_of_range("Index out of bounds");
            }

            int value = values[i];

            if (i == (cursize - 1)) {
                //we popped the last value, no need to shuffle
            } else {
                for (int j = i + 1; j < cursize; j++) {
                    values[j - 1] = values[j];
                }

                values[cursize - 1] = 0;
            }
            cursize--;
            testRemoveResize();
            return value;
        }

        bool contains(int x) {
            int i = findValue(x);

            if (i == -1) {
                return false;
            } else {
                return true;
            }
        }

        void insert(int i, int x) {
            if (i < 0 || i >= cursize) {
                throw std::out_of_range("Index out of bounds");
            }

            //we're adding a value so check if it will put us over capacity
            testAddResize();
            cursize++;

            for (int j = cursize; j > i; j--) {
                values[j] = values[j - 1];
            }

            values[i] = x;
        }

        int remove(int x) {
            int i = findValue(x);

            if (i == -1) {
                return i;
            }

            for (int j = i; j < cursize - 1; j++) {
                int next = j + 1;
                if (next == cursize) {
                    values[j] = 0;
                } else {
                    values[j] = values[next];
                }
            }

            cursize--;
            testRemoveResize();

            return i;
        }

        void printArray() {
            cout << "[";
            for (int i = 0; i < cursize; i++) {
                cout << values[i];
                if (i != cursize - 1) {
                    cout << ",";
                }
            }
            cout << "]" << endl;
        }
};

int main() {
    DynamicArray arr1;
    int val;
    bool test;

	cout << "Initializing new array..." << endl << endl;

    arr1.append(1);
    arr1.append(2);
    arr1.append(3);
    arr1.append(4);
    arr1.append(5);
    arr1.append(6);
    arr1.append(7);
    arr1.append(8);
    arr1.append(9);
    arr1.append(10);

    arr1.printArray();
    cout << endl;

    val = arr1.get(0);
	cout << "Get 0 (expected 1): " << val << endl;

    val = arr1.get(1);
	cout << "Get 1 (expected 2): " << val << endl;

    val = arr1.size();
	cout << "Size (expected 10): " << val << endl;

	cout << "Set '15' at index 2..." << endl;
    arr1.set(2, 15);

    arr1.printArray();
    cout << endl;
    val = arr1.get(2);
	cout << "Get after set (expected 15): " << val << endl << endl;

    val = arr1.pop_back();
	cout << "Pop_back (expected 10): " << val << endl;
    val = arr1.size();
	cout << "Size after pop_back (expected 9): " << val << endl;
    val = arr1.get_capacity();
	cout << "Capacity after pop_back: " << val << endl << endl;

    test = arr1.contains(15);
	cout << "Contains 15 (expected true): " << test << endl << endl;

    test = arr1.contains(10);
	cout << "Contains 10 (expected false): " << test << endl << endl;

    arr1.printArray();
    cout << endl;

    val = arr1.pop(6);
	cout << "Pop 6 (expected 7): " << val << endl << endl;
    val = arr1.size();
	cout << "Size after pop (expected 8): " << val << endl;
    val = arr1.get_capacity();
	cout << "Capacity after pop: " << val << endl << endl;
    arr1.printArray();
    cout << endl;

	cout << "Insert '20' at index 4..." << endl;

    arr1.insert(4, 20);
    val = arr1.size();
	cout << "Size after insert (expected 9): " << val << endl;
    val = arr1.get_capacity();
	cout << "Capacity after insert: " << val << endl << endl;
    arr1.printArray();
    cout << endl;

	cout << "Append '20'..." << endl;
    arr1.append(20);
	cout << "Remove first '20'..." << endl;
    val = arr1.remove(20);
	cout << "Index removed (expected 4): " << val << endl;
    val = arr1.size();
	cout << "Size after append & remove (expected 9): " << val << endl;
    val = arr1.get_capacity();
	cout << "Capacity after remove: " << val << endl << endl;
    arr1.printArray();
    cout << endl;

    val = arr1.remove(12345);
	cout << "Attempt remove nonexistent value '12345' (expected -1)" << val << endl;
    val = arr1.size();
	cout << "Size after append & remove (expected 9): " << val << endl;
    val = arr1.get_capacity();
	cout << "Capacity after append & remove: " << val << endl << endl;
    arr1.printArray();
    cout << endl;

	cout << "Remove values to check capacity reduction on remove..." << endl;
    val = arr1.remove(1);
    val = arr1.remove(20);
    val = arr1.remove(2);
    val = arr1.remove(15);
    val = arr1.remove(4);
    val = arr1.remove(9);
    val = arr1.size();
	cout << "Size after 6 removes (expected 3): " << val << endl;
    val = arr1.get_capacity();
	cout << "Capacity after 6 removes: " << val << endl << endl;
    arr1.printArray();
    cout << endl;

    try {
        arr1.get(-1);
    } catch (const std::out_of_range& e) {
        cout << "Caught expected error on -1 get: " << e.what() << endl;
    }

    try {
        arr1.get(10);
    } catch (const std::out_of_range& e) {
        cout << "Caught expected error on 10 get: " << e.what() << endl;
    }

    try {
        arr1.set(-1, 5);
    } catch (const std::out_of_range& e) {
        cout << "Caught expected error on set '5' at index -1: " << e.what() << endl;
    }

    try {
        arr1.set(10, 5);
    } catch (const std::out_of_range& e) {
        cout << "Caught expected error on set '5' at index 10: " << e.what() << endl;
    }

    try {
        arr1.set(10, 5);
    } catch (const std::out_of_range& e) {
        cout << "Caught expected error on set '5' at index 10: " << e.what() << endl;
    }

    try {
        arr1.pop(-1);
    } catch (const std::out_of_range& e) {
        cout << "Caught expected error on -1 pop: " << e.what() << endl;
    }

    try {
        arr1.pop(10);
    } catch (const std::out_of_range& e) {
        cout << "Caught expected error on 10 pop: " << e.what() << endl;
    }

    try {
        arr1.insert(-1, 20);
    } catch (const std::out_of_range& e) {
        cout << "Caught expected error on -1 insert: " << e.what() << endl;
    }

    try {
        arr1.insert(10, 20);
    } catch (const std::out_of_range& e) {
        cout << "Caught expected error on 10 insert: " << e.what() << endl << endl;
    }

    val = arr1.size();
	cout << "Size after exception checks: " << val << endl;
    val = arr1.get_capacity();
	cout << "Capacity after exception checks: " << val << endl << endl;
    arr1.printArray();
    cout << endl;

	cout << "Initializing new array for pop_back empty check..." << endl << endl;
    DynamicArray arr2;
    try {
        arr2.pop_back();
    } catch (const std::out_of_range& e) {
        cout << "Caught expected error on pop_back with empty array: " << e.what() << endl;
    }
}
