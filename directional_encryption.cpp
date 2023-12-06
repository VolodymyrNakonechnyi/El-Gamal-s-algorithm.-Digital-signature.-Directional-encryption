#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

int modPow(int base, int exponent, int modulus) {
    int result = 1;
    base = base % modulus;

    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;

        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }

    return result;
}

vector<int> breakMessage(const string& msg) {
    vector<int> blocks;
    for (char ch : msg) {
        blocks.push_back(static_cast<int>(ch));
    }
    return blocks;
}

string joinBlocks(const vector<int>& blocks) {
    string msg;
    for (int block : blocks) {
        msg.push_back(static_cast<char>(block));
    }
    return msg;
}

pair<int, int> encryptBlock(int m, int k, int p, int g, int b) {
    int x = modPow(g, k, p);
    int y = (m * modPow(b, k, p)) % p;
    return { x, y };
}

int decryptBlock(const pair<int, int>& ciphertext, int a, int p) {
    int s = modPow(ciphertext.first, a, p);
    int invS = modPow(s, p - 2, p);
    int m = (ciphertext.second * invS) % p;
    return m;
}

int main() {
    srand(time(0));

    int p = rand() % ((int)pow(2, 12) + 1) + (int)pow(2, 11);
    int g = rand() % (p - 1) + 1;

    int a = rand() % (p - 1) + 1;
    int b = modPow(g, a, p);

    string message = "Hello, ElGamal Encryption!";

    vector<int> messageBlocks = breakMessage(message);

    vector<pair<int, int>> ciphertextBlocks;
    for (int block : messageBlocks) {
        int k = rand() % (p - 2) + 1;
        ciphertextBlocks.push_back(encryptBlock(block, k, p, g, b));
    }

    cout << "Encrypted Blocks: ";
    for (const auto& block : ciphertextBlocks) {
        cout << "(" << block.first << ", " << block.second << ") ";
    }
    cout << endl;

    vector<int> decryptedBlocks;
    for (const auto& block : ciphertextBlocks) {
        decryptedBlocks.push_back(decryptBlock(block, a, p));
    }

    string decryptedMessage = joinBlocks(decryptedBlocks);

    cout << "Decrypted Message: " << decryptedMessage << endl;

    return 0;
}
