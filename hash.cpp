#include <iostream>
#include <string>
#include <bitset>
#include <fstream>
#include <sstream>
#include <chrono>   




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

    // std::cout << "input = " << input << std::endl;

    int seed = (input.length()%10)+1;
    input = wordToBinary(input);
    while (input.length() < 32){
        input += input;
        input += "1011101";
    }
    
    // std::cout << "input = " << input << std::endl;


    int amount_of_1 = 0;
    int amount_of_0 = 0;
    for (int i=0; i<input.length(); i++){
        if (input[i] == '1')
        amount_of_1 += i;
        else amount_of_0 += i;
    }

    if (amount_of_1 < 0)
    amount_of_1 *= -1;

    if (amount_of_0 < 0)
    amount_of_0 *= -1;


    // std::cout << "amount of 1, 0 = " << amount_of_1 << "    " << amount_of_0 << std::endl;


    int bigger = ((amount_of_0 > amount_of_1) ? amount_of_0 : amount_of_1)*seed;
    int smaller = ((amount_of_0 < amount_of_1) ? amount_of_0 : amount_of_1);
    if ((bigger % smaller) == 0)
        smaller++;

    // std::cout << "bigger, smaller = " << bigger << "    " << smaller << std::endl;


    if (bigger > 100000){
    bigger /= 10;
    smaller /= 10;
    }

    if (bigger > 100000){
        bigger /= (bigger/100000);
        smaller /= (smaller/100000);
    }
    //  std::cout << "bigger, smaller = " << bigger << "    " << smaller << std::endl;


    while (input.size() < 256){ 
        input += input;
    }

    int current = 0;
    for (int i=0; i<bigger; i++){
        // std::cout << "b" << std::endl;
        char temp = input[current];
        int next_pos = (current + smaller - i) % input.length();
        input[current] = input[next_pos];
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



    // Pavertus i binary, 256 bitai (nezinau ar labai reikalingas)
    std::string start = "qwertyuiopasdfghjklzxcvbnm945137";  
    start = wordToBinary(start);

    std::string Hashed = "";

    for (int i=0; i<256; i++){
        if (start[i] == input[i])
        Hashed += '1';
        else Hashed += '0';
    }

    return binaryToHex(Hashed);
}

void testFileForCollisions(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Could not open file: " << filename << "\n";
        return;
    }

    std::string line;
    int total = 0;
    int collisions = 0;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string a, b;
        iss >> a >> b;

        std::string ha = hash(a);
        std::string hb = hash(b);

        if (ha == hb) {
            collisions++;
        }
        total++;
        std::cout << total << std::endl;
        // std::cout << ha << std::endl;
        // std::cout << hb << std::endl;
    }

    std::cout << "File: " << filename << "\n";
    std::cout << "Total pairs: " << total << "\n";
    std::cout << "Collisions: " << collisions << "\n";
    std::cout << "Collision rate: "
              << (total > 0 ? (100.0 * collisions / total) : 0)
              << "%\n";
}

int main(int argc, char* argv[]){

    std::string input;
    if (argc > 1) {
        std::string filename = argv[1];
        std::ifstream file(filename);

    std::ostringstream buffer;
        std::string line;
        int count = 0;
        while (count < 128 && std::getline(file, line)) { //Cia galima nustatyt eiluciu skaiciu
            buffer << line << "\n";
            count++;
        }
    input = buffer.str();
    }
    else{
       std::cout << "Iveskite slaptazodi: ";  std::cin >> input;

    }
    // for (int i = 0; i < 100; i++)
    // std::cout << hash("azzzzzaaaaaads") << std::endl;
    testFileForCollisions("pairs_len1000.txt");

    // -------------LAIKO TESTAS------------------

    // auto start = std::chrono::high_resolution_clock::now();

    // for (int i=0; i<10; i++){
    // std::cout <<"a" << std::endl;
    // hash(input);
    // }

    //  auto end = std::chrono::high_resolution_clock::now();
    // std::cout << hash(input) << std::endl;
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    // std::cout << "Elapsed time: " << duration.count()/10.0 << " ms" << std::endl;
    return 0;
}
