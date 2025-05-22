#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;
vector<int> ranking(const string& s, const vector<string>& candidates, int n) {
    vector<int> decision;
    stringstream ss(s);
    string name;
    while (ss >> name) {
        bool found = false;
        for (int i = 0; i < n; ++i) {
            if (candidates[i] == name) {
                decision.push_back(i); 
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Кандидат с именем " << name << " не найден." << endl;
            return {};
        }
        if ( ss.peek() != ' ' && !ss.eof()) {
            cout << "Между кандидатами должен быть пробел." << endl;
            return {};
        }
    }
    if (decision.size() != n) {
        cout << "Неверное количество кандидатов в ранжировании." << endl;
        return {};
    }
    vector<int> sorted = decision;
    sort(sorted.begin(), sorted.end());
    for (int i = 0; i + 1 < sorted.size(); ++i) {
        if (sorted[i] == sorted[i + 1]) {
            cout << "Все кандидаты должны быть уникальны." << endl;
            return {};
        }
    }
    return decision;
}
int borda(const vector<vector<int>>& votes, int n) {
    vector<int> answer(n);
    for (const auto& vote : votes) {
        for (int i = 0; i < n; ++i) {
            answer[vote[i]] += n - 1 - i;
        }
    }
    int max = *max_element(answer.begin(), answer.end());
    int win = -1;
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (answer[i] == max) {
            win = i;
            count++;
        }
    }
    if (count == 1) {
        return win; 
    }
    else {
        return -1; 
    }
}
int condorcet(const vector<vector<int>>& votes, int n) {
    vector<vector<int>> wins(n, vector<int>(n, 0));
    for (const auto& vote : votes) {
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                wins[vote[i]][vote[j]]++;
                wins[vote[j]][vote[i]]--;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        bool condorcet = true;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if (wins[i][j] < 0) {
                condorcet = false;
                break;
            }
        }
        if (condorcet) {
            return i; 
        }
    }
    return -1; 
}
int main() {
    setlocale(LC_ALL, "rus");
    int n, k;
    cout << "Введите количество кандидатов: ";
    cin >> n;
    cin.ignore(); 
    vector<string> candidates(n);
    for (int i = 0; i < n; ++i) {
        cout << "Введите имя " << i + 1 << " кандидата: ";
        getline(cin, candidates[i]);
    }
    vector<string> sorted = candidates;
    sort(sorted.begin(), sorted.end());
    for (size_t i = 0; i + 1 < sorted.size(); ++i) {
        if (sorted[i] == sorted[i + 1]) {
            cout << "Имена кандидатов должны быть уникальны." << endl;
            return 1;
        }
    }
    cout << "Введите количество избирателей: ";
    cin >> k;
    cin.ignore(); 
    vector<vector<int>> votes(k, vector<int>(n));
    cout << "Введите ранжирование избирателя:" << endl;
    for (int i = 0; i < k; ++i) {
        cout << "Голос избирателя " << i + 1 << ": ";
        string s;
        getline(cin, s);
        vector<int> decision = ranking(s, candidates, n);
        if (decision.empty()) {
            cout << "Ошибка при вводе ранжирования. Повторите попытку." << endl;
            --i; 
        }
        else {
            votes[i] = decision;
        }
    }
    int bordaRes = borda(votes, n);
    if (bordaRes != -1) {
        cout << "Победитель методом Борда: " << candidates[bordaRes] << endl;
    }
    else {
        cout << "Метод Борда: Ничья" << endl;
    }
    int condorcetRes = condorcet(votes, n);
    if (condorcetRes != -1) {
        cout << "Победитель методом Кондорсе: " << candidates[condorcetRes] << endl;
    }
    else {
        cout << "Метод Кондорсе: Победитель не определен" << endl;
    }
    return 0;
}
