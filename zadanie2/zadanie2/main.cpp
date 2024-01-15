#include "chunk.h"
#include <iostream>
using namespace std;
int main() {
    // Создаем объект ChunkList для тестирования
    fefu_laboratory_two::ChunkList<int, 3> chunkList;

    // Добавляем элементы
    chunkList.insert(1);
    chunkList.insert(2);
    chunkList.insert(3);

    // Выводим значения в каждом чанке
    std::cout << "Values in Chunks:\n";
    for (const auto& chunk : chunkList) {
        for (const auto& value : chunk.data) {
            std::cout << value << ' ';
        }
        std::cout << '\n';
    }
    std::cout << std::endl;

    // Удаляем элемент
    chunkList.erase(2);

    // Выводим значения в каждом чанке после удаления
    std::cout << "Values in Chunks after Erasure:\n";
    for (const auto& chunk : chunkList) {
        for (const auto& value : chunk.data) {
            std::cout << value << ' ';
        }
        std::cout << '\n';
    }
    std::cout << std::endl;

    return 0;
}
