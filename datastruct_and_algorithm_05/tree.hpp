#ifndef TREE_HPP
#define TREE_HPP

#include "public_header.hpp"
#include <queue>

BEGIN_NAMESPACE(yyyyshen)

//二叉搜索树
struct node
{
	int data;
	node* left;
	node* right;
	node(int val) :data(val), left(nullptr), right(nullptr) {}
};
class binary_search_tree final
{
public:
	binary_search_tree() = default;
	~binary_search_tree()
	{

	}
public:
	bool find(int val) noexcept
	{
		if (root == nullptr) return false;
		node* tmp = root;
		while (tmp != nullptr)
		{
			if (tmp->data == val)
				return true;
			else if (tmp->data > val)
				tmp = tmp->left;
			else
				tmp = tmp->right;
		}
		return false;
	}
	int max() noexcept
	{
		if (root == nullptr) return -1;
		node* tmp = root;
		while (tmp->right != nullptr)
			tmp = tmp->right;
		return tmp->data;
	}
	int min() noexcept
	{
		if (root == nullptr) return -1;
		node* tmp = root;
		while (tmp->left != nullptr)
			tmp = tmp->left;
		return tmp->data;
	}
	void insert(int val)
	{
		node* new_node = new node(val);
		if (new_node == nullptr)
			return;
		if (root == nullptr)
		{
			root = new_node;
			return;
		}
		node* tmp = root;
		while (tmp != nullptr)
		{
			if (val < tmp->data)
			{
				if (tmp->left == nullptr)
				{
					tmp->left = new_node;
					return;
				}

				tmp = tmp->left;
			}
			else
			{
				if (tmp->right == nullptr)
				{
					tmp->right == new_node;
					return;
				}
				tmp = tmp->right;
			}
		}
	}
	void del(int val)
	{
		if (root == nullptr) return;
		node* tmp = root, * ptmp = nullptr;//ptmp记录删除位置的父节点
		//寻找删除点
		while (tmp != nullptr && tmp->data != val)
		{
			ptmp = tmp;
			if (val > tmp->data)
				tmp = tmp->right;
			else
				tmp = tmp->left;
		}
		if (tmp == nullptr)
			return;//没找到
		//删除节点右两个子节点
		if (tmp->left != nullptr && tmp->right != nullptr)
		{
			//需要寻找后继节点，也就是右子树最小的节点
			node* minp = tmp->right, * minpp = tmp;
			while (minp->left != nullptr)
			{
				minpp = minp;
				minp = minp->left;
			}
			//找到后先只是交换值
			tmp->data = minp->data;
			//将删除工作统一到后续逻辑中
			ptmp = minpp;
			tmp = minp;
		}
		//走到如下逻辑，删除退化为删除的是叶节点或仅有一个子节点
		//如果有子节点，记录下来
		node* child;
		if (tmp->left != nullptr)
			child = tmp->left;
		else if (tmp->right != nullptr)
			child = tmp->right;
		else
			child = nullptr;//方便统一逻辑
		//最后，将删除点子节点接到其父节点上
		if (ptmp == nullptr)//走完所有逻辑，父节点为空，说明删除的是根节点
			root = child;
		else if (tmp == ptmp->left)
			ptmp->left = child;
		else
			ptmp->right = child;
		//执行真正删除
		delete tmp;
	}
	int prenode(int val)
	{
		if (root == nullptr) return -1;
		if (root->left == nullptr && root->right == nullptr) return -1;//只有一个节点
		node* tmp = root, * ptmp = nullptr;
		while (tmp != nullptr)
		{
			if (tmp->data == val)
				break;
			ptmp = tmp;
			if (tmp->data > val)
				tmp = tmp->left;
			else
				tmp = tmp->right;
		}
		if (tmp == nullptr) return -1;//没找到
		//寻找左子树中最大节点
		if (tmp->left != nullptr)
		{
			node* maxp = tmp->left;
			while (maxp->right != nullptr)
				maxp = maxp->right;
			return maxp->data;
		}
		//没有左子树，则是其父节点
		if (ptmp == nullptr)
			return -1;
		else
			return ptmp->data;
	}
	int postnode(int val)
	{
		//与前驱同理，后继是右子树往左找到头
		return 0;
	}
	void order(node* root)
	{
		if (root == nullptr)
			return;

		//递归公式
		//逻辑放前面是前序遍历
		order(root->left);
		std::cout << root->data << " " << std::endl;//中序遍历
		order(root->right);
		//逻辑放后面是后序遍历
	}
	//层序遍历，利用一个队列，每次出队当前层，并将下一层节点入队
	void level_order()
	{
		if (root == nullptr) return;
		std::queue<node*> q;
		q.push(root);
		node* tmp;
		while (!q.empty())
		{
			tmp = q.front();
			std::cout << tmp->data << " " << std::endl;
			q.pop();
			if (tmp->left != nullptr)
				q.push(tmp->left);
			if (tmp->right != nullptr)
				q.push(tmp->right);
		}
	}
	

private:
	node* root = nullptr;
};

END_NAMESPACE(yyyyshen)

#endif // !TREE_HPP
