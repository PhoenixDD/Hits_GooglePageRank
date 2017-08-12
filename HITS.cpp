/****************************************************************************************************************************************************************
  Author:
  Dhairya Dhondiyal

  Description:
  The program calculates Hubs and Authority values for each vertex according to the input parameters.

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
struct List                                                                                  //Holds pointer to each vertex
{
    Node* first;
    List(Node* node=NULL)
    {
        first=node;
    }
};
int main()
{
    int iterations,initialvalue,inp1,inp2,no_vertices;                                      //Declaring all initial values
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
    vector<double> H;                                                                       //Declare the Hubs Vector
    input>>inp1>>inp2;                                                                      //Get the Vertice and Edge value
    no_vertices=inp1;
    if(no_vertices>10)                                                                      //set Iteration and Initial values if # vertice greater than 10
    {
        iterations=0;
        initialvalue=-1;
    }
    List* adjlist_in=(struct List*)malloc(no_vertices*sizeof(struct List));                 //Declare Adjacency list
    List* adjlist_out=(struct List*)malloc(no_vertices*sizeof(struct List));                //Declare Adjacency list for '
    for(int i=0;i<no_vertices;i++)                                                          //Initialize all list pointers to Null
        adjlist_in[i].first=NULL;
    for(int i=0;i<no_vertices;i++)                                                          //Initialize all ' list pointers to Null
        adjlist_out[i].first=NULL;
    while(input>>inp1>>inp2)                                                                //Read all file values
    {
        if(adjlist_in[inp2].first!=NULL)                                                    //Make Adjacency list'
        {
            Node* temp=adjlist_in[inp2].first;
            while(temp->next!=NULL)
                temp=temp->next;
            temp->next=new Node(inp1);
        }
        else
            adjlist_in[inp2].first=new Node(inp1);
        if(adjlist_out[inp1].first!=NULL)                                                   //Make Adjacency List
        {
            Node* temp=adjlist_out[inp1].first;
            while(temp->next!=NULL)
                temp=temp->next;
            temp->next=new Node(inp2);
        }
        else
            adjlist_out[inp1].first=new Node(inp2);
    }
    for(int i=0;i<no_vertices;i++)                                                          //Initialize all H values
    {
        if(initialvalue==-1)
            H.push_back((double)1/no_vertices);
        else if(initialvalue==-2)
            H.push_back((double)1/sqrt(no_vertices));
        else
            H.push_back(initialvalue);
    }
    vector<double> A(H);                                                                    //Declare and initialize all A values
    if(no_vertices<=10)                                                                      //Display Base values
    {
        cout<<"Base\t: "<<setw(2)<<"0"<<" :";
        for(int j=0;j<no_vertices;j++)
        {
            cout<<"A/H["<<j<<"]="<<fixed<<setprecision(7)<<A[j]<<"/"<<H[j]<<"\t";
        }
        cout<<endl;
    }
    double A_sum=0,H_sum=0;                                                                 //Declare Required variables
    for(int i=0;;i++)
    {
        vector<double> A_old(A),H_old(H);
        for(int j=0;j<no_vertices;j++)                                                      //Get authority values of each incoming vertex and do necessary calculations
        {
            Node* temp=adjlist_in[j].first;
            A[j]=0;
            while(temp!=NULL)
            {
                A[j]+=H[temp->outVertex];
                temp=temp->next;
            }
            A_sum+=A[j]*A[j];
        }
        for(int j=0;j<no_vertices;j++)                                                      //Get Hub values of each outgoing vertex and do necessary calculations
        {
            H[j]=0;
            Node* temp=adjlist_out[j].first;
            while(temp!=NULL)
            {
                H[j]+=A[temp->outVertex];
                temp=temp->next;
            }
            H_sum+=H[j]*H[j];
        }
        for(int j=0;j<no_vertices;j++)                                                      //Scaling step
        {
            A[j]/=sqrt(A_sum);
            H[j]/=sqrt(H_sum);
        }
        if(no_vertices<=10)                                                                 //Display values after each Iteration
        {
            cout<<"iter\t: "<<setw(2)<<i+1<<" :";
            for(int j=0;j<no_vertices;j++)
                cout<<"A/H["<<j<<"]="<<fixed<<setprecision(7)<<A[j]<<"/"<<H[j]<<"\t";
            cout<<endl;
        }
        A_sum=0;                                                                                        //Reset sum of Authority vector
        H_sum=0;                                                                                        //Reset sum of Hub vector
        if(iterations<0)                                                                                //Stopping condition 1
        {
            int k;
            for(k=0;k<no_vertices;k++)
            {
                if((fabs(A[k]-A_old[k])>=pow(10,iterations))||(fabs(H[k]-H_old[k])>=pow(10,iterations)))
                    break;
            }
            if(k==no_vertices)
                break;
        }
        else if(iterations>0)                                                                           //Stopping condition 2
        {
            if(i==iterations-1)
                break;
        }
        else                                                                                            //Stopping condition 3
        {
            int k;
            for(k=0;k<no_vertices;k++)
            {
                if((fabs(A[k]-A_old[k])>=pow(10,-5))||(fabs(H[k]-H_old[k])>=pow(10,-5)))
                    break;
            }
            if(k==no_vertices)
                break;
        }
    }
    if(no_vertices>10)                                                                                  //Display last iteration values if number of vertice is greater than 10
    {
        for(int i=0;i<no_vertices;i++)
            cout<<"A/H["<<i<<"]="<<fixed<<setprecision(7)<<A[i]<<"/"<<H[i]<<"\n";
    }
}

