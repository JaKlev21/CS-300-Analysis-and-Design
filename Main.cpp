//============================================================================
// Name        : Project Two Binary Search Tree.cpp
// Author      : Jonathan Kleven
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Project Two 
//============================================================================

#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Course {
    string courseId; // unique identifier
    string courseTitle;    
    vector<string> preReqs;
    
};

// Internal structure for tree node
struct Node {
    Course bid;
    Node* left; //[Jonathan Kleven]* was against the left not the Node
    Node* right;//[Jonathan Kleven]* was against the right not the Node

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Course aCourse) : Node() {
        this->bid = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void preOrder(Node* node);
    void postOrder(Node* node);
    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PreOrder();
    void PostOrder();
    void Insert(Course course);
    void Remove(string courseId);
    Course Search(string courseId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //initialize housekeeping variables
    //[Jonathan Kleven] Completed 
    //[Jonathan Kleven] This creates a blank Tree and sets the first node to null
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // In order root
    // [Jonathan Kleven] Completed
    // [Jonathan Kleven] This is a public call of a private recursive function
    // call inOrder fuction and pass root 
    this->inOrder(root);
   
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // Post order root
    // [Jonathan Kleven] Completed
    // [Jonathan Kleven] This is a public call of a private recursive function
    // postOrder root
    this->postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // Pre order root
    // [Jonathan Kleven] Completed
    // [Jonathan Kleven] This is a public call of a private recursive function
    // preOrder root
    this->preOrder(root);
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Course course) {
    // Implement inserting a bid into the tree
    // [Jonathan Kleven] Completed
    // [Jonathan Kleven] This is a public call with conditions to a private recursive function
    // [Jonathan Kleven] If the tree is empty create a new node passing in the data Else call recursive function addNode
    // if root equal to null ptr
    if (root == nullptr) {
        // root is equal to new node bid
        root = new Node(course);
    }
    // else
    else {
        // add Node root and bid
        this->addNode(root, course); //deleted this->addnode

    }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // Implement removing a bid from the tree
    // [Jonathan Kleven] Completed
    // [Jonathan Kleven] This is a public call of a private recursive function
    // remove node root bidID
    this->removeNode(root, bidId);
}

/**
 * Search for a bid
 */
Course BinarySearchTree::Search(string bidId) {
    // Implement searching the tree for a bid
    // [Jonathan Kleven] Completed
    // [Jonathan Kleven] Create a temp current node, loop through the nodes and compare 
    // the values of the node with current and look at each of the nodes data to find the one being searched
    // set current node equal to root
    Node* currentNode = root;

    // keep looping downwards until bottom reached or matching bidId found
    while (currentNode != nullptr) {
        // if match found, return current bid
        if (currentNode->bid.courseId.compare(bidId) == 0) {
            return currentNode->bid;
        }
        // if bid is smaller than current node then traverse left
        if (bidId.compare(currentNode->bid.courseId) < 0) {
            currentNode = currentNode->left;
        }
        // else larger so traverse right
        else {
            currentNode = currentNode->right;
        }
    }
    Course bid;
    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Course bid) {
    // Implement inserting a bid into the tree
    // [Jonathan Kleven] Completed
    // [Jonathan Kleven] If data is less than parent node add new data 
    // to left child checking to see if child exists and comparing new data
    // Else looking to the right child node if new data is greater than
    // if node is larger then add to left
    if (node->bid.courseId.compare(bid.courseId
    ) > 0) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(bid);
        }
        // else recurse down the left node
        else {
            this->addNode(node->left, bid); //deleted this->addNode
        }
    }
        // else
    else {
        // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(bid);
        }
        //else
        else {
            // recurse down the left node
            this->addNode(node->right, bid);//deleted this->addNode
        }
    }
}
/**
 * Remove a bid from some node (recursive)
 */
