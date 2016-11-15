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

#include <vector>
#include <cassert>
#include <algorithm>

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


#endif /* tools_h */
