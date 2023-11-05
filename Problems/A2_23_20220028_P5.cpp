// File: A2_S23_20220028_p5.cpp
// Purpose: Keeping the information of the top 10 players and making operations like searching for a player or printing the top 10 names and scores
// Author: Ahmed Alaa Eldin
// Section: S23
// ID: 20220028
// TA: Muhammad Talaat
// Date: 4 Nov 2023

#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main()
{
    vector<pair<string , int>>vp;
    string s; 
   cout<<"If you want to add a new player please, enter add ,  and enter the name of that player and their socre\nIf you want to print the names and scores of top 10 players please, enter print\nIf you want to check if a player is in the list and in the top 10 please, enter find and their name\n ";
    while(cin >> s)
      {
         
        for(auto& i : s)
           if(i >= 'A' && i <= 'Z')
            {
              i = tolower(i);
            }

       if(s == "add")
         {  
            cout<<"Please, enter the name and score\n";
            string name ;
            int score;
            cin >> name >> score;
            for(auto& i : name)
               {
                 i = tolower(i);
               }
            vp.emplace_back(name , score);
            sort(vp.begin() , vp.end() , [](pair<string , int > p1 , pair<string , int > p2){return p1.second > p2.second;});
            while(vp.size() > 10)
              {
                vp.pop_back();
              }
         }
        else if (s == "print")
           {
               if(vp.empty())
                 {
                    cout<<"The list is empty\n";
                    continue;
                 }
            for(auto i : vp)
               cout<<i.first<<' '<<i.second<<'\n';
           }
        else if(s == "find")
           {  
              cout<<"Please, enter the name\n";
              string name;  cin >> name;
              for(auto& i : name)
                 {
                    i = tolower(i);
                 }
              bool found = 0;
            for(auto i : vp)
               {
                if(i.first == name)
                   {
                     found = 1;
                    cout<<name<<' '<<i.second<<'\n';
                    break;
                   }
               }
              if(!found)
                {
                    cout<<"maybe the player is not on the top 10 or not even exist\n";
                }
           }
      }
}
