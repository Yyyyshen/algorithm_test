// data_struct_cpp_09.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;
#include <string>
#include <sstream>
/**
 * 哈希表
 *
 * 以键值对来存储数据的结构
 * 可以通过数组来实现
 * （成倍扩容的原因是扩容操作每次都要消耗O(n)的时间复杂度来将值拷贝到新的数组中，频繁操作很消耗性能）
 */
int val_0 = 0;
/**
 * 哈希表中通过一个哈希函数来将键转换为索引
 * 对于查询操作，性能仅依赖于哈希函数算法，获取索引后查询复杂度始终为O(1)
 * 常见哈希函数：
 */
int hashModular(int key, int size) {  //takes key and size of the list
	return key % size;    // 取模
}
//用键的一部分作为索引
int hashTruncation(int key) {
	return key % 5000; // we will use key upto 2 digits
}
//将键划分小块，每块进行数学运算，例如每块相加
int hashFold(int key, int chunkSize) {
	cout << "Key: " << key << endl;
	string strKey = std::to_string(key); // Convert integer into string for slicing
	int hashVal = 0, tempNum = 0;
	string temp;
	cout << "Chunks: ";
	// increment i to chunksize everytime
	for (int i = 0; i < strKey.length(); i += chunkSize) {
		temp = "";
		if (i + chunkSize <= strKey.length()) //check if chunksize is less than equal to key
		{
			for (int j = i; j < i + chunkSize; j++) {
				temp += strKey[j];
				cout << strKey[j];
			}
			cout << " ";
			// converting string to integer
			stringstream conv(temp);
			conv >> tempNum;
			hashVal = hashVal + tempNum; // adding sliced number to hashVal
		}
		else {
			for (int j = i; j <= strKey.length(); j++) {
				temp += strKey[j];
				cout << strKey[j];
			}
			// converting string to integer
			stringstream conv(temp);
			conv >> tempNum;
			hashVal = hashVal + tempNum;// adding sliced number to hashVal
		}
	}
	return hashVal;
}
/**
 * 将键转换为小范围内的索引时，可能会发生值相同的情况
 * 解决这种碰撞常见的策略：
 *
 * 线性探测——如果哈希函数返回已被填充的索引，则移至下一个索引。
 * 该增量可以基于相对于已经计算的索引的固定偏移值。如果该索引也已填充，则继续遍历直到找到一个空位。
 * 缺点是偏移值如果选不好，会错过很多可选位置
 *
 * 链接策略——哈希表的每个插槽都包含一个指向另一个数据结构（例如链表或树）的指针。
 * 该索引处的每个条目都将插入到该索引的链接列表中。
 *
 * 调整数组大小——可以设置一个阈值，一旦超过阈值，创建一个新表，该表的大小是原始表的两倍。然后，复制上一张表中的元素。
 * 调整数组大小可显着减少冲突，但函数本身的成本很高。
 * 因此，我们需要谨慎设置阈值。典型的惯例是将阈值设置为0.6，这意味着当表的60％被填充时，需要进行调整大小操作。
 *
 * 处理冲突的其他一些策略包括二次探查、桶方法、随机探查和 密钥重新哈希。必须使用最适合的哈希算法和计划存储的数据大小的策略。
 */
int val_1 = 1;
/**
 * 结合链式策略和调整大小方式避免索引冲突
 * 具有相同哈希键的所有元素将存储在该索引处的数组中。
 * 在数据结构中，这些数组称为存储桶。
 * 哈希表的大小设置为n * m，其中n是它可以容纳的键数，m是每个存储桶包含的插槽数。每个插槽都包含一个键/值对。
 */
class HashEntry {
public:
	string key;
	int value;
	HashEntry* next;

