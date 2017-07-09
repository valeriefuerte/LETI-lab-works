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
//��������� ������
struct Arm {
    unsigned int length;
    bool weightType; //false - ������, true - �������� ���������
    union {
        unsigned int weight;
        BinKor* binkor;
    };
};

struct BinKor {
    Arm left;
    Arm right;
};

BinKor* readBK(istream &in) //������� ������ ��������� ���������
{
    ++level;
    if (verbose) { printf("(%d)%*s������ ��������� ���������\n", level, level, ""); }
    BinKor* bk_p = new BinKor;
    in >> ws;
    if (in.peek() != '(') {
        printf("������ ��������� ������� ������ 1\n");
        exit(1);
    }
    in.ignore();
    if (verbose) { printf("(%d)%*s������ ������ �����\n", level, level, ""); }
    bk_p->left = readArm(in);
    if (verbose) { printf("(%d)%*s������ ������� �����\n", level, level, ""); }
    bk_p->right = readArm(in);
    in >> ws;
    if (in.peek() != ')') {
        printf("������ ��������� ������� ������ 2\n");
        exit(1);
    }
    in.ignore();
    --level;
    return bk_p;
};

Arm readArm(istream &in) //������ �� ������� ������
{
    in >> ws;
    Arm arm;
    if (in.peek() != '(') {
        printf("������ ��������� ������� ������ 3\n");
        exit(1);
    }
    in.ignore();
    in >> arm.length;
    if (in.fail()) {
        printf("������ ��������� ������� ������ 4\n");
        exit(1);
    }
    if (arm.length == 0) {
        printf("������ �� ������� ������: ����� ����� ����� ����\n");
        exit(1);
    }
    if (verbose) { printf("(%d)%*s����� �����: %u\n", level, level, "", arm.length); }
    in >> ws;
    if (in.peek() == '(') {
        arm.weightType = true;
        if (verbose) { printf("(%d)%*s����: �������� ���������\n", level, level, ""); }
        arm.binkor = readBK(in);
    } else {
        arm.weightType = false;
        in >> arm.weight;
        if (in.fail()) {
            printf("������ ��������� ������� ������ 5\n");
            exit(1);
        }
    }
    in >> ws;
    if (in.peek() != ')') {
        printf("������ ��������� ������� ������ 6\n");
        exit(1);
    }
    in.ignore();
    return arm;
};

unsigned int Length(const BinKor & bk) //������� ����� � ����
{
    ++level;
    short length = 0;
    
    if (bk.left.weightType) {
        if (verbose) { printf("(%d)%*s���� �� ����� ����� - �������� ���������, ����������� �����\n", level, level, ""); }
        length += Length(*bk.left.binkor) * bk.left.length;
        printf("(%d)%*s����� ������ �����=%d\n", level, level, "", length); 
    } 
	else{
	   	if (verbose) { printf("(%d)%*s����� �����: �����*��� - %hd\n", level, level, "", bk.left.length* bk.left.weight ); }
    	length += bk.left.length*bk.left.weight;
    }
    if (bk.right.weightType) {
        if (verbose) { printf("(%d)%*s���� �� ������ ����� - �������� ���������, ����������� �����\n", level, level, ""); }
        length += Length(*bk.right.binkor)*bk.right.length;
        printf("(%d)%*s����� ������� �����=%d\n", level, level, "", length); 
    }
    else{
		if (verbose) { printf("(%d)%*s������ �����: �����*��� - %hd\n", level, level, "", bk.right.length* bk.right.weight); }
    	length += bk.right.length*bk.right.weight;
	}
    --level;
    return length;
}
unsigned int ArmLength(const Arm & bkArm) //������� ������� ���� ����
{
    ++level;
    short length = 0;
    
    if (bkArm.weightType) {
        if (verbose) { printf("(%d)%*s���� �� ����� ����� - �������� ���������, ����������� �����\n", level, level, ""); }
        length += Length(*bkArm.binkor) * bkArm.length;
        printf("(%d)%*s����� ������ �����=%d\n", level, level, "", length); 
    } 
	else{
	   	if (verbose) { printf("(%d)%*s����� �����: �����*��� - %hd\n", level, level, "", bkArm.length* bkArm.weight ); }
    	length += bkArm.length*bkArm.weight;
    }
    
    --level;
    return length;
}

bool Balanced(const BinKor & bk) //�������� �� ������������������
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
                printf("������ � ���������� ��������� ������\n");
                exit(1);
            } else {
                ifstream* fin = new ifstream(argv[i + 1]);
                
                if (verbose) { printf("������ �� ����� %s:\n", argv[i + 1]); }
                if (!fin->is_open()) {
                    printf("������ ������ �����\n");
                    exit(1);
                }
                in = fin;
            }
        }
    }

    if (in == NULL) {
        if (verbose) { printf("������ �� �������\n"); }
        in = &cin;
        printf("������� �������� ���������: ");
    }

    BinKor* bk;
    bk = readBK(*in);
    if (verbose) { printf("\n������� ����� ���� ����:\n"); }
    int bkw = Length( * bk);
    if (Balanced(* bk))
    printf("��������������\n");
    else
    printf("�� ��������������\n");
}
