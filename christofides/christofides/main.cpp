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
#include "min_perfect_matching.h"



void build_christofides_apporx() {
    int type,n,v1,v2,add;
    int64_t expected = INF;
    
    cin >> type >> n;
    
//    vector <pair <int, pair <int,int> > > v;
    vector <vector <int64_t> > g(n,vector <int64_t> (n,INF));
    switch (type) {
        case 0:
            scan_graph(n,g);
            cout << "complete scanned graph, ";
            break;
        case 1:
            add = make_random_test_1(n,g);
            expected = n;
            cout << "complete random graph 1 type with p(1) = " << 1/(double)(add+2) << ", and exactly minimal hamilton cycle weight: " << expected << endl;
            break;
        case 2:
            expected = make_random_test_2(n,g);
            cout << "complete random graph 2 type with exactly minimal hamilton cycle weight: " << expected << endl;
            break;
        default:
            cout << "Invalid test parametrs" << endl;
            return;
    }
    
    cout << "with " << n << " nodes" << endl;
    
    
//    cout <<"**************" << endl;
//    cout << "Graph matrix:" << endl;
//    
//    for(int i = 0 ;i < n;++i) {
//        for(int j = 0;j < n;++j) {
//            cout << g[i][j] << " ";
//        }
//        cout << endl;
//    }
//    cout <<"**************" << endl;
    
    check_metric(n, g);
    
    vector <pair<int64_t, pair<int,int> > > MST = mst(n, g);
    vector <int> deg(n,0);
//    cout <<"**************" << endl;
//    cout << "MST:" << endl;
    int64_t wt = 0;
    vector <vector <int64_t> > MSTtable(n,vector <int64_t> (n,0));
    for(int i = 0;i < MST.size(); ++i) {
        v1 = MST[i].second.first;
        v2 = MST[i].second.second;
        MSTtable[v1][v2] = MST[i].first;
        MSTtable[v2][v1] = MST[i].first;
        ++deg[v1];
        ++deg[v2];
        wt += MST[i].first;
    }
    cout << "mst weight: " << wt << endl;
//    for(int i = 0;i < n;++i) {
//        for(int j = 0;j < n;++j) {
//            cout << MSTtable[i][j] << " ";
//        }
//        cout << endl;
//    }
//    
//    cout <<"**************" << endl;
    
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
    
    //Blossom Admond's Algorithm for Minimal Cost Matching
    vector <int> PERFECT_MATCHING = get_min_perfect_matching(subg);
    
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
    
    int64_t vg = 0;
    
    for(int i = 0;i < subn; ++i) {
        v1 = points_for_matching[i];
        v2 = points_for_matching[PERFECT_MATCHING[i]];
        assert(PERFECT_MATCHING[PERFECT_MATCHING[i]] == i);
        ++h[v1][v2];
        vg += g[v1][v2];
    }
    
    cout << "minimal perfect matching weight: " << vg/2 << endl;
    
    
//    cout << "**************" << endl;
//    for(int i = 0;i < subn;++i) {
//        for(int j = 0;j < subn;++j) {
//            cout << h[i][j] << " ";
//        }
//        cout << endl;
//    }
//    cout << "**************" << endl;
//    cout << "MST + minimal PM: " << endl;
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
    
//    cout << "min Hamilton cycle: " << endl;
    int64_t weight = 0;
    for(int i = 0;i < MIN_HAM_CYCLE.size();++i) {
        v1 = MIN_HAM_CYCLE[i];
        v2 = MIN_HAM_CYCLE[(i+1)%n];
//        cout << v1 + 1 << " " << v2 + 1 << " " << g[v1][v2] << endl;
        weight += g[v1][v2];
    }

    cout << "Hamilton cycle weight: ";
    cout << weight << endl;
    cout << endl << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    int t; //t - number of tests
    cin >> t;
    for(int i = 0;i < t;++i) {
        build_christofides_apporx();
    }
}
