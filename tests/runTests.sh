#!/bin/bash
# dit is wat er origineel stond (met dit werkte de awk commando niet): #!/usr/bin/env sh

# define output colors
GREEN="\e[92m"
RED="\e[31m"
BLUE="\e[36m"
EMPTY="\e[0m"

# define cleanup function
clean_up() {
  rm -r "executable" 2>/dev/null
  rm -r "executable_test" 2>/dev/null
  rm -r "test_datafiles" 2>/dev/null
  rm -r "output" 2>/dev/null
}

echo -e "${BLUE}Compiling code...${EMPTY}"

# test code
mkdir "executable_test" 2>/dev/null
cmake CMakeLists.txt -B "executable_test"
cd "executable_test" || exit 1
make
cd ..

# main code to use for testing
mkdir "executable" 2>/dev/null
cmake ../src/CMakeLists.txt -B "executable"
cd "executable" || exit 1
make
cd ..

echo -e "${BLUE}Running basic tests...${GREEN}"

cd "executable_test" || exit 1
./openseekmap_test
cd ..

echo -e "${BLUE}Prepare running advanced tests..."

echo -e "Generating data..."

mkdir "test_datafiles" 2>/dev/null
cd "test_datafiles" || exit 1

echo -e "Downloading data...${EMPTY}"
# get data
wget https://github.com/OSMNames/OSMNames/releases/download/v2.1.1/planet-latest_geonames.tsv.gz

echo -e "${BLUE}Extracting Belgium...${EMPTY}"
# extract belgium awk -F $'\t' 'BEGIN {OFS = FS} {if(NR!=1){if($16 =="be"){print}}else{print}}' | awk -F $'\t' 'BEGIN{OFS="\t"} {n=split($1,a,";");for(i=1;i<=n;i++){print($4,a[i],$9,$7,$8)}} $9 > 16 && $2 != "\"\"" && $2 ~ /^[A-Za-z ]*$/ {print($4,$2,$9,$7,$8)}'
zcat planet-latest_geonames.tsv.gz | awk -F $'\t' 'BEGIN {OFS=FS} {if(NR!=1){if($16 =="be"){print}}else{print}}' | awk -F $'\t' 'BEGIN{OFS="\t"} {n=split($1,a,";");for(i=1;i<=n;i++){print($4,a[i],$9,$7,$8)}} $9 > 16 && $2 != "\"\"" && $2 ~ /^[A-Za-z ]*$/ {print($4,$2,$9,$7,$8)}' | tail -n +2 > belgie.data

LINES=$(cat belgie.data | wc -l)

if [ "$LINES" -eq "0" ]; then
  echo -e "${RED}Extracting Belgium failed..."
  cd ..
  clean_up
  exit 3
fi

cd ..

mkdir "output" 2>/dev/null

cd "executable" || exit 1

echo -e "${BLUE}Starting advanced tests...${EMPTY}"

# Test: De Sterre Gent
# Doel: De Sterre Gent
echo -e "De Sterre Gent" | ./openseekmap ../test_datafiles/belgie.data >../output/output_de_sterre_gent
head -n 4 "../output/output_de_sterre_gent" >"../output/output_de_sterre_gent_parsed"
DIFF=$(diff "../output/output_de_sterre_gent_parsed" "../compare/de_sterre_gent.txt")
if [ "$DIFF" ]; then
  echo -e "${RED}Test Failed! Showing diff..."
  echo -e "${EMPTY}"
  echo -e "$DIFF"
  clean_up
  exit 2
fi

echo -e "${GREEN}Test 1 successful!${EMPTY}"

# Test: Zaventem
# Doel: Zaventem
echo -e "Zaventem" | ./openseekmap ../test_datafiles/belgie.data >../output/Zaventem
head -n 4 "../output/Zaventem" >"../output/Zaventem_parsed"
DIFF=$(diff "../output/Zaventem_parsed" "../compare/Zaventem.txt")
if [ "$DIFF" ]; then
  echo -e "${RED}Test Failed! Showing diff..."
  echo -e "${EMPTY}"
  echo -e "$DIFF"
  clean_up
  exit 2
fi

echo -e "${GREEN}Test 2 successful!${EMPTY}"

