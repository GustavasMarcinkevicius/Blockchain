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

    int seed = (input.length()%10)+9;
    input = wordToBinary(input);
    while (input.length() < 32){
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

    if (amount_of_1 < 0)
    amount_of_1 *= -1;

    if (amount_of_0 < 0)
    amount_of_0 *= -1;


    // std::cout << "amount of 1, 0 = " << amount_of_1 << "    " << amount_of_0 << std::endl;


    int bigger = ((amount_of_0 > amount_of_1) ? amount_of_0 : amount_of_1)*seed;
    int smaller = ((amount_of_0 < amount_of_1) ? amount_of_0 : amount_of_1);
    if ((bigger % smaller) == 0)
        smaller++;

    
    if (bigger < 0)
    bigger *= -1;

    if (smaller < 0)
    smaller *= -1;



    if (bigger > 100000){

        bigger = bigger%1000000 + 1000000;
        smaller = smaller%1000000 + 100000;

    }

    // std::cout << "bigger = " << bigger << " smaller = " << smaller << std::endl;

    while (input.size() < 256){ 
        input += input;
    }

    auto start = std::chrono::high_resolution_clock::now();
    int current = 0;
    for (int i=0; i<bigger; i++){
        // std::cout << "b" << std::endl;
        char temp = input[current];
        int next_pos = (current + smaller - i) % input.length();
        // std::cout << "current = " << current  << " next = " << next_pos << std::endl;
        input[current] = input[next_pos];
        input[next_pos] = temp;
        current = next_pos; 
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    // std::cout << "duration of first loop " << duration.count() << "ms" << std::endl;



    input = binaryToHex(input);
    input = wordToBinary(input);

    current = 0;
    for (int i=0; i<bigger; i++){
    char temp = input[current];
    int next_pos = (current + smaller - i) % input.length();
    input[current] = input[next_pos];
    input[next_pos] = temp;
    current = next_pos; 
    }


    std::string Hashed(256, '\0');
    for(int i=0; i<256; i++){
    Hashed[i] = input[i];
    }

    return binaryToHex(Hashed);
    // return Hashed;
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


void testFileForAvalanche(const std::string& filename){
    std::ifstream file(filename);
    std::string line;
    double Skirtingumai[100000];

    double MinSkirtingumas = 100;
    double MaxSkirtingumas = 0;
    int counter = 0;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string a, b;
        iss >> a >> b;

        std::string ha = hash(a);
        std::string hb = hash(b);

        //Tikrinimas hexu lygmeniu
        int counterHEX = 0;
        for(int i=0; i<64; i++){
            if (ha[i] != hb[i])
            counterHEX++;
        }

        //TIKRINIMAS binary lygmeniu (reikia originalioj hash funkcijoj nevers i hex returninant)

        // int counterBINARY = 0;
        // for(int i=0; i<256; i++){
        //     if (ha[i] != hb[i])
        //     counterBINARY++;
        // }


        double skirtingumas = counterHEX/64.0*100; // NAUDOTI SITA NORINT MATUOTI HEX
        // double skirtingumas = counterBINARY/256.0*100; //NAUDOTI SITA NORINT MATUOTI BINARY

        if(skirtingumas < MinSkirtingumas)
        MinSkirtingumas = skirtingumas;

        else if(skirtingumas > MaxSkirtingumas)
        MaxSkirtingumas = skirtingumas;
        Skirtingumai[counter] = skirtingumas;
        counter++;
        std::cout << counter << std::endl;
    }

    std::cout << "max skirtingumas = " << MaxSkirtingumas << "%" << std::endl;
    std::cout << "min skirtingumas = " << MinSkirtingumas << "%" << std::endl;
    
    int sum = 0;
    for(int i=0; i<100000; i++){
        sum += Skirtingumai[i];
    }
    std::cout << "vidutinis skirtingumas = " << sum/100000 << "%" << std::endl;
}

int main(int argc, char* argv[]){

    std::string input;
    if (argc > 1) {
        std::string filename = argv[1];
        std::ifstream file(filename);

    std::ostringstream buffer;
        std::string line;
        int count = 0;
        while (count < 512 && std::getline(file, line)) { //Cia galima nustatyt eiluciu skaiciu
            buffer << line << "\n";
            count++;
        }
    input = buffer.str();
    }
    else{
       std::cout << "Iveskite slaptazodi: ";  std::cin >> input;

    }


    // testFileForAvalanche("pairs.txt");
    // testFileForCollisions("pairs_len1000.txt");

    // -------------LAIKO TESTAS------------------

    auto start = std::chrono::high_resolution_clock::now();
    // std::cout << input << std::endl;
    for (int i=0; i<10; i++){
    hash(input);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << hash(input) << std::endl;
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Elapsed time: " << duration.count()/10.0 << " ms" << std::endl;
    return 0;
}
