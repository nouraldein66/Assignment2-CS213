#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main()
{
    string s , tmp = ""; 
    getline(cin , s);
    const int SIZE = s.size();
    set<int>He_idx  , him_idx , himself_idx;
    for(int i{} ; i < SIZE ; i++)
     {
        if(s[i] == ' ' || s[i] == '.')
          {
           if(tmp == "He" || tmp == "he")
              {
                He_idx.emplace(i);
              }
          
            if(tmp == "him")
               {
                him_idx.emplace(i);
               }  
            if(tmp == "Himself" || tmp == "himself") 
              {
               himself_idx.insert(i);
              }   
            tmp = "";
            continue;
          }
        
       tmp += s[i];
     }
   for(int i{} ; i < SIZE ; ++i)
      {
        if(He_idx.count(i))
           {
            cout<<" or she";
           }
        else if (him_idx.count(i))
           {
            cout<<" or her";
           }   
       else if(himself_idx.count(i))
          {
            cout<<" or herself";
          }
        cout<<s[i];
      }  

}