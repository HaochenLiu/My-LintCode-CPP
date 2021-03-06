/*
360. Sliding Window Median
Given an array of n integer, and a moving window(size k), move the window at each iteration from the start of the array, find the median of the element inside the window at each moving. (If there are even numbers in the array, return the N/2-th number after sorting the element in the window. )
Have you met this question in a real interview?
Example
For array [1,2,7,8,5], moving window size k = 3. return [2,7,7]
At first the window is at the start of the array like this
[ | 1,2,7 | ,8,5] , return the median 2;
then the window move one step forward.
[1, | 2,7,8 | ,5], return the median 7;
then the window move one step forward again.
[1,2, | 7,8,5 | ], return the median 7;
Challenge
O(nlog(n)) time
*/

bool RemoveElemFromVector(vector<int>& v, int a) {
    int n = v.size();
    for(int i = 0; i < n; i++) {
        if(v[i] == a) {
            v.erase(v.begin() + i);
            return true;
        }
    }
    return false;
}

bool EditElemFromVector(vector<int>& v, int a, int b) {
    int n = v.size();
    for(int i = 0; i < n; i++) {
        if(v[i] == a) {
            v[i] = b;
            return true;
        }
    }
    return false;
}

class HHeapMin {
private:
    int A[5001];
    int __size;
    unordered_map<int, vector<int>> h;

public:
    HHeapMin() {
        h.clear();
        memset(A, 0, sizeof(A));
        __size = 0;
    }
	
    void check() {
        cout<<"size: "<<__size<<endl;
        cout<<"[";
        for(int i = 0; i < __size - 1; i++) {
            cout<<A[i]<<", ";
        }
        cout<<A[__size - 1]<<"]"<<endl;
    }
    
    int size() {
        return __size;
    }

    void push(int n) {
        h[n].push_back(__size);
        A[__size] = n;
        __size++;
        int i = __size - 1;
        while(i > 0) {
            int j = (i - 1) / 2;
            if(A[j] > A[i]) {
                EditElemFromVector(h[A[i]], i, j);
                EditElemFromVector(h[A[j]], j, i);
                swap(A[j], A[i]);
                i = j;
            } else {
                break;
            }
        }
        return;
    }
    
    int top() {
        return A[0];
    }
    
    void pop() {
        RemoveElemFromVector(h[A[0]], 0);
        EditElemFromVector(h[A[__size - 1]], __size - 1, 0);
        A[0] = A[__size - 1];
        __size--;
        int i = 0;
        while(2 * i + 1 < __size) {
            int minIdx = i;
            if(A[2 * i + 1] < A[minIdx]) {
                minIdx = 2 * i + 1;
            }
            if(2 * i + 2 < __size && A[2 * i + 2] < A[minIdx]) {
                minIdx = 2 * i + 2;
            }
            if(minIdx == i) {
                break;
            }
            EditElemFromVector(h[A[i]], i, minIdx);
            EditElemFromVector(h[A[minIdx]], minIdx, i);
            swap(A[i], A[minIdx]);
            i = minIdx;
        }
        return;
    }
    
    void erase(int n) {
        if(__size == 0) return;
        if(h[n].empty()) {
            return;
        }
        int i = h[n][0];
        if(A[__size - 1] == n) {
            RemoveElemFromVector(h[n], __size - 1);
            __size--;
            return;
        } else if(A[__size - 1] > n) {
            RemoveElemFromVector(h[A[i]], i);
            EditElemFromVector(h[A[__size - 1]],  __size - 1, i);
            A[i] = A[__size - 1];
            __size--;
            while(2 * i + 1 < __size) {
                int minIdx = i;
                if(A[2 * i + 1] < A[minIdx]) {
                    minIdx = 2 * i + 1;
                }
                if(2 * i + 2 < __size && A[2 * i + 2] < A[minIdx]) {
                    minIdx = 2 * i + 2;
                }
                if(minIdx == i) {
                    break;
                }
                EditElemFromVector(h[A[i]], i, minIdx);
                EditElemFromVector(h[A[minIdx]], minIdx, i);
                swap(A[i], A[minIdx]);
                i = minIdx;
            }
            return;
        } else {
            RemoveElemFromVector(h[A[i]], i);
            EditElemFromVector(h[A[__size - 1]],  __size - 1, i);
            A[i] = A[__size - 1];
            __size--;
            while(i > 0) {
                int j = (i - 1) / 2;
                if(A[j] > A[i]) {
                    EditElemFromVector(h[A[i]], i, j);
                    EditElemFromVector(h[A[j]], j, i);
                    swap(A[j], A[i]);
                    i = j;
                } else {
                    break;
                }
            }
            return; 
        }
    }
    
    bool find(int n) {
        if(__size == 0 || n < A[0]) return false;
        return (!h[n].empty());
    }
};

