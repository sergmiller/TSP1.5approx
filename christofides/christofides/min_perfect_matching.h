//
//  min_perfect_matching.h
//  christofides
//
//  Created by Serg Miller on 23.11.16.
//  Copyright © 2016 sergmiller. All rights reserved.
//

#ifndef min_perfect_matching_h
#define min_perfect_matching_h

#include "PerfectMatching.h"
//#include "blossom5-v2Kolmogorov/GEOM/GeomPerfectMatching.h"

#define INF (long long)1e15


//Blossom Admond's Algorithm for Minimal Cost Matching
vector <int> get_min_perfect_matching(vector <vector <int64_t> >& g) {
    int n = (int)g.size();
    
    PerfectMatching matching(n,(n*(n-1))/2);
    
    for(int i = 0;i < n;++i) {
        for(int j = i+1;j < n;++j) {
            if(g[i][j] != INF) {
                matching.AddEdge(i, j, (int)g[i][j]);
            }
        }
    }
    cout << "OK" << endl;
    matching.Solve();
//    cout << "OK" << endl;
    vector <int> ans(n);
    for(int i = 0;i < n;++i) {
        ans[i] = matching.GetMatch(i);
    }
//    cout << "OK" << endl;
    
    return ans;
}

#endif /* min_perfect_matching_h */
