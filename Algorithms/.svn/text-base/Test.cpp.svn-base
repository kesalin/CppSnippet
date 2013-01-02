// Test.cpp : Defines the entry point for the console application.
//
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "SortAlgorithms.h"
#include "SearchAlgorithms.h"
#include "BinaryTree.h"
#include "BTree.h"
#include "RedBlackTree.h"

//==================================================================
//					工具函数
//==================================================================

// 打印数组
// 
void print_array(const int* a, int length, const char* prefix)
{
	assert(a && length >= 0);

	if (prefix) {
		printf("%s", prefix);
	}

	for (int i = 0; i < length; i++) {
		printf("%d ", a[i]);
	}

	printf("\n");
}

//==================================================================
//					测试各种排序算法
//==================================================================

typedef void (*Sort_Function)(int* array, int length);

struct SortFucntionInfo {
	char * name;
	Sort_Function func;
};

SortFucntionInfo sort_function_list[] = {
	{"直接插入排序",				insert_sort},
	{"希尔排序",					shell_sort},
	{"冒泡排序",					bubble_sort},
	{"冒泡排序优化版",			bubble_sort_opt},
	{"快速排序",					quick_sort},
	{"直接选择排序",				selection_sort},
	{"堆排序",					heap_sort},
	{"合并排序：自下向上二路归并",	merge_sort},
	{"合并排序：自上向下分治",		merge_sort_dc},
	{"桶/箱排序",				bucket_sort},
	{"基数排序",					radix_sort},
	{"", NULL}
};

