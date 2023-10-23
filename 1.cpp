
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