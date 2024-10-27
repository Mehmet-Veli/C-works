
void cm(void* ptr, size_t size) {
    unsigned char* p = (unsigned char*)ptr;
    while (size--) {
        *p++ = 0;
    }
}

/**
 * Return an array of starting indices of substring(s) in `s` that are a concatenation 
 * of each word in `words` exactly once, in any order. 
 * The sizes of the arrays are returned as *returnSize array. 
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findSubstring(char* s, char** w, int ws, int* rs) {
    int nw = 0, tl = 1, wl = strlen(w[0]), sl = strlen(s);
    int count[ws + 1], map[wl * ws + 1], t[wl * ws][26];
    
    cm(count, sizeof(count));
    cm(map, sizeof(map));
    cm(t, sizeof(t));

    for (int i = 0; i < ws; i++) {
        int n = 0;
        for (int j = 0; j < wl; j++) {
            char nIdx = w[i][j] - 'a';
            if (t[n][nIdx] == 0) t[n][nIdx] = tl++;
            n = t[n][nIdx];
        }
        if (map[n] == 0) map[n] = ++nw;
        count[map[n]]++;
    }

    int* result = (int*)malloc(sl * sizeof(int));
    int resLen = 0;
    int m[sl / wl + 1], wCount[nw + 1];

    for (int i = 0; i < wl; i++) {
        if (i + wl * ws > sl) continue;
        cm(wCount, sizeof(wCount));
        int h = 0, mCount = 0;

        for (int j = i, k = 0, l = 0; j + wl <= sl; j += wl, k++) {
            int n = 0;
            for (int mIdx = j; mIdx < j + wl; mIdx++) {
                n = t[n][s[mIdx] - 'a'];
                if (n == 0) { mCount++; m[k] = -1; break; }
            }
            if (n != 0) {
                int cIdx = map[n];
                m[k] = cIdx;
                wCount[cIdx]++;
                if (wCount[cIdx] == count[cIdx]) h++;
                else while (wCount[cIdx] > count[cIdx]) {
                    int leftIdx = m[l++];
                    if (leftIdx == -1) mCount--;
                    else {
                        if (wCount[leftIdx] == count[leftIdx]) h--;
                        wCount[leftIdx]--;
                    }
                }
            }
            while (l <= k && m[l] == -1) { l++; mCount--; }
            if (h == nw && mCount == 0) result[resLen++] = i + l * wl;
        }
    }

    *rs = resLen;
    return result;
}
