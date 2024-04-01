/*
 *  Build a min/max heap tree
    Sources: Me
    Verification: *
 * */
struct Heap {
    vector<int> H;
    const int INF = 1e6;
    int size;
    explicit Heap(vector<int> &a) {
        H = vector<int>(a.begin(), a.end());
        size = H.size();
        for (int i = (size >> 1)-1; i >= 0; i--) siftDown(i);
    }

    void changePriority(int i, int p) {
        int oldp = H[i];
        H[i] = p;
        if (p > oldp) siftUp(i); // for min-heap p < oldp
        else siftDown(i);
    }

    void removeIndex(int i) {
        H[i] = INF;
        siftUp(i);
        extractFirst();
    }

    int extractFirst() {
        int result = H[0];
        H[0] = H.back();
        H.pop_back();
        siftDown(0);
        return result;
    }

    void insert(int el) {
        H.push_back(el);
        siftUp(H.size()-1);
    }

    void siftUp(int i) {
        while (i > 0 && H[parent(i)] < H[i]) { // for min heap H[parent(i)] > H[i]
            swap(H[parent(i)], H[i]);
            i = parent(i);
        }
    }

    void siftDown(int i) {
        int maxIndex = i;
        int l = leftChild(i);
        if (l <= H.size()-1 && H[l] > H[maxIndex]) maxIndex = l; // for min-heap H[l] < H[maxIndex]
        int r = rightChild(i);
        if (r <= H.size()-1 && H[r] > H[maxIndex]) maxIndex = r; // for min-heap H[l] < H[maxIndex]
        if (i != maxIndex) {
            swap(H[i], H[maxIndex]);
            siftDown(maxIndex);
        }
    }

    int parent(int i) {
        return (i-1)/2;
    }

    int leftChild(int i) {
        return (2*i)+1;
    }

    int rightChild(int i) {
        return (2*i)+2;
    }
};
