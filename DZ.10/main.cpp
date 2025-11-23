#include <iostream>
#include <iomanip>
#include <Windows.h>

char Names[][20] = { "яблочный сок", "апельсиновый сок",
                         "абрикосовый сок", "грушевый сок",
                         "томатный сок", "луковый сок",
                         "огуречный сок", "чесночный чай",
                         "петрушевый чай" };

double prices[] = { 80, 90, 100, 85,
                   70, 120, 60, 150,
                   100 };

void showGoodsList() 
{
    std::cout << "Список товаров:\n";
    for (int i = 0; i < sizeof(Names) / sizeof(*Names); ++i) 
    {
        std::cout << i + 1 << ". " << Names[i] << " (" << prices[i] << " руб./л)\n";
    }
}

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));

    int userCart[sizeof(prices) / sizeof(*prices)] = {};

    showGoodsList();

    while (true) 
    {
        int index;
        std::cout << "Выберите товар (введите номер или 0 для окончания): ";
        std::cin >> index;

        if (index == 0)
            break;

        if (index <= 0 || index > sizeof(Names) / sizeof(*Names)) 
        {
            std::cerr << "Неверный номер товара.\n";
            continue;
        }

        int quantity;
        std::cout << "Количество литров: ";
        std::cin >> quantity;

        userCart[index - 1] += quantity;
    }

    double totalCost = 0.0;
    double discounts = 0.0;

    for (int i = 0; i < sizeof(userCart) / sizeof(*userCart); ++i) 
    {
        if (userCart[i] > 0) 
        {
            double cost = userCart[i] * prices[i];
            totalCost += cost;

            if (i == 8 && userCart[i] >= 3) 
            { 
                discounts += cost * 0.05; 
            }

            if (i == 5) 
            { 
                int freeBottles = userCart[i] / 4;
                discounts += freeBottles * prices[i]; 
            }
        }
    }

    const double discountThreshold = 1000.0;
    if (totalCost > discountThreshold) 
    {
        discounts += totalCost * 0.13; 
    }

    double finalCost = totalCost - discounts;

    std::cout << "\nВаш заказ:\n";
    for (int i = 0; i < sizeof(userCart) / sizeof(*userCart); ++i) 
    {
        if (userCart[i] > 0) 
        {
            std::cout << userCart[i] << " литров " << Names[i] << "\n";
        }
    }

    std::cout << "\nОбщий счёт без скидок: " << totalCost << " руб." << "\n";
    std::cout << "Скидки: " << discounts << " руб." << "\n";
    std::cout << "Итого к оплате: " << finalCost << " руб." << "\n";

    return 0;
}