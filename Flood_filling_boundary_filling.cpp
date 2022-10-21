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

void draw_polygon( vector<PT> polygon)
{
    int n=polygon.size();
    int color;
    for(int i=0 ; i<n ; i++)
    {
        if(i%3==0)
        {
            color=YELLOW;
        }
        else if(i%2==0)
        {
            color=WHITE;
        }
        else
        {
            color=GREEN;
        }
        line_draw_DDA (polygon[i], polygon[(i+1)%n],color);
    }
}

void draw_polygon_for_boundary_filling( vector<PT> polygon)
{
    int n=polygon.size();
    for(int i=0 ; i<n ; i++)
    {
        line_draw_DDA (polygon[i], polygon[(i+1)%n],YELLOW);
    }
}

void Boundary_Filling(PT p,int color,int boundary_color)
{
    PT p1=convert_pixel(p);
    int current_color=getpixel(p1.x,p1.y);
    if(current_color==boundary_color||current_color==color)
    {
        return;
    }
    draw_pixel(p,color);
    Boundary_Filling(PT(p.x,p.y+1), color, boundary_color);
    Boundary_Filling(PT(p.x,p.y-1), color, boundary_color);
    Boundary_Filling(PT(p.x+1,p.y), color, boundary_color);
    Boundary_Filling(PT(p.x-1,p.y), color, boundary_color);
}
void FloodFill(PT p, int fill_color)
{
    PT p1 = convert_pixel(p);
    int current_color = getpixel(p1.x, p1.y);
    if(current_color !=0)
    {
        return;
    }

    draw_pixel(p, fill_color);

    FloodFill(PT(p.x,p.y-1), fill_color);
    FloodFill(PT(p.x,p.y+1), fill_color);
    FloodFill(PT(p.x-1,p.y), fill_color);
    FloodFill(PT(p.x+1,p.y), fill_color);
}
int main()
{
    initwindow(window_w, window_h);
    //draw_axis();

    /**Uncomment single portion at a time */

    /**Boundary filling algorithm**/

    vector<PT> polygon ;
    polygon.push_back(PT(100,100));
    polygon.push_back(PT(0,50));
    polygon.push_back(PT(-100,100));
    polygon.push_back(PT(-50,0));
    polygon.push_back(PT(-100,-100));
    polygon.push_back(PT(0,-50));
    polygon.push_back(PT(100,-100));
    polygon.push_back(PT(50,0));
    draw_polygon_for_boundary_filling(polygon);
    Boundary_Filling(PT(10, 10), YELLOW, RED);

    /**Flood filling algorithm**/
    /**Comment 178th line/draw_axis(); for this portion**/
    /*vector<PT> polygon ;
    polygon.push_back(PT(100,100));
    polygon.push_back(PT(0,50));
    polygon.push_back(PT(-100,100));
    polygon.push_back(PT(-50,0));
    polygon.push_back(PT(-100,-100));
    polygon.push_back(PT(0,-50));
    polygon.push_back(PT(100,-100));
    polygon.push_back(PT(50,0));
    draw_polygon(polygon);
    FloodFill(PT(10, 10),RED);*/

    getchar();
    return 0;
}

