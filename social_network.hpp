#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <string>
#include <algorithm> //for sort()
using namespace std;

//========== AVL TREE ==================//
struct Node {
    int timeStamp;
    string content;
    Node* left;
    Node* right;
    int height;
    Node(int t,string c) {
        this->timeStamp = t;
        this->content = c;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
    }
};

class AvlTree {
private:
    Node* root;
    int height(Node* node){
        return node ? node->height : 0; 
    }
    int balanceFactor(Node* node){
        return node ? height(node->left)-height(node->right) : 0; 
    }
    Node* leftRotate(Node* x){
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = 1+ max(height(x->left),height(x->right));
        y->height = 1+ max(height(y->left),height(y->right));
        return y;
    }
    Node* rightRotate(Node* y){
        Node* x = y->left;
        Node* T1 = x->right;
        x->right = y;
        y->left = T1;
        y->height = 1+ max(height(y->left),height(y->right));
        x->height = 1+ max(height(x->left),height(x->right));
        return x;
    }
    Node* insertNode(Node* node,int t,string c){
        //if AVL tree is empty
        if(!node) return new Node(t,c);
        
        //traverse to appropriate position
        if(t<node->timeStamp) node->left  = insertNode(node->left,t,c);
        else node->right = insertNode(node->right,t,c);

        node->height = 1+max(height(node->left),height(node->right));
        int bal = balanceFactor(node);

        //Rotations
        //LL
        if(bal > 1 && t < node->left->timeStamp) return rightRotate(node); 
        //RR
        if(bal<-1 && t > node->right->timeStamp) return leftRotate(node);
        //LR
        if(bal>1 && t > node->left->timeStamp) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        //RL
        if(bal<-1 && t < node->right->timeStamp) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }
    void reverseInorder(Node* node,vector<string>& posts,int& count,int N){
        if(!node || (N != -1 && count >= N)) return;
        
        //go right 
        reverseInorder(node->right,posts,count,N);
        //node
        if(N == -1 || count < N) {
            posts.push_back(node->content);
            count++;
        }
        //left
        reverseInorder(node->left,posts,count,N);
    }
public:
    AvlTree(){
        root = nullptr;
    }
    void insert(int t,string c){
        root = insertNode(root,t,c);
    }
    vector<string> getRecentPosts(int N){
        vector<string> recPosts;
        int count = 0;
        reverseInorder(root,recPosts,count,N);
        return recPosts;
    }

};


