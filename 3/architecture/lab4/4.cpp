//�������������� ���� ��������� ��������� ���� ������� ������ � ��������, 
//� ������������ ���� � ���������, ��������� ������� ������� ������ ���������� � �������� ������ ���������������.
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

    cout << "4. �������������� ���� ��������� ��������� ���� ������� ������ � ��������,\n"
            "    � ������������ ���� � ���������, ��������� ������� ������� ������\n"
            "       ���������� � �������� ������ ���������������.\n"
            "��������: ������� ��. 5383 ������ �.\n";

    char src[STR_LEN] = {0};
    char dst[3 * STR_LEN] = {0};

    ofstream fout("output.txt");

    cout << "������� ������: ";
    // ��������� �������� ������
    fgets(src, STR_LEN, stdin);
    // ������� ���� \n
    src[strlen(src) - 1] = 0;

    fout << "�������� ������: " << src << endl;

    asm
    (
        ".section .data \n"
        // ������� �������������� (������� �����)
        "transliteration_table: .ascii \"ABVGDE_ZIJKLMNOPRSTUF______Y'E__\" \n"

        ".section .text \n"

        // � ebx - ����� �� ������� ��������������
        //"mov offset transliteration_table, %edi \n"
		"push offset transliteration_table \n"
		"popl %edi \n"
        "_mainloop: \n"
        
        // ��������� � ax ��������� ������
        "mov byte ptr[edi], %al \n"
//xor al,7
    //MOV     DL,BYTE PTR [BP+SI] ;����� ������ �� ������
    "inc %edi  \n"        //��������� ��������
    "cmp $96, %al  \n"      //���� ��� �������� �� ������� �� �����
    "jb  _NOT   \n"
    "sub %al,$32  \n"      //������� �� ��������
    
	"_NOT:   \n"
    "int $0x80 \n"       //������� �� �����
    "loop _mainloop   \n"    //���������� ����
     
	// ���������� ���� �� ����� ������
    "cmp $0, %byte ptr[edi] \n"
    "jne _mainloop \n"

    // ��������� ����������� ���� � �������� ������
    "mov $0, %byte ptr[edi] \n"
    "add $4, %edi\n"
    //"movl %%edi, %0"
    //:
    : "=D"(dst) //Out variable
    : "S"(src), "D"(dst) //in variable
 	: "memory"
	 );

    // ������� �������� ������
    cout << "���������: " << dst << endl;
    // ����� � ����
    fout << "���������: " << dst << endl;
    fout.close();

    return 0;
}
