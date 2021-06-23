#include<bits/stdc++.h> 
using namespace std; 


#define ALPHABET_SIZE (26) 

 
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') 

 
struct TrieNode 
{ 
	struct TrieNode *children[ALPHABET_SIZE]; 

	 
	bool isWordEnd; 
}; 

// Returns new trie node (initialized to NULLs) 
struct TrieNode *getNode(void) 
{ 
	struct TrieNode *pNode = new TrieNode; 
	pNode->isWordEnd = false; 

	for (int i = 0; i < ALPHABET_SIZE; i++) 
		pNode->children[i] = NULL; 

	return pNode; 
} 

 
void insert(struct TrieNode *root, const string key) 
{ 
	struct TrieNode *pCrawl = root; 

	for (int level = 0; level < key.length(); level++) 
	{ 
		int index = CHAR_TO_INDEX(key[level]); 
		if (!pCrawl->children[index]) 
			pCrawl->children[index] = getNode(); 

		pCrawl = pCrawl->children[index]; 
	} 

	// mark last node as leaf 
	pCrawl->isWordEnd = true; 
} 

// Returns true if key presents in trie, else false 
bool search(struct TrieNode *root, const string key) 
{ 
	int length = key.length(); 
	struct TrieNode *pCrawl = root; 
	for (int level = 0; level < length; level++) 
	{ 
		int index = CHAR_TO_INDEX(key[level]); 

		if (!pCrawl->children[index]) 
			return false; 

		pCrawl = pCrawl->children[index]; 
	} 

	return (pCrawl != NULL && pCrawl->isWordEnd); 
} 


bool isLastNode(struct TrieNode* root) 
{ 
	for (int i = 0; i < ALPHABET_SIZE; i++) 
		if (root->children[i]) 
			return 0; 
	return 1; 
} 


void suggestionsRec(struct TrieNode* root, string currPrefix) 
{ 
	// found a string in Trie with the given prefix 
	if (root->isWordEnd) 
	{ 
		cout << currPrefix; 
		cout << endl; 
	} 

	// All children struct node pointers are NULL 
	if (isLastNode(root)) 
		return; 

	for (int i = 0; i < ALPHABET_SIZE; i++) 
	{ 
		if (root->children[i]) 
		{ 
			// append current character to currPrefix string 
			currPrefix.push_back(97 + i); 

			// recur over the rest 
			suggestionsRec(root->children[i], currPrefix); 
		} 
	} 
} 

// print suggestions for given query prefix. 
int printAutoSuggestions(TrieNode* root, const string query) 
{ 
	struct TrieNode* pCrawl = root; 
     int level; 
	int n = query.length(); 
	for (level = 0; level < n; level++) 
	{ 
		int index = CHAR_TO_INDEX(query[level]); 

		// no string in the Trie has this prefix 
		if (!pCrawl->children[index]) 
			return 0; 

		pCrawl = pCrawl->children[index]; 
	} 

	// If prefix is present as a word. 
	bool isWord = (pCrawl->isWordEnd == true); 

	// If prefix is last node of tree (has no 
	// children) 
	bool isLast = isLastNode(pCrawl); 

	// If prefix is present as a word, but 
	// there is no subtree below the last 
	// matching node. 
	if (isWord && isLast) 
	{ 
		cout << query << endl; 
		return -1; 
	} 

	// If there are are nodes below last 
	// matching character. 
	if (!isLast) 
	{ 
		string prefix = query; 
		suggestionsRec(pCrawl, prefix); 
		return 1; 
	} 
} 

// Driver Code 
int main() 
{ 

fstream file;
	string word, t, q, filename;

	// filename of the file
	filename = "list.txt";

	// opening file
	file.open(filename.c_str());
	
     
     struct TrieNode* root = getNode();
	 cout<<"Enter the word you want to search"<<endl;
	 string s;
	 cin>>s;
	 cout<<endl;
	
// 	// extracting words from the file
	while (file >> word)
	{
      if(s[0]<word[0]){
		  break;
	  }
     if(s[0]==word[0]){
	 insert(root, word);
	 }


	}
        if(search(root,s)){
			cout<<s<<endl;
		}else{
			
	 int comp = printAutoSuggestions(root, s); 

	if (comp == -1) 
		cout << "No other strings found with this prefix\n"; 

	else if (comp == 0) 
		cout << "No string found with this prefix\n"; 
	
		else{
			cout<<endl<<"are some similar words"<<endl;
		}
	}
	return 0; 
} 
