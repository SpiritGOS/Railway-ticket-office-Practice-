#include <fstream>
#include <iostream>
#include <time.h>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <vector>

using namespace std;

struct passenger
{
    char FullName[96];
    int PassportSeries;
    int PassportNumber;
    tm Birthday;
};

struct schedule
{
    short NumOfRoute;
    char Station[16][32];
    tm Arrival[16];
    tm Departure[16];
    char NumOfStations;
};

struct ticket
{
    int NumOfTicket;
    passenger pass;
    short NumOfTrain;
    short NumOfCar;
    short NumOfPlace;
    char Departure[32];
    char Destination[32];
    tm Registration;
    tm Dep;
    bool Reserve;
    double Price;
};

void ShowListOfRoutes() //�������������� ����� ���������� ������� ���������� ���������...
{
    ifstream sch;
    sch.open("schedule.bin", ios::binary);
    schedule tmp;
    printf("%14s%32s%32s%32s\n\n", "����� ��������", "�������", "����� ��������", "����� �����������");
    while (sch.read((char *)&tmp, sizeof(tmp)))
    {
        printf("%14hu", tmp.NumOfRoute);
        printf("%32s", tmp.Station[0]);
        printf("%32c", '-');
        printf("%18i:%02i %02i.%02i.%04i\n", tmp.Departure[0].tm_hour, tmp.Departure[0].tm_min, tmp.Departure[0].tm_mday, tmp.Departure[0].tm_mon, tmp.Departure[0].tm_year);
        for (char i = 1; i < tmp.NumOfStations; i++)
        {
            printf("%14c", ' ');
            printf("%32s", tmp.Station[i]);
            printf("%18i:%02i %02i.%02i.%04i", tmp.Arrival[i].tm_hour, tmp.Arrival[i].tm_min, tmp.Arrival[i].tm_mday, tmp.Arrival[i].tm_mon, tmp.Arrival[i].tm_year);
            if (i != (tmp.NumOfStations - 1))
                printf("%18i:%02i %02i.%02i.%04i\n", tmp.Departure[i].tm_hour, tmp.Departure[i].tm_min, tmp.Departure[i].tm_mday, tmp.Departure[i].tm_mon, tmp.Departure[i].tm_year);
            else
                printf("%32c", '-');
        }
        printf("\n\n");
    }
}

