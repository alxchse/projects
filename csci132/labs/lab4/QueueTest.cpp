#include "ArrayQueue.h"
#include <iostream>
using namespace std;

bool areEqual(const ArrayQueue<int>&, const ArrayQueue<int>&);
int main(void) {
    ArrayQueue<int> myQueue;

    for (int i = 10; i > 0; i--) {
        myQueue.enqueue(i);
        cout << "Adding " << i << endl;
    }
    cout << endl;
    
    int temp = myQueue.size();
    if (temp == 10) {
        cout << "Size method correctly returns " << temp << "." << endl;
    } else {
        cout << "Size method incorrectly returns " << temp << "." << endl;
    } //checking size
    cout << endl;

    if (myQueue.inorder()) {
        cout << "Inorder correctly returns true on queue sorted largest (front) to smallest." << endl;
    } else {
        cout << "Inorder incorrectly returns false on queue sorted largest (front) to smallest." << endl;
    } //checking inorder
    cout << endl;

    myQueue.dequeue();
    myQueue.enqueue(11);

    if (!myQueue.inorder()) {
        cout << "Inorder correctly returns false on out-of-order queue." << endl;
    } else {
        cout << "Inorder incorrectly returns true on out-of-order queue." << endl;
    } //checking inorder
    cout << endl;

    cout << "Clearing queue. " << endl;
    myQueue.clear( );
    if (myQueue.isEmpty()) {
        cout << "Queue is empty." << endl;
    } else {
        cout << "Queue is not empty." << endl;
    }
    cout << endl;

    cout << "Testing inorder() for empty queue." << endl;
    if (myQueue.inorder()) {
        cout << "Correct value of true returned." << endl;
    } else {
        cout << "Incorrect value of false returned." << endl;
    } //checking inorder
    cout << endl;

    ArrayQueue<int> q1;
    ArrayQueue<int> q2;
    ArrayQueue<int> q3;

    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);

    q2.enqueue(1);
    q2.enqueue(2);
    q2.enqueue(3);

    q3.enqueue(4);
    q3.enqueue(5);

    cout << "Testing areEqual for two queues that are the same." << endl;
    if (areEqual(q1, q2)) {
        cout << "Correct value of true returned." << endl;
    } else {
        cout << "Incorrect value of false returned." << endl;
    }
    cout << endl;

    cout << "Testing areEqual for two queues that are not the same." << endl;
    if (areEqual(q1, q3)) {
        cout << "Incorrect value of true returned." << endl;
    } else {
        cout << "Correct value of false returned." << endl;
    }
} //main

bool areEqual(const ArrayQueue<int>& queue1, const ArrayQueue<int>& queue2) {
    int spot1;
    int spot2;
 
    for (int i = 0; i < queue1.size(); i++) {
        spot1 = queue1.peekFront();
        spot2 = queue2.peekFront();
        if (spot1 != spot2)
            return false;
    }
    return true;
}