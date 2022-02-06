#ifndef TREE_HPP
#define TREE_HPP

#include "public_header.hpp"
#include <queue>

BEGIN_NAMESPACE(yyyyshen)

//����������
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
		node* tmp = root, * ptmp = nullptr;//ptmp��¼ɾ��λ�õĸ��ڵ�
		//Ѱ��ɾ����
		while (tmp != nullptr && tmp->data != val)
		{
			ptmp = tmp;
			if (val > tmp->data)
				tmp = tmp->right;
			else
				tmp = tmp->left;
		}
		if (tmp == nullptr)
			return;//û�ҵ�
		//ɾ���ڵ��������ӽڵ�
		if (tmp->left != nullptr && tmp->right != nullptr)
		{
			//��ҪѰ�Һ�̽ڵ㣬Ҳ������������С�Ľڵ�
			node* minp = tmp->right, * minpp = tmp;
			while (minp->left != nullptr)
			{
				minpp = minp;
				minp = minp->left;
			}
			//�ҵ�����ֻ�ǽ���ֵ
			tmp->data = minp->data;
			//��ɾ������ͳһ�������߼���
			ptmp = minpp;
			tmp = minp;
		}
		//�ߵ������߼���ɾ���˻�Ϊɾ������Ҷ�ڵ�����һ���ӽڵ�
		//������ӽڵ㣬��¼����
		node* child;
		if (tmp->left != nullptr)
			child = tmp->left;
		else if (tmp->right != nullptr)
			child = tmp->right;
		else
			child = nullptr;//����ͳһ�߼�
		//��󣬽�ɾ�����ӽڵ�ӵ��丸�ڵ���
		if (ptmp == nullptr)//���������߼������ڵ�Ϊ�գ�˵��ɾ�����Ǹ��ڵ�
			root = child;
		else if (tmp == ptmp->left)
			ptmp->left = child;
		else
			ptmp->right = child;
		//ִ������ɾ��
		delete tmp;
	}
	int prenode(int val)
	{
		if (root == nullptr) return -1;
		if (root->left == nullptr && root->right == nullptr) return -1;//ֻ��һ���ڵ�
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
		if (tmp == nullptr) return -1;//û�ҵ�
		//Ѱ�������������ڵ�
		if (tmp->left != nullptr)
		{
			node* maxp = tmp->left;
			while (maxp->right != nullptr)
				maxp = maxp->right;
			return maxp->data;
		}
		//û���������������丸�ڵ�
		if (ptmp == nullptr)
			return -1;
		else
			return ptmp->data;
	}
	int postnode(int val)
	{
		//��ǰ��ͬ������������������ҵ�ͷ
		return 0;
	}
	void order(node* root)
	{
		if (root == nullptr)
			return;

		//�ݹ鹫ʽ
		//�߼���ǰ����ǰ�����
		order(root->left);
		std::cout << root->data << " " << std::endl;//�������
		order(root->right);
		//�߼��ź����Ǻ������
	}
	//�������������һ�����У�ÿ�γ��ӵ�ǰ�㣬������һ��ڵ����
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
