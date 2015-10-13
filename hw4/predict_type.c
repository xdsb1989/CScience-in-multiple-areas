struct decision_tree{//this is the tree structure
       char atribute[60];//every node has a attribute(word)
       char type;//this is the leaf,it is a type
       struct decision_tree *have_atribute;//the branch has the word
       struct decision_tree *without_atribute;//the branch hasn't the word
};
typedef struct decision_tree *tree_link;

void predict(struct decision_tree *root,word_link ptr)//get the current tree node, and the email words pointer
{
      word_link temp_ptr;
      temp_ptr=ptr;//save the start pointer in "temp_ptr"
      
      if (root->type=='H' || root->type=='S')//if the current root has a type,then copy the type to the start pointer
      {
            temp_ptr->type = root->type;
            return;
      }
      
      ptr=ptr->next_word;
      int flag=0;
      while (ptr!=NULL)
      {
            if (strcmp(ptr->word,root->atribute)==0)
            {
                  flag=1;
                  break;
            }
            ptr=ptr->next_word;
      }
      if (flag==1)
            predict(root->have_atribute,temp_ptr);//transfer the start pointer to the next level by using "temp_ptr"
      else if (flag==0)
            predict(root->without_atribute,temp_ptr);//transfer the start pointer to the next level by using "temp_ptr"
}
