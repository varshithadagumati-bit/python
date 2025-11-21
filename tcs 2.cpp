#include <bits/stdc++.h>
using namespace std;

struct Transaction {
    string type; // "credit" or "debit"
    int amount;
    bool active; // true if not aborted
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int initialBalance;
    cin >> initialBalance;

    int N;
    cin >> N;

    vector<Transaction> transactions;        // all transactions so far
    vector<int> commitBalances;              // checkpoints after each commit
    int balance = initialBalance;

    for (int i = 0; i < N; i++) {
        string op;
        cin >> op;

        if (op == "read") {
            cout << balance << "\n";
        }
        else if (op == "credit") {
            int x; cin >> x;
            transactions.push_back({"credit", x, true});
            balance += x;
        }
        else if (op == "debit") {
            int x; cin >> x;
            transactions.push_back({"debit", x, true});

