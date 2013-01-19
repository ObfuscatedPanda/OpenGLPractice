#include "LinkedList.h"
#include <Windows.h>

template <class NodeType>
LinkedList<NodeType>::LinkedList(void)
{
	head = NULL;
	tail = NULL;
}

template <class NodeType>
LinkedList<NodeType>::~LinkedList(void)
{
	DeleteAll();
}

template <class NodeType>
void LinkedList<NodeType>::Reverse(void)
{
	assert(0); //not implemented
}

template <class NodeType>
void LinkedList<NodeType>::AppendNode(LinkedListNode<NodeType> *newNode)
{
	tail->SetNext(newNode);
	tail = newNode;
	if(NULL == head)
	{
		head = newNode;
	}
}

template <class NodeType>
void LinkedList<NodeType>::PrependNode(LinkedListNode<NodeType> *newNode)
{
	newNode->SetNext(head);
	head = newNode;
	if(NULL == tail)
	{
		tail = newNode;
	}
}

template <class NodeType>
LinkedListNode*<NodeType> LinkedList<myType>::FindNode(LinkedListNode<NodeType> *newNodePtr)
{
	assert(0); //not implemented
	return null;
}

template <class NodeType>
LinkedListNode*<NodeType> LinkedList::FindNode(LinkedListNode<NodeType> newNode)
{
	assert(0); //not implemented
	return null;
}

template <class NodeType>
void LinkedList<NodeType>::RemoveNode(LinkedListNode<NodeType> *deleteMePtr)
{
	assert(0); //not implemented

}

template <class NodeType>
void LinkedList<NodeType>::RemoveNode(LinkedListNode<NodeType> deleteMe)
{
	assert(0); //not implemented

}

template <class NodeType>
LinkedListNode*<NodeType> LinkedList<myType>::YankNode(LinkedListNode<NodeType> *nodePtr)
{
	assert(0); //not implemented
	return null;
}

template <class NodeType>
LinkedListNode*<NodeType> LinkedList<myType>::YankNode(LinkedListNode<NodeType> node)
{
	assert(0); //not implemented
	return NULL;
}

template <class NodeType>
void LinkedList<NodeType>::DeleteAll()
{
	LinkedListNode *nextNode = head;
	LinkedListNode *currentNode = NULL;
	while(nextNode)
	{
		currentNode = nextNode;
		nextNode = currentNode->Next();
		delete currentNode;
	}
}