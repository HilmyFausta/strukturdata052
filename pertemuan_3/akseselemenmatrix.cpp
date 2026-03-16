#include <bits/stdc++.h>
using namespace std;

int main(){

    int matrix[3][4] = {{200, 178, 930, 124},
                        {150, 300, 67, 200},
                        {87, 90, 100, -90}};

    printf("Semua elemen dalam matriks adalah: \n");

    int i, j;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 4; j++){
            cout << matrix[i][j] << ' '; 
        }
        printf("\n");
    }

    printf("Nilai baris 2 kolom 3 adalah : ");
    cout << matrix[1][2];



    return 0;
}