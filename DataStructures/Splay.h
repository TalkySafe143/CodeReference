/*
Splay Tree implementation with sum range queries
Complexity for \textbf{Insertion}, \textbf{Deletion} and \textbf{Search}: $O(\log n)$ and for \textbf{Sum queries}: $O(\log n + k)$.
---
Source: Me & Data Structures and Algorithms Specialization (Coursera)
Verification: *
*/

struct Vertex {
    ll key;
    ll sum;
    Vertex* left;
    Vertex* right;
    Vertex* parent;

    Vertex(int key, long long sum, Vertex* left, Vertex* right, Vertex* parent)
            : key(key), sum(sum), left(left), right(right), parent(parent) {}
};

struct SplayTree {
    Vertex* root = NULL;

    void update(Vertex* v) {
        if (v == NULL) return;
        v->sum = v->key + (v->left != NULL ? v->left->sum : 0ll) + (v->right != NULL ? v->right->sum : 0ll);
        if (v->left != NULL) {
            v->left->parent = v;
        }
        if (v->right != NULL) {
            v->right->parent = v;
        }
    }

    void small_rotation(Vertex* v) {
        Vertex* parent = v->parent;
        if (parent == NULL) {
            return;
        }
        Vertex* grandparent = v->parent->parent;
        if (parent->left == v) {
            Vertex* m = v->right;
            v->right = parent;
            parent->left = m;
        } else {
            Vertex* m = v->left;
            v->left = parent;
            parent->right = m;
        }
        update(parent);
        update(v);
        v->parent = grandparent;
        if (grandparent != NULL) {
            if (grandparent->left == parent) {
                grandparent->left = v;
            } else {
                grandparent->right = v;
            }
        }
    }

    void big_rotation(Vertex* v) {
        if (v->parent->left == v && v->parent->parent->left == v->parent) {
            // Zig-zig
            small_rotation(v->parent);
            small_rotation(v);
        } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
            // Zig-zig
            small_rotation(v->parent);
            small_rotation(v);
        } else {
            // Zig-zag
            small_rotation(v);
            small_rotation(v);
        }
    }

    void splay(Vertex*& _root, Vertex* v) {
        if (v == NULL) return;
        while (v->parent != NULL) {
            if (v->parent->parent == NULL) {
                small_rotation(v);
                break;
            }
            big_rotation(v);
        }
        _root = v;
    }

    // Searches for the given key in the tree with the given root
    // and calls splay for the deepest visited node after that.
    // If found, returns a pointer to the node with the given key.
    // Otherwise, returns a pointer to the node with the smallest
    // bigger key (next value in the order).
    // If the key is bigger than all keys in the tree,
    // returns NULL.
    Vertex* find(Vertex*& _root, ll key) {
        Vertex* v = _root;
        Vertex* last = _root;
        Vertex* next = NULL;
        while (v != NULL) {
            if (v->key >= key && (next == NULL || v->key < next->key)) {
                next = v;
            }
            last = v;
            if (v->key == key) {
                break;
            }
            if (v->key < key) {
                v = v->right;
            } else {
                v = v->left;
            }
        }
        splay(_root, last);
        return next;
    }

    void split(Vertex* _root, ll key, Vertex*& left, Vertex*& right) {
        right = find(_root, key);
        splay(_root, right);
        if (right == NULL) {
            left = _root;
            return;
        }
        left = right->left;
        right->left = NULL;
        if (left != NULL) {
            left->parent = NULL;
        }
        update(left);
        update(right);
    }

    Vertex* merge(Vertex* left, Vertex* right) {
        if (left == NULL) return right;
        if (right == NULL) return left;
        Vertex* min_right = right;
        while (min_right->left != NULL) {
            min_right = min_right->left;
        }
        splay(right, min_right);
        right->left = left;
        update(right);
        return right;
    }

    void insert(ll x) {
        Vertex* left = NULL;
        Vertex* right = NULL;
        Vertex* new_vertex = NULL;
        split(root, x, left, right);
        if (right == NULL || right->key != x) {
            new_vertex = new Vertex(x, x, NULL, NULL, NULL);
        }
        root = merge(merge(left, new_vertex), right);
    }

    void erase(ll x) {
        auto _res = find(root, x);
        if (_res == NULL) return;
        if (root->key != x) return;
        auto lf = root->left, rg = root->right;
        delete root;
        root = merge(lf, rg);
        if (root) root->parent = NULL;
    }

    bool find(ll x) {
        auto _res = find(root, x);
        if (_res == NULL) {
            return false;
        }
        if (root->key != x) return false;
        return true;
    }

    long long sum(ll from, ll to) {
        Vertex* left = NULL;
        Vertex* middle = NULL;
        Vertex* right = NULL;
        split(root, from, left, middle);
        split(middle, to + 1, middle, right);
        long long ans = 0;

        if (middle) ans = middle->sum;

        middle = merge(middle, right);
        root = merge(left, middle);

        return ans;
    }
};