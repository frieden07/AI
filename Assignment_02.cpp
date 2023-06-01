#include<bits/stdc++.h>
using namespace std;

int checkheuristic(vector<vector<int>> matrix, vector<vector<int>> goal_matrix){
    int count = 0;

    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            if (matrix[i][j] != goal_matrix[i][j]){
                count++;
            }
        }
    }

    return count;
}


int checkHeuristic(vector<vector<int>> matrix, vector<vector<int>> goal_matrix){
    int count = 0;

    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            if (matrix[i][j] != 0){
                int x, y;
                int flag = 0;
                
                for (int m=0; m<3; m++){
                    for (int n=0; n<3; n++){
                        if (matrix[i][j] == goal_matrix[m][n]){
                            x = m;
                            y = n;
                            flag = 1;
                            break;
                        }
                    }
                    if (flag == 1){
                        break;
                    }   
                }

                count = count + abs(i-x) + abs(j - y);
            }

            
        }
    }

    return count;

}

void display(vector<vector<int>> matrix, vector<vector<int>> goal_matrix, int level, int type){
    cout<<"\n";
    for(int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    int h;

    if (type == 1){
        h = checkHeuristic(matrix, goal_matrix);
    }
    else{
        h = checkheuristic(matrix, goal_matrix)-1;
    }

    cout<<"\nHeuristic value : "<<h;
    cout<<"\nlevel : "<<level<<"\n";
}

vector<vector<int>> transform_matrix(vector<vector<int>> matrix, vector<vector<int>> goal_matrix, set<vector<vector<int>>> &matrix_set, int level, int type){
    // coordinate of 0;
    int x, y;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if (matrix[i][j] == 0){
                x = i;
                y = j;
            }
        }
    }

    // generation of matrix and checking if alredy exists in set;
    vector<vector<vector<int>>> matrix_collection;
    
    vector<vector<int>> matrix_a = matrix;
    vector<vector<int>> matrix_b = matrix;


    if (x == 1 and y == 1){
        vector<vector<int>> matrix_c = matrix;
        vector<vector<int>> matrix_d = matrix;

        swap(matrix_a[1][1], matrix_a[0][1]);
        swap(matrix_b[1][1], matrix_b[2][1]);
        swap(matrix_c[1][1], matrix_c[1][0]);
        swap(matrix_d[1][1], matrix_d[1][2]);

        matrix_collection.push_back(matrix_a);
        matrix_collection.push_back(matrix_b);
        matrix_collection.push_back(matrix_c);
        matrix_collection.push_back(matrix_d);
    }
    else if (x == 0 and y == 0){
        swap(matrix_a[0][0], matrix_a[0][1]);
        swap(matrix_b[0][0], matrix_b[1][0]);

        matrix_collection.push_back(matrix_a);
        matrix_collection.push_back(matrix_b);
    }
    else if (x == 0 and y == 1){
        vector<vector<int>> matrix_c = matrix;

        swap(matrix_a[0][1], matrix_a[1][1]);
        swap(matrix_b[0][1], matrix_b[0][2]);
        swap(matrix_c[0][1], matrix_c[0][0]);

        matrix_collection.push_back(matrix_a);
        matrix_collection.push_back(matrix_b);
        matrix_collection.push_back(matrix_c);

    }
    else if (x == 0 and y == 2){
        swap(matrix_a[0][2], matrix_a[1][2]);
        swap(matrix_b[0][2], matrix_b[0][1]);

        matrix_collection.push_back(matrix_a);
        matrix_collection.push_back(matrix_b);
    }
    else if (x == 1 and y == 0){
        vector<vector<int>> matrix_c = matrix;

        swap(matrix_a[1][0], matrix_a[1][1]);
        swap(matrix_b[1][0], matrix_b[0][0]);
        swap(matrix_c[1][0], matrix_c[2][0]);

        matrix_collection.push_back(matrix_a);
        matrix_collection.push_back(matrix_b);
        matrix_collection.push_back(matrix_c);
    }
    else if (x == 1 and y == 2){
        vector<vector<int>> matrix_c = matrix;

        swap(matrix_a[1][2], matrix_a[1][1]);
        swap(matrix_b[1][2], matrix_b[0][2]);
        swap(matrix_c[1][2], matrix_c[2][2]);

        matrix_collection.push_back(matrix_a);
        matrix_collection.push_back(matrix_b);
        matrix_collection.push_back(matrix_c);

    }
    else if (x == 2 and y == 0){
        swap(matrix_a[2][0], matrix_a[2][1]);
        swap(matrix_b[2][0], matrix_b[1][0]);

        matrix_collection.push_back(matrix_a);
        matrix_collection.push_back(matrix_b);
    }
    else if (x == 2 and y == 1){
        vector<vector<int>> matrix_c = matrix;

        swap(matrix_a[2][1], matrix_a[1][1]);
        swap(matrix_b[2][1], matrix_b[2][0]);
        swap(matrix_c[2][1], matrix_c[2][2]);

        matrix_collection.push_back(matrix_a);
        matrix_collection.push_back(matrix_b);
        matrix_collection.push_back(matrix_c);
    }
    else if (x == 2 and y == 2){
        swap(matrix_a[2][2], matrix_a[2][1]);
        swap(matrix_b[2][2], matrix_b[1][2]);

        matrix_collection.push_back(matrix_a);
        matrix_collection.push_back(matrix_b);
    }

    // check heuristic of all matrix;
    int min = -1;
    int heu = INT_MAX;
    for (int i = 0; i <matrix_collection.size(); i++){
        auto pos = matrix_set.find(matrix_collection[i]);
        display(matrix_collection[i], goal_matrix, level, type);

        if (pos == matrix_set.end()){
            matrix_set.insert(matrix_collection[i]);
            int temp;

            if (type == 1){
                temp = checkHeuristic(matrix_collection[i], goal_matrix);
            }
            else{
                temp = checkheuristic(matrix_collection[i], goal_matrix);
            }

            if (temp < heu){
                min = i;
                heu = temp;
            }
        }
    }

    // return one with minimum heuristics
    return matrix_collection[min];
}

