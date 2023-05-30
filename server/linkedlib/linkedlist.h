#include <stdio.h>
#include <stdbool.h>
#include "llnode.h"
#include <stdlib.h>
#include "../include/pack109.hpp"


using namespace pack109;

namespace linkedlist{

template <class T>
class LinkedList {
  private:
    linkedlist::Node<T>* head;
    linkedlist::Node<T>* tail;
  public:
    size_t length;
    LinkedList();
    ~LinkedList();
    size_t insertAtTail(T item);
    size_t insertAtHead(T item);
    size_t insertAtIndex(size_t index, T item);
    T removeTail();
    void printList();
    T removeHead();
    T removeAtIndex(size_t index);
    bool containsItem(T item);
    T itemAtIndex(int index);
    T remove(T item);
};

    template <class T>
    LinkedList<T>::LinkedList()
    {
        head = new Node<T>();
        tail = new Node<T>();
        this->head=NULL;
        this->tail=NULL;
        this->length=0;
    }

    template <class T>
    LinkedList<T>::~LinkedList()
    {
        Node<T>* temp = this->head;
        while(temp!=NULL)
        {
            Node<T>* t = temp;
            temp = temp->next;
            free(t);
        }
    }



    template <class T>
    size_t LinkedList<T>::insertAtTail(T item)
    {
        Node<T>* node = new Node<T>(item);
        if (node == NULL) {
            return 1;
        }
        //if list is empty.
        if(this->head == NULL) {
            this->head = node;
            this->tail = node;
        } else {
            this->tail->next  = node;
            this->tail 	= this->tail->next;
        }
        this->length++;	
        return 0;
    }

    template<class T>
    bool LinkedList<T>::containsItem(T item)
    {
        Node<T>* current = this->head;
        for(int i=0;i<this->length;i++)
        {
            if(current->item ==item)
            {
                printf("\nret true in linklist");
                return true;
            }
            current = current->next;
        }
                        printf("\nret false in linklist");

        return false;
    }

    template <class T>
    size_t LinkedList<T>::insertAtHead(T item)
    {
        Node<T>* node = new Node<T>(item);
        if (node == NULL) {
            return 1;
        }
        //if list is empty.
        if(this->head == NULL) {
            this->head = node;
            this->tail = node;
        } else {
            node->next 	= this->head;
            this->head 	= node;
        }
        this->length++;	
        return 0;
    }

    template <class T>
    size_t LinkedList<T>::insertAtIndex(size_t index, T item)
    {
        if(index==0)
        {
            return insertAtHead(item);
        }
        Node<T>* current = this->head;
        Node<T>* items = new Node<T>(item);
        if(items==NULL)
        {
            return 1;
        }
        for(int i =0;i<index-1;i++)
        {
            current = current->next;
        }
        items->next = current->next;
        current->next = items;
        return 0;
    }

    template <class T>
    T LinkedList<T>::removeTail()
    {
        Node<T>* temp;
        int i = 0;
        T item;
        if(this->tail == NULL) 
        {	
            // List is Empty	
            return item;
        }
        else 
        {
            temp = this->head;

            // Iterate to the end of the list
            while(temp->next != this->tail) { 
                temp = temp->next;
            }

            item = this->tail->item;

            Node<T>* old_tail = this->tail;
            this->tail = temp;
            this->tail->next = NULL;	
            free(old_tail);	
        }
        this->length--;	
        return item;
    }

    template <class T>
    T LinkedList<T>::removeHead()
    {
        T item;
        if(this->head == NULL) 
        {	
            // List is Empty	
            return item;
        } 
        else 
        {
            item = this->head->item;
            Node<T>* old_head = this->head;
            this->head = this->head->next;	
            free(old_head);	
        }
        this->length--;	
        return item;
    }

    template<class T>
    T LinkedList<T>::remove(T item)
    {
        int index = -1;
        T temp;
        Node<T>* current = this->head;
        for(int i=0;i<this->length;i++)
        {
            index++;
            if(current->item==item)
            {
                temp = this->removeAtIndex(index);
                return temp;
            }
            current = current->next;
            if(current==NULL)
            {
                break;
            }
        }
        string name = "null";
        vec temp_vec = {0};
        struct file_struct tempFile = {name ,temp_vec};
        temp = tempFile;
        return temp;
    }

    template <class T>
    T LinkedList<T>::removeAtIndex(size_t index)
    {
        T item;
        if (index < 0 || index >= this->length)
        {
            return item;
        }
        if (index == 0)
        {
            return removeHead();
        }
        if (index == length - 1)
        {
            return removeTail();
        }
        Node<T>* cN = this->head;
        size_t limit = this->length;
        for (size_t i = 0; i < limit; i++)
        {
            if (i + 1 == index)
            {
                T returnVal = cN->next->item;
                free(cN->next);
                cN->next = cN->next->next;
                this->length--;
                return returnVal;
            }
        }
        return item;
    }


    template <class T>
    T LinkedList<T>::itemAtIndex(int index)
    {

	Node<T>* current = this->head;
	for(int i = 0;i<index;i++)
	{
		if(current->next!=NULL)
		{
			current = current->next;
		}
		else
		{
			exit(1);
		}
	}
	    return current->item;
    }


    template <class T>
    void LinkedList<T>::printList()
    {
        size_t limit = this->length;
        if (!this->length)
        {
            printf("Empty");
        }
        Node<T>* cP = this->head;
        for (size_t i = 0; i < limit; i++)
        {
            std::cout<<cP->item.print();
            cP = cP->next;
        }
    }
    
}
