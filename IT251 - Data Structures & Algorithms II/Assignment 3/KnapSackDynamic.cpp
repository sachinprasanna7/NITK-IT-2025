#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;


//BRUTE FORCE USING AN EXTRA VECTOR

class Solution1
{
    private:
        vector <int> answer;
        void solve(int W, int wt[], int val[], int n, int i, int maxAns){
            
            if(i == n && W < 0) return;
            else if (i == n && W >=0){
                answer.push_back(maxAns);
                return ;
            }
            
            solve(W - wt[i], wt, val, n, i+1, maxAns + val[i]);
            solve(W, wt, val, n, i+1, maxAns);
        }
        
    public:
    int knapSack(int W, int wt[], int val[], int n) { 

       solve(W, wt, val, n ,0, 0);
       
       return *max_element(answer.begin(), answer.end());
    }
};


//USING SIMPLE RECURSION, TRAVERSING FROM LEFT TO RIGHT

class Solution2
{
    private:
    
        int solve(int W, int wt[], int val[], int n, int i) {
            
            if(i == 0){
                if(wt[0] <= W) return val[0];
                else return 0;
            }
            
            int option1 = 0;
            
            if(wt[i] <= W){
                option1 = val[i] + solve(W - wt[i], wt, val, n, i - 1);
            }
            
            int option2 = solve(W, wt, val, n, i - 1);
            
            return max(option1, option2);
        }
        
    public:
    int knapSack(int W, int wt[], int val[], int n) { 
       
       return solve(W, wt, val, n, n - 1);
    }
};



//MEMOIZATION

class Solution3
{
    private:
    
        int solve(int W, int wt[], int val[], int n, int i, vector <vector <int>> &dp) {
            
            if(i == 0){
                if(wt[0] <= W) return val[0];
                else return 0;
            }
            
            if(dp[i][W] != -1) return dp[i][W];
            
            int option1 = 0;
            
            if(wt[i] <= W){
                option1 = val[i] + solve(W - wt[i], wt, val, n, i - 1, dp);
            }
            
            int option2 = solve(W, wt, val, n, i - 1, dp);
            
            dp[i][W] = max(option1, option2);
            
            return dp[i][W];
        }
        
    public:
    int knapSack(int W, int wt[], int val[], int n) { 
        
        vector <vector <int>> dp(n, vector <int> (W+1, -1));
       
       return solve(W, wt, val, n, n - 1, dp);
    }
};


//TABULATION METHOD

class Solution4
{
    private:
    
        int solve(int W, int wt[], int val[], int n) {
            
            vector <vector <int>> dp(n, vector <int> (W+1, 0));
            
            for(int w = wt[0] ; w <= W; w++){
                if(wt[0] <= W) dp[0][w] = val[0];
                else dp[0][w] = 0;
            }
            
            for(int i = 1 ; i < n ; i++){
                for(int w = 0 ; w <= W ; w++){
                    int option1 = 0;
                    
                    if(wt[i] <= w) option1 = val[i] + dp[i-1][w - wt[i]];
                    
                    int option2 = dp[i-1][w];
                    
                    dp[i][w] = max(option1, option2);
                }
            } 
            
            return dp[n-1][W];
            
        }
        
    public:
    int knapSack(int W, int wt[], int val[], int n) { 
        
       return solve(W, wt, val, n);
    }
};


//SPACE OPTIMISED TABULATION (2 ARRRAYS REQUIRED, INSEAD OF A 2D ARRAY)

class Solution5
{
    private:
    
        int solve(int W, int wt[], int val[], int n) {
            
            vector <int> prev (W+1, 0);
            vector <int> curr (W+1, 0);
            
            for(int w = wt[0] ; w <= W; w++){
                if(wt[0] <= W) prev[w] = val[0];
                else prev[w] = 0;
            }
            
            for(int i = 1 ; i < n ; i++){
                for(int w = 0 ; w <= W ; w++){
                    int option1 = 0;
                    
                    if(wt[i] <= w) option1 = val[i] + prev[w - wt[i]];
                    
                    int option2 = prev[w];
                    
                    curr[w] = max(option1, option2);
                }
                
                prev = curr;
            } 
            
            return prev[W];
            
        }
        
    public:
    int knapSack(int W, int wt[], int val[], int n) { 
        
       return solve(W, wt, val, n);
    }
};


//SPACE OPTIMSED - BEST TABULATION (ONLY ONE ARRAY)