// 测试某种排序算法
//
void test_sort_function(Sort_Function func)
{
	const int length = 11;
	const int count = 2;
	int array[count][length] = {
		{65, 32, 49, 10, 8, 72, 27, 42, 18, 58, 91},
		{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
	};
	
	for (int i = 0; i < count; i++) {
		print_array(array[i], length, " original: ");

		func(array[i], length);

		print_array(array[i], length, "   sorted: ");

		printf("\n");
	}
}

// 测试各种排序算法
//
void test_sort()
{
	for (int i = 0; sort_function_list[i].func != NULL; ++i) {
		printf("\n=== %s ===\n", sort_function_list[i].name);
		test_sort_function(sort_function_list[i].func);
	}

	const int length = 11;
	printf("\n=== 计数排序 ===\n");
	int array2[11] = {65, 32, 49, 10, 18, 72, 27, 42, 18, 58, 91};

	print_array(array2, length, " data: ");

	counting_sort(array2, length, 100);

	print_array(array2, length, " data: ");
}

//==================================================================
//					测试各种查找算法
//==================================================================

void test_sequential_search();
void test_binary_search();
void test_blocking_search();
void test_open_address_hash_search();
void test_link_hash_search();
void test_binary_tree_search();

typedef void (*Test_Search_Function)();

struct TestSearchFucntionInfo {
	char * name;
	Test_Search_Function func;
};

TestSearchFucntionInfo test_search_function_list[] = {
	{"顺序查找",					test_sequential_search},
	{"二分查找",					test_binary_search},
	{"分块查找",					test_blocking_search},
	{"开放地址法哈希/散列查找",	test_open_address_hash_search},
	{"拉链法哈希/散列查找",		test_link_hash_search},
	{"二叉查找树查找",			test_binary_tree_search},
	{"", NULL},
};

// 测试各种查找算法
//
void test_search()
{
	for (int i = 0; test_search_function_list[i].func != NULL; ++i) {
		printf("\n=== %s ===\n", test_search_function_list[i].name);
		(test_search_function_list[i].func)();
	}
}

// 测试顺序查找
//
void test_sequential_search()
{
	const int length = 11;
	int array[length] = {65, 32, 49, 10, 18, 72, 27, 42, 18, 58, 91};

	int key1 = 72;
	int key2 = 55;
	int pos;

	print_array(array, length, " data: ");

	pos = sequential_search(array, length, key1);
	printf(" try searching %d, index is %d\n", key1, pos);

	pos = sequential_search(array, length, key2);
	printf(" try searching %d, index is %d\n", key2, pos);
}

// 测试二分查找
//
void test_binary_search()
{
	// 二分查找要求序列有序
	const int length = 11;
	int array[length] = {8, 10, 18, 27, 32, 43, 49, 58, 65, 72, 96};

	int key1 = 72;
	int key2 = 55;
	int pos;

	print_array(array, length, " data: ");

	pos = binary_search(array, length, key1);
	printf(" try searching %d, index is %d\n", key1, pos);

	pos = binary_search(array, length, key2);
	printf(" try searching %d, index is %d\n", key2, pos);
}

// 测试分块查找
//
void test_blocking_search()
{
	// 分块查找要求序列分块有序: 块长为 3，共 4 块
	const int length = 11;
	int array[length] = {10, 8, 18, 43, 27, 32, 58, 49, 65, 72, 69};

	int key1 = 72;
	int key2 = 55;
	int pos;

	// 创建分块索引表：块长为 3，共 4 块。
	const int indexTableLength = 4;
	IndexNode indexNode[indexTableLength];
	indexNode[0].key = 18;
	indexNode[0].index = 2;
	indexNode[1].key = 43;
	indexNode[1].index = 3;
	indexNode[2].key = 65;
	indexNode[2].index = 8;
	indexNode[3].key = 72;
	indexNode[3].index = 9;

	print_array(array, length, " data: ");

	pos = blocking_search(array, length, indexNode, indexTableLength, key1);
	printf(" try searching %d, index is %d\n", key1, pos);

	pos = blocking_search(array, length, indexNode, indexTableLength,  key2);
	printf(" try searching %d, index is %d\n", key2, pos);
}

// 测试采用开放地址法的哈希查找
// 
void test_open_address_hash_search()
{
	const int length = 11;
	int array[length] = {65, 32, 49, 10, 18, 72, 27, 42, 18, 58, 91};

	int pos;
	int key1 = 72;
	int key2 = 55;

	print_array(array, length, " data: ");

	// 换成别的 hash 函数试试
	Hash_Function hashFunc = hash_remiander;	
	//hashFunc = hash_multi_round_off;	

	// 换成别的探查方式试试
	Conflict_Resolution conflictResolution = Conflict_Resolution_Linear;
	conflictResolution = Conflict_Resolution_Quadratic;
	//conflictResolution = Conflict_Resolution_Double_Hash;
	
	// 创建开放地址法散列表
	int tableLength = 17;	// 对于二重探查散列法，散列表长取素数或奇数为佳
	int* hashTable = (int*)malloc(tableLength * sizeof(int));
	if (!hashTable) {
		printf("Error: out of memory!\n");
		return;
	}

	create_open_address_hash_table(
		hashTable, tableLength, array, length, 
		hashFunc, conflictResolution);

	pos = open_address_hash_search(key1, hashTable, tableLength, 
		hashFunc, conflictResolution);
	printf(" try searching %d, index at hash is table %d\n", key1, pos);
	
	pos = open_address_hash_search(key2, hashTable, tableLength,
		hashFunc, conflictResolution);
	printf(" try searching %d, index at hash is table %d\n", key2, pos);

	// 删除开放地址法散列表
	free(hashTable);
	hashTable = NULL;
}

// 测试采用拉链法的哈希查找
//
void test_link_hash_search()
{
	const int length = 11;
	int array[length] = {65, 32, 49, 10, 18, 72, 27, 42, 18, 58, 91};

	int key1 = 72;
	int key2 = 55;
	int pos;

	print_array(array, length, " data: ");

	// 换成别的 hash 函数试试
	Hash_Function hashFunc = hash_remiander;	
	//hashFunc = hash_multi_round_off;		

	// 创建拉链法散列表
	int tableLength = 7;
	Hash_Node* linkHashTable = NULL;

	create_link_hash_table(
		&linkHashTable, tableLength, array, length, hashFunc);
	if (!linkHashTable){
		printf("Failed to create link hash table!\n");
		return;
	}
	
	pos = link_hash_search(key1, linkHashTable, tableLength, hashFunc);
	printf(" try searching %d, index at hash table is %d\n", key1, pos);
	
	pos = link_hash_search(key2, linkHashTable, tableLength, hashFunc);
	printf(" try searching %d, index at hash table is %d\n", key2, pos);

	// 销毁拉链法散列表
	destroy_link_hash_table(linkHashTable, tableLength);
}

//==================================================================
//					测试二叉查找树
//==================================================================

void test_binary_tree_search()
{
	// 二叉查找树要求记录的关键字唯一，所以不能有相同的记录
	const int length = 11;
	int array[length] = {65, 32, 49, 10, 8, 72, 27, 42, 18, 58, 91};

	int key1 = 72;
	int key2 = 55;

	print_array(array, length, " data: ");

	BSTree tree = NULL;
	BSTNode* node = NULL;

	// 创建二叉树
	BST_create(&tree, array, length);
	if (!tree) {
		printf("Failed to create binary search tree!\n");
		return;
	}
	
	// 查找
	node = BST_search(tree, key1);
	printf("  %s %d in binary search tree.\n",
		(NULL == node) ? "Could not find" : "Yeah! Found", key1);

	node = BST_search(tree, key2);
	printf("  %s %d in binary search tree.\n",
		(NULL == node) ? "Could not find" : "Found", key2);

	// 插入节点
	printf(" Insert %d to binary search tree.\n", key2);
	BST_insert(&tree, key2);

	node = BST_search(tree, key2);
	printf("  %s %d in binary search tree.\n",
		(NULL == node) ? "Could not find" : "Yeah! Found", key2);

	// 删除节点
	key2 = 27;
	printf(" Remove %d from binary search tree.\n", key2);
	BST_remove(&tree, key2);

	node = BST_search(tree, key2);
	printf("  %s %d in binary search tree.\n",
		(NULL == node) ? "Could not find" : "Yeah! Found", key2);

	// 销毁二叉树
	BST_destory(&tree);

	assert(NULL == tree);
}

//==================================================================
//					测试 B- 树
//==================================================================
void test_BTree_search(BTree tree, int key)
{
	int pos = -1;
	BTNode*	node = BTree_search(tree, key, &pos);
	if (node) {
		printf("在%s节点（包含 %d 个关键字）中找到关键字 %c，其索引为 %d\n",
			node->isLeaf ? "叶子" : "非叶子",
			node->keynum, key, pos);
	}
	else {
		printf("在树中找不到关键字 %c\n", key);
	}
}

void test_BTree_remove(BTree* tree, int key)
{
	printf("\n移除关键字 %c \n", key);
	BTree_remove(tree, key);
	BTree_print(*tree);
	printf("\n");
}

void test_btree()
{
	const int length = 10;
	int array[length] = {
		'G', 'M', 'P', 'X', 'A', 'C', 'D', 'E', 'J', 'K',
		//'N', 'O', 'R', 'S', 'T', 'U', 'V', 'Y', 'Z', 'F'
	};

	BTree tree = NULL;
	BTNode* node = NULL;
	int pos = -1;
	int key1 = 'R';		// in the tree.
	int key2 = 'B';		// not in the tree.

	// 创建
	BTree_create(&tree, array, length);

	printf("\n=== 创建 B- 树 ===\n");
	BTree_print(tree);
	printf("\n");

	// 查找
	test_BTree_search(tree, key1);
	printf("\n");
	test_BTree_search(tree, key2);

	// 插入关键字
	printf("\n插入关键字 %c \n", key2);
	BTree_insert(&tree, key2);
	BTree_print(tree);
	printf("\n");

	test_BTree_search(tree, key2);

	// 移除关键字
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);

	key2 = 'M';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);

	key2 = 'E';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);

	key2 = 'G';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);

	key2 = 'A';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);

	key2 = 'D';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);

	key2 = 'K';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);

	key2 = 'P';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);

	key2 = 'J';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);

	key2 = 'C';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);

	key2 = 'X';
	test_BTree_remove(&tree, key2);
	test_BTree_search(tree, key2);

	// 销毁
	BTree_destory(&tree);
}

