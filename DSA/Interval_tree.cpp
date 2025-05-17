struct Interval{
    int low,high;
};

struct ITNode{
    Interval *i;
    int max;
    ITNode *left, *right;
};


class MyCalendar {
public:
    
    ITNode *root;
    ITNode * newNode(Interval i)
    {
        ITNode *temp = new ITNode;
        temp->i = new Interval(i);
        temp->max = i.high;
        temp->left = temp->right = NULL;
        return temp;
    }
    MyCalendar() {
        root=nullptr;
    }
    
    bool book(int start, int end) {
        
        Interval x={start,end};

        if(overlapsearch(root,x))
            return false;
        else 
        {
            root=insert(root,x);
            return true;
        }
    }
    bool doOVerlap(Interval i1, Interval i2)
    {
        if (i1.low < i2.high && i2.low < i1.high)
            return true;
        return false;
    }
    bool overlapsearch(ITNode *root, Interval i)
    {
        if(root==nullptr)
            return false;
        if(doOVerlap(*(root->i),i))
            return true;
        

        if(root->left !=nullptr && root->left->max>=i.low)
            return overlapsearch(root->left,i);
        
        return overlapsearch(root->right,i);
        
    }
    ITNode *insert(ITNode *root,Interval i)
    {
        if(root==nullptr)
        {
            return newNode(i);
        }
        
        int l=root->i->low;

        if(i.low<l)
        {
            root->left=insert(root->left,i);
        }
        else
            root->right=insert(root->right,i);
        
        if(root->max<i.high)
        {
            root->max=i.high;
        }

        

        return root;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
