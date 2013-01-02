#include "BTree.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))

#define DEBUG_TREE

#ifdef DEBUG_TREE
#define debug_print(fmt,...) printf(fmt, ## __VA_ARGS__)
#else
#define debug_print(fmt,...)
#endif

void disk_write(BTNode* node)
{
	printf("向磁盘写入节点\n");
}

void disk_read(BTNode** node)
{
	printf("从磁盘读取节点\n");
}

void BTree_print(BTree tree, int her)
{
	int i;
	BTNode* node = tree;

	if (node) {
		printf("第 %d 层， %d node : ", her, node->keynum);

		for (i = 0; i < node->keynum; ++i) {
			printf("%c ", node->key[i]);
		}

		printf("\n");

		++her;
		for (i = 0 ; i <= node->keynum; i++) {
			if (node->child[i]) {
				BTree_print(node->child[i], her);
			}
		}
	}
	else {
		printf("树为空。\n");
	}
}

// parent 是一个非满的父节点
// node 是 tree 孩子表中下标为 index 的孩子节点，且是满的
void BTree_split_child(BTNode* parent, int index, BTNode* node)
{
	assert(parent && node);

	int i;

	// 创建新节点，存储 node 中后半部分的数据
	BTNode* newNode = (BTNode*)calloc(sizeof(BTNode), 1);
	if (!newNode) {
		printf("Error! out of memory!\n");
		return;
	}

	newNode->isLeaf = node->isLeaf;
	newNode->keynum = BTree_T - 1;

	// 拷贝 node 后半部分关键字
	for (i = 0; i < newNode->keynum; ++i){
		newNode->key[i] = node->key[BTree_T + i];
		node->key[BTree_T + i] = 0;
	}

	// 如果 node 不是叶子节点，拷贝 node 后半部分的孩子节点
	if (!node->isLeaf) {
		for (i = 0; i < BTree_T; i++) {
			newNode->child[i] = node->child[BTree_T + i];
			node->child[BTree_T + i] = NULL;
		}
	}

	// 将 node 分裂出 newNode 之后，里面的数据减半
	node->keynum = BTree_T - 1;

	// 调整父节点
	for (i = parent->keynum; i > index; --i) {
		parent->child[i + 1] = parent->child[i];
	}

	parent->child[index + 1] = newNode;

	for (i = parent->keynum - 1; i >= index; --i) {
		parent->key[i + 1] = parent->key[i];
	}

	parent->key[index] = node->key[BTree_T - 1];
	++parent->keynum;

	// 清除 node 中的中后部数据
	// 可以不处理，因为是通过 keynum 控制访问的
// 	for (i = BTree_T - 1; i < BTree_N; ++i) {
// 		node->key[i] = 0;
// 		node->child[i + 1] = NULL;
// 	}

	// 写入磁盘
 	disk_write(parent);
 	disk_write(newNode);
 	disk_write(node);
}

void BTree_insert_nonfull(BTNode* node, int key)
{
	assert(node);

	int i;

	// 节点是叶子节点，直接插入
	if (node->isLeaf) {
		i = node->keynum - 1;
		while (i >= 0 && key < node->key[i]) {
			node->key[i + 1] = node->key[i];
			--i;
		}

		node->key[i + 1] = key;
		++node->keynum;

		// 写入磁盘
		disk_write(node);
	}

	// 节点是内部节点
	else {
		// 查找插入的位置
		i = node->keynum - 1;
		while (i >= 0 && key < node->key[i]) {
			--i;
		}

		++i;

		// 从磁盘读取孩子节点
		disk_read(&node->child[i]);

		// 如果该孩子节点已满，分裂调整值
		if (node->child[i]->keynum == BTree_N) {
			BTree_split_child(node, i, node->child[i]);

			if (key > node->key[i]) {
				++i;
			}
		}

		BTree_insert_nonfull(node->child[i], key);
	}
}

void BTree_insert(BTree* tree, int key)
{
	BTNode* node;
	BTNode* root = *tree;

	// 树为空
	if (NULL == root) {
		root = (BTNode*)calloc(sizeof(BTNode), 1);
		if (!root) {
			printf("Error! out of memory!\n");
			return;
		}
		root->isLeaf = true;
		root->keynum = 1;
		root->key[0] = key;

		*tree = root;

		// 写入磁盘
		disk_write(root);

		return;
	}

	// 节点已满，需要进行分裂调整
	if (root->keynum == BTree_N) {
		// 产生新节点当作根
		node = (BTNode*)calloc(sizeof(BTNode), 1);
		if (!node) {
			printf("Error! out of memory!\n");
			return;
		}

		*tree = node;
		node->isLeaf = false;
		node->keynum = 0;
		node->child[0] = root;

		BTree_split_child(node, 0, root);

		BTree_insert_nonfull(node, key);
	}

	// 节点未满，在当前节点中插入 key
	else {
		BTree_insert_nonfull(root, key);
	}
}


