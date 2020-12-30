#pragma once
#include <set>


class Node {
    public:
    std::set<int> adjacencies;
    int id;
    bool isVisited;
    bool isSelfDependent;
    Node() {
        isVisited = false;
    }
};