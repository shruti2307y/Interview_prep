class SegmentTree{
public:
    int n;
    vector<int> tree;
    SegmentTree(int nn) : n(nn){
        int size=(int)(ceil(log2(n)));
        size=(2*pow(2,size))-1;
        tree=vector<int>(size);
    }

    int max_value(){
        return tree[0];
    }

    int query(int l,int r)
    {
        return query_util(0,l,r,0,n-1);
    }

    int query_util(int i, int ql, int qr, int l, int r)
    {
        if(l>=ql && r<=qr)
            return tree[i];
        if(l>qr || r<ql)
            return INT_MIN;

        int m=(l+r)/2;

        return max(query_util(2*i+1,ql,qr,l,m),query_util(2*i+2,ql,qr,m+1,r));
    }

    void update(int i, int val)
    {
        update_util(0,i,val,0,n-1);
    }

    void update_util(int i, int pos, int val, int l, int r)
    {
        if(pos<l || pos>r)
            return ;
        if(l==r){
            tree[i]=max(val,tree[i]);
            return ;
        }

        int m=(l+r)/2;

        update_util(2*i+1,pos,val,l,m);
        update_util(2*i+2,pos,val,m+1,r);

        tree[i]=max(tree[i*2+1],tree[i*2+2]);
    }
};



class Solution {
public:
    int lengthOfLIS(vector<int>& nums, int k) {
        
       SegmentTree tree(1e5+1);
       for(int i: nums)
       {
           int lower=max(0,i-k);
           int cur=1+tree.query(lower,i-1);
           tree.update(i,cur);
       }

       return tree.max_value();
    }
};