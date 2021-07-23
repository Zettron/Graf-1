#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

class Ip
{
public:
    char ip1[13], ip2[13];
    char getIp1()
    {
        return *ip1;
    }
    char getIp2()
    {
        return *ip2;
    }
    void setIp(char ip1[], char ip2[])
    {
        strcpy_s(this->ip1, ip1);
        strcpy_s(this->ip2, ip2);
    }
};

void ping()
{
    system("cls");

    system("ping google.com > res.txt");
    cout << endl;
}

int main()
{
    setlocale(0, "ukr.UTF-8");
    ifstream fin;
    fin.open("G1.csv");
    if (!fin.is_open())
    {
        cout << "Error open file G1.csv";
        return 0;
    }
    int i, j;
    Ip* n = new Ip[819];
    char ip1[13], ip2[13];
    char ch = '1'; 
    char c = ',';
    for (i = 0; i < 819; i++)
    {
        j = 0;
            while(ch != c)
            {
                fin.get(ch);
                if(ch!=c &&j<13)
                ip1[j] = ch;
                j++;
            }
            while (!fin.get(ch))
            {
                fin.get(ch);
                if (ch != c && j < 13)
                    ip2[j] = ch;

                j++;
            }
        n[i].setIp(ip1, ip2);
        //проверка читания файла
        cout << n[i].getIp1() << "," << n[i].getIp2();
    }
    
    /*j = 0;
    while (j!=13)
    {
        fin.get(ch);
        ip1[j] = ch;
        
        cout << ip1[j];
        j++;
    }
    */



    fin.close();
    return 0;
}