class HHeapMax {
private:
    int A[5001];
    int __size;
    unordered_map<int, vector<int>> h;

public:
    HHeapMax() {
        memset(A, 0, sizeof(A));
        __size = 0;
    }
	
    void check() {
        cout<<"size: "<<__size<<endl;
        cout<<"[";
        for(int i = 0; i < __size - 1; i++) {
            cout<<A[i]<<", ";
        }
        cout<<A[__size - 1]<<"]"<<endl;
    }
	
    int size() {
        return __size;
    }

    void push(int n) {
        h[n].push_back(__size);
        A[__size] = n;
        __size++;
        int i = __size - 1;
        while(i > 0) {
            int j = (i - 1) / 2;
            if(A[j] < A[i]) {
                EditElemFromVector(h[A[i]], i, j);
                EditElemFromVector(h[A[j]], j, i);
                swap(A[j], A[i]);
                i = j;
            } else {
                break;
            }
        }
        return;
    }
    
    int top() {
        return A[0];
    }

    void pop() {
        RemoveElemFromVector(h[A[0]], 0);
        EditElemFromVector(h[A[__size - 1]], __size - 1, 0);
        A[0] = A[__size - 1];
        __size--;
        int i = 0;
        while(2 * i + 1 < __size) {
            int maxIdx = i;
            if(A[2 * i + 1] > A[maxIdx]) {
                maxIdx = 2 * i + 1;
            }
            if(2 * i + 2 < __size && A[2 * i + 2] > A[maxIdx]) {
                maxIdx = 2 * i + 2;
            }
            if(maxIdx == i) {
                break;
            }
            EditElemFromVector(h[A[i]], i, maxIdx);
            EditElemFromVector(h[A[maxIdx]], maxIdx, i);
            swap(A[i], A[maxIdx]);
            i = maxIdx;
        }
        return;
    }

    void erase(int n) {
        if(__size == 0) return;
        if(h[n].empty()) {
            return;
        }
        int i = h[n][0];
        if(A[__size - 1] == n) {
            RemoveElemFromVector(h[n], __size - 1);
            __size--;
            return;
        } else if(A[__size - 1] < n) {
            RemoveElemFromVector(h[A[i]], i);
            EditElemFromVector(h[A[__size - 1]],  __size - 1, i);
            A[i] = A[__size - 1];
            __size--;
            while(2 * i + 1 < __size) {
                int maxIdx = i;
                if(A[2 * i + 1] > A[maxIdx]) {
                    maxIdx = 2 * i + 1;
                }
                if(2 * i + 2 < __size && A[2 * i + 2] > A[maxIdx]) {
                    maxIdx = 2 * i + 2;
                }
                if(maxIdx == i) {
                    break;
                }
                EditElemFromVector(h[A[i]], i, maxIdx);
                EditElemFromVector(h[A[maxIdx]], maxIdx, i);
                swap(A[i], A[maxIdx]);
                i = maxIdx;
            }
            return;
        } else {
            RemoveElemFromVector(h[A[i]], i);
            EditElemFromVector(h[A[__size - 1]],  __size - 1, i);
            A[i] = A[__size - 1];
            __size--;
            while(i > 0) {
                int j = (i - 1) / 2;
                if(A[j] < A[i]) {
                    EditElemFromVector(h[A[i]], i, j);
                    EditElemFromVector(h[A[j]], j, i);
                    swap(A[j], A[i]);
                    i = j;
                } else {
                    break;
                }
            }
            return; 
        }
    }
    
    bool find(int n) {
        if(__size == 0 || n < A[0]) return false;
        return (!h[n].empty());
    }
};

class Solution {
public:
    /**
     * @param nums: A list of integers.
     * @return: The median of the element inside the window at each moving
     */
    vector<int> medianSlidingWindow(vector<int> &nums, int k) {
        // write your code here
        HHeapMax small;
        HHeapMin large;
        vector<int> res;
        int n = nums.size();
        if(n < 1 || k < 1 || n < k) return res;
        if(k == 1) return nums;
        small.push(INT_MIN);
        large.push(INT_MAX);

        for(int i = 0; i < n; i++) {
            if(i >= k) {
                int toDelete = nums[i - k];
                if(large.find(toDelete)) {
                    large.erase(toDelete);
                    if(small.size() > large.size() + 1) {
                        large.push(small.top());
                        small.pop();
                    }
                } else {
                    small.erase(toDelete);
                    if(large.size() > small.size()) {
                        small.push(large.top());
                        large.pop();
                    }
                }
            }
            
            if(nums[i] <= small.top()) {
                small.push(nums[i]);
                if(small.size() > large.size() + 1) {
                    large.push(small.top());
                    small.pop();
                }
            } else {
                large.push(nums[i]);
                if(large.size() > small.size()) {
                    small.push(large.top());
                    large.pop();
                }
            }
            
            if(i >= k - 1) {
                res.push_back(small.top());
            }
        }
        return res;
    }
};
