#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

int gcd(int a, int b) {
    if (a < b)
        return gcd(b, a);
    else if (a % b == 0)
        return b;
    else
        return gcd(b, a % b);
}

int modInverse(int a, int m) {
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

pair<int, int> signMessage(const string& msg, int p, int g, int a) {
    int k = rand() % (p - 2) + 1;

    int r = int(pow(g, k)) % p;

    int Hm = msg.length();

    int invK = modInverse(k, p - 1);
    int s = (Hm - a * r + (p - 1) * (p - 1)) * invK % (p - 1);

    return { r, s };
}

bool verifySignature(const string& msg, const pair<int, int>& signature, int p, int g, int b) {
    int Hm = msg.length();

    int y = modInverse(b, p);

    int invS = modInverse(signature.second, p - 1);
    int u1 = Hm * invS % (p - 1);

    int u2 = signature.first * invS % (p - 1);

    int v = (int(pow(g, u1)) * int(pow(y, u2))) % p;

    return v == signature.first;
}

int main() {
    srand(time(0));  

    int p = rand() % ((int)pow(2, 12) + 1) + (int)pow(2, 11); 
    int g = rand() % (p - 1) + 1;  

    int a = rand() % (p - 1) + 1;  // private key
    int b = int(pow(g, a)) % p;    // public key

    string message = "Hello, ElGamal!";


    pair<int, int> signature = signMessage(message, p, g, a);
    cout << "Signature: (" << signature.first << ", " << signature.second << ")" << endl;

    bool isValid = verifySignature(message, signature, p, g, b);
    cout << "Signature is " << (isValid ? "valid" : "invalid") << endl;

    return 0;
}