	HashEntry() {
		key = "";
		value = -1;
		next = NULL;
	}
	HashEntry(string key, int value) {
		this->key = key;
		this->value = value;
		next = NULL;
	}
};
//创建HashTable类，该类是HashEntry对象的集合。还要跟踪哈希表中的插槽总数和哈希表的大小。当需要调整表的大小时，这两个变量将派上用场。
class HashTable {
private:
	HashEntry** bucket;
	int slots;
	int size;

public:
	HashTable(int s) {
		bucket = new HashEntry * [s];
		//Initialise all elements of array as NULL
		for (int i = 0; i < s; i++)
			bucket[i] = NULL;
		slots = s;
		size = 0;
	}
	int getSize() { // return size of table
		return size;
	}
	bool isEmpty() { // if table is empty return true
		return getSize() == 0;
	}
	//哈希函数
	int getIndex(string key) {

		int Key = 0;
		for (int i = 0; i < key.length(); i++) {
			Key = 37 * Key + key[i];
		}
		if (Key < 0)
			Key *= -1;

		return Key % slots;
	}
	//插入，计算出的索引相同则按链表往后存储
	void insert(string key, int value) {
		// Apply hash function to find index for given key
		int hashIndex = getIndex(key);
		//cout << "hashIndex : " << hashIndex  <<endl;
		if (bucket[hashIndex] == NULL) {

			bucket[hashIndex] = new HashEntry(key, value);
			size++;
		}
		else { //find next free space

			HashEntry* temp = bucket[hashIndex];;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = new HashEntry(key, value);
			size++;

		}
	}
	//打印
	void display() {
		HashEntry* temp;
		for (int i = 0; i < slots; i++) {
			if (bucket[i] != NULL) {
				cout << "HashIndex : " << i << " ";
				temp = bucket[i];
				while (temp != NULL) {
					cout << "(key = " << temp->key << " , value = " << temp->value << " )";
					temp = temp->next;
				}
			}
			cout << endl;
		}
	}
	//重新分配大小，确保哈希表不会超出特定阈值。只要超过阈值，将元素从当前表转移到容量为原来两倍的新表中。有助于避免冲突。
	void resize() {
		cout << "resize" << endl;
		slots *= 2;
		HashEntry** tempBucket = new HashEntry * [slots];
		int hashIndex;
		HashEntry* tmp;
		for (int i = 0; i < slots; i++)
			tempBucket[i] = NULL;
		HashEntry* temp;
		for (int i = 0; i < slots / 2; i++) {
			if (bucket[i] != NULL) {

				temp = bucket[i];
				while (temp != NULL) {
					hashIndex = getIndex(temp->key);
					if (tempBucket[hashIndex] == NULL)
						tempBucket[hashIndex] = new HashEntry(temp->key, temp->value);
					else { //find next free space

						tmp = tempBucket[hashIndex];;
						while (tmp->next != NULL) {
							tmp = tmp->next;
						}
						tmp->next = new HashEntry(temp->key, temp->value);
					}
					temp = temp->next;
				}
			}
		}
		bucket = tempBucket;
	}
	//查询操作，获取索引值然后在链表中搜索，在冲突少的情况下，搜索复杂度仅为O(1)
	int search(string key) {
		int hashIndex = getIndex(key);
		if (bucket[hashIndex] == NULL) {
			cout << "Value Not Found!" << endl;
			return -1;
		}

		if (bucket[hashIndex]->key == key) {
			return bucket[hashIndex]->value;
		}
		else { //find next free space

			HashEntry* temp = bucket[hashIndex];

			while (temp != NULL) {
				if (temp->key == key) {
					return temp->value;
				}

				temp = temp->next;
			}
			cout << "Value Not Found!" << endl;
			return -1;
		}
	}
	//删除操作，首先也是查询，查到则删除；增删查操作复杂度平均都为O(1)，仅在最坏情况下为O(n)
	void Delete(string key) {
		int hashIndex = getIndex(key);
		if (bucket[hashIndex] == NULL) {
			cout << "Value To Be Deleted Not Found!" << endl;
			return;
		}
		if (bucket[hashIndex]->key == key) {
			if (bucket[hashIndex]->next != NULL) {
				bucket[hashIndex] = bucket[hashIndex]->next;

			}
			else {
				bucket[hashIndex] = NULL;
			}
		}
		else { //find next free space

			HashEntry* temp = bucket[hashIndex];
			HashEntry* prev = bucket[hashIndex];
			while (temp != NULL) {

				if (temp->key == key) {
					if (temp->next != NULL) {
						prev->next = temp->next;
						temp = temp->next;
					}
					else
						prev->next = NULL;

					return;
				}
				prev = temp;
				temp = temp->next;
			}
			cout << "Value to be deleted not Found!" << endl;
		}
	}
};
//测试hashtable
void test_ht() {
	HashTable ht(4);
	ht.insert("London", 2);

	ht.insert("London", 10);
	ht.insert("New York", 15);
	ht.insert("Tokyo", 7);
	ht.insert("Bangkok", 2);
	ht.insert("Beijing", 6);
	ht.insert("Islamabad", 9);
	ht.insert("New Delhi", 17);
	ht.insert("Moscow", 12);
	ht.display();
	ht.resize();
	ht.display();
	ht.insert("Amsterdam", 5);
	ht.insert("Paris", 13);
	ht.insert("Istanbul", 19);
	ht.insert("Kuala Lumpur", 1);
	ht.insert("Jakarta", 8);
	ht.insert("Glasgow", 3);
	ht.insert("Seattle", 14);
	cout << ht.search("London") << endl;
	cout << ht.search("Moscow") << endl;
	cout << ht.search("Berlin") << endl;
	ht.display();
	ht.Delete("London");
	ht.display();
	ht.Delete("Moscow");
	ht.display();
	ht.Delete("Istanbul");
	ht.display();
}
/**
 * 哈希表对比字典树
 *
这两种数据结构都可以用于同一工作，但是它们的性能会根据程序的性质而有所不同。

基本操作
平均而言，哈希表可以在固定时间内执行搜索，插入和删除操作，而Trie通常在O（n）中工作。
但是，在最坏的情况下，哈希表的性能可能下降到O（n），其中n是哈希条目的总数。而最坏情况下的Trie可以取O（n * m）。

哈希函数
一个有效的哈希表需要一个智能哈希函数，该函数会将密钥分布在可用的所有空间上。
在这方面，Trie更易于实现，因为它仅在需要时才访问额外的空间，并且不需要哈希函数来优化其结构。

数据顺序
如果应用程序需要按特定顺序对数据进行排序，那么Trie将被证明更加有用，因为它的树结构有助于维护顺序。
如果数据可以随机存储，则哈希表是更明智的选择。
 *
 */
