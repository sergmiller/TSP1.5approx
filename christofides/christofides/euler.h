//
//  euler.h
//  christofides
//
//  Created by Serg Miller on 15.11.16.
//  Copyright © 2016 sergmiller. All rights reserved.
//

#ifndef euler_h
#define euler_h

//DFS for Euler Cycle
void dfs(int v, vector<vector<int> >& g, vector <int>& cycle, vector <int>& ref) {
    int i;
    for(; ref[v] < g.size(); ++ref[v]) {
        i = ref[v];
        if(g[v][i]) {
            --g[v][i];
            --g[i][v];
            dfs(i, g, cycle, ref);
            cycle.push_back(v);
        }
    }
    
}

vector <int> euler_cycle(vector<vector<int> > g) {
    vector <int> cycle;
    vector <int> ref(g.size(), 0);
    dfs(0, g, cycle, ref);
    
    return cycle;
}

#endif /* euler_h */
