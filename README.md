Pagrindinis veikimo principas:

1. Input - bet kokio dydžio "string"
2. Papildomos funkcijos - wordToBinary ir binaryToHex - keičia stringo tipą į dvejetainį skaičių/dvejetainį skaičių keičia į šešioliktainį
3. Kintamieji (amount_of_1, amount_of_0) yra apskaičiuojami taip:
  3.1 Skaitomas pradinis stringas, kuris yra paverstas į dvejetainį skaičių (tarkim, 11000110)
  3.2 Iš skaičiuos yra suskaičiuojami vienetai ir nuliai įvertinant jų poziciją (Tarkim, vienetai būtų 1*0+1*1+1*6+1*7)
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
