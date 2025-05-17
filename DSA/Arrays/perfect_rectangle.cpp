
https://leetcode.com/problems/perfect-rectangle/description/


line sweep with using treeset for detecting intersection


class Solution {
public:
    struct Event {
        int tm; // x-axis position.
        int index; // pointer to the rectangle in the given array.
        bool isStart; // This is the left edge of the rectangle, otherwise, right edge.
        Event(int t, int id, bool isS): tm(t), index(id), isStart(isS) {}
    };

    bool isRectangleCover(vector<vector<int>>& rectangles) {
        auto compPQ = [&](Event* e1, Event* e2) {
            if(e1->tm != e2->tm) return e1->tm > e2->tm;
            else return rectangles[e1->index][0] > rectangles[e2->index][0];
        };
        priority_queue<Event*, vector<Event*>, decltype(compPQ)> pq(compPQ);
        int bottom = INT_MAX, roof = INT_MIN; 
        for(int i = 0; i < rectangles.size(); i++) {
            const vector<int>& rec = rectangles[i];
            Event* e1 = new Event(rec[0], i, true);
            Event* e2 = new Event(rec[2], i, false);
            pq.push(e1); pq.push(e2);
            bottom = min(bottom, rec[1]);
            roof = max(roof, rec[3]);
        }
        auto compSet = [&](Event* e1, Event* e2) {
            if(rectangles[e1->index][3] <= rectangles[e2->index][1]) return true;
            else return false;
        };
        set<Event*, decltype(compSet)> mySet(compSet);
        int yRange = 0;
        while(!pq.empty()) {
            int tm = pq.top()->tm;
            while(!pq.empty() && tm == pq.top()->tm) {
                Event* event = pq.top(); pq.pop();
                const vector<int>& rec = rectangles[event->index]; 
                if(event->isStart) {
                    auto rt = mySet.insert(event);
                    if(!rt.second) return false; // overlapping!!!
                    yRange += rec[3] - rec[1];
                }
                else {
                    mySet.erase(event);
                    yRange -= rec[3] - rec[1];
                }
            }
            if(!pq.empty() && yRange != roof - bottom) return false;
        }
        return true;
    }
};





public class Event implements Comparable<Event> {
	int time;
	int[] rect;

	public Event(int time, int[] rect) {
		this.time = time;
		this.rect = rect;
	}
	
	public int compareTo(Event that) {
		if (this.time != that.time) return this.time - that.time;
		else return this.rect[0] - that.rect[0];
	}
}

public boolean isRectangleCover(int[][] rectangles) {
	PriorityQueue<Event> pq = new PriorityQueue<Event> ();
        // border of y-intervals
	int[] border= {Integer.MAX_VALUE, Integer.MIN_VALUE};
	for (int[] rect : rectangles) {
		Event e1 = new Event(rect[0], rect);
		Event e2 = new Event(rect[2], rect);
		pq.add(e1);
		pq.add(e2);
		if (rect[1] < border[0]) border[0] = rect[1];
		if (rect[3] > border[1]) border[1] = rect[3];
	}
	TreeSet<int[]> set = new TreeSet<int[]> (new Comparator<int[]> () {
		@Override
                // if two y-intervals intersects, return 0
		public int compare (int[] rect1, int[] rect2) {
			if (rect1[3] <= rect2[1]) return -1;
			else if (rect2[3] <= rect1[1]) return 1;
			else return 0;
		}
	});
	int yRange = 0;
	while (!pq.isEmpty()) {
		int time = pq.peek().time;
		while (!pq.isEmpty() && pq.peek().time == time) {
			Event e = pq.poll();
			int[] rect = e.rect;
			if (time == rect[2]) {
				set.remove(rect);
				yRange -= rect[3] - rect[1];
			} else {
				if (!set.add(rect)) return false;
				yRange += rect[3] - rect[1];
			}
		}
                // check intervals' range
		if (!pq.isEmpty() && yRange != border[1] - border[0]) {
                        return false;
			//if (set.isEmpty()) return false;
			//if (yRange != border[1] - border[0]) return false;
		}
	}
	return true;
}