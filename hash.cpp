#include <iostream>
#include <string>
#include <bitset>


std::string wordToBinary(const std::string& text) {
    std::string binary;
    for (unsigned char c : text) {
        binary += std::bitset<8>(c).to_string();
    }
    return binary;
}

char fourNumbersToHex(const std::string& nibble) {
    int value = std::bitset<4>(nibble).to_ulong();
    if (value < 10) return '0' + value;
    return 'A' + (value - 10);
}

std::string binaryToHex(const std::string& binary) {
    std::string hex;
    for (size_t i = 0; i < binary.size(); i += 4) {
        hex += fourNumbersToHex(binary.substr(i, 4));
    }

    return hex;
}


std::string hash(std::string input, int seed){


    input = wordToBinary(input);
    int amount_of_1 = 0;
    int amount_of_0 = 0;
    for (int i=0; i<input.length(); i++){
        if (input[i] == '1')
        amount_of_1++;
        else amount_of_0++;
    }

    int bigger = ((amount_of_0 > amount_of_1) ? amount_of_0 : amount_of_1)*seed*100;
    int smaller = ((amount_of_0 < amount_of_1) ? amount_of_0 : amount_of_1);
    if ((bigger % smaller) == 0)
        smaller++;


    std::cout << input.length() << std::endl;
    std::cout << bigger << " " << smaller << std::endl;

    int current = 0;
    for (int i=0; i<bigger; i++){
        char temp = input[current];
        int next_pos = (current + smaller - i) % input.length();
        // std::cout << "next_pos: " << next_pos << " current: " << current << " smaller: " << smaller << " i: " << i << std::endl;
        input[current] = input[next_pos];
        input[next_pos] = temp;
        current = next_pos; 
        // std::cout << "switching " << current << "with " << next_pos << std::endl; 
    }
    input = binaryToHex(input);
    input = wordToBinary(input);

    current = 0;
    for (int i=0; i<smaller; i++){
    char temp = input[current];
    int next_pos = (current + bigger - i) % input.length();
    input[current] = input[next_pos];
    input[next_pos] = temp;
    current = next_pos; 
    }

    while (input.size() < 256){ //Gali but sitoj vietoj blogai
        input += input;
    }




    // Pavertus i binary, 256 bitai
    std::string start = "qwertyuiopasdfghjklzxcvbnm945137";  
    start = wordToBinary(start);

    std::string Hashed = "";

    for (int i=0; i<256; i++){
        if (start[i] == input[i])
        Hashed += '1';
        else Hashed += '0';
    }

    return binaryToHex(Hashed);
    return input;
}

int main(){

    int seed = 10;
    std::string input = "labaa";
    std::cout << hash("dfasghbjkljuiygtfyghbjuiokpkihyugtrdfyguhijoiadsgyusadaa", seed) << std::endl;
    std::cout << hash("dfasghbjkljuiygtfaghbjuiokpkihyugtrdfyguhijoiadsgyusadaa", seed) << std::endl;

    
    return 0;
}