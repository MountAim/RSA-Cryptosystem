#include<bits/stdc++.h>
using namespace std;
class Stringfunction{
    public:
        string p,q;
        bool isSmaller(string,string);
        string findSum(string,string);
        string findDiff(string,string);
        string multiply(string,string);
        string quotient(string,string,int);
        string divide_mod(string,string);
        string modInverse(string,string); 
        string powm(string,string,string);
};

bool Stringfunction::isSmaller(string str1, string str2)
{
    
    int n1 = str1.length(), n2 = str2.length();

    if (n1 < n2)
    return true;
    if (n2 < n1)
    return false;

    for (int i=0; i<n1; i++)
    if (str1[i] < str2[i])
        return true;
    else if (str1[i] > str2[i])
        return false;
    return false;
}
string Stringfunction::findSum(string str1, string str2)
{
    if (str1.length() > str2.length())
        swap(str1, str2);

    string str = "";

   
    int n1 = str1.length(), n2 = str2.length();

    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());

    int carry = 0;
    for (int i=0; i<n1; i++)
    {
        
        int sum = ((str1[i]-'0')+(str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');

        
        carry = sum/10;
    }

    
    for (int i=n1; i<n2; i++)
    {
        int sum = ((str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }
    if (carry)
        str.push_back(carry+'0');

    reverse(str.begin(), str.end());

    return str;
}

string Stringfunction::findDiff(string str1, string str2)
{
    
    if (isSmaller(str1, str2))
        swap(str1, str2);

    string str = "";

    int n1 = str1.length(), n2 = str2.length();

    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());

    int carry = 0;

    for (int i=0; i<n2; i++)
    {

        int sub = ((str1[i]-'0')-(str2[i]-'0')-carry);

        if (sub < 0)
        {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;

        str.push_back(sub + '0');
    }

    
    for (int i=n2; i<n1; i++)
    {
        int sub = ((str1[i]-'0') - carry);

        
        if (sub < 0)
        {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;

        str.push_back(sub + '0');
    }

    reverse(str.begin(), str.end());

    return str;
}

string Stringfunction::multiply(string num1, string num2)
{
    int len1 = num1.size();
    int len2 = num2.size();
    if (len1 == 0 || len2 == 0)
    return "0";

    vector<int> result(len1 + len2, 0);

    int i_n1 = 0;
    int i_n2 = 0;

    for (int i=len1-1; i>=0; i--)
    {
        int carry = 0;
        int n1 = num1[i] - '0';

        i_n2 = 0;

        for (int j=len2-1; j>=0; j--)
        {
            int n2 = num2[j] - '0';

      
            int sum = n1*n2 + result[i_n1 + i_n2] + carry;

            carry = sum/10;

            result[i_n1 + i_n2] = sum % 10;

            i_n2++;
        }

        if (carry > 0)
            result[i_n1 + i_n2] += carry;

        i_n1++;
    }

    int i = result.size() - 1;
    while (i>=0 && result[i] == 0)
    i--;

    if (i == -1)
    return "0";

    string s = "";

    while (i >= 0)
        s += std::to_string(result[i--]);

    return s;
}
string Stringfunction::quotient(string s1,string s2,int t=-1)
{
    
    if((s1.size()<s2.size())||((s1.size()==s2.size())&&(isSmaller(s1,s2))))
    {
    if(t==-1)
    return "0";
    else    
    return "";
    }
    string ans="";
    string divident="";
    int j=-1,flag=0;
    while(isSmaller(divident,s2))
    {
    if((s1[++j]=='0')&&(flag==0))
    ;
    else
    {
    flag=1; 
    divident+=s1[j];
    }
    if((j>t)&&(t!=-1))
    ans+="0";
    }
    for(char i='9';i>='1';i--)
    {
        string stemp="";
        stemp+=i;
        string ss=multiply(s2,stemp);
        if((isSmaller(ss,divident))||(ss==divident))
        {
            string s1becomes=findDiff(divident,ss);
            while(s1becomes[0]=='0')
            s1becomes=s1becomes.substr(1,(int)s1becomes.size()-1);
            int size=s1becomes.size();
            ++j;
            if((int)s1.size()-j>0)
            s1becomes+=s1.substr(j,((int)s1.size()-j));
            return ans+i+quotient(s1becomes,s2,size);
        }
    }
}
string Stringfunction::divide_mod(string s1,string s2)
{
    while((s1[0]=='0')&&(s1.size()>1))
    s1=s1.substr(1,s1.size()-1);
    if((s1.size()<s2.size())||((s1.size()==s2.size())&&(isSmaller(s1,s2))))
    return s1;
    string divident=s1.substr(0,s2.size());
    int flag=0;
    if(isSmaller(divident,s2))
    {
    flag=1;
    divident+=s1[s2.size()];
    }
    for(char i='9';i>='1';i--)
    {
        string stemp="";
        stemp+=i;
        string ss=multiply(s2,stemp);
        if((isSmaller(ss,divident))||(ss==divident))
        {
            string s1becomes=findDiff(divident,ss);
            if(flag==0)
            s1becomes+=s1.substr(s2.size(),(int)s1.size()-(int)s2.size());
            else
            {
            if(((int)s1.size()-(int)s2.size()-1)>0)
            s1becomes+=s1.substr(s2.size()+1,(int)s1.size()-(int)s2.size()-1);
            }
            return divide_mod(s1becomes,s2);
        }
    }
}

string Stringfunction::powm(string x,string y,string m)
{
x=divide_mod(x,m);
string res="1";
while(isSmaller("0",y))
{
  if(divide_mod(y,"2")=="1")
  {
    res=divide_mod((multiply(res,x)),m);
  }
  y=quotient(y,"2");
  x=divide_mod((multiply(x,x)),m);
}
return res;
}

string Stringfunction::modInverse(string a, string m)
{
    string m0 = m;
    string y = "0", x = "1";

    if (m == "1")
      return "0";
      int flaga=0,flagx=0,flagy=0,flagt=0;
    while ((isSmaller("1",a))&&(flaga==0))
    {
        string q;
        q = quotient(a,m);
        string t = m;
        flagt=0;
        m = divide_mod(a,m);
        flaga=flagt;
        a = t;
        flagt=flagy;
        t = y;
        if((flagy==1)&&(flagx==0))
        {
        y=findSum(multiply(q , y),x);
        flagy=0;
        }
        else if((flagx==1)&&(flagy==1))
        {
            if(isSmaller(x,multiply(q,y)))
            flagy=0;
            y = findDiff(multiply(q , y),x);
        }
        else if((flagx==0)&&(flagy==0))
        {
            if(isSmaller(x,multiply(q,y)))
            flagy=1;
            y = findDiff(multiply(q , y),x);
        }
        else
        {
        y = findSum(x ,multiply(q , y));
        flagy=1;
        }
        flagx=flagt;
        x = t;
        //cout<<x<<"\n";
    }
    if(flagx==1)
    {
        x=findDiff(m0,x);
    }
    return x;
}

int main()
{
    Stringfunction st;
    cout<<"Enter two prime Numbers \n";
    cout<<"p:";
    cin>>st.p;
    cout<<"q:";
    cin>>st.q;
    string n,phi,p_minus_1,q_minus_1,e,d,m; 
    n=st.multiply(st.p,st.q);
    p_minus_1=st.findDiff(st.p,"1");
    q_minus_1=st.findDiff(st.q,"1");
    phi=st.multiply(p_minus_1,q_minus_1);
    cout<<"Enter Encryption Key : ";
    cin>>e;
    d=st.modInverse(e,phi);
    cout<<"Decryption Key,d :"<<d<<"\n";
    cout<<"Enter Message : ";
    cin>>m;
    int sz=m.size();
    string mn[sz];
    for(int i=0;i<m.size();i++)
    {
       // string stt="";
        int k;
        if(islower(m[i]))
        k=m[i]-'a';
        else k=m[i]-'A';
        k++;
        mn[i]=to_string(k);
       // cout<<mn[i]<<" ";
    }
    cout<<"\nEntered message to number: ";
    for(int i=0;i<sz;i++)
    cout<<mn[i];
    cout<<"\n";
   string c[sz];
    for(int i=0;i<sz;i++)
    {
        string temp="";
        temp+=mn[i];
        c[i]=st.powm(temp,e,n);
    }
    string mes[sz];
    for(int i=0;i<sz;i++)
    {
    string temp="";
    temp+=c[i]; 
    mes[i]=st.powm(temp,d,n);
    }
    cout<<"Cyper Text :";
    for(int i=0;i<sz;i++)
    cout<<c[i];
    cout<<"\n";
    cout<<"\nMessage :";
    for(int i=0;i<sz;i++)
    cout<<mes[i];
    cout<<"\n";
    string tmp[sz];
    cout<<"\nDecrypted message was ";
    for(int i=0;i<sz;i++)
    {
    //  stringstream 
        string s;
        s=mes[i];
        stringstream ss;
        ss<<s;
        int x;
        ss>>x;
        char ch=x-1+'A';
        cout<<ch;
    }
    return 0;
}
