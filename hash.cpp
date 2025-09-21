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

    int bigger = ((amount_of_0 > amount_of_1) ? amount_of_0 : amount_of_1)*seed;
    int smaller = ((amount_of_0 < amount_of_1) ? amount_of_0 : amount_of_1)*seed;
    // std::cout << bigger << " " << smaller << std::endl;
    // std::cout << "amount of 1, 0:   " << amount_of_1 << "   " << amount_of_0 << std::endl;

    std::cout << input << std::endl;


    for (int i=0; i<smaller; i++){
        int current = 0;
        char temp = input[current];
        int next_pos = (current + bigger - i) % input.length();
        input[current] = input[next_pos];
        input[next_pos] = temp;
        current = next_pos; 
        // std::cout << input << std::endl;
    }
    std::cout << input << std::endl;

    // Pavertus i binary, 256 1 ir 0
    std::string Hashed = "qwertyuiopasdfghjklzxcvbnm945137";  
    Hashed = wordToBinary(Hashed);


    return Hashed;
}

int main(){

    int seed = 10;
    std::string input = "labaa";
    hash(input, seed);
    std::cout << binaryToHex("1100011000010110001001100001011000010110");
    
    // std::cout << hash(input) << std::endl;
    return 0;
}