void AddToListOfRoutes()
{
    fstream out;
    out.open("schedule.bin", ios::out | ios::binary | ios::app);
    schedule tmp;
    int x;
    char y[32];
Start:
    cout << "�������� ����" << endl
         << endl;
NumOfRoute:
    cout << "������� ����� ��������: ";
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    if (x < 0 or x > 32639)
    {
        cout << "������ �����. ������� ������������� �����!" << endl
             << endl;
        goto NumOfRoute;
    }
    tmp.NumOfRoute = x;
NumOfStations:
    cout << "������� ��������� ������� � ��������: ";
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    if (x > 16 or x < 2)
    {
        cout << "������ �����. ������� ���������� ������� �� 1 �� 16" << endl
             << endl;
        goto NumOfStations;
    }
    tmp.NumOfStations = x;
    for (char i = 0; i < tmp.NumOfStations; i++)
    {
        cout << "������� �������� �������: ";
        cin.clear();
        cin.get();
        cin.getline(y, 32, '\n');
        if (cin.fail()) //�������� �� ������ �����
        {
            cin.clear();             //������� ����� �����
            cin.ignore(32767, '\n'); //���������� ������
        }
        memcpy(tmp.Station[i], y, sizeof(tmp.Station[i]));
    Time:
        cout << "������� ����� ��������(����, ������, ����, �����, ���): ";
        cin >> x;
        if (cin.fail()) //�������� �� ������ �����
        {
            cin.clear();             //������� ����� �����
            cin.ignore(32767, '\n'); //���������� ������
        }
        if (x > 23 or x < 0)
        {
            cout << "������� ���� �� 0 �� 23!" << endl
                 << endl;
            goto Time;
        }
        tmp.Arrival[i].tm_hour = x;
        cin >> x;
        if (cin.fail()) //�������� �� ������ �����
        {
            cin.clear();             //������� ����� �����
            cin.ignore(32767, '\n'); //���������� ������
        }
        if (x > 59 or x < 0)
        {
            cout << "������� ������ �� 0 �� 59!" << endl
                 << endl;
            goto Time;
        }
        tmp.Arrival[i].tm_min = x;
        cin >> x;
        if (cin.fail()) //�������� �� ������ �����
        {
            cin.clear();             //������� ����� �����
            cin.ignore(32767, '\n'); //���������� ������
        }
        if (x > 31 or x < 1)
        {
            cout << "������� ���� �� 1 �� 31!" << endl
                 << endl;
            goto Time;
        }
        tmp.Arrival[i].tm_mday = x;
        cin >> x;
        if (cin.fail()) //�������� �� ������ �����
        {
            cin.clear();             //������� ����� �����
            cin.ignore(32767, '\n'); //���������� ������
        }
        if (x > 12 or x < 1)
        {
            cout << "������� ����� �� 1 �� 12!" << endl
                 << endl;
            goto Time;
        }
        tmp.Arrival[i].tm_mon = x;
        cin >> x;
        if (cin.fail()) //�������� �� ������ �����
        {
            cin.clear();             //������� ����� �����
            cin.ignore(32767, '\n'); //���������� ������
        }
        if (x < 1837)
        {
            cout << "������� ��� �� 1837!" << endl
                 << endl;
            goto Time;
        }
        tmp.Arrival[i].tm_year = x;
    TimeD:
        cout << "������� ����� �����������(����, ������, ����, �����, ���): ";
        cin >> x;
        if (cin.fail()) //�������� �� ������ �����
        {
            cin.clear();             //������� ����� �����
            cin.ignore(32767, '\n'); //���������� ������
        }
        if (x > 23 or x < 0)
        {
            cout << "������� ���� �� 0 �� 23!" << endl
                 << endl;
            goto TimeD;
        }
        tmp.Departure[i].tm_hour = x;
        cin >> x;
        if (cin.fail()) //�������� �� ������ �����
        {
            cin.clear();             //������� ����� �����
            cin.ignore(32767, '\n'); //���������� ������
        }
        if (x > 59 or x < 0)
        {
            cout << "������� ������ �� 0 �� 59!" << endl
                 << endl;
            goto TimeD;
        }
        tmp.Departure[i].tm_min = x;
        cin >> x;
        if (cin.fail()) //�������� �� ������ �����
        {
            cin.clear();             //������� ����� �����
            cin.ignore(32767, '\n'); //���������� ������
        }
        if (x > 31 or x < 1)
        {
            cout << "������� ���� �� 1 �� 31!" << endl
                 << endl;
            goto TimeD;
        }
        tmp.Departure[i].tm_mday = x;
        cin >> x;
        if (cin.fail()) //�������� �� ������ �����
        {
            cin.clear();             //������� ����� �����
            cin.ignore(32767, '\n'); //���������� ������
        }
        if (x > 12 or x < 1)
        {
            cout << "������� ����� �� 1 �� 12!" << endl
                 << endl;
            goto TimeD;
        }
        tmp.Departure[i].tm_mon = x;
        cin >> x;
        if (cin.fail()) //�������� �� ������ �����
        {
            cin.clear();             //������� ����� �����
            cin.ignore(32767, '\n'); //���������� ������
        }
        if (x < 1837)
        {
            cout << "������� ��� �� 1837!" << endl
                 << endl;
            goto TimeD;
        }
        tmp.Departure[i].tm_year = x;
        cout << endl
             << endl;
    }
    system("cls");
    cout << "��������� ��������� ������" << endl
         << endl;
    cout << "����� ��������: " << tmp.NumOfRoute << endl;
    cout << "���������� �������: " << (int)tmp.NumOfStations << endl;
    for (int i = 0; i < tmp.NumOfStations; i++)
    {
        cout << "�������: ";
        for (char c = 0; tmp.Station[i][c] != '\0' and c < 32; c++)
        {
            cout << tmp.Station[i][c];
        }
        cout << "\n����� ��������: " << tmp.Arrival[i].tm_hour << ':' << tmp.Arrival[i].tm_min << ' ' << tmp.Arrival[i].tm_mday << '.' << tmp.Arrival[i].tm_mon << '.' << tmp.Arrival[i].tm_year << endl;
        cout << "����� �����������: " << tmp.Departure[i].tm_hour << ':' << tmp.Departure[i].tm_min << ' ' << tmp.Departure[i].tm_mday << '.' << tmp.Departure[i].tm_mon << '.' << tmp.Departure[i].tm_year << endl;
    }
Choice:
    cout << endl
         << "������ �����? (1 - ��, 0 - ���): ";
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    switch (x)
    {
    case 1:
        out.write((char *)&tmp, sizeof(tmp));
        cout << "���� ������� ��������" << endl;
        break;
    case 0:
        system("cls");
        goto Start;
    default:
        cout << "������� �� 0 ��� 1 !" << endl;
        system("pause");
        goto Choice;
        break;
    }
}

