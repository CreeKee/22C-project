#include "BST_ADT.hpp"
#include <iostream>

#include <string>

template<class B>
int bTree<B>::maxDepth = 0;

template<class B>
B bTree<B>::farKey;


/*
This function will take
and inputed value and
insert it into the
appropriate place in the
tree
*/
template<class B>
void bTree<B>::insert(B* val) {

    TreeNode* newNode = new TreeNode;
    TreeNode* pCur = root;
    TreeNode** pLR = &root;



    newNode->key = *val;
    newNode->left = NULL;
    newNode->right = NULL;

    while (pCur) {

        if (pCur->key > newNode->key) {
          //  std::cout << "moving left" << std::endl;
            pLR = &(pCur->left);
            pCur = pCur->left;

        }
        else {
           // std::cout << "moving right" << std::endl;
            pLR = &(pCur->right);
            pCur = pCur->right;
        }

    }

    
    *pLR = newNode;

    count++;
}

/*
given a certain key value
this function will attempt
to locate and delete the
appropriate node in the
tree
*/
template<class B>
bool bTree<B>::remove(std::string target) {
    TreeNode* pCur = root;
    TreeNode** pLR = &root;
    bool found = false;
    B tempKey;

 
    while (pCur) {
        if (pCur->key == target) {                      //If the target is found determine the case

            found = true;
            count--;

            if (!pCur->left && !pCur->right) {          //Case 1: both children of the located node are null
                delete pCur;
                *pLR = NULL;

            }
            else {
                if (pCur->left && !pCur->right) {       //Case 2: the right node is null and the left node is not
                    *pLR = pCur->left;
                    delete pCur;
                }
                else {
                    if (!pCur->left && pCur->right) {   //Case 3: the left node is null and the right is not
                        *pLR = pCur->right;
                        delete pCur;
                    }
                    else {                              //If all the previous checks fail then neither nodes are null
                        pCur = pCur->right;
                        while (pCur->left) {            //finds the successor
                            pCur = pCur->left;
                        }
                        tempKey = pCur->key;
                        remove(pCur->key.getID());
                        (*pLR)->key = tempKey;
                    }
                }
            
            }
            
            pCur = NULL;
        }

        else {
            if (pCur->key > target) {
                pLR = &(pCur->left);
                pCur = pCur->left;
            }
            else {

                pLR = &(pCur->right);
                pCur = pCur->right;
            }
        }

    }
    return found;
}

template<class B>
bool bTree<B>::specificSearch(std::string target, void(*display)(Car&)) {

    TreeNode* pCur = root;
    bool found = false;

    //use a simple BST seearch to locate the desired car node (searching by ID)
    while (pCur && !found) {
        if (pCur->key == target) {
            found = true;
        }
        else {
            if (pCur->key > target) {
                pCur = pCur->left;
            }
            else {
                pCur = pCur->right;
            }
        }
    }
    //if found then display the located node
    if (found == true) {
       // std::cout << "found" << std::endl;
        display(pCur->key);
    }

    return found;
}

template<class B>
void bTree<B>::orderedDisplay() {
        TreeNode* pCur = root;
        if (!pCur)
            return;


    orderedDisplay(pCur->left);
    std::cout << pCur->key << std::endl;
    orderedDisplay(pCur->right);
}
    

template<class B>
void bTree<B>::orderedDisplay(TreeNode* pCur) {
    if (!pCur) {
        return;
    }
    orderedDisplay(pCur->left);
    std::cout << pCur->key << std::endl;
    orderedDisplay(pCur->right);

}

template<class B>
void bTree<B>::broadSearch(Query* searchObject, void(*display)(B&), bool& found) {
    TreeNode* pCur = root;
    if (!pCur)
        return;
    
    broadSearchUtility(searchObject, display, pCur->left, found);
    if (*searchObject==pCur->key) {
        display(pCur->key);
        found = true;
    }
    broadSearchUtility(searchObject, display, pCur->right, found);
}

template<class B>
void bTree<B>::broadSearchUtility(Query* searchObject, void(*display)(B&), TreeNode* pCur, bool& found) {
    if (!pCur)
        return;

    broadSearchUtility(searchObject, display, pCur->left, found);
    if (*searchObject == pCur->key) {
        display(pCur->key);
        found = true;
    }
    broadSearchUtility(searchObject, display, pCur->right, found);
}


template<class B>
void bTree<B>::listByModel(int(*compare)(Car&, Car&), Heap<Car>* displayHeap) {
    TreeNode* pCur = root;
    if (!pCur)
        return;

   listByModelUtility(compare, displayHeap, pCur->left);
   displayHeap->insertHeap(pCur->key, compare);
   listByModelUtility(compare, displayHeap, pCur->right);
}

template<class B>
void bTree<B>::listByModelUtility(int(*compare)(Car&, Car&), Heap<Car>* displayHeap, TreeNode* pCur) {
    if (!pCur)
        return;

    listByModelUtility(compare, displayHeap, pCur->left);
    displayHeap->insertHeap(pCur->key, compare);
    listByModelUtility(compare, displayHeap, pCur->right);
}


template<class B>
void bTree<B>::print2D()
{
    // Pass initial space count as 0  
    print2DUtil(root, 0);
}


template<class B>
void bTree<B>::print2DUtil(TreeNode* root, int space)
{
    // Base case  
    if (root == NULL)
        return;

    // Increase distance between levels  
    space += count;

    // Process right child first  
    print2DUtil(root->right, space);

    // Print current node after space  
    // count  
    std::cout << std::endl;
    for (int i = count; i < space; i++)
        std::cout << " ";
    std::cout << root->key << "\n";

    // Process left child  
    print2DUtil(root->left, space);
}

template<class B>
void bTree<B>::findLongestPath() {
    int depth = 0;
    TreeNode* pCur = root;
    if (!pCur) {
        return;
    }

    findLongestPathUtility(pCur, pCur->left, depth+1);
    findLongestPathUtility(pCur, pCur->right, depth+1);

}

template<class B>
void bTree<B>::findLongestPathUtility(TreeNode* pPre, TreeNode* pCur, int depth) {
    if (!pCur) { 
        if (depth > maxDepth) {
            maxDepth = depth;
            farKey = pPre->key;
        }
        return;
    }
    findLongestPathUtility(pCur, pCur->left, depth+1);
    findLongestPathUtility(pCur, pCur->right, depth+1);

}
