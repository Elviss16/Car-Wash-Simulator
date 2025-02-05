#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* front_node;
    Node* rear_node;
    std::size_t size;

public:
    // Constructor
    Queue() : front_node(nullptr), rear_node(nullptr), size(0) {}

    // Destructor
    ~Queue() {
        while (!is_empty()) {
            dequeue();
        }
    }

    // Add an element to the queue
    void enqueue(const T& value) {
        Node* new_node = new Node(value);
        if (rear_node) {
            rear_node->next = new_node;
        }
        rear_node = new_node;
        if (!front_node) {
            front_node = rear_node;
        }
        ++size;
    }

    // Remove an element from the queue
    void dequeue() {
        if (is_empty()) return;

        Node* temp = front_node;
        front_node = front_node->next;
        delete temp;
        --size;

        if (!front_node) {
            rear_node = nullptr;
        }
    }

    // Return the front element of the queue
    T front() const {
        if (is_empty()) {
            throw std::runtime_error("Queue is empty!");
        }
        return front_node->data;
    }

    // Check if the queue is empty
    bool is_empty() const {
        return size == 0;
    }

    // Return the size of the queue
    std::size_t get_size() const {
        return size;
    }
};

#endif