int val_2 = 2;
/**
 * unordered_map与unordered_set
 *
unordered_map是一个使用Map接口实现的容器。它以key-value成对的形式存储一个元素；它将值映射到键。
它提供了哈希的基本功能，以及一些有助于插入，删除和搜索过程的帮助程序功能。
unordered_map一些主要功能：
一个unordered_map存储key-value对（下面给出的示例）以将键映射到该值：
abc-> 123
xyz-> 456
unordered_map不能包含重复的密钥。但是，它可以具有重复的值。
unordered_map不会以key或的任何顺序存储元素value。
unordered_map使用哈希表进行实现。它获取密钥，然后使用哈希函数将其映射到哈希表范围内。
平均而言，基本操作的复杂度为 O（1）。在最坏的情况下它将上升到O（n）。

unordered_set是使用Set接口实现的C++容器。
它的构建方式也与unordered_map使用哈希表相同，但仍与哈希表unordered_map有很大不同。
unordered_set一些关键功能：
unordered_set是实现该Set接口的容器，并且此接口仅存储值，而不存储key-value对。
1->1
abc->abc
unordered_set不允许存储重复的元素，因为一个集合只能包含唯一的元素。
平均而言，基本操作的复杂度为O（1）。在最坏的情况下它将上升到O（n）。
 *
 */
int val_3 = 3;
/**
 * 练习：
 * 通过使用哈希表来查找给定的数组是否是另一个数组的子集
 */
#include <unordered_set>
bool isSubset(int* arr1, int* arr2, int size1, int size2) {
	if (size2 > size1)
	{
		//子集大小不能超过父集
		return false;
	}
	unordered_set<int> set;
	for (int i = 0; i < size1; i++)
	{
		if (set.find(arr1[i]) == set.end())//判断是否存在
			set.insert(arr1[i]);
	}
	for (int i = 0; i < size2; i++)
	{
		if (set.find(arr2[i]) == set.end())
		{
			return false;
		}
	}
	return true;
}
/**
 * 检查两数组是否不相交，跟上面反过来判断即可，有重合的元素则直接返回false
 */
bool isDisjoint(int* arr1, int* arr2, int size1, int size2) {
	unordered_set<int> set;
	for (int i = 0; i < size1; i++)
	{
		if (set.find(arr1[i]) == set.end()) set.insert(arr1[i]);
	}
	for (int i = 0; i < size2; i++)
	{
		if (set.find(arr2[i]) != set.end())	return false;
	}
	return true;
}
/**
 * 查找数组中对称对
 */
