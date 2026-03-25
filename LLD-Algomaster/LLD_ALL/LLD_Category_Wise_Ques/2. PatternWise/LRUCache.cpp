#include <iostream>
#include <unordered_map>
using namespace std;

class LRUCache {
public:
    class Node {
    public:
        int key;
        int val;
        Node* prev;
        Node* next;

        Node(int key, int val) {
            this->key = key;
            this->val = val;
            prev = next = nullptr;
        }
    };

    Node* head = new Node(-1, -1);
    Node* tail = new Node(-1, -1);

    int cap;
    unordered_map<int, Node*> m;

    LRUCache(int capacity) {
        cap = capacity;
        head->next = tail;
        tail->prev = head;
    }

    // add node right after head (MRU)
    void addNode(Node* newNode) {
        Node* temp = head->next;

        newNode->next = temp;
        newNode->prev = head;

        head->next = newNode;
        temp->prev = newNode;
    }

    // remove node from list
    void deleteNode(Node* delNode) {
        Node* prevv = delNode->prev;
        Node* nextt = delNode->next;

        prevv->next = nextt;
        nextt->prev = prevv;
    }

    int get(int key) {
        if (m.find(key) != m.end()) {
            Node* resNode = m[key];
            int ans = resNode->val;

            m.erase(key);
            deleteNode(resNode);
            addNode(resNode);
            m[key] = head->next;

            return ans;
        }
        return -1;
    }

    void put(int key, int value) {
        if (m.find(key) != m.end()) {
            Node* curr = m[key];
            m.erase(key);
            deleteNode(curr);
            delete curr; // important
        }

        if (m.size() == cap) {
            Node* lru = tail->prev;
            m.erase(lru->key);
            deleteNode(lru);
            delete lru; // important
        }

        Node* newNode = new Node(key, value);
        addNode(newNode);
        m[key] = head->next;
    }
};

// ---------------- MAIN ----------------
int main() {
    LRUCache cache(2);

    cache.put(1, 10);
    cache.put(2, 20);

    cout << "get(1): " << cache.get(1) << endl; // 10

    cache.put(3, 30); // evicts key 2

    cout << "get(2): " << cache.get(2) << endl; // -1
    cout << "get(3): " << cache.get(3) << endl; // 30

    return 0;
}
