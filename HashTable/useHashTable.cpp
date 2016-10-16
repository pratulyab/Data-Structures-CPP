#include<iostream>
#include<string>
#include"HashMap.h"
using namespace std;
int main() {
    HashMap<string, int> M;
    for (int i = 0; i < 200; i++) {
        int num = i;
        string s = "A";
        s+= '0' + num % 10;
        num/=10;
        s+= '0' + num % 10;
        num/=10;
        s+= '0' + num % 10;
        M[s] = i;
    }
    for (int i = 100; i < 200; i+=5) {
        int num = i;
        string s = "A";
        s+= '0' + num % 10;
        num/=10;
        s+= '0' + num % 10;
        num/=10;
        s+= '0' + num % 10;
        cout << M.get(s) << " ";
        M.remove(s);
    }
    try {
        cout << M.get(string("A105")) << endl;
    } catch(const char * msg) {
        cerr << msg << endl;

    } catch(int errorcode) {
        cerr << errorcode << endl;
    }
    cout << "Coding Blocks" << endl;
//    cout << M.get(string("A100")) << endl;
    /*
    string a("Anushray"), b("Ankush"), c("Kannu");
    M[a] = 10;
    M[b] = 20;
    M.insert(c, 30);
    cout << M[a] << endl;
    cout << M.get(b) << endl;
    M.remove(a);
    cout << M.contains(a) << endl;
    M[c] = 40;
    cout << M[c] << endl;
    cout << M.get(c) << endl;
    M.update(c, 100);
    cout << M[c] << endl;
    M.clear();
    cout << M.contains(b) << endl;
    */
    return 0;
}
