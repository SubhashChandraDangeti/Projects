#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Node{
    Node *links[26];
    bool flag=false;
    bool containsChar(char ch){
        return (links[ch-'a']!=NULL);
    }
    void put(char ch,Node* node){ //creates new ref node
        links[ch-'a']=node; //now ch pts to node
    }
    Node* get(char ch){
        return links[ch-'a'];
    }
    void setEnd(){
        flag=true;
    }
    bool isEnd(){
        return flag;
    }
};
class Trie{
    //every trie will have root
    private: Node* root;
    public :
        Trie(){
            root= new Node();
        }
        //inserting all words given n q //n strings to be inserted 
        void insert(string word){
            //start from root
            Node* node =root;
            for(int i=0;i<word.length();i++){
                //if curr node doesnt contain char,create it and create reference trie for it
                if(!node->containsChar(word[i])){
                    node->put(word[i], new Node());
                }
                //go to next reference trie
                node=node->get(word[i]);
            }
            //once insertion of word ends,we will be at last ref trie
            node->setEnd();
        }

        //Task-1 searching for the given word (1 string)
        bool search(string word){
            Node *node = root;
            for(int i=0;i<word.length();i++){
                if(!node->containsChar(word[i])) return 0;
                node=node->get(word[i]);//move to its reference trie
            }
            return (node->isEnd())?1:0;
        }

        //Task-2 searching all words starting with prefix
        Node* startsWith(string prefix){
            Node *node=root;
            for(int i=0;i<prefix.length();i++){
                char ch=prefix[i];
                if(!node->containsChar(prefix[i])){
                    return NULL;
                }
                node=node->get(ch);
            }
            return node;//node at end of prefix ,now we can do dfs to find all strings
        }
        void dfs(Node* node,string prefix,vector<string> &result){
            if(node->isEnd()){
                result.push_back(prefix);
            }
            for (int i=0; i<26; i++) {
                if (node->links[i] != NULL) {
                    char nextChar = 'a' + i;
                    dfs(node->links[i], prefix + nextChar, result);
                }
            }
        }
        //using dfs from root node to take all words in dict and compare with mis-spelt word using edit dist
        void autocorrect(Node* node,string prefix,vector<string> &result,string query){
            if(node->isEnd()){
                if(editDistance(prefix,query)<=3){result.push_back(prefix);}
            }
            for (int i=0; i<26; i++) {
                if (node->links[i] != NULL) {
                    char nextChar = 'a' + i;
                    autocorrect(node->links[i], prefix + nextChar, result,query);
                }
            }
        }
        int editDistance(const string& a, const string& b) {
            int m = a.size(), n = b.size();
            vector<vector<int>> dp(m+1, vector<int>(n+1));

            
            for(int i=0;i<=m;i++) dp[i][0] = i;
            for(int j=0;j<=n;j++) dp[0][j] = j;

            
            for(int i=1;i<=m;i++){
                for(int j=1;j<=n;j++){
                    if(a[i-1] == b[j-1])
                        dp[i][j] = dp[i-1][j-1]; // match
                    else
                        dp[i][j] = min({ dp[i-1][j-1]+1, // replace
                                        dp[i-1][j]+1,   // delete
                                        dp[i][j-1]+1 }); // insert
                }
            }
            return dp[m][n];
        }

        void autocomplete(string prefix) {
            Node* node = startsWith(prefix);
            if (node == NULL) {
                cout << 0 << endl;//no words with given prefix
                return;
            }
            vector<string> result;
            dfs(node, prefix, result);

            cout << result.size() << endl;
            for (string w : result) {
                cout << w << endl;
            }
        }

};
int main(){
    int n,q;
    // cout<<"Enter the no. of words u want to insert and No.of queries u want to process"<<endl;
    cin>>n>>q;
    string word;
    Trie dictionary;
    for(int i=0;i<n;i++){
        cin>>word;
        dictionary.insert(word); //inserting all n words one by one into trie
    }
    vector<pair<int,string>> vec;
    while(q--){
        int ai;
        string ti;
        cin>>ai>>ti; 
        vec.push_back({ai,ti});
    }
    int i=0;
    for(int i=0;i<vec.size();i++){
        switch (vec[i].first)
        {
            case 1:
                cout<<dictionary.search(vec[i].second)<<endl;
                break;
            case 2:
                dictionary.autocomplete(vec[i].second);
                break;
            case 3: {
                vector<string> result;
                dictionary.autocorrect(dictionary.startsWith(""), "", result, vec[i].second);
                sort(result.begin(), result.end());
                cout << result.size() << endl;
                for (string w : result) {
                    cout << w << endl;
                }
                break;
            }
            default:
                // cout<<"Please check the input correctly!"<<endl;
                break;
        }
    }
}