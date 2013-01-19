#pragma once
#include "programobject.h"


template <class NodeType>
class LinkedListNode :
	public ProgramObject
{
private:
	LinkedListNode<NodeType> *nextNode;

public:
	LinkedListNode<NodeType>(void);
	~LinkedListNode<NodeType>(void);
	inline LinkedListNode<NodeType> *Next()             { return nextNode; };
	inline void SetNext(LinkedListNode<NodeType> *next) { nextNode = next; }
};