void RemoveFromListOfRoutes()
{
    bool flag = 0;
    short x;
    cout << "������� ����" << endl
         << endl;
    ShowListOfRoutes();
    cout << "������� ����� ����� ������� ������ �������: ";
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    schedule tmp;
    fstream in, out;
    in.open("schedule.bin", ios::in | ios::binary);
    out.open("sch.bin", ios::out | ios::binary);
    while (in.read((char *)&tmp, sizeof(tmp)))
    {
        if (tmp.NumOfRoute == x)
        {
            flag = 1;
            continue;
        }
        out.write((char *)&tmp, sizeof(tmp));
    }
    in.close();
    out.close();
    remove("schedule.bin");
    rename("sch.bin", "schedule.bin");
    if (flag)
        cout << "���� ������� �����" << endl;
    else
        cout << "���� � ������ ������� �� ������" << endl;
}

void MainListOfRoutes()
{
    short tmp = 0;
choice:
    cout << "������� ������ ������" << endl
         << endl
         << "1.����������� ������ ������" << endl
         << "2.�������� ����" << endl
         << "3.������� ����" << endl
         << "4.�������� � ������� ����" << endl;
    cin >> tmp;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    switch (tmp)
    {
    case 1:
        system("cls");
        ShowListOfRoutes();
        system("pause");
        break;
    case 2:
        system("cls");
        AddToListOfRoutes();
        system("pause");
        break;
    case 3:
        system("cls");
        RemoveFromListOfRoutes();
        system("pause");
        break;
    case 4:
        return;
    default:
        cout << "������� �� ����� �� 1 �� 4 !" << endl;
        system("pause");
        system("cls");
        goto choice;
    }
}

