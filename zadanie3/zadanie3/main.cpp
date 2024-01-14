#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;
class Player
{
public:
    int x, y;
    int coins;

    Player(int startX, int startY) : x(startX), y(startY), coins(0) {}

    void move(int dx, int dy)
    {
        x += dx;
        y += dy;
    }

    void collectCoin() {
        coins++;
    }
};

class Map 
{
public:
    static const int numLevels = 2;
    static const int width = 20;
    static const int height = 10;
    char levels[numLevels][height][width];

    Map()
    {
        // Инициализация уровней
        for (int k = 0; k < numLevels; ++k) 
        {
            for (int i = 0; i < height; ++i) 
            {
                for (int j = 0; j < width; ++j) 
                {
                    if (i == 0 || i == height - 1 || j == 0 || j == width - 1) 
                        levels[k][i][j] = '#';
                    
                    else 
                        levels[k][i][j] = '.';
                    
                }
            }
        }
    }

    void printMap(const Player& player, int level) const 
    {
        system("cls");

        for (int i = 0; i < height; ++i) 
        {
            for (int j = 0; j < width; ++j) 
            {
                if (player.x == j && player.y == i) 
                    cout << '@';
            
                else 
                   cout << levels[level][i][j];
            }
           cout << endl;
        }
      cout << "Coins collected: " << player.coins << endl;
    }

    bool isWall(int x, int y, int level) const { return levels[level][y][x] == '#'; }

    bool isCoin(int x, int y, int level) const { return levels[level][y][x] == 'C'; }

    bool isExit(int x, int y, int level) const { return levels[level][y][x] == '>'; }

    void placeCoin(int x, int y, int level) { levels[level][y][x] = 'C'; }

    void placeExit(int x, int y, int level) { levels[level][y][x] = '>'; }

    void removeCoin(int x, int y, int level) { levels[level][y][x] = '.'; }

    void placeRandomObjects(int level) {
        // Случайное размещение монет
        for (int i = 0; i < 2; ++i) 
        {
            int coinX, coinY;
            do 
            {
                coinX = 1 + rand() % (width - 2);
                coinY = 1 + rand() % (height - 2);
            } while (isWall(coinX, coinY, level) || isCoin(coinX, coinY, level) || isExit(coinX, coinY, level));

            placeCoin(coinX, coinY, level);
        }

        // Случайное размещение ограждений
        for (int i = 0; i < 3; ++i)
        {
            int wallX, wallY;
            do 
            {
                wallX = 1 + rand() % (width - 2);
                wallY = 1 + rand() % (height - 2);
            } while (isWall(wallX, wallY, level) || isCoin(wallX, wallY, level) || isExit(wallX, wallY, level) || isBlockedExit(wallX, wallY, level));

            levels[level][wallY][wallX] = '#';
        }
    }

  

    bool isBlockedExit(int x, int y, int level) const
    {
        if (levels[level][y][x] == '>') 
        {
            return (
                isWall(x - 1, y, level) && isWall(x + 1, y, level) &&
                isWall(x, y - 1, level) && isWall(x, y + 1, level)
                );
        }
        return false;
    }
};

int main() 
{
    cout << "Hello! Change your language to English please!" << endl;
    cout << "When you change, press any key...";
   _getch();
    std::srand(std::time(0));

    Player player(1, 1);
    Map map;

    int currentLevel = 0;
    map.placeExit(19, 5, currentLevel);
    
    map.placeRandomObjects(currentLevel);

    while (true) 
    {
        map.printMap(player, currentLevel);
        char move = _getch();

        int dx = 0, dy = 0;

        switch (move) {
        case 'w': dy = -1; break;
        case 'a': dx = -1; break;
        case 's': dy = 1; break;
        case 'd': dx = 1; break;
        }

        if (!map.isWall(player.x + dx, player.y + dy, currentLevel)) 
            player.move(dx, dy);
        

        if (map.isCoin(player.x, player.y, currentLevel)) 
        {
            player.collectCoin();
            map.removeCoin(player.x, player.y, currentLevel);
        }

        if (map.isExit(player.x, player.y, currentLevel)) 
        {
            if (currentLevel < Map::numLevels - 1)
            {
                currentLevel++;
               
                map.placeRandomObjects(currentLevel);
                map.placeExit(13, 9, currentLevel);
            }
            else
            {
                std::cout << "Congratulations! You completed all levels." << std::endl;
                return 0;
            }
        }

        
    }
}
