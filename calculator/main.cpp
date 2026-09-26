#include <cctype>
#include <iostream>
#include <vector>
#include <string>

const int MIN_ARGS = 5;
const int MAX_ARGS = 7;
const std::string OP_MINUS = "minus";
const std::string OP_PLUS = "plus";

void help() {
    const char* text = "выбор операции: -o --operation [операция]\nДоступные операции: plus(Сложение), minus(Вычитание)";
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
    if (argc == 1) {
        help();
        return -1;
    }
    else if (argc > MAX_ARGS) {
        std::cout << "Введено слишком много чисел!" << '\n';
        return -1;
    }
    else if (argc < 3) {
        const std::string flag = argv[1];
        if ((flag != "-o" && flag != "--operation")) {
            std::cout << "Неверный флаг" << '\n';
            return -1;
        }
        std::cout << "Вы не ввели тип операции!" << '\n';
        return -1;
    }
    if (argc < 4) {
        const std::string operation = argv[2];
        if (operation != OP_PLUS && operation != OP_MINUS) {
            std::cout << "Неизвестная операция: " << operation << '\n';
            return -1;
        }        
    }
    if (argc < MIN_ARGS) {
        std::cout << "Введено слишком мало чисел!" << '\n';
        return -1;
    }
    std::vector<int> numbers;

    for (int i = 3; i < argc; ++i) {
        std::string num = argv[i];
        if (is_valid_number(num)) {
            numbers.push_back(std::stoi(num));
        }
        else {
            std::cout << "Введено некорректное число!" << '\n';
            return -1;
        }
    }

    int result{};
    const std::string operation = argv[2];

    if (operation == OP_PLUS) {
        result = addition(numbers);
    }
        else {
        result = subtraction(numbers);
    }
    std::cout << "Результат: " << result << '\n';
    return 0;
}