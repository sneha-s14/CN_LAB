/*Write a program for error detecting code using CRC-CCITT (16- bits).*/

#include <iostream>
#include <string>
using namespace std;

// Performs CRC division and returns remainder
string divide(string divident, string divisor) {
    int n = divident.length();
    int m = divisor.length();

    for (int i = 0; i < n; i++) {
        if (divident[i] == '1') {
            if (n - i < m)
                break;

            for (int j = 0; j < m; j++) {
                // XOR operation
                if (divisor[j] == '1')
                    divident[i + j] = (divident[i + j] == '1') ? '0' : '1';
            }
        }
    }

    // Return remainder (last m-1 bits)
    return divident.substr(n - m + 1);
}

// Encode: data + CRC remainder
string encode(string data, string key) {
    string zeros(key.length() - 1, '0');          // append zeros
    string temp = data + zeros;
    string rem = divide(temp, key);
    return data + rem;
}

// Decode: returns true if error is present
bool decode(string encodedData, string key) {
    string rem = divide(encodedData, key);
    return rem.find('1') != string::npos;         // true if any '1' found
}

int main() {
    string key, data, encoded;

    cout << "Enter binary key : ";
    cin >> key;

    cout << "Enter binary data : ";
    cin >> data;

    // Encoding
    encoded = encode(data, key);
    cout << "Encoded data : " << encoded << endl;

    // Decoding / Error checking
    cout << "Enter binary encoded data : ";
    cin >> encoded;

    if (decode(encoded, key))
        cout << "Error in the data" << endl;
    else
        cout << "Data is error free" << endl;

    return 0;
}
