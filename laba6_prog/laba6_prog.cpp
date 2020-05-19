#include <iostream> 
#include <fstream>
#include <string>
#include <ctime>
using namespace std;
#pragma warning(disable : 4996)
struct firm {
    string firmName;
    int compSize;
    int compPrice;
    void setName() {
        switch (rand() % 6)
        {
        case 0: firmName = "Samsung";
            break;
        case 1: firmName = "LG";
            break;
        case 2: firmName = "Philips";
            break;
        case 3: firmName = "AOC";
            break;
        case 4: firmName = "Acer";
            break;
        case 5: firmName = "Asus";
            break;
        }
    }
    void setInfo() {
        setName();
        compSize = rand() % 35 + 16;
        compPrice = rand() % 30000 + 2000;
    }
    void saveInfo(FILE* file) {
        fwrite(&firmName, sizeof(string), 1, file);
        fwrite(&compSize, sizeof(short), 1, file);
        fwrite(&compPrice, sizeof(int), 1, file);
    }
    void outInfo() {
        cout << firmName<<endl;
        cout << compPrice << endl;
        cout << compSize << endl;
    }
};
    void initInfo(firm* Comp, int* size) {
        for (size_t i = 0; i < *size; i++)
        {
            (Comp + i)->setInfo();
        }
    }
    
    void showInfo(firm* Comp, int* size, FILE* file)
    {
        for (size_t i = 0; i < *size; i++)
        {
            (Comp + i)->saveInfo(file);
        }
    }
   
    void searchInfo(firm* Comp, int* size, double ave) {
        int sum = 0;
        for (size_t i = 0; i < *size; i++)
        {
            if ((Comp + i)->compSize >= 19)
                sum += (Comp + i)->compPrice;
        }
        for (size_t i = 0; i < *size; i++)
        {
            if (sum > 0)
                ave = sum / *size;
        }
        for (size_t i = 0; i < *size; i++)
        {
            if ((Comp + i)->compSize >= 19) {
                (Comp + i)->outInfo();
            }
        }
       // fwrite(comp, *size, ave, file_out);
        
    }

    /*создать бинарный файл с информацией о предложенных к реализации мониторах:
    - название фирмы;
    - размер по диагонали;
    - стоимость;
    Определить среднюю цену мониторов, размером не менее 19 дюймов и распечатать сведения о них.*/

    void lvl1() {
        FILE* file_out, * file;
        int ave = 0;
        int size = 0;
        file = fopen("D:\\Computers.bin", "wb");
        cout << "Enter quantity of products: ";
        while (!(cin >> size))
        {
            cout << "Wrong input" << endl;
            cin.clear();
            cin.ignore(65535, '\n');
        }
        int* tempSize = &size;
        firm* Comp = new firm[size];
        delete[]Comp;
        initInfo(Comp, tempSize);      
        showInfo(Comp, tempSize, file);
        fclose(file);
        firm* comp = new firm[size];
        file_out = fopen("D:\\Computers.bin", "rb");
        fread(comp,sizeof(firm),size, file_out);
        searchInfo(comp, tempSize, ave);

        fclose(file_out);
    }
    /*Ввести в Memo или в StringGrid некоторое количество символов русского
    алфавита и записать их в бинарный файл. Переписать бинарный файл так,
    чтобы все символы были записаны прописными буквами. Распечатать
    символы до и после изменения данных в файле.*/
    void lvl2() {

    }
    /*Создать бинарный файл, компонентами которого является структура,
    содержащая следующие поля:
    - фамилия и инициалы покупателя;
    - дата покупки;
    - общая стоимость приобретенного товара;
    - начальный процент скидки на последующие приобретаемые товары.
    Переписать бинарный файл так, чтобы процентная скидка была бы
    увеличена на 5%, если покупатель заплатил за предыдущий товар 5000 грн.*/
    void lvl3() {

    }
    int main()
    {
        lvl1();
    }