// https://www.youtube.com/watch?v=oib-XsjFa-M&list=LL&index=1
// https://cp-algorithms.com/graph/lca_binary_lifting.html

#include <bits/stdc++.h>
typedef long long int lli;
#define rep(i, n) for(int i = 0; i < n; i++)
#define vi vector<int>
using namespace std;

map<int, vi> up;
vi depth;
vi tin;
vi tout;
int x = 0, timer = 0;

struct node{

    int data;
    node* left, *right, *parent;

    node(int n, node* p){
        this->data = n;
        this->left = NULL;
        this->right = NULL;
        this->parent = p;
    }
};

void dfs(node* root){

    if(root == NULL)
        return;

    up[root->data].resize(x);

    if(root->parent == NULL){
        up[root->data][0] = 0;
        depth[root->data] = 0;
    }
    else{    
        up[root->data][0] = root->parent->data;
        depth[root->data] = depth[root->parent->data]+1;
    }

    for(int i = 1; i < x; i++){
        up[root->data][i] = up[ up[root->data][i-1] ][i-1];
    }

    tin[root->data] = ++timer;
    dfs(root->left);
    dfs(root->right);
    tout[root->data] = ++timer;;

}

int kthAncestor(int n, int k){

    if(depth[n] < k)
        return -1;

    rep(j, x){
        if(1 << j & k){
            n = up[n][j];
        }
    }

    return n;

}

bool isAncestor(int anc, int child){

    return (tin[anc] <= tin[child] && tout[anc] >= tout[child]);
}

int lca(int a, int b){

    if(isAncestor(a, b))
        return a;
    else if(isAncestor(b, a))
        return b;
    else{
        for(int i = x-1; i >= 0; i--){
            if(!isAncestor(up[a][i], b))
                a = up[a][i];
        }
    }

    return up[a][0];

}

void inorder(node* root){

    if(root == NULL)
        return;

    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}

int main(){

    int n;
    cin>>n;

    while(1 << x <= n){
        x++;
    }

    cout<<x<<endl;

    depth.resize(n);
    tin.resize(n);
    tout.resize(n);

    node* root = new node(0, NULL);
    root->left = new node(1, root);
    root->right = new node(5, root);
    root->left->left = new node(2, root->left);
    root->left->right = new node(4, root->left);
    root->left->right->left = new node(7, root->left->right);
    root->left->right->left->left = new node(3, root->left->right->left);
    root->left->right->left->right = new node(8, root->left->right->left);
    root->left->right->left->right->left = new node(9, root->left->right->left->right);
    root->left->right->left->right->left->left = new node(10, root->left->right->left->right->left);
    root->right->left = new node(6, root->right);

    inorder(root);
    cout<<endl;

    dfs(root);

    rep(i, n){
        rep(j, x){
            cout<<up[i][j]<<" ";
        }
        cout<<endl;
    }

    // for(int i : tin)
    //     cout<<i<<" ";
    // cout<<endl;

    // for(int i : tout)
    //     cout<<i<<" ";
    // cout<<endl;

    // int numb, k;
    // cin>>numb>>k;

    // cout<<kthAncestor(numb, k)<<endl;

    int a, b;
    cin>>a>>b;

    cout<<lca(a, b);
}