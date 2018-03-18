#include<iostream.h>
#include<conio.h>
#include<math.h>
#include<complex.h>

void i_sol(float D,int a,int b)       //function for complex roots
{
 float x,y;           		      //real part, img part
 D=abs(D);

 x=(-b)/(2*a);
 y=sqrt(D)/(2*a);

 cout<<"\n\n\tSolution: x= "<<x<<"+"<<y<<"i or "
			    <<x<<"-"<<y<<"i";
};


void main()
{
 int a,b,c;
 float x1,x2;
 float D;
 char p='Y';
 while(p=='Y'||p=='y')
 {
  clrscr();
  cout<<"\t\tStandard form of a Quadratic equation: ax^2+bx+c=0";
  cout<<"\n"<<"a=";
  cin>>a;
  cout<<"b=";
  cin>>b;
  cout<<"c=";
  cin>>c;

  D=(b*b)-4*a*c;
  cout<<"\nDiscriminant= "<<D;
  if (D>=0)
	{
	 D=sqrt(D);
	 x1 = (-b+D)/(2*a);
	 x2 = (-b-D)/(2*a);
	 cout<<"\n\n\tSolution: x= "<<x1<<" or "<<x2;
	}
  else
	{
	 i_sol(D,a,b);
	};
  cout<<"\n\n\tDo you want to continue?(Y/N) ";
  cin>>p;
  };
}