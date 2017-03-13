//Jarvis March - Gift Wrapping Algorithm for finding Convex Hull
#include <iostream>
#include <vector>
using namespace std;
struct Point {
    int x;
    int y;
    int idx;
};
//direction function returns positive value when k is clockwise to j with i as the center point
int direction(Point i, Point j, Point k) {
    return (k.x-i.x)*(j.y-i.y) - (j.x-i.x)*(k.y-i.y);
}
int main() {
    int n;
    cout<<"Enter number of points: ";
    cin>>n;
    vector<Point> points(n);
    cout<<"Enter x and then y:-\n";
    for(int i = 0; i < n; i++) {
        cin>>points[i].x>>points[i].y;
        points[i].idx = i+1;
    }
    //Finding bottom most point, breaking tie by left most point
    Point initial = points[0];
    for(int i = 1; i < n; i++) {
        if(initial.y > points[i].y) {
            initial = points[i];
        } else if(initial.y == points[i].y && initial.x > points[i].x) {
            initial = points[i];
        }
    }
    cout<<"Bottom most point: "<<initial.idx<<" ("<<initial.x<<", "<<initial.y<<")\n";
    vector<Point> hull;
    hull.push_back(initial);
    Point p = initial;
    do {
        //Find the most clockwise point
        Point q = points[0];
        if(q.idx == p.idx) {
            q = points[1];
        }
        for(int i = 1; i < n; i++) {
            if(p.idx == points[i].idx) {
                continue;
            }
            int d = direction(p, q, points[i]);
            if(d > 0) { //clockwise
                q = points[i];
            } else if(d == 0) { //collinear
                //check the distance and choose the minimum one
                int d1 = (p.y - q.y)*(p.y - q.y) + (p.x - q.x)*(p.x - q.x);
                int d2 = (p.y - points[i].y)*(p.y - points[i].y) + (p.x - points[i].x)*(p.x - points[i].x);
                q = d1 < d2 ? q: points[i];
            }
        }
        hull.push_back(q);
        p = q;
    } while(hull.back().idx != initial.idx);
    cout<<"Hull points in counter clockwise order:-\n";
    for(vector<Point>::iterator it = hull.begin(); it != hull.end(); ++it) {
        Point z = *(it);
        cout<<z.idx<<" ("<<z.x<<", "<<z.y<<")\n";
    }
    return 0;
}
