#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <queue>

using namespace std;

vector<vector<pair<int, int>>> prevN;

//grid of building
vector<vector<int>> m;

//R is row, C is column, sr is starting row, sc is starting column
int R, C, sr, sc, er, ec;

//queue for rows and columns
deque<int> rq;
deque <int> cq;

//node count
int nodes_left = 1, nodes_next = 0;
//if reached destination
bool reachEnd = false;

//visited coords
vector<vector<bool>> visited;

//directions (N, S, E, W)
int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, 1, -1 };


//gets path
vector<pair<int, int>> reconstructPath() {
    vector<pair<int, int>> path;

    for (pair<int, int> i = make_pair(er, ec); i != make_pair(-1, -1); i = prevN[i.first][i.second]) {
        path.push_back(i);
    }
    
    if (path[path.size() - 1] == make_pair(sr, sc)) {
        return path;
    }
    vector<pair<int, int>> failed;
    return failed;
}

//checks surrounding to move (if no obstructions)
void explore_neighbours(int r, int c) {
    
    for (int i = 0; i < 4; i++) {
        int rr = r + dr[i];
        int cc = c + dc[i];
        
        if (rr < 0 || cc < 0) continue; //if out of bounds
        if (rr >= R || cc >= C) continue; //if out of bounds
        if (visited[rr][cc]) continue; //if already visited
        if (m[rr][cc] == 0) continue; //if wall

        rq.push_back(rr);
        cq.push_back(cc);
        visited[rr][cc] = true;
        prevN[rr][cc] = make_pair(r, c);
        nodes_next++;
    }
}

//the BFS
int solve() {
    int amt = 0;
    rq.push_back(sr);
    cq.push_back(sc);
    visited[sr][sc] = true;
    int r, c;
    while (rq.size() > 0) {
        r = rq[0];
        rq.pop_front();
        c = cq[0];
        cq.pop_front();
        if (m[r][c] == 2) {
            reachEnd = true;
            break;
        }
        explore_neighbours(r, c);
        nodes_left--;
        if (nodes_left == 0) {
            nodes_left = nodes_next;
            nodes_next = 0;

            //moves once
            amt++;
        }
    }
    if (reachEnd) {
        return amt; //finished
    }


    return -1;
}



int main() {
    
    ifstream fin("path.in");
    ofstream fout("path.out");
    fin >> R >> C >> sr >> sc >> er >> ec;

    //initializes vectors
    for (int i = 0; i < R; i++) {
        vector<bool> a;
        vector<int> b;
        vector<pair<int, int>> c;
        visited.push_back(a);
        m.push_back(b);
        prevN.push_back(c);
    }

    //initializes grid and vector values
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            int num;
            fin >> num;
            m[i].push_back(num);
            visited[i].push_back(false);
            prevN[i].push_back(make_pair(-1, -1));
        }
    }

    m[er][ec] = 2; //setting end point
    int total = solve();
    vector<pair<int, int>> path = reconstructPath();

    fout << total << endl;
    
    for (int i = path.size() - 1; i >= 0; i--) {
        fout << path[i].first << ", " << path[i].second << endl;
    }
    return 0;
}