#include "datalog.h"
#include <sstream>

vector<Rule> Datalog::GetRules() {
    return Rules;
}
vector<Predicate> Datalog::GetQueries() {
    return Queries;
}
vector<Predicate> Datalog::GetFacts() {
    return Facts;
}
vector<Predicate> Datalog::GetSchemes() {
    return Schemes;
}
void Datalog::SetDomain(set<string> Set) {
    Domain = Set;
}
void Datalog::SetFacts(vector<Predicate> Fact) {
    for (unsigned int i = 0; i < Fact.size(); i++) {
        Facts.push_back(Fact.at(i));
    }
}
void Datalog::SetQueries(vector<Predicate> Query) {
    for (unsigned int i = 0; i < Query.size(); i++) {
        Queries.push_back(Query.at(i));
    }
}
void Datalog::SetSchemes(vector<Predicate> Scheme) {
    for (unsigned int i = 0; i < Scheme.size(); i++) {
        Schemes.push_back(Scheme.at(i));
    }
}
void Datalog::SetRules(vector<Rule> Rule) {
    for (unsigned int i = 0; i < Rule.size(); i++) {
        Rules.push_back(Rule.at(i));
    }
}
string Datalog::ToString() {
    stringstream ss;
    ss << "Schemes(" << Schemes.size() << "):\n";
    for (unsigned int i = 0; i< Schemes.size();i++) {
        ss<< "  " << Schemes.at(i).ToString() << "\n";
    }
    ss << "Facts(" << Facts.size() << "):\n";
    for (unsigned int i = 0; i< Facts.size();i++) {
        ss<< "  " << Facts.at(i).ToString() << ".\n";
    }
    ss << "Rules(" << Rules.size() << "):\n";
    for (unsigned int i = 0; i< Rules.size();i++) {
        ss<< "  " << Rules.at(i).ToString() << "\n";
    }
    ss << "Queries(" << Queries.size() << "):\n";
    for (unsigned int i = 0; i< Queries.size();i++) {
        ss<< "  " << Queries.at(i).ToString() << "?\n";
    }
    ss << "Domain(" << Domain.size() << "):\n";
    set<string>::iterator it;
    for (it = Domain.begin(); it != Domain.end(); it++) {
        ss << "  " << *it << "\n";
    }

    string thing = ss.str();
    return thing;
}
