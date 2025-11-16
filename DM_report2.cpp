#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

const int N = 5;

void printMatrix(const vector<vector<int>>& R) {
    for (int i=0; i<N; i++) {
        cout<<"  ";
        for (int j=0; j<N; j++) {
            cout<<setw(2)<<R[i][j]<<" ";
        }
        cout<<endl;
    }
}

// 기능 1: 관계 행렬 입력 기능
void inputMatrix(vector<vector<int>>& R) {
    cout<<"Enter a 5x5 relation matrix (elements 0 or 1).\n";
    cout<<"Input 5 elements per row, separated by spaces.\n";
    for (int i=0; i<N; i++) {
        cout<<"Row "<<(i+1)<<" input: ";
        for (int j=0; j<N; j++) {
            cin>>R[i][j];
        }
    }
}

// 기능 2: 동치 관계 판별 기능
bool isReflexive(const vector<vector<int>>& R) {
    for (int i=0; i<N; i++) {
        if (R[i][i]==0) {
            return false;
        }
    }
    return true;
}

bool isSymmetric(const vector<vector<int>>& R) {
    for (int i=0; i<N; i++) {
        for (int j=i+1; j<N; j++) {
            if (R[i][j]!=R[j][i]) {
                return false;
            }
        }
    }
    return true;
}

bool isTransitive(const vector<vector<int>>& R) {
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            for (int k=0; k<N; k++) {
                if (R[i][j]==1 && R[j][k]==1) {
                    if (R[i][k]==0) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

// 기능 3: 동치 관계일 경우 동치류 출력 기능
void printEquivalenceClasses(const vector<vector<int>>& R) {
    cout<<"\nEquivalence Class Output:\n";
    vector<bool> visited(N, false);

    for (int i=0; i<N; i++) {
        if (visited[i]) {
            continue;
        }

        cout<<"  - Element "<<(i+1)<<"'s class: { ";
        
        for (int j=0; j<N; j++) {
            if (R[i][j]==1) {
                cout<<(j+1)<<" ";
                visited[j] = true;
            }
        }
        cout<<"}\n";
    }
}

// 기능 4: 폐포 구현 기능
void reflexiveClosure(vector<vector<int>>& R) {
    cout<<"\n[Reflexive Closure Creation]\n  (Before)\n";
    printMatrix(R);

    for (int i=0; i<N; i++) {
        R[i][i] = 1;
    }

    cout<<"  (After: Reflexive Closure)\n";
    printMatrix(R);
}

void symmetricClosure(vector<vector<int>>& R) {
    cout<<"\n[Symmetric Closure Creation]\n  (Before)\n";
    printMatrix(R);

    for (int i=0; i<N; i++) {
        for (int j=i+1; j<N; j++) {
            if (R[i][j]==1) {
                R[j][i] = 1;
            } else if (R[j][i]==1) {
                R[i][j] = 1;
            }
        }
    }

    cout<<"  (After: Symmetric Closure)\n";
    printMatrix(R);
}

void transitiveClosure(vector<vector<int>>& R) {
    cout<<"\n[Transitive Closure Creation]\n  (Before)\n";
    printMatrix(R);

    for (int k=0; k<N; k++) {
        for (int i=0; i<N; i++) {
            for (int j=0; j<N; j++) {
                if (R[i][k]==1 && R[k][j]==1) {
                    R[i][j] = 1;
                }
            }
        }
    }

    cout<<"  (After: Transitive Closure)\n";
    printMatrix(R);
}

// 추가 기능: 빈대칭성검사
bool isAntiSymmetric(const vector<vector<int>>& R) {
    for (int i=0; i<N; i++) {
        for (int j=i+1; j<N; j++) {
            if (R[i][j]==1 && R[j][i]==1) {
                return false;
            }
        }
    }
    return true;
}


int main() {
    vector<vector<int>> R(N, vector<int>(N));

    inputMatrix(R);

    bool r = isReflexive(R);
    bool s = isSymmetric(R);
    bool t = isTransitive(R);

    cout<<"\n--- Equivalence Relation Check ---\n";
    cout<<"1. Reflexive: "<<(r ? "O" : "X")<<endl;
    cout<<"2. Symmetric: "<<(s ? "O" : "X")<<endl;
    cout<<"3. Transitive: "<<(t ? "O" : "X")<<endl;

    if (r && s && t) {
        cout<<"\n>> Result: The input relation is an equivalence relation.\n";
        printEquivalenceClasses(R);
    } 
    else {
        cout<<"\n>> Result: The input relation is NOT an equivalence relation.\n";
    
        vector<vector<int>> closureR = R;
    
        if (!r) {
            reflexiveClosure(closureR);
        }
    
        if (!s) {
            symmetricClosure(closureR);
        }
        
        transitiveClosure(closureR);
    
        cout<<"\nFinal Equivalence Closure Matrix Relation Check:\n";
        bool r_new = isReflexive(closureR);
        bool s_new = isSymmetric(closureR);
        bool t_new = isTransitive(closureR);
    
        cout<<"1. Reflexive: "<<(r_new ? "O" : "X")<<endl;
        cout<<"2. Symmetric: "<<(s_new ? "O" : "X")<<endl;
        cout<<"3. Transitive: "<<(t_new ? "O" : "X")<<endl;
    
        if (r_new && s_new && t_new) {
            cout<<"\n>> Final Result: The equivalence closure is now an equivalence relation.\n";
            printEquivalenceClasses(closureR);
        } else {
            cout<<"\n>> Error: Even after closure operations, this is not an equivalence relation.\n";
        }
    }

    cout<<"\n--- Partial Order Relation Check ---\n";
    bool as = isAntiSymmetric(R);
  
    cout<<"1. Reflexive: "<<(r ? "O" : "X")<<endl;
    cout<<"2. Anti-symmetric: "<<(as ? "O" : "X")<<endl;
    cout<<"3. Transitive: "<<(t ? "O" : "X")<<endl;

    if (r && as && t) {
        cout<<"\n>> Result: The input relation is a Partial Order (POSET).\n";
    } else {
        cout<<"\n>> Result: The input relation is NOT a Partial Order.\n";
    }

    return 0;
}
