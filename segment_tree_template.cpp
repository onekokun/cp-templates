#include<bits/stdc++.h>
using namespace std;
# define SIZE 100005
int a[SIZE], seg[4 * SIZE], lazy[4 * SIZE];

void buildmax(int ind, int low, int high) {
    if(low == high) {
        seg[ind] = a[low];
        return;
    }
    int mid = (low + high)/2;
    buildmax(2*ind+1, low, mid);
    buildmax(2*ind+2, mid+1, high);
    seg[ind] = max(seg[2*ind+1], seg[2*ind+2]);
}
void buildmin(int ind, int low, int high) {
    if(low == high) {
        seg[ind] = a[low];
        return;
    }
    int mid = (low + high)/2;
    buildmin(2*ind+1, low, mid);
    buildmin(2*ind+2, mid+1, high);
    seg[ind] = min(seg[2*ind+1], seg[2*ind+2]);
}
void buildrange(int ind, int left, int right){
    if(left == right){
        seg[ind] = a[left];
        return ;
    }
    int mid = (left + right) / 2;
    
    buildrange(2*ind+1, left, mid);
    buildrange(2*ind+2, mid+1, right);
    
    seg[ind] = seg[2*ind+1] + seg[2*ind+2];
}
int maxquery(int ind, int low, int high, int l, int r) {
    if(low>=l && high<=r) {
        return seg[ind];
    }
    if(high<l || low>r) return INT_MIN;
    int mid = (low + high)/2;
    int left = maxquery(2*ind+1, low, mid, l, r);
    int right = maxquery(2*ind+2, mid+1, high, l, r);
    return max(left, right);
}
int minquery(int ind, int low, int high, int l, int r) {
    if(low>=l && high<=r) {
        return seg[ind];
    }
    if(high<l || low>r) return INT_MAX;
    int mid = (low + high)/2;
    int left = minquery(2*ind+1, low, mid, l, r);
    int right = minquery(2*ind+2, mid+1, high, l, r);
    return min(left, right);
}
void rangeUpdate(int ind, int left, int right, int l, int r, int val){
    if(lazy[ind]){
        seg[ind] = (right-left+1) * lazy[ind];
        if(left!=right){
            lazy[2*ind+1] += lazy[ind]; 
            lazy[2*ind+2] += lazy[ind]; 
        }
        lazy[ind] = 0;
    }

    if(r < left || right < l || left > right) return ;
    if(left>=l && right<=r){
        seg[ind] += (right-left+1)*val;
        if(left!=right){
            lazy[2*ind+1] += val;
            lazy[2*ind+2] += val;
        }
        return ;
    }

    int mid = (left + right) / 2;
    rangeUpdate(2*ind+1, left, mid, l, r, val);
    rangeUpdate(2*ind+2, mid+1, right, l, r, val);
    seg[ind] = seg[ind*2+1] + seg[ind*2+2];
}
int querySumLazy(int ind, int left, int right, int l, int r){
    if(lazy[ind]){
        seg[ind] += (right - left + 1) * lazy[ind];
        if(left!=right){
            lazy[2*ind+1] += lazy[ind];
            lazy[2*ind+2] += lazy[ind];
        }
        lazy[ind] = 0;
    }

    if(r < left || right < l || left > right) return 0;

    if(left >= l && right <= r){
        return seg[ind];
    }

    int mid = (right + left)/2;
    int leftSide = querySumLazy(2*ind+1, left, mid, l, r);
    int rightSide = querySumLazy(2*ind+2, mid+1, right, l, r);
    return leftSide + rightSide;
}
int main() {
    vector<int> nums{1,3,2,5,4};
    int n = nums.size();
    for(int i = 0; i < n; i++) a[i] = nums[i];
    // buildmin(0, 0, n-1);
    // buildmax(0, 0, n-1);
    // buildrange(0, 0, n-1);
    // rangeUpdate(0, 0, n-1, 1, 1, -1);
    // cout<<querySumLazy(0, 0, n-1, 0, 2);
    // cout<<minquery(0, 0, n-1, 1, 4);
    return 0;
}
