/*
 * Joseph Kelley
 * 11/07/2020
 * QueArr_BST_Fin.h
 */
#include <iostream>
using namespace std;

template <class ItemType>
class QueArr
{
private:
    int maxSize;
    int front;
    int rear;
    ItemType* items;

public:
    QueArr();
    QueArr(int size);
    ~QueArr();

    void makeEmpty();
    bool isEmpty() const;
    bool isFull() const;

    void enqueue(ItemType item);
    void dequeue(ItemType& item);

    void printQueue() const;
};

template <class ItemType>
QueArr<ItemType>::QueArr()
{
    maxSize = 100;
    front = maxSize - 1;
    rear = maxSize - 1;
    items = new ItemType[maxSize];
}

template <class ItemType>
QueArr<ItemType>::QueArr( int size )
{
    maxSize = size;
    front = maxSize - 1;
    rear = maxSize - 1;
    items = new ItemType[maxSize];
}

template <class ItemType>
QueArr<ItemType>::~QueArr()
{
    delete[] items;
}

template <class ItemType>
void QueArr<ItemType>::makeEmpty()
{
    front = maxSize - 1;
    rear = maxSize - 1;
}

template <class ItemType>
bool QueArr<ItemType>::isEmpty() const
{
    return (rear == front);
}

template <class ItemType>
bool QueArr<ItemType>::isFull() const
{
    return ((rear+1)%maxSize == front);

}

template <class ItemType>
void QueArr<ItemType>::enqueue(ItemType item)
{
    if (isFull())
        cout << "Qeueue is full and item cannot be added." << endl;
    else
    {
        rear = (rear + 1) % maxSize;
        items[rear] = item;
    }
}

template <class ItemType>
void QueArr<ItemType>::dequeue(ItemType& item)
{
    if (isEmpty())
        cout << "Qeueue is Empty and there is no item to remove." << endl;
    else
    {
        front = (front + 1) % maxSize;
        item = items[front];
    }
}

template <class ItemType>
void QueArr<ItemType>::printQueue() const
{
    if (isEmpty())
        cout << "Qeueue is Empty." << endl;
    else
    {
        int temp = front;
        while (temp != rear)
        {
            temp = (temp + 1) % maxSize;
            cout << items[temp] << " ";
        }
        cout << endl;
    }

}