void BuyTicket()
{
    srand(time(NULL));
    bool flag = 0;
    bool flag2 = 0;
    schedule sch;
    ifstream sch_f;
    fstream out;
    out.open("tickets.bin", ios::in | ios::out | ios::binary | ios::app);
    vector<schedule> routes;
    vector<tm> rtt;
    char y[32];
    ticket cur;
    ticket cr;
    passenger pass;
    fstream psg;
Buying:
    cout << "������������� �����" << endl
         << endl;
    int x;
StationD:
    sch_f.open("schedule.bin", ios::binary);
    cout << "������� ������� �����������: ";
    cin.clear();
    cin.get();
    memset(y, '\0', 32);
    cin.getline(y, 32, '\n');
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    while (sch_f.read((char *)&sch, sizeof(sch)))
    {
        for (char i = 0; i < sch.NumOfStations; i++)
        {
            if ((strcmp(y, sch.Station[i]) == 0) and (i != sch.NumOfStations - 1))
            {
                routes.push_back(sch);
                rtt.push_back(sch.Departure[i]);
            }
        }
    }
    if (routes.empty())
    {
        cout << "������� ������� �������" << endl
             << endl;
        sch_f.close();
        goto StationD;
    }
    memcpy(cur.Departure, y, sizeof(cur.Departure));
    vector<schedule> tmp;
    vector<tm> rt;
StationS:
    rt = rtt;
    tmp = routes;
    cout << "������� ������� ����������: ";
    cin.clear();
    cin.getline(y, 32, '\n');
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    if (strcmp(y, cur.Departure) == 0)
    {
        cout << "������� ����������� � ������� ���������� �� ������ ���������!" << endl;
        goto StationS;
    }
    for (char i = 0; i < tmp.size(); i++)
    {
        flag = 0;
        for (char j = 0; j < tmp[i].NumOfStations; j++)
        {
            if (((strcmp(y, tmp[i].Station[j])) == 0) and (j != 0))
            {
                flag = 1;
            }
        }
        if (!flag)
        {
            tmp.erase(tmp.cbegin() + i);
            rt.erase(rt.cbegin() + i--);
        }
    }
    if (tmp.empty())
    {
        cout << "������� ������� �������" << endl;
        goto StationS;
    }
    memcpy(cur.Destination, y, sizeof(cur.Destination));
Select:
    cout << "\n�������� ������� ����:\n\n";
    char m = 0;
    for (; m != tmp.size(); m++)
    {
        cout << m + 1 << ") " << rt[m].tm_hour << ':' << rt[m].tm_min << ' ' << rt[m].tm_mday << '.' << rt[m].tm_mon << '.' << rt[m].tm_year << endl;
    }
    m--;
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    if (x < 1)
    {
        cout << "������������ �����!" << endl;
        goto Select;
    }
    cur.Dep = rt[m];
    fstream pas("tickets.bin", ios::in | ios::binary | ios::app);
    pas.seekg(sizeof(cr), ios::end);
    pas.read((char *)&cr, sizeof(cr));
    cur.NumOfTicket = cr.NumOfTicket + 1;
    pas.close();

    cout << "������� ���� ���: ";
    cin.get();
    cin.clear();
    cin.getline(pass.FullName, 96);
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
Passport:
    cout << "������� ����� � ����� ��������: ";
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    if (x < 0 or x > 9999)
    {
        cout << "������������ ����� ��������" << endl;
        goto Passport;
    }
    pass.PassportSeries = x;
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    if (x < 00001 or x > 999999)
    {
        cout << "������������ ����� ��������" << endl;
        goto Passport;
    }
    pass.PassportNumber = x;
Birth:
    cout << "������� ���� ��������: ";
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    if (x < 1 or x > 31)
    {
        cout << "����������� ������ ����" << endl;
        goto Birth;
    }
    pass.Birthday.tm_mday = x;
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    if (x < 1 or x > 12)
    {
        cout << "����������� ������ �����" << endl;
        goto Birth;
    }
    pass.Birthday.tm_mon = x;
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    if (x < 1863)
    {
        cout << "����������� ������ ���" << endl;
        goto Birth;
    }
    pass.Birthday.tm_year = x;
Train:
    cur.NumOfTrain = 1 + rand() % 10000;
    cout << "�������� ����� ������: ";
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    if (x < 1 or x > 20)
    {
        cout << "����������� ������ ����� ������" << endl;
        goto Train;
    }
    cur.NumOfCar = x;
    cout << "�������� ����� �����: ";
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    if (x < 1 or x > 50)
    {
        cout << "����������� ������ ����� �����" << endl;
        goto Train;
    }
    cur.NumOfPlace = x;
    cur.pass = pass;
    system("cls");
    cout << "��������� ������������ ��������� ������" << endl
         << endl;
    printf("������� �����������: %s\n", cur.Departure);
    printf("������� ����������: %s\n", cur.Destination);
    printf("����� �������: %02i:%02i %02i.%02i.%04i\n", cur.Dep.tm_hour, cur.Dep.tm_min, cur.Dep.tm_mday, cur.Dep.tm_mon, cur.Dep.tm_year);
    printf("����� ������: %04i\n", cur.NumOfTrain);
    printf("����� ������: %02i\n", cur.NumOfCar);
    printf("����� �����: %02i\n", cur.NumOfPlace);
    printf("��� ���������: %s\n", cur.pass.FullName);
    printf("����� � ����� ��������: %04i %06i\n", cur.pass.PassportSeries, cur.pass.PassportNumber);
    cur.Price = 1 + rand() % 100;
    printf("���� ������: %04.2f$\n", cur.Price);
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    cur.Registration = *timeinfo;
    printf("����� ���������� ������: %02i:%02i %02i.%02i.%04i\n", cur.Registration.tm_hour, cur.Registration.tm_min, cur.Registration.tm_mday, 1 + cur.Registration.tm_mon, 1900 + cur.Registration.tm_year);
Choice:
    cout << endl
         << "������ �����? (1 - ��, 0 - ���): ";
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    switch (x)
    {
    case 1:
        psg.open("passengers.bin", ios::binary | ios::out | ios::app);
        psg.write((char *)&pass, sizeof(pass));
        out.write((char *)&cur, sizeof(cur));
        cout << "����� ������� ��������" << endl;
        break;
    case 0:
        system("cls");
        goto Buying;
    default:
        cout << "������� �� 0 ��� 1 !" << endl;
        system("pause");
        goto Choice;
        break;
    }
}

