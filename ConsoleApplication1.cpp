#include <iostream>
#include <vector>
#include<ctime>
#include <cstdlib>

struct Point {
    bool mine;
    bool flag;
    bool open;
    int rydom;
};

class Saper {
public:
    Saper(int s, int c);
    void hod(char f, int x, int y);
    int resultat();
private:
    void inicialization();
    void minaa(size_t x, size_t y);
    void mina1(size_t x, size_t y);
    void get_minefield();
    const int shirina;
    int colichestvo_min;
    std::vector<std::vector<Point>> minefield;
    int flagi = 0;
    int sostoinie = 0;
};

Saper::Saper(int s, int c) : shirina(s), colichestvo_min(c) {
    inicialization();
}
int Saper::resultat() {
    return sostoinie;
}
void Saper::inicialization() {
    minefield.resize(shirina, std::vector<Point>(shirina));
    int d = 0;
    while (d < colichestvo_min) {
        size_t i = rand() % shirina;
        size_t j = rand() % shirina;
        if (!minefield[i][j].mine) {
            minefield[i][j].mine = true;
            ++d;
            minaa(i, j);
        }
    }
}
void Saper::minaa(size_t x, size_t y) {
    for (int i = -1; i < 2;++i) {
        for (int j = -1; j < 2;++j) {
            if ((x + i < shirina) && (x + i >= 0) && (y + j >= 0) && (y + j < shirina)) {
                minefield[unsigned(x + i)][unsigned(y + j)].rydom++;
            }
        }
    }
}
void Saper::mina1(size_t x, size_t y) {
    if (x >= shirina || y >= shirina) {
        return;
    }
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            size_t newX = x + i;
            size_t newY = y + j;
            if (newX < shirina && newY < shirina && minefield[newX][newY].open == false && minefield[x][y].mine == false && minefield[x][y].rydom == 0) {
                mina1(newX, newY);
            }
            if (minefield[x][y].mine == false) {
                minefield[x][y].open = true;
            }
        }
    }
}
void Saper::get_minefield() {
    for (size_t i = 0; i != unsigned(shirina);++i) {
        for (size_t j = 0; j != unsigned(shirina);++j) {
            if (minefield[i][j].flag == true) {
                std::cout << "f" << " ";
            }
            if (minefield[i][j].flag == false && minefield[i][j].open == false) {
                std::cout << "-" << " ";
            }
            if (minefield[i][j].flag == false && minefield[i][j].mine == false && minefield[i][j].open == true) {
                std::cout << minefield[i][j].rydom << " ";
            }

        }
        std::cout << "\n";
    }
}
void Saper::hod(char f, int x, int y) {
    
    switch (f)
    {
    case 'f':
        minefield[x - 1][y - 1].flag = true;
        if (minefield[x - 1][y - 1].mine == true) {
            ++flagi;
        }
        break;
    case 'g':
        if (minefield[x - 1][y - 1].mine == true) {
            --sostoinie;
        }
        else {
            minefield[x - 1][y - 1].open = true;
            minefield[x - 1][y - 1].flag = false;
            if (minefield[x - 1][y - 1].rydom == 0) {
                mina1(x - 1, y - 1);
            }
        }
        break;
    }
    if (flagi == colichestvo_min) {
        ++sostoinie;
    }
    get_minefield();
    

}
int main() {
    setlocale(LC_ALL, "Russian");
    std::srand(std::time(0));
    int q1 = 0;
    int q2 = 0;
    char q3 = 'f';

    std::cout << "Введи размер поля+ количество мин\n";
    std::cin >> q1 >> q2;
    Saper c(q1, q2);
    std::cout << "Вводишь сначала символ g - если хочешь открыть  клетку, либо символ f - если хочешь поставить флаг + 2 координаты x y \n";
    while (c.resultat() == 0) {
        std::cin >> q3 >> q2 >> q1;
        c.hod(q3, q2, q1);
    }
    if (c.resultat() == 1) {
        std::cout << "Ты выиграл";
    }
    else {
        std::cout << "Ты проиграл";
    }
}