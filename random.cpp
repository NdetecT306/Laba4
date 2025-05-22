#include<iostream>
#include<vector>
#include<random>
#include<algorithm>
#include<numeric>
#include <chrono>
#include <map>
using namespace std;
vector<int> RandomNumbers(int n, int start, int end)
{
    vector<int> Vec(n);
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    ranlux24_base generation(seed);
    uniform_int_distribution<int> distribution(start, end);
    for (int i = 0; i < n; ++i) {
        Vec[i] = distribution(generation);
    }
    return Vec;
}
vector<char> SpecialGeneration(int n) 
{
    vector<char> Vec(n);
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    ranlux24_base generation(seed);
    uniform_int_distribution<> Distribution(0, 35);
    for (int i = 0; i < n; ++i) {
        int symbolIndex = Distribution(generation);
        if (symbolIndex < 10) {
            Vec[i] = symbolIndex + '0';
        }
        else {
            Vec[i] = (symbolIndex - 10) + 'a';
        }
    }
    return Vec;
}
vector<int> Sort(vector<int> Vec, int n)
{
    for (int k = 0; k < n - 1; k++)
    {
        int index = k;
        for (int i = k + 1; i < n;i++)
        {
            if (Vec[i] >= Vec[index])
            {
                index = i;
            }
        }
        int t = Vec[k];
        Vec[k] = Vec[index];
        Vec[index] = t;
    }
    return Vec;
}
int main()
{
    setlocale(LC_ALL, "rus");
    int n1;
    cout << "Введите количество элементов первого массива: ";
    cin >> n1;
    if (n1 < 10) 
    {
        cout << "Число не соответствует условиям";
        return 1;
    }
    int start_1 = 150;
    int end_1 = 300;
    vector<int> Vec1 = RandomNumbers(n1, start_1, end_1);
    cout << "Пункт 1: ";
    for (int n : Vec1)
    {
        cout << n << " ";
    }
    int best_start = -1; 
    int best_length = 0;
    for (int i = 0; i < n1; ++i)
    {
        int current_start = i;
        int current_length = 1;
        while (i + 1 < n1 && Vec1[i + 1] <= Vec1[i]) {
            current_length++;
            i++;  
        }
        if (current_length >= best_length) 
        {  
            best_length = current_length;
            best_start = current_start;
        }
    }
    cout << endl << "Пункт 2: ";
    if (best_start != -1) 
    {
        for (int i = best_start; i < best_start + best_length; ++i)
        {
            cout << Vec1[i] << " ";
        }
    }
    else 
    {
        cout << "В массиве нет убывающих последовательностей";
    }
    double sum = accumulate(Vec1.begin(), Vec1.end(), 0);
    double srznach = sum / n1;
    vector<int> Vec3;
    for (int n : Vec1)
    {
        if (n < srznach)
        {
            Vec3.push_back(n);
        }
    }
    cout << endl << "Пункт 3: ";
    for (int n : Vec3)
    {
        cout << n << " ";
    }

    int n2;
    cout << endl << "Введите количество элементов второго массива: ";
    cin >> n2;
    if (n2 < 5) 
    {
        cout << "Число не соответствует условиям";
        return 1;
    }
    vector<char> Vec4 = SpecialGeneration(n2);
    cout << "Пункт 4: " << endl;
    cout << "Исходный массив: ";
    for (auto n: Vec4) 
    {
        cout << n << " ";
    }
    cout << endl;
    char first = Vec4[0];
    char second = Vec4[1];
    for (int i = 0; i < n2 - 2; ++i) 
    {
        Vec4[i] = Vec4[i + 2];
    }
    Vec4[n2 - 2] = first;
    Vec4[n2 - 1] = second;
    cout << "Измененный массив: ";
    for (auto n: Vec4) {
        cout << n << " ";
    }
    int start_5 = 100; 
    int end_5 = 900;
    vector<int> Vec5 = RandomNumbers(n1, start_5, end_5);
    Vec5 = Sort(Vec5, n1);
    cout << endl << "Пункт 5: ";
    for (int n : Vec5)
    {
        cout << n << " ";
    }
    map<int, int> digitCounts;
    for (int n : Vec5) {
        string numStr = to_string(n);
        for (char c : numStr) {
            int digit = c - '0'; // Преобразуем символ цифры в число
            digitCounts[digit]++;
        }
    }
    cout << endl;
    for (int i = 0; i <= 9; ++i) {
        cout << "Цифра " << i << ": " << digitCounts[i] << " раз(а)" << endl;
    }
}


