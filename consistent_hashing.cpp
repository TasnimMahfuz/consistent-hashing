#include <bits/stdc++.h>
using namespace std;

vector<pair<string, int>> hash_ring(509);
map<string, vector<string>> server_pool;

int hash_string(string value);
void add_server(string server_name);
void add_key(string key);
void remove_key(string key);
void remove_server(string server_name);
void print_server_keys(string server_name);


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

    add_server("130");

    remove_key("seven");
    remove_key("four");
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

    vector<pair<string,int> > temporary_key_holder;
    string previous_server;

    for(int i = hash_value - 1; ; i--)
    {
        if(i == -1)
            i = 508;

        if(i == hash_value)
        {
            cout<<"\nThere is only one server in the server pool.\n";
            cout<<"No need for key redistribution\n";

            break;
        }

        if(hash_ring[i].second== 2025)
        {
            previous_server = hash_ring[i].first;
            cout<<"Previous Server Found! Server name: <"<<previous_server<<">\n\n";
            cout<<"This server contains: ";

            print_server_keys(previous_server);
            break;
        }

        if(hash_ring[i].second != -1)
        {
            temporary_key_holder.push_back(hash_ring[i]);
        }
    }

    if(temporary_key_holder.size() != 0)
    {   
        cout<<"--------------------------------------------\n";
        cout<<"Total keys to be transferred: "<<temporary_key_holder.size()<<endl;

        for(int i = 0; i < temporary_key_holder.size(); i++)
            cout<<"<"<<temporary_key_holder[i].first<<">    ";
        cout<<"\n****************************************************\n";

        for(int i = 0; i < temporary_key_holder.size(); i++)
        {

            string current_key = temporary_key_holder[i].first;
            int current_key_server_hash = temporary_key_holder[i].second;
            string current_key_server_name = hash_ring[current_key_server_hash].first;

            cout<< "Key: <"<<current_key<<">\tPrevious Server: <"<<current_key_server_name<<">\n";
        
            int key_hash = hash_string(current_key);
            hash_ring[key_hash] = {current_key, hash_value};
            server_pool[server_name].push_back(current_key);

            cout<<"\nKey transferred to new server successfully! Now:\n";
            cout<< "Key: <"<<current_key<<">\tCurrent server: <"<<hash_ring[hash_ring[key_hash].second].first<<">\n";

            cout<<"\nBefore Deleting from Key's Previous Server, it contains: ";
            print_server_keys(current_key_server_name);
            
            auto it = server_pool.find(current_key_server_name);

            if(it != server_pool.end())
            {
                auto &vec = it->second;
                vec.erase(remove(vec.begin(), vec.end(), current_key), vec.end());
            }

            cout<<"\nAfter Deleting from Key's Previous Server, it contains: ";
            print_server_keys(current_key_server_name);
        }
        cout<<"--------------------------------------------\n\n";
    }

    cout<<"\n****************************************************\n";
    cout<<"The added server now contains: ";
    print_server_keys(server_name);
    cout<<"\n****************************************************\n";

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

void remove_key(string key)
{
    int key_hash = hash_string(key);
    int key_server_hash = hash_ring[key_hash].second;

    if(key_server_hash == -1)
    {
        cout<<"The key <"<<key<<"> does not exist in the server.\n\n";
        cout<<"###################################################\n";
        return;
    }

    cout<< "Before removing, the main server contains: ";
    print_server_keys(hash_ring[key_server_hash].first);

    auto it = server_pool.find(hash_ring[key_server_hash].first);

    if(it != server_pool.end())
    {
        auto &vec = it -> second;
        vec.erase(remove(vec.begin(), vec.end(), key), vec.end());
    }

    cout<< "\n\nAfter removing, the main server contains: ";
    print_server_keys(hash_ring[key_server_hash].first);

    cout<<"Remove from server successful!\n";

    hash_ring[key_hash] = {"empty", -1};

    cout<<"Remove from hash ring successful!\n";
    cout<<"#######################################################\n\n";
   
}

void remove_server(string server_name)
{

}

void print_server_keys(string server_name)
{
    vector<string> keys = server_pool[server_name];

    for(int i = 0; i < keys.size(); i++)
        cout<<"<"<<keys[i]<<">\t";

    cout<<endl<<endl;
    
}