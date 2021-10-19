#include<unordered_map>
#include <iostream>

using namespace std;


struct Node{
    Node* prev;
    Node* next;
    int key;
    int val;
    int freq;
    Node(int keyIn, int valIn){
        key = keyIn;
        val = valIn;
        freq = 0;
        prev = nullptr;
        next = nullptr;
    }
};

class LFUCache {
    int cp;
    unordered_map<int, Node*> map;
    unordered_map<int, Node*> freqMap;
    Node* head;
    Node* tail;


public:
    void connectNodes(Node* n1, Node* n2){
        n1->next = n2;
        n2->prev = n1;
    }

    void removeNode(Node *& node){
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void insertNode(Node*& node, Node* &swapNode){
        // insert node left
        swapNode->prev->next = node;
        node->prev = swapNode->prev;
        swapNode->prev = node;
        node->next = swapNode;
    }

    void updateFoundNode(Node* node){
        // update freq and move to new spot
        bool found = freqMap.find(node->freq) != freqMap.end();
        if (found && freqMap[node->freq] == node){
            if (node->next->freq == node->freq)
                freqMap[node->freq] = node->next;
            else
                freqMap.erase(node->freq);
        }
        node->freq++;
        Node* swapNode;
        found = freqMap.find(node->freq) != freqMap.end();
        if (found){
            swapNode = freqMap[node->freq];
        } else{
            int freq = node->freq-1;
            while (freqMap.find(freq) == freqMap.end()){
                freq--; // while not found, keep lowering
            }
            swapNode = freqMap[freq];
        }
        if (swapNode != node) {
            removeNode(node);
            insertNode(node, swapNode);
            freqMap[node->freq] = node;
        }

    }

    LFUCache(int capacity) {
        cp = capacity;
        int largestInt = (int) 0x7FFFFFFF;
        head = new Node(-1,-1);
        tail = new Node(-1,-1);
        head->freq = largestInt;
        tail->freq = 0;
        freqMap[tail->freq] = tail;
        connectNodes(head, tail);
    }
    ~LFUCache(){
        Node* tmp = head->next;
        while (tmp != tail){
            delete tmp->prev;
            tmp = tmp->next;
        }
        delete tail->prev;
        delete tail;
    }

    int get(int key) {
        if (cp == 0)
            return -1;
        bool found = map.find(key) != map.end();
        if (found){
            Node* node = map[key];
            updateFoundNode(node);
            return node->val;
        } else{
            return -1;
        }
    }

    void put(int key, int value) {
        if (cp ==0)
            return;
        bool found = map.find(key) != map.end();
        if (found){
            Node* node = map[key];
            node->val = value;
            updateFoundNode(node);

        } else{
            if (map.size() == cp){
                int key2 = tail->prev->key;
                Node* tmp = map[key2];
                if (freqMap.find(tmp->freq) != freqMap.end() && freqMap[tmp->freq] == tmp){
                    if (tmp->next->freq == tmp->freq)
                        freqMap[tmp->freq] = tmp->next;
                    else
                        freqMap.erase(tmp->freq);
                }
                tmp->prev->next = tail;
                tail->prev = tmp->prev;
                map.erase(key2);
                delete tmp;
            }
            Node* node = new Node(key, value);
            map[key] = node;
            tail->prev->next = node;
            node->prev = tail->prev;
            tail->prev = node;
            node->next = tail;
            updateFoundNode(node);
        }
    }
};
//Your LFUCache object will be instantiated and called as such:
int main(){
    LFUCache lfu = LFUCache(2);
    lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
    lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
    cout << lfu.get(1) << " ";      // return 1
    // cache=[1,2], cnt(2)=1, cnt(1)=2
    lfu.put(3, 3);   // 2 is the LFU key because cnt(2)=1 is the smallest, invalidate 2.
    // cache=[3,1], cnt(3)=1, cnt(1)=2
    cout << lfu.get(2) << " ";      // return -1 (not found)
    cout << lfu.get(3) << " ";      // return 3
    // cache=[3,1], cnt(3)=2, cnt(1)=2
    lfu.put(4, 4);   // Both 1 and 3 have the same cnt, but 1 is LRU, invalidate 1.
    // cache=[4,3], cnt(4)=1, cnt(3)=2
    cout << lfu.get(1) << " ";      // return -1 (not found)
    cout << lfu.get(3) << " ";      // return 3
    // cache=[3,4], cnt(4)=1, cnt(3)=3
    cout << lfu.get(4) << " ";      // return 4
    // cache=[3,4], cnt(4)=2, cnt(3)=3

    // [null,null,null,1,null,-1,3,null,-1,3,4]
  return 0;
}
