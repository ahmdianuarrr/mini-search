#include<iostream>
#include<string>
#include<cctype>
using namespace std;

int main (){
    string teks = "HaLo, dunia !";
   

    for ( int i = 0; i <teks.size() ; i++){
        char huruf = tolower(teks[i]);

        if (isalnum (huruf))
        cout << huruf <<endl;
        
        /* code */
    }
    
    return 0;
}