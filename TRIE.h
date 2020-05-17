#pragma once
#include<iostream>
#include<string>
#include<fstream>
#define nOfAlphabets 26
using namespace std;

template <typename T>
class Vector {
	T* str;
	int size;
public:
	Vector()
	{
		str = new T[0];
		size = 0;
	}
	void resize(int siz)
	{
		int i;
		T* temp = new T[size];
		for (i = 0; i < size; i++) {
			temp[i] = str[i];
		}
		delete[] str;
		size = siz;
		str = new T[size];
		for (int i = 0; i < size - 1; i++) {
			str[i] = temp[i];
		}
		delete[] temp;
	}
	int Size()
	{
		return size;
	}
	T& operator[](int index)
	{
		if (index >= 0 && index < this->Size())
			return str[index];
	}
	Vector<T>& operator = (const Vector<T>& v) {
		if (this == &v)
			return *this;
		delete[] str;
		size = v.size;
		str = new T[size];
		for (int i = 0; i < size; i++)
			str[i] = v.str[i];
		return *this;
	}
	bool find(string wordd)
	{
		for (int i = 0; i < size; i++)
		{
			if (str[i] == wordd)
			{
				return 0;
			}
		}
		return -1;
	}

	void display()
	{
		for (int i = 0; i < size; i++) {
			cout << str[i] << endl;
		}
	}
};

class trieNode {
public:
	char data;			                //character at any particular Node
	bool isLeaf;
	Vector<string> synonyms;		//array of synonyms;
	string meaning;					//meaning of word
	trieNode* child[nOfAlphabets];
};

