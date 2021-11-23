// Written By: Seth Kiefer
// IDE: Visual Studio
#pragma once
#ifndef BST_ADT_H
#define BST_ADT_H
#include<string>
#include<iostream>
#include "SearchObject.h"
#include "Heap.h"

template<class B>
class bTree {
private:




	struct TreeNode {
		B key;
		TreeNode* left = NULL;
		TreeNode* right = NULL;
	};
	int year;
	TreeNode* root;
	int count;


	void orderedDisplay(TreeNode*); //overloaded display function that is only to be called by the other display function
	void print2DUtil(TreeNode*, int);
	void broadSearchUtility(Query*, void(*display)(B&), TreeNode*, bool&);
	void listByModelUtility(int(*compare)(Car&, Car&), Heap<Car>*, TreeNode*);
	void recursiveDestruction(TreeNode* pCur) {if (pCur) { recursiveDestruction(pCur->left); recursiveDestruction(pCur->right); delete pCur; } }
	void findLongestPathUtility(TreeNode* pPre, TreeNode* pCur, int depth);
public:
	static B farKey;
	static int maxDepth;
	//constructor & destructor
	bTree() { root = NULL; count = 0; year = -1; };
	~bTree() { recursiveDestruction(root); };

	void insert(B*); //adds a new node into the tree with a given key

	bool remove(std::string); //removes a node from the tree with a given key

	bool specificSearch(std::string, void(*display)(Car&));

	void orderedDisplay(); //displays the tree in order of keys from smallest to largest
	void broadSearch(Query*, void(*display)(B&), bool&); //displays the tree in order of keys from smallest to largest
	void listByModel(int(*compare)(Car&, Car&), Heap<Car>*);
	void print2D();
	void findLongestPath();
	void displayFarthest() { std::cout << "longest collision chain is " << maxDepth << " and leads to " << farKey << std::endl; }

	void setYear(int y) { year = y; };

	int getCount() const { return count; }
	int getYear() const { return year; }
  
};
#endif