//==================================================================
//					测试红黑树
//==================================================================
void test_redblacktree_delete(RBTree* tree, int key)
{
	RBNode* node = RBTree_search(*tree, key);
	assert(node != RBTree_nil());

	printf("\n删除节点 %d \n", node->key);
	
	node = RBTree_delete(tree, node);
	free(node);
	
	RBTree_print(*tree);
}

void test_redblacktree()
{
	const int length = 14;
	int array[length] = {
		2, 3, 4, 6, 7, 11, 9, 18, 12, 14, 19, 17, 22, 20
	};

	int i;
	RBTree tree = RBTree_nil();
	RBNode* node = NULL;

	// 插入节点生成树
	for (i = 0; i < length; i++) {
		node = (RBNode*)malloc(sizeof(RBNode));
		node->key = array[i];
		node->color = RB_Red;
		node->parent = RBTree_nil();
		node->leftChild = RBTree_nil();
		node->rightChild = RBTree_nil();

		RBTree_insert(&tree, node);	
	}

	RBTree_print(tree);

	// 插入测试
	node = (RBNode*)malloc(sizeof(RBNode));
	node->key = 21;

	printf("\n插入节点 %d\n", node->key);

	RBTree_insert(&tree, node);
	RBTree_print(tree);

	// 查找测试
	i = 6;
	node = RBTree_search(tree, i);

	if (node != RBTree_nil()) {
		printf("\n在红黑树中找到节点 %d\n", node->key);
	}
	else {
		printf("\n在红黑树中找不到节点 %d\n", i);
	}

	// 删除测试
	// 
	i = 4;// 取值 1, 2, 3, 4，分别对应 case 1, 2, 3, 4

	switch (i)
	{
	case 1:	// 兄弟为红色
		test_redblacktree_delete(&tree, 3);
		break;

	case 2:	// 兄弟为黑色，且兄弟的两孩子均为黑色
		test_redblacktree_delete(&tree, 12);
		break;

	case 3:	// 兄弟为黑色，且兄弟的左孩子为红色，右孩子均为黑色
		test_redblacktree_delete(&tree, 19);
		break;

	case 4:	// 兄弟为黑色，且兄弟的右孩子为红色
		test_redblacktree_delete(&tree, 9);
		break;
	}

	test_redblacktree_delete(&tree, 21);

	// 删除树
	for (i = 0; i < length; i++) {
		node = RBTree_search(tree, array[i]);

		if (node != RBTree_nil()) {
			printf("删除 %d\n", node->key);
			node = RBTree_delete(&tree, node);
			free(node);
		}
	}

	assert(tree == RBTree_nil());
}

//==================================================================
//					MAIN
//==================================================================

typedef void (*Test_Function)();

Test_Function test_function[] = {
	//test_sort,		// 测试排序算法
	//test_search,		// 测试查找算法
	//test_btree,		// 测试 B- 树
	test_redblacktree,	// 测试红黑树
	NULL
};

int main(int argc, const char* argv[])
{
	for (int i = 0; test_function[i] != NULL; i++) {
		test_function[i]();
	}

	printf("\n测试结束\n");
	system("pause");
	return 0;
}