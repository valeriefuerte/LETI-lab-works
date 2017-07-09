#include <cstdio>
#include <cstdlib> // exit
#include <cstring> // strcmp
#include <iostream>
#include <fstream>

using namespace std;

struct BinKor;
struct Arm;

Arm readArm(istream&);
BinKor* readBK(istream&);
unsigned int bkWeight(const BinKor &);

int level = 0;
bool verbose = true;
//структуры данных
struct Arm {
    unsigned int length;
    bool weightType; //false - гирька, true - бинарное коромысло
    union {
        unsigned int weight;
        BinKor* binkor;
    };
};

struct BinKor {
    Arm left;
    Arm right;
};

BinKor* readBK(istream &in) //функция чтения бинарного коромысла
{
    ++level;
    if (verbose) { printf("(%d)%*sЧтение бинарного коромысла\n", level, level, ""); }
    BinKor* bk_p = new BinKor;
    in >> ws;
    if (in.peek() != '(') {
        printf("Ошибка обработки входных данных 1\n");
        exit(1);
    }
    in.ignore();
    if (verbose) { printf("(%d)%*sЧтение левого плеча\n", level, level, ""); }
    bk_p->left = readArm(in);
    if (verbose) { printf("(%d)%*sЧтение правого плеча\n", level, level, ""); }
    bk_p->right = readArm(in);
    in >> ws;
    if (in.peek() != ')') {
        printf("Ошибка обработки входных данных 2\n");
        exit(1);
    }
    in.ignore();
    --level;
    return bk_p;
};

Arm readArm(istream &in) //ошибки на входные данные
{
    in >> ws;
    Arm arm;
    if (in.peek() != '(') {
        printf("Ошибка обработки входных данных 3\n");
        exit(1);
    }
    in.ignore();
    in >> arm.length;
    if (in.fail()) {
        printf("Ошибка обработки входных данных 4\n");
        exit(1);
    }
    if (arm.length == 0) {
        printf("Ошибка во входных данных: длина плеча равна нулю\n");
        exit(1);
    }
    if (verbose) { printf("(%d)%*sДлина плеча: %u\n", level, level, "", arm.length); }
    in >> ws;
    if (in.peek() == '(') {
        arm.weightType = true;
        if (verbose) { printf("(%d)%*sГруз: бинарное коромысло\n", level, level, ""); }
        arm.binkor = readBK(in);
    } else {
        arm.weightType = false;
        in >> arm.weight;
        if (in.fail()) {
            printf("Ошибка обработки входных данных 5\n");
            exit(1);
        }
    }
    in >> ws;
    if (in.peek() != ')') {
        printf("Ошибка обработки входных данных 6\n");
        exit(1);
    }
    in.ignore();
    return arm;
};

unsigned int Length(const BinKor & bk) //подсчет длины и веса
{
    ++level;
    short length = 0;
    
    if (bk.left.weightType) {
        if (verbose) { printf("(%d)%*sГруз на левом плече - бинарное коромысло, рекурсивный вызов\n", level, level, ""); }
        length += Length(*bk.left.binkor) * bk.left.length;
        printf("(%d)%*sдлина левого плеча=%d\n", level, level, "", length); 
    } 
	else{
	   	if (verbose) { printf("(%d)%*sЛевое плечо: длина*вес - %hd\n", level, level, "", bk.left.length* bk.left.weight ); }
    	length += bk.left.length*bk.left.weight;
    }
    if (bk.right.weightType) {
        if (verbose) { printf("(%d)%*sГруз на правом плече - бинарное коромысло, рекурсивный вызов\n", level, level, ""); }
        length += Length(*bk.right.binkor)*bk.right.length;
        printf("(%d)%*sдлина правого плеча=%d\n", level, level, "", length); 
    }
    else{
		if (verbose) { printf("(%d)%*sПравое плечо: длина*вес - %hd\n", level, level, "", bk.right.length* bk.right.weight); }
    	length += bk.right.length*bk.right.weight;
	}
    --level;
    return length;
}
unsigned int ArmLength(const Arm & bkArm) //подсчет момента силы веса
{
    ++level;
    short length = 0;
    
    if (bkArm.weightType) {
        if (verbose) { printf("(%d)%*sГруз на левом плече - бинарное коромысло, рекурсивный вызов\n", level, level, ""); }
        length += Length(*bkArm.binkor) * bkArm.length;
        printf("(%d)%*sдлина левого плеча=%d\n", level, level, "", length); 
    } 
	else{
	   	if (verbose) { printf("(%d)%*sЛевое плечо: длина*вес - %hd\n", level, level, "", bkArm.length* bkArm.weight ); }
    	length += bkArm.length*bkArm.weight;
    }
    
    --level;
    return length;
}

bool Balanced(const BinKor & bk) //проверка на сбалансированность
{ if (ArmLength(bk.left)==ArmLength(bk.right) )
	return true;
	else
	return false;
}

int main(int argc, char const *argv[])
{
    setlocale(LC_ALL,"Russian");
        
	istream* in = NULL;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-v") == 0) {
            verbose = true;
        } else if (strcmp(argv[i], "-f") == 0) {
            if ((i + 1) >= argc) {
                printf("Ошибка в аргументах командной строки\n");
                exit(1);
            } else {
                ifstream* fin = new ifstream(argv[i + 1]);
                
                if (verbose) { printf("Чтение из файла %s:\n", argv[i + 1]); }
                if (!fin->is_open()) {
                    printf("Ошибка чтения файла\n");
                    exit(1);
                }
                in = fin;
            }
        }
    }

    if (in == NULL) {
        if (verbose) { printf("Чтение из консоли\n"); }
        in = &cin;
        printf("Введите бинарное коромысло: ");
    }

    BinKor* bk;
    bk = readBK(*in);
    if (verbose) { printf("\nПодсчет длины всех плеч:\n"); }
    int bkw = Length( * bk);
    if (Balanced(* bk))
    printf("Сбалансировано\n");
    else
    printf("НЕ сбалансировано\n");
}
