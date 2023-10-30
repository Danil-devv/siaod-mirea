#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

string swapBorderWords(string s) {
    int first = -1, last = -1;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ',') {
            if (first == -1) first = i;
            last = i;
        }
    }

    string res = "";
    for (int i = last + 1; i < s.size(); i++) {
        res += s[i];
    }
    for (int i = first; i <= last; i++) {
        res += s[i];
    }
    for (int i = 0; i < first; i++) {
        res += s[i];
    }
    return res;
}

map<string, int> RobinKarp(string s, vector<string> v) {
    const unsigned long long k = 911382323;
    int n = s.size();

    // массив степеней множителя k
    // pows[i] == k ^ i
    vector<unsigned long long> pows(n + 1);
    pows[0] = 1;
    for (int i = 1; i <= n; i++) {
        pows[i] = pows[i - 1] * k;
    }

    // массив хэшей префиксов строки s
    // h[k] -- хэш префикса длины k
    vector<unsigned long long> hash(n + 1);
    hash[0] = s[0] - 'a' + 1;
    for (int i = 1; i < n; i++) {
        hash[i] = (hash[i - 1] * k + (s[i] - 'a' + 1));
    }

    map<string, int> cnt;  // мапа из пар {строка, кол-во вхождений}
    for (auto t : v) {
        if (t.size() > s.size()) {
            cnt[t] = 0;
            continue;
        }

        unsigned long long h = t[0] - 'a'+1;
        for (int i = 1; i < t.size(); i++) {
            // считаем хэш строки t
            h = (h * k + (t[i] - 'a' + 1));
        }

        for (int i = t.size()-1; i < s.size(); i++) {
            int r = i, l = i - t.size() + 1;
            unsigned long long substringHash = 0;
            if (l == 0) substringHash = hash[r];
            else substringHash = (hash[r] - hash[l - 1] * pows[r - l + 1]);

            // проверяем, что хэши строки t и подстроки s[l..r] совпали
            if (substringHash == h) {
                cnt[t]++;
            }
        }

    }

    return cnt;
}

int main() {
    cout << "first,second,third,fourth,fifth\n";
    cout << swapBorderWords("first,second,third,fourth,fifth") << "\n";

    cout << "-------------------\n";
    string s = "abacaba";
    vector<string> v(5);
    v[0] = "ab";
    v[1] = "a";
    v[2] = "ca";
    v[3] = "aca";
    v[4] = "tt";

    map<string, int> res = RobinKarp(s, v);
    cout << s << "\n";
    for (auto u : v) {
        cout << u << ": " << res[u] << "\n";
    }
    return 0;
}
