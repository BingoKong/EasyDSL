#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include "LinkList.h"

namespace EasyDSL
{

template <typename T>
class CircleList : public LinkList<T>
{
protected:
	typedef typename LinkList<T>::Node Node;
	Node* mTail;

public:
	CircleList();
	~CircleList();
	
	bool insert(int index, const T& element);
	bool remove(int index);
	  
	bool set(int index, const T& element);
	bool get(int index, T& element) const;

	int find(T& element) const;

	virtual bool move(int index, int step = 1);
};

template <typename T>
CircleList<T>::CircleList()
{
	mTail = NULL;
}

template <typename T>
CircleList<T>::~CircleList()
{
	LinkList<T>::clear();
}

template <typename T>
bool CircleList<T>::insert(int index, const T& element)
{
	int new_index = index;
	int len = LinkList<T>::length();
	if (len == 0)
	{
	    new_index = 0; 		
	}
	else if (index != 0 && index % len == 0)
	{
	    new_index = len;
	}
	else
	{
	    new_index = index % len;
	}

	if (LinkList<T>::insert(new_index, element) == true)
    {
		if (len == 0)
		{
			mTail = this->mHeader;	
			this->mHeader->next = this->mHeader;
		}
		else if (index != 0 && index % len == 0)
		{
			mTail = mTail->next;
	    	mTail->next = this->mHeader;
		}
    	return true;
    }
    else
    {
    	return false;
    }  
}

template <typename T>
bool CircleList<T>::remove(int index)
{
	index = index % LinkList<T>::length();
	if (LinkList<T>::remove(index) == true)
	{
		if (LinkList<T>::length() != 0)
		{
			if (index == 0)
			{
				mTail->next = this->mHeader;
			}
			else if (index == LinkList<T>::length())
			{
				Node* current = this->mHeader;
				while (current->next != this->mHeader)
				{
					current = current->next;
				}
				mTail = current;
			}
		}
		else
		{
			mTail = NULL;
		}
		return true;
	}
	else
	{
		return false;
	}
}

template <typename T>
bool CircleList<T>::set(int index, const T& element)
{
    return LinkList<T>::set(index % LinkList<T>::length(), element);
}

template <typename T>
bool CircleList<T>::get(int index, T& element) const
{
    return LinkList<T>::get(index % LinkList<T>::length(), element);
}

template <typename T>
int CircleList<T>::find(T& element) const
{
	if (mTail != NULL && element == mTail->value)
	{
		return LinkList<T>::length() - 1;
	}
	
	int count = 0;
    for (Node* current = this->mHeader; current != mTail; current = current->next, count++)
    {
    	if (current->value == element)
    	{
    		return count;
    	}
    }
    
    return -1;
}

template <typename T>
bool CircleList<T>::move(int index, int step)
{
	return LinkList<T>::move(index % LinkList<T>::length(), step);
}

}   // end namespace EasyDSL

#endif


