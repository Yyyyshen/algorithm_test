// data_struct_cpp_07.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
/**
 * Trie
 * 字典树，常用于解决字符串相关问题，如：自动完成、拼写检查、搜索电话
 *
 * 特性：
 * 与图相似，因为它们是节点的组合，其中每个节点代表一个唯一的字母。
 * 每个节点可以指向None或其他子节点。
 * 大小取决于字母的数量。例如，在英语中，有26个字母，因此唯一数nodes不能超过26。
 * 深度取决于它存储的最长单词。
 * 另一个重要特性是，它为共享公共前缀的单词提供了相同的路径。
 * 例如，“ there”和“ their”具有共同的前缀“ the”。因此，它们将共享相同的路径，直到“ e”为止。之后，路径将分为两个分支
 */
#define ALPHABET_SIZE 26
 //基本结构
class TrieNode {
public:
	TrieNode* children[ALPHABET_SIZE];
	bool isEndWord;

	TrieNode() {
		this->isEndWord = false;
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			this->children[i] = NULL;
		}
	}
	//Function to mark the currentNode as Leaf
	void markAsLeaf() {
		this->isEndWord = true;
	}
	//Function to unMark the currentNode as Leaf
	void unMarkAsLeaf() {
		this->isEndWord = false;
	}
};
class Trie {
private:
	TrieNode* root;

public:
	Trie() {
		root = new TrieNode();
	}
	//Function to get the index of a character 't'
	int getIndex(char t) {
		return t - 'a';
	}
	TrieNode* getRoot() {
		return root;
	}
	//Function to insert a key,value pair in the Trie
	void insertNode(string key) {
		//Empty string is not allowed
		if (key.empty())
			return;

		//using transform() function and ::tolower in STL to convert 'key' to lowercase
		transform(key.begin(), key.end(), key.begin(), ::tolower);
		TrieNode* currentNode = root;
		int index = 0;

		//Iterate the trie with the given character index,
		//If the index points to NULL
		//simply create a TrieNode and go down a level
		for (int level = 0; level < key.length(); level++) {
			index = getIndex(key[level]);

			if (currentNode->children[index] == NULL) {
				currentNode->children[index] = new TrieNode();
				cout << key[level] << " inserted" << endl;
			}
			currentNode = currentNode->children[index];
		}

		//Mark the end character as leaf node
		currentNode->markAsLeaf();
		cout << "'" << key << "' inserted" << endl;
	}
	//Function to search given key in Trie
	bool searchNode(string key) {
		if (key.empty())
			return false;

		//using transform() function and ::tolower in STL to convert 'key' to lowercase
		transform(key.begin(), key.end(), key.begin(), ::tolower);
		TrieNode* currentNode = root;
		int index = 0;

		//Iterate the Trie with given character index,
		//If it is NULL at any point then we stop and return false
		//We will return true only if we reach leafNode and have traversed the
		//Trie based on the length of the key
		for (int level = 0; level < key.length(); level++) {
			index = getIndex(key[level]);

			if (currentNode->children[index] == NULL)
				return false;
			currentNode = currentNode->children[index];
		}
		if (currentNode != NULL and currentNode->isEndWord)
			return true;

		return false;
	}
	//Function to delete given key from Trie
	void deleteNode(string key) {
		if ((root == NULL) || (key.empty())) {
			cout << "Null key or Empty trie error\n";
			return;
		}
		deleteHelper(key, root, key.length(), 0);
	}
	bool hasNoChildren(TrieNode* currentNode) {
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			if ((currentNode->children[i]) != NULL)
				return false;
		}
		return true;
	}
	//Recursive function to delete given key
	bool deleteHelper(string key, TrieNode* currentNode, int length, int level) {
		bool deletedSelf = false;

		if (currentNode == NULL) {
			cout << "Key does not exist\n";
			return deletedSelf;
		}

		//Base Case: If we have reached at the node which points to the alphabet at the end of the key.
		if (level == length) {
			//If there are no nodes ahead of this node in this path
			//Then we can delete this node
			if (hasNoChildren(currentNode)) {
				delete currentNode; //free the memory 
				currentNode = NULL; //clear the pointer by pointing it to NULL
				deletedSelf = true;
			}
			//If there are nodes ahead of currentNode in this path 
			//Then we cannot delete currentNode. We simply unmark this as leaf
			else {
				currentNode->unMarkAsLeaf();
				deletedSelf = false;
			}
		}
		else {
			TrieNode* childNode = currentNode->children[getIndex(key[level])];
			bool childDeleted = deleteHelper(key, childNode, length, level + 1);
			if (childDeleted) {
				//Making children pointer also null: since child is deleted
				currentNode->children[getIndex(key[level])] = NULL;
				//If currentNode is leaf node that means currntNode is part of another key
				//and hence we can not delete this node and it's parent path nodes
				if (currentNode->isEndWord) {
					deletedSelf = false;
				}
				//If childNode is deleted but if currentNode has more children then currentNode must be part of another key.
				//So, we cannot delete currenNode
				else if (!hasNoChildren(currentNode)) {
					deletedSelf = false;
				}
				//Else we can delete currentNode
				else {
					currentNode = NULL;
					deletedSelf = true;
				}
			}
			else {
				deletedSelf = false;
			}
		}
		return deletedSelf;
	}

};
/**
 * 字典树中包含的单词数量
 */
