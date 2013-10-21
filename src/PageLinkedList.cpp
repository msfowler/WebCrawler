#include "PageLinkedList.h"
#include <string>

PageLinkedList::PageLinkedList()
{
	first = NULL;
	last = NULL;
	size = 0;
}

PageLinkedList::PageLinkedList(const PageLinkedList & other)
{
	Copy(other);
}

PageLinkedList::~PageLinkedList()
{
	Free();
}

PageLinkedList& PageLinkedList::operator =(const PageLinkedList & other)
	{
		if (&other != this) 
		{
			Free();
			Copy(other);
		}

		return *this;
	}
void PageLinkedList::Copy(const PageLinkedList & other)
{
	size = other.size;
	if(first != NULL)	
	{			
		first = recursive_copy(other.GetFirst());
		
		PageLLNode * current_node;
		current_node = first;
	
		if(current_node == NULL)
		{
			last = NULL;
		}
		else
		{
        	while(current_node->next != NULL)
        	{
				current_node = current_node->next;
        	}	
			last = current_node;
		}
		double_link(first);
	}
	else
	{
		first = NULL;
		last = NULL;
	}
}

void PageLinkedList::Free()
{
	if(first != NULL)
    {
		size = 0;
		recursive_delete(first);
		first = NULL;
		last = NULL;
    }
    else
	{
		first = NULL;  
       	size = 0;
	}
}

bool PageLinkedList::IsEmpty() const
{
	if(size == 0)
		return true;
	else
		return false;
}

void PageLinkedList::Clear()
{
    if(first != NULL)
    {
	recursive_delete(first);
	first = NULL;
	last = NULL;
	size = 0;
    }
}

int PageLinkedList::GetSize() const
{	
	return size;
}

PageLLNode * PageLinkedList::GetFirst()const
{
	return first;
}

PageLLNode * PageLinkedList::GetLast()const
{
	return last;
}
 
PageLLNode * PageLinkedList::Insert(Page * v, PageLLNode * n)
{


	PageLLNode * new_node = new PageLLNode(v, NULL, NULL);
	size++;


	if(n == NULL)
	{
        new_node->next = first;
		if(first != NULL)
		{	
			first->prev = new_node;
		}

		first = new_node;
		if(last == NULL)
		{
			last = first;
		}
		return first;
	}

	else if(n->next == NULL)
	{
		n->next = new_node;
		new_node->prev = n;
		last = new_node;
		return new_node;
	}

	else
	{
		n->next->prev = new_node;
		new_node->next = n->next;
		n->next = new_node;
		new_node->prev = n;
		return new_node;
	}


}

PageLLNode * PageLinkedList::Find(Page * v, PageLLNode * n) const
{

	if(n == NULL)
	{
		return recursive_find(first, v);
	}
	else if (n->next != NULL)
	{
		return recursive_find(n->next, v);
	} 
	else
	{
		return NULL;
	}

}

void PageLinkedList::Remove(PageLLNode * n)
{
	if(n != NULL)
	{
		size--;
		if(n == first)
		{
			if(first == last)
			{
				last = NULL;
			}
		    first = n->next;
		    delete n;
		    n = NULL;
		}
		else if(n->prev != NULL  && n->next != NULL) //if its in the middle 
		{
		    
		   n->prev->next = n->next;
		   n->next->prev = n->prev;
		   delete n;
		   n = NULL;
		}
		else if(n->prev != NULL) //if it's last
		{
		   n->prev->next = NULL;
		   last = n->prev;
		   delete n;
		   n = NULL;	
		}
	}

}


PageLLNode * PageLinkedList::recursive_copy(PageLLNode * current_node)
{
	PageLLNode * new_node = NULL;
	if(current_node != NULL)
	{
		Page * val = current_node->GetValue();
		new_node = new PageLLNode(val, NULL, NULL);

		if(current_node->GetNext() != NULL)
		{	
			new_node->next = recursive_copy(current_node->GetNext());
		}
		else
		{
			new_node->next = NULL;

		}
	}
	else
	{
	   return NULL;
	}

	return new_node;

}
void PageLinkedList::recursive_delete(PageLLNode * current_node)
{
	if(current_node->next != NULL)
	{
		recursive_delete(current_node->GetNext());
	}
	
	
	current_node->next = NULL;
	current_node->prev = NULL;
	delete current_node;
	current_node = NULL;
}

PageLLNode * PageLinkedList::recursive_find(PageLLNode * start_point, Page * v) const
{
	if(start_point->GetValue()->compare(v) == 0)
	{
		return start_point;
	}
	else if(start_point->GetNext()!= NULL)
	{

		return recursive_find(start_point->GetNext(), v);
	}
	else
	{
		return NULL;
	}

}


void PageLinkedList::double_link(PageLLNode * current_node)
{
	if(current_node != NULL)
	{
	if(current_node->GetNext() != NULL)
	{
		current_node->next->prev= current_node;
		double_link(current_node->GetNext());
	}
	}

}
