#pragma once

template<class K,class V>
struct BSTNode{
	BSTNode<K,V> *_left;
	BSTNode<K,V> *_right;
	K _key;
	V _value;

	BSTNode(const K &key,const V &value)
		:_left(NULL)
		,_right(NULL)
		,_key(key)
		,_value(value)
	{}
};

template<class K,class V>
class BinarySearchTree{
	typedef BSTNode<K,V> Node;
public:
	BinarySearchTree()
		:_root(NULL)
	{}

	~BinarySearchTree()
	{}

	bool Insert(const K &key,const V &value)
	{
		if(_root == NULL)
		{
			_root = new Node(key,value);
			return true;
		}
		Node *cur = _root;
		Node *parent = NULL;
		while(cur != NULL)
		{
			if(cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if(cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
				return false;
		}
		Node *node = new Node(key,value);
		if(key > parent->_key)
		{
			parent->_right = node;
			return true;
		}
		else
		{
			parent->_left = node;
			return true;
		}
	}
	bool Insert_R(const K &key,const V &value)
	{
		return _Insert_R(_root,key,value);
	}
	bool Remove(const K &key)
	{
		if(_root ->_left == NULL && _root->_right == NULL)
		{
			delete _root;
			_root = NULL;
			return true;
		}
		Node *del = _root;
		Node *parent = _root;
		while(del != NULL)
		{
			if(del->_key > key)
			{
				parent = del;
				del = del->_left;
			}
			else if(del->_key < key)
			{
				parent = del;
				del = del->_right;
			}
			else
				break;
		}
		if(del != NULL)
		{
			if(del->_left == NULL)     //缺左子树就用右子树来补
			{
				if(del != _root)
				{
					if(parent->_left = del)
						parent->_left = del->_right;
					else
						parent->_right = del->_right;
				}
				else
				{
					_root = del->_right;
				}
			}
			else if(del->_right == NULL)   //缺右子树就用左子树来补
			{
				if(del != _root)
				{
					if(parent->_left = del)
						parent->_left = del->_left;
					else
						parent->_right = del->_left;
				}
				else
				{
					_root = del->_left;
				}
			}
			else     //左右都不为空就与右子树上中序遍历的第一个数交换
			{
				Node *firstInOrder = del->_right;
				parent = del;
				while(firstInOrder->_left == NULL)
				{
					parent = firstInOrder;
					firstInOrder = firstInOrder->_left;
				}
				swap(del->_key,firstInOrder->_key);
				swap(del->_value,firstInOrder->_value);
				del = firstInOrder;

				if(parent->_left = del)    //firstInOrder的左数必为空
					parent->_left = del->_right;
				else
					parent->_right = del->_right;
			}
			delete del;
			return true;
		}
		else
		{
			return false;
		}

	}
	bool Remove_R(const K &key)
	{
		return _Remove_R(_root,key);
	}
	bool Find(const K &key)
	{
		Node *cur = _root;
		while(cur != NULL)
		{
			if(cur->_key > key)
				cur = cur->_left;
			else if(cur->_key < key)
				cur = cur->_right;
			else 
				return true;
		}
		return false;
	}
	bool Find_R(const K &key)
	{
		return _Find_R(_root,key);
	}
protected:
	bool _Insert_R(Node* &root,const K &key,const V &value)
	{
		if(root == NULL)
		{
			root = new Node(key,value);
			return true;
		}
		if(key > root->_key)
			return _Insert_R(root->_right,key,value);
		if(key < root->_key)
			return _Insert_R(root->_left,key,value);
		else
			return false;
	}
	bool _Remove_R(Node * &root,const K &key)
	{
		if(root == NULL)
		{
			return false;
		}
		if(root->_key > key)
			_Remove_R(root->_left,key);
		else if(root->_key < key)
			_Remove_R(root->_right,key);
		else                    //root->_key == key
		{
			Node *del;
			if(root->_left == NULL)     //缺左子树就用右子树来补
			{
				delete root
				root = root->_right;
			}
			else if(del->_right == NULL)   //缺右子树就用左子树来补
			{
				delete root;
				root = root->_left;
			}
			else     //左右都不为空就与右子树上中序遍历的第一个数交换
			{
				Node *firstInOrder = root->_right;
				while(firstInOrder->_left == NULL)
				{
					firstInOrder = firstInOrder->_left;
				}
				swap(root->_key,firstInOrder->_key);
				swap(root->_value,firstInOrder->_value;

				return _Remove_R(root->_right,key);
		}
	}
	bool _Find_R(Node *root,const K &key)
	{
		if(root == NULL)
			return false;
		if(root->_key > key)
			_Find_R(root->_left,key);
		else if(root->_key < key)
			_Find_R(root->_right,key);
		else 
			return true;
	}
private:
	Node *_root;
};