#include <cctype>
#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>

void help() {
    const char* text = "main -o/--operation [plus/minus] -- [числа]";
    std::cout << text << '\n';
}

int addition(const std::vector<int>& numbers) {
    int result = 0;
    for (auto num : numbers) {
        result += num;
    }
    return result;
}

int subtraction(const std::vector<int>& numbers) {
    int result = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        result -= numbers[i];
    }
    return result;
}

bool is_valid_number(const std::string& number) {
    if (number.empty()) {
        return false;
    }
    else if (number.size() == 1 && (number[0] == '+' || number[0] == '-')) {
        return false;
    }
    if (number[0] == '-' || isdigit(number[0])) {
        for (size_t i = 1; i < number.size(); ++i) {
            if (!isdigit(number[i])) {
                return false;
            }
        }
        return true;
    }
    return false;
}

int main(int argc, char** argv)
{
    const char* operations = ":ho:";
    std::string operation;
    int opt;

    struct option long_options[] = {
        {"help", no_argument, nullptr, 'h'},
        {"operation", required_argument, nullptr, 'o'},
        {0, 0, 0, 0}
    };
    
    while ((opt = getopt_long(argc, argv, operations, long_options, nullptr)) != -1) {
        switch (opt)
        {
        case 'h':
            help();
            return 0;
        case 'o':
            operation = optarg;
            break;
        case ':':
            std::cout << "Не введён аргумент для опции: " << char(optopt) << '\n';
            help();
            return 1;
        case '?':
            std::cout << "Неизвестная опция: " << char(optopt) << '\n';
            help();
            return 1;
        }
    }
    if (operation.empty()) {
        std::cout << "Не указана операция!\n";
        help();
        return 1;
    }
    if (operation != "plus" && operation != "minus") {
        std::cout << "Неизвестная операция: " << operation << '\n';
        help();
        return 1;
    }
    
    if (argc - optind < 2) {
        std::cout << "Передано недостаточно операндов!\n";
        return 1;
    }
    else if (argc - optind > 4) {
        std::cout << "Передано больше операндов, чем требуется!\n";
        return 1;
    }
    std::vector<int> numbers;
    for (int i = optind; i < argc; ++i) {
        std::string num = argv[i];
        if (!is_valid_number(num)) {
            std::cout << "Введено некорректное число: " << num << '\n';
            return 1;
        }
        numbers.push_back(std::stoi(num));
    }
    if (operation == "plus") {
        std::cout << "Результат: " << addition(numbers) << '\n';
    }
    else {
        std::cout << "Результат: " << subtraction(numbers) << '\n';
    }
    return 0;
}