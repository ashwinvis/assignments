#include<iostream.h>
#include<conio.h>
void main()

{
 unsigned long int n;
 int i,mod;
 char prompt='y';

 while (prompt=='y' || prompt=='Y')
 {
  clrscr();
  cout<<"\t\t\t\tPRIME NUMBER TEST";
  cout<<"\n\nEnter Number :";
  cin>>n;
  for( i=2; i<=n/2 ; i++)
  {
   mod= n%i;
   if (mod==0)
   {
    cout<<"\nThe Number is NOT PRIME, divisible by "<<i;
    break;
   }
  }

  if (mod>0)
	cout<<"\nThe Number IS PRIME";

  cout<<"\n\nWanna Continue? (Y/N) ";
  cin>>prompt;
  }
}