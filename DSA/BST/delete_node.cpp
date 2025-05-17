 TreeNode* deleteNode(TreeNode* root, int key) {
        if(root) 
        {
            if(root->val>key)
            {
                root->left=deleteNode(root->left,key);
                return root;
            }
            else if(root->val<key)
            {
                root->right=deleteNode(root->right,key);
                return root;
            }
            else
            {
                if(root->left==nullptr)
                {
                    return root->right;
                }
                if(root->right==nullptr)
                {
                    return root->left;
                }

                TreeNode *curr=root->right,*par=root;

                while(curr->left!=nullptr)
                {
                    par=curr;
                    curr=curr->left;
                    
                }

                if(par==root)
                {
                    par->right=curr->right;
                }
                else
                {
                    par->left=curr->right;
                }
                
                root->val=curr->val;

                return root;

            }
        }
        return root;
    }   
    