string findSymmetric(int arr[][2], int size) {
	// Create an empty hash table 
	unordered_set<string> hash;
	string result = " ";
	// Traverse rows of given 2D array
	for (int i = 0; i < size; i++) {
		// Store values in current row
		string pair = "{" + to_string(arr[i][0]) + ", " +
			to_string(arr[i][1]) + "}";
		// Store values in current row in reverse order
		string reverse = "{" + to_string(arr[i][1]) + ", " +
			to_string(arr[i][0]) + "}";
		// Check if reverse pair of current pair is already present in the hash table
		if (hash.find(reverse) != hash.end()) {
			//Symmetric pair found
			result += pair + reverse;
		}
		// Insert pair in hash table
		hash.insert(pair);

	}
	return result;
}
/**
 * 按顺序遍历
 map = {
  "NewYork": "Chicago",
  "Boston": "Texas",
  "Missouri": "NewYork",
  "Texas": "Missouri"
 }
 Boston->Texas, Texas->Missouri, Missouri->NewYork, NewYork->Chicago
 */
#include <unordered_map>
string tracePath(unordered_map<string, string> map) {

	string result = "";

	//Create a reverse Map of given map i.e if given map has (N,C) then reverse map will have (C,N) as key value pair
	//Traverse original map and see if corresponding key exist in reverse Map
	//If it doesn't exist then we found our starting point.
	//After starting point is found, simply trace the complete path from original map.
	unordered_map<string, string> reverseMap;
	unordered_map<string, string>::iterator itr;
	//To fill reverse map, iterate through the given map
	for (itr = map.begin(); itr != map.end(); itr++)
	{
		// itr works as a pointer to pair<string, string>
		// type itr->first stores the key part  and
		// itr->second stores the value part

		reverseMap[itr->second] = itr->first;
	}

	//Find the starting point of the journey
	string from = "";
	for (itr = map.begin(); itr != map.end(); itr++)
	{
		if (reverseMap.find(itr->first) == reverseMap.end()) {
			from = itr->first;
			break;
		}
	}

	//Trace complete path
	string to = map[from];
	unordered_map<string, string>::iterator To_itr;
	while ((map.find(to)) != map.end()) {
		result += from + "->" + to + ", ";
		from = to;
		to = (map.find(to))->second;
	}
	result += from + "->" + to + ", ";

	return result;
}
/**
 * 给定数组，找出两对和相等的结果
 */
string findPair(int* arr, int size) {

	string result = "";

	// Create HashMap with Key being sum and value being a pair i.e key = 3 , value = {1,2}
	// Traverse all possible pairs in given arr and store sums in map
	// If sum already exist then print out the two pairs.

	unordered_map<int, int*> hMap;
	int sum;
	int* prev_pair;
	for (int i = 0; i < size; ++i) {
		for (int j = i + 1; j < size; ++j) {
			sum = arr[i] + arr[j]; //calculate sum

			if (hMap.find(sum) == hMap.end()) {
				// If the sum is not present in Map then insert it along with pair
				int* temp_Arr = new int[2];
				temp_Arr[0] = arr[i];
				temp_Arr[1] = arr[j];
				hMap[sum] = temp_Arr;

			}
			else {
				//Sum already present in Map
				prev_pair = (hMap.find(sum))->second;
				// Since array elements are distinct, we don't
				// need to check if any element is common among pairs

				result += "{" + to_string(prev_pair[0]) + "," + to_string(prev_pair[1]) + "}{" + to_string(arr[i]) + "," + to_string(arr[j]) + "}";
				return result;


			}
		}
	}//end of for
	return result;
}
/**
 * 给定数组，找出是否有和为0的子集
 */
bool findSubZero(int* arr, int size) {

	//Use hMap to store Sum as key and index i as value till sum has been calculated.
	//Traverse the array and return true if either
	//arr[i] == 0 or sum == 0 or hMap already contains the sum
	//If you completely traverse the array and haven't found any of the above three
	//conditions then simply return false.
	unordered_map <int, int> hMap;

	int sum = 0;

	// Traverse through the given array
	for (int i = 0; i < size; i++) {
		sum += arr[i];
		//本身有0、按顺序加起来和为0、计算过程中出现两次相同的结果，三种情况都说明有和为0的子集
		if (arr[i] == 0 || sum == 0 || hMap.find(sum) != hMap.end())
			return true;

		hMap[sum] = i;
	}

	return false;
}
/**
 * 找出数组中第一个唯一的整数
 */
