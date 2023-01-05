#include <string>

using namespace std;

class Node {
  public:
    string key;
    Node *left, *right, *parent;
    int height;
		int size;

    Node();
    Node(string);
		string print();
};

class AVL {
  public:
    Node* root;

		AVL();
    int balanceFactor(Node*);
		void update(Node*);
    Node* rotateLeft(Node*, Node*);
		Node* rotateRight(Node*, Node*);
    void insert(string);
    void insert(Node*, Node*);
		string inorder();
		string inorder(Node*);
		string preorder();
		string preorder(Node*);
		string heights();
		string sizes();

    void append(string);
    void append(Node*, Node*);

		int range(string, string);
		int range(Node*, string, string);
		int leftRange(Node*, string);
		int rightRange(Node*, string);

};
