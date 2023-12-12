#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int gcd(int a, int b) {
    if (a < b) return gcd(b, a);
    else if (a % b == 0) return b;
    else return gcd(b, a % b);
}

int gen_key(int q) {
    int key = rand() % (int)pow(10, 20);
    while (gcd(q, key) != 1) {
        key = rand() % (int)pow(10, 20);
    }
    return key;
}

int power(int a, int b, int c) {
    int x = 1;
    int y = a;

    while (b > 0) {
        if (b % 2 != 0) {
            x = (x * y) % c;
        }
        y = (y * y) % c;
        b = b / 2;
    }

    return x % c;
}

pair<vector<int>, int> encrypt(const string& msg, int q, int h, int g) {
    vector<int> en_msg;
    int k = gen_key(q);
    int s = power(h, k, q);
    int p = power(g, k, q);

    for (char i : msg) {
        en_msg.push_back(i);
    }

    cout << "g^k used : " << p << endl;
    cout << "g^ak used : " << s << endl;

    for (int i = 0; i < en_msg.size(); ++i) {
        en_msg[i] = s * int(en_msg[i]);
    }

    return make_pair(en_msg, p);
}

vector<char> decrypt(const vector<int>& en_msg, int p, int key, int q) {
    vector<char> dr_msg;
    int h = power(p, key, q);

    for (int i : en_msg) {
        dr_msg.push_back(char(i / h));
    }

    return dr_msg;
}

int main() {
    srand(time(0)); 

    string msg = "encryption";
    cout << "Original Message : " << msg << endl;

    int q = rand() % (int)pow(10, 50) + pow(10, 20);
    int g = rand() % (q - 2) + 2;

    int key = gen_key(q);
    int h = power(g, key, q);

    cout << "g used : " << g << endl;
    cout << "g^a used : " << h << endl;

    auto encrypted_message = encrypt(msg, q, h, g);
    auto decrypted_message = decrypt(encrypted_message.first, encrypted_message.second, key, q);

    cout << "Decrypted Message : " << string(decrypted_message.begin(), decrypted_message.end()) << endl;

    return 0;
}
