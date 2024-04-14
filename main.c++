#include<iostream>
#include<vector>
#include<tuple>


using namespace std;

bool isPrime(int n){
    if(n <= 1){
        return false;
    }
    if(n ==2 || n == 3){
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0){
        return false;
    }
    for (int i = 5; i*i <= n; i = i + 6){
        if( n % i == 0 || n % (i+2) == 0){
            return false;
        }
    }
    return true;
}

vector<int> primeNums(int n){
    vector<int> primes;
    if(isPrime(n)){
        primes.push_back(n);
    }
    else{
        for (int i = 2; i <= n; i++){
            while(n%i == 0){
                primes.push_back(i);
                n = n/i;
            }
        }
    }
    return primes;
}
    
vector<int> exponents(vector<int> primeNumbers) {
    // List of prime numbers up to 97
    const vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    vector<int> exponents(primes.size(), 0);

    for (int i = 0; i < primes.size(); i++) {
        int counter = 0;
        for (int j = 0; j < primeNumbers.size(); j++) {
            if (primeNumbers[j] == primes[i]) {
                counter++;
            }
        }
        exponents[i] = counter;
    }

    return exponents;
}

//modify exponents array size
vector<int> finalExponents(vector<int> foundExponents){
    int i = foundExponents.size()-1;
    while(foundExponents[i] == 0){
        
        foundExponents.pop_back();
        i--;
        
    }
    return foundExponents;
}
    

// calculate a,b,c 
tuple<int, int, int> compute( int n)
{

    int a = 0, b = 0, c = 0, z = 0;
    n = n+1;
    while( n % 2 == 0){
        a++;
        n /= 2;
    }
    z = (n-1) / 2;
    z = z + 1;
    while ( z % 2 == 0 ){
        b++;
        z /= 2;
    }
    c = (z - 1) / 2;
    return make_tuple(a, b, c);
}

vector<tuple<int, int, int>> instructions(vector<int> expArr, int arrLen)
{
    vector<tuple<int, int, int>> result;
    for(int i = 0; i < arrLen; i++){
        result.push_back(compute(expArr[i]));
    }
    return result;
}
//make coding labels
string codLab(int a)
{
    
    if(a == 0)
    {
        return " ";
    }
    else
    {    
        char letter[5] = {'A', 'B', 'C', 'D', 'E'};
        // cout<<"a: "<<a<<endl;
        char letterLabel = letter[(a % 5)-1];
        // cout<<"letterlabel: "<<letterLabel<<endl;
        int count = 1;
        
        while(a > 5){
            a = a - 5;
            count++;
        }
        return letterLabel+to_string(count);
    }
}


string codeVar(int c)
{
   
    int varNum = c+1;
    if(varNum == 1){
        return "Y";
    }
    else{
        if ((varNum)%2 == 0)
        {
            return "X"+ to_string(varNum/2);
        }
        else{
            return "Z" + to_string(varNum/2);
        }
    }
    return "blaah, blaaah, blaah";
}
//print instructions
string program(int a, int b, int c)
{
    if( b == 0){
        return codLab(a) + "  "+ codeVar(c) + "←" + codeVar(c);
    }
    else if (b == 1)
    {
        return codLab(a) + "  " + codeVar(c) + "←"  + codeVar(c) + " + 1";
    }
    else if (b == 2)
    {
        return codLab(a) + "  " + codeVar(c) + "←"  + codeVar(c) + " - 1";
    }
    else{
        return to_string(a+2) + "  " + "IF " + codeVar(c) + " ≠ 0 GOTO" + codLab(a) ;
    }
}


int main(){
    int n;
    cout<<"enter n: ";
    cin>>n;
    n = n+1;
    // cout<<"n+1 = "<<n<<endl;
    // cout<<"prime numbers for n+1: ";
    for (int i: primeNums(n)){
        cout<<i<<" ";
    }
    cout<<endl;
    // cout<<"exponents: ";
    vector<int> expArr = finalExponents(exponents(primeNums(n)));
    for (int j: expArr)
    {
        cout<<j<<" ";
    }
    cout<<endl;
    int arrLen = expArr.size();
    
    for(int i = 0; i < arrLen; i++){
        cout<<"instruction #"<<i<<": ";
        tuple<int, int, int> result = instructions(expArr, arrLen)[i];
        // cout<<"〈" << get<0>(result) << ", 〈" << get<1>(result) << ", " << get<2>(result) << "〉〉" << endl;

        int a = get<0>(result);
        // string x = codLab(a);
        // cout<<"a: "<<x;
        // cout<<endl;

        

        int c = get<2>(result);
        // string z = codeVar(c);
        // cout<<"c: "<<z<<endl;
        int b = get<1>(result);
        string y = program(a,b,c);
        cout<<y<<endl;


    }
    cout<<endl;
    return 0;
}