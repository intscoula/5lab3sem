#include <iostream>
#include <string>
#include <regex>
#include <algorithm> // Для std::remove_if

// Базовый класс для транспортного средства
class Vehicle {
protected:
    std::string licensePlate;
    std::string ownerName;
    std::string model;

public:
    virtual ~Vehicle() = default;

    // Виртуальная функция для проверки номера
    virtual bool isValidLicensePlate(const std::string& plate) const = 0;

    // Метод для ввода данных
    void inputData() {
        while (true) {
            std::cout << "Enter the license plate: ";
            std::getline(std::cin, licensePlate);

            // Удаляем пробелы из введенного номера
            std::string cleanedPlate = removeSpaces(licensePlate);

            // Добавляем пробел в правильное место для проверки
            std::string formattedPlate = cleanedPlate.substr(0, 6) + " " + cleanedPlate.substr(6);

            // Проверка корректности номера
            if (isValidLicensePlate(formattedPlate)) {
                licensePlate = formattedPlate; // Сохраняем отформатированный номер
                break; // Выходим из цикла, если номер корректен
            } else {
                std::cout << "Error: Invalid license plate format. Example of a valid plate: A055AE 54\n";
                std::cout << "Please try again.\n";
            }
        }

        std::cout << "Enter the owner's name: ";
        std::getline(std::cin, ownerName);

        std::cout << "Enter the vehicle model: ";
        std::getline(std::cin, model);
    }

    // Метод для вывода данных
    void displayInfo() const {
        std::cout << "License Plate: " << licensePlate << "\n";
        std::cout << "Owner: " << ownerName << "\n";
        std::cout << "Model: " << model << "\n";
    }

private:
    // Вспомогательная функция для удаления пробелов
    std::string removeSpaces(const std::string& str) const {
        std::string result = str;
        result.erase(std::remove_if(result.begin(), result.end(), ::isspace), result.end());
        return result;
    }
};

// Класс для автомобиля
class Car : public Vehicle {
public:
    // Реализация проверки номера
    bool isValidLicensePlate(const std::string& plate) const override {
        // Регулярное выражение для проверки формата номера
        std::regex pattern(R"(^[A-Z]\d{3}[A-Z]{2} \d{2}$)");
        return std::regex_match(plate, pattern);
    }
};

// Фабричный метод для создания транспортных средств
class VehicleFactory {
public:
    static Vehicle* createVehicle(const std::string& type) {
        if (type == "car") {
            return new Car();
        }
        return nullptr;
    }
};

int main() {
    std::cout << "Welcome to the Traffic Police Automated Workstation!\n";

    // Создаем объект транспортного средства с помощью фабрики
    Vehicle* vehicle = VehicleFactory::createVehicle("car");
    if (vehicle) {
        vehicle->inputData();
        std::cout << "\nVehicle successfully added!\n";
        vehicle->displayInfo();
        delete vehicle;
    } else {
        std::cout << "Error: Invalid vehicle type.\n";
    }

    return 0;
}
