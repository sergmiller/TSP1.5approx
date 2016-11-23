//
//  cf_ant_task.h
//  christofides
//
//  Created by Serg Miller on 24.11.16.
//  Copyright © 2016 sergmiller. All rights reserved.
//

#ifndef cf_ant_task_h
#define cf_ant_task_h

#define INF (long long)1e15
#define loop(i, n) for(long long (i) = 0; (i) < (n) ; ++ (i))

typedef long long ll;

const ll maxn = 5000 + 100;

int64_t solve(int n, int s, int e, vector <int64_t>& a, vector <int64_t>& b, vector <int64_t>& c, vector <int64_t>& d, vector <int64_t>& x) {
    int64_t dp[2][maxn][2][2];
    int64_t ans = INF;
    fill(&dp[0][0][0][0], &dp[0][0][0][0] + 8 * maxn, INF);
    dp[1][0][0][0] = 0;
    loop(i,n) {
        bool I = i & 1;
        bool J = !I;
        loop(j,n+1)  loop(k,2)  loop(l,2)  dp[I][j][k][l] = INF;
        loop(j,n+1)  loop(k,2)  loop(l,2)  if(dp[J][j][k][l] != INF){
            int64_t val = dp[J][j][k][l];
            if(i != s && i != e){
                /* LL */{
                    int64_t cur = 2LL * x[i] + a[i] + c[i];
                    if(j + k + l > 1)   dp[I][j-1][k][l] = min(dp[I][j-1][k][l], cur + val);
                    if(i == n-1 && !j && k && l)    ans = min(ans, cur + val);
                }
                /* LR */{
                    int64_t cur = a[i] + d[i];
                    if(j or k)  dp[I][j][k][l] = min(dp[I][j][k][l], cur + val);
                }
                /* RL */{
                    int64_t cur = b[i] + c[i];
                    if(j or l)  dp[I][j][k][l] = min(dp[I][j][k][l], cur + val);
                }
                /* RR */{
                    int64_t cur = -2LL * x[i] + b[i] + d[i];
                    dp[I][j+1][k][l] = min(dp[I][j+1][k][l], cur + val);
                }
            }
            else if(i == s && !k){
                /* L */{
                    int64_t cur = x[i] + c[i];
                    if(j)   dp[I][j-1][1][l] = min(dp[I][j-1][1][l], cur + val);
                    if(i == n-1 && !j && l) ans = min(ans, cur + val);
                }
                /* R */{
                    int64_t cur = -x[i] + d[i];
                    dp[I][j][1][l] = min(dp[I][j][1][l], cur + val);
                }
            }
            else if(i == e && !l){
                /* L */{
                    int64_t cur = x[i] + a[i];
                    if(j)   dp[I][j-1][k][1] = min(dp[I][j-1][k][1], cur + val);
                    if(i == n-1 && !j && k) ans = min(ans, cur + val);
                }
                /* R */{
                    int64_t cur = -x[i] + b[i];
                    dp[I][j][k][1] = min(dp[I][j][k][1], cur + val);
                }
            }
        }
    }
    return ans;
}


int64_t solve_cf_ant(int n, vector<int64_t>& a, vector <int64_t>& x){
    int64_t ans = INF;
    for(int i = 0;i < n;++i) {
        for(int j = i+1;j < n;++j) {
            ans = min(ans, solve(n, i, j, a, a, a, a, x) + x[j] - x[i] + a[i] + a[j]);
        }
    }
    
    return ans;
}

#endif /* cf_ant_task_h */
