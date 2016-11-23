//
//  mst.h
//  christofides
//
//  Created by Serg Miller on 14.11.16.
//  Copyright © 2016 sergmiller. All rights reserved.
//

#ifndef mst_h
#define mst_h


// Decreasing Paths Heuristic
int get_leader(int v, vector<int>& parent) {
    if(parent[v] == v)
        return v;
    return parent[v] = get_leader(parent[v], parent);
}

// Rank Heuristic
void merge(int v1, int v2, vector<int>& parent, vector <int>& sizes) {
    v1 = get_leader(v1,parent);
    v2 = get_leader(v2,parent);
    if(sizes[v1] < sizes[v2]) {
        std::swap(v1,v2);
    }
    parent[v2] = v1;
    sizes[v1] += sizes[v2];
}

// Kruscal's algorithm implementation
vector <pair<pair<int,int>,int64_t > > mst(int n, vector <vector <int64_t> >& g) {
    vector <pair< pair<int,int>,int64_t> > v;
    for(int i = 0 ;i < n;++i) {
        for(int j = i+1; j < n;++j) {
            v.push_back(make_pair(make_pair(i,j), g[i][j]));
        }
    }
    
    sort(v.begin(), v.end());
    
    vector <int> parent(n);
    vector <int> sizes(n,1);
    
    for(int i = 0;i < n;++i) {
        parent[i] = i;
    }
    
    vector <pair<pair<int,int>, int64_t > > ans;
    
    int ind = 0, v1, v2;
    
    while(ans.size() < n - 1) {
        v1 = v[ind].first.first;
        v2 = v[ind].first.second;
        if(get_leader(v1, parent) != get_leader(v2, parent)) {
            merge(v1,v2, parent, sizes);
            ans.push_back(v[ind]);
        }
        ++ind;
    }
    return ans;
}


#endif /* mst_h */
