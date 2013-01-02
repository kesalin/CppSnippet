#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <assert.h>

#include "SearchAlgorithms.h"

#define DEBUG_SEARCH

#ifdef DEBUG_SEARCH
#define debug_print(fmt,...) printf(fmt, ## __VA_ARGS__)
#else
#define debug_print(fmt,...)
#endif

// 顺序查找:在任意序列中查找，成功时返回结点的位置，失败时返回 -1
//
int sequential_search(const int* array, int length, int key)
{
	assert(array && length >= 0);

	int i;

	for (i = 0; i < length; ++i) {
		if (array[i] == key) {
			return i;
		}
	}

	return -1;
}

// 二分查找:在有序序列中查找，成功时返回结点的位置，失败时返回 -1
//
int binary_search(const int* array, int length, int key)
{
	assert(array && length >= 0);

	int low = 0;
	int high = length;
	int mid;

	while (low <= high) {
		mid = (low + high) >> 1;

		if (array[mid] == key) {
			return mid;
		}

		if (array[mid] > key) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}

	return -1;
}

// 分块查找/索引顺序查找
//
int blocking_search(
	const int* array,
	int length,
	IndexNode* indexTable,
	int indexTableLength,
	int key)
{
	assert(array && length >= 0 && indexTable && indexTableLength >= 0);

#if 1
	// 二分查找索引表
	int i, mid;
	int low = 0;
	int high = indexTableLength - 1;

	while (low <= high) {
		mid = (low + high) >> 1;

		if (indexTable[mid].key == key) {
			return indexTable[mid].index;
		}
		else if (indexTable[mid].key > key) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}

	low = indexTable[low].index;
	high = indexTable[high].index;

#else

	// 顺序查找索引表
	int i;
	int low = 0;
	int high = length - 1;

	for (i = 0; i < indexTableLength; ++i) {
		if (indexTable[i].key > key) {
			high = indexTable[i].index - 1;
			break;
		}

		low = indexTable[i].index;
	}
#endif

	for (i = low; i <= high; ++i) {
		if (array[i] == key) {
			return i;
		}
	}

	return -1;
}

// 散列查找
// 

// 散列函数：取余法
// h(key) = key % tableLength
//
int hash_remiander(int key, int tableLength)
{
	return key % tableLength;
}

// 散列函数：相乘取整法
// h(key) = [tableLength * (key * A - [key * A])]
// A 约等于 (根号 5 - 1)/2 = 0.61803398
//
int hash_multi_round_off(int key, int tableLength)
{
	double d = key * 0.61803398;
	return (int)(tableLength * (d - (int)d));
}

// 探查时，使用的二重 hash 函数 h1。总的探查法为：
// hi = (h(key) + i * h1(key)) % tableLength, 0 <= i <= tableLength - 1
// 
// 定义 h1(key) 的方法较多，但无论采用什么方法定义，都必须使 h1(key) 的值和
// tableLength 互素，才能使发生冲突的同义词地址均匀地分布在整个表中，
// 否则可能造成同义词地址的循环计算。
//
// 【例】若 tableLength 为素数，则 h1(key) 取 1 到 tableLength - 1 之间
//		的任何数均与 tableLength 互素，因此，我们可以简单地将它定义为：
//		h1(key) = key % (tableLength - 2) + 1
// 【例】若 tableLength 是 2 的方幂，
//      则 h1(key) 可取 1 到 tableLength - 1之间的任何奇数。
//
int hash_double(int key, int tableLength)
{
	return key % (tableLength - 2) + 1;
}

//=========================================================
//					开放地址法散列
//=========================================================
// 创建采用开放地址法的散列表
//
void create_open_address_hash_table(
   int* table,
   int tableLength,
   const int* data,
   int dataLength,
   Hash_Function hashFunc,
   Conflict_Resolution confictResolution,
   int zeroValue)
{
	assert(data && table && hashFunc
		&& dataLength > 0 && tableLength > 0);

	int i, j, index, index2, temp;

	// 初始化 hash table, 设置为序列中没有的值（零值）
	for (i = 0; i < tableLength; ++i) {
		table[i] = zeroValue;
	}

	for (i = 0; i < dataLength; ++i){
		index = (hashFunc)(data[i], tableLength);
		if (table[index] == zeroValue) {
			table[index] = data[i];
		}
		
		// 有冲突
		else {
			// 采用双重散列探查解决冲突
			// hi = (h(key) + i * h1(key)) % tableLength, 0 <= i <= tableLength - 1
			if (Conflict_Resolution_Double_Hash == confictResolution) {
				index2 = hash_double(data[i], tableLength);

				j = 1;
				while (j < tableLength) {
					temp = index + j * index2;
					if (table[temp] == zeroValue) {
						table[temp] = data[i];
						break;
					}

					++j;
				}
			}

			// 采用二次探查解决冲突
			// hi = (h(key) + i * i) % tableLength, 0 <= i <= tableLength - 1
			else if (Conflict_Resolution_Quadratic == confictResolution) {
				j = 1;
				while (j < tableLength) {
					temp = (index + j * j) % tableLength;
					if (table[temp] == zeroValue) {
						table[temp] = data[i];
						break;
					}

					++j;
				}

				// hash 表可能已满，报错。
				// 在这里表有可能尚未填满，只是二次散列算法无法探查到那些空挡。
				if (temp == tableLength) {
					assert(0 && "Error: Hash table may be full!\n");
				}
			}

			// 采用线性探查解决冲突（Conflict_Resolution_Linear）
			// hi = (h(key) + i) % tableLength, 0 <= i <= tableLength - 1
			else {
				temp = (index + 1) % tableLength;	
				while (temp != index) {
					if (table[temp] == zeroValue) {
						table[temp] = data[i];
						break;
					}

					temp = (++temp) % tableLength;
				}

				// hash 表已满，报错
				if (temp == index) {
					assert(0 && "Error: Hash table is full!\n");
				}
			}
		}
	}

#ifdef DEBUG_SEARCH
	debug_print("\n创建长度为 %d 的 hash table：\n  ", tableLength);
	for (i = 0; i < tableLength; ++i) {
		debug_print("%d ", table[i]);
	}
	debug_print("\n");
#endif
}

