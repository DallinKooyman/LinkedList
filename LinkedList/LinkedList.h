#pragma once
#include "LinkedListInterface.h"
#include <sstream>
#include <iostream>

using namespace std;

template<typename T>
class LinkedList : public LinkedListInterface<T>
{
private:
    struct Node
    {
        T nodeValue;
        Node* nextNode;
        Node(T newData, Node* newNextNode = NULL)//Null incase they don't put anything (like if its a new tail)
        {
            nodeValue = newData;
            nextNode = newNextNode;
        }

        T getValue()
        {
            return nodeValue;
        }

        Node* getNextNode()
        {
            return nextNode;
        }

        void setNextNode(Node* newNext)
        {
            nextNode = newNext;
        }

    };
    Node* headNode = NULL;
    int sizeOfList = 0;

public:
    LinkedList(void)
    {
        headNode = NULL; //Its the only thing in the list so Null
        sizeOfList = 0;
    }

    ~LinkedList(void)
    {
        if (headNode != NULL)
        {
            Node* currNode = headNode;
            Node* currNextNode = currNode->getNextNode();
            while (currNextNode != NULL)
            {
                delete currNode;
                currNode = currNextNode;
                currNextNode = currNextNode->getNextNode();
            }

            delete currNode;
        }
    }

    bool findValue(T testValue)
    {
        Node* currNode = headNode;
        while (currNode != NULL)
        {
            if (currNode->getValue() == testValue)
            {
                return true;
            }
            else {
                currNode = currNode->getNextNode();
            }
        }
        return false;
    }

    void insertHead(T value)
    {
        if (headNode == NULL)
        {
            headNode = new Node(value);
            sizeOfList += 1;
        }

        if (!findValue(value))
        {
            Node* newNode = new Node(value, headNode);
            headNode = newNode;
            sizeOfList += 1;
        }
    };

    void insertTail(T value)
    {
        if (!findValue(value))
        {
            if (headNode == NULL)
            {
                insertHead(value);
            }
            else
            {
                Node* newNode = new Node(value);
                Node* currNode = headNode;
                while (currNode->getNextNode() != NULL)
                {
                    currNode = currNode->getNextNode();
                }

                currNode->setNextNode(newNode);
                sizeOfList += 1;
            }
        }
    };

    void insertAfter(T value, T insertionNode)
    {
        if (!findValue(value))
        {
            if (findValue(insertionNode))
            {

                Node* newNode = new Node(value);
                Node* currNode = headNode;
                if (currNode->getValue() == insertionNode)
                {
                    newNode->setNextNode(currNode->getNextNode());
                    currNode->setNextNode(newNode);
                }
                else
                {
                    while (currNode->getNextNode()->getValue() != insertionNode)
                    {
                        currNode = currNode->getNextNode();
                    }
                    currNode = currNode->getNextNode(); //this is now the insertionNode
                    newNode->setNextNode(currNode->getNextNode());
                    currNode->setNextNode(newNode);
                }
                sizeOfList += 1;
            }
        }
    };

    void remove(T value)
    {
        if (findValue(value))
        {
            if (headNode->getValue() == value)
            {
                Node* oldHeadNode = headNode;
                headNode = headNode->getNextNode();
                delete oldHeadNode;
            }
            else
            {
                Node* testNode = headNode;
                while (testNode->getNextNode()->getValue() != value)
                {
                    testNode = testNode->getNextNode();
                }

                Node* nodeToRemove = testNode->getNextNode();
                testNode->setNextNode(nodeToRemove->getNextNode());
                delete nodeToRemove;
            }
            sizeOfList -= 1;
        }
    };

    void clear()
    {
        if (sizeOfList != 0)
        {
            if (headNode->getNextNode() != NULL)
            {
                Node* nodeToDelete = headNode;
                Node* nextNodeToClear = nodeToDelete->getNextNode();
                while (nextNodeToClear != NULL)
                {
                    delete nodeToDelete;
                    nodeToDelete = nextNodeToClear;
                    nextNodeToClear = nextNodeToClear->getNextNode();
                }

                delete nodeToDelete;
            }
            else
            {
                Node* headPointer = headNode;
                delete headPointer;
            }
            headNode = NULL;
            sizeOfList = 0;
        }
    };

    T at(int index)
    {
        if ((index < 0) || (index >= sizeOfList))
        {
            throw out_of_range("Out of Range");
        }

        else
        {
            Node* nextNode = headNode;
            for (int i = 0; i < index; ++i)
            {
                nextNode = nextNode->getNextNode();
            }
            return nextNode->getValue();
        }
    };

    int size()
    {
        return sizeOfList;
    };

    string toString()
    {

        if (sizeOfList == 0)
        {
            return "";//return nothing
        }

        ostringstream outStream;
        if (headNode != NULL)
        {
            Node* nodeToOutput = headNode;
            while (nodeToOutput != NULL)
            {
                outStream << nodeToOutput->getValue();
                outStream << " ";
                nodeToOutput = nodeToOutput->getNextNode();
            }
        }

        string finalString;
        finalString = outStream.str();
        finalString.erase(finalString.size() - 1);
        return finalString;
    };
};