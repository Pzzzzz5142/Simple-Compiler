#pragma once
#include "LL1a.h"
using namespace std;

struct DAGNode
{
    int id;             //���
    string op;          //�������
    SemNode zhu;        //�����
    vector<SemNode> fu; //���������
    int houji0;
    int houji1;
};

class Optimizer
{
    struct DAGNode
    {
        int id;             //���
        string op;          //�������
        SemNode zhu;        //�����
        vector<SemNode> fu; //���ӱ������
        int houji0;
        int houji1;
    };
    vector<DAGNode> DAG; //DAGͼ
    vector<QtNode> QT;  //�Ż�ǰ
    vector<QtNode> QT2; //�Ż���
    int numnum = 0;         //�Ż���ǰ��Ԫʽ��λ��

    string num2str(double i)//����ת���ַ���
    {
        stringstream ss;
        ss << i;
        return ss.str();
    }

    int str2num(string str)//�ַ���ת������
    {
        int num;
        stringstream ss(str);
        ss >> num;
        return num;
    }

    bool equal(SemNode a, SemNode b)//������Ԫʽ�����Ƿ����
    {
        if ((a.x == b.x) && (a.y == b.y))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool equall(DAGNode a, DAGNode b)//DAG�ڵ����������е�
    {
        if (equal(a.zhu, b.zhu))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int zhufu(SemNode a)//�ڸ��ӱ���в���,���ؽڵ�ı��
    {
        for (int i = DAG.size() - 1; i >= 0; i--)
        {
            for (int j = 0; j < DAG[i].fu.size(); j++)
            {
                if (equal(a, DAG[i].fu[j]))
                {
                    return i;
                }
            }
        }
        return -1;
    }

    bool dingyi(SemNode x) //�Ƿ���Ϊ����Ǳ������,��ʼ����ʱ����
    {
        for (int i = DAG.size() - 1; i >= 0; i--)
        {
            if (equal(x, DAG[i].zhu))
            {
                return 1;
            }
        }
        return 0;
    }

    int findzhu(SemNode key) //����DAGͼ�е������,��������DAG�ڵ�ı��
    {
        for (int i = DAG.size() - 1; i >= 0; i--)
        {
            if (equal(key, DAG[i].zhu))
            {
                return i;
            }
        }
        return -1;
    }

    void chongfubiaoji(SemNode x) //�ظ��ĸ��ӱ�Ǵ���,�������ɾ,��ʵ��������м�����Ļ�����ɾ��
    {
        for (int i = DAG.size() - 1; i >= 0; i--)
        {
            for (int j = 0; j < DAG[i].fu.size(); j++)
            {
                if (equal(x, DAG[i].fu[j]))
                {
                    for (auto it = DAG[i].fu.begin(); it != DAG[i].fu.end();)
                    {
                        if (equal(DAG[i].fu[j], *it))
                        {
                            it = DAG[i].fu.erase(it);
                        }
                        else
                        {
                            ++it;
                        }
                    }
                }
            }
        }
    }

    void change(DAGNode& a)//���DAG�ڵ�Ĵ���
    {
        int tempx;
        string tempy;
        if (a.zhu.y[0] == '#')
        {
            for (int i = 0; i < a.fu.size(); i++)
            {
                if (a.fu[i].y[0] != '#')
                {
                    tempx = a.zhu.x;
                    tempy = a.zhu.y;

                    a.zhu.x = a.fu[i].x;
                    a.zhu.y = a.fu[i].y;

                    a.fu[i].x = tempx;
                    a.fu[i].y = tempy;
                }
            }
        }
    }

    int findfu(SemNode key, DAGNode a) //�����ж�ĳһ��DAG�ڵ�ĸ��ӱ��,�������ڸ��ӱ�ǵ�λ��
    {
        for (int i = 0; i < a.fu.size(); i++)
        {
            if (equal(key, a.fu[i]))
            {
                return i;
            }
        }
        return -1;
    }

    int yunsuan(DAGNode a, SemNode b, SemNode c) //�ж��Ƿ���ǰ����̵Ĺ�ϵ������һ��DAG�ڵ㣬����������󣬸��ݵ��ǽڵ�
    {
        if ((a.houji0 >= 0) && (a.houji1 >= 0))//���ڵ�DAG�ڵ����к�̽ڵ��
        {
            DAGNode k1 = DAG[a.houji0];//������������ڵĽڵ�
            DAGNode k2 = DAG[a.houji1];//������������ڵĽڵ�
            if ((!equall(a, k1)) && (!(equall(a, k2))))
            {
                if ((equal(k1.zhu, b) || (findfu(b, k1) >= 0)) && ((equal(k2.zhu, c)) || (findfu(c, k2) >= 0)))
                {
                    return 1;//������ڵ������Ǿ���������󣬻�����������������ڵ�ĸ��ӱ����
                }
                else
                {
                    return 0;
                }
            }
        }
        else
        {
            return 0;
        }
    }

    void InitDAG(int m, int n) //���ݵ�ǰ����Ԫʽ��ʼ��DAGͼ
    {
        for (int i = m; i <= n; i++)
        {
            if ((QT[i].a.y == ">") || (QT[i].a.y == "<") || (QT[i].a.y == "+") || (QT[i].a.y == "-") || (QT[i].a.y == "*") || (QT[i].a.y == "/") || (QT[i].a.y == ">=") || (QT[i].a.y == "<=") || (QT[i].a.y == "==")) //����������ǵ��ڣ�������ϵ������������㣬��Ҫ��
            {
                if ((!dingyi(QT[i].b)) && (!((QT[i].b.y[0] == '@') && (QT[i].c.y[0] == '@'))) && QT[i].b.y[0] != '#') //û�ж�����Ͷ���,���ǳ������м������������һ������
                {
                    DAG.push_back(DAGNode());
                    DAG[DAG.size() - 1].zhu = QT[i].b;
                    DAG[DAG.size() - 1].id = DAG.size() - 1;
                    DAG[DAG.size() - 1].houji0 = -1;
                    DAG[DAG.size() - 1].houji1 = -1;
                }
                if ((!dingyi(QT[i].c)) && (!((QT[i].b.y[0] == '@') && (QT[i].c.y[0] == '@'))) && QT[i].c.y[0] != '#')
                {
                    DAG.push_back(DAGNode());
                    DAG[DAG.size() - 1].zhu = QT[i].c;
                    DAG[DAG.size() - 1].id = DAG.size() - 1;
                    DAG[DAG.size() - 1].houji0 = -1;
                    DAG[DAG.size() - 1].houji1 = -1;
                }
            }
        }
    }

    void createDAG(int m, int n) //������Ԫʽ����DAGͼ,��ӵ�����
    {
        for (int i = m; i <= n; i++)
        {
            if ((QT[i].a.y == "=") && (QT[i].b.y[0] != '@')) //��ֵ��Ԫʽ,��Ҫ�ǳ�����,A=B
            {
                if (findzhu(QT[i].b) >= 0)//B�������
                {
                    chongfubiaoji(QT[i].d);                      //A�Ѿ��Ƕ�����ĸ��ӱ�ǵĴ���������ǲ�ɾ��
                    DAG[findzhu(QT[i].b)].fu.push_back(QT[i].d); //B�ĸ���Ǽ�A
                    change(DAG[findzhu(QT[i].b)]);
                }
                else//B���������
                {
                    if (zhufu(QT[i].b) >= 0)//B��ĳ�����ӱ��
                    {
                        chongfubiaoji(QT[i].d);
                        DAG[zhufu(QT[i].b)].fu.push_back(QT[i].d);//�ҵ���Ϊ���ӱ�����ڵĽڵ�
                        change(DAG[zhufu(QT[i].b)]);
                    }
                }


            }
            if (((QT[i].b.y[0] == '@') && (QT[i].c.y[0] == '@')) || ((QT[i].b.y[0] == '@') && (QT[i].c.x == -1) && (QT[i].a.y == "=")))//��������ʽ,ֱ�Ӹ������������Ҫ����
            {

                if ((QT[i].b.y[0] == '@') && (QT[i].c.y[0] == '@'))//��Ҫ������
                {
                    int a1, a2, a3;
                    a1 = QT[i].b.x;
                    a2 = QT[i].c.x;//ת������ֵ
                    if (QT[i].a.y == "+")
                    {
                        a3 = a1 + a2;
                    }
                    if (QT[i].a.y == "-")
                    {
                        a3 = a1 - a2;
                    }
                    if (QT[i].a.y == "*")
                    {
                        a3 = a1 * a2;
                    }
                    if (QT[i].a.y == "/")
                    {
                        a3 = a1 / a2;
                    }
                    SemNode r;//��������ĳ���
                    r.x = 0;
                    r.y = '@' + to_string(a3);
                    //cout<<r.y;
                    if (findzhu(r) >= 0)//�ó����Ѿ����������Ϊ�����
                    {
                        chongfubiaoji(QT[i].d);//A�Ѿ��Ƕ�����Ĵ���������ǲ�ɾ��
                        DAG[findzhu(r)].fu.push_back(QT[i].d);
                        change(DAG[findzhu(r)]);
                    }
                    else//�ó���û�ж����
                    {
                        DAG.push_back(DAGNode());
                        int o = DAG.size() - 1;
                        DAG[o].zhu = r;
                        DAG[o].id = o;
                        DAG[o].houji0 = -1;
                        DAG[o].houji1 = -1;
                        chongfubiaoji(QT[i].d);//A�Ѿ��Ƕ�����Ĵ���������ǲ�ɾ��
                        DAG[o].fu.push_back(QT[i].d);
                        change(DAG[o]);
                    }
                }
                else//����Ҫ������
                {
                    SemNode r;//��������ĳ���
                    r = QT[i].b;
                    if (findzhu(r) >= 0)//�ó����Ѿ������
                    {
                        chongfubiaoji(QT[i].d);
                        DAG[findzhu(r)].fu.push_back(QT[i].d);
                        change(DAG[findzhu(r)]);
                    }
                    else//�ó���û�ж����
                    {

                        DAG.push_back(DAGNode());
                        int o = DAG.size() - 1;
                        DAG[o].zhu = r;
                        DAG[o].id = o;
                        DAG[o].houji0 = -1;
                        DAG[o].houji1 = -1;
                        chongfubiaoji(QT[i].d);//A�Ѿ��Ƕ�����Ĵ���������ǲ�ɾ��
                        DAG[o].fu.push_back(QT[i].d);
                        change(DAG[o]);
                    }
                }
            }

            if (((QT[i].a.y == ">") || (QT[i].a.y == "<") || (QT[i].a.y == "+") || (QT[i].a.y == "-") || (QT[i].a.y == "*") || (QT[i].a.y == "/") || (QT[i].a.y == ">=") || (QT[i].a.y == "<=") || (QT[i].a.y == "==")) && (QT[i].b.y[0] != '@') && (QT[i].c.y[0] != '@'))//���ǳ������������ʽ
            {
                int shifou = 0;
                for (int j = DAG.size() - 1; j >= 0; j--)//�ѵ�
                {
                    if ((yunsuan(DAG[j], QT[i].b, QT[i].c) == 1) && DAG[j].op == QT[i].a.y)//���DAG�ڵ����������ʽ
                    {
                        chongfubiaoji(QT[i].d); //A�Ѿ��Ƕ�����Ĵ���������ǲ�ɾ��
                        DAG[j].fu.push_back(QT[i].d); //���A��Ϊ���ӱ����
                        change(DAG[j]);
                        shifou = 1;
                        break;
                    }
                }
                if (shifou == 0)//������������һ�������������Ľڵ�,������������Ҫ�½���
                {
                    chongfubiaoji(QT[i].d);//����ǰ����ɾ������˵
                    DAG.push_back(DAGNode());//������һ��DAG�ڵ���˵
                    int o = DAG.size() - 1;
                    DAG[o].op = QT[i].a.y;//�����
                    DAG[o].id = o;
                    DAG[o].zhu = QT[i].d;//��Ϊ�����
                    for (int k = DAG.size() - 1; k >= 0; k--)
                    {
                        if (equal(DAG[k].zhu, QT[i].b))//��Ϊ������ҵ�
                        {
                            DAG[o].houji0 = k;
                            break;
                        }
                        if (findfu(QT[i].b, DAG[k]) >= 0)//��Ϊ���ӱ�Ǳ��ҵ�
                        {
                            DAG[o].houji0 = k;
                            break;
                        }
                    }
                    for (int k = DAG.size() - 1; k >= 0; k--)
                    {
                        if (equal(DAG[k].zhu, QT[i].c))
                        {
                            DAG[o].houji1 = k;
                            break;
                        }
                        if (findfu(QT[i].c, DAG[k]) >= 0)
                        {
                            DAG[o].houji1 = k;
                            break;
                        }
                    }
                }
            }
            if (((QT[i].a.y == ">") || (QT[i].a.y == "<") || (QT[i].a.y == "+") || (QT[i].a.y == "-") || (QT[i].a.y == "*") || (QT[i].a.y == "/") || (QT[i].a.y == ">=") || (QT[i].a.y == "<=") || (QT[i].a.y == "==")) && (((QT[i].b.y[0] != '@') && (QT[i].c.y[0] == '@')) || ((QT[i].b.y[0] == '@') && (QT[i].c.y[0] != '@'))))
            {
                int shifou = 0;
                for (int j = DAG.size() - 1; j >= 0; j--)//�ѵ�
                {
                    if ((yunsuan(DAG[j], QT[i].b, QT[i].c) == 1) && DAG[j].op == QT[i].a.y)//���DAG�ڵ����������ʽ
                    {
                        chongfubiaoji(QT[i].d); //A�Ѿ��Ƕ�����Ĵ���������ǲ�ɾ��
                        DAG[j].fu.push_back(QT[i].d); //���A��Ϊ���ӱ����
                        change(DAG[j]);
                        shifou = 1;
                        break;
                    }
                }
                if (shifou == 0)//������������һ�������������Ľڵ�,������������Ҫ�½���
                {
                    chongfubiaoji(QT[i].d);//����ǰ����ɾ������˵
                    DAG.push_back(DAGNode());//������һ��DAG�ڵ���˵
                    int o = DAG.size() - 1;
                    DAG[o].op = QT[i].a.y;//�����
                    DAG[o].id = o;
                    DAG[o].zhu = QT[i].d;//��Ϊ�����
                    for (int k = DAG.size() - 1; k >= 0; k--)
                    {
                        if (equal(DAG[k].zhu, QT[i].b))//��Ϊ������ҵ�
                        {
                            DAG[o].houji0 = k;
                            break;
                        }
                        if (findfu(QT[i].b, DAG[k]) >= 0)//��Ϊ���ӱ�Ǳ��ҵ�
                        {
                            DAG[o].houji0 = k;
                            break;
                        }
                    }
                    for (int k = DAG.size() - 1; k >= 0; k--)
                    {
                        if (equal(DAG[k].zhu, QT[i].c))
                        {
                            DAG[o].houji1 = k;
                            break;
                        }
                        if (findfu(QT[i].c, DAG[k]) >= 0)
                        {
                            DAG[o].houji1 = k;
                            break;
                        }
                    }
                }
            }
        }
    }

    void recombineDAG() //DAGͼ������Ԫʽ
    {
        for (int i = 0; i < DAG.size(); i++)
        {
            if ((DAG[i].houji0 == -1) && (DAG[i].houji1 == -1)) //�����ӱ�ǵ�Ҷ�ӽڵ�
            {
                for (int j = 0; j < DAG[i].fu.size(); j++) //���ڸ��ӱ��
                {
                    if (DAG[i].fu[j].y[0] != '#') //������ʱ����
                    {
                        QT2.push_back(QtNode()); //���ɸ�ֵ����Ԫʽ
                        QT2[QT2.size() - 1].a.x = 0;
                        QT2[QT2.size() - 1].a.y = "=";
                        QT2[QT2.size() - 1].b = DAG[i].zhu;
                        QT2[QT2.size() - 1].d = DAG[i].fu[j];
                        QT2[QT2.size() - 1].c.x = -1;
                        numnum++;
                    }
                }
            }

            if (!((DAG[i].houji0 == -1) && (DAG[i].houji1 == -1))) //�����ӱ�ǵķ�Ҷ�ӽڵ�
            {
                QT2.push_back(QtNode());
                QT2[QT2.size() - 1].a.x = 0;
                QT2[QT2.size() - 1].a.y = DAG[i].op;
                QT2[QT2.size() - 1].b = DAG[DAG[i].houji0].zhu;
                QT2[QT2.size() - 1].c = DAG[DAG[i].houji1].zhu;
                QT2[QT2.size() - 1].d = DAG[i].zhu;
                numnum++;

                for (int j = 0; j < DAG[i].fu.size(); j++) //���ڸ��ӱ��
                {
                    if (DAG[i].fu[j].y[0] != '#') //������ʱ����
                    {
                        QT2.push_back(QtNode()); //���ɸ�ֵ����Ԫʽ
                        QT2[QT2.size() - 1].a.x = 0;
                        QT2[QT2.size() - 1].a.y = "=";
                        QT2[QT2.size() - 1].b = DAG[i].zhu;
                        QT2[QT2.size() - 1].d = DAG[i].fu[j];
                        QT2[QT2.size() - 1].c.x = -1;
                        numnum++;
                    }
                }
            }
        }
    }




    void optimazte(int m, int n)
    {
        DAG.clear();     //DAGͼ�����
        InitDAG(m, n);   //��ʼ��ʱ���ʼ��DAGͼ
        createDAG(m, n); //����DAGͼ
        recombineDAG();  //����������Ԫʽ
    }



    void pr(DAGNode a)
    {

        cout << a.zhu.y;
        cout << ' ';
        for (int k = 0; k < a.fu.size(); k++)
        {
            cout << a.fu[k].y;
            cout << ' ';
        }
        cout << ' ';
        cout << ' ';
        cout << a.houji0;
        cout << ' ';
        cout << a.houji1;
        cout << endl;
    }


    void opsolve()
    {
        int op1 = 0;
        int op2 = 0;
        int i = 0;
        while (i < QT.size())
        {
            if ((QT[i].a.y == ">") || (QT[i].a.y == "<") || (QT[i].a.y == "+") || (QT[i].a.y == "-") || (QT[i].a.y == "*") || (QT[i].a.y == "/") || (QT[i].a.y == ">=") || (QT[i].a.y == "<=") || (QT[i].a.y == "==") || (QT[i].a.y == "="))
            {
                op1 = i;
                for (int j = i; j < QT.size() && ((QT[j].a.y == ">") || (QT[j].a.y == "<") || (QT[j].a.y == "+") || (QT[j].a.y == "-") || (QT[j].a.y == "*") || (QT[j].a.y == "/") || (QT[j].a.y == ">=") || (QT[j].a.y == "<=") || (QT[j].a.y == "==") || (QT[j].a.y == "=")) && j < QT.size();)
                {
                    j++;
                    op2 = j - 1;
                }
                optimazte(op1, op2);
                i = op2 + 1;
            }
            else
            {
                QT2.push_back(QT[i]);
                numnum++;
                i++;
            }
        }
    }

public:
    vector<QtNode> solve()
    {
		opsolve();
        for (auto& x : QT2)
        {
            if (x.a.y == "=")
            {
                swap(x.b, x.d);
            }
        }
        return QT2;
    }
	void show()
	{
		int i = 0;
        for (int i = 0; i < QT.size(); i++)
        {
            cout << "(" << i << ") " << QT[i];
            cout << "\t";
            if (i < QT2.size())
            {
                cout << "(" << i << ") " << QT2[i];
            }
            cout << endl;
        }
	}
    Optimizer(const LL1& a)
    {
        QT = a.QT;
        for (auto& x : QT)
        {
            if (x.a.y == "=")
            {
                swap(x.b, x.d);
            }
        }
    }
};