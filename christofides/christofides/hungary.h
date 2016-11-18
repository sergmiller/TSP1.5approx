//
//  hungary.h
//  christofides
//
//  Created by Serg Miller on 14.11.16.
//  Copyright © 2016 sergmiller. All rights reserved.
//

#ifndef hungary_h
#define hungary_h

#define BIG_INF (long long)1e17

using std::cout;
using std::endl;

//Hungarian Assignment Algorithm
vector <int> hungary(vector <vector <int64_t> >& g) {
    int n = (int)g.size();
    vector <vector <int64_t> > a(n+1,vector <int64_t> (n+1));
    for(int i = 0 ;i < n;++i) {
        for(int j = 0;j < n;++j) {
            a[i+1][j+1] = g[i][j];
        }
    }
    vector <int64_t> u(n+1), v(n+1);
    vector <int> p(n+1), way(n+1);
    for(int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0;
        vector<int64_t> minv (n+1, BIG_INF);
        vector<int> used (n+1, false);
        do{
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            int64_t delta = BIG_INF;
            for(int j = 1; j <= n; ++j)
                if(!used[j]) {
                    int64_t cur = a[i0][j]-u[i0]-v[j];
                    if(cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta)
                        delta = minv[j],  j1 = j;
                }
            for(int j = 0; j <= n; ++j)
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                }
                else
                    minv[j] -= delta;
            j0 = j1;
        } while(p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    
    vector <int> ans(n);
    for(int i = 0;i < n;++i) {
        ans[p[i+1]-1] = i;
    }
    return ans;
}

#endif /* hungary_h */
