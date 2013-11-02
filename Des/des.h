#ifndef DES_H
#define DES_H

#include <QDialog>
# include <stdio.h>
# include <fstream>
# include <string.h>
# include <iostream>
# include <stdlib.h>

using namespace std;
namespace Ui {

class Des;
}

class Des : public QDialog
{
    Q_OBJECT

public:
    explicit Des(QWidget *parent = 0);
    ~Des();
    int keyi[16][48],
        total[64],
        left[32],
        right[32],
        ck[28],
        dk[28],
        expansion[48],
        z[48],
        xor1[48],
        sub[32],
        p[32],
        xor2[32],
        temp[64],
        pc1[56],
        ip[64],
        inv[8][8];

    char final[1000];
    void IP();
    void PermChoice1();
    void PermChoice2();
    void Expansion();
    void inverse();
    void xor_two();
    void xor_oneE(int);
    void xor_oneD(int);
    void substitution();
    void permutation();
    void keygen();
    char * Encrypt(char *);
    char * Decrypt(char *);

private slots:
    void on_start_clicked();

private:
    Ui::Des *ui;
};

#endif // DES_H
