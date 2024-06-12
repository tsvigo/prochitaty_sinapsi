//#include <QCoreApplication>

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

//    return a.exec();
//}
//###########################################################################
#include <QCoreApplication>
#include <QDataStream>
#include <QFile>
#include <iostream>
#include <vector>

// Функция для чтения чисел из бинарного файла
std::vector<unsigned long long> readNumbersFromFile2(const QString &fileName, size_t count)
{
    std::vector<unsigned long long> numbers;
    numbers.reserve(count);

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Failed to open file for reading." << std::endl;
        return numbers;
    }

    QDataStream in(&file);
    unsigned long long number;
    while (numbers.size() < count && !in.atEnd()) {
        in >> number;
        numbers.push_back(number);
    }

    file.close();
    return numbers;
}

// Главная функция
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const QString fileName
        = "/home/viktor/my_projects_qt_2/sgenerirovaty_sinapsi/random_sinapsi.bin"; // Имя бинарного файла
    const size_t numberCount = 10105;

    // Чтение чисел из бинарного файла
    std::vector<unsigned long long> readNumbers = readNumbersFromFile2(fileName, numberCount);

    // Проверка, что прочитано правильное количество чисел
    if (readNumbers.size() != numberCount) {
        std::cerr << "File does not contain the expected number of numbers." << std::endl;
        return 1;
    }

    // Вывод чисел в консоль по числу на строку
    for (const auto &number : readNumbers) {
        std::cout << number << std::endl;
    }

    return 0;
}
