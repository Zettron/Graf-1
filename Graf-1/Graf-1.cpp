#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <queue>

using namespace std;
#define word unsigned int

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
//
//int deikstry()
//{
//    Ip* n = new Ip[819];
//    int i, j, ping = 0, host = 5, on = 1;
//    queue<int>q;
//    while (!q.empty())
//    {
//
//    }
//}

//int pin(int h, int o)
//{
//    Ip* n = new Ip[819];
//    int i, j = 0, ping = 0, host = 1, on = 0, Istart = 0, Jstart = 0, b;
//    //while (1)
//    //{
//    host = h;
//    on = o;
//    ping = 0;
//    for (i = Istart; i < 819; i++)
//    {
//        if (host == n[i].getIp1())
//        {
//            if (n[i].getIp2() != on)
//            {
//                ping = 0;
//            }
//            else if (n[i].getIp2() == on)
//            {
//                ping = ping + 2;
//                return ping;
//            }
//            for (j = Jstart; j < 819; j++)
//            {
//                if (n[i].getIp2() == n[j].getIp1())
//                {
//                    ping = ping + 2;
//                    host = n[j].getIp1();
//                }
//            }
//        }
//
//    }
//    //}
//
//    /*for (i = 0; i < 819; i++)
//    {
//        if (host == on)
//        {
//            ping += 2;
//            return ping;
//        }
//        host = h;
//        on = o;
//        ping = 0;
//        if (host == n[i].getIp1() || on == n[i].getIp2())
//        {
//            ping += 2;
//            if (host == n[i].getIp1())
//            {
//                for (j = 0; j < 819; j++)
//                {
//                    if (n[i].getIp2() == n[j].getIp1())
//                    {
//                        host = n[j].getIp1();
//                        break;
//                    }
//                }
//            }
//            else if (on == n[i].getIp2())
//            {
//                for (j = 0; j < 819; j++)
//                {
//                    if (n[i].getIp2() == n[j].getIp1())
//                    {
//                        on = n[j].getIp2();
//                        break;
//                    }
//                }
//            }
//        }
//        else if (on == n[i].getIp2())
//        {
//            ping += 2;
//            for (j = 0; j < 819; j++)
//            {
//                if (n[i].getIp2() == n[j].getIp1())
//                {
//                    on = n[j].getIp2();
//                    break;
//                }
//            }
//        }
//    }*/
//}

int Ping()
{
    Ip* n = new Ip[819];
    int i = 0, j = 0, host = 5, serch = 1;
    int ping = 0, v[819];
    while(1)
    for (i; i < 819; i++)
    {
        if (n[i].getIp1() == host && v[i]!=0)
        {
            for (j; j < 819; j++)
            {
                if (n[j].getIp1() == n[i].getIp2())
                {
                    ping += 2;
                    i = -1;
                    host = n[j].getIp1();
                    break;
                }
            }
        }
    }
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
    int i, j=0;
    Ip* n = new Ip[819];
    string ips;

    for (i = 0; i < 819; i++)
    {
        fin >> ips;
        n[i].setIp(ips);
        //проверка читання файла
        //cout << n[i].getConnection() << endl;
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
       cout << endl << n[i].getIp1() << "->";
       cout << n[i].getIp2();
    }

    ofstream png("res.txt", ios_base::out);
    string command, target = "ping 192.168.0.1 -c 1 > res.txt";
    int ping , maxping;
    //cin >> command;
    //if (command == "ping 192.168.0.1 -c 1 > res.txt")
    //{

        //ping = pin(125, 114);
        //cout << ping << "ms";
        //png << ping;
    //}
    //cout << "max ping " << maxping << "ms";



    png.close();
    return 0;
}