#include <bits/stdc++.h>
using namespace std;

int tanda(char op) {
    if (op == '^'){
        return 3;
    }else if (op == '.' || op == '/'){
        return 2;
    }else if (op == '+' || op == '-'){
        return 1;
    }else{
        return 0;
    }
}

bool cekoperator(char c) {
    return (c == '+' || c == '-' || c == '.' || c == '/' || c == '^');
}

string infixtopostfix(string infix) {
    stack<char> st;
    string postfix = "";

    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];

        if (c == ' '){
            continue;
        }

        if (isalnum(c)) {
            postfix += c;
        }else if (c == '(') {
            st.push(c);
        }else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            if (!st.empty()){
                st.pop();
            }
        }
        
        else if (cekoperator(c)) {
            while (!st.empty() && tanda(st.top()) >= tanda(c)) {
                postfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    while (!st.empty()) {
        postfix += st.top();
        st.pop();
    }

    return postfix;
}

int main() {
    string infix;

    cout << "Input infix: ";
    getline(cin, infix);

    string postfix = infixtopostfix(infix);
    cout << "Postfix: " << postfix << endl;

    return 0;
}