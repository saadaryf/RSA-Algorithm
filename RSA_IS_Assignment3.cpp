#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cmath>
using namespace std;

bool validatePrime(int a) {
	if (a <= 1) 
		return false;
	else if (a == 2)
		return true;
	else if (a % 2 == 0)
		return false;
	for (int i = 2; i < a; i++) {
		if (a % i == 0) 
			return false;
	}
	return true;
}
int findGCD(int a, int b) {
	while (b != 0) {
		int temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}
bool validateE(int e, int phiN, int n) {
	return (e > 1 && e < n && findGCD(e, phiN) == 1);
}
int modInverse(int e, int phiN) {
	int d = 0;
	int i = 1;
	while ((phiN * i + 1) % e != 0) {
		i++;
	}
	d = (phiN * i + 1) / e;
	return d;
}
int findD(int e, int phiN) {
	return modInverse(e, phiN);
}
string readPlainText(string filename) {
	ifstream fin(filename);
	if (fin.is_open()) {
		string plaintext;
		getline(fin, plaintext);
		fin.close();
		return plaintext;
	}
	else {
		cout << "\nUnable to open file: " << filename << endl;
	}
}
int calculateCipherValue(int base, int exponent, int modulus) {
	int result = 1;
	base = base % modulus;
	for (int i = 0; i < exponent; i++)
		result = (result * base) % modulus;
	return result;
}
string encryptData(string plaintext, int e, int n) {
	// cipher = plaitext (power e) mod n
	vector<int> plainTextInNumbers;
	vector<int> cipherTextInNumbers;
	string cipherText;
	for (char letter : plaintext) {
		int ascii = static_cast<int>(letter);
		plainTextInNumbers.push_back(ascii);
	}
	for (int no : plainTextInNumbers) {
		//cout << "\nNumbers for HELLO: " << no << " - ";
		int cipherValue = calculateCipherValue(no, e, n);
		cipherTextInNumbers.push_back(cipherValue);
	}
	for (int no : cipherTextInNumbers) {
		//cout << "\nCipher Values after: " << no << " - ";
		char letter = static_cast<char>(no);
		cipherText = cipherText + letter;
	}
	return cipherText;
}
string decryptText(string ciphertext, int d, int n) {
	//plain = cipher(power d) mod n
	vector<int> cipherTextInNumbers;
	vector<int> plainTextInNumbers;
	string plaintext;
	for (char letter : ciphertext) {
		int cipherValue = static_cast<int>(letter);
		cipherTextInNumbers.push_back(cipherValue);
	}
	for (int no : cipherTextInNumbers) {
		int plainValue = calculateCipherValue(no, d, n);
		plainTextInNumbers.push_back(plainValue);
	}
	for (int no : plainTextInNumbers) {
		char letter = static_cast<char>(no);
		plaintext = plaintext + letter;
	}
	return plaintext;
}
int main() {
	int p, q; // prime numbers
	cout << "Input first prime number: ";
	cin >> p;
	cout << "Input second prime number: ";
	cin >> q;
	if (validatePrime(p) && validatePrime(q)) {
		int n = p * q;
		int phiN = (p - 1) * (q - 1);
		int e = 0;
		for (int i = 1; i < n; i++) {
			cout << "Enter your public key(e): ";
			cin >> e;
			if (validateE(e, phiN, n)) {
				cout << "\nValid public Key: " << e << endl;
				int d = findD(e, phiN);
				//cout << "private key D: " << d << endl;
				string filename = "plain-text.txt";
				string plainText = readPlainText(filename);
				cout << "Plain: " << plainText << endl;
				string cipherText = encryptData(plainText,e,n);
				cout << "Cipher: " << cipherText << endl;
				string decreyptedText = decryptText(cipherText, d, n);
				cout << "DecreyptedText: " << decreyptedText << endl;
				break;
			}
			else {
				cout << "\nInvalid public Key(e)\nConditions:-\n(i): 1 < " << e << " > " << phiN << "" << "\n(ii): " << "GCD is: " << findGCD(e, phiN) << " should be 1" << endl;
			}
		}
	}
	else {
		cout << "NOT PRIME";
		return 0;
	}

}