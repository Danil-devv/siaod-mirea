﻿#include <stdio.h>
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <vector>
#include <random>
#include <map>
#include <queue>
#include <stack>

using namespace std;

struct Node {
	int data; // значение в вершине
	Node* parent; // указатель на родителя
	Node* left; // укзаатель на левого потомка
	Node* right; // указатель на правого потомка
	int color; // 1 -> красный, 0 -> черный
};

typedef Node* NodePtr;

class RBTree {
private:
	NodePtr root;
	NodePtr TNULL;

	void inOrderHelper(NodePtr node) {
		if (node != TNULL) {
			inOrderHelper(node->left);
			cout << node->data << " ";
			inOrderHelper(node->right);
		}
	}

	void fixInsert(NodePtr k) {
		NodePtr u;
		while (k->parent->color == 1) {
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left; 
				if (u->color == 1) {
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->left) {
						k = k->parent;
						rightRotate(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					leftRotate(k->parent->parent);
				}
			}
			else {
				u = k->parent->parent->right;

				if (u->color == 1) {
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->right) {
						k = k->parent;
						leftRotate(k);
					}
					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->color = 0;
	}

	void printHelper(NodePtr root, string indent, bool last) {
		if (root != TNULL) {
			cout << indent;
			if (last) {
				cout << "R----";
				indent += "     ";
			}
			else {
				cout << "L----";
				indent += "|    ";
			}

			string sColor = root->color ? "R" : "B";
			cout << root->data << "(" << sColor << ")" << endl;
			printHelper(root->left, indent, false);
			printHelper(root->right, indent, true);
		}
	}

	int findPathLengthHelper(NodePtr node, int val) {
		if (node == TNULL) return 0;
		if (node->data == val) return 1;
		
		int l = findPathLengthHelper(node->left, val);
		if (l != 0) return l + 1;

		l = findPathLengthHelper(node->right, val);
		if (l != 0) return l + 1;

		return 0;
	}

public:
	RBTree() {
		TNULL = new Node;
		TNULL->color = 0;
		TNULL->left = nullptr;
		TNULL->right = nullptr;
		root = TNULL;
	}

	void inorder() {
		inOrderHelper(this->root);
		cout << "\n";
	}

	NodePtr minimum(NodePtr node) {
		while (node->left != TNULL) {
			node = node->left;
		}
		return node;
	}

	void leftRotate(NodePtr x) {
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != TNULL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rightRotate(NodePtr x) {
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != TNULL) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->right) {
			x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	void insert(int key) {
		NodePtr node = new Node;
		node->parent = nullptr;
		node->data = key;
		node->left = TNULL;
		node->right = TNULL;
		node->color = 1;

		NodePtr y = nullptr;
		NodePtr x = this->root;

		while (x != TNULL) {
			y = x;
			if (node->data < x->data) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}

		node->parent = y;
		if (y == nullptr) {
			root = node;
		}
		else if (node->data < y->data) {
			y->left = node;
		}
		else {
			y->right = node;
		}

		if (node->parent == nullptr) {
			node->color = 0;
			return;
		}

		if (node->parent->parent == nullptr) {
			return;
		}

		fixInsert(node);
	}

	void prettyPrint() {
		if (root) {
			printHelper(this->root, "", true);
		}
	}

	void bfs() { 
		queue<NodePtr> q;
		q.push(this->root);

		while (!q.empty()) {
			NodePtr node = q.front(); q.pop();

			if (node == TNULL) continue;

			cout << node->data << " ";

			q.push(node->left);
			q.push(node->right);
		}

		cout << "\n";
		return;
	}

	float findAverage() {
		queue<NodePtr> q;
		float sum = 0;
		int count = 0;

		q.push(this->root);

		while (!q.empty()) {
			NodePtr node = q.front(); q.pop();

			if (node == TNULL) continue;

			sum += node->data;
			count++;

			q.push(node->left);
			q.push(node->right);
		}

		return sum / count;
	}

	int findPathLength(int val) {
		return findPathLengthHelper(this->root, val) - 1;
	}
};

int main() {
	RBTree bst;
	bst.insert(8);
	bst.insert(18);
	bst.insert(5);
	bst.insert(15);
	bst.insert(17);
	bst.insert(40);
	bst.insert(80);
	bst.prettyPrint();

	bst.inorder(); // симметричный обход
	bst.bfs(); // обход в ширину
	cout << bst.findAverage() << "\n"; // среднее арифметическое
	cout << bst.findPathLength(80) << "\n"; // поиск длины пути от корня до заданного числа
	return 0;
}
