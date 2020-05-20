#include <iostream> 
#include <fstream>
#include <string>
#include <ctime>
#include <windows.h>
using namespace std;
#pragma warning(disable : 4996)

const char* firmName[6]= { "Samsung","LG","Philips","AOC","Acer","Asus"};
const char* Last[5] = { "Stark", "Smith", "White", "Jackson", "Potter" };
const char* First[5] = { "Robert", "Emma","Peter", "Alice","James" };
const char* Second[5] = { "Tony","Johnson", "Niko", "Charlotte","Ciara" };

struct firm {
    //srand(time(NULL));
    char name[56] = "";
    int compSize;
    int compPrice;
    void setInfo() {
        strcat(name, firmName[rand() % 6]);
        compSize = rand() % 35 + 13;
        compPrice = rand() % 30000 + 2000;
    }
    void saveInfo(FILE* file) {
        fwrite(&firmName, sizeof(char), 1, file);
        fwrite(&compSize, sizeof(int), 1, file);
        fwrite(&compPrice, sizeof(int), 1, file);
    }
    void outInfo() {
        string info = "";
        info += "Company name: ";
        info += name;
        info += "\n";
        info += "Price: "+to_string(compPrice)+"\n";
        info += "Computer size: " + to_string(compSize)+"\n";
        cout << info;
        //return info;
    }
};
/////////////////////////////////////////////////////////////for3
struct Date {
    short day;
    short month;
    short year;
    bool isCorrect();
};

struct client {
    Date lastPurchaseDate;
    int lastTimePrice;
    double discount = 0;   
    char f[56] = "";
    char i[56] = "";
    char o[56] = "";
    void setCus() {
        strcat(f, Last[rand() % 5]);
        strcat(i,First[rand() % 5]);
        strcat(o, Second[rand() % 5]);
    }
    void showCus() {
        string info = "";
        info += "First name: ";
        info += f;
        info += "\n";
        info += "Second name: ";
        info += i;
        info += "\n";
        info += "Last name: ";
        info += o;
        info += "\n";
        cout << info;
    }
    void customerName(FILE* f_out) {
        fwrite(&f, sizeof(char*), 1, f_out);
        fwrite(&i, sizeof(char*), 1, f_out);
        fwrite(&o, sizeof(char*), 1, f_out);
    }

};


