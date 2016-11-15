//
//  euler.h
//  christofides
//
//  Created by Serg Miller on 15.11.16.
//  Copyright © 2016 sergmiller. All rights reserved.
//

#ifndef euler_h
#define euler_h

void dfs(int prev, int v, vector<vector<int> >& g, vector <int>& cycle) {
    for(int i = 0;i < g.size(); ++i) {
        if(g[v][i]) {
            g[v][i] = g[i][v] = 0;
            dfs(v, i, g, cycle);
            cycle.push_back(v);
        }
    }
    
}

vector <int> euler_cycle(vector<vector<int> > g) {
    vector <int> cycle;
    
    for(int i = 0;i < g.size();++i) {
        if(g[0][i]) {
            dfs(0, i, g, cycle);
            break;
        }
    }
    return cycle;
}

#endif /* euler_h */
