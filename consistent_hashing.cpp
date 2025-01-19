#include <bits/stdc++.h>
using namespace std;

vector<pair<string, int>> hash_ring(509);
map<string, vector<string>> server_pool;

int hash_string(string value);
void add_server(string server_name);
void add_key(string key);
void remove_server(string server_name);


void empty_hash_ring()
{
    for(int i = 0; i < 509; i++)
        hash_ring[i] = {"empty",-1};
}




int main()
{
    empty_hash_ring();

    add_key("one");

    add_server("server_1");

    add_key("one");
    add_key("two");

    add_server("ser_2");
    add_key("three");
    add_key("four");
}

int hash_string(string value)
{
    int mod = 509; 

    int string_to_int = 0;
    int idx = 0;

    for(int i = value.size() - 1; i >= 0; i--)
    {
        int converted_int;

        if(value[i]>= 'a' and value[i] <= 'z')
            converted_int = (value[i] - 'a' + 1);
        else if(value[i] >='A' and value[i]<= 'Z')
            converted_int = (value[i] - 'A' + 1);
        else 
            converted_int = (value[i] - '1' + 1);

        string_to_int += converted_int*pow(10,idx);
        idx++;
        
    }

    return string_to_int % mod;

}

void add_server(string server_name)
{
    int hash_value = hash_string(server_name);

    hash_ring[hash_value] = {server_name,2025};

    cout<<"Server added successfully!\nHash value: "<<hash_value<<endl;
}

void add_key(string key)
{
    int hash_value = hash_string(key);

    int count = 0;

    for(int i = hash_value; ; i++)
    {
        count++;

        if(count == (509 + 1))
        {
            cout<<endl;
            cout<<"No server in the system. Key storage failed.\nPlease, add a server.\n\n";

            break;
        }

        if(i == 509)
            i = 0;
        
        if(hash_ring[i].second == 2025)
        {
            hash_ring[hash_value] = {key,i};

            cout<<endl;
            cout<<"Key: '"<<key<<"' is added to: <"<<hash_ring[i].first<<"> server."<<endl;
            cout<<"key hash: <"<<hash_value<<">    server hash: <"<<i<<">\n\n";

            server_pool[hash_ring[i].first].push_back(key);

            break;
        }
    }

}

void remove_server(string server_name)
{

}