#include "OcrBST.h"
#include <string>
#include <iostream>

OcrBST::OcrBST()
{
	root = NULL;
	size = 0;
	returnValue = NULL;
}

OcrBST::OcrBST(const OcrBST & other)
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

OcrBST :: ~OcrBST()
{ 
	recursive_delete_node(root);
	root = NULL;
	size = 0;
	returnValue = NULL;
}

 OcrBST& OcrBST::operator =(const OcrBST & other)
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

OcrBSTNode * OcrBST::GetRoot()const
{

	return root;
}



int OcrBST::GetSize() const
{
	return size;
}

OcrBSTNode * OcrBST::Insert(const Occurrence & v)
{
    if(root == NULL)
    {
        root = new OcrBSTNode(v);
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

OcrBSTNode * OcrBST::Find(const Occurrence & v) const
{
    if(root != NULL)
		return recursive_find(root, v);
    else
        return NULL;
}

void OcrBST :: recursive_delete_node(OcrBSTNode * current_node)
{

	if(current_node == NULL) 
		return;

	recursive_delete_node(current_node->left);
	recursive_delete_node(current_node->right);
	delete current_node;
}

void OcrBST :: recursive_insert(OcrBSTNode * current_node, const Occurrence & v)
{
	int compare_result;
	compare_result = v.compare(current_node->GetValue());

	if(compare_result < 0)
	{
		//go left
		if(current_node->GetLeft() == NULL)
		{
			current_node->left = new OcrBSTNode(v);
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
			current_node->right = new OcrBSTNode(v);
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


OcrBSTNode * OcrBST :: recursive_find(OcrBSTNode * current_node, const Occurrence & v) const
{

	int compare_result;

	compare_result = v.compare(current_node->GetValue());

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

OcrBSTNode * OcrBST :: recursive_copy(OcrBSTNode * current_node) const
{
	Occurrence val;
	val = current_node->GetValue();  

	OcrBSTNode * new_node = new OcrBSTNode(val);

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

