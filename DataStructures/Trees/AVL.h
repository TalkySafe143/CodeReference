
/*
    AVL Tree implementation
    Sources:  Me
    Verification: *
*/
typedef long long ll;

struct Node {
    ll key;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
    ll height = 1;

    Node(ll d) : key(d) {};
};

struct AVL {

    Node* root;

    AVL() : root(nullptr) {}
    AVL(Node* N) : root(N) {}


private:

    Node* LeftDescendant(Node * N) {
        if (N->left == nullptr) return N;
        return LeftDescendant(N->left);
    }

    Node* RightAncestor(Node* N) {
        if (N->key < N->parent->key) return N->parent;
        return RightAncestor(N->parent);
    }

    Node* Next(Node* u) {
        if (u->right != nullptr) return LeftDescendant(u->right);
        return RightAncestor(u);
    }

    void Insert(ll k, Node* R) {
        if (R == nullptr) {
            this->root = new Node(k);
            return;
        }
        auto P = Find(k, R);
        auto N = new Node(k);
        N->parent = P;
        if (k > P->key) P->right = N;
        else P->left = N;
    }

    void DeleteFromKey(ll k, Node* R) {
        auto N = Find(k, R);
        Delete(N);
        delete N;
    }

    Node* Delete(Node* N) {
        Node* ret;
        if (N->right == nullptr) {
            bool okNParent = true;
            if (N->parent == nullptr) okNParent = false;

            if (okNParent) {
                if (N->key > N->parent->key) N->parent->right = N->left;
                else N->parent->left = N->left;
            }
            if (N->left != nullptr) N->left->parent = N->parent;
            ret = N->left;
        } else {
            Node* X = Next(N);
            bool okNParent=true, okXParent=true;

            if (N->parent == nullptr) okNParent = false;
            if (X->parent == nullptr) okXParent = false;

            if (okNParent) {
                if (X->key > N->parent->key) {
                    N->parent->right = X;
                } else {
                    N->parent->left = X;
                }
            }

            if (okXParent) {

                if (X->right == nullptr) {
                    if (X->key > X->parent->key) X->parent->right = nullptr;
                    else X->parent->left = nullptr;
                } else {
                    if (X->right->key > X->parent->key) {
                        X->parent->right = X->right;
                    } else {
                        X->parent->left = X->right;
                    }
                }
            }

            if (X->right != nullptr) X->right->parent = X->parent;
            X->parent = N->parent;
            X->right = N->right;
            X->left = N->left;

            if (N->right != nullptr) N->right->parent = X;
            if (N->left != nullptr) N->left->parent = X;
            ret = X;
        }

        return ret;
    }

    void AVLDelete(Node* N) {
        auto M = Delete(N);
        if(M != nullptr) Rebalance(M->parent);
        //delete N;
    }

    void RotateRight(Node* X) {
        auto P = X->parent;
        auto Y = X->left;
        auto B = Y->right;

        if (P != nullptr) {
            if (Y == nullptr) {
                if (X->key > P->key) P->right = Y;
                else P->left = Y;
            } else {
                if (Y->key > P->key) P->right = Y;
                else P->left = Y;
            }
        }
        Y->parent = P;
        X->parent = Y;
        Y->right = X;
        if (B != nullptr) B->parent = X;
        X->left = B;

        if (X == this->root) {
            this->root = Y;
            Y->parent = nullptr;
        }
    }

    void RotateLeft(Node *Y) {
        auto P = Y->parent;
        auto X = Y->right;
        auto B = X->left;

        if (P != nullptr) {
            if (X == nullptr) {
                if (Y->key > P->key) P->right = X;
                else P->left = X;
            } else {
                if (X->key > P->key) P->right = X;
                else P->left = X;
            }
        }
        X->parent = P;
        Y->parent = X;
        X->left = Y;
        if (B != nullptr) B->parent = Y;
        Y->right = B;
        if (Y == this->root) {
            this->root = X;
            X->parent = nullptr;
        }
    }

    ll ComputeHeight(Node* N) {
        if (N == nullptr) return 0LL;
        if (N->left == nullptr && N->right == nullptr) return N->height = 1LL;
        return N->height = 1LL + max(ComputeHeight(N->left), ComputeHeight(N->right));
    }