int getInteger(const char* text)
{
    bool isError = false;
    string s;
    int number = 0;
    do {
        isError = false;
        cout << text << endl;
        cin >> s;
        for (size_t i = 0; i < s.length(); i++)
        {
            if ((int)(s[i]) < 0 || !isdigit(s[i]))
            {
                isError = true;
                break;
            }
        }
        if (!isError)
            number = atoi(s.c_str());
        else { cout << "Error: Wrong entering.\n"; }
    } while (isError || number <= 0);

    return number;
}
bool Date::isCorrect()
{
    bool result = false;
    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
    {
        if ((day <= 31) && (day > 0))
            result = true;
        break;
    }

    case 4:
    case 6:
    case 9:
    case 11:
    {
        if ((day <= 30) && (day > 0))
            result = true;
        break;
    }

    case 2:
    {
        if (year % 4 != 0)
        {
            if ((day <= 28) && (day > 0))
                result = true;
        }
        else
            if (year % 400 == 0)
            {
                if ((day <= 29) && (day > 0))
                    result = true;
            }
            else
                if ((year % 100 == 0) && (year % 400 != 0))
                {
                    if ((day == 28) && (day > 0))
                        result = true;
                }
                else
                    if ((year % 4 == 0) && (year % 100 != 0))
                        if ((day <= 29) && (day > 0))
                            result = true;
        break;
    }

    default:
        result = false;
    }
    if (year > 2020) { result = false; }

    return result;
}
////////////////////////////////////////////////////////////////////////
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
    initInfo(Comp, tempSize);
    fwrite(Comp, sizeof(firm), size, file);
    showInfo(Comp, tempSize, file);
    fclose(file);
    delete[] Comp;
    firm* comp = new firm[size];
    file_out = fopen("D:\\Computers.bin", "rb");
    fread(comp, sizeof(firm), size, file_out);
    searchInfo(comp, tempSize, ave);

    fclose(file_out);
}
/*Ввести в Memo или в StringGrid некоторое количество символов русского
алфавита и записать их в бинарный файл. Переписать бинарный файл так,
чтобы все символы были записаны прописными буквами. Распечатать
символы до и после изменения данных в файле.*/
void lvl2() {
    FILE* f_out, * f_in;
    const int size = 200;
    wchar_t  entering[size] = L"РУССКИЙ ТЕКСТ УУУ ПАМАГИТИ ЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮЁ waAAAbaLabadaBDa";
    char originalArray[size] = "";
    CharToOem(entering, originalArray);
    cout << originalArray << endl;
    f_out = fopen("D:\\1.bin", "wb");
    fwrite(originalArray, sizeof(char), size, f_out);
    fclose(f_out);

    char import[200];
    f_in = fopen("1.bin", "rb");
    fread(import, sizeof(char), size, f_in);
    fclose(f_in);

    for (int i = 0; i < strlen(import); i++)
    {
        if (import[i] >= 65 && import[i] <= 90)
        {
            import[i] += (char)32;
        }
        else if (import[i] >= -128 && import[i] <= -113)
        {
            import[i] += (char)32;
        }
        else if (import[i] >= -112 && import[i] <= -97)
        {
            import[i] += (char)80;
        }
        else if (import[i] == -16)
        {
            import[i] += (char)1;
        }
    }
    cout << import << endl;

    f_out = fopen("1.bin", "wb");
    fwrite(import, sizeof(char), size, f_out);
    fclose(f_out);
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
    FILE* f_out, * f_in;

    int size = 0;
    // client array[size];
    cout << "Enter quantity of customers: ";
    while (!(cin >> size))
    {
        cout << "Wrong input" << endl;
        cin.clear();
        cin.ignore(65535, '\n');
    }
    int* tempSize = &size;
    client* array = new client[size];

    for (int i = 0; i < size; i++)
    {
        do
        {
            array[i].setCus();
            array[i].showCus();
            array[i].lastPurchaseDate.day = getInteger("Enter day of last purchase:");
            array[i].lastPurchaseDate.month = getInteger("Enter month of last purchase:");
            array[i].lastPurchaseDate.year = getInteger("Enter year of last purchase:");
            if (array[i].lastPurchaseDate.isCorrect() != true)
            {
                cout << "Error. Try again.";
            }
        } while (array[i].lastPurchaseDate.isCorrect() != true);
        array[i].lastTimePrice = getInteger("Enter the price of last purchase:");
        array[i].discount = 0;

    }
    f_out = fopen("D:\\3.bin", "wb");
    fwrite(array, sizeof(client), size, f_out);
    fclose(f_out);

    client* import = new client[size];
    f_in = fopen("D:\\3.bin", "rb");
    fread(import, sizeof(client), size, f_in);

    for (int i = 0; i < size; i++)
    {
        if (import[i].lastTimePrice > 5000 && import[i].discount <= 10)
        {
            cout << endl << endl;
            import[i].discount += 5;
            import[i].customerName(f_in);
            cout << import[i].f;
            cout << " recieves +5% discount!\n";
        }
    }
    fclose(f_in);
    f_out= fopen("D:\\3.bin", "wb");
    fwrite(import, sizeof(client), size, f_out);
    fclose(f_out);

}
int main()
{
    int varForSwitch;
    cout << "Choose level 1-3:\t";
    cin >> varForSwitch;
    switch (varForSwitch)
    {
    case 1:
        cout << "Your choice was 1 level:\n\n";
        lvl1();
        break;
    case 2:
        cout << "Your choice was 2 level:\n\n";
        lvl2();
        break;
    case 3:
        cout << "Your choice was 3 level:\n\n";
        lvl3();
        break;
    default:
        cout << "Action not found." << endl;
        break;
    }
    system("pause");
    return 0;
}