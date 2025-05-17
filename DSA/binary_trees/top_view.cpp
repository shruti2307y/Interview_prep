vector<int> topView(Node *root)
    {
           //Your code here
          
          queue<pair<int,Node*>> st;
          st.push({0,root});
          int maxl=0,maxr=0;
          
          vector<int> l,r;
          pair<int,Node*> curr;
          r.push_back(root->data);
          int currLevel;
          Node *currNode;
          while(!st.empty())
          {
              curr=st.front();
              st.pop();
              currNode=curr.second;
              currLevel=curr.first;
              if(currLevel<maxl)
              {
                  l.push_back(currNode->data);
                  maxl=currLevel;
              }
              if(currLevel>maxr)
              {
                  r.push_back(currNode->data);
                  maxr=currLevel;
              }
              
              if(currNode->left)
              st.push({currLevel-1,currNode->left});
              
              if(currNode->right)
                st.push({currLevel+1,currNode->right});
          }
        
          reverse(l.begin(),l.end());
          
          l.insert(l.end(),r.begin(),r.end());
          
          return l;
    }