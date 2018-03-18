#include<iostream.h>
#include<conio.h>
#include<math.h>
struct gear
{ int n;
  float z,ze,d,y,sig;
}g,p;
float cal(float power, gear g,float bang)
{ float lhs,rhs,m,cw;
  cout<<"\nEnter wear and lubrication factor:";
  cin>>cw;
  for(m=0;m<10;m=m+.01)
  {  lhs=1000*power/(3.14*g.z*m*g.n/60000);
     rhs=g.sig*(4.58/(4.58+3.142*g.z*m*g.n/60000))*(1.15*3.14*m/tan(bang))*g.y*3.142*m*cos(bang)/cw;
     cout<<m<<"\t"<<lhs<<"\t"<<rhs<<endl;
     if(fabs(lhs-rhs)<10)
       break;
  }
  return m;
}
void main()

{ float gr,ft,fw,fd,fs,power,bang,pang,a,zmin,m,mn,b,x;
  int cho=0;
  cout<<"\nEnter power:";
  cin>>power;
  cout<<"\Enter speed of gear & pinion:";
  cin>>g.n>>p.n;
  cout<<"\nEnter allowable static stress of gear and pinion in n/mm2:";
  cin>>g.sig>>p.sig;
  gr=(p.n/g.n);
  cout<<"\nEnter helix angle:";
  cin>>bang;
  cout<<"\n1.14.5 deg form\n2 20 deg full depth \n3 20 deg stub \n enter choice:";
  cin>>cho;
  switch (cho)
  {case 1:
       {  pang=14.5;
	  a=.8;
	  zmin=12;
       }
   case 2:
       {  pang=20;
	  a=1;
	  zmin=18;
       }
   case 3:
       {  pang=20;
	  a=1;
	  zmin=14;
       }
   default:cout<<"\nwrong choice!!!!!!!!!!!!!";
  }
  p.z=(2*a/gr)/(sqrt(1+((1/gr)+2)/gr*pow(sin(pang),2)-1));
  if(p.z<zmin)
  { p.z=zmin;
  }
  else
  { cout<<"\nEnter the roundoff value:";
    cin>>p.z;
  }
  g.z=p.z*gr;
  cout<<"\nequivalent no.of teeth of gear is "<<(g.z/pow(cos(bang),3))<<"\nequivalent no.of teeth of pinion is"<<(p.z/pow(cos(bang),3));
  cout<<"\nenter corresponding form factor of gear and pinion:";
  cin>>g.y>>p.y;
  if((g.sig*g.y)<(p.sig*p.y))
  { cout<<"\ngear is weaker hence lewis equation is applied to gear";
    m=cal(power,p,bang);
    x=0;
  }
  else
  { cout<<"\npinion is weaker hence lewis equation is applied to pinion";
    m=cal(power,g,bang);
    x=1;
  }
  mn=m*cos(bang);
  cout<<"\nequivalent module is "<<mn<<"\nplease standardise equivalent module";
  cin>>mn;
  m=mn/cos(bang);
  cout<<"\n corresponding module is "<<m;


  // checking of loads
  loadchecking:
  float v,c;
  b=1.15*3.14*mn/10*sin(bang);
  v=3.14*g.n*m*g.n/60000;
  ft=(1000*power)/(v/9.81);
  cout<<"\n Enter value for dynamic factor ( table 12.12):";
  cin>>c;
  fd=ft+((20.67*v*(c*pow(cos(bang),2)+ft)*cos(bang))/((20.67*v)+sqrt(c*b*pow(cos(bang),2)+ft)));
  b=b*10;
  ft=ft*9.81;

  if(x==1)
  { fs=p.sig*b*3.14*p.y*mn;
  }
  else
  { fs=g.sig*b*3.14*g.y*mn;
  }

  cout<<"\nenter the load stress factor (table 12.6 & 12.17):";
  cin>>c;
  fw=(p.z*m*b*2*g.z*c)/((g.z+p.z)*pow(cos(bang),2));
  cout<<"\nfd="<<fd<<"\nfs="<<fs<<"\nfw="<<fw;
  if(fw>=fd && fs>=fd)
  { cout <<"\n design is safe";
  }
  else
  { cout <<"\ndesign is not safe\nenter higher equivalent module:";
    cin>>mn;
    m=mn/cos(bang);
    goto  loadchecking;
  }
  getch();
}








