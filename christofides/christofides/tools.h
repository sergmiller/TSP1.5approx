//
//  tools.h
//  christofides
//
//  Created by Serg Miller on 14.11.16.
//  Copyright © 2016 sergmiller. All rights reserved.
//

#ifndef tools_h
#define tools_h

#define INF (long long)1e15

#include <cassert>
#include <random>
#include "cf_ant_task.h"

void check_metric(int n, vector <vector <int64_t> >&  g) {
    for(int i = 0;i < n;++i) {
        for(int j = i+1;j < n;++j) {
            for(int k = j+1;k < n;++k) {
                int64_t v[3];
                v[0] = g[i][j];
                v[1] = g[i][k];
                v[2] = g[j][k];
                std::sort(v, v+3);
                assert(v[0] + v[1] >= v[2]);
            }
        }
    }
}

void scan_graph(int n, vector <vector <int64_t> >& g) {
    int m;
    cin >> m;
    int v1,v2,c;
    
    for(int i = 0;i < m;++i) {
        cin >> v1 >> v2 >> c;
        --v1;
        --v2;
        g[v1][v2] = c;
        g[v2][v1] = c;
    }
}

int make_random_test_1(int n, vector <vector <int64_t> >& g) {
    int add;
    cin >> add;
    //Random Generator for random weights
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1,2 + add);
    
    vector <int> ind(n);
    for(int i = 0;i < n;++i) {
        ind[i] = i;
    }
    random_shuffle(ind.begin(), ind.end());
    for(int i = 0;i < n;++i) {
        g[ind[i]][ind[(i+1)%n]] = 1;
        g[ind[(i+1)%n]][ind[i]] = g[ind[i]][ind[(i+1)%n]];
    }
    
    int64_t cur;
    
    for(int i = 0;i < n;++i) {
        for(int j = i+1;j < n;++j) {
            cur = dis(gen);
            cur = min(2LL,cur);
            g[i][j] = min(g[i][j], cur);
            g[j][i] = g[i][j];
        }
    }
    return add;
}

int64_t make_random_test_2(int n, vector <vector <int64_t> >& g) {
    //Random Generator for random weights
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1,100);
    
    vector <int64_t> a(n);
    vector <int64_t> x(n);
    int64_t cur;
    
    for(int i = 0;i < n;++i) {
        cur = dis(gen);
        a[i] = cur;
        cur = dis(gen);
        x[i] = cur;
        if(i)
            x[i] += x[i-1];
    }
    
    
    for(int i = 0;i < n;++i) {
        for(int j = i+1;j < n;++j) {
            g[i][j] = x[j] - x[i] + a[i] + a[j];
            g[j][i] = g[i][j];
        }
    }
    
    int64_t exactly_min = solve_cf_ant(n, a, x);
    
//    for(int i = 0; i < n;++i) {
//        cout << a[i] << " ";
//    }
//    cout << endl;
//    for(int i = 0;i < n;++i){
//        cout << x[i] << " ";
//    }
//    cout << endl;
//    for(int i = 0;i < n;++i) {
//        for(int j = 0;j < n;++j) {
//            cout << g[i][j] << " ";
//        }
//        cout << endl;
//    }
    
    return exactly_min;
}


#endif /* tools_h */