void BookTicket()
{
    srand(time(NULL));
    bool flag = 0;
    bool flag2 = 0;
    schedule sch;
    ifstream sch_f;
    fstream out;
    out.open("tickets.bin", ios::in | ios::out | ios::binary | ios::app);
    vector<schedule> routes;
    vector<tm> rtt;
    char y[32];
    ticket cur;
    ticket cr;
    passenger pass;
    fstream psg;
Buying:
    cout << "������������� �����" << endl
         << endl;
    int x;
    sch_f.open("schedule.bin", ios::binary);
StationD:
    cout << "������ ������������� �����?(0 - ���, 1 - ��): ";
    cin >> x;
    if (x != 0 and x != 1)
    {
        cout << "������������ ����" << endl;
        goto StationD;
    }
    if (x == 0)
    {
        return;
    }
    cout << "������� ������� �����������: ";
    cin.clear();
    cin.get();
    memset(y, '\0', 32);
    cin.getline(y, 32, '\n');
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    while (sch_f.read((char *)&sch, sizeof(sch)))
    {
        for (char i = 0; i < sch.NumOfStations; i++)
        {
            if ((strcmp(y, sch.Station[i]) == 0) and (i != sch.NumOfStations - 1))
            {
                routes.push_back(sch);
                rtt.push_back(sch.Departure[i]);
            }
        }
    }
    if (routes.empty())
    {
        cout << "������� ������� �������" << endl
             << endl;
        sch_f.close();
        goto StationD;
    }
    memcpy(cur.Departure, y, sizeof(cur.Departure));
    vector<schedule> tmp;
    vector<tm> rt;
StationS:
    rt = rtt;
    tmp = routes;
    cout << "������� ������� ����������: ";
    cin.clear();
    cin.getline(y, 32, '\n');
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    if (strcmp(y, cur.Departure) == 0)
    {
        cout << "������� ����������� � ������� ���������� �� ������ ���������!" << endl;
        goto StationS;
    }
    for (char i = 0; i < tmp.size(); i++)
    {
        flag = 0;
        for (char j = 0; j < tmp[i].NumOfStations; j++)
        {
            if (((strcmp(y, tmp[i].Station[j])) == 0) and (j != 0))
            {
                flag = 1;
            }
        }
        if (!flag)
        {
            tmp.erase(tmp.cbegin() + i);
            rt.erase(rt.cbegin() + i--);
        }
    }
    if (tmp.empty())
    {
        cout << "������� ������� �������" << endl;
        goto StationS;
    }
    memcpy(cur.Destination, y, sizeof(cur.Destination));
Select:
    cout << "\n�������� ������� ����:\n\n";
    char m = 0;
    for (; m != tmp.size(); m++)
    {
        cout << m + 1 << ") " << rt[m].tm_hour << ':' << rt[m].tm_min << ' ' << rt[m].tm_mday << '.' << rt[m].tm_mon << '.' << rt[m].tm_year << endl;
    }
    m--;
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    if (x < 1)
    {
        cout << "������������ �����!" << endl;
        goto Select;
    }
    cur.Dep = rt[m];
    fstream pas("tickets.bin", ios::in | ios::binary | ios::app);
    pas.seekg(sizeof(cr), ios::end);
    pas.read((char *)&cr, sizeof(cr));
    cur.NumOfTicket = cr.NumOfTicket + 1;
    pas.close();

    cout << "������� ���� ���: ";
    cin.get();
    cin.clear();
    cin.getline(pass.FullName, 96);
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
Passport:
    cout << "������� ����� � ����� ��������: ";
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    if (x < 0 or x > 9999)
    {
        cout << "������������ ����� ��������" << endl;
        goto Passport;
    }
    pass.PassportSeries = x;
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    if (x < 00001 or x > 999999)
    {
        cout << "������������ ����� ��������" << endl;
        goto Passport;
    }
    pass.PassportNumber = x;
Birth:
    cout << "������� ���� ��������: ";
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    if (x < 1 or x > 31)
    {
        cout << "����������� ������ ����" << endl;
        goto Birth;
    }
    pass.Birthday.tm_mday = x;
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    if (x < 1 or x > 12)
    {
        cout << "����������� ������ �����" << endl;
        goto Birth;
    }
    pass.Birthday.tm_mon = x;
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    if (x < 1863)
    {
        cout << "����������� ������ ���" << endl;
        goto Birth;
    }
    pass.Birthday.tm_year = x;
Train:
    cur.NumOfTrain = 1 + rand() % 10000;
    cout << "�������� ����� ������: ";
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    if (x < 1 or x > 20)
    {
        cout << "����������� ������ ����� ������" << endl;
        goto Train;
    }
    cur.NumOfCar = x;
    cout << "�������� ����� �����: ";
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    if (x < 1 or x > 50)
    {
        cout << "����������� ������ ����� �����" << endl;
        goto Train;
    }
    cur.NumOfPlace = x;
    cur.pass = pass;
    system("cls");
    cout << "��������� ������������ ��������� ������" << endl
         << endl;
    printf("������� �����������: %s\n", cur.Departure);
    printf("������� ����������: %s\n", cur.Destination);
    printf("����� �������: %02i:%02i %02i.%02i.%04i\n", cur.Dep.tm_hour, cur.Dep.tm_min, cur.Dep.tm_mday, cur.Dep.tm_mon, cur.Dep.tm_year);
    printf("����� ������: %04i\n", cur.NumOfTrain);
    printf("����� ������: %02i\n", cur.NumOfCar);
    printf("����� �����: %02i\n", cur.NumOfPlace);
    printf("��� ���������: %s\n", cur.pass.FullName);
    printf("����� � ����� ��������: %04i %06i\n", cur.pass.PassportSeries, cur.pass.PassportNumber);
    cur.Price = 1 + rand() % 100;
    printf("���� ������: %04.2f$\n", cur.Price);
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    cur.Registration = *timeinfo;
    printf("����� ���������� ������: %02i:%02i %02i.%02i.%04i\n", cur.Registration.tm_hour, cur.Registration.tm_min, cur.Registration.tm_mday, 1 + cur.Registration.tm_mon, 1900 + cur.Registration.tm_year);
Choice:
    cout << endl
         << "������ �����? (1 - ��, 0 - ���): ";
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    switch (x)
    {
    case 1:
        psg.open("passengers.bin", ios::binary | ios::out | ios::app);
        psg.write((char *)&pass, sizeof(pass));
        out.write((char *)&cur, sizeof(cur));
        cout << "����� ������� ��������" << endl;
        break;
    case 0:
        system("cls");
        goto Buying;
    default:
        cout << "������� �� 0 ��� 1 !" << endl;
        system("pause");
        goto Choice;
        break;
    }
}

