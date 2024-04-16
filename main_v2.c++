#include<iostream>
#include<vector>
#include<tuple>
#include<cstdlib>

using namespace std;


bool isPrime(unsigned long long int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (unsigned long long int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

vector<unsigned long long int> primeNums(unsigned long long int n) {
    vector<unsigned long long int> primes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
        31, 37, 41, 43, 47, 53, 59, 61, 67, 
        71, 73, 79, 83, 89, 97
    };

    vector<unsigned long long int> factors;

    for (unsigned long long int prime : primes) {
        while (n % prime == 0) {
            factors.push_back(prime);
            n /= prime;
        }
    }

    if (n != 1) {
        cout << "Input not completely factorized by the provided list of prime numbers." << endl;
        exit(0);
    }

    return factors;
}

    
vector<unsigned long long int> exponents(vector<unsigned long long int> primeNumbers) {
    // List of prime numbers up to 97
    const vector<unsigned long long int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    vector<unsigned long long int> exponents(primes.size(), 0);
    int length = primes.size();

    for (unsigned long long int i = 0; i < primes.size(); i++) {
        unsigned long long int counter = 0;
        for (unsigned long long int j = 0; j < primeNumbers.size(); j++) {
            if (primeNumbers[j] == primes[i]) {
                counter++;
            }
        }
        exponents[i] = counter;
    }
    return exponents;
}

//modify exponents array size
vector<unsigned long long int> finalExponents(vector<unsigned long long int> foundExponents){
    unsigned long long int i = foundExponents.size()-1;
    while(foundExponents[i] == 0){
        
        foundExponents.pop_back();
        i--;    
    }
    return foundExponents;
}
    

// calculate a,b,c 
tuple<unsigned long long int, unsigned long long int, unsigned long long int> compute( unsigned long long int n)
{

    unsigned long long int a = 0, b = 0, c = 0, z = 0;
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

vector<tuple<unsigned long long int, unsigned long long int, unsigned long long int>> instructions(vector<unsigned long long int> expArr, unsigned long long int arrLen)
{
    vector<tuple<unsigned long long int, unsigned long long int, unsigned long long int>> result;
    for(unsigned long long int i = 0; i < arrLen; i++){
        result.push_back(compute(expArr[i]));
    }
    return result;
}
//make coding labels
string codLab(unsigned long long int a)
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
        unsigned long long int count = 1;
        
        while(a > 5){
            a = a - 5;
            count++;
        }
        return   letterLabel+to_string(count);
    }
}


string codeVar(unsigned long long int c)
{
   
    unsigned long long int varNum = c+1;
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
//prunsigned long long int instructions
string program(unsigned long long int a, unsigned long long int b, unsigned long long int c)
{
    if( b == 0){
        return codLab(a) + "  "+ codeVar(c) + " ← " + codeVar(c);
    }
    else if (b == 1)
    {
        return codLab(a) + "  " + codeVar(c) + " ← " + codeVar(c) + " + 1";
    }
    else if (b == 2)
    {
        return codLab(a) + "  " + codeVar(c) + " ← " + codeVar(c) + " - 1";
    }
    else{
        return codLab(a) + "  " + "IF " + codeVar(c) + " ≠ 0 GOTO " + codLab(b-2) ;
    }
}


int main(){
    unsigned long long n;
    cout<<"enter n: ";
    cin>>n;
    if(n == 1 || n == 0)
    {
        cout<<n<<" can't be factorized using the list of numbers."<<endl;
        return 0;

    }
    // n = n+1;
    // cout<<"n+1 = "<<n<<endl;
    // cout<<"prime numbers for n+1: ";
    for (unsigned long long int i: primeNums(n)){
        cout<<i<<" ";
    }
    cout<<endl;
    // cout<<"exponents: ";
    vector<unsigned long long int> expArr = finalExponents(exponents(primeNums(n)));
    for (unsigned long long int j: expArr)
    {
        cout<<j<<" ";
    }
    cout<<endl;
    unsigned long long int arrLen = expArr.size();
    
    for(unsigned long long int i = 0; i < arrLen; i++){
        cout<<"instruction #"<<i<<": ";
        tuple<unsigned long long int, unsigned long long int, unsigned long long int> result = instructions(expArr, arrLen)[i];
        // cout<<"〈" << get<0>(result) << ", 〈" << get<1>(result) << ", " << get<2>(result) << "〉〉" << endl;

        unsigned long long int a = get<0>(result);
        // string x = codLab(a);
        // cout<<"a: "<<x;
        // cout<<endl;

        unsigned long long int c = get<2>(result);
        // string z = codeVar(c);
        // cout<<"c: "<<z<<endl;
        unsigned long long int b = get<1>(result);
        string y = program(a,b,c);
        cout<<y<<endl;

    }
    cout<<endl;
    return 0;
}