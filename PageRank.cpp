/****************************************************************************************************************************************************************
  Author:
  Dhairya Dhondiyal

  Description:
  The program calculates pagerank values for each vertex according to the input parameters.

  Disclaimer:
  Copyright (C) - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
  Written by Dhairya Dhondiyal, March 2017

****************************************************************************************************************************************************************/
#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<math.h>
#define d 0.85                                                                              //Damping Factor
using namespace std;
struct Node                                                                                 //Structure of a vertex of a graph
{
    int outVertex;
    Node* next;
    Node(int V=-1,Node* node=NULL)
    {
        outVertex=V;
        next=node;
    }
};
struct List                                                                                 //Holds pointer to each vertex
{
    Node* first;
    List(Node* node=NULL)
    {
        first=node;
    }
};
int main()
{
    int iterations,initialvalue,inp1,inp2,no_vertices;                                    //Declaring all initial values
    string filename;
    cout<<"Enter the number of iterations:\t";
    cin>>iterations;
    cout<<"\nEnter the initial value:\t";
    cin>>initialvalue;
    cout<<"\nEnter the filename:\t";
    cin>>filename;
    ifstream input(filename.c_str());
    if(!input.good())                                                                       //Check if the file exists
    {
        perror("Error:\t");
        exit(-1);
    }
    vector<double> P;                                                                       //Declare the Pagerank Vector
    input>>inp1>>inp2;                                                                      //Get the Vertice and Edge value
    no_vertices=inp1;
    if(no_vertices>10)                                                                      //set Iteration and Initial values if # vertice greater than 10
    {
        iterations=0;
        initialvalue=-1;
    }
    vector<int> C(no_vertices,0);                                                           //Count vector for outgoing edges
    List* adjlist=(struct List*)malloc(no_vertices*sizeof(struct List));                    //Declare Adjacency list
    for(int i=0;i<no_vertices;i++)                                                          //Initialize all list pointers to Null
        adjlist[i].first=NULL;
    while(input>>inp1>>inp2)                                                                //Read all file values
    {
        C[inp1]++;                                                                          //Increase outgoing count
        if(adjlist[inp2].first!=NULL)                                                       //}
        {                                                                                   //}
            Node* temp=adjlist[inp2].first;                                                 //}
            while(temp->next!=NULL)                                                         //} Make Adjacency list'
                temp=temp->next;                                                            //}
            temp->next=new Node(inp1);                                                      //}
        }                                                                                   //}
        else                                                                                //}
            adjlist[inp2].first=new Node(inp1);                                             //}
    }
    for(int i=0;i<no_vertices;i++)                                                          //Initialize all P values
    {
        if(initialvalue==-1)
            P.push_back((double)1/no_vertices);
        else if(initialvalue==-2)
            P.push_back((double)1/sqrt(no_vertices));
        else
            P.push_back(initialvalue);
    }
    vector<double> P_old(P);                                                                //Make P_old vector to store old values
    if(no_vertices<=10)                                                                     //Display Base values
    {
        cout<<"Base\t: "<<setw(2)<<"0"<<" :";
        for(int j=0;j<no_vertices;j++)
        {
            cout<<"P["<<j<<"]="<<fixed<<setprecision(7)<<P[j]<<"\t";
        }
        cout<<endl;
    }
    double tempcalc=0,pr_sum=0;                                                             //Declare Required variables
    for(int i=0;;i++)
    {
        for(int j=0;j<no_vertices;j++)                                                      //Get authority values of each incoming vertex
        {
            Node* temp=adjlist[j].first;
            while(temp!=NULL)
            {
                tempcalc+=P_old[temp->outVertex]/C[temp->outVertex];
                temp=temp->next;
            }
            P[j]=((1-d)/4)+d*tempcalc;
            pr_sum+=P[j];
            tempcalc=0;
        }
        /*for(int j=0;j<no_vertices;j++)                                                      //Scaling step , make sum of all values= 1
            P[j]=P[j]/pr_sum;*/
        if(no_vertices<=10)                                                                 //Display values after each Iteration
        {
            cout<<"iter\t: "<<setw(2)<<i+1<<" :";
            for(int j=0;j<no_vertices;j++)
                cout<<"P["<<j<<"]="<<fixed<<setprecision(7)<<P[j]<<"\t";
            cout<<endl;
        }
        if(iterations<0)                                                                    //Stopping condition 1
        {
            int k;
            for(k=0;k<no_vertices;k++)
            {
                if(fabs(P[k]-P_old[k])>=pow(10,iterations))
                    break;
            }
            if(k==no_vertices)
                break;
        }
        else if(iterations>0)                                                               //Stopping condition 2
        {
            if(i==iterations-1)
                break;
        }
        else                                                                                //Stopping condition 3
        {
            int k;
            for(k=0;k<no_vertices;k++)
            {
                if(fabs(P[k]-P_old[k])>=pow(10,-5))
                    break;
            }
            if(k==no_vertices)
                break;
        }
        P_old=P;                                                                            //Set Old P values equal to new P values
        pr_sum=0;                                                                           //Reset sum of P vector
    }
    if(no_vertices>10)                                                                      //Display last iteration values if number of vertice is greater than 10
    {
        for(int i=0;i<no_vertices;i++)
            cout<<"P["<<i<<"]="<<fixed<<setprecision(7)<<P[i]<<"\n";
    }
}
