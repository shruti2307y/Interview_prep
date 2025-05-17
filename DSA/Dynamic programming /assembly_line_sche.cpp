
The above recursion exhibits overlapping sub-problems. There are two ways to reach station S1, j: 

From station S1, j-1
From station S2, j-1
So, to find the minimum time to leave station S1, j the minimum time to leave the previous two stations must be calculated(as explained in above recursion).

Similarly, there are two ways to reach station S2, j: 

From station S2, j-1
From station S1, j-1



int carAssembly(int a[][NUM_STATION],
                int t[][NUM_STATION],
                int *e, int *x)
{
    int T1[NUM_STATION], T2[NUM_STATION], i;
 
    // time taken to leave first station in line 1
    T1[0] = e[0] + a[0][0];
     
    // time taken to leave first station in line 2
    T2[0] = e[1] + a[1][0];
 
    // Fill tables T1[] and T2[] using the
    // above given recursive relations
    for (i = 1; i < NUM_STATION; ++i)
    {
        T1[i] = min(T1[i - 1] + a[0][i],
                    T2[i - 1] + t[1][i] + a[0][i]);
        T2[i] = min(T2[i - 1] + a[1][i],
                    T1[i - 1] + t[0][i] + a[1][i]);
    }
 
    // Consider exit times and return minimum
    return min(T1[NUM_STATION - 1] + x[0],
               T2[NUM_STATION - 1] + x[1]);
}