// 对 tree 中的节点 node 进行合并孩子节点处理
// 注意：孩子节点的 keynum 必须均已达到下限，即均等于 BTree_T - 1
// 将 node 中索引为 index + 1 的孩子节点合并到索引为 index 的孩子节点中，
// 并将 tree 中索引为 index  的 key 下降到该节点中，调整相关的 key 和指针。
//
void BTree_merge_child(BTree* tree, BTNode* node, int index)
{
	assert(tree && node && index >= 0 && index < node->keynum);

	int i;

	int key = node->key[index];
	BTNode* prevChild = node->child[index];
	BTNode* nextChild = node->child[index + 1];

	assert(prevChild && prevChild->keynum == BTree_T - 1
		&& nextChild && nextChild->keynum == BTree_T - 1);

	prevChild->key[prevChild->keynum] = key;
	prevChild->child[prevChild->keynum + 1] = nextChild->child[0];
	++prevChild->keynum;

	// 合并
	for (i = 0; i < nextChild->keynum; ++i) {
		prevChild->key[prevChild->keynum] = nextChild->key[i];
		prevChild->child[prevChild->keynum + 1] = nextChild->child[i + 1];
		++prevChild->keynum;
	}

	// 在 node 中移除 key 以及指向后继孩子节点的指针
	for (i = index; i < node->keynum - 1; ++i) {
		node->key[i] = node->key[i + 1];
		node->child[i + 1] = node->child[i + 2];
	}

	node->key[node->keynum - 1] = 0;
	node->child[node->keynum] = NULL;
	--node->keynum;

	// 如果根节点没有 key 了，删之，并将根节点调整为前继孩子节点。
	if (node->keynum == 0) {
		if (*tree == node) {
			*tree = prevChild;
		}

		free(node);
		node = NULL;
	}

	free(nextChild);
}

