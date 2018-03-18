/*
  Name: 
  Description: 
*/

#include<iostream.h>
#include<iomanip.h>
#include<conio.h>
#include<math.h>

using namespace std;

struct gear
{
       float z,N,D,sigma,y,E,endur;
};       

float zmin(float a, float g,float phi)
{
 float z;
 z=(2*a/g)/(sqrt(1+ ((1/g)+2)/g*pow(sin(phi),2))-1);         
 if(z<18 && phi==20)
         z=18;
 if(z<14 && phi==14.5)
         z=14;
 return z;        
}


float calcmod(float power, gear g)
{
      float lhs, rhs,m;
      
      for(m= 0; m<10; m=m+0.1)
      {     
            lhs=1000*power/(3.14*g.z*m*g.N/60000);        // ft from power                         
            rhs=g.sigma*( 3.05/(3.05+ 3.142*g.z*m*g.N/60000) )*10*m*m*3.142*g.y; //lewis eqn
            cout<<m<<'\t'<<lhs<<'\t'<<rhs<<endl;

            if(fabs(lhs-rhs) <10)
                             break;
      }
      
  return m;                                                    
}
       

void stdmodule(float &m)
{
     if(m<1) m=1;
     else if(m<1.25) m=1.25;
     else if(m<1.5) m=1.5;
     else if(m<2) m=2;
     else if(m<2.5) m=2.5;
     else if(m<3) m=3;
     else if(m<4) m=4;
     else if(m<5) m=5;
     else if(m<6) m=6;
     else if(m<8) m=8;
     else if(m<10) m=10;
     else if(m<12) m=12;
     else if(m<16) m=16;
     else if(m<20) m=20;
     else if(m<25) m=25;
     else if(m<32) m=32;
     else if(m<40) m=40;
     else if(m<50) m=50;
}
               


int main()
{/*
   //clrscr();
     gear g,p;
     float power,phi,m;
     int system=0;
     cout<<"Enter Power : ";
     cin>>power;
     cout<<"Enter speed of gear,pinion : ";
     cin>>g.N>>p.N;
     float G;
     G=p.N/g.N; 
     cout<<"Enter allowable static stress of gear and pinion material : ";
     cin>>g.sigma>>p.sigma;
     cout<<"Enter modulus of elasticity of gear and pinion material : ";
     cin>>g.E>>p.E;
     cout<<"Enter endurance limits of gear and pinion material : ";
     cin>>g.endur>>p.endur;
     
     
     cout<<"Enter pressure angle : ";
     cin>>phi;
     if(phi==20)
     {
      cout<<"Enter if:\n 1. Full depth\n 2. Stub system\n";
      cin>>system;
      cout<<endl<<system;
      if(system==1)
      {
                          p.z=zmin(1,G,phi);
                      g.z=(int)(G*p.z);
                      cout<<"\np.z="<<p.z<<"\ng.z="<<g.z<<"\n";
                      
                      g.y=0.154-0.912/g.z;
                      p.y=0.154-0.912/p.z;
                      cout<<"\np.y="<<p.y<<"\ng.y="<<g.y<<"\n";
                      
                      if((g.sigma*g.y)>(p.sigma*p.y))
                       {cout<<"p is weaker";
                       m=calcmod(power,p);}
                      else
                       {cout<<"g is weaker";
                       m=calcmod(power,g);}
      }
      else if(system==2)                                      
      {               p.z=zmin(0.8,G,phi);
                      g.z=G*p.z;
                      
                      g.y=0.175-0.95/g.z;
                      p.y=0.175-0.95/p.z;
                      
                      if((g.sigma*g.y)>(p.sigma*p.y))
                       {cout<<"p is weaker";
                       m=calcmod(power,p);}
                      else
                       {cout<<"g is weaker";
                       m=calcmod(power,g);}
      }
     }
     stdmodule(m);
     cout<<"Module = "<<m;
     
     g.D=g.z*m;
     p.D=p.z*m;
     
     /***********checking of loads***********
     checkloads:
     
     float ft,fd,fs,fw,v,b;
     float e,k3,c,K;
     v=3.142*g.z*m*g.N/600000;
     ft=1000*power/v;
     
     b=10*m;
     //error in action
     if(m<=4) e=0.0508;
     else if(m<=5) e=0.0555;
     else if(m<=6) e=0.0652;
     else if(m<=7) e=0.0712;
     else if(m<=8) e=0.0778;
     else if(m<=10) e=0.0891;
     else if(m<=12) e=0.0987;
     else if(m<=15) e=0.1080;
     else if(m<=20) e=0.1168;
     else           e=0.1217;
    
                
     switch(system)
     {
      case 1: k3=9; //full depth
      case 2: k3=8.7; //stub
     }
     c=e/(k3*(1/g.E + 1/p.E));              

     //dynamic load
     fd=ft+(20.67*v*(c*b/10+ft)/(20.67*v+sqrt(c*b/10+ft)));
     
     //wear load
     K=pow(p.endur,2)*sin(phi)*(1/g.E + 1/p.E)/1.4;
     fw=p.D*b*( 2*g.z/(g.z+p.z) )*K;
     
     //dynamic strength of gear
     fs=g.sigma*b*3.142*g.y*m;
     
     cout<<endl<<"Fd="<<fd<<endl;
     cout<<"Fs="<<fs<<endl;
     cout<<"Fw="<<fw<<endl;
     
     
     if(fw>=fd && fs>=fd)
               cout<<"\nthe design is safe";
     else
         {     cout<<"\nthe design is not safe";
               m++;
               stdmodule(m);
               cout<<"\t New module ="<<m;
               goto checkloads;
               
               }
    */           
              
    //Display gear proportions         
    cout<<"\n\n\n"<<setw(15)<<"GEAR"<<setw(10)<<"PINION"<<endl;
    cout<<"module"<<endl<<m
        <<"teeth"<<endl<<
        <<"speed"<<endl
        <<"pcd"<<endl;            
    
      
    getch();
return 0;               
}
    
     
     
     
     
     