    void RebalaceRight(Node* N) {
        auto M = N->left;
        ll nLeftH = 0, nRightH = 0;
        if (M != nullptr) {
            if (M->right != nullptr) nRightH = M->right->height;
            if (M->left != nullptr) nLeftH = M->left->height;
        }
        if (M != nullptr && M->right != nullptr && nLeftH > nRightH) RotateLeft(M);
        RotateRight(N);
        ComputeHeight(N);
        ComputeHeight(M);
    }

    void RebalanceLeft(Node* N) {
        auto M = N->right;
        ll nLeftH = 0, nRightH = 0;
        if (M != nullptr) {
            if (M->right != nullptr) nRightH = M->right->height;
            if (M->left != nullptr) nLeftH = M->left->height;
        }
        if (M != nullptr && M->left != nullptr && nLeftH > nRightH) RotateRight(M);
        RotateLeft(N);
        ComputeHeight(N);
        ComputeHeight(M);
    }

    void Rebalance(Node* N) {
        if (N == nullptr) return;
        auto P = N->parent;
        ll nLeftH, nRightH;

        if (N->left == nullptr) nLeftH = 0;
        else nLeftH = N->left->height;

        if (N->right == nullptr) nRightH = 0;
        else nRightH = N->right->height;

        if (nLeftH > nRightH+1LL) RebalaceRight(N);
        if (nRightH > nLeftH+1LL) RebalanceLeft(N);

        ComputeHeight(N);
        if (P != nullptr) Rebalance(P);
    }

    void MergeWithRoot(Node* R1, Node* R2, Node* T) {
        T->left = R1;
        T->right = R2;
        R1->parent = T;
        R2->parent = T;
    }

    Node* AVLMergeWithRoot(Node* R1, Node* R2, Node* T) {
        if (R1 == nullptr || R2 == nullptr) return T;
        if (abs(R1->height - R2->height) <= 1) {
            MergeWithRoot(R1, R2, T);
            T->height = max(R1->height, R2->height)+1;
            return T;
        } else if (R1->height > R2->height) {
            auto Rp = AVLMergeWithRoot(R1->right, R2, T);
            R1->right = Rp;
            Rp->parent = R1;
            Rebalance(R1);
            return T;
        } else if (R1->height < R2->height) {
            auto Rp = AVLMergeWithRoot(R1, R2->left, T);
            R2->left = Rp;
            Rp->parent = R2;
            Rebalance(R2);
            return T;
        }
        return T;
    }

public:

    void InOrder(Node* U, void (*Visit)(ll)) {
        if (U == nullptr) return;
        InOrder(U->left, Visit);
        (*Visit)(U->key);
        InOrder(U->right, Visit);
    }

    void AVLInsert(ll k, Node* R) {
        if (R == nullptr) {
            this->root = new Node(k);
            return;
        }
        Insert(k, R);
        auto N = Find(k, R);
        Rebalance(N);
    }

    pair<AVL, AVL> Split(Node* R, ll x) {
        if (R == nullptr) return { AVL(nullptr), AVL(nullptr) };
        if (x <= R->key) {
            auto Rpair = Split(R->left, x);
            R->left = nullptr;
            auto R3 = AVLMergeWithRoot(Rpair.second.root, R->right, R);
            R3->parent = nullptr;
            return {Rpair.first, AVL(R3)};
        } else if (x > R->key) {
            auto Rpair = Split(R->right, x);
            R->right = nullptr;
            auto R3 = AVLMergeWithRoot(R->left, Rpair.first.root, R);
            R3->parent = nullptr;
            return { AVL(R3), Rpair.second };
        }
    };

    Node* Merge(Node* R1, Node* R2) {
        auto T = Find(1e18, R1);
        AVLDelete(T);
        AVLMergeWithRoot(R1, R2, T);
        return T;
    }

    void AVLDeleteFromKey(ll k, Node* R) {
        auto N = Find(k, R);
        auto M = Delete(N);
        Rebalance(M->parent);
        delete N;
    }

    void RangeSearch(ll x, ll y, Node* R, vector<ll> &result) {
        auto N = Find(x, R);
        while (N->key <= y) {
            if (N->key >= x) result.push_back(N->key);
            N = Next(N);
        }
    }

    Node* Find(ll k, Node* u) {
        if (u->key == k) return u;

        if (u->key > k) {
            if (u->left == nullptr) return u;
            return Find(k, u->left);
        }
        if (u->right == nullptr) return u;
        return Find(k, u->right);
    }
};