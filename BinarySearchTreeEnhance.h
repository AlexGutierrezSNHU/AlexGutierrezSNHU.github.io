#include <algorithm>
#include <climits>
#include <iostream>
#include <string> 
#include <time.h>
#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// Forward declarations
double strToDouble(string str, char ch);

// Global data structure to hold variable inputs used in testing performance of
// developed algorithm. 
struct Bid {
    string bidId; 
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// Global Data Structure to map node pointes for binary search tree algorithm
struct Node { 
		Bid key; 
		Node* left; 
		Node* right; 
	};



/**
 * Defines the class containing data members and methods to implement a binary search tree.
 * The class utilizes private classes in order to generate the nodes and pointers for traversing
 * the binary search tree. Methods used to modify the loaded container are  public. 
 */
class BinarySearchTree {

private:
	Node* root; 
	Bid findKey (Node* node, string bidId);
	Node* findMin(Node* node); 
	void addNode(Node* node, Bid bid); 
	void inOrder(Node* node); 
	void removeKey(Node* node, Node* matchKey,bool left);
	struct Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree(); 
    Bid Search(string bidId); 
    Node* newNode(Bid bid); 
	virtual ~BinarySearchTree(); 
    void InOrder(); 
    void Insert(Bid bid); 
    void Remove(string bidId); 

};

// Creates a new node with a key, left, and right pointers. 
// Returns new node when called.  

Node *BinarySearchTree::newNode (Bid bid)  
			{
				Node* n= new Node; 
				n -> key = bid; 
				n -> left = NULL; 
				n -> right = NULL; 
				return n; 
			};

// Default constructor to initalize binary search tree Root Node
 
BinarySearchTree::BinarySearchTree() {
   	root = NULL; 

}


// Default destructor to remove all nodes including root node when called. 

BinarySearchTree::~BinarySearchTree() {

	Node* delPtr; 
	if (root != NULL){ 
		if (root -> left != NULL)
		{
			root = root -> left;
		}
		if(root -> right != NULL)
		{
			root = root -> right;
		}
	delPtr = root;
	delete delPtr;
	}
}

//Method to return bid value from passed string value if found. 

Bid BinarySearchTree::Search (string bidId){
	Bid bid = findKey(root, bidId); 
	return bid; 
}

// Method to Traverse Binary Search tree in order if root value exsists

void BinarySearchTree::InOrder() {
	if (root != NULL)
	   {
		inOrder(root);
	   }
}



// Method to add new bid and new leaf node by calling private function addNode. 
// Function will pass root node and bid to be added to binary search tree.  

void BinarySearchTree::Insert(Bid bid) { 
    	addNode(root, bid); 
}

// Method to remove bid and leaf node by calling private function removeNode. 
// Function will pass root node and bid to be deleted from binary search tree.

void BinarySearchTree::Remove(string bidId) {
   	removeNode(root, bidId); 
}

// Method to find bid key if rood node exsists, algorithm will traverse binary search tree utilizing 
// a recursive call until the bid is found. If Node does not exsist method will exit.

Bid BinarySearchTree::findKey (Node* node, string bidId) { //Private funstion findKey
	Bid bid; 
	    if (node != NULL) 
	    {
	    	if (node->key.bidId == bidId) 
	    	{
	    		return  node-> key; 
	    	}
	    	else
	    	{
	    		if (bidId < node->key.bidId) 
	    		{
	    			return findKey(node -> left, bidId); 
	    		}
	    		else 
	    		{
	    			return findKey(node -> right, bidId); 
	    		}
	    	}
	    }
	    else
	    { 
    }
}


/**
 * Add a bid to exsisting node through recursive call if root node exsists.
 * If root node does not exsists, new root node will be created
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
 
void BinarySearchTree::addNode(Node* node, Bid bid) { 

	if (root == NULL) /
	{
	       root= newNode(bid); 
	}
	else if (bid.bidId < node -> key.bidId)
	{
		if (node ->left != NULL)  
		{
			addNode(node->left, bid); 
		}
		else
		{
			node-> left = newNode(bid); 
		}
	}

	else if (bid.bidId > node -> key.bidId) 
		if (node ->right != NULL)
			{
			addNode(node-> right, bid);
			}
		else
		{
			node-> right = newNode(bid);
		}
	}
}

// Function to Traverse binary search tree from left most leaf to right most leaf  if root node exsists. If root node exsits 
// function will print formatted leaf node bid information to console.  

void BinarySearchTree::inOrder(Node* node) {
	if (root != NULL) 
	        if (node -> left != NULL) 
	        {
	        	inOrder(node -> left);
	        }
	        
	        cout << node-> key.bidId + " | " << node-> key.title + " | " << node-> key.amount <<  " | " + node-> key.fund << endl;
	        if (node -> right != NULL) 
	        {
	        	inOrder(node -> right);
	        }
	    }
	   else
	    {
	        return; 
	    }
}

// Function to remove leaf or root node from biinary search tree and re-associates node pointers to
// maintain binary search tree intact for further access or manipulation. 

struct Node* BinarySearchTree::removeNode(Node *root, string bidId){


	  if (root == NULL)
	  {
		  return root;
	  }
	  if (bidId < root -> key.bidId)
	  {
		  root -> left = removeNode(root->left, bidId);
	  }
	  else if (bidId > root -> key.bidId)
	  {
		  root -> right = removeNode(root->right, bidId);
	  }

	  else{  
		  	 if (root -> left == NULL && root -> right == NULL) 
		  		 {
		  		 delete root; 
		  		 root = NULL; 
		  		 }

		  	 else if (root->left == NULL) 
			 {
				 Node *temp = root; 
				 root = root -> right; 
				 delete temp;
			 }

			 else if (root->right == NULL) 
	         {
				Node *temp = root;
				 root = root -> left;
				 delete temp;

	          }

			 else{
				 Node *temp = findMin(root->right); 
	             root -> key = temp -> key; 
	             root -> right = removeNode(root->right, temp -> key.bidId);
				 }
	  return root;
	  }
}

// Function that finds the minimum value in binary search tree by traversing left leaf node pointer 
// until the the pointer points to null returning the node value to the terminal. 

Node* BinarySearchTree::findMin(Node* root) 
{
	while(root->left != NULL)
		{
		root = root->left;
		}

	      return root;


/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 * Try and Catch statment is utilzied to check target location for file access
 *
 * Provided as Part of template for project
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    csv::Parser file = csv::Parser(csvPath);

    
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        /
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

           cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            
            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 *
 * Provided as part of template for Project
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}


// Main method allows used to test perfomrance and accuracy od data structures and algorithms. 
// Preliminary performance is tested using cpu clock ticks, performance will vary greatly depending
// on the specifications of the system being used. There is currently no timeout interupt in place. 


int main(int argc, char* argv[]) {

 
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "C:/Users/Alex Gutierrez/workspace/BinarySearchTree/src/eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            bst = new BinarySearchTree();

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

			cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; 
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; 

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
