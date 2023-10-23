#include "bits/stdc++.h"

using namespace std;

int getLength(string s) {
    int cnt = 0;
    for (int i = 0; s[i] != '\0'; ++i) {
        ++cnt;
    }
    return cnt;
}

int countUpper(string s) {
    int cnt = 0;
    for (int i = 0; i < getLength(s); ++i) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            ++cnt;
        }
    }
    return cnt;
}

int countMatches(string s, string p) {
    int N = getLength(s);
    int M = getLength(p);
    int cnt = 0;
    for (int i = 0; i <= N - M; ++i) {
        int j;
        for (j = 0; j < M; ++j) {
            if (s[i + j] != p[j]) {
                break;
            }
        }
        if (j == M) {
            ++cnt;
            i += M - 1;
        }
    }
    return cnt;
}

struct Info {
    string name;
    struct Point {
        float kinhDo;
        float viDo;
    } point;
    int vehicle;
};

struct Node {
    Info key;
    Node *left;
    Node *right;
    int color; // 1 red 0 black
};

Node *searchTree(Node *root, string name) {
    if (root == nullptr || root->key.name == name) {
        return root;
    }
    else if (root->key.name > name) {
        return searchTree(root->left, name);
    }
    else {
        return searchTree(root->right, name);
    }
}

Info::Point getLocationName(Node *root, string name) {
    Node *p = searchTree(root, name);
    if (p == nullptr) {
        return { -1e9, 1e9 };
    }
    else {
        return { p->key.point.kinhDo, p->key.point.viDo };
    }
}

// 1st way

int getMax(int a, int b) {
    return a > b ? a : b;
}

void findMax(Node *root, int &value) {
    if (root == nullptr) return;
    value = getMax(value, root->key.vehicle);
    findMax(root->left, value);
    findMax(root->right, value);
}

void searchItem(Node *&root) {
    int max = -1e9;
    findMax(root, max);
    if (max == -1e9) {
        return; // STOP
    }
    if (root->key.vehicle == max) {
        return;
    }
    searchItem(root->left);
    searchItem(root->right);
}

Node *searchMostCongestive(Node *root) {
    int max = -1e9;
    findMax(root, max);
    if (max == -1e9) {
        return nullptr;
    }
    else {
        searchItem(root);
    }
    return root;
}

// 2nd way
Node *createNode(Info info) {
    Node *p = new Node;
    p->key = info;
    p->left = p->right = nullptr;
    p->color = 0;
    return p;
}

void insertNode(Node *&root, Info info) {
    Node *p = createNode(info);
    if (root == nullptr) {
        root = p;
    }
    else if (root->key.vehicle > info.vehicle) {
        insertNode(root->left, info);
    }
    else {
        insertNode(root->right, info);
    }
}

void createTree(Node *root, Node *&subRoot) {
    if (root == nullptr) {
        return;
    }
    insertNode(subRoot, root->key);
    if (root->left != nullptr) {
        createTree(root->left, subRoot);
    }
    if (root->right != nullptr) {
        createTree(root->right, subRoot);
    }
}

Node *searchMostCongestive(Node *root) {
    if (root == nullptr) {
        return nullptr; // CANNOT FIND
    }
    Node *subRoot = nullptr;
    createTree(root, subRoot);
    while (subRoot != nullptr) {
        subRoot = subRoot->right;
    }
    return subRoot;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}