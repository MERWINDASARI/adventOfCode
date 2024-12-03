#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main() {
    string input = "";
    string s;
    
    // Read the entire input
    while (getline(cin, s)) {
        input += s;
    }

    
    std::regex mul_pattern(R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))");

    // Iterator to search through the input
    smatch matches;
    string::const_iterator search_start(input.cbegin());
    int sum = 0;
    bool add = true;  
    while (regex_search(search_start, input.cend(), matches, mul_pattern)) {
        // Check if it's a do() or don't()
        if (matches[0]=="don't()") { 
                add = false;
                search_start = matches.suffix().first;
                continue;
        }
         if (matches[0]=="do()") { 
                add = true;
                search_start = matches.suffix().first;
                continue;
        }
        if (add) {
           
            int first_number = std::stoi(matches[1].str()); 
            int second_number = std::stoi(matches[2].str()); 
            // cout << first_number << " " << second_number << '\n';
            sum += first_number * second_number; 
        }
        // Move the search cursor forward
        search_start = matches.suffix().first;  
    }

    cout << sum << endl;  // Output the sum

    return 0;
}
