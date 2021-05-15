import java.util.Random;
  
class GFG
{
  
    // function to check Lehmann's test 
    static int lehmann(int n, int t)
    {
      
        // create instance of Random class 
        Random rand = new Random(); 
          
        // generating a random base less than n 
        int a = rand.nextInt(n - 3) + 2;
      
        // calculating exponent 
        float e = (n - 1) / 2;
      
        // iterate to check for different base values 
        // for given number of tries 't' 
        while(t > 0)
        {
      
            // calculating final value using formula 
            int result = ((int)(Math.pow(a, e))) % n;
      
            // if not equal, try for different base 
            if((result % n) == 1 || (result % n) == (n - 1))
            {
                a = rand.nextInt(n - 3) + 2;
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
    public static void main (String[] args)
    {
    int n = 3; // number to be tested 
    int t = 10; // number of tries 
      
    // if n is 2, it is prime 
    if(n == 2)
        System.out.println(" 2 is Prime."); 
      
    // if even, it is composite 
    if(n % 2 == 0)
        System.out.println(n + " is Composite");
      
    // if odd, check 
    else
    {
        long flag = lehmann(n, t);
      
        if(flag == 1)
            System.out.println(n + " may be Prime.");
      
        else
            System.out.println(n + " is Composite."); 
    }
}
}
