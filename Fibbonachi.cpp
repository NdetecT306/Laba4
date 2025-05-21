#include <iostream>
#include <vector>
using namespace std;
vector<int> Fibonacci(int j, int k, int k0, int k1, int m, char operation, int length) 
{
    vector<int> answer(length); 
    answer[0] = k0; 
    answer[1] = k1;
    for (int i = 2; i < length; ++i) {
        switch (operation) {
        case '+':
            answer[i] = (answer[i - j] + answer[i - k]) % m;
            break;
        case '-':
            answer[i] = (answer[i - j] - answer[i - k] + m) % m;
            break;
        case '*':
            answer[i] = (answer[i - j] * answer[i - k]) % m;
            break;
        case 'XOR': 
            answer[i] = answer[i - j] ^ answer[i - k];
            break;
        default:
            cout << "Неизвестная операция." << endl;
            break;
        }
    }
    return answer;
}
int main() {
    setlocale(LC_ALL, "rus");
    int j, k, k0, k1, m, length = 10;
    char operation;
    cout << "Введите j: ";
    cin >> j;
    cout << "Введите k: ";
    cin >> k;
    cout << "Введите k0: ";
    cin >> k0;
    cout << "Введите k1: ";
    cin >> k1;
    cout << "Введите m: ";
    cin >> m;
    cout << "Введите операцию (+, -, *, XOR): "; 
    cin >> operation;
    if (j >= length || k >= length || j >= k || j < 0) 
    {
        cout << "Ошибка ввода значений." << endl;
        return 1; 
    }
    vector<int> answer = Fibonacci(j, k, k0, k1, m, operation, length);
    cout << "Результат: ";
    for (auto i : answer) 
    {
        cout << i << " ";
    }
    return 0;
}
