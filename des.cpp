#include "des.h"
#include "ui_des.h"

des::des(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::des)
{
    ui->setupUi(this);
}

des::~des()
{
    delete ui;
}

void des::on_buttonStart_clicked()
{
    file.open("test.txt", ios::binary | fstream::in | fstream::out | fstream::app);
    if(file.is_open())
    {
        file.seekg(0,ios::beg);
        if(ui->radioCodifica->isChecked()) // se c'e' da fare codifica
        {
            DES = true; // sta per la codifica
        }
        else if(ui->radioDecodifica->isChecked()) // se c'e' da fare decodifica
        {
            DES = false; // decodifica
        }
        encryption();
    }
    file.close();
}

void des::on_buttonChoose_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open Text File"), "",tr("TXT (*.txt )")); // il file
}

void des::encryption()
{
    ofstream des("des.txt",ios::binary | fstream::in | fstream::out | fstream::app);
    char msg[8]; // messaggio;
    file.seekg(0,ios::beg); // lettura
    des.seekp(0,ios::beg); // scrittura
    while(!file.eof())
    {
        file.read((char*)msg,(sizeof(char)*8));
        char vectPass[8]; // pass
        int vetBinPass[8][8]; // vetore per i valori binari del pass
        int vetBinMsg[8][8]; // vetore per i valori binari del messaggio
        char vettore[8];
        int vetRisultato[8][8]; // risultato
        strcpy(vectPass,ui->password->text().toStdString().c_str());
        for(int i=0;i<8;i++)
        {
            binary(vetBinPass,vectPass);
            binary(vetBinMsg,msg);
        }
        if(DES)
        {
           sum(vetRisultato,vetBinMsg,vetBinPass);
        }
        else
        {
            diff(vetRisultato,vetBinMsg,vetBinPass);
        }
        binToInt(vetRisultato,vettore);
        des.write((const char*)&vettore,(sizeof(char)*8));
    }
}

void des::binary(int vetB[8][8], char vetC[8])
{
    for(int v=0;v<8;v++)
    {
        int carattere = vetC[v];
        for(int i=0;i<8;i++)
        {
            vetB[v][7-i] = carattere % 2;
            carattere = carattere / 2;
        }
    }
}

void des::sum(int Risultato[8][8],int msg[8][8], int pass[8][8])
{
    for(int a=0;a<8;a++)
    {
        int resto = 0;
        for(int b=0;b<8;b++)
        {
            Risultato[a][b] = msg[a][b] + pass[a][b] + resto;
            resto--;
            if(Risultato[a][b] > 1)
            {
                resto++;
                if(Risultato[a][b] == 3)
                {
                    Risultato[a][b] = 1;
                }
                else
                {
                    Risultato[a][b] = 0;
                }
            }
        }
    }
}

void des::diff(int Risultato[8][8],int msg[8][8], int pass[8][8])
{
    for(int a=0;a<8;a++)
    {
        for(int b=0;b<8;b++)
        {
            Risultato[a][b] = msg[a][b] - pass[a][b];

            if(Risultato[a][b] < 0)
            {
                Risultato[a][b] += 2;
                if(Risultato[a][b+1] > 0 && (b-1) > 0)
                {
                    Risultato[a][b+1] -= 1;
                }
            }
        }
    }
}

void des::binToInt(int Risultato[8][8],char vettore[8])
{
    for(int a=0;a<8;a++)
    {
        int numero = 0;
        int moltiplicatore = 1;
        for(int b=0;b<8;b++)
        {
            numero += (Risultato[a][b] * moltiplicatore);
            moltiplicatore = moltiplicatore * 2;
        }
        vettore[a] = (char)numero;
    }
}
