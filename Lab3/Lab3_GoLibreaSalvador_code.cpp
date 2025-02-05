#include <iostream>
using namespace std;

struct IntNode {
    int data; // the actual value
    IntNode *next; // points to the next node in the stack

    // Default Constructor
    // Initializes data to 0 and next to null
    IntNode() {
        this->data = 0;
        this->next = NULL;
    }

    // Parameterized Constructor
    // Initializes data to a given value and next to null
    IntNode(int data) {
        this->data = data;
        this->next = NULL;
    }

    // Paramarized Constructor
    // Initializes data to a given value and links the node to a given existing node
    IntNode(int data, IntNode *link) {
        this->data = data;
        this->next = link;
    }
};

struct IntStack {
    IntNode *top; // points to the top node
    
    // Default Constructor
    // Initializes top to null (empty stack)
    IntStack() {
        this->top = NULL;
    }

    // Destrcutor
    // Loops through the stack snd deletes all nodes to prevent memory leaks
    ~IntStack() {
        while (top) {
            IntNode* temp = top; 
            top = top->next;
            delete temp;
        }
    }
};

// Removing the top element from the stack
int pop(IntStack *stack) {
    // Checks first if the stack is empty before doing the pop
    if (stack->top == NULL){
        throw std::runtime_error("Not allowed to pop from an empty stack");
    }
    // Accesses top node from stack
    IntNode *top = stack->top;
    // Saves top node data for later
    int data = top->data;
    // Sets top node of stack to next node on stack
    stack->top = stack->top->next;
    // De-allocates top node from memory
    delete top;
    // Returns top node data
    return data;
}

// Adds an element to the top of the stack
void push(IntStack *stack, int data) {
    // Makes new node with value data and sets its next to the current top
    // to link it to the existing stack
    IntNode *node = new IntNode(data, stack->top);
    stack->top = node;
}

// Returns the top element without removing it
int peek(IntStack *stack) {
     // Checks first if the stack is empty before doing the peek
    if (stack->top == NULL) {  
        throw runtime_error("Not allowed to peek at an empty list");
    }
    return stack->top->data;
}

int main(void) {
    IntStack *stack = new IntStack();
    for (int i = 0; i < 100; i++) {
        push(stack, i);
    }
    
    push(stack, 5);
    push(stack, 3);
    push(stack, 2);
    cout << pop(stack) << endl << "Popped" << endl;
    cout << peek(stack) << endl << "Peeked" << endl;
    cout << pop(stack) << endl << "Popped" << endl;
    cout << pop(stack) << endl << "Popped" << endl;
    cout << pop(stack) << endl << "Popped" << endl;
    cout << pop(stack) << endl << "Popped" << endl;
    cout << pop(stack) << endl << "Popped" << endl;
    delete stack; // to avoid memory leak deletes the stack when finished
    return 0;
}