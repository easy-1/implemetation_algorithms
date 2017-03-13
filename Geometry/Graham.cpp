//Graham scan for finding Convex Hull
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Point {
    int x;
    int y;
    int idx;
};
Point initial;
int direction(Point i, Point j, Point k) {
    return (k.x-i.x)*(j.y-i.y) - (j.x-i.x)*(k.y-i.y);
}
bool cmp(const Point &a, const Point &b) {
    int d = direction(initial, a, b);
    if(d < 0) return true;
    return false;
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
    int yMin = points[0].y, min = 0;
    for(int i = 1; i < n; i++) {
        if(yMin > points[i].y) {
            yMin = points[i].y;
            min = i;
        } else if(yMin == points[i].y && points[min].x > points[i].x) {
            yMin = points[i].y;
            min = i;
        }
    }
    //swap points[0] and points[min]
    Point temp = points[0];
    points[0] = points[min];
    points[min] = temp;

    initial = points[0];
    cout<<"Bottom most point: "<<initial.idx<<" ("<<initial.x<<", "<<initial.y<<")\n";

    sort(points.begin()+1, points.end(), cmp);
    /*
    cout<<"Anti-clockwise order:-\n";
    for(int i = 1; i < n; i++) {
        cout<<points[i].idx<<" ";
    }*/

    vector<Point> hull(n+1);
    hull[0] = points[0];
    hull[1] = points[1];
    hull[2] = points[2];
    int top = 2;         //top pointer for using vector as a stack
    for(int i = 3; i < n; i++) {
        while(direction(hull[top-1], hull[top], points[i]) >= 0) { //remove that equality to include all points that lie on the hull.
            //pop from stack
            top--;
        }
        //now push into stack
        hull[++top] = points[i];
    }
    hull[++top] = initial;   //push initial point to complete the hull
    hull.shrink_to_fit();
    //hull.resize(top+1);
    cout<<"Hull points in counter clockwise order:-\n";
    for(int i = 0; i <= top; ++i) {
        cout<<hull[i].idx<<" ("<<hull[i].x<<", "<<hull[i].y<<")\n";
    }
    return 0;
}
