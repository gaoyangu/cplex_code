#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <math.h>
#include <fstream>
#include <sstream>

#include <ilcplex/ilocplex.h>

#include "Data.h"
#include "CSVReader.h"

using namespace std;

ILOSTLBEGIN

typedef IloArray<IloNumVarArray> NumVarMatrix;
vector<vector<string>> strArray;		//����
vector<vector<string>> portsArray;		//�ǻ���
vector<vector<string>> resultArray;
vector<vector<string>> ticketsArray;	//�ÿ�
vector<vector<string>> passengerArray;	//Ԥ�������ÿ�
vector<int> v1;
vector<int> v2;

int time(string date, string str)
{
    int t = 0;
    int pos = str.find(':');
    string hour = str.substr(0, pos);
    string mininute = str.substr(pos + 1, 2);
    //cout << "hour = " << hour << "," << "min = " << mininute << endl;

    if (date.substr(0, 2) == "19") {
        t = -24 * 60 + stoi(hour) * 60 + stoi(mininute);
    }
    else if (date.substr(0, 2) == "20") {
        t = stoi(hour) * 60 + stoi(mininute);
    }
    else if (date.substr(0, 2) == "21") {
        t = 24 * 60 + stoi(hour) * 60 + stoi(mininute);
    }

    return t;
}

int type(string str)
{
    int tmp = 0;

    if (str == "D") {
        tmp = 0;
    }
    else if (str == "I") {
        tmp = 1;
    }
    else
    {
        tmp = 2;
    }
    return tmp;
}

string plane_type(string str)
{
    string c;
    if (str == "332" || str == "333" || str == "33E" || str == "33H" || str == "33L" || str == "773") {
        c = 'W';
    }
    else if (str == "319" || str == "320" || str == "321" || str == "323" || str == "325" || str == "738" || str == "73A" || str == "73E" || str == "73H" || str == "73L") {
        c = 'N';
    }
    return c;
}

