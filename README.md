# Pagrindinis veikimo principas:

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

7. Įvykdoma:
   input = binaryToHex(input);
   input = wordToBinary(input);

   (Kadangi Hex kodas yra skaitomas kaip paprastas string, bitai persistumdo)

8. Kartojamas For loop'as
9. Galutinis dvejetainis kodas yra paverčiamas šešioliktainiu.(esant reikalui, galima neverst)  
   \*Kode taip pat yra papildomų if salygų, kad kodo veikimo laikas neartėtų link begalybės

# KAI INPUT'AS YRA VIENAS SIMBOLIS (pirmi du vienodi siekiant parodyt, kad vienodas inputas grąžina vienodą outputą):

<img width="687" height="279" alt="image" src="https://github.com/user-attachments/assets/9dad4907-9554-4cca-b9cc-5d50116304b3" />

# LAIKO TESTAS:

<img width="754" height="448" alt="image" src="https://github.com/user-attachments/assets/0aed5f57-413c-49d0-9425-47b1ca35983b" />

# COLLISION TESTAS:

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

COLLISION TESTAS (AI)   
File: pairs_len10.txt  
Total pairs: 100000  
Collisions: 0  
Collision rate: 0%  

COLLISION TESTAS (SHA-256)  
File: pairs_len10.txt  
Total pairs: 100000  
Collisions: 0  
Collision rate: 0%  

# LAVINOS EFEKTAS

LAVINOS EFEKTAS(HEX)  
max skirtingumas = 100%  
min skirtingumas = 1.5625%  
vidutinis skirtingumas = 89%

LAVINOS EFEKTAS(HEX)(AI)  
max skirtingumas = 100%  
min skirtingumas = 1.5625%  
vidutinis skirtingumas = 76%

LAVINOS EFEKTAS(BINARY)  
max skirtingumas = 62.1094%  
min skirtingumas = 0.390625%  
vidutinis skirtingumas = 45%

LAVINOS EFEKTAS(BINARY)(AI)  
max skirtingumas = 58.9844%  
min skirtingumas = 0.390625%  
vidutinis skirtingumas = 35%  

LAVINOS EFEKTAS(HEX)(SHA-256)   
max skirtingumas = 100%  
min skirtingumas = 76.5625%  
vidutinis skirtingumas = 93%  


# IŠVADOS:


Mano pradinė kurta versija v0.1x, palyginus su kitom, yra gera: Collision testuose, Lavinos efekte, tačiau veikia ganėtinai lėtai  

Paprašius AI mano sukurtą hashą patobulinti ir sukurti versiją v0.2x, ji patapo: tokia pati gera collision testuose, šiek tiek prastesnė Lavinos efekte, drastiškai sulėtėjo kai inputas yra mažas, tačiau labai pagreitėjo kai inputas yra didelis  

SHA-256: Pati geriausia versija, nenusileidžianti nei vienoje srityje (išskyrus lygiąsias collision teste)  
