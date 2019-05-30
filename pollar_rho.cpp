#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define LL __int128
#define endl '\n'
void printLL(LL n)
{
    string cad;
    while(n)
    {
        char s = (n%10) + '0';
        string ss;
        ss.push_back(s);
        n/=10;
        cad.append(ss);
    }
    reverse(cad.begin(),cad.end());
    cout<<cad;
}

LL absLL(LL a)
{
    a>0?a:a=-a;
    return a;
}
map<LL,int>fact;
LL f_p(LL x, LL n, LL mod)
{
    LL res = 1;
    while(n)
    {
        if(n&1)
            res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}
bool isprime(LL n)
{
    if(n == 2 or n == 3) return true;
    if(n < 2 or n%2==0) return false;
    for(int i = 0; i < 10; i++)
    {
        LL a = (rand() % (n - 4)) + 2;
        LL s = n - 1;
        while(!(s&1))s/=2;
        LL mod = f_p(a, s, n);
        if( mod == 1 or mod == (n - 1))
            continue;
        bool is = false;
        while(s != (n-1))
        {
            mod = f_p(a, s, n);
            if(mod == (n - 1))
            {
                is = true;
                break;
            }
            s *=2;
        }
        if(!is)
            return false;
    }
    return true;
}

LL gcd(LL a, LL b)
{
    if(b == 0)
        return a;
    return gcd(b, a%b);
}

LL pollard_rho(LL n)
{
    LL x = rand() % n + 1;
    LL c = rand() % n + 1;
    LL y = x;
    LL d =  1;
    while(d == 1)
    {
        x = (f_p(x,2,n) + c ) % n;
        y = (f_p(y,2,n) + c ) % n;
        y = (f_p(y,2,n) + c ) % n;
        d = gcd(absLL(x-y),n);
        if(d == n) 
            return pollard_rho(n);
    }
    return d;
}
void factorize(LL n)
{
    if(n == 1)
        return;
    if( isprime(n) )
    {
        fact[n]++;
        return;
    }
    LL div = pollard_rho(n);
    factorize(div);
    factorize(n/div);
}
int main()
{
    srand(time(NULL));
    ll num;
    cin>>num;
    while(num%2 == 0)
    {
        num/=2;
        fact[2]++;
    }
    factorize(num);
    for(auto a: fact)
    {
        printLL(a.first);
        cout<<" ^ "<<a.second<<endl;
    }
        
    return 0;

}  