//========== SOCIAL NETWORK ==================//
class SocialNetwork {
private:
    unordered_map<string,vector<string>> adj;
    unordered_map<string,AvlTree*> posts;
    int globalTimestamp;
    static string normalize(string s){
        for (int i = 0; i <(int) s.size(); i++) {
            if (s[i] >= 'A' && s[i] <= 'Z')
                s[i] = s[i] - 'A' + 'a';
        }
        return s;
    }
public:
    SocialNetwork( ){
        globalTimestamp = 0;
    }
    void adduser(string u){
        // Convert username to lowercase to make the check case-insensitive.
        u = normalize(u);

        // Check if the user exists.
        if(!adj.count(u)){
            adj[u] = {};
            posts[u] = new AvlTree();
            cout << "User '" << u << "' added successfully." << endl;
            return;
        }
        cout << "User '" << u << "' already added." << endl;
    }
    void addFriend(string u,string v){
        // Convert username to lowercase for case-insensitive handling
        u  = normalize(u);
        v = normalize(v);

        // check if both users exist
        if(!adj.count(u)  ){
            cout << "User '" << u << "' does not exist added." << endl;
            return;
        }   
        if(  !adj.count(v)){
            cout << "User '" << v << "' does not exist added." << endl;
            return;
        }   

        // check for self friendship
        if(u == v){
            cout << "Can not add self as friend\n";
            return;
        }

        // check if they are already friends
        auto &friendsOfU = adj[u];
        if (find(friendsOfU.begin(), friendsOfU.end(), v) != friendsOfU.end()) {
            cout << "'" << u << "' and '" << v << "' are already friends.\n";
            return;
        }
        
        // otherwise add the friendship (bidirectional)
        adj[u].push_back(v);
        adj[v].push_back(u);
        cout << "'"<< u <<"' and '" << v << "' are added as friends" <<endl;
    }
    void listFriends(string u){
        // Convert username to lowercase for case-insensitive handling
        u = normalize(u);

        // check if  user exist
        if(!adj.count(u)){
            cout << "User '" << u << "' does not exist." << endl;
            return;
        }
        // Get the list of friends for this user
        vector<string> friends = adj[u];

        // Sort friends alphabetically before displaying
        sort(friends.begin(), friends.end());

        // Print the header line
        cout << "Friends of '" << u << "' :" << endl;

        // Print each friend name separated by space
        for (auto& f : friends) {
            cout << f << " ";
        }
        cout << "\n";
    }
    void addPost(string u,string content){
        // Convert username and content to lowercase for case-insensitive handling
        u = normalize(u);
        content = normalize(content);

        // Check if the user exists in the social network.
        if(!posts.count(u)){
            cout << "User '" << u << "' does not exist added." << endl;
            return;
        }
        // Insert the new post into the user's AVL tree.
        // globalTimestamp is incremented to maintain unique ordering
        // based on time of post creation.
        posts[u]->insert(++globalTimestamp,content);
        cout << "Post added successfully\n";
    }
    void outputPosts(string u,int N){
        // Convert  username to lowercase to ensure case-insensitive behavior.
        u = normalize(u);

        // Check if the user exists in the social network.
        if(!adj.count(u)){
            cout << "User '" << u << "' does not exist added." << endl;      
            return;
        }
        // Retrieve the N most recent posts using the user's AVL tree.
        // If N == -1, all posts will be returned.          
        vector<string> recPosts = posts[u]->getRecentPosts(N);

        cout << "Recent Posts of User '" << u << "'  :-\n";
        for(auto& p : recPosts) {
            cout << p << "\n";
        }
    }
    int degreeOfSeperation(string u,string v){
        // Convert both username to lowercase for case-insensitive handling 
        u  = normalize(u);
        v = normalize(v);
        
        // check if both users exist
        if(!adj.count(u)){
            cout << "User '" << u << "' does not exist added." << endl;      
            return -1;
        }
        if(!adj.count(v)){
            cout << "User '" << v << "' does not exist added." << endl;      
            return -1;
        }
        
        // If both usernames are the same, degree of separation is zero.
        if( u == v) return 0;

        // 'visited' keeps track of already explored users to prevent cycles.
        unordered_set<string> visited;

        // Queue stores (username, distance) pairs for BFS traversal.
        queue<pair<string,int>> q;

        // Start BFS from user 'u' at distance 0.
        q.push({u,0});
        visited.insert(u);

        //bfs
        while(!q.empty()) {
            string cur = q.front().first;
            int dist = q.front().second;
            q.pop();

            // Traverse all friends (neighbors) of the current user.
            for(auto& n : adj[cur]) {
                // If we find the target user, return current distance + 1.
                if( n == v) 
                    return dist+1;
                
                // If this friend hasn't been visited, add to queue for exploration.
                if(!visited.count(n)){
                    visited.insert(n);
                    q.push({n,dist+1});
                }
            }
        }
        // If BFS finishes without finding 'v', no connection exists between them.
        return -1;
    }
    void suggestFriends(string u,int N){
        // Convert username to lowercase to make the check case-insensitive.
        u = normalize(u);

        // Check if the user exists.
        if(!adj.count(u) ){
            cout << "User '" << u << "' doesnot exist." << endl;
            return;
        } 
        // If N is 0, no suggestions should be shown.
        if(N == 0){
            cout << endl;
            return;
        }
        // Store all users that are already connected to 'u' (including u itself).
        // This helps us skip them later when finding new friend suggestions
        unordered_set<string> existing(adj[u].begin(),adj[u].end());
        existing.insert(u);

        // Map to store potential friends and how many mutual friends they share with 'u'.
        unordered_map<string,int> mutuals;

        // For every friend of 'u', look at their friends (friends-of-friends).
        for(auto& f : adj[u]){
            for(auto& fof : adj[f]){
                // For every friend of 'u', look at their friends (friends-of-friends).
                if(!existing.count(fof)) 
                    mutuals[fof]++; // Count how many mutual friends connect 'u' and 'fof'.
            }
        }

        // Move all candidates into a vector for sorting.
        vector<pair<string,int>> cand(mutuals.begin(),mutuals.end());

        // Sort by:
        // 1. Number of mutual friends (descending)
        // 2. Username (alphabetically ascending) for tie-breaking      
        sort(cand.begin(),cand.end(),[](auto& a,auto& b){
            if(a.second != b.second) return a.second > b.second;
            return a.first < b.first;
        });

        int c  = 0;
        if(cand.size() == 0){
            cout << "No suggested friends.\n";
        }
        for(auto& p : cand){
            if( c++ >= N) break;
            cout << p.first << " ( " << p.second << " mutuals )\n";
        }
    }
};

