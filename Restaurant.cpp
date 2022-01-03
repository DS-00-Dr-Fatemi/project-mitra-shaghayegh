#include<bits/stdc++.h>
using namespace std;
using ll=long long;
vector<string> Rs_map;
struct customer{
    string name;
    string ordered_food;
    ll prepartion_time;
    ll eating_time;
};
int main(){
    string input_str,customer_detail;
    // getting the map
    while (cin>>input_str){
        Rs_map.push_back(input_str);
    }
    // getting constome's data
    vector<customer> costomer_ifno;
  // cin.ignore();
    while(getline(cin,customer_detail)){
        stringstream ss(customer_detail);
        customer x;
        string word;
            ss>>word; x.name=word;
            ss>>word; x.ordered_food=word;
            ss>>word; x.prepartion_time=stoi(word);
            ss>>word; x.eating_time=stoi(word);
            costomer_ifno.push_back(x);
    }
    return 0;
}