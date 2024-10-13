//Avleen Gill - 210 Lab 22
//upgrade dll class to delete by position instead of value

#include <iostream>
#include <cstdlib>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void pop_front(){
        if (!head) return;

        Node* temp = head;
        head = temp->next;

        delete temp;
    }

    void pop_back(){
        if (!tail) return;

        Node* temp = tail;
        tail = temp->prev;
        tail->next = nullptr;
        
        delete temp;
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void deleteNode_2(int pos){
        if (!head) return; //if list is empty

        Node* temp = head;
        for (int i = 0; i < (pos-1) && temp; i++){ //traverse to node 
            temp = temp->next;
        }        

        if (!temp) return; //position greater than list length
        
        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    srand(time(0));
    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);
    cout << "List forward: ";
    list.print();
    cout << endl;

    cout << "Which node to delete? Enter position: "; //deleting by pos-------------------
    int pos;
    cin >> pos;
    list.deleteNode_2(pos);
    cout << endl;
    cout << "New list: ";
    list.print();
    cout << endl;

    cout << "Would you like to delete the head node? y/n: "; //deleting head node-----------------
    char entry;
    cin >> entry;
    entry = tolower(entry);
    if(entry == 'y'){
        list.pop_front();
        cout << "Deleted.\n";
        list.print();
    }
    else{
        cout << "List untouched:\n";
        list.print();
    }

    cout << "Would you like to delete the tail node? y/n: "; //deleting tail node-----------------
    cin >> entry;
    entry = tolower(entry);
    if(entry == 'y'){
        list.pop_back();
        cout << "Deleted.\n";
        list.print();
    }
    else{
        cout << "List untouched:\n";
        list.print();
    }

    //cout << "List backward: ";
    //list.print_reverse();


    /*cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();*/

    return 0;
}
