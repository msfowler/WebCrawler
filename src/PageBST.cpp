#include "PageBST.h"
#include <string>
#include <iostream>

PageBST::PageBST()
{
	root = NULL;
	size = 0;
	returnValue = NULL;
}

PageBST::PageBST(const PageBST & other)
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

PageBST :: ~PageBST()
{ 
	recursive_delete_node(root);
	root = NULL;
	size = 0;
	returnValue = NULL;
}

 PageBST& PageBST::operator =(const PageBST & other)
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

PageBSTNode * PageBST::GetRoot()const
{

	return root;
}



int PageBST::GetSize() const
{
	return size;
}

PageBSTNode * PageBST::Insert(Page * v)
{
    if(root == NULL)
    {
        root = new PageBSTNode(v);
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

PageBSTNode * PageBST::Find(Page * v) const
{
    if(root != NULL)
		return recursive_find(root, v);
    else
        return NULL;
}

void PageBST :: recursive_delete_node(PageBSTNode * current_node)
{

	if(current_node == NULL) 
		return;

	recursive_delete_node(current_node->left);
	recursive_delete_node(current_node->right);
	delete current_node;
}

void PageBST :: recursive_insert(PageBSTNode * current_node, Page * v)
{
	int compare_result;
	compare_result = v->compare(current_node->GetValue());

	if(compare_result < 0)
	{
		//go left
		if(current_node->GetLeft() == NULL)
		{
			current_node->left = new PageBSTNode(v);
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
			current_node->right = new PageBSTNode(v);
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


PageBSTNode * PageBST :: recursive_find(PageBSTNode * current_node, Page * v) const
{

	int compare_result;

	compare_result = v->compare(current_node->GetValue());

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

PageBSTNode * PageBST :: recursive_copy(PageBSTNode * current_node) const
{
	
	Page * val = current_node->GetValue();  

	PageBSTNode * new_node = new PageBSTNode(val);

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

