#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll oo = 1e9,mod = 1e9 + 7, N = 2e5+ 9;
int n;
vector<int>vis(28);
struct d
{
  int left , right;
};
vector<d>v(28);
vector<int>ans;
int check(vector<int>vis , vector<int>cur)
{
if(cur.size() == n)
   {
    ans = cur;
    return 1;
   }
int ret = 0;
for(int i{} ; i < n ; i++)
  {
    if(!vis[i] && (cur.empty() || v[cur.back()].right == v[i].left))
       {
        cur.emplace_back(i);
        vis[i] = 1;
       ret |= check(vis , cur);
        cur.pop_back();
        vis[i] = 0;
       }
  }
 return ret; 
}
void solve()
{
  cin >> n;
  for(int i{} ; i < n ; i++)
      cin >> v[i].left >> v[i].right;
  vector<int>cur;    
  int flag = check(vis , cur);
  if(flag)
    {
      cout<<"YES\n";
      for(int i{} ; i < n ; i++)
        {
          cout<<v[ans[i]].left<<'|'<<v[ans[i]].right;
          if(i != n - 1)cout<<" - ";
        }
    }    

}
int main()
{
    //  freopen("input.txt","r",stdin);
//   freopen("output.txt","w",stdout);
    std:: ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    ll t = 1;
    // cin>>t;
 while(t--)
      solve();
}