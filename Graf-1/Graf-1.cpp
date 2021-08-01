#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

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

int Ping(int start, int finish, Ip* n)
{
    int length[127][127], a = 0, b = 0, i=0, j=0, s=0;

    for (j=0; j < 127; j++)
    {
        for (i = 0; i < 127; i++)
        {
             length[j][i] = 0;   
        }
    }

    for (i=0; i < 819; i++)
    {
        a = n[i].getIp1();
        b = n[i].getIp2();

        if (a != b)
        {
            length[a][b] = 2;
        }
        
    }
    
    for (int p = 0; p < 819; p++)
    {
        s = start;
        for (i = 0; i < 819; i++)
        {
            if (s == n[i].getIp1())
            {
                for (j = 0; j < 819; j++)
                {
                    if (n[i].getIp2() == n[j].getIp1())
                    {
                        
                        if (length[s][n[j].getIp2()] == 0 || length[s][n[j].getIp2()] > length[s][n[i].getIp2()] + 2)
                        {
                            length[n[i].getIp1()][n[j].getIp2()] = length[n[i].getIp1()][n[i].getIp2()] + 2;
                            s = n[j].getIp1();
                        }
                        

                        /*if (length[n[i].getIp1()][n[j].getIp2()] ==0)
                            length[n[i].getIp1()][n[j].getIp2()] = length[n[i].getIp1()][n[i].getIp2()] + 2;*/

                            /*else if (length[n[i].getIp1()][n[j].getIp2()] > length[n[i].getIp1()][n[i].getIp2()] + 2)
                                length[n[i].getIp1()][n[j].getIp2()] = length[n[i].getIp1()][n[i].getIp2()] + 2;*/


                    }
                    

                }
                
            }
        }
    }

    int fir=0, sec=0, maxping=0;

    for (i = 0; i < 127; i++)
    {
        for (j = 0; j < 127; j++)
        {
            if (maxping < length[n[i].getIp1()][n[j].getIp2()])
            {
                maxping = length[n[i].getIp1()][n[j].getIp2()];
                fir = n[i].getIp1();
                sec = n[j].getIp2();
            }
        }
    }
    cout << "->maxping from 192.168.0." << fir << " to 192.168.0." << sec << " - " << maxping << "ms\n";


    //вивід на екран
    /*for (i=0; i < 127; i++)
    {
        for (j=0; j < 127; j++)
        {

            cout << length[i][j] << " ";
        }
        cout << endl << endl;
    }*/
    

    return length[start][finish];
}

int main()
{
    setlocale(0, "ukr.UTF-8");
    ifstream fin;
    cout << "\tDebian 10\n";
    fin.open("G1.csv");
    if (!fin.is_open())
    {
        cout << "Error opening file G1.csv";
        return 0;
    }
    else if (fin.is_open())
    {
        cout << "The file G1.csv is open\n";
    }
    int i=0, j=0;
    Ip* n = new Ip[819];
    string ips;

    for (i = 0; i < 819; i++)
    {
        fin >> ips;
        n[i].setIp(ips);
    }
    fin.close();
    
    int x=0, y=0, d=1, sum=0;
    int g;
    char coma = ',', point ='.';
    for (i = 0; i < 819; i++)
    {
        ips = n[i].getConnection();
        for (j = ips.length() - 1; ips[j] != point; j--)
        {
            x = (int)ips[j];
            x -= 48;
            sum += x * d;
            d *= 10;
            if(ips[j-1] == point)
                n[i].setIp2(sum);
        }
        sum = 0;
        d = 1;
        for (j = 13 ; j >= 10; j--)
        {   
            if (ips[j] == coma)
            {
                g = j-1;
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
       /*cout << endl << n[i].getIp1() << "->";
       cout << n[i].getIp2();*/
    }
    cout << endl;
    ofstream png("res.txt", ios_base::out);
    string command;
    char target[] = "ping 192.168.0.1 -c 1 > res.txt";
    int ping, host = 5, out = 1;

    cin >> command;
    if (command[1] == target[1])
    {
        cout << endl;
        ping = Ping(5, 1, n);
        png << ping;
        cout << "\n->ping from 192.168.0.5 to 192.168.0.1 - " << ping << "ms\n";
    }

    png.close();
    return 0;
}