int findFirstUnique(int arr[], int size) {
	unordered_map <int, int> MP;  // createing hash map
	for (int i = 0; i < size; i++)
		MP[arr[i]]++;     // inserting elements in hash map
	//第一轮遍历记录每个值出现次数，第二轮遍历找出第一个只出现一次的值
	for (int i = 0; i < size; i++)
		if (MP[arr[i]] == 1)     // if value is equal to 1
			return arr[i];     // return that element
	return -1;
}
/**
 * 使用哈希表去掉链表中重复的值
 */
class Node {
public:
	int data; //Data to store (could be int,string,object etc)
	Node* nextElement; //Pointer to next element

	Node() {
		//Constructor to initialize nextElement of newlyCreated Node
		nextElement = nullptr;
	}
};
class LinkedList {
private:
	Node* head;
public:

	LinkedList() {
		head = nullptr;
	}

	Node* getHead() {
		return head;
	}

	bool isEmpty() {
		if (head == nullptr) //Check whether the head points to null
			return true;
		else
			return false;
	}

	bool printList() {
		if (isEmpty()) {
			cout << "List is Empty!";
			return false;
		}
		Node* temp = head;
		cout << "List : ";

		while (temp != nullptr) {
			cout << temp->data << "->";
			temp = temp->nextElement;
		}
		cout << "null " << endl;
		return true;
	}

	//Function inserts a value/new Node as the first Element of list
	void insertAtHead(int value) {
		Node* newNode = new Node();
		newNode->data = value;
		newNode->nextElement = head; //Linking newNode to head's nextNode
		head = newNode;
		cout << value << " Inserted!";
	}

	string elements() { // this function will return all values of linked List
		string elementsList = "";
		Node* start = head;

		while (start != nullptr) {
			elementsList += std::to_string(start->data);
			elementsList += "->";
			start = start->nextElement;
		}
		elementsList += "null";
		return elementsList;
	}

	void insertAtTail(int value) {
		if (isEmpty()) { // inserting first element in list
			insertAtHead(value);
		}
		else {
			Node* newNode = new Node();
			Node* last = head;

			while (last->nextElement != nullptr) {
				last = last->nextElement;
			}

			newNode->data = value;
			cout << value << " Inserted!    ";
			newNode->nextElement = nullptr;
			last->nextElement = newNode;
		}
	}

	bool search(int value) {
		Node* temp = head; // pointing temp to the head

		while (temp != nullptr) {
			if (temp->data == value) { // if passed value matches with temp's data
				return true;
			}
			temp = temp->nextElement; // pointig to temp's nextElement
		}
		return false; // if not found
	}

	bool deleteAtHead() {
		if (isEmpty()) { // check if lis is empty
			cout << "List is Empty" << endl;
			return false;
		}
		//if list is not empty, start traversing it from the head
		Node* currentNode = head; // currentNode pointing to head
		head = head->nextElement; //nextNode point to head's nextElement

		delete currentNode;
		return true;
	}

	bool Delete(int value) {
		bool deleted = false; //returns true if the node is deleted, false otherwise

		if (isEmpty()) { //check if the list is empty
			cout << "List is Empty" << endl;
			return deleted; //deleted will be false
		}

		//if list is not empty, start traversing it from the head
		Node* currentNode = head; //currentNode to traverse the list
		Node* previousNode = nullptr; //previousNode starts from null

		if (currentNode->data == value) { // deleting value of head
			deleted = deleteAtHead();
			cout << value << " deleted!" << endl;
			deleted = true; // true because value found and deleted
			return deleted; //returns true if the node is deleted
		}
		previousNode = currentNode;
		currentNode = currentNode->nextElement; // pointing current to current's nextElement
		//Traversing/Searching for Node to Delete
		while (currentNode != nullptr) {

			//Node to delete is found
			if (value == currentNode->data) {
				// pointing previousNode's nextElement to currentNode's nextElement
				previousNode->nextElement = currentNode->nextElement;
				delete currentNode;
				currentNode = previousNode->nextElement;
				deleted = true;
				break;
			}
			previousNode = currentNode;
			currentNode = currentNode->nextElement; // pointing current to current's nextElement
		}
		//deleted is true only when value is found and delted
		if (deleted == false) {
			cout << value << " does not exist!" << endl;
		}
		else {
			cout << value << " deleted!" << endl;
		}
		return deleted;
	}

