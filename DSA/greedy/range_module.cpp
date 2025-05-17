https://leetcode.com/problems/range-module/description/


class RangeModule {
public: 

    map<int,int> list;

    RangeModule() {
        
    }
    
    void addRange(int left, int right) {
        
        auto itr = list.upper_bound(left);

        if(list.empty())
        {
            list[left]=right;
            return ;
        }
        
        while(itr!=list.end() && itr->first<=right)
        {    
            right=max(itr->second,right);
            itr++;
            list.erase(prev(itr));
        }
        
        if(itr!=list.begin() && left<=(--itr)->second)
            itr->second=max(right,itr->second);
       else
            list[left]=right;
    }
    
    bool queryRange(int left, int right) {
        
       
        auto itr = list.upper_bound(left);
        if(itr==list.begin())
            return false;
        else
            return prev(itr)->second>=right;
        

    }
    
    void removeRange(int left, int right) {
        
        auto itr = list.lower_bound(left);
       int cutEnd=-1;

       while(itr!=list.end() && itr->first<right)
       {
           cutEnd=max(cutEnd,itr->second);
           itr++;
           list.erase(prev(itr));
       }

       if(itr!=list.begin() && left<(--itr)->second)
       {
           cutEnd=max(cutEnd,itr->second);
           itr->second=left;
       }

       if(right<cutEnd)
       {
           list[right]=cutEnd;
       }
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */