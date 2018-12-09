#include<iostream>
#include<bits/stdc++.h>
#define training 120
#define testing 15
#define features 5
using namespace std;
float train[training][features],test[testing][features];

struct Dist
{
    float d;
    float cls;
};

bool compare(Dist a,Dist b)
{
    return a.d<b.d;
}

int main()
{
    float sl,sw,pl,pw;
    int i=0,j;
    float successrate=0;
    char str[100];
    FILE *trainFile = fopen("training.txt","r");
    FILE *testFile = fopen("test.txt","r");
    while((fscanf(trainFile ,"%f %f %f %f %s",&sl,&sw,&pl,&pw,str)) != EOF)
    {
        //cout<<sl<<" "<<sw<<" "<<pl<<" "<<pw << " " << str <<endl;
        train[i][0]=sl;
        train[i][1]=sw;
        train[i][2]=pl;
        train[i][3]=pw;
        if(!strcmp(str,"Iris-setosa"))
        {
            train[i][4]=0;
        }
        if(!strcmp(str,"Iris-versicolor"))
        {
            train[i][4]=1;
        }
        if(!strcmp(str,"Iris-virginica"))
        {
            train[i][4]=2;
        }
        i++;
    }
    i=0;

    while(fscanf(testFile,"%f %f %f %f %s",&sl,&sw,&pl,&pw,str)!=EOF)
    {
        //cout<<sl<<" "<<sw<<" "<<pl<<" "<<pw << " " << str <<endl;
        test[i][0]=sl;
        test[i][1]=sw;
        test[i][2]=pl;
        test[i][3]=pw;
        if(!strcmp(str,"Iris-setosa"))
        {
            test[i][4]=0;
        }
        if(!strcmp(str,"Iris-versicolor"))
        {
            test[i][4]=1;
        }
        if(!strcmp(str,"Iris-virginica"))
        {
            test[i][4]=2;
        }
        i++;
    }
    Dist distances[training];
    for(i=0;i<testing;i++)
    {
        float sum=0;
        for(j=0;j<training;j++)
        {
            //cout << test[i][0] << " " << train[j][0] << " " << test[i][1] << " " << train[j][1] << endl;
            distances[j].d=sqrt(pow(test[i][0]-train[j][0],2)+pow(test[i][1]-train[j][1],2)+pow(test[i][2]-train[j][2],2)+pow(test[i][3]-train[j][3],2));
            distances[j].cls=train[j][4];
        }
        sort(distances,distances+training,compare);
        int k=101;
        int c1=0,c2=0,c3=0;
        for(j=0;j<k;j++)
        {
           // cout << distances[j].cls << " ";
            if(distances[j].cls==0)
                c1++;
            else if(distances[j].cls==1)
                c2++;
            else c3++;
        }
        //cout << endl;
        int maxi=c1,predict=0;
        if(maxi<c2){maxi=c2;predict=1;}
        if(maxi<c3){maxi=c3;predict=2;}
        if(test[i][4]==predict)
            successrate++;
    }
    //cout<<successrate<<endl;
    cout<<successrate/testing*100.0;

    return 0;
}
