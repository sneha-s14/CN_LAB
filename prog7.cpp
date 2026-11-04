#include <iostream>
#include <string>
#include <random>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

class RSAalgorithm {
    cpp_int prk, puk, mod;

    cpp_int gcd(cpp_int a, cpp_int b) {
        while (b != 0) {
            cpp_int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    cpp_int modInverse(cpp_int e, cpp_int phi) {
        cpp_int t = 0, newt = 1;
        cpp_int r = phi, newr = e;

        while (newr != 0) {
            cpp_int q = r / newr;

            cpp_int temp = t;
            t = newt;
            newt = temp - q * newt;

            temp = r;
            r = newr;
            newr = temp - q * newr;
        }

        if (t < 0)
            t += phi;

        return t;
    }

    cpp_int modPow(cpp_int base, cpp_int exp, cpp_int m) {
        cpp_int result = 1;
        base %= m;

        while (exp > 0) {
            if (exp % 2 == 1)
                result = (result * base) % m;

            base = (base * base) % m;
            exp /= 2;
        }

        return result;
    }

public:
    void getkeys(int bitlen) {
        // Simplified key generation
        cpp_int p = 61;
        cpp_int q = 53;

        mod = p * q;

        cpp_int phi = (p - 1) * (q - 1);

        puk = 17;
        prk = modInverse(puk, phi);
    }

    cpp_int encrypt(cpp_int m) {
        return modPow(m, puk, mod);
    }

    cpp_int decrypt(cpp_int c) {
        return modPow(c, prk, mod);
    }
};

int main() {
    RSAalgorithm rsa;

    rsa.getkeys(512);

    string message;

    cout << "Enter the message to be encrypted: ";
    cin >> message;

    cpp_int m = 0;

    for (char ch : message) {
        m = m * 256 + (unsigned char)ch;
    }

    cpp_int c = rsa.encrypt(m);

    cout << "Encrypted message: " << c << endl;

    cpp_int d = rsa.decrypt(c);

    string decrypted;

    while (d > 0) {
        decrypted.insert(decrypted.begin(), (char)(d % 256));
        d /= 256;
    }

    cout << "Decrypted message: " << decrypted << endl;

    return 0;
}
