#include <iostream>
#include <string>
#include <bitset>
#include <fstream>
#include <sstream>


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


std::string hash(std::string input){

    int seed = (input.length()%10)+9;
    input = wordToBinary(input);
    if (input.length() < 32){
        for(int i = 0; i<10; i++)
        input += input;
        input += "1011101";
    }

    int amount_of_1 = 0;
    int amount_of_0 = 0;
    for (int i=0; i<input.length(); i++){
        if (input[i] == '1')
        amount_of_1 += i;
        else amount_of_0 += i;
    }


 std::cout << "kiekis " << amount_of_1 << " " << amount_of_0 << std::endl;

    if (amount_of_1 < 0)
    amount_of_1 = amount_of_1*(-1);

    if (amount_of_0 < 0)
    amount_of_0 = amount_of_0*(-1);

    int bigger = ((amount_of_0 > amount_of_1) ? amount_of_0 : amount_of_1)*seed;
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
        // std::cout << "switching " << current << " with " << next_pos << std::endl; 

        input[next_pos] = temp;
        current = next_pos; 
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

    std::ifstream file("Input.txt");  
    std::ostringstream buffer;
    buffer << file.rdbuf(); 
    std::string input = buffer.str();

    // std::cout << input.length() << std::endl;
    // std::cout << hash("input") << std::endl;
    std::cout << hash("ciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupas") << std::endl;
    std::cout << hash("liaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupasciaupas") << std::endl;
    std::cout << hash("labas") << std::endl;
    std::cout << hash("lapas") << std::endl;

    
    return 0;
}