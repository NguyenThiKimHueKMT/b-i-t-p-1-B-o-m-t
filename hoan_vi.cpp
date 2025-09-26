#include <bits/stdc++.h>
using namespace std;

string clean(string s){
    string t;
    for(char c:s) if(isalpha(c)) t.push_back(toupper(c));
    return t;
}

vector<int> parseKeyOrder(string key){
    key=clean(key);
    vector<pair<char,int>> arr;
    for(int i=0;i<(int)key.size();i++) arr.push_back({key[i],i});
    sort(arr.begin(),arr.end(),[](auto &a, auto &b){
        if(a.first!=b.first) return a.first<b.first;
        return a.second<b.second;
    });
    vector<int> order(key.size());
    for(int i=0;i<(int)arr.size();i++) order[arr[i].second]=i;
    return order;
}

string encrypt(string pt,string key){
    string s=clean(pt);
    auto order=parseKeyOrder(key);
    int cols=order.size();
    int rows=(s.size()+cols-1)/cols;
    vector<vector<char>> grid(rows,vector<char>(cols,'X'));
    int idx=0;
    for(int r=0;r<rows;r++)
        for(int c=0;c<cols;c++)
            if(idx<(int)s.size()) grid[r][c]=s[idx++];
    string out;
    for(int ord=0;ord<cols;ord++){
        int c=find(order.begin(),order.end(),ord)-order.begin();
        for(int r=0;r<rows;r++) out.push_back(grid[r][c]);
    }
    return out;
}

string decrypt(string ct,string key){
    string s=clean(ct);
    auto order=parseKeyOrder(key);
    int cols=order.size();
    int rows=(s.size()+cols-1)/cols;
    vector<vector<char>> grid(rows,vector<char>(cols,'X'));
    int idx=0;
    for(int ord=0;ord<cols;ord++){
        int c=find(order.begin(),order.end(),ord)-order.begin();
        for(int r=0;r<rows;r++) if(idx<(int)s.size()) grid[r][c]=s[idx++];
    }
    string out;
    for(int r=0;r<rows;r++)
        for(int c=0;c<cols;c++) out.push_back(grid[r][c]);
    // b? X padding cu?i
    while(!out.empty() && out.back()=='X') out.pop_back();
    return out;
}

int main(){
    string key,text;
	cout << "===== Ma hoa Hoan vi =====" << endl;

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
