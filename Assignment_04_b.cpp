#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    void dfs(int n, int i, vector<bool>&& cols, vector<bool>&& diag1, vector<bool>&& diag2, vector<string>&& board, vector<vector<string>>& ans) {
        if (i == n) {
            ans.push_back(board);
            return;
        }

        for (int j = 0; j < n; ++j) {
            if (cols[j] || diag1[i + j] || diag2[j - i + n - 1])
                continue;

            board[i][j] = 'Q';
            cols[j] = diag1[i + j] = diag2[j - i + n - 1] = true;
            dfs(n, i + 1, move(cols), move(diag1), move(diag2), move(board), ans);
            cols[j] = diag1[i + j] = diag2[j - i + n - 1] = false;
            board[i][j] = '.';
        }
    }
    
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        dfs(n, 0, vector<bool>(n), vector<bool>(2 * n - 1), vector<bool>(2 * n - 1), vector<string>(n, string(n, '.')), ans);
        return ans;
    }

    void display(vector<vector<string>> sol){
        for (int i=0; i<sol.size(); i++){
            for(int j=0; j<sol[0].size(); j++){
                cout<<sol[i][j]<<"\n";
            }
            cout<<"\n\n";
        }
    }
};

int main(){
    Solution s;
    int n;
    cout<<"Enter the size of matrix : ";
    cin>>n;
    vector<vector<string>> sol(n, vector<string>(n, ""));

    sol = s.solveNQueens(n);

    s.display(sol);

    return 0;
}