class Solution6
{
    private:
    
        int solve(int W, int wt[], int val[], int n) {
            
            vector <int> curr (W+1, 0);
            
            for(int w = wt[0] ; w <= W; w++){
                if(wt[0] <= W) curr[w] = val[0];
                else curr[w] = 0;
            }
            
            for(int i = 1 ; i < n ; i++){
                for(int w = W ; w >= 0 ; w--){
                    int option1 = 0;
                    
                    if(wt[i] <= w) option1 = val[i] + curr[w - wt[i]];
                    
                    int option2 = curr[w];
                    
                    curr[w] = max(option1, option2);
                }
            } 
            
            return curr[W];
        }
        
    public:
    int knapSack(int W, int wt[], int val[], int n) { 
        
       return solve(W, wt, val, n);
    }
};

int main(){

    Solution1 sol1;
    Solution2 sol2;
    Solution3 sol3;
    Solution4 sol4;
    Solution5 sol5;
    Solution6 sol6;

    //SAMPLE TEST CASE
    
    int W = 50;
    int wt[] = {10, 20, 30};
    int val[] = {60, 100, 120};
    int n = sizeof(wt)/sizeof(wt[0]);
    
    int max_val_1 = sol1.knapSack(W, wt, val, n);
    int max_val_2 = sol2.knapSack(W, wt, val, n);
    int max_val_3 = sol3.knapSack(W, wt, val, n);
    int max_val_4 = sol4.knapSack(W, wt, val, n);
    int max_val_5 = sol5.knapSack(W, wt, val, n);
    int max_val_6 = sol6.knapSack(W, wt, val, n);

    cout<<"ANSWERS FOR SAMPLE TEST CASES GIVEN:\n\n";
    
    cout << "Maximum value in the Knapsack through BRUTE FORCE RECURSION USING EXTRA VECTOR: " << max_val_1 << endl;
    cout << "Maximum value in the Knapsack through SIMPLE RECURSION: " << max_val_2 << endl;
    cout << "Maximum value in the Knapsack through MEMOIZATION: " << max_val_3 << endl;
    cout << "Maximum value in the Knapsack through TABULATION: " << max_val_4 << endl;
    cout << "Maximum value in the Knapsack through SPACE OPTIMIZED TABULATION (2 ARRAYS): " << max_val_5 << endl;
    cout << "Maximum value in the Knapsack through SPACE OPTIMIZED BEST TABULATION (1 ARRAY): " << max_val_6 << endl;

    cout<<"\n\nENTER VALUES FOR A USER INPUTTED SOLUTION!\n\n";
    
    int weight;

    cout<<"Enter number of Objects: ";
    cin>>n;

    cout<<"Enter weight (Capacity) of Knapsack: ";
    cin>>weight;

    cout<<"Enter Value and Weight of each object:\n ";

    int weights[1000000], values[1000000];

    for(int i = 0 ; i < n ; i++){
        cin>>values[i]>>weights[i];
    }

    Solution1 sol7;
    Solution2 sol8;
    Solution3 sol9;
    Solution4 sol10;
    Solution5 sol11;
    Solution6 sol12;
    
    int max_val_7 = sol7.knapSack(weight, weights, values, n);
    int max_val_8 = sol8.knapSack(weight, weights, values, n);
    int max_val_9 = sol9.knapSack(weight, weights, values, n);
    int max_val_10 = sol10.knapSack(weight, weights, values, n);
    int max_val_11 = sol11.knapSack(weight, weights, values, n);
    int max_val_12 = sol12.knapSack(weight, weights, values, n);

    cout<<"\n\nANSWERS FOR USER INPUTTED TEST CASE:\n\n";
    
    cout << "Maximum value in the Knapsack through BRUTE FORCE RECURSION USING EXTRA VECTOR: " << max_val_7 << endl;
    cout << "Maximum value in the Knapsack through SIMPLE RECURSION: " << max_val_8 << endl;
    cout << "Maximum value in the Knapsack through MEMOIZATION: " << max_val_9 << endl;
    cout << "Maximum value in the Knapsack through TABULATION: " << max_val_10 << endl;
    cout << "Maximum value in the Knapsack through SPACE OPTIMIZED TABULATION (2 ARRAYS): " << max_val_11 << endl;
    cout << "Maximum value in the Knapsack through SPACE OPTIMIZED BEST TABULATION (1 ARRAY): " << max_val_12 << endl;

  return 0;
}