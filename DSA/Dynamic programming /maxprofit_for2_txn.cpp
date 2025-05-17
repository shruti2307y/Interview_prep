
Efficient Solution. The idea is to store the maximum possible profit of every subarray and solve the problem in the following two phases.

1) Create a table profit[0..n-1] and initialize all values in it 0.
2) Traverse price[] from right to left and update profit[i] such that profit[i] stores maximum profit achievable from one transaction in subarray price[i..n-1]
3) Traverse price[] from left to right and update profit[i] such that profit[i] stores maximum profit such that profit[i] contains maximum achievable profit from two transactions in subarray price[0..i].
4) Return profit[n-1]

int maxProfit(vector<int>&price){
    //Write your code here..
    int n=price.size();
    vector<int> profit(n+1,0);
    
    int rm=price[n-1];
    
    int i=n-2;
    while(i>=0)
    {
        rm=max(price[i],rm);
        profit[i]=max(profit[i+1],rm-price[i]);
        i--;
    }
    
    rm=price[0];
    for(int i=0;i<n;i++)
    {
        profit[i]=max(profit[i-1],max(profit[i],profit[i+1]+price[i]-rm));
        rm=min(rm,price[i]);
    }
    
    return profit[n-1];
}