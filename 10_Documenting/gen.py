import roman

roman_numbers = []
for i in range(0, 101):
    roman_numbers.append('"' + roman.toRoman(i) + '"')

print("{" + ",".join(roman_numbers) + "}")