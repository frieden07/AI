#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

map<string, string> reflections = {
    {"i am", "you are"},
    {"i was", "you were"},
    {"i", "you"},
    {"i'm", "you are"},
    {"i'd", "you would"},
    {"i've", "you have"},
    {"i'll", "you will"},
    {"my", "your"},
    {"you are", "I am"},
    {"you were", "I was"},
    {"you've", "I have"},
    {"you'll", "I will"},
    {"your", "my"},
    {"yours", "mine"},
    {"you", "me"},
    {"me", "you"}};

vector<vector<string>> pairs = {
    {"my name is (.*)", "Hello %1, How can I assist you today?"},
    {"hi|hey|hello", "Hello", "Hey there"},
    {"what is your name ?", "I am a vegetable shop chatbot. How may I help you?"},
    {"how are you ?", "I'm doing well, thank you. How about you?"},
    {"sorry (.*)", "It's alright", " No problem", " Apologies accepted"},
    {"i am fine", "Great to hear that. How can I assist you?"},
    {"i'm (.*) doing good", "Nice to hear that. How can I help you?"},
    {"(.*) current price (.*)", "Current price of vegetable is:"},
    {"(.*) purchase (.*)", "Select the vegetables from the list"},
    {"(.*) age (.*)", "I am a vegetable shop chatbot. I don't have an age."},
    {"(.*) do (.*)", "I want to help you find the best vegetables for your needs."},
    {"(.*)who\\s+.*\\s+created\\s+.*\\?", "I was created by a team of developers.", "My creators remain anonymous."},
    {"(.*) (location|city) ?", "I am a virtual vegetable shop, so I don't have a physical location."},
    {"quit", "Goodbye! Have a great day.", "See you soon!", "Take care!"}};

string reflect(const string &word)
{
    auto it = reflections.find(word);
    if (it != reflections.end())
    {
        return it->second;
    }
    return word;
}

bool validateEmail(const std::string &email)
{
    // Regular expression pattern for email validation
    regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");

    // Match the email against the pattern
    return regex_match(email, pattern);
}

void chat()
{
    cout << "Bot: Hello! How can I assist you today?" << std::endl;
    cout << "Enter your Name :-";
    string name;
    cin >> name;
    bool flag = false;
    string email;
    while (!flag)
    {
        cout << "Enter valid e-mail : - ";
        cin >> email;
        if (validateEmail(email))
        {
            flag = true;
            break;
        }
    }

    string user_input;
    while (true)
    {
        // cout<<"bot: Welcome\n";
        cout << "User: ";
        getline(cin, user_input);

        bool pattern_matched = false;
        for (const auto &pair : pairs)
        {
            regex pattern(pair[0], std::regex_constants::icase);
            smatch matches;
            if (regex_match(user_input, matches, pattern))
            {
                pattern_matched = true;

                string response = pair[1];
                if (pair.size() > 2)
                {
                    response += pair[2 + (rand() % (pair.size() - 2))];
                }

                regex word_regex("(%\\d+)");
                sregex_iterator it(response.begin(), response.end(), word_regex);
                sregex_iterator end;
                while (it != end)
                {
                    smatch match = *it;
                    string match_str = match.str();
                    int match_index = std::stoi(match_str.substr(1));
                    string reflection = reflect(matches.str(match_index));
                    response = std::regex_replace(response, regex(match_str), reflection);
                    ++it;
                }

                cout << "Bot: " << response << endl;
                map<string, int> bill;
                if (response == "Current price of vegetable is:" || response == "Select the vegetables from the list")
                {
                    ifstream fin("vegetable.txt"); // Open the file for reading

                    if (fin.is_open())
                    {
                        cout<<"Vegetable"<<"      "<<"Price(KG)\n";
                        string line;
                        while(getline(fin,line)){
                        std::stringstream ss(line);
                        std::string key;
                        int value;

                        if (ss >> key >> value)
                        {
                            // Store the key-value pair in the map
                            bill[key] = value;
                            cout<<line<<"\n";
                        }
                        }
                        fin.close(); // Close the file
                    }
                    else
                    {
                        cout << "Error opening the file." << endl;
                    }
                }
                if (response == "Select the vegetables from the list")
                {
                    string bill_name = "Bill_"+name+".csv";
                    ofstream fout(bill_name);
                    fout<<"Online vegetable shop"<<endl;
                    fout<<"Customer name "<<","<<name<<endl;
                    fout<<"Vegetable"<<","<<"price"<<endl;
                    cout<<"Enter the number of vegetable do you want to buy :-\n";
                    int vege ;
                    cin>>vege;
                    int total = 0;
                    while(vege--){
                        string gt;
                        
                        cout<<"Enter the name of vegetable :";
                        cin>>gt;
                        if(bill.find(gt) == bill.end()){
                            cout<<"Enter the name of valid vegetable\n";
                        }
                        else{
                            int quan;
                            cout<<"Enter the quantity in Kg"<<"\n";
                            cin>>quan;
                            fout<<gt<<","<<bill[gt]*quan<<endl;
                            total += bill[gt]*quan;
                        }
                    }
                    cout<<"Your total cost is :- "<<total<<"\n";
                    cout<<"Thanking for shopping with us\n";
                    fout<<"Total price"<<","<<total<<endl;
                    fout<<"Thanking for shopping with us"<<endl;
                    fout<<"Good once sold never be taken back"<<endl;
                    fout.close();
                }
                break;
            }
        }

        if (!pattern_matched)
        {
            cout << "Bot: Sorry, I didn't understand. Can you please rephrase your statement or question?" << std::endl;
        }

        if (user_input == "quit")
        {
            break;
        }
    }
}

int main()
{
    cout << "Vegetable Shop Chatbot" << endl;
    chat();
    return 0;
}
