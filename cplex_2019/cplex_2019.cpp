#include <iostream>
#include <vector>
#include <string>
#include <math.h>

#include <xlnt/xlnt.hpp>
#include <ilcplex/ilocplex.h>

using namespace std;

ILOSTLBEGIN

typedef IloArray<IloNumVarArray> NumVarMatrix;
vector<vector<string>> theWholeSpreadSheet;
vector<vector<double>> d;

void readData() {
    xlnt::workbook wb;
    wb.load("example.xlsx");
    auto ws = wb.active_sheet();

    std::clog << "Processing spread sheet" << std::endl;
    for (auto cell_vec : ws)
    {
        std::vector<string> aSingleRow;
        for (auto cell : cell_vec)
        {
            if (cell.has_value()) {
                aSingleRow.push_back(cell.to_string());
            }
        }
        theWholeSpreadSheet.push_back(aSingleRow);
    }
    std::clog << "Processing complete" << std::endl;

    cout << "该Excel共有：" << theWholeSpreadSheet.size() << " 行， " << theWholeSpreadSheet.at(0).size() << " 列" << endl;
    wb.save("example.xlsx");

    /*cout << "-----------------------" << endl;
    for (int rowint = 0; rowint < theWholeSpreadSheet.size(); rowint++)
    {
        for (int colint = 0; colint < theWholeSpreadSheet.at(rowint).size(); colint++)
        {
            std::cout << theWholeSpreadSheet.at(rowint).at(colint) << "\t";
        }
        cout << endl;
    }
    cout << "-----------------------" << endl;*/
}

