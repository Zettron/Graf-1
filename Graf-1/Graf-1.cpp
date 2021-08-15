#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;
#pragma comment(linker, "/STACK:66216")

const int countip = 127;

class Ip
{
public:
    int ip1, ip2;
    string ip;
    string getConnection()
    {
        return ip;
    }
    int getIp1()
    {
        return ip1;
    }
    int getIp2()
    {
        return ip2;
    }
    void setIp(string ips)
    {
        ip = ips;
    }
    void setIp1(int ip11)
    {
        ip1 = ip11;
    }
    void setIp2(int ip22)
    {
        ip2 = ip22;
    }
};

void CheckDistance(int strc, Ip* n)
{
    int x = 0, y = 0, d = 1, sum = 0;
    int g, i=0, j=0;
    const char coma = ',', point = '.';
    string ips;
    for (i = 0; i < strc; i++)
    {
        ips = n[i].getConnection();
        for (j = ips.length() - 1; ips[j] != point; j--)
        {
            x = (int)ips[j];
            x -= 48;
            sum += x * d;
            d *= 10;
            if (ips[j - 1] == point)
                n[i].setIp2(sum);
        }
        sum = 0;
        d = 1;
        for (j = 13; j >= 10; j--)
        {
            if (ips[j] == coma)
            {
                g = j - 1;
                for (g; g >= 10; g--)
                {
                    y = (int)ips[g];
                    y -= 48;
                    sum += y * d;
                    d *= 10;
                }
            }
            else if (ips[j - 1] == point)
                n[i].setIp1(sum);
        }
        sum = 0;
        d = 1;
        //проверка виводу іп1->іп2
      /* cout << endl << n[i].getIp1() << "->";
       cout << n[i].getIp2();*/
    }
    cout << endl;
}

void MaxPing(int(*length)[countip])
{
    int i, j, fir = 0, sec = 0, maxping = 0;

    for (i = 1; i < countip; i++)
    {
        for (j = 1; j < countip; j++)
        {
            if (maxping < length[i][j])
            {
                maxping = length[i][j];
                fir = i;
                sec = j;
            }
        }
    }
    cout << "->maxping from 192.168.0." << fir << " to 192.168.0." << sec << " - " << maxping << "ms\n";
}

void NoConnection(int(*length)[countip])
{
    int i, j;
    bool notConnect = 0;
    for (i = 1; i < countip; i++)
    {
        for (j = 1; j < countip; j++)
        {
            if (i != j && length[i][j] == 0)
            {
                cout << "\n->node no connected from 192.168.0." << i << " to " << j;
                notConnect = 1;
            }
        }
    }

    if (notConnect == 0)
        cout << "\n->There are no nodes with no connection\n\n";
}

int CalculateDistance(int start, int finish, Ip* n, int strc)
{
    ofstream png("res.txt", ios_base::out);
    int length[countip][countip], a = 0, b = 0, i = 0, j = 0, s = 0;

    for (j = 0; j < countip; j++)
    {
        for (i = 0; i < countip; i++)
        {
            if (i == j) {
                length[j][i] = 0;
                continue;
            }
            length[j][i] = INT_MAX;
        }
    }

    for (i = 0; i < strc; i++)
    {
        a = n[i].getIp1();
        b = n[i].getIp2();

        if (a != b)
        {
            length[a][b] = 2;
        }
    }

    for (int k = 0; k < countip; k++) {
        for (int i = 0; i < countip; i++) {
            for (int j = 0; j < countip; j++) {
                if (length[i][j] > (length[i][k] + length[k][j]) && (length[k][j] != INT_MAX && length[i][k] != INT_MAX))
                    length[i][j] = length[i][k] + length[k][j];
            }
        }
    }

    //вивід на екран
    /*for (i = 0; i < countip; i++)
    {
        for (j = 0; j < countip; j++)
        {

            if (length[i][j] == INT_MAX) {
                cout << "INF ";
                continue;
            }
            cout << length[i][j] << " ";
        }
        cout << endl << endl;
    }*/
    png << length[start][finish] << "ms";
    cout << "\n->ping from 192.168.0.5 to 192.168.0.1 - " << length[start][finish] << "ms\n";
    cout << "\tSaved to res.txt - " << length[start][finish] << "ms\n";
    
    MaxPing(length);
    NoConnection(length);
    png.close();
        //return (*length)[countip];
    return 0;
}



int main()
{
    setlocale(0, "ukr.UTF-8");
    ifstream fin;
    cout << "\tDebian 10\n";
    fin.open("G1.csv");
    if (!fin.is_open())
    {
        cout << "\tError opening file G1.csv";
        return 0;
    }
    int i=0, j=0, strc=-1;
    Ip* n = new Ip[16000];
    string ips;

    for(i=0;!fin.eof(); i++)
    {
        fin >> ips;
        n[i].setIp(ips);
        strc ++;
    }
    //вивести к-ть рядків в файлі
    //cout << strc << endl;
    fin.close();
    
    CheckDistance(strc, n);

    string command;
    char target[] = "ping 192.168.0.1 -c 1 > res.txt";
    int host = 5, out = 1, length[countip][countip];
    
    cin >> command;
    if (command[3] == target[3])
    {
        CalculateDistance(host, out, n, strc);
    }

    return 0;
}