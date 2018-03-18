#include <fstream>
#include <iostream>
#include <iomanip>
#include <math.h>
#define NMAX 6
//#define method 2

using namespace std;

double k[4][3];		//values for increment function
double f[100000][3];	//stores the values for f,f' and f'' at each step
double n;			//step size

void rk2(int i)
{
	k[0][0]=f[i-1][1];
	k[0][1]=f[i-1][2];
	k[0][2]=-f[i-1][0]*f[i-1][2];

	k[1][0]=f[i-1][1] + k[0][1]*n;
	k[1][1]=f[i-1][2] + k[0][2]*n;
	k[1][2]=-(f[i-1][0]+k[0][0]*n)*k[1][1];

	for(int j=0;j<3;j++)
		f[i][j]= f[i-1][j]+ (k[0][j]+k[1][j])*n/2;
}

void rk3(int i)
{
	//K1 values for f, f', f'', then K2, K3
	k[0][0]=f[i-1][1];
	k[0][1]=f[i-1][2];
	k[0][2]=-f[i-1][0]*f[i-1][2];

	k[1][0]=f[i-1][1] + k[0][1]*n/2;
	k[1][1]=f[i-1][2] + k[0][2]*n/2;
	k[1][2]=-(f[i-1][0]+k[0][0]*n/2)*k[1][1];

	k[2][0]=f[i-1][1] + (-k[0][1]+2*k[1][1])*n;
	k[2][1]=f[i-1][2] + (-k[0][2]+2*k[1][2])*n;
	k[2][2]=-(f[i-1][0]+(-k[0][0]+2*k[1][0])*n)*k[2][1];

	for(int j=0;j<3;j++)
		f[i][j]= f[i-1][j]+ (k[0][j]+4*k[1][j]+k[2][j])*n/6;
}


void rk4(int i)
{
	//K1 values for f, f', f'', then K2, K3, K4 similarly
	k[0][0]=f[i-1][1];
	k[0][1]=f[i-1][2];
	k[0][2]=-f[i-1][0]*f[i-1][2];

	k[1][0]=f[i-1][1] + k[0][1]*n/2;
	k[1][1]=f[i-1][2] + k[0][2]*n/2;
	k[1][2]=-(f[i-1][0]+k[0][0]*n/2)*k[1][1];

	k[2][0]=f[i-1][1] + k[1][1]*n/2;
	k[2][1]=f[i-1][2] + k[1][2]*n/2;
	k[2][2]=-(f[i-1][0]+k[1][0]*n/2)*k[2][1];

	k[3][0]=f[i-1][1] + k[2][1]*n;
	k[3][1]=f[i-1][2] + k[2][2]*n;
	k[3][2]=-(f[i-1][0]+k[2][0]*n)*k[3][1];

	for(int j=0;j<3;j++)
		f[i][j]= f[i-1][j]+ (k[0][j]+2*k[1][j]+2*k[2][j]+k[3][j])*n/6;

}

int main()
{
	int i=0;
	double abserr;
	int method;
	ofstream soln("/media/OS/Documents and Settings/Pazu/Documents/IITK/Assignments/Sci Comp/solutionnew.csv");
	cout<<"Blassius solver for f'''+f f'' = 0\n*******************************\n\n";

	/*Feeding the initial values*/
	f[i][0]=f[i][1]=0;
	f[i][2]=0.4696;

	cout<<"Input the step size:";
	cin>>n;

	rep:
	cout<<"\nMethod RK2,RK3, or RK4?";
	cin>>method;

	double newstep=n;

	do
	{
		n=newstep;
		switch(method)
		{
		case 2:	for(i=1;ceil(i*n) <= NMAX; i++)
						rk2(i);
				break;
		case 3:	for(i=1;ceil(i*n) <= NMAX; i++)
						rk3(i);
				break;
		case 4:	for(i=1;ceil(i*n) <= NMAX; i++)
							rk4(i);
				break;
		default:	cout<<"\nwrong choice";
				goto rep;
		}
		i=6/n-1;
		abserr=log(fabs(f[i][0]-4.78322)/4.78322);
		break;
		newstep=n*0.9;
		cout<<"\n"<<n<<"\t"<<abserr;;
	//	cin.get();
	}while(abserr>=-6);


   /*Display solution*/
	cout<<setw(12)<<setiosflags(ios::left)<<"\n\nη\t"<<"f\t"<<"f\'\t"<<"f\'\'\n";
	soln<<"η,f,f\',f\'\',\n";
	for(i=0;i*n<=NMAX;i++)
		{
			cout<<setprecision(8)<<setw(12)<<setiosflags(ios::left)
				<<i*n<<'\t'<<f[i][0]<<'\t'<<f[i][1]<<'\t'<<f[i][2]<<'\n';
			soln<<setprecision(8)<<i*n<<','<<f[i][0]<<','<<f[i][1]<<','<<f[i][2]<<",\n";
		}

	cout<<"\nLog Relative error = "<<abserr<<"x10^-5";//log error"<<log(abserr);
	cout<<"\nRK method order "<<method<<"\nStep size adopted= "<<n;
	cin.get();

	return 0;

}
