#include <bits/stdc++.h>
using namespace std;
#include <chrono>
using namespace std::chrono;
vector<vector<int>> MatrixMultiplication(vector<vector<int>> &Matrix1, vector<vector<int>> &Matrix2)
{
    vector<vector<int>> AnsMatrix(Matrix1.size(), vector<int>(Matrix2[0].size()));
    for (int i = 0; i < Matrix1.size(); i++)
    {
        for (int j = 0; j < Matrix1[0].size(); j++)
        {
            int Ans = 0;
            for (int k = 0; k < Matrix2[0].size(); k++)
                Ans += Matrix1[i][k] * Matrix2[k][j];
            AnsMatrix[i][j] = Ans;
        }
    }
    cout << sizeof(AnsMatrix) << endl;
    return AnsMatrix;
}
void PrintMatrix(vector<vector<int>> &Matrix)
{
    for (int i = 0; i < Matrix.size(); i++)
    {
        for (int j = 0; j < Matrix[0].size(); j++)
            cout << Matrix[i][j] << " ";
        cout << endl;
    }
}
void Inputffile(int N , int M , vector<vector<int>>&Matrix , ifstream& MyFile){
    int i = 0;
    string Row;
    while(getline(MyFile , Row) && i < N){
        int j = 0;
        stringstream Str(Row);
        string Num;
        while(j < M && getline(Str , Num , ' ')){
            Matrix[i][j] = stoi(Num);
            j++;
        }
        i++;
    }
}
int main()
{
    srand(time(0));
    int N1, M1, N2, M2;
    cout << "Dimension Of 1 Matrix : ";
    cin >> N1 >> M1;
    cout << "Dimension Of 2 Matrix : ";
    cin >> N2 >> M2;
    if (M1 != N2)
    {
        cout << "Enter Valid Matrices :(";
        return 0;
    }
    vector<vector<int>> Matrix1(N1, vector<int>(M1)), Matrix2(N2, vector<int>(M2));
    ifstream MyFile;
    MyFile.open("Matrix1.txt");
    Inputffile(N1 , M1 , Matrix1 , MyFile);
    MyFile.close();
    MyFile.open("Matrix2.txt");
    Inputffile(N2 , M2 , Matrix2 , MyFile);
    vector<vector<int>> AnsMatrix(N1, vector<int>(M2));
    auto start = high_resolution_clock::now();
    AnsMatrix = MatrixMultiplication(Matrix1, Matrix2);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << fixed << "Time Taken In MilliSecond : " << (double)duration.count() / 1000 << setprecision(9) << endl;
}