void BTree_remove(BTree* tree, int key)
{
	// B-数的保持条件之一：
	// 非根节点的内部节点的关键字数目不能少于 BTree_T - 1

	int i, j, index;
	BTNode *root = *tree;
	BTNode *node = root;
	BTNode *prevChild, *nextChild, *child;
	int prevKey, nextKey;

	if (!root) {
		printf("Failed to remove %c, it is not in the tree!\n", key);
		return;
	}

	index = 0;
	while (index < node->keynum && key > node->key[index]) {
		++index;
	}

	//
	//  index of key:    i-1  i  i+1
	//	            +---+---+---+---+---+
	//             ...  +   + A +   +  ...
	//	            +---+---+---+---+---+
	//                 /    |    \
	//  index of C: i - 1   i    i + 1
	//               /      |      \
	//	    +---+---+     +---+	  +---+---+
	//     ...  +   +     +   +   +   +  ...
	//	    +---+---+     +---+	  +---+---+
	//      prevChild     child   nextChild

	// Find the key.
	if (index < node->keynum && node->key[index] == key) {
		// 1，所在节点是叶子节点，直接删除
		if (node->isLeaf) {
			for (i = index; i < node->keynum; ++i) {
				node->key[i] = node->key[i + 1];
				node->child[i + 1] = node->child[i + 2];
			}

			--node->keynum;

			if (node->keynum == 0) {
				assert(node == *tree);
				free(node);
				*tree = NULL;
			}

			return;
		}

		// 2a，如果位于 key 前的子节点的 key 数目 >= BTree_T，
		// 在其中找 key 的前驱，用前驱的 key 值赋予 key，
		// 然后在前驱所在孩子节点中递归删除前驱。
		else if (node->child[index]->keynum >= BTree_T) {
			prevChild = node->child[index];
			prevKey = prevChild->key[prevChild->keynum - 1];
			node->key[index] = prevKey;

			BTree_remove(&prevChild, prevKey);
		}

		// 2b，如果位于 key 后的子节点的 key 数目 >= BTree_T，
		// 在其中找 key 的后继，用后继的 key 值赋予 key，
		// 然后在后继所在孩子节点中递归删除后继。
		else if (node->child[index + 1]->keynum >= BTree_T) {
			nextChild = node->child[index + 1];
			nextKey = nextChild->key[0];
			node->key[index] = nextKey;

			BTree_remove(&nextChild, nextKey);
		}

		// 2c，前驱和后继都只包含 BTree_T - 1 个节点，
		// 将 key 下降前驱孩子节点，并将后继孩子节点合并到前驱孩子节点，
		// 删除后继孩子节点，在 node 中移除 key 和指向后继孩子节点的指针，
		// 然后在前驱所在孩子节点中递归删除 key。
		else if (node->child[index]->keynum == BTree_T - 1
			&& node->child[index + 1]->keynum == BTree_T - 1){
			prevChild = node->child[index];

			BTree_merge_child(tree, node, index);

			// 在前驱孩子节点中递归删除 key
			BTree_remove(&prevChild, key);
		}
	}

	// 3，key 不在内节点 node 中，则应当在某个包含 key 的子节点中。
	//  key < node->key[index], 所以 key 应当在孩子节点 node->child[index] 中
	else {
		child = node->child[index];
		if (!child) {
			printf("Failed to remove %c, it is not in the tree!\n", key);
			return;
		}

		if (child->keynum == BTree_T - 1) {
			prevChild = NULL;
			nextChild = NULL;

			if (index - 1 >= 0) {
				prevChild = node->child[index - 1];
			}

			if (index + 1 <= node->keynum) {
				nextChild = node->child[index + 1];
			}

			// 3a，如果所在孩子节点相邻的兄弟节点中有节点至少包含 BTree_t 个关键字
			// 将 node 的一个关键字下降到 child 中，将相邻兄弟节点中一个节点上升到
			// node 中，然后在 child 孩子节点中递归删除 key。
			if ((prevChild && prevChild->keynum >= BTree_T)
				|| (nextChild && nextChild->keynum >= BTree_T)) {

				if (nextChild && nextChild->keynum >= BTree_T) {
					child->key[child->keynum] = node->key[index];
					child->child[child->keynum + 1] = nextChild->child[0];
					++child->keynum;

					node->key[index] = nextChild->key[0];

					for (j = 0; j < nextChild->keynum - 1; ++j) {
						nextChild->key[j] = nextChild->key[j + 1];
						nextChild->child[j] = nextChild->child[j + 1];
					}
					--nextChild->keynum;
				}
				else {
					for (j = child->keynum; j > 0; --j) {
						child->key[j] = child->key[j - 1];
						child->child[j + 1] = child->child[j];
					}
					child->child[1] = child->child[0];
					child->child[0] = prevChild->child[prevChild->keynum];
					child->key[0] = node->key[index - 1];
					++child->keynum;

					node->key[index - 1] = prevChild->key[prevChild->keynum - 1];

					--prevChild->keynum;
				}
			}

			// 3b, 如果所在孩子节点相邻的兄弟节点都只包含 BTree_t - 1 个关键字，
			// 将 child 与其一相邻节点合并，并将 node 中的一个关键字下降到合并节点中，
			// 再在 node 中删除那个关键字和相关指针，若 node 的 key 为空，删之，并调整根。
			// 最后，在相关孩子节点中递归删除 key。
			else if ((!prevChild || (prevChild && prevChild->keynum == BTree_T - 1))
				&& ((!nextChild || nextChild && nextChild->keynum == BTree_T - 1))) {
				if (prevChild && prevChild->keynum == BTree_T - 1) {

					BTree_merge_child(tree, node, index - 1);

					child = prevChild;
				}

				else if (nextChild && nextChild->keynum == BTree_T - 1) {

					BTree_merge_child(tree, node, index);
				}
			}
		}

		BTree_remove(&child, key);
	}
}

BTNode* BTree_search(const BTree tree, int key, int* pos)
{
	if (!tree) {
		return NULL;
	}

	int i = 0;

	while (i < tree->keynum && key > tree->key[i]) {
		++i;
	}

	// Find the key.
	if (i < tree->keynum && tree->key[i] == key) {
		if (pos) {
			*pos = i;
		}

		return tree;
	}

	// tree 为叶子节点，找不到 key，查找失败返回
	if (tree->isLeaf) {
		return NULL;
	}

	// 节点内查找失败，但 tree->key[i - 1]< key < tree->key[i]，
	// 下一个查找的结点应为 child[i]

	// 从磁盘读取第 i 个孩子的数据
	disk_read(&tree->child[i]);

	// 递归地继续查找于树 tree->child[i]
	return BTree_search(tree->child[i], key, pos);
}

void BTree_create(BTree* tree, const int* data, int length)
{
	assert(tree);

	int i;

#ifdef DEBUG_TREE
	debug_print("\n 开始创建 B- 树，关键字为:\n");
	for (i = 0; i < length; i++) {
		printf(" %c ", data[i]);
	}
	debug_print("\n");
#endif


	for (i = 0; i < length; i++) {
#ifdef DEBUG_TREE
		debug_print("\n插入关键字 %c:\n", data[i]);
#endif
		BTree_insert(tree, data[i]);

#ifdef DEBUG_TREE
		BTree_print(*tree);
#endif
	}

	debug_print("\n");
}

void BTree_destory(BTree* tree)
{
	int i;
	BTNode* node = *tree;

	if (node) {
		for (i = 0; i <= node->keynum; i++) {
			BTree_destory(&node->child[i]);
		}

		free(node);
	}

	*tree = NULL;
}

