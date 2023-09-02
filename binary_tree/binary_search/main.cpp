#include <iostream>
#include <cassert>
#include <queue>

template<typename Key, typename Value>
class BST
{
private:
    struct Node
    {
        Key key;
        Value value;
        Node* left;
        Node* right;
        Node(Key k, Value v) :key(k), value(v), left(nullptr), right(nullptr) {}
        Node(Node* t) 
        {
            key = t.key;
            value = t.value;
            left = t.left;
            right = t.right;
        }
    }
    Node* root;
    int count;
public:
    BST() :root(nullptr), count(0) {}
    ~BST() { destroy(root); }
    int size() { return count; }
    bool is_empty() { return count == 0; }
    void insert(Key k, Value v) { root = insert(root, k, v); }
    bool contain(Key k) { return contain(root, k); }
    Value* search(Key k) { return search(root, k); }
    void pre_order() { pre_order(root); }
    void in_order() { in_order(root); }
    void pos_order() { pos_order(root); }
    // 广
    void lever_order()
    {
        std::queue<Node*> q;
        q.push(root);
        while (q.size())
        {
            auto t = q.front(); q.pop();
            std::cout << t->key << "\n";
            if (t->left != nullptr) q.push(t->left);
            if (t->right != nullptr) q.push(t->right);
        }
    }
    // 寻找最小键值
    Key minnum()
    {
        assert(count > 0);
        Node* t = minnum(root);
        return t->key;
    }
    Key maxnum()
    {
        assert(count > 0);
        Node* t = maxnum(root);
        return t->key;
    }
    void remove_min()
    {
        if (root != nullptr) root = remove_min(root);
    }
    void remove_max()
    {
        if (root != nullptr) root = remove_max(root);
    }
    void remove(Key key)
    {
        root = remove(root, key);
    }
private:
    // 删除以node为根键值为k的节点并返回删除后的新根
    Node* remove(Node* node, Key k)
    {
        if (node == nullptr) return nullptr;
        if  (node->key < k) return remove(node->right, k);
        else if (node->key > k) return remove(node->left, k);
        else 
        {
            if (node->left == nullptr) 
            {
                Node* t = node->right;
                delete node;
                count--;
                return t;
            }       
            if (node->right == nullptr) 
            {
                Node* t = node->left;
                delete node;
                count--;
                return t;
            }       
            // 找右子树后继
            Node* after = new Node(minnum(node->right));
            after->right = remove_min(node->right);
            after->left = node->left;
            delete node;
            count--;
            return after;

        }
    }
    Node* remove_max(Node* node)
    {
        if (node->right == nullptr)
        {
            Node* t = node->left;
            delete node;
            count--;
            return t;
        }
        node->right = remove_max(node->right);
        return node;
    }
    // 删除以node为根的最小值，并且返回删除后的根
    Node* remove_min(Node* node)
    {
        if (node->left == nullptr) 
        {
            Node* t = node->right;
            delete node;
            count--;
            return t;
        }
        node->left = remove_min(node->left);
        return node;
    }
    Node* maxnum(Node* node)
    {
        if (node->right == nullptr) return node;
        return maxnum(node->right);
    }
    Node* minnum(Node* node)
    {
        if (node->left == nullptr) return node;
        return minnum(node->left);
    }
    void destory(Node* node)
    {
        if (node != nullptr)
        {
            destory(node->left);
            destory(node->right);
            delete node;
            count--;
        }
    }
    void pre_order(Node* node) 
    {
        if (node != nullptr) 
        {
            std::cout << node->key << " ";
            pre_order(node->left);
            pre_order(node->right);
        }
    }
    void in_order(Node* node) 
    {
        if (node != nullptr) 
        {
            in_order(node->left);
            std::cout << node->key << " ";
            in_order(node->right);
        }
    }
    void pos_order(Node* node) 
    {
        if (node != nullptr) 
        {
            pos_order(node->left);
            pos_order(node->right);
            std::cout << node->key << " ";
        }
    }
    Value* search(Node* node, Key k)
    {
        if (node == nullptr) return nullptr;
        if (node->key == k) return &(node->value);
        else if (node->key < k) return search(node->right, k);
        else return search(node->left, k);
    }

    Node* insert(Node* node, Key k, Value v)
    {
        if (node == nullptr)
        {
            count++;
            return node = new Node(k, v);
        }
        if (node->key == k) node->value = v;
        else if (node->key < k) node->right = insert(node->right, k, v);
        else node->left = insert(node->left, k, v);
        return node;
    }
    bool contain(Node* node, Key k)
    {
        if (node == nullptr) return false;
        if (node->key == k) return true;
        else if (node->key < k) return contain(node->right, k);
        else return contain(node->left, k);
    }
};

int main()
{

}