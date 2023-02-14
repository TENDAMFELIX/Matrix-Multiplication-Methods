#include <bits/stdc++.h>
using namespace std;
#include <chrono>
using namespace std::chrono;
void Add_Partition(vector<vector<int>> A, vector<vector<int>> B, vector<vector<int>> &Result, int Index)
{
    for (int i = 0; i < Index; i++)
    {
        for (int j = 0; j < Index; j++)
        {
            Result[i][j] = A[i][j] + B[i][j];
        }
    }
}
vector<vector<int>> MatrixMultiplication(vector<vector<int>> A, vector<vector<int>> B)
{
    int N1 = A.size();
    int M1 = A[0].size();
    int N2 = B.size();
    int M2 = B[0].size();
    vector<vector<int>> Result(N1, vector<int>(M2));
    if (M1 == 1)
        Result[0][0] = A[0][0] * B[0][0];
    else
    {
        int Split = M1 / 2;
        vector<vector<int>> Result_00(Split, vector<int>(Split));
        vector<vector<int>> Result_01(Split, vector<int>(Split));
        vector<vector<int>> Result_10(Split, vector<int>(Split));
        vector<vector<int>> Result_11(Split, vector<int>(Split));
        vector<vector<int>> A_00(Split, vector<int>(Split));
        vector<vector<int>> A_01(Split, vector<int>(Split));
        vector<vector<int>> A_10(Split, vector<int>(Split));
        vector<vector<int>> A_11(Split, vector<int>(Split));
        vector<vector<int>> B_00(Split, vector<int>(Split));
        vector<vector<int>> B_01(Split, vector<int>(Split));
        vector<vector<int>> B_10(Split, vector<int>(Split));
        vector<vector<int>> B_11(Split, vector<int>(Split));
        for (int i = 0; i < Split; i++)
        {
            for (int j = 0; j < Split; j++)
            {
                A_00[i][j] = A[i][j];
                A_01[i][j] = A[i][j + Split];
                A_10[i][j] = A[i + Split][j];
                A_11[i][j] = A[i + Split][j + Split];
                B_00[i][j] = B[i][j];
                B_01[i][j] = B[i][j + Split];
                B_10[i][j] = B[i + Split][j];
                B_11[i][j] = B[i + Split][j + Split];
            }
        }
        Add_Partition(MatrixMultiplication(A_00, B_00), MatrixMultiplication(A_01, B_10), Result_00, Split);
        Add_Partition(MatrixMultiplication(A_00, B_01), MatrixMultiplication(A_01, B_11), Result_01, Split);
        Add_Partition(MatrixMultiplication(A_10, B_00), MatrixMultiplication(A_11, B_10), Result_10, Split);
        Add_Partition(MatrixMultiplication(A_10, B_01), MatrixMultiplication(A_11, B_11), Result_11, Split);
        for (int i = 0; i < Split; i++)
        {
            for (int j = 0; j < Split; j++)
            {
                Result[i][j] = Result_00[i][j];
                Result[i][j+Split] = Result_01[i][j];
                Result[i+Split][j] = Result_10[i][j];
                Result[i+Split][j+Split] = Result_11[i][j];
            }
        }
        Result_00.clear();
        Result_01.clear();
        Result_10.clear();
        Result_11.clear();
        A_00.clear();
        A_01.clear();
        A_10.clear();
        A_11.clear();
        B_00.clear();
        B_01.clear();
        B_10.clear();
        B_11.clear();
    }
    return Result;
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
void Inputffile(int N, int M, vector<vector<int>> &Matrix, ifstream &MyFile)
{
    int i = 0;
    string Row;
    while (getline(MyFile, Row) && i < N)
    {
        int j = 0;
        stringstream Str(Row);
        string Num;
        while (j < M && getline(Str, Num, ' '))
        {
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
    Inputffile(N1, M1, Matrix1, MyFile);
    MyFile.close();
    MyFile.open("Matrix2.txt");
    Inputffile(N2, M2, Matrix2, MyFile);
    vector<vector<int>> AnsMatrix(N1, vector<int>(M2));
    auto start = high_resolution_clock::now();
    AnsMatrix = MatrixMultiplication(Matrix1, Matrix2);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << fixed << "Time Taken In MilliSecond : " << (double)duration.count() / 1000 << setprecision(9) << endl;
}