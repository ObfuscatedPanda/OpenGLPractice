#pragma once
#include "programobject.h"
#include "LinkedListNode.h"
//
//class LinkedList :
//	public ProgramObject
//{
//private:
//	LinkedListNode *head;
//	LinkedListNode *tail;
//
//public:
//	LinkedList(void);
//	~LinkedList(void);
//	void Reverse(void);
//	void AppendNode(LinkedListNode *newNode);
//	void PrependNode(LinkedListNode *newNode);
//	LinkedListNode * FindNode(LinkedListNode *newNodePtr);
//	LinkedListNode * FindNode(LinkedListNode newNode);
//	void RemoveNode(LinkedListNode *deleteMePtr);
//	void RemoveNode(LinkedListNode deleteMe);
//	LinkedListNode * YankNode(LinkedListNode *nodePtr);
//	LinkedListNode * YankNode(LinkedListNode node);
//	void DeleteAll();
//
//};

#ifndef LINKED_LIST_TEMPLATE_H
#define LINKED_LIST_TEMPLATE_H
template <class NodeType>
class LinkedList :
	public ProgramObject{
private
	LinkedListNode<NodeType> *head;
	LinkedListNode<NodeType> *tail;
public:
   	LinkedList<NodeType>(void);
	~LinkedList<NodeType>(void);
	void Reverse(void);
	void AppendNode(LinkedListNode<NodeType> *newNode);
	void PrependNode(LinkedListNode<NodeType> *newNode);
	LinkedListNode*<NodeType> FindNode(LinkedListNode<NodeType> *newNodePtr);
	LinkedListNode*<NodeType> FindNode(LinkedListNode<NodeType> newNode);
	void RemoveNode(LinkedListNode<NodeType> *deleteMePtr);
	void RemoveNode(LinkedListNode<NodeType> deleteMe);
	LinkedListNode*<NodeType> YankNode(LinkedListNode<NodeType> *nodePtr);
	LinkedListNode*<NodeType> YankNode(LinkedListNode<NodeType> node);
	void OrderedInsert(LinkedListNode<NodeType> newNode);
	void OrderedInsert
	void DeleteAll();
};

#endif

//
//template <class myType>
//myType GetMax (myType a, myType b) {
// return (a>b?a:b);
//}