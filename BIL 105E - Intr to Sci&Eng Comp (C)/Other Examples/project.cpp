#include <iostream>             // std::xxx
#include <stdlib.h>             // EXIT_SUCCESS
#include "ops.h"                // gcd,lcm,...

int main(void)
{
    int num1 = 0, num2 = 0;
    factor_t factors[MAXFACTOR];
    int n, i;
    int choice;

    while (true) {
        std::cout << "Sayi 1: " << num1 << std::endl;
        std::cout << "Sayi 2: " << num2 << std::endl << std::endl;
        std::cout << "1. Sayi 1'i degistir" << std::endl;
        std::cout << "2. Sayi 2'yi degistir" << std::endl;
        std::cout << "3. Sayi 1'in carpanlarini goster" << std::endl;
        std::cout << "4. En buyuk ortak bolen bul" << std::endl;
        std::cout << "5. En kucuk ortak kat bul" << std::endl;
        std::cout << "6. Cik" << std::endl << std::endl;
        std::cout << "Seciminiz: ";
        std::cin >> choice;
        if (choice == 6)
            exit(EXIT_SUCCESS);
        switch (choice) {
            case 1:
            case 2:
                std::cout << "Sayiyi yaziniz: ";
                if (choice == 1)
                    std::cin >> num1;
                else
                    std::cin >> num2;
                break;
            case 3:
                factorize(num1, factors, n);
                for (i = 0; i < n; i++)
                    std::cout << factors[i].base << "^" << factors[i].power << " ";
                std::cout << std::endl;
                break;
            case 4:
                std::cout << "En buyuk ortak bolen: " << gcd(num1, num2) << std::endl;
                break;
            case 5:
                std::cout << "En kucuk ortak kat: " << lcm(num1, num2) << std::endl;
                break;
        }
        std::cout << std::endl;
    }
    return EXIT_SUCCESS;
}
