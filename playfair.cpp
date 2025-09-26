#include <bits/stdc++.h>
using namespace std;

string clean(string s) {
    string t;
    for (char c : s) {
        if (isalpha(c)) {
            c = toupper(c);
            if (c == 'J') c = 'I';
            t.push_back(c);
        }
    }
    return t;
}

vector<vector<char>> buildSquare(const string& key) {
    vector<bool> used(26, false);
    used['J' - 'A'] = true; // gộp J vào I
    string seq;

    for (char c : key) {
        if (c == 'J') c = 'I';
        if (!used[c - 'A']) {
            used[c - 'A'] = true;
            seq.push_back(c);
        }
    }
    for (int i = 0; i < 26; i++) {
        if (!used[i]) seq.push_back('A' + i);
    }

    vector<vector<char>> m(5, vector<char>(5));
    int idx = 0;
    for (int r = 0; r < 5; r++)
        for (int c = 0; c < 5; c++)
            m[r][c] = seq[idx++];
    return m;
}

pair<int,int> findPos(const vector<vector<char>>& m, char ch) {
    if (ch == 'J') ch = 'I';
    for (int r=0;r<5;r++)
        for (int c=0;c<5;c++)
            if (m[r][c]==ch) return {r,c};
    return {-1,-1};
}

string prepare(string pt) {
    pt = clean(pt);
    string out;
    for (size_t i=0;i<pt.size();) {
        char a = pt[i];
        char b = (i+1<pt.size()) ? pt[i+1] : '\0';
        if (b=='\0') {
            out.push_back(a);
            out.push_back('X');
            i++;
        } else if (a==b) {
            out.push_back(a);
            out.push_back('X');
            i++;
        } else {
            out.push_back(a);
            out.push_back(b);
            i+=2;
        }
    }
    if (out.size()%2==1) out.push_back('X');
    return out;
}

string encrypt(string pt, string key) {
    auto m=buildSquare(clean(key));
    string s=prepare(pt);
    string out;
    for (size_t i=0;i<s.size();i+=2){
        auto [r1,c1]=findPos(m,s[i]);
        auto [r2,c2]=findPos(m,s[i+1]);
        if(r1==r2){
            out.push_back(m[r1][(c1+1)%5]);
            out.push_back(m[r2][(c2+1)%5]);
        } else if(c1==c2){
            out.push_back(m[(r1+1)%5][c1]);
            out.push_back(m[(r2+1)%5][c2]);
        } else {
            out.push_back(m[r1][c2]);
            out.push_back(m[r2][c1]);
        }
    }
    return out;
}

string decrypt(string ct, string key) {
    auto m=buildSquare(clean(key));
    string s=clean(ct);
    string out;
    for (size_t i=0;i<s.size();i+=2){
        auto [r1,c1]=findPos(m,s[i]);
        auto [r2,c2]=findPos(m,s[i+1]);
        if(r1==r2){
            out.push_back(m[r1][(c1+4)%5]);
            out.push_back(m[r2][(c2+4)%5]);
        } else if(c1==c2){
            out.push_back(m[(r1+4)%5][c1]);
            out.push_back(m[(r2+4)%5][c2]);
        } else {
            out.push_back(m[r1][c2]);
            out.push_back(m[r2][c1]);
        }
    }
    // loại bỏ X padding: giữa 2 ký tự giống nhau hoặc cuối
    string cleaned;
    for (size_t i=0;i<out.size();i++) {
        if (out[i]=='X') {
            if (i==out.size()-1) continue; // X cuối
            if (i>0 && out[i-1]==out[i+1]) continue; // X chèn giữa
        }
        cleaned.push_back(out[i]);
    }
    return cleaned;
}

int main() {
    string key, text;
	cout << "===== Ma hoa playfair =====" << endl;

    cout<<"Nhap van ban can ma hoa: ";
    getline(cin,text);
        cout<<"Nhap khoa: ";
    getline(cin,key);
    string ct=encrypt(text,key);
    
    cout<<"Ciphertext: "<<ct<<"\n";

    cout<<"Nhap van ban can giai ma: ";
    getline(cin,text);
    string pt=decrypt(text,key);
    cout<<"Plaintext: "<<pt<<"\n";
}
