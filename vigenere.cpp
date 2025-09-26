#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string vigenere_encrypt(const string &text, const string &key) {
    string result = "";
    int j = 0;
    for (char c : text) {
        if (isalpha(c)) {
            char offset = isupper(c) ? 'A' : 'a';
            char k = toupper(key[j % key.size()]) - 'A';
            result += (c - offset + k) % 26 + offset;
            j++;
        } else result += c;
    }
    return result;
}

string vigenere_decrypt(const string &text, const string &key) {
    string result = "";
    int j = 0;
    for (char c : text) {
        if (isalpha(c)) {
            char offset = isupper(c) ? 'A' : 'a';
            char k = toupper(key[j % key.size()]) - 'A';
            result += (c - offset - k + 26) % 26 + offset;
            j++;
        } else result += c;
    }
    return result;
}

int main() {
    string plainText, cipherText, key;

    cout << "===== VIGENERE CIPHER =====" << endl;
    cout << "\nNhap van ban can ma hoa: ";
    getline(cin, plainText);

    cout << "Nhap khoa (chuoi ky tu): ";
    cin >> key;
    cin.ignore();

    string encrypted = vigenere_encrypt(plainText, key);
    cout << "Van ban sau khi ma hoa: " << encrypted << endl;

    cout << "\nNhap van ban can giai ma: ";
    getline(cin, cipherText);

    string decrypted = vigenere_decrypt(cipherText, key);
    cout << "Van ban sau khi giai ma: " << decrypted << endl;

    return 0;
}
