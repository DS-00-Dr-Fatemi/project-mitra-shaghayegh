#include<bits/stdc++.h>
using namespace std;
using ll=long long;
vector<string> Rs_map;
pair<ll,ll>kitchen_plc;
map<pair<ll,ll>,int> visited;
map<pair<ll,ll>,pair<ll,ll>> path;
queue<pair<ll,ll>> q;
set<pair<ll,ll>> final_path;
int length=0;
struct customer{
    string name;
    string ordered_food;
    ll prepartion_time;
    ll eating_time;
};
void print_path(ll i_fnd,ll j_fnd,map<pair<ll,ll>,pair<ll,ll>> path){
    ll i=i_fnd,j=j_fnd,prv;
    while(1){
        final_path.insert({i,j});
        prv=i;
        i=path[{i,j}].first;
        j=path[{prv,j}].second;
        if(i==kitchen_plc.first && j==kitchen_plc.second) break;
    }
    final_path.insert({kitchen_plc.first,kitchen_plc.second});
    cout<<final_path.size()<<endl;
    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ll k=13;
    // printing the map and coloring the nodes that are included in the shortest path
    for(ll i=0;i<length;i++){
        for(ll j=0;j<Rs_map[i].size();j++){
             if(final_path.find({i,j})!=final_path.end()) cout<<' ';
        //         SetConsoleTextAttribute(hConsole, k),cout<<k;
            else cout<<Rs_map[i][j];
        }
        cout<<"\n";
    }
}
void find_shortest_path(char search){
    bool found=0;
    ll i_fnd,j_fnd;
    visited[{kitchen_plc.first,kitchen_plc.second}]=1;
    // applying bfs for shortest path
    q.push({kitchen_plc.first,kitchen_plc.second});
    while(!q.empty()){
        ll i=q.front().first,j=q.front().second;
        q.pop();
        // checking all the nighbar  
        for(int k=-1;k<=1;k++){
            for(int w=-1;w<=1;w++){
                if(i+k>=0 && j+w>=0 && i+k<Rs_map[i].size() && j+w<length){
                if(visited[{i+k,j+w}]==0 && Rs_map[i+k][j+w]!='#'){
                    visited[{i+k,j+w}]=1;
                    path[{i+k,j+w}]={i,j};
                    q.push({i+k,j+w});
                    if(Rs_map[i+k][j+w]==search){
                        i_fnd=i+k,j_fnd=j+w;
                        found=1;
                        break;
                    }
                  }
                }
            }
            if(found) break;
        }
        if(found) break;
    }
    if(!found) cout<<"CHE KHAKI BE SARAM KONAM GHAZAM YAKH KARD\n";
    else {
        cout<<"sdds"<<endl;
        print_path(i_fnd,j_fnd,path);
     }
}
int main(){
    string input_str,customer_detail;
    // getting the map
    while (cin>>input_str){
        Rs_map.push_back(input_str);
       if ( std::string::npos != input_str.find('$')){
           kitchen_plc.first=length;
           kitchen_plc.second=input_str.find('$');
       }
    length++;
    if(length==10) break;
    }
    find_shortest_path('d');
    // getting constome's data
    vector<customer> costomer_info;
    // cin.ignore();
    // while(getline(cin,customer_detail)){
    //     stringstream ss(customer_detail);
    //     customer x;
    //     string word;
    //         ss>>word; x.name=word;
    //         ss>>word; x.ordered_food=word;
    //         ss>>word; x.prepartion_time=stoi(word);
    //         ss>>word; x.eating_time=stoi(word);
    //         costomer_info.push_back(x);
    // }
    return 0;
}