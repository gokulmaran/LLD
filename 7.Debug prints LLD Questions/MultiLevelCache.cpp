#include <iostream>
#include <unordered_map>
#include <string>

// Node for custom Doubly Linked List (as used in previous LRD implementation)
struct Node {
    std::string key, val;
    Node *prev, *next;
    Node(std::string k, std::string v) : key(k), val(v), prev(nullptr), next(nullptr) {}
};

// Standard LRU Cache for a single level
class CacheLevel {
private:
    int capacity;
    std::unordered_map<std::string, Node*> map;
    Node *head, *tail;

    void remove(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void addToHead(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

public:
    CacheLevel(int cap) : capacity(cap) {
        head = new Node("", "");
        tail = new Node("", "");
        head->next = tail;
        tail->prev = head;
    }

    std::string get(std::string key) {
        if (map.find(key) == map.end()) return "";
        Node* node = map[key];
        remove(node);
        addToHead(node);
        return node->val;
    }

    void put(std::string key, std::string val) {
        if (map.find(key) != map.end()) {
            remove(map[key]);
            delete map[key];
        } else if (map.size() == capacity) {
            Node* lru = tail->prev;
            map.erase(lru->key);
            remove(lru);
            delete lru;
        }
        Node* newNode = new Node(key, val);
        map[key] = newNode;
        addToHead(newNode);
    }
};

// Multi-Level Cache Manager
class MultiLevelCache {
private:
    CacheLevel *l1, *l2;

public:
    MultiLevelCache(int l1Cap, int l2Cap) {
        l1 = new CacheLevel(l1Cap);
        l2 = new CacheLevel(l2Cap);
    }

    std::string get(std::string key) {
        // 1. Check L1 first (Fastest)
        std::string val = l1->get(key);
        if (val != "") {
            std::cout << "[Hit L1] Key: " << key << "\n";
            return val;
        }

        // 2. Check L2 if L1 misses
        val = l2->get(key);
        if (val != "") {
            std::cout << "[Hit L2] Key: " << key << ". Promoting to L1...\n";
            l1->put(key, val); // Promote to L1 for faster future access
            return val;
        }

        std::cout << "[Miss] Key: " << key << " not in any cache.\n";
        return "";
    }

    void put(std::string key, std::string val) {
        // Typically, new data is written to L1. 
        // Some systems write-through to L2 as well.
        std::cout << "[Put] Storing " << key << " in L1 and L2\n";
        l1->put(key, val);
        l2->put(key, val);
    }
};

int main() {
    MultiLevelCache cache(2, 4); // L1 capacity 2, L2 capacity 4

    cache.put("user1", "Alice");
    cache.put("user2", "Bob");
    cache.put("user3", "Charlie"); // Evicts "user1" from L1 (stays in L2)

    cache.get("user1"); // L1 miss, L2 hit, re-promotes user1 to L1
    
    return 0;
}
