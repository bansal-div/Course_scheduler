#include <bits/stdc++.h>

using namespace std;

class course {
    public:
    bool explored;
    int num;
    vector<string> prereq;
};

void addedgedir(unordered_map<string, course> &graph, string &s1, string &s2) {
    graph[s2].prereq.push_back(s1);
}

void addedgeundir(unordered_map<string, course> &graph, string &s1, string &s2) {
    graph[s2].prereq.push_back(s1);
    graph[s1].prereq.push_back(s2);
}

void check(unordered_map<string, course> &graph, string s, int &c) {
    graph[s].explored = true;
    graph[s].num = c;
    for(auto i : graph[s].prereq) {
        if(graph[i].explored == false) {
            check(graph, i, c);
        }
    }
}

int calc(unordered_map<string, course> &undirgraph, unordered_map<string, course> &dirgraph) {
    int c = 1;
    for(auto i : undirgraph) {
        if(i.second.explored == false) {
            check(undirgraph, i.first, c);
            c++;
        }
    }
    for(auto i : undirgraph) {
        dirgraph[i.first].num = i.second.num;
    }
    return c;
}

void dfs(unordered_map<string, course> &graph, string s, vector<string> &temp, int &c) {
    graph[s].explored = true;
    for(auto i : graph[s].prereq) {
        if(graph[i].explored == false) {
            dfs(graph, i, temp, c);
        }
    }
    temp.push_back(s);
}

bool iscycle(unordered_map<string, course> &graph, string s, unordered_map<string, bool> &stack) {
    graph[s].explored = true;
    stack[s] = true;
    for(auto i : graph[s].prereq) {
        if(graph[i].explored == false) {
            bool t = iscycle(graph, i, stack);
            if(t == true) {
                return true;
            }
        }
        else {
            if(stack[i]) {
                return true;
            }
        }
    }
    stack[s] = false;
    return false;
}

bool cycle(unordered_map<string, course> graph) {
    unordered_map<string, bool> stack;
    for(auto i : graph) {
        stack[i.first] = false;
    }
    bool che = false;
    for(auto i : graph) {
        if(i.second.explored == false) {
            che = iscycle(graph, i.first, stack);
            if(che == true) {
                break;
            }
        }
    }
    return che;
}

int main() {
    int n;
    cout << "Enter number of courses" << endl;
    cin >> n;
    unordered_map<string, course> dirgraph;
    unordered_map<string, course> undirgraph;
    vector<string> vertex(n);
    for(int i =0; i < n; i++) {
        cout << "Enter name of course " << i + 1 << ":";
        string s;
        cin >> s;
        course c;
        c.explored = false;
        vector<string> temp;
        c.prereq = temp;
        c.num = 0;
        dirgraph[s] = c;
        undirgraph[s] = c;
        vertex[i] = s;
    }
    for(auto i : vertex) {
        cout << "Enter number of pre-prequisites for " << i << ":";
        int m;
        cin >> m;
        int j = 0;
        while(j < m) {
            string s;
            cin >> s;
            if(dirgraph.find(s) == dirgraph.end()) cout << "Enter valid course" << endl;
            else {
                addedgedir(dirgraph, i, s);
                addedgeundir(undirgraph, i, s);
                j++;
            }
        }
    }

    if(cycle(dirgraph)) {
        cout << "Cycle detected" << endl;
        return 0;
    }

    int comp = calc(undirgraph, dirgraph);
    vector<vector<string>> schedule(comp);

    for(auto str : vertex) {
        if(dirgraph[str].explored == false) {
            dfs(dirgraph, str, schedule[dirgraph[str].num], comp);
        }
    }
    for(int i = 0; i < comp; i++) {
        for(int j = schedule[i].size() - 1; j >= 0; j--) {
            cout << schedule[i][j] << "-> ";
        }
        cout << endl;
    }
}