#include <iostream>
#include <iomanip>
#include <Windows.h>


const std::string fruits[] = { "яблочный", "апельсиновый", "абрикосовый", "грушевый" };
const std::string vegetables[] = { "томатный", "луковый", "огуречный" };
const std::string teas[] = { "чесночный", "петрушевый" };

const double prices[] = { 30.0, 35.0, 40.0, 45.0,
                         25.0, 30.0, 35.0,
                         40.0, 45.0 };

const int F_MAX = sizeof(fruits) / sizeof(fruits[0]);
const int V_MAX = sizeof(vegetables) / sizeof(vegetables[0]);
const int T_MAX = sizeof(teas) / sizeof(teas[0]);


void requestItemQuantity(const std::string& itemName, int& qty)
{
    std::cout << itemName << ": ";
    std::cin >> qty;
}


bool chooseCategory(const std::string& categoryName)
{
    char response;
    std::cout << "Выбрать товары из категории \"" << categoryName << "\"? (Y/N): ";
    std::cin >> response;
    return tolower(response) == 'y';
}

// Размещение заказа
void placeOrder(int* fruitQ, int* veggieQ, int* teaQ)
{
    if (chooseCategory("Фруктовые"))
    {
        for (int i = 0; i < F_MAX; ++i)
        {
            requestItemQuantity(fruits[i], fruitQ[i]);
        }
    }

    if (chooseCategory("Овощные"))
    {
        for (int i = 0; i < V_MAX; ++i)
        {
            requestItemQuantity(vegetables[i], veggieQ[i]);
        }
    }

    if (chooseCategory("Чаи"))
    {
        for (int i = 0; i < T_MAX; ++i)
        {
            requestItemQuantity(teas[i], teaQ[i]);
        }
    }
}

double calculateTotal(int* fruitQ, int* veggieQ, int* teaQ)
{
    double total = 0.0;

    for (int i = 0; i < F_MAX; ++i)
    {
        total += fruitQ[i] * prices[i];
    }

    for (int i = 0; i < V_MAX; ++i)
    {
        if (i == 1 && veggieQ[i] > 0)
        {
            int freeBottles = veggieQ[i] / 4;
            total += (veggieQ[i] - freeBottles) * prices[F_MAX + i];
        }
        else
        {
            total += veggieQ[i] * prices[F_MAX + i];
        }
    }

    for (int i = 0; i < T_MAX; ++i)
    {
        if (i == 1 && teaQ[i] >= 3)
        {
            double discount = 0.05 * teaQ[i] * prices[F_MAX + V_MAX + i];
            total += (teaQ[i] * prices[F_MAX + V_MAX + i]) - discount;
        }
        else
        {
            total += teaQ[i] * prices[F_MAX + V_MAX + i];
        }
    }

    if (total > 200.0)
    {
        total *= 0.87;
    }

    return total;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(static_cast<unsigned>(time(nullptr)));

    int fruitQuantities[F_MAX] = { 0 };
    int veggieQuantities[V_MAX] = { 0 };
    int teaQuantities[T_MAX] = { 0 };

    placeOrder(fruitQuantities, veggieQuantities, teaQuantities);

    double totalBill = calculateTotal(fruitQuantities, veggieQuantities, teaQuantities);

    std::cout << "Итого к оплате: " << std::fixed << std::setprecision(2) << totalBill << " руб.\n";

    return 0;
}