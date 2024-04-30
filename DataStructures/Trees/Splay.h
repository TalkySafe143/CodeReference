typedef long long ll;

struct Node {
    ll key;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(ll d) : key(d) {};
};

struct Splay {
    Node* root;
    Splay() : root(nullptr) {}
    Splay(Node* N) : root(N) {}


    Node* Zig(Node* P, Node *C) {

        if (C == P->left) {
            P->left = C->right;
            C->right = P;
        } else {
            P->right = C->left;
            C->left = P;
        }
        C->parent = P->parent;
        P->parent = C;
        return C;
    }

    Node* ZigZig(Node* G, Node* P, Node* C) {
        bool isLeft = true;
        auto parentOfG = G->parent;

        if (parentOfG != nullptr && G == parentOfG->right) isLeft = false;
        P = Zig(G, P);
        C = Zig(P, C);

        if (parentOfG != nullptr) {
            if (isLeft) parentOfG->left = C;
            else parentOfG->right = C;
        }

        return C;
    }
    Node* ZigZag(Node* G, Node* P, Node* C) {
        bool isLeft = true;

        if (P == G->right) isLeft = false;
        C = Zig(P, C);
        if (isLeft) G->left = C;
        else G->right = C;

        isLeft = true;
        auto parentOfG = G->parent;

        if (parentOfG != nullptr && G == parentOfG->right) isLeft = false;

        C = Zig(G, C);

        if (parentOfG != nullptr) {
            if (isLeft) parentOfG->left = C;
            else parentOfG->right = C;
        }

        return C;
    }

    Node* SplayOp(vector<Node*>& path) {
        int i = (int)path.size()-1;
        auto C = path[i];
        i--;

        while (i >= 0) {
            auto P = path[i];
            i--;
            if (i < 0) {
                C = Zig(P, C);
                return C;
            } else {
                auto G = path[i];
                i--;
                bool leftParent = true;
                if (P == G->right) leftParent = false;
                bool leftChild = true;
                if (C == P->right) leftChild = false;

                if (leftParent == leftChild) C = ZigZig(G, P, C);
                else C = ZigZag(G, P, C);
            }
        }

        return C;
    }

    Node* Find(ll k, Node* u, vector<Node*> & path) {
        path.push_back(u);
        if (u->key == k) return u;

        if (u->key > k) {
            if (u->left == nullptr) return u;
            return Find(k, u->left, path);
        }
        if (u->right == nullptr) return u;
        return Find(k, u->right, path);
    }

    Node* SplayFind(Node *R, ll k) {
        vector<Node*> path;
        Find(k, R, path);
        auto N = SplayOp(path);
        this->root = N;
        return N;
    }

    void SplayInsert(Node* R, ll k) {

        if (this->root == nullptr) {
            this->root = new Node(k);
            return;
        }

        auto trees = Split(R, k);
        Node* node = new Node(k);
        node->left = trees.first;
        if (trees.first != nullptr) trees.first->parent = node;
        if (trees.second != nullptr) trees.second->parent = node;
        node->right = trees.second;
        this->root = node;
    }

    Node* SplayDelete(Node* R, ll k) {
        SplayFind(R, k);
        R = Merge(R->left, R->right);
        return R;
    }

    Node* Merge(Node* R1, Node* R2) {
        ll maxi = R1->key;
        auto node = R1->right;

        while (node != nullptr) {
            maxi = node->key;
            node = node->right;
        }

        SplayFind(R1, maxi);
        auto newRoot = R1;
        R1->right = R2;
        return newRoot;
    }

    pair<Node*, Node*> Split(Node* R, ll x) {
        SplayFind(R, x);
        Node* leftTree, *rightTree;
        if (this->root->key <= x) {
            leftTree = this->root;
            rightTree = this->root->right;
        } else {
            leftTree = this->root->left;
            rightTree = this->root;
        }

        return { leftTree, rightTree };
    }

};