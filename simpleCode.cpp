//block problem -> using best fit search and heuristics

#include<iostream>
#include<queue>
#include<vector>
#include<map>
#include<set>
#include<limits>
#include<chrono>
using namespace std;

chrono::high_resolution_clock clk;
struct myComp {
    constexpr bool operator()(
        pair<set<string>, int> const& a,
        pair<set<string>, int> const& b)
        const noexcept
    {
        return a.second < b.second;
    }
};

void print_sol(map<set<string>,set<string>> mp,set<string> final_state){
    vector<set<string>> ans;
    set<string> parent,child=final_state;
    set<string> b={"-1"};
    while(child!= b)
    {
        ans.push_back(child);
        parent=mp[child];
        child=parent;
    }
    
    for(int i=ans.size()-1;i>=0;i--){
        for(auto it:ans[i]){
            cout<<it<<" ";
        }
        cout<<endl;
        cout<<endl;
    }
    
}



vector<set<string>> generate_children(set<string> &node){
    vector<set<string>> ans;
   

    for(auto it:node){
       

        set<string> temp=node;
        temp.erase(it);
        string str=it;
        char ch=str[str.size()-1];
        str.pop_back();
        if(str!="")
            temp.insert(str);

        
        for(auto it2:temp){
            set<string> tt=temp;
            string s=it2;
            tt.erase(it2);
            tt.insert(s+ch);
            ans.push_back(tt);


        }
        string s="";
        s+=ch;
        temp.insert(s);
        ans.push_back(temp);

    }
    return ans;

}

auto hueristics(set<string> const & cur_state, set<string> const &final_state) -> int {
  long res = 0;
  for (auto &iter : cur_state) {
    long h = numeric_limits<long>::min();
    for (auto &gstack : final_state) {
    long temp = 0;
      temp = static_cast<long>(gstack.size()) - iter.size();
      temp = abs(temp) * -1;
      for (int i = 0; i < min(gstack.size(), iter.size()); ++i)
        gstack[i] == iter[i] ? ++temp : --temp;
      h = max(h, temp);
      res += h;
    }
  }
  return res;
}       

void best_first_search(set<string> intial_state,set<string> final_state){
    
    priority_queue<pair<set<string>, int>,vector<pair<set<string>, int>>,myComp> q;
;
    map<set<string>,int> mp;
    map<set<string>,set<string>> path;
    path[intial_state]={"-1"};

    q.push({intial_state,hueristics(intial_state, final_state)});
    mp[intial_state]++;
    bool flag=false;
    int level=0;
    while(!q.empty() && flag==false){
        int size=q.size();
        while(size--){
            auto z=q.top();
            set<string> temp = z.first;
            int h=z.second;
            q.pop();

            if(temp==final_state)
            {
                // cout<<"Levels -> "<<level<<endl;
                flag=true;
                break;
            }

            vector<set<string>> children_nodes=generate_children(temp);

            for(auto child: children_nodes){
                if(mp.find(child)==mp.end())
                {
                    q.push({child, hueristics(child, final_state)});
                    mp[child]++;
                    path[child]=temp;
                }
            }

            
        }
        level++;
    }

    print_sol(path,final_state);
}




int main(int argc, char const *argv[])
{

    set<string> final_state={"abc","def"};
    set<string> intial_state={"cab", "fed"};    
    auto start=clk.now();
    best_first_search(intial_state,final_state);
    auto end=clk.now();
    cout<< (end-start).count()/100000.;
    
    return 0;
}
