//Author: Ashwin Vishnu  Aug 12,2005
/*
  Hi,
	Verion 2.0 of the QUAD is reinforced with added functionality.
  Changelog:
   -LOTS of comments for the curious-but-confused reader
   -diversion in the beginning of the program prompting for real coefficients.
   -i_coef() for dealing with complex coefficients.
   -substituting math.h with complex.h for program condensation and for
    enabling complex data type -> by complex().
   -use of real() and imag() functions with complex datatypes.

other features are retained
AIM: to make QUAD as reliable and user friendly as possible.
P.S: comments and suggestions are warmly welcomed.
*/

#include<iostream.h>
#include<conio.h>
#include<complex.h>

void i_sol(float D,int a,int b)       //function for real coeff-complex roots
{
 float x,y;           		      //real part, img part of the root
 D=abs(D);

 x=(-b)/(2*a);
 y=sqrt(D)/(2*a);

 cout<<"\n\n\t\aSolution: x= "<<x<<"+"<<y<<"i or "
			    <<x<<"-"<<y<<"i";  //Back to main() -> loop prompt
};

/* CAUTION: Cluttered up ahead. Read the comments to assist your course */


void i_coef()				//function for complex coeff.
{
 int a[2], b[2], c[2];                  //for inputed coeff
 complex az,bz,cz, x1,x2, Dz;           //az= a[0]+a[1]i ...  //x1,x2 = roots
 cout<<"\tStandard form: (a1+a2i)x^2 + (b1+b2i)x + (c1+c2i) = 0\n";
 cout<<"a1,a2? ";                       //inputting coeffs.
	cin>> a[0] >> a[1];
 cout<<"b1,b2? ";
	cin>> b[0] >> b[1];
 cout<<"c1,c2? ";
	cin>> c[0] >> c[1];

 az= complex (a[0], a[1]);                //conversion -> complex datatype
 bz= complex (b[0], b[1]);
 cz= complex (c[0], c[1]);

 Dz= sqrt (bz*bz-4*az*cz);                //discriminant (complex rvalue)

 x1= (-bz+ Dz)/(2*az);      //quad formula
 x2= (-bz- Dz)/(2*az);

 cout<<"\n\tSolutions are: ("<<          //to print in x+yi form rather than in (x,y)
	real(x1)<<" + "<<imag(x1)<<"i)"<<"  OR  ("<<
	real(x2)<<" + "<<imag(x2)<<"i)";
}


void main()
{
 int a,b,c;
 float x1,x2;
 float D;
 char prompt='Y';
 while(prompt =='Y' || prompt =='y') //loop @ "Do you want to continue"
 {
  clrscr();
  cout<<"Are the coefficients real? (Y/N) ";  //main diversion
  cin>>prompt;
  clrscr();

  if(prompt=='Y' || prompt=='y')      //double-use of prompt to save variables
  {                                   //actually, the main diversion is here
   cout<<"\t\tStandard form of a Quadratic equation: ax^2+bx+c=0";
   cout<<"\n"<<"a=";
	cin>>a;        //coeffs being inputted
   cout<<"b=";
	cin>>b;
   cout<<"c=";
	cin>>c;

   D=(b*b)-4*a*c;
   cout<<"\nDiscriminant= "<<D;
	if (D>=0)      //sub diversion -> real coeff. and real roots
	{
	 D=sqrt(D);
	 x1 = (-b+D)/(2*a);
	 x2 = (-b-D)/(2*a);
	 cout<<"\n\n\t\aSolution: x= "<<x1<<" or "<<x2;
	}

	else            //sub diversion -> real coeff. but complex roots
	{ i_sol(D,a,b);	};   //diverted to i_sol()
  }

  else       		//main diversion -> complex coeff func., i_sol()
  { i_coef(); };

  cout<<"\n\n\tDo you want to continue? (Y/N) ";
  cin>>prompt;
  }; 	     //end of while loop || consequence> prog termination or loop
}