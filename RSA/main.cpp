#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

int p, q;       // prime numbers
int n;          // product of prime numbers
int phi;        // (p - 1) * (q - 1)
int e;          // public key
int d;          // private key
string oMsg;    // original message
string eMsg;    // encrypted message
string dMsg;    // decrypted message
int X[200];     // message length

int gcd(int a, int b)
{
    /// Euclidean algorithm
    if (a == 0)
        return b;
    return gcd(b % a, a);
}
bool isPrime(int a) {
    bool isPrime = true;

    if (a == 0 || a == 1) {
        isPrime = false;
    }

    for (int i = 2; i <= a / 2; ++i) {
        if (a % i == 0) {
            isPrime = false;
            break;
        }
    }
    return isPrime;
}
int calculateD() {

    /// Extended Euclidean algorithm
    int x=0, y=1, u=1, v=0;
    int m, N, a, b;
    int Q, P;
    x = 0;
    y = 1;
    u = 1;
    v = 0;
    for (a = e, b = phi; 0 != a; b = a, a = P, x = u, y = v, u = m, v = N) {
        Q = b / a;
        P = b % a;
        m = x - (u * Q);
        N = y - (v * Q);
    }
    if(m+x < 0)
        return m+x+phi;
    else return m+x;
}
int calculateE() {
    for (int j = 2; j < phi; j++) {
        if(gcd(j, phi)==1){
            return j;
        }
    }
    return 0;
}

void encryption() {

    int k; // encrypted value
    int t; // ascii int value of char

    unsigned char ch;
    eMsg = "";
    for (int i = 0; i < oMsg.length(); i++) {
        ch = oMsg.at(i);
        t = int(ch); //int value of char


        k = 1;
        for (int j = 0; j < e; j++) {
            k = k * t;
            k = k % n;
        }

        X[i] = 0;
        if (k > 126) {
            while (k > 126) {
                k = k - 126;
                X[i]++;
            }
        }
        eMsg += static_cast<char>(k);
    }
}
void decryption() {
    int k;
    int t;

    unsigned char ch;
    dMsg = "";
    for (int i = 0; i < eMsg.length(); i++) {
        ch = eMsg.at(i);
        t = int(ch);

        if (X[i] != 0) {
            t = t + (126 * X[i]);
        }

        k = 1;
        for (int j = 0; j < d; j++) {
            k = k * t;
            k = k % n;
        }
        dMsg += static_cast<char>(k);
    }
}
void input() {

    bool flag = false;
    while (!flag) {
        cout << "Select 2 random prime numbers: "; cin >> p >> q;
        if (!isPrime(p) || !isPrime(q)) {
            if (!isPrime(p))
                cout << p << " is not a prime number" << endl;
            if (!isPrime(q))
                cout << q << " is not a prime number" << endl;
            flag = false;
        } else{
            flag = true;
        }
    }

    n = p * q;
    phi = (p - 1) * (q - 1);
    e = calculateE();
    d = calculateD();
    cout << "=========================================" << endl;
    cout << "p = " << p << endl;
    cout << "q = " << q << endl;
    cout << "n = " << n << endl;
    cout << "phi = " << phi << endl;
    cout << "e = " << e << endl;
    cout << "d = " << d << endl;
    cout << "=========================================" << endl;
}
void initMsg(){
    cout << "Enter text (max 200 char): ";
    getline(cin >> ws, oMsg);
}
int main()
{
    int opt = 1;
    while (opt) {
        cout << "Choose: " << endl;
        cout << "1. Choose prime numbers" << endl;
        cout << "2. Write text" << endl;
        cout << "3. Encrypt text" << endl;
        cout << "4. Decrypt text" << endl;
        cout << "5. End" << endl;

        cin >> opt;

        if (opt == 1) {
            input();
        } else if (opt == 2){
            initMsg();
            cout << " Original Message = " << oMsg << endl;
            cout << "=========================================" << endl;
        } else if (opt == 3){
            encryption();
            cout << " Encrypted message = " << eMsg << endl;
            cout << "=========================================" << endl;
        } else if (opt == 4){
            decryption();
            cout << " Decrypted message = " << dMsg << endl;
            cout << "=========================================" << endl;
        } else{
            opt = 0;
        }
    }

    return 0;
}


