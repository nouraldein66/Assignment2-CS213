#include<bits/stdc++.h>
#include<fstream>
using namespace std;
int main()
{
    string firstFileName , secondFileName;
    cin >> firstFileName >> secondFileName;
    fstream firstFile , secondFile;
    int option;
    cout<<"If you want to compare these two files word by word :\nEnter 1\n";
    cout<<"If you want to compare them character by character :\nEnter 2\n";
    cin >> option;
    firstFile.open(firstFileName , ios::in);
    secondFile.open(secondFileName , ios::in);
    if(!(firstFile.is_open() && secondFile.is_open()))
      {
        cout<<"Invalid file names\n";
        return 0;
      }
    if(option == 1)
      {
        string line1 , line2;
        vector<string>v1 , v2;
        while(getline(firstFile , line1))
          {
            string tmp = "";
            for(auto character : line1)
               {
                if(character == ' '){
                     tmp = "";
                   if(!tmp.empty())
                      v1.emplace_back(tmp);  
                }
                  else tmp += character;   
               }
          }
          while(getline(secondFile , line2))
            {
                string tmp = "";
                for(auto ch : line2)
                   {
                    if(ch == ' ' )
                     {
                         tmp = "";
                         if(!tmp.empty())
                            v2.emplace_back(tmp);
                     }   
                     else tmp += ch;
                        
                   }
            }
         if(v2 == v1)cout<<"Identical files!\n";
         else cout<<"The files differ";   
      }
     else if(option == 2)
       {
         string line1 , line2;
        vector<char>v1 , v2;
        while(getline(firstFile , line1))
          {
            
            for(auto character : line1)
               {
                v1.emplace_back(character);
               }
          }
          while(getline(secondFile , line2))
            {
                
                for(auto ch : line2)
                   {
                      v2.emplace_back(ch);
                        
                   }
            }
         if(v2 == v1)cout<<"Identical files!\n";
         else cout<<"The files differ";   
          
       } 

//   firstFile.close();
//   secondFile.close()''

}