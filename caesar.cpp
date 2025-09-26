#include <iostream>
#include <string>
using namespace std;

string caesar_encrypt(const string &text, int key) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            char offset = isupper(c) ? 'A' : 'a';
            result += (c - offset + key) % 26 + offset;
        } else {
            result += c; // giữ nguyên ký tự không phải chữ cái
        }
    }
    return result;
}

string caesar_decrypt(const string &text, int key) {
    return caesar_encrypt(text, 26 - key); // giải mã bằng cách đảo chiều mã hóa
}

int main() {
    string plainText, cipherText;
    int key;

    cout << "===== CAESAR CIPHER =====" << endl;

    // --- Mã hóa ---
    cout << "\nNhap van ban can ma hoa: ";
    getline(cin, plainText);

    cout << "Nhap khoa (1-25): ";
    cin >> key;
    cin.ignore(); // bỏ ký tự xuống dòng

    string encrypted = caesar_encrypt(plainText, key);
    cout << "Van ban sau khi ma hoa: " << encrypted << endl;

    // --- Giải mã ---
    cout << "\nNhap van ban can giai ma: ";
    getline(cin, cipherText);

    string decrypted = caesar_decrypt(cipherText, key);
    cout << "Van ban sau khi giai ma: " << decrypted << endl;

    return 0;
}