int main(){
    cout<<"\n\n\t\t 8 puzzle game";

    vector<vector<int>> matrix(3, vector<int>(3, 0));
    vector<vector<int>> goal_matrix(3, vector<int>(3, 0));

    set<vector<vector<int>>> matrix_set;
    matrix_set.insert(matrix);

    cout<<"\n\nEnter initial matrix : ";

    for(int i = 0; i <3; i++){
        for (int j = 0; j <3; j++){
            cin>>matrix[i][j];
        }
    }

    cout<<"\nEnter goal matrix : ";

    for(int i = 0; i <3; i++){
        for (int j = 0; j <3; j++){
            cin>>goal_matrix[i][j];
        }
    }

    int choice;
    cout<<"\nUser Manual : \n1. Manhattan\n2. Tile Difference\n3. Exit";
    cout<<"\n\nEnter your choice : ";
    cin>>choice;
    int loop = 0;

    if (choice == 1){
        int heuristic = checkHeuristic(matrix, goal_matrix);
        int level = 0;

        while (heuristic != 0){
            matrix = transform_matrix(matrix, goal_matrix, matrix_set, level+1, 1);
            heuristic = checkHeuristic(matrix, goal_matrix);
            level++;
        }
    }
    else if (choice == 2){
        int heuristic = checkheuristic(matrix, goal_matrix);
        int level = 0;

        while (heuristic != 0){
            matrix = transform_matrix(matrix, goal_matrix, matrix_set, level+1, 2);
            heuristic = checkheuristic(matrix, goal_matrix);
            level++;
        }
    }
    else if (choice == 3){
        cout<<"\nTerminated Successfully !!";
    }
    else{
        cout<<"\nInvalid choice so terminated !!";
    }

    return 0;
}