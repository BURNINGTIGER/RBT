#include <iostream>

const bool black = 1;
const bool red = 0;


template<typename T> 
struct Node
{
	T value;
	bool color;
	Node* left;
	Node* right;
	Node* parent;
};

template<typename T> 
class RBT
{
private:
	Node<T>* root;
	Node<T>* NIL;
public:
	RBT()
	{
		NIL = new Node<T>;
		NIL->left = NIL->parent = NIL->right = nullptr;
		NIL->color = black;
		root = NIL;
	}

	bool _color(const T& value)const
	{
		return search(value)->color;
	}

	Node<T>* _root()const
	{
		return root;
	}

	Node<T>* _NIL()const
	{
		return NIL;
	}

	void leftRotate(Node<T>* current)
	{
		Node<T>* temp = current->right;
		current->right = temp->left;
		if (temp->left != NIL)
			temp->left->parent = current;
		if (temp != NIL)
			temp->parent = current->parent;
		if (current->parent != NIL)
		{
			if (current == current->parent->left)
				current->parent->left = temp;
			else
				current->parent->right = temp;
		}
		else
		{
			root = temp;
		}
		temp->left = current;
		if (current != NIL)
			current->parent = temp;
	}

	void rightRotate(Node<T> *current)
	{
		Node<T> *temp = current->left;
		current->left = temp->right;
		if (temp->right != NIL)
			temp->right->parent = current;
		if (temp != NIL)
			temp->parent = current->parent;
		if (current->parent != NIL)
		{
			if (current == current->parent->right)
				current->parent->right = temp;
			else
				current->parent->left = temp;
		}
		else
		{
			root = temp;
		}


		temp->right = current;
		if (current != NIL)
			current->parent = temp;
	}


	void insertFixup(Node<T>* current)
	{
		while (current != root && current->parent->color == red)
		{
			if (current->parent == current->parent->parent->left)
			{
				Node<T>* temp = current->parent->parent->right;
				if (temp->color == red)
				{
					current->parent->color = black;
					temp->color = black;
					current->parent->parent->color = red;
					current = current->parent->parent;
				}

				else
				{
					if (current == current->parent->right)
					{
						current = current->parent;
						leftRotate(current);
					}
					current->parent->color = black;
					current->parent->parent->color = red;
					rightRotate(current->parent->parent);
				}
			}

			else
			{
				Node<T>* temp = current->parent->parent->left;
				if (temp->color == red)
				{
					current->parent->color = black;
					temp->color = black;
					current->parent->parent->color = red;
					current = current->parent->parent;
				}
				else
				{
					if (current == current->parent->left)
					{
						current = current->parent;
						rightRotate(current);
					}
					current->parent->color = black;
					current->parent->parent->color = red;
					leftRotate(current->parent->parent);
				}
			}
		}
		root->color = black;
	}


	void insert(const T& added)
	{
		if (search(added))
		{
			std::cout << "This value's already added in the tree\n";
			return;
		}
		Node<T>* daughter = new Node<T>;
		daughter->value = added;
		daughter->color = red;
		daughter->left = daughter->right = daughter->parent = NIL;
		Node<T>* parent = NIL;
		Node<T>* temp = root;
		if (root == NIL)
		{
			root = daughter;
			root->color = black;
			return;
		}
		while (temp != NIL)
		{

			if (daughter->value == temp->value)
				return;

			parent = temp;
			if (added < temp->value)
				temp = temp->left;
			else
				temp = temp->right;
		}
		if (added < parent->value)
		{
			parent->left = daughter;
		}
		else
		{
			parent->right = daughter;

		}
		daughter->parent = parent;
		insertFixup(daughter);
	}

	Node<T>* search(const T& value)const
	{
		Node<T>* current = root;
		while (current != NIL)
		{
			if (value == current->value)
				return current;
			else
			{
				if (value < current->value)
					current = current->left;
				else current = current->right;
			}
		}
		return 0;
	}
};