// 在采用开放地址法的散列表中查找
//
int open_address_hash_search(
	 int key,
	 const int* table,
	 int tableLength,
	 Hash_Function hashFunc,
	 Conflict_Resolution confictResolution,
	 int zeroValue)
{
	assert(table && hashFunc && tableLength > 0);
	assert(key != zeroValue);

	int j, index, index2, temp;

	index = (hashFunc)(key, tableLength);
	if (table[index] == key) {
		return index;
	}
	else if (table[index] == zeroValue) {
		return -1;
	}

	// 可能是有冲突
	else {
		// 采用双重散列探查继续查找
		// hi = (h(key) + i * h1(key)) % tableLength, 0 <= i <= tableLength - 1
		if (Conflict_Resolution_Double_Hash == confictResolution) {
			index2 = hash_double(key, tableLength);
			j = 1;
			while (j < tableLength) {
				temp = index + j * index2;
				if (table[temp] == zeroValue) {
					return -1;
				}
				else if (table[temp] == key) {
					return temp;
				}

				++j;
			}
		}

		// 采用二次探查继续查找
		// hi = (h(key) + i * i) % tableLength, 0 <= i <= tableLength - 1
		else if (Conflict_Resolution_Quadratic == confictResolution) {
			j = 1;
			while (j < tableLength) {
				temp = (index + j * j) % tableLength;
				if (table[temp] == key) {
					return temp;
				}
				else if (table[index] == zeroValue) {
					return -1;
				}

				++j;
			}
		}

		// 采用线性探查继续查找（Conflict_Resolution_Linear）
		// hi = (h(key) + i) % tableLength, 0 <= i <= tableLength - 1
		else {
			temp = (index + 1) % tableLength;
			while (temp != index) {
				if (table[temp] == key) {
					return temp;
				}
				else if (table[temp] == zeroValue){
					return -1;
				}

				temp = (++temp) % tableLength;
			}
		}
	}

	return -1;
}

//=========================================================
//					拉链址法散列
//=========================================================

// 创建采用拉链法的散列表
//
void create_link_hash_table(
	Hash_Node** pTable,
	int tableLength,
	const int* data,
	int dataLength,
	Hash_Function hashFunc,
	int zeroValue)
{
	assert(pTable && data && hashFunc && tableLength > 0 && dataLength > 0);

	int i, index;
	Hash_Node* node, *newNode;
	Hash_Node* table = NULL;

	table = (Hash_Node*)malloc(tableLength * sizeof(Hash_Node));
	if (!table) {
		*pTable = NULL;
		printf("Error: out of memory!\n");
		return;
	}

	*pTable = table;

	// 初始化表
	for (i = 0; i < tableLength; ++i) {
		table[i].key = zeroValue;
		table[i].next = NULL;
	}

	for (i = 0; i < dataLength; ++i) {
		index = (hashFunc)(data[i], tableLength);
		if (table[index].key == zeroValue) {
			table[index].key = data[i];
		}
		else {
			node = &table[index];
			while (node->next) {
				node = node->next;
			}

			newNode = (Hash_Node*)malloc(sizeof(Hash_Node));
			newNode->key = data[i];
			newNode->next = NULL;

			node->next = newNode;
		}
	}

#ifdef DEBUG_SEARCH
	debug_print("\n创建长度为 %d 的 hash table：\n", tableLength);
	for (i = 0; i < tableLength; ++i) {
		node = &table[i];
		debug_print(" %d : ", i);
		while (node) {
			debug_print(" %d ->", node->key);
			node = node->next;
		}

		debug_print(" null\n");
	}
	debug_print("\n");
#endif
}

// 销毁采用拉链法的散列表
//
void destroy_link_hash_table(
	Hash_Node* table,
	int tableLength)
{
	int i;
	Hash_Node* node, *nextNode;

	for (i = 0; i < tableLength; ++i) {
		node = table[i].next;
		while (node) {
			nextNode = node->next;
			free(node);

			node = nextNode;
		}
	}

	free(table);
	table = NULL;
}

// 在采用拉链法的散列表中查找
//
int link_hash_search(
	int key,
	const Hash_Node* table,
	int tableLength,
	Hash_Function hashFunc,
	int zeroValue)
{
	assert(table && hashFunc && tableLength > 0);
	assert(key != zeroValue);

	int index = (hashFunc)(key, tableLength);
	const Hash_Node* node = &table[index];

	while (node) {
		if (node->key == key) {
			return index;
		}
		
		node = node->next;
	}

	return -1;
}
