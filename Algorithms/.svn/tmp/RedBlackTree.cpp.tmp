#include "RedBlackTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

static RBNode RBNode_Nil = {RB_Black, 0, 0, 0, 0};

RBNode* RBTree_nil()
{
	return &RBNode_Nil;
}

void RBTree_print(RBTree tree, int her)
{
	int i;
	RBNode* node = tree;

	assert(node);

	if (node != &RBNode_Nil) {
		for (i = 0; i < her; i++) {
			printf(" ");
		}
		printf("第 %d 层， %d(%c)\n",
			her, node->key, node->color == RB_Black ? 'B' : 'R');

		if (node->leftChild != &RBNode_Nil) {
			RBTree_print(node->leftChild, her + 1);
		}

		if (node->rightChild != &RBNode_Nil) {
			RBTree_print(node->rightChild, her + 1);
		}
	}
}

// 最小关键字元素
RBNode* RBTree_minimum(RBNode* node)
{
	assert(node);

	RBNode* temp = node;
	while (temp->leftChild != &RBNode_Nil) {
		temp = temp->leftChild;
	}

	return temp;
}


// 最大关键字元素
RBNode* RBTree_maximum(RBNode* node)
{
	assert(node);

	RBNode* temp = node;
	while (temp->rightChild != &RBNode_Nil) {
		temp = temp->rightChild;
	}

	return temp;
}

// 中序遍历中的前驱
RBNode* RBTree_predecessor(RBNode* node)
{
	assert(node);

	RBNode* child = node->leftChild;

	// 没有左孩子，返回自身
	if (child == &RBNode_Nil) {
		return node;
	}

	// 只有左孩子，则左孩子是其直接前驱
	else if (child->rightChild == &RBNode_Nil) {
		return child->leftChild;
	}

	// 左右孩子均有，则右孩子树中最大的元素为其直接前驱
	else {
		return RBTree_maximum(child->rightChild);
	}
}

// 中序遍历中的后继
RBNode* RBTree_successor(RBNode* node)
{
	// 有右孩子，则右孩子树中最小的元素为其直接后继
	if (node->rightChild != &RBNode_Nil) {
		return RBTree_minimum(node->rightChild);
	}

	// 没有右孩子，向上找到的第一个左分支节点为其直接后继，
	// 即 node 为其直接后继的左孩子树中的最大元素。
	RBNode* temp = node;
	RBNode* parent = temp->parent;

	while (parent != &RBNode_Nil && temp == parent->rightChild) {
		temp = parent;
		parent = temp->parent;
	}

	return parent;
}

RBNode* RBTree_search(const RBTree tree, int key)
{
	RBNode* node = tree;

	while (node != &RBNode_Nil) {
		if (node->key == key) {
			return node;
		}

		else if (node->key < key) {
			node = node->rightChild;
		}
		else {
			node = node->leftChild;
		}
	}

	return &RBNode_Nil;
}

// 左旋
//            node                        right
//           /    \                      /     \
//          a    right     -->         node     c
//              /     \               /    \
//             b       c             a      b
//
void RBTree_left_rotate(RBTree* tree, RBNode* node)
{
	assert(node->rightChild && (*tree)->parent == &RBNode_Nil);

	RBNode* right = node->rightChild;

	// set b
	node->rightChild = right->leftChild;
	if (right->leftChild != &RBNode_Nil) {
		right->leftChild->parent = node;
	}

	right->parent = node->parent;
	if (node->parent == &RBNode_Nil) {
		*tree = right;
	}
	else if (node->parent->leftChild == node) {
		node->parent->leftChild = right;
	}
	else {
		node->parent->rightChild = right;
	}

	right->leftChild = node;
	node->parent = right;
}

