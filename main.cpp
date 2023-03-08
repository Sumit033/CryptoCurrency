#include <bits/stdc++.h>
using namespace std;

class transactiondata
{
public:
    double amount;
    string senderkey;
    string recieverkey;
    
    //constroctor
    transactiondata(){}
    transactiondata(double amt, string skey, string rkey)
    {
        amount = amt;
        senderkey = skey;
        recieverkey = rkey;
    }
};

class block
{
private:
    long long generatehash()
    {
        long long hash_value = 0;
        size_t p = 131;
        long long m = 1e12 + 9;
        size_t pow_p = 1;
        string s1 = to_string(data.amount) + data.senderkey + data.recieverkey + to_string(previoushash);
        for (char c : s1)
        {
            hash_value = (hash_value + (c - '0' + 1) * pow_p) % m;
            pow_p = (pow_p * p) % m;
        }
        return hash_value;
    }
    long long previoushash;
    long long blockhash;

public:
    transactiondata data;
    // constroctor
    block(transactiondata d, long long prevHash)
    {
        data = d;
        previoushash = prevHash;
        blockhash = generatehash();
    }
    long long gethash()
    {
        return blockhash;
    }
    long long getprevioushash()
    {
        return previoushash;
    }
    bool ishashvalid()
    {
        if (gethash() == generatehash())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class blockchain
{
    vector<block> chain;

public:
    void addblock(transactiondata d)
    {
        long long previoushash = (int)chain.size() > 0 ? getlatesthash()->gethash() : 0;
        block add(d, previoushash);
        chain.push_back(add);
    }
    block *getlatesthash()
    {
        return &chain.back();
    }
    bool ischainvalid()
    {
        vector<block>::iterator it;
        for (it = chain.begin(); it != chain.end(); it++)
        {
            block currentblock = *it;
            if (!currentblock.ishashvalid())
            {
                return false;
            }
            if (it != chain.begin())
            {
                block previousBlock = *(it - 1);
                if (previousBlock.gethash() != currentblock.getprevioushash())
                {
                    return false;
                }
            }
        }
        return true;
    }
    void printChain()
    {
        std::vector<block>::iterator it;

        for (it = chain.begin(); it != chain.end(); ++it)
        {
            block currentBlock = *it;
            printf("\n\nBlock ===================================");
            printf("\nAmount: %f", currentBlock.data.amount);
            printf("\nSenderKey: %s", currentBlock.data.senderkey.c_str());
            printf("\nReceiverKey: %s", currentBlock.data.recieverkey.c_str());
            //printf("\nTimestamp: %ld", currentBlock.data.timestamp);
            printf("\nHash: %zu", currentBlock.gethash());
            printf("\nPrevious Hash: %zu", currentBlock.getprevioushash());
            printf("\nIs Block Valid?: %d\n", currentBlock.ishashvalid());
        }
    }
};

void tempering(class block *c)
{
    double num;
    string s1;
    string s2;
    cout << "enter changes" << endl;
    cout << endl;
    cout << "enter amount" << endl;
    cin >> num;
    cout << "enter sender name" << endl;
    cin >> s1;
    cout << "enter reciever name" << endl;
    cin >> s2;
    c->data.amount = num;
    c->data.senderkey = s1;
    c->data.recieverkey = s2;
}

int main()
{
    blockchain dd;
    char c;
    do
    {
        cout << "want to add block (y/n)" << endl;
        cin >> c;
        if (c == 'n')
        {
            break;
        }
        transactiondata d;
        cout << "enter amount:" << endl;
        cin >> d.amount;
        cout << "enter senderkey:" << endl;
        cin >> d.senderkey;
        cout << "enter recieverkey:" << endl;
        cin >> d.recieverkey;
        dd.addblock(d);
    } while (c != 'n');
    
    dd.printChain();
    dd.ischainvalid();
    //now we try to manipulate the data
    //we are trying to change last block data
    block *change = dd.getlatesthash();
    tempering(change);
    dd.printChain();
    dd.ischainvalid();

    return 0;
}