void RefundTicket()
{
    int x;
    int Series, Number;
    cout << "������� �����" << endl
         << endl;
Passport:
    cout << "������� ����� � ����� ��������: ";
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    if (x < 0 or x > 9999)
    {
        cout << "������������ ����� ��������" << endl;
        goto Passport;
    }
    Series = x;
    cin >> x;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    if (x < 00001 or x > 999999)
    {
        cout << "������������ ����� ��������" << endl;
        goto Passport;
    }
    bool flag = 1;
    ticket tmp;
    Number = x;
    fstream in, out;
    in.open("tickets.bin", ios::in | ios::binary);
    out.open("tck.bin", ios::out | ios::binary);
    while (in.read((char *)&tmp, sizeof(tmp)))
    {
        if (tmp.pass.PassportNumber == Number and tmp.pass.PassportSeries == Series)
        {
            flag = 1;
            continue;
        }
        out.write((char *)&tmp, sizeof(tmp));
    }
    in.close();
    out.close();
    remove("tickets.bin");
    rename("tck.bin", "tickets.bin");
}

void BookingSaleRefundOfTickets()
{
    short tmp = 0;
choice:
    cout << "������������, ������� � ������� �������" << endl
         << endl
         << "1.������ �����" << endl
         << "2.������������� �����" << endl
         << "3.������� �����" << endl
         << "4.�������� � ������� ����" << endl;
    cin >> tmp;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    switch (tmp)
    {
    case 1:
        system("cls");
        BuyTicket();
        break;
    case 2:
        system("cls");
        BookTicket();
        break;
    case 3:
        system("cls");
        RefundTicket();
        break;
    case 4:
        return;
    default:
        cout << "������� �� ����� �� 1 �� 4 !" << endl;
        system("pause");
        system("cls");
        goto choice;
    }
}

