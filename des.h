#ifndef DES_H
#define DES_H

#include <QDialog>
#include <iostream>
#include <fstream>
#include <QFileDialog>
#include <vector>
using namespace std;

namespace Ui {
class des;
}

class des : public QDialog
{
    Q_OBJECT
    
public:
    explicit des(QWidget *parent = 0);
    ~des();

    char *text;
    QString fileName;
    fstream file;
    int filesize;
    bool DES;
    void blocks(fstream &file);
    void encryption();
    void decryption(int &numero);
    void binary(int vetB[8][8], char vetC[8]);
    void sum(int Risultato[8][8],int msg[8][8], int pass[8][8]);
    void diff(int Risultato[8][8],int msg[8][8], int pass[8][8]);
    void binToInt(int Risultato[8][8], char vettore[8]);
private slots:
    void on_buttonStart_clicked();

    void on_buttonChoose_clicked();

private:
    Ui::des *ui;
};

#endif // DES_H