int totalWords(TrieNode* root) {
	int result = 0;

	// Leaf denotes end of a word
	if (root->isEndWord)
		result++;

	for (int i = 0; i < 26; i++)
		if (root->children[i] != NULL)
			result += totalWords(root->children[i]);
	return result;
}
/**
 * 找出字典树中所有单词
 */
void getWords(TrieNode* root, vector<string>& result, int level, string& word)
{
	//Leaf denotes end of a word
	if (root->isEndWord) {
		//current word is stored till the 'level' in the word string
		string temp = "";
		for (int x = 0; x < level; x++) {
			temp += word[x];
		}
		result.push_back(temp);
	}
	for (int i = 0; i < 26; i++) {
		if (root->children[i] != NULL) {
			//Non-null child, so add that index to the word string
			word[level] = (char)(i + 'a');
			getWords(root->children[i], result, level + 1, word);
		}
	}
}
vector<string> findWords(TrieNode* root)
{
	vector<string> result;
	string word = "";
	getWords(root, result, 0, word);
	return result;
}
/**
 * 使用字典树排序字符串数组
 */
vector<string> sortArray(string arr[], int arr_length) {
	vector<string> result;
	//先存入字典树，再进行先序遍历
	//Creating Trie and Inserting words from array
	Trie* trie = new Trie();
	for (int x = 0; x < arr_length; x++)
		trie->insertNode(arr[x]);

	string str;
	getWords(trie->getRoot(), result, 0, str);
	return result;
}
/**
 * 使用字典树判断是否可进行匹配
 */
bool isFormationPossible(vector<string> list, string word) {
	//Create Trie and insert vector elements in it
	Trie* trie = new Trie();

	for (int x = 0; x < list.size(); x++) {
		trie->insertNode(list[x]);
	}

	TrieNode* currentNode = trie->getRoot();

	for (int i = 0; i < word.size(); i++) {
		char index = trie->getIndex(word[i]);
		// if the prefix of word does not exist, word would not either
		if (currentNode->children[index] == NULL) {
			return false;
		}
		// if the substring of the word exists as a word in trie, check whether rest of the word also exists, if it does return true
		else if (currentNode->children[index]->isEndWord == true && trie->searchNode(word.substr(i + 1))) {
			return true;
		}
		currentNode = currentNode->children[index];
	}
	return false;
}

int main()
{
	std::cout << "Hello World!\n";
}