//=========== COMMAND PROCESSOR ==============//
class CommandProcessor {
private:
    SocialNetwork sn;
    
public:

    void processCommand(const string& command){
        vector<string> tokens = parseCommand(command);
        if (!tokens.empty()) {
            executeCommand(tokens);
        }
    }
    void run(){
        string line;
        cout << "****** SocialNet Simulator ******\n";
        cout << "Enter commands: " ;
        cout<< "(Type EXIT to quit.)\n";

        while (true) {
            cout << "> ";
            if (!getline(cin, line)) break;  // Exit on EOF or error
            if (line == "EXIT"||line=="exit"||line=="Exit") break;
            try {
                processCommand(line);
            } catch (const  exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    }
    
private:
    
    vector<string> parseCommand(const string& command) {
        vector<string> tokens;
        stringstream ss(command);
        string token;
        while (ss >> token) {
            if (!token.empty())
                tokens.push_back(token);
        }
        return tokens;
    }
    void executeCommand(const vector<string>& tokens){
        if (tokens.empty()) return;
        
        string cmd = tokens[0];
        transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
        
        if (cmd == "add_user") {
            if (tokens.size() < 2) {
                cout << "Usage: ADD_USER <user_name>" << endl;
                return;
            }
            string u = tokens[1];
            sn.adduser(u);
        }
        else if (cmd == "add_friend") {
            if (tokens.size() < 3) {
                cout << "Usage: ADD_FRIEND <user_name1> <user_name2>" << endl;
                return;
            }
            string u  = tokens[1],v = tokens[2]; 
            sn.addFriend(u,v);
        }
        else if (cmd == "list_friends" ) {
            if (tokens.size() < 2) {
                cout << "Usage: LIST_FRIENDS <user_name>" << endl;
                return;
            }
            
            string u = tokens[1];
            sn.listFriends(u);
        }
        else if (cmd == "suggest_friends") {
            if (tokens.size() < 3) {
                cout << "Usage: SUGGEST_FRIENDS <user_name> <N>" << endl;
                return;
            }
            string u  = tokens[1];
            int N = stoi(tokens[2]);
            sn.suggestFriends(u,N);
        }
        else if (cmd == "degrees_of_seperation") {
            if (tokens.size() < 3) {
                cout << "Usage: DEGREES_OF_SEPARATION <user_name1> <user_name2>" << endl;
                return;
            }
            string u = tokens[1],v = tokens[2];
            cout << sn.degreeOfSeperation(u,v) << endl;
        }
        else if (cmd == "add_post") {
            if (tokens.size() < 3) {
                cout << "Usage: ADD_POST <user_name>  <post content>" << endl;
                return;
            }
            string u  = tokens[1];
            string post_content = tokens[2];
            size_t f = post_content.find('"');
            size_t l = post_content.rfind('"');
            post_content = post_content.substr(f+1,l-f-1);
            for(size_t i = 3;i<tokens.size();i++){
                post_content += " " + tokens[i];
            }
            sn.addPost(u,post_content);   
        }
        else if (cmd == "output_posts") {
            if (tokens.size() < 3) {
                cout << "Usage: OUTPUT_POSTS <user_name> <N> " << endl;
                return;
            }
            string u  = tokens[1];
            int N = stoi(tokens[2]);
            sn.outputPosts(u,N);
        }
        else {
            cout << "Unknown command: " << cmd << endl;
            cout << "Available commands: \n";
            cout << " ADD_USER \n";
            cout << " ADD_FRIEND  \n";
            cout << " LIST_FRIENDS  \n";
            cout << " SUGGEST_FRIENDS  \n";
            cout << " DEGREES_OF_SEPARATION  \n";
            cout << " ADD_POST \n";
            cout << " OUTPUT_POSTS \n";
        }
    }
};
  
