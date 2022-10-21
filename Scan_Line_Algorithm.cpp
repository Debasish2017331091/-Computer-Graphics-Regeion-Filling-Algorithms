#include<bits/stdc++.h>
#include<windows.h>
#include<graphics.h>
using namespace std;

const int window_h=800,window_w=1000;

struct PT   ///Point Stracture
{
    double x,y;
    PT()
    {
    }
    PT(double a,double b)
    {
        x=a;
        y=b;
    }
    bool operator < (const PT &p) const{
        return x < p.x ;
    }
};

struct edge{
    double y_min, y_max, x_with_y_min, m_inv ;
    edge(){}

    edge(double a, double b,double c,double d){
        y_min = a;
        y_max = b;
        x_with_y_min = c;
        m_inv = d;
    }
    bool operator < (const edge &p) const{
        return y_min < p.y_min ;
    }

};
void draw_axis()///x,y axis drawing
{
    for(int i=0 ; i<=window_w ; i++)
    {
        delay(0.2);
        putpixel( i, (window_h/2), GREEN );
    }
    for(int i=0 ; i<=window_h ; i++)
    {
        putpixel( (window_w/2), i, GREEN);
    }
}

PT convert_pixel(PT p)///Point convert with respect to axis
{
    p.x+=(window_w/2);
    p.y=-p.y;
    p.y+=(window_h/2);
    return p;
}

void draw_pixel(PT p,int color) ///Pixel filling with color
{
    p=convert_pixel(p);
    putpixel( (int)(p.x+0.5), (int)(p.y+0.5), color );
}

void line_draw_DDA(PT p1,PT p2,int color) ///DDA algorithm for line draging
{
    double dx=abs(p2.x-p1.x);
    double dy=abs(p2.y-p1.y);
    if(p1.y==p2.y) ///horijontal line
    {
        if(p1.x>p2.x)
        {
            swap(p1,p2);
        }
        for(int i=p1.x ; i<=p2.x ; i++)
        {
            delay(0.2);
            draw_pixel(PT(i,p1.y),color);
        }
    }
    else if(p1.x==p2.x)  ///vertical line
    {
        if(p1.y>p2.y)
        {
            swap(p1,p2);
        }
        for(int i=p1.y ; i<=p2.y ; i++)
        {
            draw_pixel(PT(p1.x,i),color);
        }
    }
    else if(dx>dy)
    {
        if(p1.x>p2.x)
        {
            swap(p1,p2);
        }
        draw_pixel(p1,color);
        double xi=p1.x;
        double yi=p1.y;
        double m=(p2.y-p1.y)/(p2.x-p1.x);
        while(xi<p2.x)
        {
            xi+=1;
            yi+=(m);
            draw_pixel(PT(xi,yi),color);
        }
        draw_pixel(p2,color);
    }
    else
    {
        if(p1.y>p2.y)
        {
            swap(p1,p2);
        }
        draw_pixel(p1,YELLOW);
        double xi=p1.x;
        double yi=p1.y;
        int n=abs(p2.y-p1.y);
        double m=(p2.y-p1.y)/(p2.x-p1.x);
        for(int i=1 ; i<n ; i++)
        {
            xi+=(1/m);
            yi+=1;
            draw_pixel(PT(xi,yi),YELLOW);
        }
        draw_pixel(p2,YELLOW);

    }
}


void scan_line(vector<PT> points,int color){
    ///edge list
    vector<edge> edges;
    int n=points.size();
    double st=1e15 , en=-1e15 ;
    unordered_map <double, int> mp;
    for(int i=0 ; i<n ; i++){
        PT a = points[i];
        PT b = points[(i+1)%n];
        if(a.y==b.y) continue;
        edge temp;

        temp.y_min=min(a.y , b.y);
        temp.y_max=max(a.y , b.y);
        temp.x_with_y_min= a.y < b.y ? a.x : b.x ;
        temp.m_inv=(b.x-a.x)/(b.y-a.y);

        st= min(st,temp.y_min);
        en= max(en,temp.y_max);
        mp[temp.y_min]=1;
        edges.push_back(temp);
    }
    n=edges.size();
    ///sort edge list
    sort(edges.begin(), edges.end());
    ///loop on y
    for(double y=st ; y <= en ; y++){
        vector<PT> int_points;
        ///intersecting point calculation
        for(int i=0 ; i<n ; i++){
            if( y >= edges[i].y_min && y<=edges[i].y_max){
                PT tmp;
                tmp.x=edges[i].x_with_y_min;
                tmp.y=y;
                edges[i].x_with_y_min+=edges[i].m_inv;
                int_points.push_back(tmp);
            }
        }
        ///sort intersecting points
        sort(int_points.begin(),int_points.end());
        ///line draw
        for(int i=0 ; i<int_points.size()-1 ; i+=2){
            line_draw_DDA(int_points[i],int_points[i+1],WHITE);
        }
    }



}
int main()
{
    initwindow(window_w, window_h);
    //draw_axis();
    vector<PT> polygon ;
    polygon.push_back(PT(100,100));
    polygon.push_back(PT(0,50));
    polygon.push_back(PT(-100,100));
    polygon.push_back(PT(-50,0));
    polygon.push_back(PT(-100,-100));
    polygon.push_back(PT(0,-50));
    polygon.push_back(PT(100,-100));
    polygon.push_back(PT(50,0));
    scan_line(polygon,RED);
    getchar();
    return 0;
}

