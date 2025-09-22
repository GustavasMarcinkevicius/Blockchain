Pagrindinis veikimo principas:

1. Input - bet kokio dydžio "string"
2. Papildomos funkcijos - wordToBinary ir binaryToHex - keičia stringo tipą į dvejetainį skaičių/dvejetainį skaičių keičia į šešioliktainį
3. Kintamieji (amount_of_1, amount_of_0) yra apskaičiuojami taip:

      3.1 Skaitomas pradinis stringas, kuris yra paverstas į dvejetainį skaičių (tarkim, 11000110)

      3.2 Iš skaičiuos yra suskaičiuojami vienetai ir nuliai įvertinant jų poziciją (Tarkim, vienetai būtų 1x0+1x1+1x6+1x7)

4. Iš šių dviejų skaičių yra surandamas didesnis (int bigger) ir mažesnis (int smaller)
5. Didesnis skaičius yra padauginamas iš seed, kuris yra apskaičiuojamas: int seed = (input.length()%10)+9;
6. Prasideda FOR loop'as: (vyksta bitų permaišymas pagal bigger, smaller ir i vertes)
    for (int i=0; i<smaller; i++){
    char temp = input[current];
    int next_pos = (current + bigger - i) % input.length();
    input[current] = input[next_pos];
    input[next_pos] = temp;
    current = next_pos; 
    }
7. Galiausiai vyksta AND bitų operacija su const stringu (std::string start = "qwertyuiopasdfghjklzxcvbnm945137";)  (jeigu pradinis string per trumpas, jis yra pratęsiamas jį kartojant)
8. Galutinis dvejetainis kodas yra paverčiamas šešioliktainiu.


KAI INPUT'AS YRA VIENAS SIMBOLIS:

<img width="632" height="366" alt="image" src="https://github.com/user-attachments/assets/b39a8c4b-5541-4d28-8d84-f9717cad45bc" />


LAIKO TESTAS:

<img width="751" height="452" alt="image" src="https://github.com/user-attachments/assets/c5021403-b696-4794-a161-ca0a6366d6e4" />


COLLISION TESTAS:

File: pairs_len10.txt

Total pairs: 100000

Collisions: 0

Collision rate: 0%



COLLISION TESTAS:

File: pairs_len10.txt  
Total pairs: 100000  
Collisions: 0  
Collision rate: 0%  

File: pairs_len100.txt  
Total pairs: 100000  
Collisions: 0  
Collision rate: 0%  

File: pairs_len500.txt  
Total pairs: 100000  
Collisions: 0  
Collision rate: 0%  

File: pairs_len500.txt  
Total pairs: 100000  
Collisions: 0  
Collision rate: 0%  





