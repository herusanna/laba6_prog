#include <iostream> 
#include <fstream>
using namespace std;
struct firm {
    char firmName[32];
    int compSize;
    int compPrice;
void setInfo(){
    ofstream fileStrmOut("file.bin", ios::binary);
 cin.ignore(cin.rdbuf()->in_avail());
    cout << endl << "Firm name : ";
    cin.getline(firmName, 32);
    fileStrmOut.write(firmName, sizeof(int));
    while (!(cin >> compSize))
    {
        cout << "Wrong input" << endl;
        cin.clear();
        cin.ignore(65535, '\n');
    }
    fileStrmOut.write((char*)&compSize, sizeof(int));
    while (!(cin >> compPrice))
    {
        cout << "Wrong input" << endl;
        cin.clear();
        cin.ignore(65535, '\n');
    }
    fileStrmOut.write((char*)&compPrice, sizeof(int));
}
void showInfo() {
    ofstream fileStrmOut("file.bin", ios::binary);
    fileStrmOut.write(firmName, sizeof(int));
    fileStrmOut.write((char*)&compSize, sizeof(int));
    fileStrmOut.write((char*)&compPrice, sizeof(int));
    fileStrmOut.close();
}
};
void searchInfo(firm*Comp, int* size ) {
    int sum=0;
    double ave;
    for (size_t i = 0; i < *size; i++)
    {
        if ((Comp + i)->compSize >= 19) {
            (Comp + i)->showInfo();
            sum += (Comp + i)->compPrice;
        }
    }
    for (size_t i = 0; i < *size; i++)
    {
         ave = sum / *size;
    }
    ofstream fileStrmOut("file.bin", ios::binary);
    fileStrmOut.write((char*)&ave, sizeof(int));
}

/*создать бинарный файл с информацией о предложенных к реализации мониторахЖ
- название фирмы;
- размер по диагонали;
- стоимость;
Определить среднюю цену мониторов, размером не менее 19 дюймов и распечатать сведения о них.*/

void lvl1() {
    
    int size;
    cout << "Enter size of products: ";
    while (!(cin >> size))
    {
        cout << "Wrong input" << endl;
        cin.clear();
        cin.ignore(65535, '\n');
    }
    int* tempSize = &size;
    firm* Comp = new firm[size];
    ifstream fileStrmIn("file.bin", ios::binary);
    searchInfo(Comp, tempSize);
    //while (fileStrmIn.read((char*)&compSize, sizeof(int))) {}

    fileStrmIn.close();
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
- дата покупки4
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