// 右旋
//            node                  left
//           /    \                /    \
//         left    c     -->      a     node
//        /     \                      /    \
//       a       b                    b      c
//
void RBTree_right_rotate(RBTree* tree, RBNode* node)
{
	assert(node->leftChild && (*tree)->parent == &RBNode_Nil);

	RBNode* left = node->leftChild;

	// set b
	node->leftChild = left->rightChild;
	if (left->rightChild != &RBNode_Nil) {
		left->rightChild->parent = node;
	}

	left->parent = node->parent;
	if (node->parent == &RBNode_Nil) {
		*tree = left;
	}
	else if (node->parent->leftChild == node) {
		node->parent->leftChild = left;
	}
	else {
		node->parent->rightChild = left;
	}

	left->rightChild = node;
	node->parent = left;
}

// 插入调整
void RBTree_insert_fixup(RBTree* tree, RBNode* node)
{
	assert(tree && node);

	RBNode* parent = NULL;
	RBNode* uncle = NULL;
	RBNode* grand = NULL;
	RBNode* temp = NULL;

	parent = node->parent;
	while (parent->color == RB_Red) {
		// 根据红黑树性质，以及 node 的父亲的颜色为红色，
		// 可以肯定 node 的祖父节点一定存在
		grand = parent->parent;

		// 确定叔父节点
		if (parent == grand->leftChild) {
			uncle = grand->rightChild;

			// case 1: 叔父节点为红色
			//         grand(B)        new node  ->    grand(R)
			//         /     \                         /      \
			//   parent(R)    uncle(R)    -->     node(B)   uncle(B)
			//   /     \      /  \                /   \        /  \
 			//  a    node(R) d    e          parent  node(R)  d    e
			//       /   \                          /   \
			//      b     c                        b     c
			//
			if (uncle->color == RB_Red) {
				parent->color = RB_Black;
				uncle->color = RB_Black;
				grand->color = RB_Red;
				node = grand;
				parent = node->parent;
			}

			// case 2, case 3：叔父节点为黑色
			//         case 2     --->    case 3         -->  done
			//                      parent is as new node
			//         grand(B)          grand(B)            node(B)
			//         /     \           /      \           /      \
 			//   parent(R)    d       node(R)   d      parent(R)  grand(R)
			//   /     \               /     \           /  \      /   \
			//  a    node(R)      parent(R)   c         a    b    c     d
 			//       /   \         /  \
			//      b     c       a    b
			//
			else {
				// 将 case 2 装换成 case 3
				// 注意：转换到 case 3之后， parent 为case 2中的 node，
				// node 为 case 2 中的 parent
				if (parent->rightChild == node) {
					RBTree_left_rotate(tree, parent);
					temp = parent;
					parent = node;
					node = temp;
				}

				// case 3
				parent->color = RB_Black;
				grand->color = RB_Red;

				RBTree_right_rotate(tree, grand);
			}
		}
		else {
			// 与上面的情况对称
			uncle = grand->leftChild;

			if (uncle->color == RB_Red) {
				parent->color = RB_Black;
				uncle->color = RB_Black;
				grand->color = RB_Red;
				node = grand;
				parent = node->parent;
			}

			else {
				// 将 case 2 装换成 case 3
				if (parent->leftChild == node) {
					RBTree_right_rotate(tree, parent);
					temp = parent;
					parent = node;
					node = temp;
				}

				// case 3
				parent->color = RB_Black;
				grand->color = RB_Red;

				RBTree_left_rotate(tree, grand);
			}
		}
	}

	(*tree)->color = RB_Black;
}

// 将节点 node 插入树 tree 内，然后将 node 着色为红色，此时，树可能不再
// 满足红黑树性质，因此调用 RBTree_insert_fixup 来对节点重新着色调整。
void RBTree_insert(RBTree* tree, RBNode* node)
{
	assert(tree && node);

	RBNode* parent = &RBNode_Nil;
	RBNode* temp = *tree;

	// 像二叉树一样，在树中查找适当的位置插入
	while (temp != &RBNode_Nil) {
		parent = temp;

		if (node->key < temp->key) {
			temp = temp->leftChild;
		}
		else {
			temp = temp->rightChild;
		}
	}

	node->parent = parent;

	// 树为空
	if (parent == &RBNode_Nil) {
		*tree = node;
	}
	else if (node->key < parent->key) {
		parent->leftChild = node;
	}
	else {
		parent->rightChild = node;
	}

	// 为节点着色
	node->leftChild = &RBNode_Nil;
	node->rightChild = &RBNode_Nil;
	node->color = RB_Red;

	// 调整树使之满足红黑树性质
	RBTree_insert_fixup(tree, node);
}

