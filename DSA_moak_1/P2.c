#include<stdio.h>
#include<stdlib.h>
/* This is a program that builds the tools necessary for Huffman code. 

1. Write a program that will traverse a binary tree and when it encounters a leaf it should print the code corresponding to the leaf. 

 */
int test;

// Node definition of a linked list
struct nodeL{
  int val;
  struct nodeL *next;
};

//Node definition of a binary tree
struct node{
  int val;
  struct node *left;
  struct node *right;
};


// Functions related to Linked list
struct nodeL *getnodeL(int val){
  struct nodeL *temp;
  temp=(struct nodeL *)malloc(sizeof(*temp));
  temp->val=val;
  temp->next=NULL;
  return temp;
}

struct nodeL *addAtHead(struct nodeL *h, int val){
  struct nodeL *temp;
  temp=getnodeL(val);
  if(h==NULL) return temp;
  temp->next=h;
  return temp;
}

struct nodeL *deleteHead(struct nodeL *h,int val){
  struct nodeL *temp;
  if(h==NULL) return h;
  temp=h->next;
  free(h);
  return temp;
}

// Binary Tree Related Functions
struct node *getnode(int val){
  struct node *temp;
  temp=(struct node *)malloc(sizeof(*temp));
  temp->val=val;
  temp->left=NULL;
  temp->right=NULL;
  return temp;
}

struct node *insert(struct node *root, int val){
  struct node *temp,*curr;
  int move=1;
  temp=getnode(val);
  if(root==NULL) return temp;
  curr=root;
  while(move==1){
    if(curr->val<=val && curr->right!=NULL) {curr=curr->right; continue;}
    if(curr->val<=val && curr->right==NULL) {move=0; break;}
    if(curr->val> val && curr->left!=NULL ) {curr=curr->left; continue;}
    if(curr->val> val && curr->left==NULL) {move=0; break;}
  }
  if(curr->val<=val)curr->right=temp;
  else curr->left=temp;
  return root;
}


void preorder(struct node *root){
  if (root!=NULL){
    printf("%d ",root->val);
    preorder(root->left);
    preorder(root->right);
   }
}

// Do not change the part above.

void printRev(struct nodeL *h){
  // Write a function that prints the elemnts in reverse direction (i.e., tail to head).
  

}


void printCode(struct node *root, struct nodeL *l){
  // Write a program that will traverse the tree and when it encounters a leaf it should print the code corresponding to the leaf.
}

int main(){
  struct node *root;
  struct nodeL *h;
  int i;
  int A[]={10,2,34,12,67,9};

  root=NULL;
  
  preorder(root);
  for(i=0;i<6;i++) {
    root=insert(root, A[i]);
  }
  preorder(root);

  
  for(i=0;i<6;i++) h=addAtHead(h,A[i]);

  // printRev(h);  

  h=NULL;
  printCode(root,h);
}