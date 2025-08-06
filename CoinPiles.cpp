#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
       long long a, b;
       cin >> a >> b;

       if(a*2 >= b && b*2 >= a && (a+b)%3 == 0){
           cout << "YES" << endl;
       } else {
           cout << "NO" << endl;
       }
    }
    
   
    return 0;
}