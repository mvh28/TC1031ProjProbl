class MyCircularQueue {
private:
    int* queue;
    int count;
    int size;
    int front;
    int rear;

public:
    MyCircularQueue(int k)
    {
        size = k;
        count = 0;
        front = -1;
        rear = -1;
        queue = new int[size];
    }

    bool enQueue(int value)
    {
        if (isFull()) {
            return false;
        }

        if (isEmpty()) {
            front = 0;
        }

        rear = (rear + 1) % size;
        queue[rear] = value;
        count++;
        return true;
    }

    bool deQueue()
    {
        if (isEmpty()) {
            return false;
        }

        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % size;
        }
        count--;

        return true;
    }

    int Front()
    {
        if (isEmpty()) {
            return -1;
        }
        return queue[front];
    }

    int Rear()
    {
        if (isEmpty()) {
            return -1;
        }
        return queue[rear];
    }

    bool isEmpty()
    {
        return (count == 0 && front == -1 && rear == -1);
    }

    bool isFull()
    {
        return (count == size);
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */