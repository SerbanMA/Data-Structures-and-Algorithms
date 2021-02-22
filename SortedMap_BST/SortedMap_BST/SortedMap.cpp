#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

//BC = O(log(n)) AC = O(log(n)) WC = O(n)
Node* SortedMap::minValueNode(Node* node)
{
	Node* current = node;
	Node* minNode = node;

	while (current != nullptr)
	{
		minNode = current;
		current = current->left;
	}

	return minNode;
}

//Theta(1)
SortedMap::SortedMap(Relation r)
{
	this->root = nullptr;
	this->relation = r;
	this->numberOfElements = 0;
}

//BC = O(log(n)) AC = O(log(n)) WC = O(n)
TValue SortedMap::add(TKey k, TValue v)
{
	Node* current = this->root;
	Node* parent = nullptr;

	while (current != nullptr)
	{
		parent = current;
		if (current->info.first == k)
		{
			TValue oldValue = current->info.second;
			current->info.second = v;
			return oldValue;
		}

		else if (this->relation(k, current->info.first))
			current = current->left;

		else
			current = current->right;
	}

	Node* newNode = new Node{ TElem(k, v) };
	if (this->root == nullptr)
		this->root = newNode;

	else if (this->relation(k, parent->info.first))
		parent->left = newNode;

	else
		parent->right = newNode;

	this->numberOfElements++;
	return NULL_TVALUE;
}

//BC = O(log(n)) AC = O(log(n)) WC = O(n)
int SortedMap::addIfNotPresent(SortedMap& sm)
{
	SMIterator it = sm.iterator();
	int nr = 0;

	while (it.valid())
	{
		if (this->search(it.getCurrent().first) == NULL_TVALUE)
		{
			nr++;
			this->add(it.getCurrent().first, it.getCurrent().second);
		}
		it.next();
	}
	return nr;
}

//BC = O(log(n)) AC = O(log(n)) WC = O(n)
TValue SortedMap::search(TKey k) const 
{
	Node* current = this->root;

	while (current != nullptr)
	{
		if (current->info.first == k)
			return current->info.second;

		else if (this->relation(k, current->info.first))
			current = current->left;

		else
			current = current->right;
	}

	return NULL_TVALUE;
}

//BC = O(log(n)) AC = O(log(n)) WC = O(n)
Node* SortedMap::removeRecursively(Node* node, TKey k, TValue& v)
{
	if (node == NULL) 
		return node;

	// if info is same as node's key, then this is the node 
	// to be deleted 
	if (k == node->info.first)
	{
		v = node->info.second;
		// node with only one child or no child 
		if (node->left == NULL)
		{
			Node* temp = node->right;
			free(node);
			return temp;
		}
		else if (node->right == NULL)
		{
			Node* temp = node->left;
			free(node);
			return temp;
		}

		// node with two children: Get the inorder successor (smallest 
		// in the right subtree) 
		Node* temp = minValueNode(node->right);

		// Copy the inorder successor's content to this node 
		node->info = temp->info;

		// Delete the inorder successor 
		node->right = removeRecursively(node->right, temp->info.first, v);
	}

	// If the key to be deleted is smaller than the node's key, 
	// then it lies in left subtree 
	else if (this->relation(k, node->info.first))
		node->left = removeRecursively(node->left, k, v);

	// If the key to be deleted is greater than the node's key, 
	// then it lies in right subtree 
	else
		node->right = removeRecursively(node->right, k, v);

	return node;
}

//BC = O(log(n)) AC = O(log(n)) WC = O(n)
TValue SortedMap::remove(TKey k) 
{
	TValue v = NULL_TVALUE;
	this->root = removeRecursively(this->root, k, v);

	if (v != NULL_TVALUE)
		this->numberOfElements--;
	return v;
}

//Theta(1)
int SortedMap::size() const 
{
	return this->numberOfElements;
}

//Theta(1)
bool SortedMap::isEmpty() const 
{
	return this->numberOfElements == 0;
}

//Theta(1)
SMIterator SortedMap::iterator() {
	return SMIterator(*this);
}

//O(n)
void SortedMap::postOrderDelete(Node* node)
{
	if (node == nullptr)
		return;

	if (node->left == nullptr && node->right == nullptr)
	{
		delete node;
		return;
	}

	if (node->left != nullptr)
		postOrderDelete(node->left);
	if (node->right != nullptr)
		postOrderDelete(node->right);
}

//Theta(1);
SortedMap::~SortedMap() {
	postOrderDelete(this->root);
}
