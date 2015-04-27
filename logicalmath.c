
const unsigned int UINT_ALL_SET = ~0;
#ifndef UINT_MAX
const unsigned int UINT_MAX = ~0;
#endif
#ifndef INT_MAX
const int INT_MAX = (int)(((unsigned int)~0) >> 1);
#endif
#ifndef INT_MIN
const int INT_MIN = ~(((unsigned int)~0) >> 1);
#endif
const unsigned int INT_HIGH_BIT = ~(((unsigned int)~0) >> 1);

int add(int m, int n);
int negative(int n);
int subtract(int m, int n);
int increment(int n);
int decrement(int n);
int equal(int m, int n);
int notEqual(int m, int n);
int greaterThan(int m, int n);
int lesserThan(int m, int n);
int unsignedGreaterThan(unsigned int m, unsigned int n);
int multiply(int m, int n);
int divide(int m, int n);
int absValue(int n);

int add(int m, int n)
{
   int carry = (m & n) << 1;
   if(carry) {
      return add(m^n, carry);
   }
   return m^n;
}

int negative(int n)
{
   return add(~n, 1);
}

int subtract(int m, int n)
{
   return add(m, negative(n));
}

int increment(int n)
{
   return add(n, 1);
}

int decrement(int n)
{
   return add(n, negative(1));
}

int equal(int m, int n)
{
   return !(m^n); 
}

int notEqual(int m, int n)
{
   return m^n;
}

int greaterThan(int m, int n)
{
  unsigned int s = INT_HIGH_BIT;
  int x = m & s, y = n & s;
  if(x ^ y) {
    return y;      
  }
  s>>=1;
  while(s) {
      if((m ^ n) & s) {
          return m & s;
      }
      s>>=1;
  }
  return 0;
}

int lesserThan(int m, int n)
{
   return greaterThan(n, m);
}

int unsignedGreaterThan(unsigned int m, unsigned int n)
{
  unsigned int s = INT_HIGH_BIT;
  
  while(s) {
      if((m ^ n) & s) {
          return m & s;
      }
      s>>=1;
  }
  return 0;
}
   
int multiply(int m, int n)
{
  int sum=0, shiftbit=1;

  while(shiftbit) {
     if(shiftbit & n) {
        sum = add(sum, m);
     }
     m <<= 1;
     shiftbit <<= 1;
  }
  return sum;
}

int absValue(int n)
{
  return (n & INT_HIGH_BIT) ? negative(n) : n;
}

int divide(int m, int n)
{
  unsigned int shiftbit = INT_HIGH_BIT, sum = 0, tmpSum = 0;
  int sign = 1; 
  unsigned int um = absValue(m), un = absValue(n);
  if((m^n) & shiftbit) {
    sign = negative(1);
  }
  if(equal(m, INT_MIN)) {
    sign = negative(sign);
  }
      
  if(!n) {
    exit(1); /* divide by zero error */    
  }

  while(shiftbit && !(shiftbit & um)) {  
    shiftbit >>= 1;
  }

  while(shiftbit && unsignedGreaterThan(multiply(shiftbit,un),um)) {
    shiftbit >>= 1;
  }
  sum = add(sum, shiftbit);

  shiftbit >>= 1;
  while(shiftbit) {
    tmpSum = add(sum, shiftbit);
    while(shiftbit && unsignedGreaterThan(multiply(tmpSum,un),um)) {
        shiftbit >>= 1;
        tmpSum = add(sum, shiftbit);
    }
    sum = tmpSum;
    shiftbit >>= 1;
  }  
  return multiply(sum, sign); 
}




