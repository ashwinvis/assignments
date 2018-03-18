#include <fstream>
#include <iostream>
#include <iomanip>
#include <math.h> 

using namespace std;

double y[10000][4];
double z[10000];
double f[10000][3];

//f''''-a1*f'''-a2*f''-a3*f'-a4*f=r
double a1=0,a2=3601,a3=0,a4=-3600;

double ycomp[4][4]={{0,1,0,0},
				   {a2,a1,1,0},
				   {-a3,0,a1,1},
				   {a4,0,0,a1}
				  };
			  
int w[]={0,0.5,0.5,1};
double dx;				   	

void rk_yz(int i)
{
	double ky[5][4];
	double kz[5];
	
	//k-> k1,k2,
	//p-> y1,y2...
	//q-> y1,y2..
	
	/*K values calculated using companion matrix*/
	/*for(int k=1; k<=4; k++)
		{
			for(int p=0;p<4;p++)
				{
					for(int q=0;q<4;q++)
						ky[k][p]+=y[i][q]*ycomp[p][q];
					ky[k][p]+=ky[k-1][p]*dx*w[k-1];
				}
		}
	*/
	
	ky[1][0]=y[i][1];
	ky[1][1]=3601*y[i][0]+y[i][2];
	ky[1][2]=y[i][3];
	ky[1][3]=-3600*y[i][0];
	
	ky[2][0]=y[i][1]+ky[1][1]*dx/2;
	ky[2][1]=3601*(y[i][0] + ky[1][0]*dx/2)+( y[i][2]+ky[1][2]*dx/2);
	ky[2][2]=y[i][3]+ky[1][3]*dx/2;
	ky[2][3]=-3600*(y[i][0]+ ky[1][0]*dx/2);
	
	ky[3][0]=y[i][1]+ky[2][1]*dx/2;
	ky[3][1]=3601*(y[i][0] + ky[2][0]*dx/2)+( y[i][2]+ky[2][2]*dx/2);
	ky[3][2]=y[i][3]+ky[2][3]*dx/2;
	ky[3][3]=-3600*(y[i][0]+ ky[2][0]*dx/2);
	
	ky[4][0]=y[i][1]+ky[3][1]*dx;
	ky[4][1]=3601*(y[i][0] + ky[3][0]*dx)+( y[i][2]+ky[3][2]*dx);
	ky[4][2]=y[i][3]+ky[3][3]*dx;
	ky[4][3]=-3600*(y[i][0]+ ky[3][0]*dx);
	
	for(int j=0;j<4; j++)
		y[i+1][j]=y[i][j]+ (ky[1][j]+2*ky[2][j]+2*ky[3][j]+ky[4][j])*dx/6;
	
	
	
	//k-> k1,k2,
	/*for(int k=1; k<=4; k++)
		kz[k]= ( 1-1800*pow((i*dx)+dx*w[k-1],2 ))*(y[i][0] + ky[k][0]*dx*w[k-1]);
	*/
	
	kz[1]= ( 1-1800*pow(i*dx,2 ))*(y[i][0]);
	kz[2]= ( 1-1800*pow((i+0.5)*dx,2 ))*(y[i][0] + ky[1][0]*dx/2);
	kz[3]= ( 1-1800*pow((i+0.5)*dx,2 ))*(y[i][0] + ky[2][0]*dx/2);
	kz[4]= ( 1-1800*pow((i+1)*dx,2 ))*(y[i][0]+ ky[3][0]*dx);
	
	z[i+1]=z[i] + (kz[1] +2*kz[2] +2*kz[3] +kz[4] )*dx/6;
		
}


void rk_f(int i)
{
	double kf[5][3];
	double fcomp[3][3]={{0,1,0},
				   {0,0,1},
				   {y[i][3]/y[i][0],-y[i][2]/y[i][0],y[i][1]/y[i][0]}
				  };
	double c[]={0,0,z[i]/y[i][0]};	
				  

	for(int x=1; x<=4; x++)
		for(int l=0;l<3;l++)
			{	
				kf[x][l]=0;
				for(int m=0;m<3; m++)
					kf[x][l]+= fcomp[l][m]*(f[i][m]+kf[x-1][m]*dx*w[x-1]) - c[m];
			}
	
		
	for(int j=0;j<3; j++)
		f[i-1][j]=f[i][j] - (kf[1][j]+2*kf[2][j]+2*kf[3][j]+kf[4][j])*dx/6;
}

int main()
{
	long int imax; //iterations required to march from 0 to 1
	
	int i=0;
	ofstream soln("CMMsolution.csv");
	cout<<"CMM Method\n*******************************\n\n";


	cout<<"Input the step size:";
	cin>>dx;
	imax=1/dx;
	
	//initial conditions
	y[0][0]=1;
	y[0][1]=60;
	y[0][2]=-1;
	y[0][3]=-60;
	
	z[0]=120;
	
	for(int i=0;i<imax ; i++)
		 rk_yz(i);
	
	f[imax][0]=1.5+sinh(1);
	f[imax][1]=1+cosh(1);
	f[imax][2]=1+sinh(1);

		 
	for(int i=imax;i>0 ; i--)
		 rk_f(i);
	
	for(i=0;i<=imax ;i++)
		{
			cout<<setprecision(4)<<setw(12)<<setiosflags(ios::left)
				<<i*dx<<'\t'<<y[i][0]<<'\t'<<y[i][1]<<'\t'<<y[i][2]<<'\t'<<y[i][3]<<'\t'<<z[i]<<'\n';
			soln<<setprecision(8)<<i*dx<<'\t'<<y[i][0]<<'\t'<<y[i][1]<<'\t'<<y[i][2]<<'\t'<<y[i][3]<<'\t'<<z[i]<<'\t'
				<<'\t'<<y[i][1]/y[i][0]<<'\t'<<y[i][2]/y[i][0]<<'\t'<<y[i][3]/y[i][0]<<'\t'<<z[i]/y[i][0]<<'\t'
				<<'\t'<<f[i][0]<<'\t'<<f[i][1]<<'\t'<<f[i][2]<<'\n';
		}
	
	return 0;
}
