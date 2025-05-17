vector<int> merge(Node *root1, Node *root2)
    {
       //Your code here
       
       stack<Node*> st1,st2;
       vector<int> ans;
       Node*curr1=root1,*curr2=root2;
       
       while(!st1.empty() || !st2.empty() || curr1 || curr2)
       {
           if(curr1!=NULL)
           {
               st1.push(curr1);
               curr1=curr1->left;
           }
           else if(curr2!=NULL)
           {
              st2.push(curr2);
              curr2=curr2->left;
           }
           else
           {
               int c1,c2;
               if(st1.empty())
               {
                    c1=INT_MAX;
               }
               else
               {
                   curr1=st1.top();
                    st1.pop();
                    c1=curr1->data;
               }
               
               if(st2.empty())
                    c2=INT_MAX;
               else{
                   
                   curr2=st2.top();
                   st2.pop();
                   c2=curr2->data;
               }
               
               
               
               if(c1<c2)
               {
                   ans.push_back(curr1->data);
                   curr1=curr1->right;
                   if(curr2)
                   st2.push(curr2);
                   curr2=NULL;
               }
               else 
               {
                   ans.push_back(curr2->data);
                   curr2=curr2->right;
                   if(curr1)
                   st1.push(curr1);
                   curr1=NULL;
               }
           }
       }
       
       return ans;
    }