#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Funkcja do wyświetlania planszy
void wyswietlPlansze(const vector<vector<char>>& plansza) {
    cout << "\n\n";
    for (const auto& wiersz : plansza) {
        cout << " " << wiersz[0] << " " << "|";
        cout << " " << wiersz[1] << " " << "|";
        cout << " " << wiersz[2] << " "; 
        if (&wiersz != &plansza.back()) {
            cout << "\n---+---+---\n";
        }
        
    }
    cout << "\n\n";
}

// Sprawdza, czy ktoś wygrał
bool sprawdzWygrana(const vector<vector<char>>& plansza, char gracz) {
    for (int i = 0; i < 3; i++) {
        if ((plansza[i][0] == gracz && plansza[i][1] == gracz && plansza[i][2] == gracz) ||
            (plansza[0][i] == gracz && plansza[1][i] == gracz && plansza[2][i] == gracz)) {
            return true;
        }
    }
    if ((plansza[0][0] == gracz && plansza[1][1] == gracz && plansza[2][2] == gracz) ||
        (plansza[0][2] == gracz && plansza[1][1] == gracz && plansza[2][0] == gracz)) {
        return true;
    }
    return false;
}

// Sprawdza, czy jest remis
bool remis(const vector<vector<char>>& plansza) {
    for (const auto& wiersz : plansza) {
        for (char pole : wiersz) {
            if (pole == ' ') return false;
        }
    }
    return true;
}

// Funkcja AI komputera - wybiera losowy wolny ruch
void ruchKomputera(vector<vector<char>>& plansza) {
    vector<pair<int, int>> wolne_pola;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (plansza[i][j] == ' ') {
                wolne_pola.push_back({i, j});
            }
        }
    }

    if (!wolne_pola.empty()) {
        srand(time(0));
        auto ruch = wolne_pola[rand() % wolne_pola.size()];
        plansza[ruch.first][ruch.second] = 'O';
    }
}

int main() {
    vector<vector<char>> plansza(3, vector<char>(3, ' '));
    char gracz = 'X';
    int x, y;
    bool trybGraczVsKomputer;

    cout << "Wybierz tryb gry: (1) Gracz vs Gracz, (2) Gracz vs Komputer: ";
    int wybor;
    cin >> wybor;
    trybGraczVsKomputer = (wybor == 2);

    while (true) {
        wyswietlPlansze(plansza);

        if (gracz == 'X' || !trybGraczVsKomputer) {  // Gracz wykonuje ruch
            cout << "Gracz " << gracz << " - podaj rząd i kolumnę (0-2): ";
            cin >> x >> y;

            if (x < 0 || x > 2 || y < 0 || y > 2 || plansza[x][y] != ' ') {
                cout << "❌ Nieprawidłowy ruch! Spróbuj ponownie.\n";
                continue;
            }
            plansza[x][y] = gracz;
        } else {  // Komputer wykonuje ruch
            cout << "💻 Komputer wykonuje ruch...\n";
            ruchKomputera(plansza);
        }

        if (sprawdzWygrana(plansza, gracz)) {
            wyswietlPlansze(plansza);
            cout << "🎉 Gracz " << gracz << " wygrywa!\n";
            break;
        }

        if (remis(plansza)) {
            wyswietlPlansze(plansza);
            cout << "🤝 Remis!\n";
            break;
        }

        gracz = (gracz == 'X') ? 'O' : 'X';
    }

    return 0;
}
