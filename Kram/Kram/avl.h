#pragma once

#include <algorithm>

template<class _Ty>
class AVL;

template<class _Ty>
class AVLNode
{
private:
	_Ty data;
	size_t height;
	AVLNode* left;
	AVLNode* right;
	AVLNode* parent;

	AVLNode(const _Ty& data, size_t height = 1, AVLNode* parent = nullptr, AVLNode* left = nullptr, AVLNode* right = nullptr) :
		data{ data },
		height{ height },
		left{ left },
		right{ right },
		parent{ parent }
	{}
	AVLNode(_Ty&& data, size_t height = 1, AVLNode* parent = nullptr, AVLNode* left = nullptr, AVLNode* right = nullptr) :
		data{ data },
		height{ height },
		left{ left },
		right{ right },
		parent{ parent }
	{}

public:
	template<class _Ty> friend class AVL;
};


template<class _Ty>
class AVL
{
public:
	using data_t = _Ty;

private:
	AVL* _left;
	AVL* _right;
	AVL* _parent;
	size_t _height;
	data_t _data;

public:
	AVL(const data_t& data) :
		_left{ nullptr },
		_right{ nullptr },
		_parent{ nullptr },
		_height{ 1 },
		_data{ data }
	{}
	AVL(data_t&& data) :
		_left{ nullptr },
		_right{ nullptr },
		_parent{ nullptr },
		_height{ 1 },
		_data{ std::move(data) }
	{}

private:
	static constexpr size_t _Height(const AVL* node) { return node ? node->_height : 0; }

	static constexpr int _GetBalance(const AVL* node) { return node ? _Height(node->_left) - _Height(node->_right) : 0; }

	void _UpdateHeight() { _height = std::max(_Height(_left), _Height(_right)) + 1; }

	AVL* _RightRotate()
	{
		AVL* x = _left;
		AVL* y = this;
		AVL* T2 = x->_right;

		// Perform rotation
		x->_right = y;
		y->_left = T2;

		// Update heights
		y->_UpdateHeight();
		x->_UpdateHeight();

		// Return new root
		return x;
	}

	AVL* _LeftRotate()
	{
		AVL* x = this;
		AVL* y = x->_right;
		AVL* T2 = x->_left;

		// Perform rotation
		y->_left = x;
		x->_right = T2;

		// Update heights
		x->_UpdateHeight();
		y->_UpdateHeight();

		// Return new root
		return y;
	}

	static constexpr AVL* _MinNode(const AVL* node)
	{
		while (node->_left)
			node = node->_left;
		return node;
	}

	AVL* _ToBalance()
	{
		int balance = _GetBalance(this);

		// If this node becomes unbalanced, then there are 4 cases

		if (balance > 1)
		{
			// Left Left Case
			if (data < _left->_data)
				return _RightRotate();

			// Left Right Case
			else if (data > _left->_data)
			{
				_left = _left->_LeftRotate();
				return _RightRotate();
			}
		}
		else if (balance < -1)
		{
			// Right Right Case
			if (data > _right->_data)
				return _LeftRotate();

			// Right Left Case
			else if (data < _right->_data)
			{
				_right = _right->_RightRotate();
				return _LeftRotate();
			}
		}

		/* return the (unchanged) node pointer */
		return this;
	}

	AVL* _Insert(data_t&& data)
	{
		/* 1.  Perform the normal BST rotation */
		if (data < _data)
			_left = _left ? _Insert(_left, data) : new AVL{ data };
		else _right = _right ? _Insert(_right, data) : new AVL{ data };

		/* 2. Update height of this ancestor node */
		_UpdateHeight();

		/* 3. Get the balance factor of this ancestor node to check whether this node became unbalanced */
		return _ToBalance();
	}

	AVL* _Remove(const data_t& data)
	{
		// STEP 1: PERFORM STANDARD BST DELETE

		AVL* root = this;

		// If the value to be deleted is smaller than the root's value,
		// then it lies in left subtree
		if (data < root->_data)
			root->_left = root->_left->_Remove(data);

		// If the value to be deleted is greater than the root's value,
		// then it lies in right subtree
		else if (data > _data)
			root->_right = root->_right->_Remove(data);

		// if value is same as root's value, then This is the node
		// to be deleted
		else
		{
			// node with only one child or no child
			if (!root->_left || !root->_right)
			{
				AVL* temp = root->_left ? root->_left : root->_right;

				// No child case
				if (!temp)
				{
					temp = root;
					root = nullptr;
				}
				else root = temp;
			}
			else
			{
				// node with two children: Get the inorder successor (smallest
				// in the right subtree)
				AVL* temp = _MinNode(root->_right);

				// Copy the inorder successor's data to this node
				root->_data = temp->_data;

				// Delete the inorder successor
				root->_right = root->_Remove(temp->_data);
			}
		}

		// If the tree had only one node then return
		if (!root)
			return nullptr;

		// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
		root->_UpdateHeight();

		// STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether
		//  this node became unbalanced)
		return root->_ToBalance();
	}

public:
	size_t height() const { return _height; }

	void in_order(void(*action)(data_t&)) const
	{
		if (_left)
			_left->in_order(action);
		action(_data);
		if (_right)
			_right->in_order(action);
	}

	inline void insert(const data_t& data) { _Insert(data); }
	inline void insert(data_t&& data) { _Insert(data); }

	inline void remove(const data_t& data) { _Remove(data); }
};