int main()
{
    int f_Num = 0;  //��������
    int p_Num = 0;  //�ǻ�������
    int t_Num = 0;  //�ÿ�����

    Data data;

	CSVReader reader_pucks("Pucks.csv");	
	strArray = reader_pucks.getData();
	CSVReader reader_ports("Gates.csv");
	portsArray = reader_ports.getData();
	CSVReader reader_ticks("Ticks.csv");
	ticketsArray = reader_ticks.getData();

    //�ɻ�ת����¼Ԥ����
    for (int i = 0; i < strArray.size(); i++) {
        Flight flight;
        string tmp_at = strArray.at(i).at(1);   //��������
        string tmp_lt = strArray.at(i).at(6);   //��������

        if ((tmp_at.substr(0, 2) == "20") || (tmp_lt.substr(0, 2) == "20")) {

            if (tmp_at.substr(0, 2) == "19") {
                //flight.name = strArray.at(i).at(0);
                flight.name = f_Num;
                flight.startTime = time("19", strArray.at(i).at(2));
                flight.endTime = time("20", strArray.at(i).at(7));
                flight.arriveType = type(strArray.at(i).at(4));
                flight.leaveType = type(strArray.at(i).at(9));
                flight.planeType = plane_type(strArray.at(i).at(5));

                flight.arriveNum = strArray.at(i).at(3);
                flight.leaveNum = strArray.at(i).at(8);

                data.flightList.push_back(flight);
            }
            if (tmp_at.substr(0, 2) == "20") {
                if (tmp_lt.substr(0, 2) == "20") {
                    //flight.name = strArray.at(i).at(0);
                    flight.name = f_Num;
                    flight.startTime = time("20", strArray.at(i).at(2));
                    flight.endTime = time("20", strArray.at(i).at(7));
                    flight.arriveType = type(strArray.at(i).at(4));
                    flight.leaveType = type(strArray.at(i).at(9));
                    flight.planeType = plane_type(strArray.at(i).at(5));

                    flight.arriveNum = strArray.at(i).at(3);
                    flight.leaveNum = strArray.at(i).at(8);

                    data.flightList.push_back(flight);
                }
                else if (tmp_lt.substr(0, 2) == "21") {
                    //flight.name = strArray.at(i).at(0);
                    flight.name = f_Num;
                    flight.startTime = time("20", strArray.at(i).at(2));
                    flight.endTime = time("21", strArray.at(i).at(7));
                    flight.arriveType = type(strArray.at(i).at(4));
                    flight.leaveType = type(strArray.at(i).at(9));
                    flight.planeType = plane_type(strArray.at(i).at(5));

                    flight.arriveNum = strArray.at(i).at(3);
                    flight.leaveNum = strArray.at(i).at(8);

                    data.flightList.push_back(flight);
                }
            }
            f_Num++;
        }
    }
    data.flightNum = f_Num;
    cout << "[info]: 20�յ���ͳ����ĺ��๲�У�" << f_Num << endl;

    /*ofstream outFile;
    outFile.open("flight.csv", ios::out);
    for (int i = 0; i < data.flightNum; i++) {
        outFile << data.flightList[i].name << ","
                << data.flightList[i].arriveNum << ","
                << data.flightList[i].leaveNum << ","
                << data.flightList[i].planeType << ","
                << data.flightList[i].startTime << ","
                << data.flightList[i].endTime << ","
                << data.flightList[i].arriveType << ","
                << data.flightList[i].leaveType << endl;
    }
    outFile.close();*/

    /*for (int i = 0; i < data.flightList.size(); i++) {
        cout << data.flightList.at(i).name << " " << data.flightList.at(i).startTime << " "
            << data.flightList.at(i).arriveType << " " << data.flightList.at(i).endTime << " "
            << data.flightList.at(i).leaveType << " " << data.flightList.at(i).planeType << endl;
    }*/

    //�ǻ���
    for (int i = 0; i < portsArray.size(); i++) {
        Deport deport;
        deport.name = portsArray.at(i).at(0);
        deport.location = portsArray.at(i).at(1);
        deport.area = portsArray.at(i).at(2);
        deport.arriveType = type(portsArray.at(i).at(3));
        deport.leaveType = type(portsArray.at(i).at(4));
        deport.planeType = portsArray.at(i).at(5);

        data.deportList.push_back(deport);
        p_Num++;
    }
    data.parkNum = p_Num;
    cout << "[info]: ���еǻ��ڣ�" << p_Num << endl;

    /*for (int i = 0; i < data.deportList.size(); i++) {
        cout << i << " "
            << data.deportList.at(i).name << " " << data.deportList.at(i).location << " "
            << data.deportList.at(i).area<< " " << data.deportList.at(i).arriveType << " "
            << data.deportList.at(i).leaveType << " " << data.deportList.at(i).planeType << endl;
    }*/

    //�ÿ�����Ԥ����
    for (int i = 0; i < ticketsArray.size(); i++) {
        string tmp_at = ticketsArray.at(i).at(3);
        string tmp_lt = ticketsArray.at(i).at(5);
        if ((tmp_at.substr(0, 2) == "20") || (tmp_lt.substr(0, 2) == "20")) {
            Passenger passenger;
            //cout << ticketsArray.at(i).at(0) << " : "<< ticketsArray.at(i).at(1) << endl;
            t_Num += stoi(ticketsArray.at(i).at(1));

            //����Ԥ����
            for (int j = 0; j < data.flightList.size(); j++) {
                if (ticketsArray.at(i).at(2) == data.flightList.at(j).arriveNum) {
                    passenger.passengerNum = stoi(ticketsArray.at(i).at(1));
                    passenger.arriveFlight = data.flightList.at(j).name;
                }
                if (ticketsArray.at(i).at(4) == data.flightList.at(j).leaveNum) {
                    passenger.passengerNum = stoi(ticketsArray.at(i).at(1));
                    passenger.leaveFlight = data.flightList.at(j).name;
                }
            }
            data.passengerList.push_back(passenger);
        }
    }
    data.passengerNum = t_Num;
    cout << "[info]: 20�Ź��г˿ͣ�" << t_Num << endl;

 //   /*for (int i = 0; i < data.passengerList.size(); i++) {
 //       cout << i << " "
 //           << data.passengerList.at(i).passengerNum << " "
 //           << data.passengerList.at(i).arriveFlight << " "
 //           << data.passengerList.at(i).leaveFlight << endl;
 //   }*/

    /*ofstream outFile;
    outFile.open("passenger.csv", ios::out);

    for (int i = 0; i < data.passengerList.size(); i++) {
        outFile << data.passengerList[i].passengerNum << ","
            << data.passengerList[i].arriveFlight << ","
            << data.passengerList[i].leaveFlight << endl;
    }
    outFile.close();*/

    //�ȴ�Ԥ����ĳ˿�����
	CSVReader reader_passenger("passenger.csv");
	passengerArray = reader_passenger.getData();
	
    data.passengerList.clear();

    Passenger p_tmp;
    //cout << passengerArray.at(0).at(0) << endl;
    //cout << passengerArray.at(0).at(1) << endl;
    //cout << passengerArray.at(0).at(2) << endl;
    p_tmp.passengerNum = stoi(passengerArray.at(0).at(0));
    p_tmp.arriveFlight = stoi(passengerArray.at(0).at(1));
    p_tmp.leaveFlight = stoi(passengerArray.at(0).at(2));

    for (int i = 0; i < passengerArray.size(); i++) {
        int index = i + 1;
        if (index == passengerArray.size()) {
            p_tmp.passengerNum = stoi(passengerArray.at(index - 1).at(0));
            p_tmp.arriveFlight = stoi(passengerArray.at(index - 1).at(1));
            p_tmp.leaveFlight = stoi(passengerArray.at(index - 1).at(2));
            data.passengerList.push_back(p_tmp);
            break;
        }
        if ((p_tmp.arriveFlight == stoi(passengerArray.at(index).at(1))) &&
            (p_tmp.leaveFlight == stoi(passengerArray.at(index).at(2)))) {
            p_tmp.passengerNum += stoi(passengerArray.at(index).at(0));
        }
        else {
            data.passengerList.push_back(p_tmp);
            p_tmp.passengerNum = stoi(passengerArray.at(index).at(0));
            p_tmp.arriveFlight = stoi(passengerArray.at(index).at(1));
            p_tmp.leaveFlight = stoi(passengerArray.at(index).at(2));
        }
    }

    int n = 0;
    for (int i = 0; i < data.passengerList.size(); i++) {
        n += data.passengerList.at(i).passengerNum;
        /*cout << i << " "
            << data.passengerList.at(i).passengerNum << " "
            << data.passengerList.at(i).arriveFlight << " "
            << data.passengerList.at(i).leaveFlight << endl;*/
    }
    data.passengerNum = n;
    //cout << "data.passengerList.size() = "<< data.passengerList.size() << endl;
    cout << "[info]: �����ϲ�������г˿ͣ�" << n << endl;

	/*fstream outFile;
	outFile.open("processed_pass.csv", ios::out);

	for (int i = 0; i < data.passengerList.size(); i++) {
		outFile << i << ","
			<< data.passengerList.at(i).passengerNum << ","
			<< data.passengerList.at(i).arriveFlight << ","
			<< data.passengerList.at(i).leaveFlight << endl;
	}
	outFile.close();*/

    //��ʼ�� isTypeMatching �� isConflict
    for (int i = 0; i < data.flightList.size(); i++) {
        vector<int> v;
        for (int j = 0; j < data.deportList.size(); j++) {
            v.push_back(0);
        }
        data.isTypeMatching.push_back(v);
    }
    for (int i = 0; i < data.flightList.size(); i++) {
        vector<int> v;
        for (int j = 0; j < data.flightList.size(); j++) {
            v.push_back(1);
        }
        data.isConflict.push_back(v);
    }

    //w_ij ���� i ��ǻ��� j �����Ƿ�ƥ��
    for (int i = 0; i < data.flightList.size(); i++) {
        for (int j = 0; j < data.deportList.size(); j++) {
            if ((data.flightList.at(i).arriveType == data.deportList.at(j).arriveType || data.deportList.at(j).arriveType == 2) &&
                (data.flightList.at(i).leaveType == data.deportList.at(j).leaveType || data.deportList.at(j).leaveType == 2) &&
                (data.flightList.at(i).planeType == data.deportList.at(j).planeType)) {
                data.isTypeMatching.at(i).at(j) = 1;    //��
            }
            else {
                data.isTypeMatching.at(i).at(j) = 0;    //��
            }
        }
    }

    //p_i1i2 ���� i1 �ͺ��� i2 �Ƿ��ͻ
    for (int i = 0; i < data.flightList.size(); i++) {
        for (int j = 0; j < data.flightList.size(); j++) {
            if (i == j)
                continue;
            Flight flight1 = data.flightList.at(i);
            Flight flight2 = data.flightList.at(j);
            data.isConflict[i][j] = 1;  //��ͻ
            if ((flight1.endTime + 45 <= flight2.startTime) || (flight1.startTime - 45 >= flight2.endTime)) {
                data.isConflict[i][j] = 0;  //û�г�ͻ
            }
        }
    }

    cout << "----------cplex------------" << endl;
    IloEnv env;
    try {
        IloModel model(env);

        //��ʼ�����߱���
        NumVarMatrix xVar(env, data.flightNum);
        IloNumVarArray yVar(env, data.parkNum);
        IloNumVarArray flightLocation1(env, data.flightNum);
        IloNumVarArray flightLocation2(env, data.flightNum);

        for (int i = 0; i < data.flightNum; i++) {
            xVar[i] = IloNumVarArray(env, data.parkNum, 0, 1, ILOINT);
        }
        for (int i = 0; i < data.parkNum; i++) {
            yVar[i] = IloNumVar(env, 0, 1, ILOINT);
        }
        for (int i = 0; i < data.flightNum; i++) {
            flightLocation1[i] = IloNumVar(env, 0, 1, ILOINT);
        }
        for (int i = 0; i < data.flightNum; i++) {
            flightLocation2[i] = IloNumVar(env, 0, 1, ILOINT);
        }

        //�Ż�Ŀ��
        IloNumExpr obj1(env);
        for (int i = 0; i < data.flightNum; i++) {
            for (int j = 0; j < data.parkNum; j++) {
                obj1 += xVar[i][j];
            }
        }
        IloNumExpr obj2(env);
        for (int i = 0; i < data.parkNum; i++) {
            obj2 += yVar[i];
        }

        cout << "��ʼ�� obj3" << endl;
        IloNumExpr obj3(env);

        for (int i = 0; i < data.passengerList.size(); i++) {
            int pArrive = data.passengerList[i].arriveFlight;
            int pLeave = data.passengerList[i].leaveFlight;
            int index = 2 * data.flightList.at(pArrive).arriveType + data.flightList.at(pLeave).leaveType;

            //cout << i << " " << pArrive << " " << pLeave << " " << index << " " << data.passengerList.at(i).passengerNum  << endl;
            IloNumExpr exp(env);
            exp += flightLocation1[pArrive] * flightLocation1[pLeave] * data.tranTime[index][0];
            exp += flightLocation1[pArrive] * flightLocation2[pLeave] * data.tranTime[index][1];
            exp += flightLocation2[pArrive] * flightLocation1[pLeave] * data.tranTime[index][2];
            exp += flightLocation2[pArrive] * flightLocation2[pLeave] * data.tranTime[index][3];

            obj3 += exp * data.passengerList.at(i).passengerNum;
            exp.end();

        }
        cout << "��ʼ����� obj3" << endl;
        //......����1 ���Ż�Ŀ��......
        //model.add(IloMaximize(env, obj1 - 0.01 * obj2));

        //......����2 ���Ż�Ŀ��......
        //model.add(IloMinimize(env, obj3 + 0.01 * obj2 + 100000 * (256 - obj1)));
        model.add(IloMinimize(env, obj3 + 0.01 * obj2 - 100000 * obj1));


        //Լ��1: ����ƥ��
        for (int i = 0; i < data.flightNum; i++) {
            for (int j = 0; j < data.parkNum; j++) {
                if (data.isTypeMatching[i][j] == 0)
                    model.add(xVar[i][j] == 0);
            }
        }

        //Լ��2��ÿ������ֻ��ѡ��һ���ǻ���
        for (int i = 0; i < data.flightNum; i++) {
            IloNumExpr exp1(env);
            for (int j = 0; j < data.parkNum; j++) {
                exp1 += xVar[i][j];
            }
            model.add(exp1 <= 1);
        }

        //Լ��3�����ʱ��С��45����
        for (int i = 0; i < data.flightNum; i++) {
            for (int j = 0; j < data.flightNum; j++) {
                if (i == j)
                    continue;
                for (int k = 0; k < data.parkNum; k++) {
                    if (data.isTypeMatching[i][k] == 1 && data.isTypeMatching[j][k] == 1 && data.isConflict[i][j] == 1)
                        model.add(xVar[i][k] + xVar[j][k] <= 1);
                }
            }
        }

        //Լ��4��ֻ��ѡ�񿪷ŵĵǻ���
        for (int i = 0; i < data.flightNum; i++) {
            for (int j = 0; j < data.parkNum; j++) {
                model.add(xVar[i][j] <= yVar[j]);
            }
        }

        //Լ��5����¼ÿ�������λ��ƥ�����
        for (int i = 0; i < data.flightNum; i++) {
            IloNumExpr exp2(env);
            IloNumExpr exp3(env);
            for (int j = 0; j < 28; j++) {
                exp2 += xVar[i][j];
            }
            for (int j = 28; j < data.parkNum; j++) {
                exp3 += xVar[i][j];
            }
            model.add(flightLocation1[i] == exp2);
            model.add(flightLocation2[i] == exp3);
        }

        IloCplex cplex(model);
        cplex.extract(model);
        cplex.exportModel("transpotr.lp");

        if (!cplex.solve()) {
            env.error() << "Failed to optimize LP." << endl;
            throw(-1);
        }

        env.out() << "Solution status = " << cplex.getStatus() << endl;
        env.out() << "Solution value = " << cplex.getObjValue() << endl;
        env.out() << " - solution: " << endl;
        int a = 0;
        for (int i = 0; i < data.flightNum; i++) {
            for (int j = 0; j < data.parkNum; j++) {
                //env.out() << cplex.getValue(x[i][j]) << "\t";
                if (cplex.getValue(xVar[i][j]) == 1) {
                    cout << "i = " << i << "\t" << "j = " << j << endl;
                    a++;
                }
            }
        }
        for (int i = 0; i < data.flightNum; i++) {
            v1.push_back(cplex.getValue(flightLocation1[i]));

            /*if (cplex.getValue(flightLocation1[i]) == 1) {
                cout << "flightLocation1 = " << i << endl;
            }*/
        }
        /*for (int i = 0; i < v1.size(); i++) {
            cout << "v1.at( " << i << ") = " << v1.at(i) << endl;
        }*/

        for (int i = 0; i < data.flightNum; i++) {
            v2.push_back(cplex.getValue(flightLocation2[i]));

            /*if (cplex.getValue(flightLocation2[i]) == 1) {
                cout << "flightLocation2 = " << i << endl;
            }*/
        }
        cout << "������ " << a << "�ܴηɻ�" << endl;
        //for (int i = 0; i < data.parkNum; i++) {
        //    //env.out() << cplex.getValue(x[i][j]) << "\t";
        //    if (cplex.getValue(yVar[i]) == 1) {
        //        cout << "i = " << i  << endl;
        //    }
        //}
        int time = 0;
        int total_time = 0;
        for (int i = 0; i < data.passengerList.size(); i++) {
            int pArrive = data.passengerList[i].arriveFlight;
            int pLeave = data.passengerList[i].leaveFlight;
            int index = 2 * data.flightList.at(pArrive).arriveType + data.flightList.at(pLeave).leaveType;

            //cout << i << " " << pArrive << " " << pLeave << " " << index << " " << endl;

            time += v1[pArrive] * v1[pLeave] * data.tranTime[index][0];
            //cout << "time = " << time << endl;
            time += v1[pArrive] * v2[pLeave] * data.tranTime[index][1];
            //cout << "time = " << time << endl;
            time += v2[pArrive] * v1[pLeave] * data.tranTime[index][2];
            //cout << "time = " << time << endl;
            time += v2[pArrive] * v2[pLeave] * data.tranTime[index][3];
            //cout << "time = " << time << endl;

            total_time += time * data.passengerList.at(i).passengerNum;
            time = 0;
        }
        cout << "total_time = " << total_time << endl;

        //ofstream outFile;
        //outFile.open("Result.csv", ios::out);

        //for (int i = 0; i < data.flightNum; i++) {
        //    for (int j = 0; j < data.parkNum; j++) {
        //        //env.out() << cplex.getValue(x[i][j]) << "\t";
        //        if (cplex.getValue(xVar[i][j]) == 1) {
        //            outFile << i << "," << j << "," 
        //                << data.flightList[i].name << ","
        //                << data.flightList[i].planeType << ","
        //                << data.flightList[i].startTime << ","
        //                << data.flightList[i].endTime << ","
        //                << data.flightList[i].arriveType << ","
        //                << data.flightList[i].leaveType << endl;
        //        }
        //    }
        //}
        //outFile.close();

    }

    catch (IloException& e) { cerr << "Concert exception caught: " << e << endl; }
    catch (...) { cerr << "Unknown exception caught" << endl; }
    env.end();

    system("pause");
    return 0;
}

