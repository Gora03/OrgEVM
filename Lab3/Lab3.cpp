#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <stdio.h>
const double PI = 3.141592653589793;
const int scalex = 20;
const int scaley = 34;

double x1=PI/2;
double x2=5*PI;

double f(double x);

int main()
{
    int graph_driver,graph_mode,graph_error_code;
    char text[5];
    double current_x=x1;
    double current_y=f(x1);
    double prev_x=current_x,prev_y=current_y;
    double max_y=current_y;
    double im_x=0;
    graph_driver=DETECT;
    initgraph(&graph_driver,&graph_mode,"C:\\TurboC3\\BGI");
    graph_error_code=graphresult();
    if(graph_error_code != grOk)
    {
        cputs(grapherrormsg(graph_error_code));
        return 255;
    }

    double cur_x=getmaxx()/8;
    double cur_y=getmaxy()/2;
    setviewport(cur_x,cur_y,getmaxx(),getmaxy(),0);

    line(0,-getmaxy(),0,180);
    line(0,0,getmaxx(),0);
    settextstyle(0,HORIZ_DIR,0);
    settextjustify(LEFT_TEXT,TOP_TEXT);
    outtextxy(-10,10,"0");
    for(int i=1;i<=30;i+=1)
    {
        sprintf(text,"%d",i);
        line(i*scalex,-2,i*scalex,2);
        outtextxy(i*scalex,10,text);
    }
    for(int j=-2;j<3;j++)
    {
        
        if(j==0)
        {
             sprintf(text," ");
        }
        else
        {
            sprintf(text,"%d",j);
            line(-2,-2*j*scaley,2,-2*j*scaley);
        }
        outtextxy(-20,-2*j*scaley,text);
    }
    setlinestyle(1,1,1);
    line(0,-2*current_y*scaley,current_x*scalex,-scaley*2*current_y);
    line(current_x*scalex,0,current_x*scalex,-scaley*2*current_y);
    putpixel(current_x*scalex,0,4);
    putpixel(0,-current_y*scaley*2,4);
    setlinestyle(0,1,1);
    while(im_x<27)
    {
        if(im_x<x1||im_x>x2)
        {
            setcolor(WHITE);
            line(scalex*im_x,-f(im_x)*scaley*2,scalex*(im_x+0.0001),-f(im_x+0.0001)*scaley*2);
        }
        else
        {
            setcolor(RED);
            current_x+=0.0001;
            current_y=f(current_x);
            line(scalex*prev_x,-prev_y*scaley*2,scalex*current_x,-current_y*scaley*2);
            prev_x=current_x;
            prev_y=current_y;
            if(current_y>max_y) max_y=current_y;
        }
        im_x+=0.0001;
    }
    setlinestyle(1,1,1);
    line(0,-2*current_y*scaley,current_x*scalex,-scaley*2*current_y);
    line(current_x*scalex,0,current_x*scalex,-scaley*2*current_y);
    putpixel(0,-2*current_y*scaley,4);
    putpixel(current_x*scalex,0,4);
    setcolor(RED);
    setlinestyle(0,1,3);
    rectangle(75,75,170,100);
    setcolor(WHITE);
    setlinestyle(0,1,1);
    sprintf(text,"%.2f",max_y);
    settextjustify(LEFT_TEXT,TOP_TEXT);
    outtextxy(85,80,"Max value: ");
    outtextxy(85,90,text);
    getch();
    closegraph();
    return 0;
}
double f(double x){
    return pow(sin(x),2)+pow(cos(x),3);
}