class TRIE {
	trieNode* root;
public:
	TRIE(void)
	{
		root = new trieNode;
		root->data = '\0';
		root->isLeaf = false;
		root->meaning = "";
		for (int i = 0; i < nOfAlphabets; i++) {
			root->child[i] = NULL;
		}
	}
	~TRIE(void)
	{

	}
	bool isEmpty()
	{
		bool flag = true;
		for (int i = 0; i < nOfAlphabets; i++) {
			if (root->child[i]) {
				flag = false;
				break;
			}
		}
		return flag;
	}
	string getWord(string w) {
		string tempWord;
		for (int i = 0; i < w.length(); i++) {
			if (w[i] != '-')
				tempWord += w[i];
		}
		return tempWord;
	}
	void TrieWords(trieNode* current, string word, string* s, int& idx)
	{
		if (current->isLeaf) {
			word += current->data;
			s[idx] = word;
			idx += 1;
			for (int i = 0; i < nOfAlphabets; i++) {
				if (current->child[i]) {
					TrieWords(current->child[i], word, s, idx);
				}
			}
			return;
		}
		word += current->data;
		for (int i = 0; i < nOfAlphabets; i++) {
			if (current->child[i]) {
				TrieWords(current->child[i], word, s, idx);
			}
		}
	}
	void getSynonyms(trieNode* current, string word, string* s, int& idx, const string key)
	{
		if (current->isLeaf) {
			word += current->data;
			if (key == word) {
				for (int i = 0; i < current->synonyms.Size(); i++) {
					s[idx] = current->synonyms[i];
					idx += 1;
				}
				return;
			}
			for (int i = 0; i < nOfAlphabets; i++) {
				if (current->child[i]) {
					getSynonyms(current->child[i], word, s, idx, key);
				}
			}
		}
		word += current->data;
		for (int i = 0; i < nOfAlphabets; i++) {
			if (current->child[i]) {
				getSynonyms(current->child[i], word, s, idx, key);
			}
		}
	}
	void getMeaning(trieNode* current, string word, string& s, const string key)
	{
		if (current->isLeaf) {
			word += current->data;
			if (key == word) {
				s = current->meaning;;
				return;
			}
			for (int i = 0; i < nOfAlphabets; i++) {
				if (current->child[i]) {
					getMeaning(current->child[i], word, s, key);
				}
			}
			return;
		}
		word += current->data;
		for (int i = 0; i < nOfAlphabets; i++) {
			if (current->child[i]) {
				getMeaning(current->child[i], word, s, key);
			}
		}
	}
	void findPrefix(trieNode* current, string word, string* s, int& idx, const string prefix)
	{
		if (current->isLeaf) {
			bool flag = true;
			word += current->data;
			for (int i = 0; i < prefix.length(); i++) {
				if (word[i] != prefix[i])
					flag = false;
			}
			if (flag) {
				s[idx] = word;
				idx += 1;
			}
			for (int i = 0; i < nOfAlphabets; i++) {
				if (current->child[i]) {
					findPrefix(current->child[i], word, s, idx, prefix);
				}
			}
			return;
		}
		word += current->data;
		for (int i = 0; i < nOfAlphabets; i++) {
			if (current->child[i]) {
				findPrefix(current->child[i], word, s, idx, prefix);
			}
		}
	}
	void getWordsOfLen(trieNode* current, string word, string* s, int& idx, const int len, int chk)
	{
		if (current->isLeaf) {
			word += current->data;
			if (chk == 1) {
				if (word.length() < len) {
					s[idx] = word;
					idx += 1;
				}
			}
			if (chk == 2) {
				if (word.length() <= len) {
					s[idx] = word;
					idx += 1;
				}
			}
			if (chk == 3) {
				if (word.length() > len) {
					s[idx] = word;
					idx += 1;
				}
			}
			for (int i = 0; i < nOfAlphabets; i++) {
				if (current->child[i]) {
					getWordsOfLen(current->child[i], word, s, idx, len, chk);
				}
			}
			return;
		}
		word += current->data;
		for (int i = 0; i < nOfAlphabets; i++) {
			if (current->child[i]) {
				getWordsOfLen(current->child[i], word, s, idx, len, chk);
			}
		}
	}
	void OutputAnagrams(trieNode* current, string word, string* s, int& idx, const string key)
	{
		if (current->isLeaf) {
			bool  found = false;
			bool notfound = false;
			word += current->data;
			if (word.length() == key.length() && word.compare(key) != 0) {
				for (int i = 0; i < word.length(); i++) {
					found = false;
					for (int j = 0; j < key.length(); j++) {
						if (word[i] == key[j]) {
							found = true;
							break;
						}
					}
					if (found == false) {
						notfound = true;
						break;
					}
				}
				if (notfound == false) {
					s[idx] = word;
					idx += 1;
				}
			}
			for (int i = 0; i < nOfAlphabets; i++) {
				if (current->child[i]) {
					OutputAnagrams(current->child[i], word, s, idx, key);
				}
			}
			return;
		}
		word += current->data;
		for (int i = 0; i < nOfAlphabets; i++) {
			if (current->child[i]) {
				OutputAnagrams(current->child[i], word, s, idx, key);
			}
		}
	}
	void FindSuffix(trieNode* current, string word, string* s, int& idx, const string key)
	{
		if (current->isLeaf) {
			bool flag = true;
			word += current->data;
			for (int i = word.length() - 1, j = key.length() - 1; j >= 0; i--, j--) {
				if (word[i] != key[j])
					flag = false;
			}
			if (flag) {
				s[idx] = word;
				idx += 1;
			}
			for (int i = 0; i < nOfAlphabets; i++) {
				if (current->child[i]) {
					FindSuffix(current->child[i], word, s, idx, key);
				}
			}
			return;
		}
		word += current->data;
		for (int i = 0; i < nOfAlphabets; i++) {
			if (current->child[i]) {
				FindSuffix(current->child[i], word, s, idx, key);
			}
		}
	}
	void CreateDictionary(const char* Path)
	{
		trieNode* current;
		ifstream file(Path);
		if (file.is_open())
		{

			string line;
			getline(file, line, '\n');
			while (!file.eof())
			{
				current = root;
				string word = getWord(line);
				for (int j = 0; j < word.length(); j++)
				{	//input of word in different nodes
					if (word[j] >= 65 && word[j] <= 90)
						word[j] += 32;
					int index = word[j] - 'a';
					char temp = word[j];
					if (!current->child[index]) {
						current->child[index] = new trieNode;
						current->child[index]->data = temp;
						current->child[index]->isLeaf = false;
						for (int k = 0; k < nOfAlphabets; k++) {
							current->child[index]->child[k] = NULL;
						}
					}
					current = current->child[index];
				}
				current->isLeaf = true;          //it's leaf boolean will be because it's last node;
				getline(file, line, '\n');
				word = getWord(line);
				current->meaning = word;         //meaning at it's leaf
				int size = 0;
				int k = 0;
				while (getline(file, line, '\n'))
				{   //assigning synonyms
					word = getWord(line);
					if (line[0] == '-')
						break;
					else
					{
						current->synonyms.resize(size += 1);
						current->synonyms[k] = word;
						k++;
					}
				}
			}
		}
		file.close();
	}
	Vector<string> OutputAscending()
	{
		Vector<string>order;
		int size = 0;
		if (!isEmpty()) {
			string* str = new string[100];
			for (int i = 0; i < 100; i++)
				str[i] = "";
			string word = "";
			int strIdx = 0;
			trieNode* current = root;
			for (int i = 0; i < nOfAlphabets; i++) {
				if (current->child[i]) {
					TrieWords(current->child[i], word, str, strIdx);
				}
			}
			for (int i = 0; str[i] != "\0"; i++) {
				order.resize(size += 1);
				order[i] = str[i];
			}
		}
		else
			cout << "TRIE IS EMPTY\n";
		return order;
	}
	Vector<string> OutputDescending()
	{
		Vector<string>order;
		int size = 0;
		if (!isEmpty()) {
			string* str = new string[100];
			for (int i = 0; i < 100; i++)
				str[i] = "";
			string word = "";
			int strIdx = 0;
			trieNode* current = root;
			for (int i = 0; i < nOfAlphabets; i++) {
				if (current->child[i]) {
					TrieWords(current->child[i], word, str, strIdx);
				}
			}
			for (int i = strIdx - 1, j = 0; i >= 0; i--, j++) {
				order.resize(size += 1);
				order[j] = str[i];
			}
		}
		else
			cout << "TRIE IS EMPTY\n";
		return order;
	}
	bool FindWord(const string key)
	{
		if (isEmpty())
			return 0;
		bool flag = false;
		string* str = new string[100];
		for (int i = 0; i < 100; i++)
			str[i] = "";
		string word = "";
		int strIdx = 0;
		trieNode* current = root;
		for (int i = 0; i < nOfAlphabets; i++) {
			if (current->child[i]) {
				TrieWords(current->child[i], word, str, strIdx);
			}
		}
		for (int i = 0; str[i] != "\0"; i++) {
			if (str[i] == key)
				flag = true;
		}
		return flag;
	}
	Vector<string>FindSynonyms(const string key)
	{
		Vector<string>synonym;
		int size = 0;
		if (!isEmpty()) {
			string* str = new string[100];
			for (int i = 0; i < 100; i++)
				str[i] = "";
			string word = "";
			int strIdx = 0;
			if (!FindWord(key))
				return synonym;
			trieNode* current = root;
			for (int i = 0; i < nOfAlphabets; i++) {
				if (current->child[i]) {
					getSynonyms(current->child[i], word, str, strIdx, key);
				}
			}
			for (int i = 0; str[i] != "\0"; i++) {
				synonym.resize(size += 1);
				synonym[i] = str[i];
			}
		}
		else
			cout << "TRIE IS EMPTY\n";
		return synonym;
	}
	string FindMeaning(const string key)
	{
		string str = "";
		if (!isEmpty()) {
			string word = "";
			int strIdx = 0;
			if (!FindWord(key))
				return str;
			trieNode* current = root;
			for (int i = 0; i < nOfAlphabets; i++) {
				if (current->child[i]) {
					getMeaning(current->child[i], word, str, key);
				}
			}
		}
		else
			cout << "TRIE IS EMPTY\n";
		return str;
	}
	Vector<string> OutputPrefix(const string prefix)
	{
		Vector<string>strPrefix;
		int size = 0;
		if (!isEmpty()) {
			string* str = new string[100];
			for (int i = 0; i < 100; i++)
				str[i] = "";
			string word = "";
			int strIdx = 0;
			trieNode* current = root;
			for (int i = 0; i < nOfAlphabets; i++) {
				if (current->child[i] && current->child[i]->data == prefix[0]) {
					findPrefix(current->child[i], word, str, strIdx, prefix);
				}
			}
			for (int i = 0; str[i] != "\0"; i++) {
				strPrefix.resize(size += 1);
				strPrefix[i] = str[i];
			}
		}
		else
			cout << "TRIE IS EMPTY\n";
		return strPrefix;
	}
	Vector<string> OutputSmaller(const int length)
	{
		Vector<string>output;
		int size = 0;
		int smaller = 1;
		if (!isEmpty()) {
			string* str = new string[100];
			for (int i = 0; i < 100; i++)
				str[i] = "";
			string word = "";
			int strIdx = 0;
			trieNode* current = root;
			for (int i = 0; i < nOfAlphabets; i++) {
				if (current->child[i]) {
					getWordsOfLen(current->child[i], word, str, strIdx, length, smaller);
				}
			}
			for (int i = 0; str[i] != "\0"; i++) {
				output.resize(size += 1);
				output[i] = str[i];
			}
		}
		else
			cout << "TRIE IS EMPTY\n";
		return output;
	}
	Vector<string> OutputSE(const int length)
	{
		Vector<string>output;
		int size = 0;
		int equal = 2;
		if (!isEmpty()) {
			string* str = new string[100];
			for (int i = 0; i < 100; i++)
				str[i] = "";
			string word = "";
			int strIdx = 0;
			trieNode* current = root;
			for (int i = 0; i < nOfAlphabets; i++) {
				if (current->child[i]) {
					getWordsOfLen(current->child[i], word, str, strIdx, length, equal);
				}
			}
			for (int i = 0; str[i] != "\0"; i++) {
				output.resize(size += 1);
				output[i] = str[i];
			}
		}
		else
			cout << "TRIE IS EMPTY\n";
		return output;
	}
	Vector<string> OutputGreater(const int length)
	{
		Vector<string>output;
		int size = 0;
		int greater = 3;
		if (!isEmpty()) {
			string* str = new string[100];
			for (int i = 0; i < 100; i++)
				str[i] = "";
			string word = "";
			int strIdx = 0;
			trieNode* current = root;
			for (int i = 0; i < nOfAlphabets; i++) {
				if (current->child[i]) {
					getWordsOfLen(current->child[i], word, str, strIdx, length, greater);
				}
			}
			for (int i = 0; str[i] != "\0"; i++) {
				output.resize(size += 1);
				output[i] = str[i];
			}
		}
		else
			cout << "TRIE IS EMPTY\n";
		return output;
	}
	Vector<string> OutputAnagrams(const string key)
	{
		Vector<string>anagram;
		int size = 0;
		if (!isEmpty()) {
			string* str = new string[100];
			for (int i = 0; i < 100; i++)
				str[i] = "";
			string word = "";
			int strIdx = 0;
			trieNode* current = root;
			for (int i = 0; i < nOfAlphabets; i++) {
				if (current->child[i]) {
					OutputAnagrams(current->child[i], word, str, strIdx, key);
				}
			}
			for (int i = 0; str[i] != "\0"; i++) {
				anagram.resize(size += 1);
				anagram[i] = str[i];
			}
		}
		else
			cout << "TRIE IS EMPTY\n";
		return anagram;
	}
	Vector<string> CompleteString(string wordd)
	{
		Vector<string> v;
		return v;
	}
	Vector<string> SpellChecker(string wordd)
	{
		Vector<string> v;
		return v;
	}
	Vector<string> OutputSuffix(const string suffix)
	{
		Vector<string>Suffix;
		int size = 0;
		if (!isEmpty()) {
			string* str = new string[100];
			for (int i = 0; i < 100; i++)
				str[i] = "";
			string word = "";
			int strIdx = 0;
			trieNode* current = root;
			for (int i = 0; i < nOfAlphabets; i++) {
				if (current->child[i]) {
					FindSuffix(current->child[i], word, str, strIdx, suffix);
				}
			}
			for (int i = 0; str[i] != "\0"; i++) {
				Suffix.resize(size += 1);
				Suffix[i] = str[i];
			}
		}
		else
			cout << "TRIE IS EMPTY\n";
		return Suffix;
	}
};