# Test: De Maaskuns Arendok
# Doel: De Maaskens Arendonk
echo -e "De Maaskuns Arendok" | ./openseekmap ../test_datafiles/belgie.data > ../output/De_Maaskuns_Arendok
head -n 4 "../output/De_Maaskuns_Arendok" >"../output/De_Maaskuns_Arendok_parsed"
DIFF=$(diff "../output/De_Maaskuns_Arendok_parsed" "../compare/De_Maaskuns_Arendok.txt")
if [ "$DIFF" ]; then
  echo -e "${RED}Test Failed! Showing diff..."
  echo -e "${EMPTY}"
  echo -e "$DIFF"
  clean_up
  exit 2
fi

echo -e "${GREEN}Test 3 successful!${EMPTY}"

# Test: HELDENPLIJN HIJST
# Doel: Heldenplein Heist
echo -e "HELDENPLIJN HIJST" | ./openseekmap ../test_datafiles/belgie.data > ../output/heldenplijn_hijst
head -n 4 "../output/heldenplijn_hijst" >"../output/heldenplijn_hijst_parsed"
DIFF=$(diff "../output/heldenplijn_hijst_parsed" "../compare/heldenplijn_hijst.txt")
if [ "$DIFF" ]; then
  echo -e "${RED}Test Failed! Showing diff..."
  echo -e "${EMPTY}"
  echo -e "$DIFF"
  clean_up
  exit 2
fi

echo -e "${GREEN}Test 4 successful!${EMPTY}"

# Test: éssésträät ampe
# Doel: Essestraat Impe
echo -e "éssésträät ampe" | ./openseekmap ../test_datafiles/belgie.data > ../output/essestraat_impe
head -n 4 "../output/essestraat_impe" >"../output/essestraat_impe_parsed"
DIFF=$(diff "../output/essestraat_impe_parsed" "../compare/essestraat_impe.txt")
if [ "$DIFF" ]; then
  echo -e "${RED}Test Failed! Showing diff..."
  echo -e "${EMPTY}"
  echo -e "$DIFF"
  clean_up
  exit 2
fi

echo -e "${GREEN}Test 5 successful!${EMPTY}"

# Test: De Sterre Gent (4x)
# Doel: De Sterre Gent -> de laatste
# shellcheck disable=SC2002
cat ../compare/test_multiple_lines.txt | ./openseekmap ../test_datafiles/belgie.data > ../output/test_multiple_lines
tail -n 21 "../output/test_multiple_lines" | head -n 4 >"../output/test_multiple_lines_parsed"
DIFF=$(diff "../output/test_multiple_lines_parsed" "../compare/de_sterre_gent.txt")
if [ "$DIFF" ]; then
  echo -e "${RED}Test Failed! Showing diff..."
  echo -e "${EMPTY}"
  echo -e "$DIFF"
  clean_up
  exit 2
fi

echo -e "${GREEN}Test 6 successful!${EMPTY}"

# Test: De Sterre
# Doel: De Sterre 51.302790 4.451600
echo -e "De Sterre" | ./openseekmap ../test_datafiles/belgie.data 51.302790 4.451600 > ../output/de_sterre_coordinaat1
head -n 4 "../output/de_sterre_coordinaat1" >"../output/de_sterre_coordinaat1_parsed"
DIFF=$(diff "../output/de_sterre_coordinaat1_parsed" "../compare/de_sterre_co1.txt")
if [ "$DIFF" ]; then
  echo -e "${RED}Test Failed! Showing diff..."
  echo -e "${EMPTY}"
  echo -e "$DIFF"
  clean_up
  exit 2
fi

echo -e "${GREEN}Test 7 successful!${EMPTY}"

# Test: De Sterre
# Doel: De Sterre 50.831550 3.308650
echo -e "De Sterre" | ./openseekmap ../test_datafiles/belgie.data 50.831550 3.308650 > ../output/de_sterre_coordinaat2
head -n 4 "../output/de_sterre_coordinaat2" >"../output/de_sterre_coordinaat2_parsed"
DIFF=$(diff "../output/de_sterre_coordinaat2_parsed" "../compare/de_sterre_co2.txt")
if [ "$DIFF" ]; then
  echo -e "${RED}Test Failed! Showing diff..."
  echo -e "${EMPTY}"
  echo -e "$DIFF"
  clean_up
  exit 2
fi

echo -e "${GREEN}Test 8 successful!${EMPTY}"

cd ..

echo -e "${GREEN}All advanced tests are successful"

echo -e "${BLUE}Cleanup datafiles & executables..."

# clean up all downloaded files
clean_up

echo -e "Done!"

exit 0
