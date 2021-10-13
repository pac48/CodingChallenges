#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <ostream>
#include <fstream>

using namespace std;

struct State{
  int row;
  int col;
  int val; // cost to go
  State* backPointer = nullptr;

  State(int rowIn=0, int colIn=0, int valIn=0, State* backPointerIn=nullptr){
      col = colIn;
      row = rowIn;
      val = valIn;
      backPointer = backPointerIn;
  }
  bool operator==(const State* state) const  {
        return col == state->col && row == state->row;
    }
    bool operator()(const State* state1, const State* state2) const {
        return (state1->val > state2->val);
    }
    unsigned long operator() (const State* state) const{
        unsigned long h1 = hash<int>()(state->row);
        unsigned long h2 = hash<int>()(state->col);
        return h1 ^ h2;
    }
};


//bool myfunction (State s1, State s2) { return (s1.val < s2.val); }

vector<State*> getChildren(State* cur){
    vector<State*> children;
    int newVal = cur->val + 1;;
    children.push_back(new State(cur->row, cur->col+1, newVal, cur));
    children.push_back(new State(cur->row, cur->col-1, newVal, cur));
    children.push_back(new State(cur->row+1, cur->col, newVal, cur));
    children.push_back(new State(cur->row-1, cur->col, newVal, cur));
    return children;
}

void printDebug(State* cur){
    while (cur->val != 0){
        cout << "row: " <<cur->row << ", col: " <<cur->col << ", val " << cur->val << " -- ";
        cur = cur->backPointer;
    }
    cout << "row: " <<cur->row << ", col: " <<cur->col << ", val " << cur->val << " -- ";
    cout << endl;

}

void nextMove(int n, int r, int c, vector <string> grid){
    unordered_set<State*, State> closedList;
    State* cur = new State(r,c, 0);
    priority_queue<State*, vector<State*>, State > openList;
    openList.emplace(cur);
    while (!openList.empty()){
        cur = openList.top();
        openList.pop();
        printDebug(cur);
        closedList.insert(cur);
        auto children = getChildren(cur);
        for (State* child: children){
            if (child->row < 0 || child->row >= grid.size() || child->col < 0 || child->col >= grid[0].size() ) {
                delete child;
                continue;
            }
            bool found = closedList.find(child) != closedList.end();
            if (!found || child->val < (*closedList.find(child))->val){ // not in closed set
                openList.push(child);
            }
        }
        int cur_row = cur->row;
        int cur_col = cur->col;
        if (grid[cur_row][cur_col] == 'p'){ // princess found
            break;
        }
    }

    while(cur->val != 0){
        cur = cur->backPointer;
    }
    for(auto state: closedList){
        delete state;
    }
    while (!openList.empty()){
        delete openList.top();
        openList.pop();
    }

}

int main(void) {

    int n, r, c;
    vector <string> grid;
    ifstream f;
    f.open("input");
    f >> n;
    f >> r;
    f >> c;

    for(int i=0; i<n; i++) {
        string s; f >> s;
        grid.push_back(s);
    }

    nextMove(n, r, c, grid);
    return 0;
}