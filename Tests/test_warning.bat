@echo off

rem Make copy of image "input.png"
Depict-It.exe input.png -average in.png

>result_warning.txt (
rem This test should generate warnings

rem Warning: Max asis size for Blur algorithm is 20. Asis will be truncated...
Depict-It.exe in.png -blur 1000

rem Warning: Min brightness level is -255. Brightness level will be truncated...
Depict-It.exe in.png -brighten -2000

rem Warning: Max brightness level is 255. Brightness level will be truncated...
Depict-It.exe in.png -brighten 2000

rem Warning: Min contrast level is -255. Contrast level will be truncated...
Depict-It.exe in.png -contrast -55555

rem Warning: Max contrast level is 255. Contrast level will be truncated...
Depict-It.exe in.png -contrast 55555

rem Warning: Function name for Decompose algorithm is not set... choosing min function
Depict-It.exe in.png -decompose

rem Warning: Function name for Decompose algorithm is not properly set... choosing min function
Depict-It.exe in.png -decompose something_wrong

rem Warning: Max number of colors for Diffuse algortihm is 12 (to the power of 3)...
Depict-It.exe in.png -diffuse 13

rem Warning: Gamma correction algorithm takes only positive floating-point numbers...
Depict-It.exe in.png -gamma -13.25

rem Warning: Gamma correction algorithm max floating-point number is 8.0, reducing...
Depict-It.exe in.png -gamma 9.00

rem Warning: Increasing number of shades for Grayshade algorithm to 2...
Depict-It.exe in.png -grayshade 1

rem Warning: Max number of shades for Grayshade algorithm is 255, reducing number of shades...
Depict-It.exe in.png -grayshade 256

rem Warning: Luminancing image, red ratio's max value is 1.0, reducing red channel...
Depict-It.exe in.png -luminance 1.1 0.9 0.9

rem Warning: Luminancing image, green ratio's max value is 1.0, reducing green channel...
Depict-It.exe in.png -luminance 1.0 1.1 0.9

rem Warning: Luminancing image, blue ratio's max value is 1.0, reducing blue channel...
Depict-It.exe in.png -luminance 0.1 0.9 1.1

rem Warning: Min pixel size for Pixelate algorithm is 2, increasing pixel size to 2...
Depict-It.exe in.png -pixelate 1

rem Warning: Max number of colors for Reduce algortihm is 15 (to the power of 3)...
Depict-It.exe in.png -reduce 16

rem Warning: Threshold is too great for Solarise algorithm, reducing threshold...
Depict-It.exe in.png -solarise 256 above

rem Warning: Function name for Solarise algorithm is not set... choosing below function
Depict-It.exe in.png -solarise 88

rem Warning: Function name for Solarise algorithm is not properly set... choosing below function
Depict-It.exe in.png -solarise 88 something_wrong
)