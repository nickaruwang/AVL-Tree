#include <iostream>
#include <string>
#include <queue>
#include "utils.h"

using namespace std;

Node :: Node() {
  key = "";
  left = right = parent = NULL;
	height = 1;
	size = 1;
}

Node :: Node(string k) {
  key = k;
  left = right = parent = NULL;
	height = 1;
	size = 1;
}

string Node :: print() {
	string p, l, r;
	p = l = r = "-";
	if (parent) {
		p = parent->key;
	}
	if (left) {
		l = left->key;
	}
	if (right) {
		r = right->key;
	}
	return key + " " + p + " " + l + " " + r;
}

AVL :: AVL() {
	root = NULL;
}

int AVL :: balanceFactor(Node* n) {
	int r = 0;
	int l = 0;
	if (n->left) {
		l = n->left->height;
	}
	if (n->right) {
		r = n->right->height;
	}
	return r - l;
}

void AVL :: update(Node* n) {
	if (n == NULL) {
		return;
	}
	// update height
	int lh = 0, rh = 0;
	int ls = 0, rs = 0;
	if (n->left) {
		lh = n->left->height;
		ls = n->left->size;
	}
	if (n->right) {
		rh = n->right->height;
		rs = n->right->size;
	}
	n->height = max(lh, rh) + 1;
	n->size = ls + rs + 1;
}

Node* AVL :: rotateRight(Node* target, Node* dest) {
	if (balanceFactor(target) > 0) {
		target = rotateLeft(target->right, target);
	}

	Node* p = dest->parent;
	Node* c = target->right;
	target->right = dest;
	dest->left = c;
	dest->parent = target;
	if (p == NULL) {
		root = target;
	}
	else if (dest == p->right) {
		p->right = target;
	}
	else {
		p->left = target;
	}
	target->parent = p;
	if (c) {
		c->parent = dest;
	}
	update(dest);
	update(target);
	return target;
}

Node* AVL :: rotateLeft(Node* target, Node* dest) {
	if (balanceFactor(target) < 0) {
		target = rotateRight(target->left, target);
	}

	Node* p = dest->parent;
	Node* c = target->left;
	target->left = dest;
	dest->right = c;
	dest->parent = target;
	if (p == NULL) {
		root = target;
	}
	else if (dest == p->right) {
		p->right = target;
	}
	else {
		p->left = target;
	}
	target->parent = p;
	if (c) {
		c->parent = dest;
	}
	update(dest);
	update(target);
	return target;
}

string AVL :: inorder() {
	return inorder(root);
}

string AVL :: inorder(Node* start) {
	if (start == NULL) {
		return "";
	}
	string l = inorder(start->left);
	string out = start->key;
	string r = inorder(start->right);
	if (l.length() > 0) {
		out = l + " " + out;
	}
	if (r.length() > 0) {
		out = out + " " + r;
	}
	return out;
}


string AVL :: preorder() {
	return preorder(root);
}

string AVL :: preorder(Node* start) {
	if (start == NULL) {
		return "";
	}
	string l = preorder(start->left);
	string out = start->key;
	string r = preorder(start->right);
	if (l.length() > 0) {
		out = out + " " + l;
	}
	if (r.length() > 0) {
		out = out + " " + r;
	}
	return out;
}

string AVL :: heights() {
	if (root == NULL) {
		return "0";
	}
	string ret = "";
	queue<Node*> q;
	q.push(root);
	while (q.size() > 0) {
		Node* f = q.front();
		q.pop();
		if (f == NULL) {
			continue;
		}
		ret += to_string(f->height) + " ";
		q.push(f->left);
		q.push(f->right);
	}
	return ret;
}

string AVL :: sizes() {
	if (root == NULL) {
		return "0";
	}
	string ret = "";
	queue<Node*> q;
	q.push(root);
	while (q.size() > 0) {
		Node* f = q.front();
		q.pop();
		if (f == NULL) {
			continue;
		}
		ret += to_string(f->size) + " ";
		q.push(f->left);
		q.push(f->right);
	}
	return ret;
}

void AVL :: insert(string k) {
	Node* n = new Node(k);
	if (root == NULL) {
		root = n;
	}
	else {
		insert(root, n);
	}
}

void AVL :: insert(Node* start, Node* in) {
	if (start->key == in->key) {
		return;
	}
	if (in->key > start->key) {
		if (start->right == NULL) {
			start->right = in;
			in->parent = start;
			// propagateHeight(in);
		}
		else {
			insert(start->right, in);
		}
	}
	else {
		if (start->left == NULL) {
			start->left = in;
			in->parent = start;
			// propagateHeight(in);
		}
		else {
			insert(start->left, in);
		}
	}
	update(start);
	if (balanceFactor(start) > 1) {
		rotateLeft(start->right, start);
	}
	else if (balanceFactor(start) < -1) {
		rotateRight(start->left, start);
	}
}

void AVL :: append(string s) {
	Node* n = new Node(s);
	if (root == NULL) {
		root = n;
	}
	else {
		append(root, n);
	}
}

void AVL :: append(Node* start, Node* in) {
	if (in->key > start->key) {
		if (start->right == NULL) {
			start->right = in;
			in->parent = start;
		}
		else {
			append(start->right, in);
		}
	}
	else {
		if (start->left == NULL) {
			start->left = in;
			in->parent = start;
		}
		else {
			append(start->left, in);
		}
	}
}

int AVL :: range(string l, string r) {
	return range(root, l, r);
}

int AVL :: range(Node* start, string l, string r) {
	if (start == NULL) {
		return 0;
	}
	if (start->key < l) {
		return range(start->right, l, r);
	}
	else if (start->key > r) {
		return range(start->left, l, r);
	}
	else {
		int lr = leftRange(start->left, l);
		int rr = rightRange(start->right, r);
		return lr + rr + 1;
	}
}

int AVL :: leftRange(Node* start, string l) {
	if (start == NULL) {
		return 0;
	}
	if (start->key < l) {
		return leftRange(start->right, l);
	}
	else {
		int nodes = 0;
		if (start->right) {
			nodes = start->right->size;
		}
		return leftRange(start->left, l) + nodes + 1;
	}
}

int AVL :: rightRange(Node* start, string r) {
	if (start == NULL) {
		return 0;
	}
	if (start->key > r) {
		return rightRange(start->left, r);
	}
	else {
		int nodes = 0;
		if (start->left) {
			nodes = start->left->size;
		}
		return rightRange(start->right, r) + nodes + 1;
	}
}
