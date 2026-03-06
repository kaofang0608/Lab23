#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream fin("name_score.txt") ;
    string s ;
    
    while(getline(fin,s)){
        char format[] = "%[^:]: %d %d %d" ;
        char name[100] ;
        int a,b,c ;
        sscanf(s.c_str(),format,name,&a,&b,&c) ;
        
        names.push_back(name); //เก็บชื่อ
        
        int total=a+b+c ;
        scores.push_back(total);
        grades.push_back(score2grade(total));
        
        
    }


}

void getCommand(string &command, string &key){
    cout << "Please input your command:" ;
    string input;
    getline(cin, input);
    cout << "\n" ;
    
    size_t pos = input.find_first_of(" "); //นับจนตัว
    
    if(pos != string::npos){
        command = input.substr(0, pos); //ถ้าเจอวรรคให้commandเป็นตัวก่อนวรรค
        key = input.substr(pos + 1); //keyเป็นตัวหลัง
    } else {
        command = input;
        key = "";
    }


}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool found = false;
    cout << "---------------------------------\n";
    
    string upperKey = toUpperStr(key); 

    for(unsigned int i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == upperKey){ 
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            found = true;
            break; 
        }
    }
    
    if(!found){
        cout << "Cannot found.\n";
    }
    
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool found = false;
    cout << "---------------------------------\n";
    
    for(unsigned int i = 0; i < grades.size(); i++){
        if(grades[i] == key[0]){ 
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    
    if(!found){
        cout << "Cannot found.\n";
    }
    
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}