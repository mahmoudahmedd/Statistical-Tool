/*
****************************************************************************
*                        FCI – Programming 1 – 2018                        *
** Project Name: Statistical Tool                                          *
** Last Modification Date: 01/04/2018                                      *
** Author: Mahmoud Ahmed Tawfik                                            *
****************************************************************************
*/

#include <iostream>
#include <map>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <string>
#include <sstream>
#include <set>
#include <bitset>
#include <utility>
using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;



string fileName = "";
ifstream ifile;
ofstream ofile;
vector<float> v;
float q1,q2,q3 ;

/*linearRegression*/
string fileName2 = "";
ifstream ifile2;
double a = 0, b = 0;
vector<float> vXSet;
vector<float> vYSet;
/****************/

void printByeBye()
{
    cout<<endl<<"Bye..."<<endl<<endl;
}
void printDone()
{
    cout<<endl<<"\tDone..."<<endl;
    if(ofile.is_open())
    {
        cout<<"\tFilename : "<<fileName<<endl;
    }
}
void printError()
{
    cout<<endl<<"Error...."<<endl<<endl;
}
void printWelcome()
{
    cout<<"Ahlan ya user ya hbibi."<<endl;
    cout<<"What do you like to do today?"<<endl;
}
void printmenu()
{
    cout<<endl<<endl;
    cout<<"\t1-  Enter a new data set."<<endl;
    cout<<"\t2-  Load a data set."<<endl;
    cout<<"\t3-  Display a data set."<<endl;
    cout<<"\t4-  Calculate the quartiles of the data set."<<endl;
    cout<<"\t5-  Calculate the Interquartile range."<<endl;
    cout<<"\t6-  Calculate the Correlation Coefficient of the data set."<<endl;
    cout<<"\t7-  Calculate the median value of the data set."<<endl;
    cout<<"\t8-  Calculate linear regression coefficients a, b & formula y = ax + b."<<endl;
    cout<<"\t9-  Calculate the mean square error MSE of the linear regression of 8."<<endl;
    cout<<"\t10- Calculate the mean and standard deviation of the data set."<<endl;
    cout<<"\t11- Relative standard deviation."<<endl;
    cout<<"\t12- Calculate the mode value of the data set."<<endl;
    cout<<"\tE-  End."<<endl<<endl;
    cout<<"You choose >>> ";
}
float mean()
{
    float sum = 0;
    for(int i = 0; i < v.size(); i++)
        sum += v[i];
    return sum/v.size();
}
void loadData()
{
    v.clear();
    float temp ;
    ifile.open(fileName.c_str(), ios::in | ios::app );
    while(ifile>>temp)
    {
        v.push_back(temp);
    }
    ifile.close();
}
void NewFile()
{
    int size;
    float temp;
    cout<<"Enter filename ya user ya hbibi : "<<endl;
    cin>>fileName;
    if(fileName.find(".txt") == string::npos)
        fileName.append(".txt");
    ofile.open(fileName.c_str(), ios::out | ios::app );
    cout<<"Enter the number of element : ";
    cin>>size;
    for(int i = 0; i < size; i++)
    {
        cout<<"Enter float value #"<<i+1<<" : ";
        cin>>temp;
        ofile<<temp<<endl;
    }
    ofile.close();
    loadData();
    printDone();
}
void loadFile()
{
    cout<<"Enter filename ya user ya hbibi : "<<endl;
    cin>>fileName;
    if(fileName.find(".txt") == string::npos)
        fileName.append(".txt");
    loadData();
    printDone();
}
void displayFileContent()
{
    if(fileName == "")
    {
        cout<<"Please... Create/Load a new file."<<endl;
    }
    else
    {
        for(int i = 0; i < v.size(); i++)
        {
            cout<<"Element #"<<i+1<<" = "<<v[i]<<endl;
        }
        printDone();
    }
}
float getQ1(vector<float> _v, int size)
{
    float q1;
    int p, tPos;
    p = (size / 2) - 1;
    if (p%2 == 0)
    {
        tPos = p/2;
        q1 = _v[tPos];
    }
    else
    {
        tPos = ((p + 1) / 2) - 1;
        q1 = (_v[tPos] + _v[tPos + 1]) / 2;
    }
    return q1;
}

