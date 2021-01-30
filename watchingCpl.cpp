/*
    Input: # of test_cases
           N (Total number of boxes available), K (Height of the wall)

    Output: Minimum number of boxes required to build 2 towers of height at least K

    Time Complexity : O(N*K)
    Space Complexity : O(N*K)
*/


#include<bits/stdc++.h>
using namespace std;

typedef long long int lli;

int main(){

    lli T, N, K;
    cin>>T;

    while(T){
        T-=1;

        cin>>N>>K;

        vector<lli> H;
        
        lli numb;

        for(int i = 0; i < N; i++){
            cin>>numb;
            H.push_back(numb);
        }

        sort(H.begin(), H.end(), greater<lli>());

        vector<lli> prefixSum;
        lli prefixSumSoFar = 0;

        for(auto n: H){
            prefixSumSoFar += n;
            prefixSum.push_back(prefixSumSoFar);
        }
        
        lli MAX = LLONG_MAX;
        vector<vector<lli>> dp(N+1, vector<lli>(K+1, MAX));

        for(lli i = 1; i <= N; i++){
            for(lli j = 0; j <= K; j++){
                if(j <= H[i-1]){
                    dp[i][j] = H[i-1];
                }
                else{
                    if(dp[i-1][j-H[i-1]] == MAX)
                        dp[i][j] = MAX;
                    else
                        dp[i][j] = min(dp[i-1][j], H[i-1] + dp[i-1][j-H[i-1]]);
                }
            }
        }

        bool possible = false;

        for(int i = 0; i < N; i++){
            if(prefixSum[i] - dp[i][K] >= K){
                cout<<i+1<<endl;
                possible = true;
                break;
            }
        }

        if(!possible)
            cout<<-1<<endl;
        
    }
}