void PassengerAccounting()
{
    ticket psg;
    ifstream in;
    in.open("tickets.bin", ios::binary | ios::app | ios::in);
    cout << "���� ����������" << endl
         << endl;
    printf("%12s%32s%16s%16s%16s%18s%28s%28s", "����� ������", "��� ���������", "����� ��������", "����� ��������", "���� ��������", "����� �����������", "������� �����������", "������� ����������\n\n");
    while (in.read((char *)&psg, sizeof(psg)))
    {
        printf("%12i", psg.NumOfTicket);
        printf("%32s", psg.pass.FullName);
        printf("%16i", psg.pass.PassportSeries);
        printf("%16i", psg.pass.PassportNumber);
        printf("      %02i.%02i.%04i", psg.pass.Birthday.tm_mday, psg.pass.Birthday.tm_mon, psg.pass.Birthday.tm_year);
        printf("  %02i:%02i %02i.%02i.%04i", psg.Dep.tm_hour, psg.Dep.tm_min, psg.Dep.tm_mday, psg.Dep.tm_mon, psg.Dep.tm_year);
        printf("%28s", psg.Departure);
        printf("%27s\n", psg.Destination);
    }
    system("pause");
}

void menu()
{
    short tmp = 0;
choice:
    cout << "����� ��� 2.0" << endl
         << endl
         << "1.������� ������ ������" << endl
         << "2.������������, ������� � ������� �������" << endl
         << "3.���� ����������" << endl
         << "4.����� �� ���������" << endl;
    cin >> tmp;
    if (cin.fail()) //�������� �� ������ �����
    {
        cin.clear();             //������� ����� �����
        cin.ignore(32767, '\n'); //���������� ������
    }
    switch (tmp)
    {
    case 1:
        system("cls");
        MainListOfRoutes();
        system("cls");
        goto choice;
        break;
    case 2:
        system("cls");
        BookingSaleRefundOfTickets();
        system("cls");
        goto choice;
        break;
    case 3:
        system("cls");
        PassengerAccounting();
        system("cls");
        goto choice;
        break;
    case 4:
        return;
    default:
        cout << "������� �� ����� �� 1 �� 4 !" << endl;
        system("pause");
        system("cls");
        goto choice;
    }
}

int main()
{
    system("chcp 1251");
    system("cls");
    menu();
}