void calquartiles()
{
    if(fileName == "")
    {
        cout<<"Please... Create/Load a new file."<<endl;
    }
    else
    {
        sort(v.begin(),v.end());
		int p, temp;
        int c = v.size() ;
        if(c%2 == 0)
        {
            q2 = (v[c/2]+v[(c/2)-1])/2;
        }
        else
        {
            q2 = v[((c+1)/2)-1];
        }
		
		p = (v.size() / 2) - 1;
		if (p%2 == 0)
		{
			temp = p / 2;
			q3 = v[temp + ( v.size() / 2)];
			q1 = v[temp];
		}
		else
		{
			temp = ((p + 1) / 2) - 1;
			q3 = (v[temp + v.size() / 2] + v[temp + 1 + v.size() / 2]) / 2;
			q1 = (v[temp] + v[temp + 1]) / 2;
		}
        cout<<"Q1="<<q1<<endl;
        cout<<"Q2="<<q2<<endl;
        cout<<"Q3="<<q3<<endl;
    }
}
void interquartileRange()
{
    if(fileName == "" )
    {
        cout<<"Please... Create/Load a new file."<<endl;
    }
    else
    {
        cout<<"The Interquartile range = "<<q3-q1<<endl;
    }
}
float correlationCoefficient()
{
    int x, y;
    double sumX = 0;
    double sumX2 = 0;
    double sumY = 0;
    double sumY2 = 0;
    double sumXY = 0;

    cout<<"Enter the X size : ";
    cin>>x;
    cout<<"Enter the Y size : ";
    cin>>y;
    vector<float> vX(max(x,y),0);
    vector<float> vY(max(x,y),0);
    cout<<"Enter the X values: "<<endl;
    for(int i = 0; i < x; i++)
        cin>>vX[i];
    cout<<"Enter the Y values: "<<endl;
    for(int i = 0; i < y; i++)
        cin>>vY[i];
    for(int i = 0; i < max(x,y); i++)
    {
        sumX  += vX[i];
        sumX2 += vX[i] * vX[i];
        sumY  += vY[i];
        sumY2 += vY[i] * vY[i];
        sumXY += vX[i] * vY[i];
    }
    return   ((max(x,y) * sumXY) - (sumX * sumY))/sqrt( (max(x,y)*sumX2 - sumX*sumX) * (max(x,y)*sumY2 - sumY*sumY) );
}
float medianvalue()
{
    if(fileName == "")
    {
        cout<<"Please... Create/Load a new file."<<endl;
    }
    else
    {
        sort(v.begin(),v.end());
        if(v.size()%2 == 0)
        {
            return (v[v.size()/2] + v[v.size()/2 + 1] )/ 2;
        }
        else
        {
            return v[v.size()/2];
        }
    }
}
void linearRegression()
{

    bool val = true ;
    double meanX = 0;
    double meanY = 0;
    double sumX2 = 0;
    double sumXY = 0;


    cout<<"Enter filename ya user ya hbibi : "<<endl;
    cin>>fileName2;
    if(fileName2.find(".txt") == string::npos)
        fileName2.append(".txt");
    float temp ;
    ifile2.open(fileName2.c_str(), ios::in | ios::app );
    while(ifile2>>temp)
    {
        if(val)
        {
            vXSet.push_back(temp);
            val = false ;
        }
        else
        {
            vYSet.push_back(temp);
            val = true ;
        }
    }
    ifile2.close();

    cout<<"The file content:"<<endl;
    cout<<setw(6)<<"X"<<setw(6)<<"Y"<<endl;
    for(int i = 0;i < vXSet.size();i++)
        cout<<setw(8)<<vXSet[i]<<setw(8)<<vYSet[i]<<endl;
    cout<<endl;
    for(int i = 0;i < vXSet.size();i++)
    {
        meanX += vXSet[i];
        meanY += vYSet[i];
        sumX2 += vXSet[i] * vXSet[i];
        sumXY += vXSet[i] * vYSet[i];
    }
    meanX /= vXSet.size();
    meanY /= vYSet.size();
    b = (sumXY  - (vXSet.size() * meanX * meanY )) / ( sumX2 - (vXSet.size() * meanX * meanX ));
    a =  meanY - b * meanX ;
    cout<<"Sample size: "<<vXSet.size()<<endl;
    cout<<"Mean x : "<<meanX<<endl;
    cout<<"Mean y : "<<meanY<<endl;
    cout<<"Intercept (a): "<<a<<endl;
    cout<<"Slope (b): "<<b<<endl;
    cout<<endl;
    cout<<"Regression line equation: y="<<b<<"x+"<<a<<endl;
}
void MSE()
{
    if(fileName2 == "")
    {
        cout<<"Please... Choose (8) first."<<endl;
    }
    else
    {
        vector<float> vNewYSet;
        double sum = 0;
        cout<<"New y values:"<<endl;
        for(int i = 0;i < vYSet.size();i++)
        {
            vNewYSet.push_back(b*vXSet[i] + a);
            cout<<vNewYSet[i]<<endl;
        }
        cout<<"Error:"<<endl;
        for(int i = 0;i < vYSet.size();i++)
        {
            cout<<vYSet[i] - vNewYSet[i]<<endl;
        }
        cout<<"(Error)^2:"<<endl;
        for(int i = 0;i < vYSet.size();i++)
        {
            sum += (vYSet[i] - vNewYSet[i])*(vYSet[i] - vNewYSet[i]);
            cout<<(vYSet[i] - vNewYSet[i])*(vYSet[i] - vNewYSet[i])<<endl;
        }
        cout<<endl<<"MSE = "<<sum/vYSet.size()<<endl;
    }

}
float standardDeviation()
{
    if(fileName == "")
    {
        cout<<"Please... Create/Load a new file."<<endl;
    }
    else
    {
        double standardDeviation = 0;
        float m = mean();
        for(int i = 0; i < v.size(); ++i)
            standardDeviation += pow((v[i] - m),2);
        return sqrt(standardDeviation / v.size() );
    }
}
float relativeStandardDeviation()
{
    return (standardDeviation()/mean())*100;
}
void mode()
{
    if(fileName == "")
    {
        cout<<"Please... Create/Load a new file."<<endl;
    }
    else
    {
        map<float,int> m;
        for(int i = 0; i < v.size(); i++)
        {
            ++m[v[i]];
        }
        vector<pair<int,float> > p;

        float maxIndex = v[0];
        int maxValue = m[v[0]];
        for(int i = 0; i < v.size(); i++)
        {
            if(m[v[i]] > maxValue)
            {
                maxValue = m[v[i]];
                maxIndex = v[i];
            }
            p.push_back(make_pair(m[v[i]],v[i]));
        }
        sort(p.begin(),p.end());
        reverse(p.begin(), p.end());
        if(maxValue == 1)
        {
            cout<<"No mode"<<endl;
        }
        else
        {
            cout<<maxValue<<" modes"<<endl;
            for(int i = 0; p[i].first != 1; i+=maxValue)
                cout<<"Mode #"<<i<<" = "<< p[i].second <<endl;
        }
    }
}
int main()
{
    printWelcome();
    printmenu();
    int choice;
    while(cin>>choice)
    {
        if(choice == 1)
        {
            system("CLS");
            NewFile();
        }
        else if(choice == 2)
        {
            system("CLS");
            loadFile();
        }
        else if(choice == 3)
        {
            system("CLS");
            displayFileContent();
        }
        else if(choice == 4)
        {
            system("CLS");
            calquartiles();
        }
        else if(choice == 5)
        {
            system("CLS");
            interquartileRange();
        }
        else if(choice == 6)
        {
            system("CLS");
            cout<<"Correlation coefficient (r): "<<correlationCoefficient()<<endl;
        }
        else if(choice == 7)
        {
            system("CLS");
            cout<<medianvalue()<<endl;
        }
        else if(choice == 8)
        {
            system("CLS");
            linearRegression();

        }
        else if(choice == 9)
        {
            system("CLS");
            MSE();
        }
        else if(choice == 10)
        {
            system("CLS");
            cout<<"Arithmetic mean (μ): "<<mean()<<endl;
            cout<<"Standard deviation (σ): "<<standardDeviation()<<endl;
        }
        else if(choice == 11)
        {
            system("CLS");
            cout<<"RSE = (Standard deviation / Mean)x100 = "<<relativeStandardDeviation()<<endl;
        }
        else if(choice == 12)
        {
            system("CLS");
            mode();
        }
        else
        {
            system("CLS");
            printError();
        }
        printmenu();
    }
    printByeBye();

    return 0;
}
