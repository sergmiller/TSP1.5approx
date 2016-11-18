//
//  main.cpp
//  christofides
//
//  Created by Serg Miller on 14.11.16.
//  Copyright © 2016 sergmiller. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#include "mst.h"
#include "tools.h"
#include "euler.h"
#include "hungary.h"



int main() {
    freopen("input.txt", "r", stdin);
    int n,m;
    cin >> n >> m;
    vector <pair <int, pair <int,int> > > v(m);
    vector <vector <int64_t> > g(n,vector <int64_t> (n,INF));
    int v1,v2;
    for(int i = 0;i < m;++i) {
        cin >> v1 >> v2 >> v[i].first;
        --v1;
        --v2;
        v[i].second.first = v1;
        v[i].second.second = v2;
        g[v1][v2] = v[i].first;
        g[v2][v1] = v[i].first;
    }
    
//    for(int i = 0 ;i < n;++i) {
//        for(int j = 0;j < n;++j) {
//            cout << g[i][j] << " ";
//        }
//        cout << endl;
//    }
    
    check_metric(n, g);
    
    vector <pair<int, pair<int,int> > > MST = mst(n, v);
    vector <int> deg(n,0);
    for(int i = 0;i < MST.size(); ++i) {
        ++deg[MST[i].second.first];
        ++deg[MST[i].second.second];
    }
    
    vector <int> points_for_matching;
    map <int,int> numbers;
    
    for(int i = 0;i < n;++i) {
        if(deg[i] % 2 == 1) {
            numbers[i] = (int)points_for_matching.size();
            points_for_matching.push_back(i);
        }
    }
    
    int subn = (int)points_for_matching.size();
    
    vector <vector <int64_t> > subg(subn, vector <int64_t> (subn,INF));
    for(int i = 0;i < subn;++i) {
        for(int j = i+1;j < subn;++j) {
            subg[i][j] = g[points_for_matching[i]][points_for_matching[j]];
            subg[j][i] = subg[i][j];
        }
    }
    
    vector <int> PERFECT_MATCHING = hungary(subg);
    
//    cout << "mst:" << endl;
//    for(int i = 0;i < n-1; ++i) {
//        cout << MST[i].second.first + 1 << " " << MST[i].second.second + 1 << endl;
//    }
//    cout << "verts for matching:" << endl;
//    for(int i = 0;i < subn; ++i) {
//        cout << points_for_matching[i] + 1<< " ";
//    }
//    cout << endl;
//    cout << "matching:" << endl;
//    for(int i = 0;i < subn;++i) {
//        cout << points_for_matching[i] + 1 << " " << points_for_matching[PERFECT_MATCHING[i]] + 1 << endl;
//    }
    
    //merge edges from MST and Best Matching subrgraphs to H
    vector <vector <int> > h(n,vector <int>(n,0));
    for(int i = 0;i < n-1;++i) {
        v1 = MST[i].second.first;
        v2 = MST[i].second.second;
        ++h[v1][v2];
        ++h[v2][v1];
    }
    
    for(int i = 0;i < subn; ++i) {
        v1 = points_for_matching[i];
        v2 = points_for_matching[PERFECT_MATCHING[i]];
        ++h[v1][v2];
    }
    
//    cout << "merged: " << endl;
//    for(int i = 0;i < n; ++i) {
//        for(int j = 0;j < n;++j) {
//            cout << h[i][j] << " ";
//        }
//        cout << endl;
//    }
    
    vector <int> EULER_CYCLE = euler_cycle(h);
    
//    cout << "Euler cycle: " << endl;
//    for(int i = 0;i < EULER_CYCLE.size(); ++i) {
//        cout << EULER_CYCLE[i] + 1 << " ";
//    }
//    cout << endl;
    
    vector <int> MIN_HAM_CYCLE;
    vector <char> used(n, 0);
    
    for(int i = 0;i < EULER_CYCLE.size(); ++i) {
        if(used[EULER_CYCLE[i]])
            continue;
        MIN_HAM_CYCLE.push_back(EULER_CYCLE[i]);
        used[EULER_CYCLE[i]] = 1;
    }
    
    cout << "min hamilton path: " << endl;
    int64_t weight = 0;
    for(int i = 0;i < MIN_HAM_CYCLE.size();++i) {
        v1 = MIN_HAM_CYCLE[i];
        v2 = MIN_HAM_CYCLE[(i+1)%n];
        cout << v1 + 1 << " " << v2 + 1 << " " << g[v1][v2] << endl;
        weight += g[v1][v2];
    }
    
    cout << "path weight: " << weight << endl;
    
    return 0;
}