// 删除调整
void RBTree_delete_fixup(RBTree* tree, RBNode* node)
{
	RBNode* brother = NULL;
	RBNode* parent = NULL;

	while (node != *tree && node->color == RB_Black) {
		parent = node->parent;

		// 确定兄弟节点
		if (node == parent->leftChild) {
			brother = parent->rightChild;

			// case 1: 兄弟节点为红色
			if (brother->color == RB_Red) {
				brother->color = RB_Black;
				parent->color = RB_Red;

				RBTree_left_rotate(tree, parent);

				brother = node->parent->rightChild;
			}

			// case 2: 兄弟节点的两孩子均为黑色
			if (brother->leftChild->color == RB_Black
				&& brother->rightChild->color == RB_Black) {
					brother->color = RB_Red;
					node = parent;
			}

			else {
				// case 3: 兄弟节点的左孩子为红色，右孩子为黑色
				if (brother->rightChild->color == RB_Black) {
					brother->leftChild->color = RB_Black;
					brother->color = RB_Red;

					RBTree_right_rotate(tree, brother);

					brother = node->parent->rightChild;
				}

				// case 4:兄弟节点的右孩子为红色
				brother->color = parent->color;
				parent->color = RB_Black;
				brother->rightChild->color = RB_Black;

				RBTree_left_rotate(tree, parent);

				node = *tree;
			}
		}
		else {
			brother = parent->leftChild;

			// case 1: 兄弟节点为红色
			if (brother->color == RB_Red) {
				brother->color = RB_Black;
				parent->color = RB_Red;

				RBTree_right_rotate(tree, parent);

				brother = parent->leftChild;
			}

			// case 2: 兄弟节点的两孩子均为黑色
			if (brother->leftChild->color == RB_Black
				&& brother->rightChild->color == RB_Black) {
					brother->color = RB_Red;
					node = parent;
			}

			else {
				// case 3: 兄弟节点的左孩子为红色，右孩子为黑色
				if (brother->rightChild->color == RB_Black) {
					brother->leftChild->color = RB_Black;
					brother->color = RB_Red;

					RBTree_left_rotate(tree, brother);

					brother = parent->rightChild;
				}

				// case 4:兄弟节点的右孩子为红色
				brother->color = parent->color;
				parent->color = RB_Black;
				brother->leftChild->color = RB_Black;

				RBTree_right_rotate(tree, parent);

				node = *tree;
			}
		}
	}

	node->color = RB_Black;
}

// 删除
RBNode* RBTree_delete(RBTree* tree, RBNode* node)
{
	RBNode* successor = NULL;
	RBNode* temp = NULL;

	// 确定后继结点
	if (node->leftChild == &RBNode_Nil || node->rightChild == &RBNode_Nil) {
		successor = node;
	}
	else {
		successor = RBTree_successor(node);
	}

	if (successor->leftChild != &RBNode_Nil) {
		temp = successor->leftChild;
	}
	else {
		temp = successor->rightChild;
	}

	// 用后继替换节点，然后删除后继结点
	temp->parent = successor->parent;

	if (successor->parent == &RBNode_Nil) {
		*tree = temp;
	}
	else {
		if (successor == successor->parent->leftChild) {
			successor->parent->leftChild = temp;
		}
		else {
			successor->parent->rightChild = temp;
		}
	}

	if (successor != node) {
		node->key = successor->key;
	}

	// 如果删除的后继节点是黑色的，则不满足红黑树性质，需要调整
	if (successor->color == RB_Black) {
		RBTree_delete_fixup(tree, temp);
	}

	return successor;
}