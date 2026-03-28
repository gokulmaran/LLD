#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;

    ListNode(int x) : val(x), next(nullptr) {}
};

void deleteNode(ListNode*& head, int key) {
    // Case 1: Empty list
    if (!head) return;

    // Case 2: Head is the node to delete
    if (head->val == key) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    ListNode* prev = nullptr;
    ListNode* curr = head;

    // Find the node
    while (curr && curr->val != key) {
        prev = curr;
        curr = curr->next;
    }

    // Case 3: Node found
    if (curr) {
        prev->next = curr->next;
        delete curr;
    }
}
void deleteNode(ListNode* node) {
    node->val = node->next->val;
    ListNode* temp = node->next;
    node->next = node->next->next;
    delete temp;
}