	int length() {
		Node* current = head; // Start from the first element
		int count = 0; // in start count is 0

		while (current != nullptr) { // Traverse the list and count the number of nodes
			count++; // increment everytime as element is found
			current = current->nextElement; // pointing to current's nextElement
		}
		return count;
	}

	string reverse() {
		Node* previous = nullptr; //To keep track of the previous element, will be used in swapping links
		Node* current = head; //firstElement
		Node* next = nullptr;

		//While Traversing the list, swap links
		while (current != nullptr) {
			next = current->nextElement;
			current->nextElement = previous;
			previous = current;
			current = next;
		}

		head = previous; // pointing head to start of the list
		return elements(); // calling elements to return a string of values in list
	}
	string removeDuplicates();
	string Union(LinkedList list1, LinkedList list2);
	string Intersection(LinkedList list1, LinkedList list2);
};
string LinkedList::removeDuplicates() {
	Node* current, * previous;
	current = head;
	previous = current;
	unordered_set<int> hash;

	/* Pick elements one by one */
	while (current != nullptr) {
		/* If duplicate then delete it */
		if (hash.find(current->data) != hash.end()) {
			previous->nextElement = current->nextElement;
			delete(current);
		}
		else {
			hash.insert(current->data);
			previous = current;
		}
		current = previous->nextElement;
	}
	return elements();
}
/**
 * 使用哈希表找交并集
 */
string LinkedList::Union(LinkedList list1, LinkedList list2) {
	//Return other List if one of them is empty
	if (list1.isEmpty())
		return list2.elements();
	else if (list2.isEmpty())
		return list1.elements();

	unordered_set < int > visited;
	LinkedList list3;

	Node* node1 = list1.head;
	Node* node2 = list2.head;
	//遍历两个链表，通过哈希表判断是否有相同元素，只将不同的放入新链表，最终结果为并集
	//Traverse first list till the last element
	while (node1 != NULL) {
		// Add current element of list1 in list3 if it not repeated yet
		if (visited.find(node1->data) == visited.end()) {
			list3.insertAtHead(node1->data);
			visited.insert(node1->data);
		}
		node1 = node1->nextElement;
	}
	//Traverse second list till the last element 
	while (node2 != NULL) {
		// Add current element of list2 in list3 if it not repeated yet
		if (visited.find(node2->data) == visited.end()) {
			list3.insertAtHead(node2->data);
			visited.insert(node2->data);
		}
		node2 = node2->nextElement;
	}
	return list3.elements();
}


string LinkedList::Intersection(LinkedList list1, LinkedList list2) {
	unordered_set < int > visited;
	LinkedList list3;

	Node* node1 = list1.head;
	Node* node2 = list2.head;
	//遍历两个链表，通过哈希表判断是否有相同元素，只将相同的放入新链表，最终结果为交集
	//Traverse first list till the last element
	while (node1 != NULL) {
		// Add current element of list1 in hash set if it not repeated yet
		if (visited.find(node1->data) == visited.end()) {
			visited.insert(node1->data);
		}
		node1 = node1->nextElement;
	}
	//Traverse second list till the last element 
	while (node2 != NULL) {
		// Add current element of list2 in list3 if is present in the hash set
		if (visited.find(node2->data) != visited.end()) {
			list3.insertAtHead(node2->data);
			visited.erase(node2->data);
		}
		node2 = node2->nextElement;
	}
	return list3.elements();
}
/**
 * 给定数组，找出两个和为指定值的元素
 * 同leetcode两数之和题目
 */
int* findSum(int arr[], int sum, int size) {
	unordered_set<int> set;
	int* ret = new int[2];
	for (int i = 0; i < size; i++)
	{
		if (set.find(sum - arr[i]) != set.end())
		{
			ret[0] = arr[i];
			ret[1] = sum - arr[i];
			break;
		}
		set.insert(arr[i]);
	}
	return ret;
}

int main()
{
	test_ht();
}

