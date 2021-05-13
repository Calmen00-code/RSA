#include<stdio.h>
#include<stdlib.h>
#include<ctime>
#include<bits/stdc++.h>
using namespace std;
  
// function to check Lehmann's test
int lehmann(int n, int t)
{
  
    // generating a random base less than n
    int a = 2 + (rand() % (n - 1));
  
    // calculating exponent
    int e = (n - 1) / 2;
  
    // iterate to check for different base values 
    // for given number of tries 't'
    while(t > 0)
    {
  
        // calculating final value using formula
        int result =((int)(pow(a, e)))% n;
  
        //if not equal, try for different base
        if((result % n) == 1 || (result % n) == (n - 1)) 
        {
            a = 2 + (rand() % (n - 1));
            t -= 1;
        }
  
        // else return negative
        else
            return -1;
    }
  
    // return positive after attempting
    return 1;
}
  
// Driver code
int main()
{
    int n = 3 ; // number to be tested
    int t = 10 ; // number of tries
  
    // if n is 2, it is prime
    if(n == 2)
    cout << "2 is Prime.";
  
    // if even, it is composite
    if(n % 2 == 0)
        cout << n << " is Composite";
  
    // if odd, check
    else
    {
        int flag = lehmann(n, t);
      
        if(flag ==1)
            cout << n << " may be Prime.";
      
        else
            cout << n << " is Composite.";
    } 
}
  
// This code is contibuted by chitranayal
