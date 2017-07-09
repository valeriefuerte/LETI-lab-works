//Преобразование всех заглавных латинских букв входной строки в строчные, 
//а восьмеричных цифр в инверсные, остальные символы входной строки передаются в выходную строку непосредственно.
#include <iostream>
#include <fstream>
#include <locale>
#include <string.h>
#include <windows.h>

using namespace std;
const int STR_LEN = 100;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "4. Преобразование всех заглавных латинских букв входной строки в строчные,\n"
            "    а восьмеричных цифр в инверсные, остальные символы входной строки\n"
            "       передаются в выходную строку непосредственно.\n"
            "Выполнил: студент гр. 5383 Допира В.\n";

    char src[STR_LEN] = {0};
    char dst[3 * STR_LEN] = {0};

    ofstream fout("output.txt");

    cout << "Введите строку: ";
    // считываем исходную строку
    fgets(src, STR_LEN, stdin);
    // удаляем знак \n
    src[strlen(src) - 1] = 0;

    fout << "Исходная строка: " << src << endl;

    asm
    (
        ".section .data \n"
        // таблица преобразования (простые буквы)
        "transliteration_table: .ascii \"ABVGDE_ZIJKLMNOPRSTUF______Y'E__\" \n"

        ".section .text \n"

        // в ebx - адрес на таблицу преобразования
        //"mov offset transliteration_table, %edi \n"
		"push offset transliteration_table \n"
		"popl %edi \n"
        "_mainloop: \n"
        
        // загружаем в ax очередной символ
        "mov byte ptr[edi], %al \n"
//xor al,7
    //MOV     DL,BYTE PTR [BP+SI] ;взять символ из буфера
    "inc %edi  \n"        //увеличить смещение
    "cmp $96, %al  \n"      //если это заглвная то вывести на экран
    "jb  _NOT   \n"
    "sub %al,$32  \n"      //перейти на строчную
    
	"_NOT:   \n"
    "int $0x80 \n"       //вывести на экран
    "loop _mainloop   \n"    //продолжить цикл
     
	// продолжаем пока не конец строки
    "cmp $0, %byte ptr[edi] \n"
    "jne _mainloop \n"

    // добавляем завершающий нуль в выходную строку
    "mov $0, %byte ptr[edi] \n"
    "add $4, %edi\n"
    //"movl %%edi, %0"
    //:
    : "=D"(dst) //Out variable
    : "S"(src), "D"(dst) //in variable
 	: "memory"
	 );

    // выводим выходную строку
    cout << "Результат: " << dst << endl;
    // вывод в файл
    fout << "Результат: " << dst << endl;
    fout.close();

    return 0;
}