Node* BinarySearchTree::removeNode(Node* node, string bidId) {
    // [Jonathan Kleven] Removing a bid from the tree was omitted from starter code
    // From Module 5 Announcements added comments
    // If the node is null return, if data is less then recurse though left side
    // If data is greater then recurse through right side
    // then look for child node and identify which (left or right) to determine which to remove
    // When there are two children a temp node is created to move the right child into the parent node position

    // if node is nullptr return node
    if (node == nullptr) {
        return node;
    }

    // else if bidId < current bid recurse down the left subtree
    else if (bidId.compare(node->bid.courseId) < 0) {
        node->left = removeNode(node->left, bidId);
    }

    // else if bidId > current bid recurse down the right subtree
    else if (bidId.compare(node->bid.courseId) > 0) {
        node->right = removeNode(node->right, bidId);

    }
    // else 
    else {
        // if no children so node is a leaf node
        if (node->left == nullptr && node->right == nullptr) {
            // delete node then set node to nullptr
            delete node;
            node = nullptr;
        }
        // else if there's one child to the left
        else if (node->left != nullptr && node->right == nullptr) {
            // store node values in temp, set node to child to the left, delete temp node 
            Node* tempNode = node;
            node = node->left;
            delete tempNode;
        }
        // else if one child to the right
        else if (node->right != nullptr && node->left == nullptr) {
            // store node values in temp, set node to child to right, delete temp node
            Node* tempNode = node;
            node = node->right;
            delete tempNode;
        }
        // else there are two children
        else {
            // store right node in temp
            Node* tempNode = node->right;

           // traverse left to find the minimum (while loop)
            while (tempNode->left != nullptr) {
                // set temp to left
                tempNode = tempNode->left;
            }

           // set bid to temp (minimum)
            node->bid = tempNode->bid;
           // recurse down the right subtree
            node->right = removeNode(node->right, tempNode->bid.courseId);
        }
    }
    //return node
    return node;
}
void BinarySearchTree::inOrder(Node* node) {
    // In order root
    // [Jonathan Kleven] Completed
    // [Jonathan Kleven] In order means to look at the furthest left node
    // print that node, then look at and print the parent then look at and print the right
    // moving from lowest tree level to highest printing the furthest right node last
    // if node is not equal to null ptr
    // [Jonathan Kleven] Zybooks 6.7.1
    if (node != nullptr) {
          
        //InOrder not left
        inOrder(node->left);
          
        //output course and title
        //[Jonathan Kleven] Display the course and title in order smallest to largest
        cout << node->bid.courseId << ", "
            << node->bid.courseTitle 
            << endl;
        
          
        //InOder right
        inOrder(node->right);
      }
      
      
      
}
void BinarySearchTree::postOrder(Node* node) {
    // Post order root
    // [Jonathan Kleven] Completed
    // [Jonathan Kleven] Post order means to look at the left side first 
    // then print the lowest level leaf nodes followed by its parent
    // When it reaches the root it will traverse the right side
    //if node is not equal to null ptr
    if (node != nullptr) {
        //postOrder left
        postOrder(node->left);
        //postOrder right
        postOrder(node->right);
        //output bidID, title, amount, fund
        cout << node->bid.courseId << ": "
            << node->bid.courseTitle
            << endl;
    }

}