int main()
{
    float M1 = 20.0;
    float M2 = 140.0;
    float t = 0.001;
    float a1 = 20;
    float a2 = 10;
    float b1 = 15;
    float b2 = 20;
    float c = 20;

    float d_max = 0;

    readData();
    int pointsNum = theWholeSpreadSheet.size();
    cout << "该数据集共有：" << pointsNum << " 个点" << endl;

    cout << "d process start!" << endl;
    for (int i = 0; i < pointsNum; i++) {
        vector<double> v1;
        for (int j = 0; j < pointsNum; j++) {
            double tmp = sqrt(
                (stod(theWholeSpreadSheet.at(i).at(1)) - stod(theWholeSpreadSheet.at(j).at(1))) * (stod(theWholeSpreadSheet.at(i).at(1)) - stod(theWholeSpreadSheet.at(j).at(1))) +
                (stod(theWholeSpreadSheet.at(i).at(2)) - stod(theWholeSpreadSheet.at(j).at(2))) * (stod(theWholeSpreadSheet.at(i).at(2)) - stod(theWholeSpreadSheet.at(j).at(2))) +
                (stod(theWholeSpreadSheet.at(i).at(3)) - stod(theWholeSpreadSheet.at(j).at(3))) * (stod(theWholeSpreadSheet.at(i).at(3)) - stod(theWholeSpreadSheet.at(j).at(3)))
            );
            v1.push_back(tmp);
        }
        d.push_back(v1);
    }
    cout << "d process end!" << endl;
    cout << "d 共有 " << d.size() << " 行 " << d.at(0).size() << " 列。" << endl;

    cout << "-----------------------" << endl;
    for (int i = 0; i < pointsNum; i++) {
        for (int j = 0; j < pointsNum; j++) {
            if (d_max < d[i][j]) {
                d_max = d[i][j];
            }
        }
        // cout << endl;
    }
    cout << "d_max = " << d_max << endl;
    cout << "-----------------------" << endl;

    cout << "----------cplex------------" << endl;
    IloEnv env;
    try {
        IloModel model(env);

        //初始化
        NumVarMatrix x(env, pointsNum);
        IloNumVarArray level(env, pointsNum);
        IloNumVarArray vert(env, pointsNum);

        for (int i = 0; i < pointsNum; i++) {
            x[i] = IloNumVarArray(env, pointsNum, 0, 1, ILOINT);
            //level[i] = IloNumVar(env, 0, M1, ILOFLOAT);
            //vert[i] = IloNumVar(env, 0, M1, ILOFLOAT);
        }

        //level[0] = IloNumVar(env, 0, 0, ILOFLOAT);      
        for (int i = 0; i < pointsNum; i++) {
            level[i] = IloNumVar(env, 0, M1, ILOFLOAT);
        }
        model.add(level[0] == 0);

        //vert[0] = IloNumVar(env, 0, 0, ILOFLOAT);       
        for (int i = 0; i < pointsNum; i++) {
            vert[i] = IloNumVar(env, 0, M1, ILOFLOAT);
        }
        model.add(vert[0] == 0);

        //优化目标：最小距离
        IloNumExpr obj1(env);
        IloNumExpr obj2(env);
        for (int i = 0; i < pointsNum; i++) {
            for (int j = 0; j < pointsNum; j++) {
                obj1 += d[i][j] * x[i][j];
            }
        }
        // !!! obj2 
        for (int i = 0; i < pointsNum; i++) {
            for (int j = 1; j < pointsNum - 1; j++) {
                obj2 += x[i][j];
            }
        }
        obj1 = 10 * obj1 + obj2;
        model.add(IloMinimize(env, obj1));
        //obj1.end();
        //obj2.end();

        //约束1：每个节点最多访问一次，且不能访问自己
        for (int i = 0; i < pointsNum; i++) {
            model.add(IloSum(x[i]) <= 1);
            model.add(x[i][i] == 0);
        }

        //约束2：流平衡
        for (int i = 1; i < pointsNum - 1; i++) {
            IloNumExpr expr(env);
            for (int j = 0; j < pointsNum; j++) {
                expr += x[j][i];
            }
            model.add(IloSum(x[i]) == expr);
            //expr.end();
        }

        //约束3：必须从A点出发
        model.add(IloSum(x[0]) == 1);

        //约束4：必须回到B点
        IloNumExpr expr(env);
        for (int i = 0; i < pointsNum - 1; i++) {
            expr += x[i][pointsNum - 1];
        }
        model.add(expr == 1);
        model.add(IloSum(x[pointsNum - 1]) == 0);
        //expr.end();

        //约束5：水平和垂直误差
        for (int j = 1; j < pointsNum; j++) {
            for (int i = 0; i < pointsNum - 1; i++) {
                model.add((M2 * (1 - x[i][j]) + level[j]) >= (t * d[i][j] + level[i] * stoi(theWholeSpreadSheet.at(i).at(4))));
                model.add((M2 * (1 - x[i][j]) + vert[j]) >= (t * d[i][j] + vert[i] * (1 - stoi(theWholeSpreadSheet.at(i).at(4)))));
            }
        }

        //误差传递
        for (int i = 0; i < pointsNum - 1; i++) {
            //垂直误差校正点
            if (stoi(theWholeSpreadSheet.at(i).at(4)) == 1) {
                model.add(level[i] <= a2);
                model.add(vert[i] <= a1);
            }
            //水平误差校正点
            else if (stoi(theWholeSpreadSheet.at(i).at(4)) == 0)
            {
                model.add(level[i] <= b2);
                model.add(vert[i] <= b1);
            }
        }

        //约束6：终点误差
        model.add(level[pointsNum - 1] <= c);
        model.add(vert[pointsNum - 1] <= c);

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
        for (int i = 0; i < pointsNum; i++) {
            for (int j = 0; j < pointsNum; j++) {
                //env.out() << cplex.getValue(x[i][j]) << "\t";
                if (cplex.getValue(x[i][j]) == 1) {
                    cout << "i = " << i << "\t" << "j = " << j << endl;
                }
            }
        }
    }
    catch (IloException& e) { cerr << "Concert exception caught: " << e << endl; }
    catch (...) { cerr << "Unknown exception caught" << endl; }
    env.end();

    system("pause");

    return 0;
}

