#include<bits/stdc++.h>
#include <stdlib.h>
using namespace std;
using ll=long long;
vector<string> Rs_map;
pair<ll,ll>kitchen_plc;
int length=0;
struct customer{
    string name;
    string ordered_food;
    ll prepartion_time;
    ll eating_time;
};
// Tsp part  & dynamic part Dp[2^n][n]
ll distances[6][6],Dp[64][6];

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
        print_path(initial_pos_i,initial_pos_j,path,initial_pos_i,initial_pos_j);
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
    return final_depth;
}

void deliverFood_from_kitchen(){
       ll i_fnd=kitchen_plc.first,j_fnd=kitchen_plc.second;
       find_shortest_path('a',kitchen_plc.first,kitchen_plc.second,1,i_fnd,j_fnd);
}

void get_restaurant_map(){
      // getting the map
    ll map_i,map_j;
     cout<<"Enter map's dimentions : ";
       cin>>map_i>>map_j;
       string input_str;
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

ll Tsp(){
    
}

void calMin_distn(){
    // calculating the minimum distance between each node exisited in this graph that should be traversed
    // Assuming our tables won't reach more than six (including kitchen)
    // if the minimal diatnce from A to B is X , then the minimal distance from B to A is also X here
    // 0->$ , 1->a, 2->b, 3->c , 4->e , 5->f , 6->g
    vector<pair<ll,ll>>table_pos;
    ll i_fnd=-1,j_fnd=-1;
    char x='a';
    for(int i=1;i<6;i++,x++){
        distances[0][i]=find_shortest_path(x,kitchen_plc.first,kitchen_plc.second,0,i_fnd,j_fnd);
        // pushing back each nodes position in the map
        table_pos.push_back({i_fnd,j_fnd});
    }
    for(auto i:table_pos) cout<<i.first<<' '<<i.second<<endl;
}

int main(){
    string customer_detail;
    // getting constome's data
    get_restaurant_map();
    calMin_distn();
    vector<customer> costomer_info;
    cin.ignore();
    while(getline(cin,customer_detail)){
        stringstream ss(customer_detail);
        customer x;
        string word;
            ss>>word; x.name=word;
            ss>>word; x.ordered_food=word;
            ss>>word; x.prepartion_time=stoi(word);
            ss>>word; x.eating_time=stoi(word);
            costomer_info.push_back(x);
    }
    return 0;
}