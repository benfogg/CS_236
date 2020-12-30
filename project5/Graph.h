#pragma once
#include <map>
#include "Node.h"
#include <stack>
#include <iostream>
#include <vector>
using namespace std;

class Graph {
    public:
    map<int, Node> nodeList;
    stack<int> topologicalSearch;
    vector<set<int>> scc;
    set<int>local;

    void dfs(Node theNode) {
        //cout <<"THIS NODE:" << theNode.id << endl;
        if (theNode.isVisited == true) {
            return;
        }
        else {
            //cout << "here 8"<< endl; //8,9,10,11 ?
            nodeList.at(theNode.id).isVisited = true;
            //cout << "PUSHED: " <<theNode.id <<  endl;
            //topologicalSearch.push(theNode.id);
            //cout << "Adjecency size: " <<theNode.adjacencies.size() << endl;
            for (auto i: theNode.adjacencies) {
                //cout << i << " adjecency" << endl;
                //cout << nodeList[i].id << endl;
                //cout << "here 9"<< endl;
                if (nodeList[i].isVisited == false) {
                    //cout << "here 10"<< endl;
                    dfs(nodeList[i]);
                }
            }
            //cout << "PUSHED: " <<theNode.id <<  endl;
            topologicalSearch.push(theNode.id);
            return;
        }
    }
    void dfsForest() {
        //cout << "here 11"<< endl;
        for (auto i: nodeList) {
            //cout << "start node: " << i.first << endl;
            //cout << "ADJACENEY size: "<< i.second.adjacencies.size() << endl;
            /*
            for (auto j: i.second.adjacencies) {
                //cout << "adjecent" <<j << endl;
                //cout << "nodeList[j].id" << nodeList[j].id << endl;
            }
            */
            //cout << "here 11.1"<< endl;
            if(i.second.isVisited == false) {
                //cout << "here 11.1.1"<< endl;
                dfs(i.second);
            }
            else {
                //cout << "here 11.1.2"<< endl;
            }

        }
        return;
    }


    void dfsForestForward() {
        /*
        for (auto i: nodeList) {
            if(i.second.isVisited == false) {
                dfs(i.second);
            }
        }
        */
        //cout << "stack SIZE: " << topologicalSearch.size() << endl;
        while(topologicalSearch.size() != 0){
            //cout << endl;
            //cout << "stack TOP: " << topologicalSearch.top() << endl;
            //cout << "here 12"<< endl;
            if (!nodeList[topologicalSearch.top()].isVisited) {
                //cout << "here 12.1"<< endl;
                dfsSCC(nodeList[topologicalSearch.top()]);
            }
            else {
                //cout << "here 12.2"<< endl;
                if (local.size() != 0) {
                    scc.push_back(local);
                    //cout << "new SCC:";
                    /*
                    for (auto i: local) {
                        cout << i<< ",";
                    }
                    cout << endl;
                    */
                    local.clear();
                }
                //cout << "POPPED: " << topologicalSearch.top() << endl;
                topologicalSearch.pop();
            }
        }
        //cout <<  endl << endl;
        return;
    }

    void dfsSCC(Node theNode) {
        //cout <<"THIS NODE: " << theNode.id << endl;
        if (theNode.isVisited == true) {
            
            return;
        }
        else {
            //cout << "here 13"<< endl;
            nodeList.at(theNode.id).isVisited = true;
            //cout << theNode.id << "was visited" << endl;
            local.insert(theNode.id);
            //topologicalSearch.pop();
            //cout << "Adjecency size: " <<theNode.adjacencies.size() << endl;
            for (auto i: theNode.adjacencies) {
                //cout << "check node "<< i << "  which is adjecent" << endl;
                if (nodeList[i].isVisited == false) {
                    dfsSCC(nodeList[i]);
                    //cout << "here 13.1"<< endl;
                }/*
                else {
                    cout << "here 13.2"<< endl;
                }*/
            }
            return;
        }
    }

    void addEdge(int from, int to, bool dependent) {
        //Node newNode;
        nodeList[from].adjacencies.insert(to);
        nodeList[from].isSelfDependent = dependent;
        /*
        newNode.id = from;
        newNode.isSelfDependent = dependent;
        newNode.adjacencies.insert(to); //  next thing to try
        nodeList.insert({from, newNode});
        //nodeList[from].adjacencies.insert(to);
        */
        return;
    }
    void ToString() {
        cout << "Dependency Graph" << endl;
        //cout << "here 7" << endl;
        for(auto i:nodeList) {
            cout << "R" << i.first << ":";
            int x = i.second.adjacencies.size();
            int y = 0;
            for (auto j: i.second.adjacencies) {
                //cout << "here 7." << y << endl;
                if (y != x - 1) {
                    cout <<"R" << j <<",";
                }
                else {
                     cout <<"R" << j;
                }
                y++;
            }
            cout << endl;
        }
        return;
    }

};
