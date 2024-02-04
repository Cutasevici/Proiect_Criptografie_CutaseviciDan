#include <iostream>

using namespace std;


class Node {
public:
	string planeText;
	string key;
	Node* next;
	bool encrypted;
	Node(string planeText, string key) {
		this->planeText = planeText;
		this->key = key;
		next = nullptr;
	}

};

class LinkedList {
private:
	Node* head;
	Node* tail;
	int length;
public:
	LinkedList() {
		head = nullptr;
		tail = nullptr;
		length = 0;
	}
	~LinkedList() {
		Node* current = head;
		while (current != nullptr) {
			Node* next = current->next;
			delete current;
			current = next;
		}
	}

	void insertNode(const string& planeText, const string& key) {
		Node* newNode = new Node(planeText, key);
		if (head == nullptr) {
			head = tail = newNode; 
		}
		else {
			tail->next = newNode; 
			tail = newNode; 
		}
		length++;
	}


	void display() {
		Node* current = head;
		int index = 0; // Start the index at 0
		while (current != nullptr) {
			cout << "Index: " << index << " - PlainText: " << current->planeText
				<< ", Key: " << current->key << endl;
			current = current->next;
			index++; 
		}
	}

	void applyXOR(int index) {
		// Check if index is within bounds and find the node
		if (index < 0 || index >= length) {
			cout << "Index out of bounds" << endl;
			return;
		}
		Node* current = head;
		for (int i = 0; i < index && current != nullptr; ++i) {
			current = current->next;
		}
		if (current != nullptr) {
			current->planeText = encryptXOR(current->planeText, current->key);
			current->encrypted = true; // Mark as encrypted
		}
	}



	void decryptXOR(int index) {
		if (index < 0 || index >= length) {
			cout << "Index out of bounds" << endl;
			return;
		}
		Node* current = head;
		for (int i = 0; i < index && current != nullptr; ++i) {
			current = current->next;
		}
		if (current != nullptr) {
			if (!current->encrypted) {
				cout << "Node at index " << index << " is not encrypted or already decrypted." << endl;
				return;
			}
			// Perform decryption, assuming the same key is used and the encryption method is reversible
			current->planeText = encryptXOR(current->planeText, current->key); // XOR is its own inverse
			current->encrypted = false; // Mark as decrypted
		}
	}







	
	void vigenereEncryptNode(int index) {
		if (index < 0 || index >= length) {
			cout << "Index out of bounds" << endl;
			return;
		}
		Node* current = head;
		for (int i = 0; i < index && current != nullptr; ++i) {
			current = current->next;
		}
		if (current != nullptr) {
			current->planeText = encryptVigenere(current->planeText, current->key);
			current->encrypted = true;
		}
	}
	void decryptVigenere(int index) {
		if (index < 0 || index >= length) {
			cout << "Index out of bounds" << endl;
			return;
		}
		Node* current = head;
		for (int i = 0; i < index && current != nullptr; ++i) {
			current = current->next;
		}
		if (current != nullptr) {
			if (!current->encrypted) {
				cout << "Node at index " << index << " is not encrypted or already decrypted." << endl;
				return;
			}
			// Perform Vigenere decryption
			current->planeText = decryptVigenere(current->planeText, current->key);
			current->encrypted = false; // Mark as decrypted
		}
	}


	



private:
	string encryptXOR(const string& planeText, const string& key) {
		string encryptedText = "";
		for (size_t i = 0; i < planeText.length(); ++i) {
			// Use the key characters in a cyclic manner to match the length of plainText
			char keyChar = key[i % key.length()];
			encryptedText += planeText[i] ^ keyChar;
		}
		return encryptedText;
	}
	string encryptVigenere(const string& planeText, const string& key) {
		string encryptedText = "";
		for (size_t i = 0; i < planeText.length(); ++i) {
			char keyChar = key[i % key.length()];
			// Vigenere encryption: Add (modulo 26) the keyChar to the plainText character
			char encryptedChar = ((planeText[i] - 'A' + keyChar - 'A') % 26) + 'A';
			encryptedText += encryptedChar;
		}
		return encryptedText;
	}
	string decryptVigenere(const string& encryptedText, const string& key) {
		string decryptedText = "";
		for (size_t i = 0, j = 0; i < encryptedText.length(); ++i) {
			char c = encryptedText[i];
			if (c >= 'A' && c <= 'Z') {
				// Convert to uppercase if necessary: c = toupper(c); // If supporting lowercase
				char decryptedChar = (c - key[j] + 26) % 26 + 'A';
				decryptedText += decryptedChar;
				j = (j + 1) % key.length();
			}
			else {
				// Directly append non-alphabetical characters
				decryptedText += c;
			}
		}
		return decryptedText;
	}

	
};


int main() {
	LinkedList list;
	list.insertNode("hello", "keyone");
	list.insertNode("myName", "keytwo");
	list.insertNode("myNameDan", "keythre");
	list.insertNode("myNameCuta", "keyfor");
	list.display();
	cout << endl;
	// Apply Vigenere encryption to node at index 2
	

	// Apply XOR encryption to node at index 3
	
	list.vigenereEncryptNode(2);
	list.applyXOR(2);
	list.display();
	cout << endl;
	list.decryptXOR(2);
	list.display();
	cout << endl;
	list.decryptVigenere(2);
	list.display();
	

	// Decrypt the XOR-encrypted node at index 3
	
	

		
		return 0;
}