#ifndef __BTREE_SEARCH_H__
#define __BTREE_SEARCH_H__

// B- 树
//

// 定义B- 树的最小度数
// 每个节点中关键字的最大数目 BTree_N = 2 * BTree_T - 1
#define	BTree_T		2
#define BTree_N		(BTree_T * 2 - 1)

struct BTNode {
	int	keynum;						// 结点中关键字的个数，keynum <= BTree_N
	int key[BTree_N];				// 关键字向量为key[0..keynum - 1]
	BTNode* child[BTree_T * 2];		// 孩子指针向量为child[0..keynum]
	bool isLeaf;					// 是否是叶子节点的标志
};

typedef BTNode* BTree;				// B-树的类型


void BTree_create(BTree* tree, const int* data, int length);

void BTree_destory(BTree* tree);

void BTree_insert(BTree* tree, int key);

void BTree_remove(BTree* tree, int key);

void BTree_print(BTree tree, int her = 1);

// 在B-树 tree 中查找关键字 key，
// 成功时返回找到的节点的地址及 key 在其中的位置 *pos
// 失败时返回 NULL 及查找失败时扫描到的节点位置 *pos
//
BTNode* BTree_search(const BTree tree, int key, int* pos);


#endif	// __BTREE_SEARCH_H__