#include <bits/stdc++.h>
using namespace std;

void vokalkonsonan(char n){
    if(n == 'a' || n == 'A' || n == 'i' || n == 'I' || n == 'u' || n == 'U' || n == 'e' || n == 'E' || n == 'o' || n == 'O'){
        cout << "Vokal" << endl;
    } else{
        cout << "Konsonan" << endl;
    }
}

int main(){

    puts("CEK VOKAL/KONSONAN");
    char n;
    cin >> n;

    vokalkonsonan(n);

    return 0;
}