#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Templated Node class
// Normal node except that each node can hold a pair <T,int>
// where the first value is templated and the second value is the frequency
// (or quantity) of the first
// For example, if T was a string then it would hold string,int
template <class T>
class Node {
public:
  Node( const T& data ); //Node Constructor - Assume each quan
  pair<T,int>& GetData(); //Node Data Getter
  void SetData( const pair<T,int>& ); //Node Data Setter
  Node<T>* GetNext(); //Node m_next getter
  void SetNext( Node<T>* next ); //Node m_next setter
private:
  pair <T,int> m_data; //Holds templated data
  Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node( const T& data ) {
  m_data = make_pair(data,1);
  m_next = nullptr;
}

template <class T>
pair<T,int>& Node<T>::GetData() {
   return m_data;
}

template <class T>
void Node<T>::SetData( const pair<T,int>& data ) {
   m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

//Templated Linked List class
template <class T>
class LL {
 public:
  // Name: LL() (Linked List) - Default Constructor
  // Desc: Used to build a new linked list
  // Preconditions: None
  // Postconditions: Creates a new linked list where m_head points to nullptr
  LL();
  // Name: ~LL() - Destructor
  // Desc: Used to destruct a LL
  // Preconditions: There is an existing LL with at least one node
  // Postconditions: A LL is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
 ~LL();
  // Name: LL (Copy Constructor)
  // Desc: Creates a copy of existing LL
  //       Requires a LL - REQUIRED to be implemented even if not used
  // Preconditions: Source LL exists
  // Postconditions: Copy of source LL
  LL(const LL&);
  // Name: operator= (Overloaded Assignment Operator)
  // Desc: Makes two LL of the same type have identical number of nodes and values
  // Preconditions: Requires two linked lists of the same templated type
  //                REQUIRED to be implemented even if not used
  // Postconditions: Two idenetical LL
  LL<T>& operator= (const LL&);
  // Name: Find
  // Desc: Iterates through LL and returns node if data found
  // Preconditions: LL Populated
  // Postconditions: Returns nullptr if not found OR Node pointer if found
  Node<T>* Find(const T& data);
  // Name: Insert
  // Desc: Either inserts a node to the linked list OR increments frequency of first
  //       Takes in data. If "first" (of pair) NOT in list, adds node
  //       If "first" (of pair) is already in list, increments quantity
  //       Inserts "first" in order with no duplicates
  // Preconditions: Requires a LL.
  // Postconditions: Node inserted in LL based on first value (or quantity incremented)
  void Insert(const T&);
  // Name: RemoveAt
  // Desc: Removes a node at a particular position based on data passed (matches first)
  // Preconditions: LL with at least one node. 
  // Postconditions: Removes first node with passed value (in first)
  void RemoveAt(const T&);
  // Name: Display
  // Desc: Display all nodes in linked list
  // Preconditions: Outputs the LL
  // Postconditions: Displays the pair in each node of LL 
  void Display();
  // Name: GetSize
  // Desc: Returns the size of the LL
  // Preconditions: Requires a LL
  // Postconditions: Returns m_size
  int GetSize();
  // Name: operator<< (Overloaded << operator)
  // Desc: Returns the ostream of the data in each node
  // Preconditions: Requires a LL
  // Postconditions: Returns an ostream with the data from each node on different line
  template <class U>
  friend ostream& operator<<(ostream& output, const LL<U>&);
  // Name: Overloaded [] operator
  // Desc: When passed an integer, returns the data at that location
  // Precondition: Existing LL
  // Postcondition: Returns pair from LL using []
  pair<T,int>& operator[] (int x);//Overloaded [] operator to pull data from LL
private:
  Node <T> *m_head; //Node pointer for the head
  int m_size; //Number of nodes in queue
};
//*****************************************************************
//Implement LL here


// Default Constructor
template <class T>
LL<T>::LL(){
  // sets each of the member variables to 0 and nullptr
  m_head = nullptr;
  m_size = 0;

} // end of default constructor

// Destructor
template <class T>
LL<T>::~LL(){
  // deletes the nodes within the linked list
  Node<T> *curr = m_head;
  while (curr != nullptr){
    m_head = curr;
    curr = curr->GetNext();
    delete m_head;

  } // end of while loop

  // sets the member variables to 0 and nullptr
  m_head = nullptr;
  m_size = 0;
  
} // end of destructor

// Copy Constructor
template <class T>
LL<T>::LL(const LL& source){
  // copies the size of the source list
  m_size = source.m_size;

  // fills the head of the destination with that of the source
  m_head = new Node<T>(source.m_head->GetData().first);
  m_head->SetData(source.m_head->GetData());

  // sets variables to the second item in each list
  // as well as creating a destination node pointer to fill in the nodes of the destination
  Node<T> *dest = m_head;
  Node<T> *curr = m_head->GetNext();
  Node<T> *sCurr = source.m_head->GetNext();

  while (sCurr != nullptr){
    // makes a new node with the string of sCurr
    curr = new Node<T>(sCurr->GetData().first);
    // sets the second part of the pair to match that of the sCurr node
    curr->SetData(sCurr->GetData());

    // sets the current destination node to point to the newly created node
    dest->SetNext(curr);

    // moves each of the nodes up one in the lists
    dest = dest->GetNext();
    curr = curr->GetNext();
    sCurr = sCurr->GetNext();

  } // end of while loop

} // end of copy constructor

// Overloaded = operator
template <class T>
LL<T>& LL<T>::operator=(const LL& source){
  // SAME CODE AS ABOVE IN THE COPY CONSTRUCTOR ONLY DIFFERENCE IS THE FIRST LINE

  // I dont know if calling the destructor like this is allowed, but it somehow works how I want it to
  // deletes the list that is on the left of the = then allows it to be refilled
  this->~LL();
  // copies the size of the source
  m_size = source.m_size;

  // fills the head of the destination with that of the source
  m_head = new Node<T>(source.m_head->GetData().first);
  m_head->SetData(source.m_head->GetData());

  // sets variables to the second item in each list
  // in addition to this, sets the destination node pointer
  Node<T> *dest = m_head;
  Node<T> *curr = m_head->GetNext();
  Node<T> *sCurr = source.m_head->GetNext();

  while (sCurr != nullptr){
    // makes a new node from the sCurr node, sets the data to match
    curr = new Node<T>(sCurr->GetData().first);
    curr->SetData(sCurr->GetData());

    // sets the destination to point to the new node
    dest->SetNext(curr);

    // iterates to the next nodes
    dest = dest->GetNext();
    curr = curr->GetNext();
    sCurr = sCurr->GetNext();

  } // end of while loop

  // returns the new linked list that was made
  return *this;

} // end of overloaded assignment operator

// Find function
template <class T>
Node<T>* LL<T>::Find(const T& data){
  // iterates across the linked list
  Node<T> *curr = m_head;
  while (curr != nullptr){
    // returns the node that matches the data that was passed in
    if (curr->GetData().first == data){
      return curr;

    } // end of if statement

    curr = curr->GetNext();

  } // end of while loop

  // else returns a nullptr
  return nullptr;

} // end of Find

// Insert function
template <class T>
void LL<T>::Insert(const T& nodeInfo){
  // if there is nothing in the list
  if (m_size == 0){
    m_head = new Node<T>(nodeInfo);
    m_size++;

  } // end of if statement
  
  // if the size is 1 or more
  else{
    bool isNew = true; // if the node is new to the LL, starts as true

    // iterates across the linked list
    Node<T> *curr = m_head;
    while (curr != nullptr){
      // if the node is the same as the current, increments the amount of times that it has appeared
      // then sets isNew to false to show that the node is not new
      if (nodeInfo == curr->GetData().first){
        curr->GetData().second++;
        isNew = false;

      } // end of if statement

      // goes to the next item in the list
      curr = curr->GetNext();

    } // end of while

    // if the node is a new object, adds it to the LL and increases the size
    if (isNew){
      Node<T> *curr = m_head;
      Node<T> *prev = nullptr;
      // checks for the end of the list, and if the new item is greater than the current
      while ((curr != nullptr) and (curr->GetData().first < nodeInfo)){
        prev = curr;
        curr = curr->GetNext();

      } // end of while loop

      // makes a new node for the information passed in
      Node<T> *newNode = new Node<T>(nodeInfo);
      // if the previous has yet to be set, sets the head to the new node
      if (prev == nullptr){
        m_head = newNode;

      } // end of if statement

      // if the previous is set, fills it in as normal
      else{
        prev->SetNext(newNode);

      } // end of else statement

      // puts the newNode before the curr node and increases the size
      newNode->SetNext(curr);
      m_size++;

    } // end of if statement

  } // end of else statement

} // end of Insert

// RemoveAt function
template <class T>
void LL<T>::RemoveAt(const T& thing){
  // sets the curr and previous variables
  Node<T> *curr = m_head;
  Node<T> *prev = nullptr;

  // if the preffered item is the head, changes the head to the second item, and removes the head
  if (curr->GetData().first == thing){
    m_head = m_head->GetNext();
    delete curr;
    curr = nullptr;
    m_size--;

  } // end of if statement

  // if not the head, iterates through the list until it finds it and removes it
  else{
    while (curr != nullptr){
      if (curr->GetData().first == thing){
        prev->SetNext(curr->GetNext());
        delete curr;
        curr = nullptr;
        m_size--;

      } // end of if statement

      else{
        prev = curr;
        curr = curr->GetNext();
      
      } // end of else statement

    } // end of while loop

  } // end of else statement

} // end of RemoveAt

// Display function
template <class T>
void LL<T>::Display(){
  // couts the output of the overloaded operator
  cout << *this;
  
} // end of Display

// GetSize function
template <class T>
int LL<T>::GetSize(){return m_size;} // end of GetSize

// Overloaded << operator
template <class U>
ostream& operator << (ostream& output, const LL<U>& list){
  // iterates through the linked list to put each objects first and second into the output which is returned
  Node<U> *curr = list.m_head;
  while (curr != nullptr){
    output << curr->GetData().first << ":" << curr->GetData().second << endl;
    curr = curr->GetNext();

  } // end of while loop

  return output;

} // end of overloaded << operator

// overloaded [] operator
template <class T>
pair<T,int>& LL<T>::operator[] (int x){
  // if the x is outside the range of the list
  if (x >= m_size){
    cout << "Input is outside the bounds of the list." << '\n' << "Outputting m_head." << endl;
    return m_head->GetData();

  } // end of if statement

  // if the index is the first in the linked list
  else if (x == 0){
    return m_head->GetData();

  } // end of if statement

  // if the index is not the first
  else{
    Node<T> *curr = m_head;
    // iterates for x times then returns that node
    for (int i = 0; i < x; i++){
      curr = curr->GetNext();

    } // end of for loop

    return curr->GetData();
    
  } // end of else statement

} // end of overloaded [] operator

/*
// ****************************************************************
// To test just LL follow these instructions:
//   1.  Uncomment out int main below
//   2.  make LL
//   3.  ./LL (try valgrind too!)


int main () {
  //Test 1 - Default Constructor and Push
  cout << "Test 1 - Default Constructor and Push Running" << endl;
  //Test Default Constructor
  LL <string>* newLL1 = new LL<string>();
  //Push 4 nodes into LL
  newLL1->Insert("candy");
  newLL1->Insert("cookies");
  newLL1->Insert("candy");
  newLL1->Insert("bananas");
  newLL1->Insert("dogs");
  newLL1->Insert("apples");
  newLL1->Insert("elephants");
  newLL1->Insert("barf");
  newLL1->Insert("candy");
  newLL1->Insert("cookies");
  newLL1->Insert("candy");
  newLL1->Insert("bananas");
  newLL1->Insert("dogs");
  newLL1->Insert("apples");
  newLL1->Insert("elephants");
  newLL1->Insert("barf");
  newLL1->Display();


  //Test 2 - Copy Constructor and Assignment Operator
  cout << "Test 2 - Copy Constructor and Assignment Operator Running" << endl;
  //Test Copy constructor
  LL <string>* newLL2 = new LL<string>(*newLL1);
  cout << "*******Original*********" << endl;
  newLL1->Display();
  cout << "*******Copy*********" << endl;
  newLL2->Display();

  //Test Overloaded Assignment Operator
  LL <string>* newLL3 = new LL<string>();
  *newLL3 = *newLL1;
  cout << "*******Assignment*********" << endl;
  newLL3->Display();
  cout << endl;

  //Test 3 - Test Display and Overloaded <<
  cout << "Test 3 - Display and Overloaded << Running" << endl;
  cout << "newLL1 Display Function" << endl;
  newLL1->Display();
  cout << "newLL1 Overloaded" << endl;
  cout << *newLL1;
  cout << "RemoveAt(candy)" << endl;
  newLL1->RemoveAt("candy");
  cout << "newLL1 Display Function" << endl;
  newLL1->Display();

  // Test 4 - Test overloaded [] operator
  cout << "Test 4 - Display pair using []" << endl;
  cout << (*newLL1)[3].first << endl;

  delete newLL1;
  delete newLL2;
  delete newLL3;

  return 0;

} // end of test

*/