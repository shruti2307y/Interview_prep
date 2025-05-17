https://leetcode.com/problems/find-median-from-data-stream/description/

So we maintain two heaps, one maxheap and other minheap;

maxheap will have lower half of numbers and minheap will have upper half;


class MedianFinder {
public:
    priority_queue<int> left_max_heap; // max heap
    priority_queue<int, vector<int>,greater<int>> right_min_heap; // min heap
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if(left_max_heap.empty() || num<left_max_heap.top()){
            left_max_heap.push(num);
        }else{
            right_min_heap.push(num);
        }
        //always maintain left max heap size >= right min heap
        if(abs((int)left_max_heap.size() - (int)right_min_heap.size()) > 1){
            right_min_heap.push(left_max_heap.top());
            left_max_heap.pop();
        }else if(left_max_heap.size()<right_min_heap.size()){
            left_max_heap.push(right_min_heap.top());
            right_min_heap.pop();
        }
    }
    
    double findMedian() {
        if(left_max_heap.size()==right_min_heap.size()){
            return (double)(left_max_heap.top()+right_min_heap.top())/2;
        }
        return left_max_heap.top();
    }
};
