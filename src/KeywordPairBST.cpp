#include "KeywordPairBST.h"
#include <string>
#include <iostream>

KeywordPairBST::KeywordPairBST()
{
	root = NULL;
	size = 0;
	returnValue = NULL;
}

KeywordPairBST::KeywordPairBST(const KeywordPairBST & other)
{
	
	if(other.GetRoot() != NULL)
	{
		size = other.GetSize();
		root = recursive_copy(other.GetRoot());
	}
	else
	{	
		size = 0;
		root = NULL;
	}
}

KeywordPairBST :: ~KeywordPairBST()
{ 
	recursive_delete_node(root);
	root = NULL;
	size = 0;
	returnValue = NULL;
}

 KeywordPairBST& KeywordPairBST::operator =(const KeywordPairBST & other)
{
	if (&other != this) 
	{
		recursive_delete_node(root);
		if(other.GetRoot() != NULL)
		{
		
		size = other.GetSize();
		root = recursive_copy(other.GetRoot());
		}
		else
		{	size = 0;
			root = NULL;
		}	
	}

	return *this;
}

KeywordPairBSTNode * KeywordPairBST::GetRoot()const
{

	return root;
}



int KeywordPairBST::GetSize() const
{
	return size;
}

KeywordPairBSTNode * KeywordPairBST::Insert(const KeywordPair & v)
{
    if(root == NULL)
    {
        root = new KeywordPairBSTNode(v);
        size++;
        return root;
    }
    else
    {
		returnValue = NULL;
		recursive_insert(root, v);
		return returnValue;
    }
}

KeywordPairBSTNode * KeywordPairBST::Find(const string & v) const
{
    if(root != NULL)
		return recursive_find(root, v);
    else
        return NULL;
}

void KeywordPairBST :: recursive_delete_node(KeywordPairBSTNode * current_node)
{

	if(current_node == NULL) 
		return;

	recursive_delete_node(current_node->left);
	recursive_delete_node(current_node->right);
	delete current_node;
}

void KeywordPairBST :: recursive_insert(KeywordPairBSTNode * current_node, const KeywordPair & v)
{
	int compare_result;
	compare_result = v.getKeyword().compare(current_node->GetValue().getKeyword());

	if(compare_result < 0)
	{
		//go left
		if(current_node->GetLeft() == NULL)
		{
			current_node->left = new KeywordPairBSTNode(v);
			size++;
			returnValue = current_node->left;
		}
		else
		{
			recursive_insert(current_node->GetLeft(), v);
		}
	}

	else if(compare_result > 0)
	{
		//go right
		if(current_node->GetRight() == NULL)
		{
			current_node->right = new KeywordPairBSTNode(v);
			size++;
			returnValue = current_node->right;
		}
		else
		{
			recursive_insert(current_node->GetRight(), v);
		}
	}
	else
	{
		returnValue = NULL;
	}

}


KeywordPairBSTNode * KeywordPairBST::recursive_find(KeywordPairBSTNode * current_node,
																		 const string & v) const
{

	int compare_result;

	compare_result = v.compare(current_node->GetValue().getKeyword());

	if(compare_result < 0)
	{
		//go left
		if(current_node->GetLeft() == NULL)
		{
			return NULL;
		}
		else
		{
			return recursive_find(current_node->GetLeft(), v);
		}
	}

	else if(compare_result > 0)
	{
		//go right
		if(current_node->GetRight() == NULL)
		{
			return NULL;
		}
		else
		{
			return recursive_find(current_node->GetRight(), v);
		}
	}
	else
	{
		return current_node;
	}

}

KeywordPairBSTNode * KeywordPairBST::recursive_copy(KeywordPairBSTNode * current_node) const
{
	KeywordPair val;
	val = current_node->GetValue();  

	KeywordPairBSTNode * new_node = new KeywordPairBSTNode(val);

	if(current_node->GetLeft() != NULL)
	{
		new_node->left = recursive_copy(current_node->GetLeft());
	}

	if(current_node->GetRight() != NULL)
	{
		new_node->right = recursive_copy(current_node->GetRight());
	}

	return new_node;
}

