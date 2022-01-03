#include<bits/stdc++.h>
using namespace std;
using ll=long long;
vector<string> Rs_map;
pair<ll,ll>kitchen_plc;
struct customer{
    string name;
    string ordered_food;
    ll prepartion_time;
    ll eating_time;
};
void find_shortest_path(char search){
    map<pair<ll,ll>,bool> visited;
    map<pair<ll,ll>,pair<ll,ll>> path;
    queue<pair<ll,ll>> q;
    bool found=0;
    ll i_fnd,j_fnd;
    visited[{kitchen_plc.first,kitchen_plc.second}]=1;
    q.push({kitchen_plc.first,kitchen_plc.second});
    while(!q.empty()){
        ll i=q.front().first,j=q.front().second;
        q.pop();
        for(int k=-1;k<1;i++){
            for(int w=-1;w<1;w++){
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
    }
    if(!found) cout<<"CHE KHAKI BE SARAM KONAM GHAZAM YAKH KARD\n";
    else{

    }
}
int main(){
    string input_str,customer_detail;
    // getting the map
    int length=0;
    while (cin>>input_str){
        Rs_map.push_back(input_str);
       if ( std::string::npos != input_str.find('$')){
           kitchen_plc.first=length;
           kitchen_plc.second=input_str.find('$');
       }
    length++;
    }
    // getting constome's data
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