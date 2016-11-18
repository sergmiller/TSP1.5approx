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

void check_metric(int n, vector <vector <int64_t> >&  g) {
    for(int i = 0;i < n;++i) {
        for(int j = i+1;j < n;++j) {
            for(int k = j+1;k < n;++k) {
                int64_t v[3];
                v[0] = g[i][j];
                v[1] = g[i][k];
                v[2] = g[j][k];
                std::sort(v, v+3);
                if(v[2] == INF) {
                    continue;
                }
                assert(v[0] + v[1] >= v[2]);
            }
        }
    }
}

vector <pair<int,pair<int,int> > >  scan_graph(int n, vector <vector <int64_t> >& g) {
    int m;
    cin >> m;
    int v1,v2;
    vector <pair <int, pair <int,int> > > v(m);
    for(int i = 0;i < m;++i) {
        cin >> v1 >> v2 >> v[i].first;
        --v1;
        --v2;
        v[i].second.first = v1;
        v[i].second.second = v2;
        g[v1][v2] = v[i].first;
        g[v2][v1] = v[i].first;
    }
    return v;
}

vector <pair<int,pair<int,int> > >  make_random_test(int n, vector <vector <int64_t> >& g) {
    //Random Generator for random edges
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,2);
    
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
            if(!cur)
                continue;
            g[i][j] = min(g[i][j], cur);
            g[j][i] = g[i][j];
        }
    }
    
    vector <pair<int,pair<int,int> > > bd;
    
    for(int i = 0;i < n;++i) {
        for(int j = i+1;j < n;++j) {
            if(g[i][j] != INF) {
                bd.push_back(make_pair((int)g[i][j], make_pair(i, j)));
            }
        }
    }
  
    
    return bd;
}





#endif /* tools_h */
