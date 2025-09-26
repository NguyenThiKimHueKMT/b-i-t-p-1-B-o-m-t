#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int mod_inverse(int a, int m) {
    a = (a % m + m) % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

string affine_encrypt(const string &text, int a, int b) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            char offset = isupper(c) ? 'A' : 'a';
            result += char((a * (c - offset) + b) % 26 + offset);
        } else result += c;
    }
    return result;
}

string affine_decrypt(const string &text, int a, int b) {
    int a_inv = mod_inverse(a, 26);
    if (a_inv == -1) return "Loi: 'a' khong co nghich dao modulo 26";
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            char offset = isupper(c) ? 'A' : 'a';
            int x = (a_inv * ((c - offset - b + 26) % 26)) % 26;
            result += char(x + offset);
        } else result += c;
    }
    return result;
}

int main() {
    string plainText, cipherText;
    int a, b;

    cout << "===== AFFINE CIPHER =====" << endl;
    cout << "\nNhap van ban can ma hoa: ";
    getline(cin, plainText);

    cout << "Nhap khoa a (coprime voi 26): ";
    cin >> a;
    cout << "Nhap khoa b: ";
    cin >> b;
    cin.ignore();

    string encrypted = affine_encrypt(plainText, a, b);
    cout << "Van ban sau khi ma hoa: " << encrypted << endl;

    cout << "\nNhap van ban can giai ma: ";
    getline(cin, cipherText);

    string decrypted = affine_decrypt(cipherText, a, b);
    cout << "Van ban sau khi giai ma: " << decrypted << endl;

    return 0;
}
