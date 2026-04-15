//Musfirat-223
#include <bits/stdc++.h>
using namespace std;
#define ch char
#define str string

set<ch> A;
vector<pair<str,str>> F;
vector<set<ch>> CK;

set<ch> clsr(set<ch> s){
    set<ch> r = s;
    bool chng = true;
    while(chng){
        chng = false;
        for(auto &fd : F){
            bool ok = true;
            for(ch c : fd.first)
                if(!r.count(c)) ok = false;

            if(ok){
                for(ch c : fd.second){
                    if(!r.count(c)){
                        r.insert(c);
                        chng = true;
                    }
                }
            }
        }
    }
    return r;
}
bool mnml(set<ch> s){
    for(auto &k : CK){
        if(includes(s.begin(), s.end(), k.begin(), k.end()))
            return false;
    }
    return true;
}
vector<set<ch>> sub(set<ch> s){
    vector<ch> v(s.begin(), s.end());
    vector<set<ch>> rlt;
    int n = v.size();

    for(int i = 1; i < (1<<n); i++){
        set<ch> t;
        for(int j = 0; j < n; j++){
            if(i & (1<<j)) t.insert(v[j]);
        }
        rlt.push_back(t);
    }
    return rlt;
}
set<ch> get_RS(){
    set<ch> RS = A;
    for(ch a : A){
        set<ch> temp = RS;
        temp.erase(a);
        if(clsr(temp) == A){
            RS.erase(a);
        }
    }
    return RS;
}
void ck_rs(set<ch> RS){
    vector<set<ch>> subs = sub(RS);
    bool found = false;
    for(auto &s : subs){
        if(clsr(s) == A && mnml(s)){
            CK.push_back(s);
            found = true;
        }
    }
    if(!found){
        CK.push_back(RS);
    }
}
void replc(){
    set<ch> DA;
    for(auto &fd : F){
        for(ch c : fd.second) DA.insert(c);
    }
    queue<set<ch>> q;
    set<set<ch>> vs;
    for(auto &k : CK){
        q.push(k);
        vs.insert(k);
    }
    while(!q.empty()){
        set<ch> curr = q.front();
        q.pop();
        set<ch> PA = curr;
        set<ch> al;
        for(ch c : PA){
            if(DA.count(c)) al.insert(c);
        }
        if(al.empty()) continue;
        for(ch a : al){
            for(auto &fd : F){
                if(fd.first.find(a) != str::npos){
                    set<ch> nws = curr;
                    nws.erase(a);
                    for(ch c : fd.second) nws.insert(c);
                    if(vs.count(nws)) continue;
                    vs.insert(nws);
                    if(clsr(nws) == A && mnml(nws)){
                        CK.push_back(nws);
                        q.push(nws);
                    }
                }
            }
        }
    }
}
int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");
    if(!in){ cout << "ERROR: input.txt not found\n"; return 0; }
    str s1, s2;
    getline(in, s1);
    getline(in, s2);
    for(ch c : s1){
        if(isalpha(c)) A.insert(c);
    }
    stringstream ss(s2);
    str tmp;
    while(getline(ss, tmp, ',')){
        int p = tmp.find("->");
        if(p == str::npos) continue;
        str l = tmp.substr(0, p);
        str r = tmp.substr(p+2);
        l.erase(remove(l.begin(), l.end(), ' '), l.end());
        r.erase(remove(r.begin(), r.end(), ' '), r.end());
        F.push_back({l, r});
    }
    set<ch> RS = get_RS();   
    ck_rs(RS);               
    replc();                 
    out << "Total Candidate Keys: " << CK.size() << "\n";
    int i = 1;

    for(auto &k : CK){
        out << "CK" << i++ << ": ";
        for(ch c : k) out << c;
        out << "\n";
    }

    cout << "Done. \n";
}