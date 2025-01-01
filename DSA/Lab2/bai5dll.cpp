#include <iostream>
#include <list>

using namespace std;

class DataLog
{
private:
    list<int> logList;
    list<int>::iterator currentState;

public:
    DataLog()
    {
        logList.push_back(0);
        currentState = logList.begin();
    }

    DataLog(const int &data)
    {
        logList.push_back(data);
        currentState = logList.begin();
    }

    void addCurrentState(int number)
    {
        /*  * TODO: Add a new state after the current state with the given number.
            * Hint: Use the list::insert() function to insert the new state after the currentState iterator.
            *       Don't forget to update the currentState iterator to point to the new state.
        */
        currentState++;
        logList.insert(currentState, number);
    }

    void subtractCurrentState(int number)
    {
        /*  * TODO: Subtract the given number from the current state.
            * Hint: Use the list::erase() function to remove the current state and then insert a new state with the subtracted value.
            *       Don't forget to update the currentState iterator to point to the new state.
        */
        int currentData = *currentState;
        logList.erase(currentState);
        currentState = logList.insert(currentState, currentData - number);
    }

    void save()
    {
        /*  * TODO: Save the current state by creating a new state with the same value.
            * Hint: Use the list::insert() function to insert the new state after the currentState iterator.
            *       Don't forget to update the currentState iterator to point to the new state.
        */
        currentState++;
        logList.insert(currentState, *currentState);
    }

    void undo()
    {
        /*  * TODO: Move the currentState iterator back one state.
            * Hint: Use the list::prev() function to move the iterator back one state.
            *       Don't forget to check if the iterator is at the beginning of the list.
        */
        if (currentState != logList.begin()) {
            currentState--;
        }
    }

    void redo()
    {
        /*  * TODO: Move the currentState iterator forward one state.
            * Hint: Use the list::next() function to move the iterator forward one state.
            *       Don't forget to check if the iterator is at the end of the list.
        */
        if (currentState != logList.end()) {
            currentState++;
        }
    }

    int getCurrentStateData()
    {
        return *currentState;
    }

    void printLog()
    {
        for (auto i = logList.begin(); i != logList.end(); i++) {
            if (i == currentState) cout << "Current state: ";
            cout << "[ " << *i << " ] => ";
        }
        cout << "END_LOG";
    }
};