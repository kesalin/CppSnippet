#ifndef __RED_BLACK_TREE_H__
#define __RED_BLACK_TREE_H__

enum RBColor{
	RB_Red,
	RB_Black,
};

struct RBNode 
{
	RBColor color;
	int key;
	RBNode* leftChild;
	RBNode* rightChild;
	RBNode* parent;
};

typedef RBNode* RBTree;

RBNode* RBTree_nil();

// 最小关键字元素
RBNode* RBTree_minimum(RBNode* node);

// 最大关键字元素
RBNode* RBTree_maximum(RBNode* node);

// 中序遍历中的前驱
RBNode* RBTree_predecessor(RBNode* node);

// 中序遍历中的后继
RBNode* RBTree_successor(RBNode* node);

void RBTree_insert(RBTree* tree, RBNode* node);

RBNode* RBTree_delete(RBTree* tree, RBNode* node);

RBNode* RBTree_search(const RBTree tree, int key);

void RBTree_print(RBTree tree, int her = 1);

#endif	// __RED_BLACK_TREE_H__