/* this project is written by Mitra Omrani & Shaghayegh Shahbazi */
// this project is for restaurant administraition for following matarials 
/*
 1. store customer's data 
 2. store foods and their requirments 
 3. get service and find the shortes path to deliver the food
 4. find the shortest path among all the tables
 5. asign turns to each customer that enters & take their service by their priority 
 */
#include<bits/stdc++.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
using namespace std;
using ll=long long;
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m" 
#define BLUE    "\033[34m"
#define WHITE   "\033[37m"
#define CYAN    "\033[36m" 
#define MAGENTA "\033[35m"
#define YELLOW  "\033[33m" 
#define BOLDGREEN   "\033[1m\033[32m" 
#define BOLDYELLOW  "\033[1m\033[33m"
#define BOLDWHITE   "\033[1m\033[37m" 
#define BOLDBLUE    "\033[1m\033[34m"
#define BOLDRED     "\033[1m\033[31m" 
#define BOLDMAGENTA "\033[1m\033[35m"
#define BOLDCYAN    "\033[1m\033[36m"
vector<string> Rs_map;
pair<ll,ll>kitchen_plc;
int length=0;

struct customer{
    string name;
    string ordered_food;
    ll prepartion_time;
    ll eating_time;
};
void delivery_menu();
/* Delivery part functions */
// Tsp part  & dynamic part Dp[2^n][n]
ll distances[6][6],Dp[64][6],visited_all=(1<<6)-1;

    void print_path(ll i_fnd,ll j_fnd,map<pair<ll,ll>,pair<ll,ll>> path,ll initial_pos_i,ll initial_pos_j){
        ll i=i_fnd,j=j_fnd,prv;
        set<pair<ll,ll>> final_path;
        // starting from the end to raech the initail position 
        while(1){
            final_path.insert({i,j});
            prv=i;
            i=path[{i,j}].first;
            j=path[{prv,j}].second;
            if(i==initial_pos_i && j==initial_pos_j) break;
        }
        // if the node we are searching for is not itself
        if(i_fnd!=initial_pos_i &&j_fnd!=initial_pos_j) final_path.insert({initial_pos_i,initial_pos_j});
        system("clear");
        // printing the way colored
        for(ll i=0;i<length;i++){
            for(ll j=0;j<Rs_map[i].size();j++){
                if(final_path.find({i,j})!=final_path.end())    
                {
                    printf("\x1B[35m");
                    cout<<Rs_map[i][j];
                    printf("\033[0m");
                }
                else cout<<Rs_map[i][j];
            }
            cout<<"\n";
        }
    }

    ll find_shortest_path(char search,ll initial_pos_i,ll initial_pos_j,bool print,ll &i_fnd,ll &j_fnd){
        bool found=0;
        ll final_depth;
        map<pair<ll,ll>,ll> visited,depth;
        map<pair<ll,ll>,pair<ll,ll>> path;
        queue<pair<ll,ll>> q;
        visited[{initial_pos_i,initial_pos_j}]=1;
        if(Rs_map[initial_pos_i][initial_pos_j]==search) {
            // if the node we are searching for is itself 
            path[{initial_pos_i,initial_pos_j}]={initial_pos_i,initial_pos_j};
            if(print) print_path(initial_pos_i,initial_pos_j,path,initial_pos_i,initial_pos_j);
            return 0;
        }
        // applying bfs for shortest path
        q.push({initial_pos_i,initial_pos_j});
        // calculating the depth for each path for two nodes
        depth[{initial_pos_i,initial_pos_j}]=0;
        while(!q.empty()){
            ll i=q.front().first,j=q.front().second;
            q.pop();
            // checking all the nighbar  
            for(int k=-1;k<=1;k++){
                for(int w=-1;w<=1;w++){
                    if(i+k>=0 && j+w>=0 && i+k<Rs_map[i].size() && j+w<length){
                    if(visited[{i+k,j+w}]==0 && (Rs_map[i+k][j+w]=='+' || Rs_map[i+k][j+w]==search)){
                        visited[{i+k,j+w}]=1;
                        path[{i+k,j+w}]={i,j};
                        depth[{i+k,j+w}]=depth[{i,j}]+1;
                        q.push({i+k,j+w});
                        if(Rs_map[i+k][j+w]==search){
                            i_fnd=i+k,j_fnd=j+w;
                            found=1;
                            final_depth=depth[{i+k,j+w}];
                            break;
                        }
                    }
                    }
                }
                if(found) break;
            }
            if(found) break;
        }
        if(!found) {
        if(print) cout<<"CHE KHAKI BE SARAM KONAM GHAZAM YAKH KARD\n";
            final_depth=-1;
        }
        else if(print) print_path(i_fnd,j_fnd,path,initial_pos_i,initial_pos_j);
        return final_depth-1;
    }

    void deliverFood_from_kitchen(){
        ll i_fnd=kitchen_plc.first,j_fnd=kitchen_plc.second;
        cout<<find_shortest_path('b',kitchen_plc.first,kitchen_plc.second,1,i_fnd,j_fnd)<<endl;;
    }

    void calculate_Min_distn(){
        // calculating the minimum distance between each node exisited in this graph that should be traversed
        // Assuming our tables won't reach more than six (including kitchen)
        // 0->$ , 1->a, 2->b, 3->c , 4->d , 5->e 
        vector<pair<ll,ll>>table_pos;
        ll i_fnd=kitchen_plc.first,j_fnd=kitchen_plc.second;
        char x='a';
        for(int i=1;i<6;i++,x++){
            distances[0][i]=find_shortest_path(x,kitchen_plc.first,kitchen_plc.second,false,i_fnd,j_fnd);
            // if the minimal diatnce from A to B is X , then the minimal distance from B to A is also X here
            distances[i][0]=distances[0][i];
            // pushing back each nodes position in the map
            table_pos.push_back({i_fnd,j_fnd});
        }
        for(int i=0;i<5;i++){
            ll cur_i=table_pos[i].first,cur_j=table_pos[i].second;
            x= Rs_map[cur_i][cur_j];
            for(int j=i;j<5;j++,x++){
                distances[i+1][j+1]=find_shortest_path(x,cur_i,cur_j,false,i_fnd,j_fnd);
                distances[j+1][i+1]=distances[i+1][j+1];
            }
        }
    }

    ll Tsp(ll mark,ll position){
        if(mark==visited_all) 
            return distances[position][0];

        if(Dp[mark][position]!=-1)
            return Dp[mark][position];
        
        ll ans=__INT64_MAX__;

        for(int table=0;table<6;table++){
            if((mark&(1<<table))==0){
                ll newAns = distances[position][table] + Tsp( mark|(1<<table),table);
                ans = min(ans,newAns);
            }
        }
    return Dp[mark][position]=ans;
    }

    void shortest_distn_btwn_allNodes(){
        // initialize the Dp array 
        for(int i=0;i<(1<<6);i++){
            for(int j=0;j<6;j++){
                Dp[i][j] = -1;
            }
        }
        calculate_Min_distn();
        cout<< BOLDYELLOW <<Tsp(1,0)<< RESET <<endl;
    }

    /*Kitchen part functions*/
    class Food {
    public:
        //Finished food class
        string name;
        ll TimePrepare;
        map<string, ll> Nodes;
        map<string, vector<string>> adj;
        map<string, ll>indeg;
        map<string, ll>visited;
        //vector to save topological sort
        vector<string> SortedNodes;

        Food(string n)
        {
            name = n;
            TimePrepare = 0;
        }

        void TopologicalSort(const string& node)
        {
            visited[node] = 1;
            for (auto i : adj[node])
            {
                if (!visited[i])
                    TopologicalSort(i);
            }
            SortedNodes.push_back(node);
        }

        void PrintSortedNodes()
        {
            for (auto i : visited)
                visited[i.first] = 0;
            for (auto i : adj)
            {
                if (!visited[i.first])
                {
                    TopologicalSort(i.first);
                }
            }
            reverse(SortedNodes.begin(), SortedNodes.end());
            cout << "Topo Sort : ";
            for (auto i : SortedNodes)
                cout << i << ' ';
            cout << endl;
        }

        void GetPrereq()
        {
            //Get and find relation between prerequisites by using adjacency map
            string Relations;
            /*cin.ignore();*/
            while (getline(cin, Relations))
            {
                if (Relations == "end")
                    return;
                if (Relations != "End of instructions")
                {
                    vector<string> NodeRel;
                    istringstream isspre(Relations);
                    for (string s; isspre >> s; )
                        NodeRel.push_back(s);
                    string DepenNode = NodeRel[0];
                    for (ll i = 1; i < NodeRel.size(); i += 2)
                    {
                        adj[NodeRel[i]].push_back(DepenNode);
                        indeg[DepenNode]++;
                        Nodes[DepenNode] += stoi(NodeRel[i + 1]) + Nodes[NodeRel[i]];
                    }
                }
                else break;
            }
            PrintSortedNodes();
            TimePrepare = Nodes[name];
        }

        bool ThereIsPath(string u, string v)
        {
            if (u == v)
                return true;
            for (auto i : visited)
                visited[i.first] = 0;
            queue<string> q;
            visited[u] = true;
            q.push(u);
            while (!q.empty())
            {
                u = q.front();
                q.pop();
                for (auto i : adj[u])
                {
                    if (i == v)
                        return true;
                    if (!visited[i])
                    {
                        visited[i] = true;
                        q.push(i);
                    }
                }
            }
            return false;
        }

        void AddRelation(string rel)
        {
            vector<string> newRel;
            istringstream isspre(rel);
            for (string s; isspre >> s; )
                newRel.push_back(s);
            string NewDepenNode = newRel[0];
            string PrereqNode = newRel[1];
            if (!ThereIsPath(NewDepenNode, PrereqNode))
            {
                adj[PrereqNode].push_back(NewDepenNode);
                indeg[NewDepenNode]++;
                Nodes[NewDepenNode] += stoi(newRel[2]) + Nodes[PrereqNode];
                SortedNodes.clear();
                PrintSortedNodes();
            }
            else
            {
                cout << "Chef will be crashed!!" << endl;
            }
        }
    };

    void DeleteFood(string deletefood, unordered_map<string, Food*>& foods)
    {
        //Delete the food
        try
        {
            foods.erase(deletefood);
        }
        catch (const std::exception&)
        {
            cout << "Unable to delete the food";
        }
    }

    void hasMaxPrereq(unordered_map<string, Food*>& foods)
    {
        //find the food which has the maximum prerequisites
        ll MaxPrereq = 0;
        string MaxPrereqFood;
        for (auto i : foods)
        {
            //iterate in map to find the maximum prerequisites
            if (i.second->indeg[i.first] > MaxPrereq)
            {
                MaxPrereq = i.second->indeg[i.first];
                MaxPrereqFood = i.first;
            }
        }
        cout << "Max Prereq : " << MaxPrereqFood << endl;
    }

    void MaxMinTimePrepareFood(map<ll, Food*>& FoodTimePrepare)
    {
        cout << "Min: " << FoodTimePrepare.begin()->second->name << " Max: " << FoodTimePrepare.rbegin()->second->name << endl;
    }