void BinarySearchTree::preOrder(Node* node) {
    // Pre order root
    // [Jonathan Kleven] Completed
    // [Jonathan Kleven] PreOrder means to start at the root then 
    // look at the left side Print the parent, then the left child then the right child
    //if node is not equal to null ptr
    if (node != nullptr) {
        //output bidID, title, amount, fund
        cout << node->bid.courseId << ": "
            << node->bid.courseTitle
            << endl;
        //postOrder left
        preOrder(node->left);
        //postOrder right
        preOrder(node->right);
    }
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Course bid) {
    //[Jonathan Kleven] Modified displayBid to print out 
    //Courses that are searched for and if found return the course and title
    cout << bid.courseId << ", " << bid.courseTitle << endl;
    //[Jonathan Kleven] Added condition if no prereqs then print NONE
    if (bid.preReqs.size() == 0) {
        cout << "Prerequisites: None";
    }
    //[Jonathan Kleven] If prereqs are found go through and print them on the same line
    else {
        cout << "Prerequisites: ";
        string delim = "";
        for (int i = 0; i < bid.preReqs.size(); ++i) {
            cout << delim << bid.preReqs.at(i);
            delim = ", ";
        }
    }
    cout << endl;
    cout << endl;
    return;
}
/** [Jonathan Kleven]
* Search Vector function to determine if PreReqs are valid
* Search the file at location [i][0] for if prereq matches
* If it matches return true
* Else return false
* BONUS Something I had merely a concept of through the milestones
* BONUS and pseudocode is now working code!
*/
bool searchVector(string csvPath, string preReqData) {
    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // loop to read rows of a CSV file
    for (unsigned int i = 0; i < file.rowCount(); i) {
        if (file[i][0] == preReqData) {
            return true;
        }
        if (file[i][0] != preReqData) {
            i++;
        }
        else {
            return false;
        }
    }
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Course bid;
            bid.courseId = file[i][0];
            bid.courseTitle = file[i][1];

            //[Jonathan Kleven] Added for loop to add preReqs
            //[Jonathan Kleven] make sure that course ID's that are not listed or invalid are not added to PreReqs
            /*[Jonathan Kleven] in my test data I added a preReq that was not on the list ex CSCI999
            * With this if statement and searchVector method I successfully omitted CSCI999
            * from being added to the BST
            * Added to TestData CSCI999 and BST added a node and kept prereq noted above
            */
            for (unsigned int j = 2; j < file[i].size(); j++) {
                if (searchVector(csvPath,file[i][j]) == true) {
                    bid.preReqs.push_back(file[i][j]);
                }
            }
            
            // push this bid to the end
            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}


/** [Jonathan Kleven]
* Function for input validation of the search method
* Take the input assumed its a string and make all characters upper case
* return the input in a formatted upper case string
*/
string stringToUpper(string userInput) {
    for (int i = 0; i < userInput.size(); ++i) {
        userInput[i] = toupper(userInput[i]);
    }
    return userInput;
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "CSCI400"; // [Jonathan Kleven] Added command line argument CSCI400
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "TestData.csv"; 
        bidKey = "CSCI400"; // [Jonathan Kleven] Added command line argument CSCI400
    }

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course bid;

    //Define searchCourse variable
    string searchCourse;

    int choice = 0;

    //[Jonathan Kleven] moved out of the while loop based on Project two sample output
    cout << "Welcome to the course planner.\n" << endl;

    while (choice != 9) {
        cout << "  1. Load Data Structure." << endl;
        cout << "  2. Print Course List." << endl;
        cout << "  3. Print Course." << endl;
        cout << "  9. Exit\n" << endl;
        cout << "What would you like to do? ";
        cin >> choice;
                
        
        switch (choice) {

        case 1:
                        
            // Complete the method call to load the bids
            loadBids(csvPath, bst);            
            break;

        case 2:
            cout << "Here is a sample schedule:\n" << endl;
            bst->InOrder(); //[Jonathan Kleven] Tested InOrder, PostOrder, and PreOrder; InOrder prints in alpanumeric from lowest to highest
            cout << endl;
            break;

        case 3:
            cout << "What course do you want to know about? ";
            
            //TODO Add in input validation            
            cin >> searchCourse;
            
            //[Jonathan Kleven] method to make input upper case
            bid = bst->Search(stringToUpper(searchCourse));

            if (!bid.courseId.empty()) {
                displayBid(bid);
            }
            else {
                cout << "Course " << stringToUpper(searchCourse) << " was not found." << endl;
            }

            break;
        
        //[Jonathan Kleven] Added case for 9 to allow for default to handle menu input validation
        case 9:
            break;

        default:
            cout << choice << " is not a valid option.\n" << endl;

        }
    }

    cout << "Thank you for using the course planner!" << endl;

	return 0;
}