/* Party part functions*/
class Node
{
    //class of every node (every guests)
public:
    ll Turn;
    string name;
    Node* left, * right;
    ll height;

    Node(ll t, string n)
    {
        Turn = t;
        name = n;
        left = right = nullptr;
        height = 1;
    }
};

class AVLTree
{
public:
    Node* root;
    map<Node*, int>visited;
    AVLTree()
    {
        root = nullptr;
    }

    ll height(Node* N)
    {
        //return height of node
        if (N == NULL)
            return 0;
        return N->height;
    }

    Node* rightRotate(Node* y)
    {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    Node* leftRotate(Node* x)
    {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    ll getBalance(Node* N)
    {
        if (N == NULL)
            return 0;
        return height(N->left) - height(N->right);
    }

    Node* insert(Node* node, ll turn, string name)
    {
        //insert a new node(new guest)
        if (node == NULL)
            return(new Node(turn, name));
        if (turn < node->Turn)
            node->left = insert(node->left, turn, name);
        else if (turn > node->Turn)
            node->right = insert(node->right, turn, name);
        else
            return node;
        node->height = 1 + max(height(node->left), height(node->right));
        ll balance = getBalance(node);
        if (balance > 1 && turn < node->left->Turn)
            return rightRotate(node);
        if (balance < -1 && turn > node->right->Turn)
            return leftRotate(node);
        if (balance > 1 && turn > node->left->Turn)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && turn < node->right->Turn)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    Node* minValueNode(Node* node)
    {
        Node* current = node;
        while (current->left != NULL)
            current = current->left;
        return current;
    }

    ll searchByName(string name)
    {
        //search in tree using dfs and return its turn
        queue<Node*> q;
        q.push(root);
        visited[root] = 1;
        while (!q.empty()) {
            Node* u = q.front();
            if (u->name == name)
                return u->Turn;
            q.pop();
            if (visited[u->left] == 0 && u->left)
            {
                visited[u->left] = 1;
                q.push(u->left);
            }
            if (visited[u->right] == 0 && u->right)
            {
                visited[u->right] = 1;
                q.push(u->right);
            }
        }
        //node not found
        return -1;
    }

    Node* deleteNodeByName(string name)
    {
        //getting name of the guest and finding its turn to remove it
        for (auto i : visited)
            visited[i.first] = 0;
        ll turn = searchByName(name);
        if (turn != -1)
            return deleteNodeByTurn(root, turn);
        return root;
    }

    Node* deleteNodeByTurn(Node* root, ll turn)
    {
        //remove a node by its turn
        if (root == NULL)
            return root;
        if (turn < root->Turn)
            root->left = deleteNodeByTurn(root->left, turn);
        else if (turn > root->Turn)
            root->right = deleteNodeByTurn(root->right, turn);
        else
        {
            if ((root->left == NULL) || (root->right == NULL))
            {
                Node* temp = root->left ? root->left : root->right;
                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else
                    *root = *temp;
                free(temp);
            }
            else
            {
                Node* temp = minValueNode(root->right);
                root->Turn = temp->Turn;
                root->name = temp->name;
                root->right = deleteNodeByTurn(root->right, temp->Turn);
            }
        }
        if (root == NULL)
            return root;
        root->height = 1 + max(height(root->left), height(root->right));
        ll balance = getBalance(root);
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);
        if (balance > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);
        if (balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }

    bool searchByTurn(Node* root, ll TurntoSearch)
    {
        //finding the node by getting its turn
        if (root != NULL)
        {
            if (root->Turn == TurntoSearch)
            {
                cout << root->name << endl;
                return true;
            }
            else if (root->Turn < TurntoSearch)
            {
                searchByTurn(root->right, TurntoSearch);
            }
            else
            {
                searchByTurn(root->left, TurntoSearch);
            }
        }
        //node not found
        return false;
    }

    void ShowTree()
    {
        //print the AVL tree
        //vector to save every line
        vector<vector<string>> lines;
        vector<Node*> level;
        //vector to save next line
        vector<Node*> next;
        level.push_back(root);
        int c = 1;
        //length of widest node name
        int widest = 0;
        while (c != 0)
        {
            vector<string> line;
            c = 0;
            for (auto n : level)
            {
                if (n == NULL)
                {
                    line.push_back("");
                    next.push_back(NULL);
                    next.push_back(NULL);
                }
                else
                {
                    string nodenam = n->name;
                    line.push_back(nodenam);
                    if (nodenam.length() > widest)
                        widest = nodenam.length();
                    next.push_back(n->left);
                    next.push_back(n->right);
                    if (n->left != NULL)
                        c++;
                    if (n->right != NULL)
                        c++;
                }
            }
            if (widest % 2 == 1)
                widest++;
            lines.push_back(line);
            vector<Node*> tmp = level;
            level = next;
            next = tmp;
            next.clear();
        }
        //number of spaces
        int perpiece = lines.rbegin()->size() * (widest + 4);
        for (int i = 0; i < lines.size(); i++)
        {
            vector<string> line = lines[i];
            int hpw = (int)(perpiece / 2) - 1;
            if (i > 0) {
                for (int j = 0; j < line.size(); j++)
                {
                    string c = " ";
                    if (j % 2 == 1)
                    {
                        if (line[j - 1] != "")
                            c = "+";
                        else if (line[j] != "")
                        {
                            for (int k = 0; k < lines[i - 1].size(); k++)
                                cout << " ";
                            c = "+";
                        }
                    }
                    cout << c;
                    if (line[j] == "")
                        for (int k = 0; k < perpiece - 1; k++)
                            cout << " ";
                    else
                    {

                        for (int k = 0; k < hpw; k++)
                            cout << (j % 2 == 0 ? " " : "-");
                        cout << (j % 2 == 0 ? "| " : " |");
                        for (int k = 0; k < hpw; k++)
                            cout << (j % 2 == 0 ? "-" : " ");
                    }
                }
                cout << endl;
            }
            for (int j = 0; j < line.size(); j++)
            {
                string f = line[j];
                int gap1 = perpiece / 2 - f.size() / 2 + 1;
                int gap2 = ceil(perpiece / 2.0) - ceil(f.size() / 2.0);
                for (int k = 0; k < gap1; k++)
                    cout << " ";
                cout << f;
                for (int k = 0; k < gap2; k++)
                    cout << " ";
            }
            cout << endl;
            perpiece /= 2;
        }
    }
};

    bool isNumber(const string& str)
    {
        //check str is number or not
        return str.find_first_not_of("0123456789") == string::npos;
    }

    /* getting input parts */

    void Party_inputs()
    {
        AVLTree AVL;
        string Operation;
        while (cin >> Operation)
        {
            if (Operation == "Insert")
            {
                string name;
                ll turn;
                cin >> name >> turn;
                AVL.root = AVL.insert(AVL.root, turn, name);
            }
            else if (Operation == "Delete")
            {
                string TurnName;
                cin >> TurnName;
                if (isNumber(TurnName))
                {
                    AVL.root = AVL.deleteNodeByTurn(AVL.root, stoi(TurnName));
                }
                else
                    AVL.root = AVL.deleteNodeByName(TurnName);
            }
            else if (Operation == "Search")
            {
                ll turn;
                cin >> turn;
                if (!AVL.searchByTurn(AVL.root, turn))
                    cout << "Not Found!" << endl;
            }
            else if (Operation == "ShowTree")
            {
                AVL.ShowTree();
            }
        }
    }

    void Kitchen_inputs()
    {
        //using unordered map to have access to finished foods and their names
        unordered_map<string, Food*> Foods;
        //using map to to have access to finished foods and their time prepare
        map<ll, Food*> SortedFoodTimePrepare;
        string str;
        /*cin.ignore();*/
        while (getline(cin, str))
        {
            //create a new food and insert to unordered map and map
            if (str == "New Food:")
            {
                string NewFoodName;
                getline(cin, NewFoodName);
                Food* newfood = new Food(NewFoodName);
                newfood->GetPrereq();
                Foods.insert({ NewFoodName,newfood });
                SortedFoodTimePrepare.insert({ newfood->TimePrepare, newfood });
            }
            else break;
        }
    }

    void get_restaurant_map(){
        // getting the map
        ll map_i,map_j;
        string input_str;
        try
        {
            printf(CYAN "Enter map's rows : " RESET);
            cin>>map_i;
            printf(CYAN "Enter map's calumn : " RESET);
            cin>>map_j;
                for(ll k=0;k<map_j;k++){
                cin>>input_str;
                Rs_map.push_back(input_str);
                if ( std::string::npos != input_str.find('$')){
                    kitchen_plc.first=length;
                    kitchen_plc.second=input_str.find('$');
                }
                length++;
                }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    void custumers_data_inputs(){

        string customer_detail;
        // getting constome's data
        vector<customer> customer_info;
        try
        {
             cin.ignore();
            while(getline(cin,customer_detail)){
                if(customer_detail=="END" || customer_detail=="end") break;
                if(customer_detail.empty()) continue;
                stringstream ss(customer_detail);
                customer x;
                string word;
                    ss>>word; x.name=word;
                    ss>>word; x.ordered_food=word;
                    ss>>word; x.prepartion_time=stoi(word);
                    ss>>word; x.eating_time=stoi(word);
                    customer_info.push_back(x);
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    void main_menu(){
        ll x,tmp;
        system ("clear");
        printf(BOLDYELLOW "---------------- Resraurant Management ----------------\n" RESET);
        printf(RED "Choose Parts :\n" RESET);
        printf(RED "1. " RESET);
        printf(CYAN "Customer Acceptance \n" RESET);
        printf(RED "2. " RESET);
        printf(CYAN "Food Delivery \n" RESET);
        printf(RED "3. " RESET);
        printf(CYAN "Kitchen \n" RESET);
        printf(RED "4. " RESET);
        printf(CYAN "Party\n" RESET);
        cin>>x;
        system("clear");
        switch (x)
        {
        case 1:
            printf(YELLOW "Eneter customer's data as follow:\n" RESET);
            printf(RED "*Note that each charactristic must be written in a single line and (each property shouldn't comtain space) !\n" RESET);
            printf (GREEN " => First enter the name  \n => second enter Food's name\n => third line enter the time taken by customer to eat his food\n " RESET);
            printf(RED "When you 're finished filling up, enter " BOLDRED "END\n" RESET);
            custumers_data_inputs();
            return main_menu();
            break;
        case 2:
        delivery_menu();
        return main_menu();
            break;
        default:
            break;
        }
    }

    void delivery_menu(){
        system("clear");
        ll tmp,i_fnd,j_fnd;
        char table_name,test;
        printf(CYAN "Choose the one you desire to do:\n" RESET);
        printf (GREEN " 1. Enter map's Restaurant  \n 2. Find the shortest path from kitchen to chosen table \n 3. Find the length of the shortest path crossing all nodes(tables)\n 4. Find shortest path between two nodes \n 5. Back to main menu \n" RESET);
        cin>>tmp;
        system("clear");
            switch (tmp)
            {
            case 1:
                get_restaurant_map();
                std::this_thread::sleep_for(std::chrono::seconds(2)); 
                return delivery_menu();
                break;

            case 2:
                if(Rs_map.size()==0){
                    printf(RED " You need to enter restaurant's map first ! \n");
                    std::this_thread::sleep_for(std::chrono::seconds(2)); 
                    return delivery_menu();
                }
                printf(YELLOW "Enter your desired table char representation : " RESET);
                cin>>table_name;
                find_shortest_path(table_name,kitchen_plc.first,kitchen_plc.second,1,i_fnd,j_fnd);
                printf(GREEN "To turn back to menu Enter" BOLDYELLOW " q\n" RESET);
                cin>>test;
                if(test=='q' || test=='Q') return delivery_menu();
                break;

            case 3:
                if(Rs_map.size()==0){
                    printf(RED " You need to enter restaurant's map first ! \n");
                    std::this_thread::sleep_for(std::chrono::seconds(2)); 
                    return delivery_menu();
                }
                shortest_distn_btwn_allNodes();
                 printf(GREEN "To turn back to menu Enter" BOLDYELLOW " q\n" RESET);
                    cin>>test;
                    if(test=='q' || test=='Q') return delivery_menu();
                break;

            case 4:
                  if(Rs_map.size()==0){
                    printf(RED " You need to enter restaurant's map first ! \n");
                    std::this_thread::sleep_for(std::chrono::seconds(2)); 
                    return delivery_menu();
                }
                printf(CYAN "Eneter the first node's char representation : " RESET);
                cin>>test;
                find_shortest_path(test,kitchen_plc.first,kitchen_plc.second,0,i_fnd,j_fnd);
                printf(CYAN "Eneter the second node's char representation : " RESET);
                cin>>test;
                find_shortest_path(test,i_fnd,j_fnd,1,i_fnd,j_fnd);
                printf(GREEN "To turn back to menu Enter" BOLDYELLOW " q\n" RESET);
                    cin>>test;
                    if(test=='q' || test=='Q') return delivery_menu();
                break;
            
            case 5:
                return ;
                break;
            default:
                printf(RED "OUT OF RANGE ! \n" RESET);
                std::this_thread::sleep_for(std::chrono::seconds(2)); 
                delivery_menu();
                break;
            }
    }

int main(){
     ll x,tmp;
    printf(YELLOW " _    _   _____   _       _____   _____   __  __   _____   \n");
    printf("| |  | | |  ___| | |     |  __ | |  _  | |   V  | |  ___| \n");
    printf("| |  | | | |__   | |     | |  || | | | | | .  . | | |__   \n");
    printf("| |__| | |  __|  | |     | |     | | | | | | V| | |  __|  \n");
    printf("|  ^^  | | |___  | |____ | |__|| | |_| | | |  | | | |___  \n");
    printf(" V    V  |_____| |_____/ | ____| |_____| |_|  |_| | ____| \n" RESET);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    main_menu();
    return 0;
}