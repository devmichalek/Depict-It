![umbrella](https://user-images.githubusercontent.com/19840443/59093871-36e7f300-8915-11e9-8fde-61ad9d488b4b.gif)

### Depict-It - List of Commands
```-average``` - grays the image by averaging RGB channels of the image.<br>
```-blur <matrix size>``` - blurs the image with given matrix size (Gaussian Blur Algorithm).<br>
```-brighten <level>``` - brightens the image with positive values (max 255) or dims it with negative values (min -255).<br>
```-contrast <level>``` - makes image more contrast (positive values up to 255) or smears it (negative values down to -255).<br>
```-decompose <min/max>``` - decomposes the image by taking the smallest/greatest channel of each pixel.<br>
```-desaturate``` - desaturates the image, converts RGB channel into HSL channels each divided by two.<br>
```-diffuse <n>``` - reduces to the n to the power of 3 colors with Floyd-Steinberg Error Diffusion.<br>
```-gamma <ratio>``` - produces gamma correction on image with given level.<br>
```-grayshade <number of shades>``` - grays the image determined by number of shades.<br>
```-invert``` - inverts RGB channels of the image.<br>
```-luminance <r> <g> <b>``` - luminances the image, takes each ratio separetaly for each channel.<br>
```-pixelate <chunk size>``` - cuts image into smaller chunks defined by chunk size.<br>
```-reduce <n>``` - reduces image colors to the n to the power of 3 colors.<br>
```-singechannel <r/g/b>``` - grays the image by chosen RGB channel.<br>
```-solarise <threshold> <below/above>``` - solarises the image above/below to the given threshold.<br>

### Depict-It - Syntax & Examples:
```<executable name> <input.png> <commands> <output.png>``` - notice that *output.png* is optional but other arguments are required for program to run correctly without errors.<br>
```image.png -blur 8 -luminance 0.2 0.5 0.3``` - *image.png* will be blurred with Gaussian Kernel 8x8 then luminanced.<br>
```in.png -decompose max -solarise 128 below out.png``` - *in.png* will be decomposed with max function then solarised (each pixel below 128) then *out.png* will be produced.<br>
```picture.png -gamma 1.25``` - *picture.png* will be converted with gamma conversion algorithm with ratio 1.25.<br>
### List of Used Articles
[Francis G. Loch Article](https://www.dfstudios.co.uk/articles/programming/image-programming-algorithms/image-processing-algorithms-part-1-finding-nearest-colour/)<br>
[Wikipedia Article](https://en.wikipedia.org/wiki/List_of_monochrome_and_RGB_palettes#6-bit_RGB)<br>
[Tanner Helland Article](http://www.tannerhelland.com/3643/grayscale-image-algorithm-vb6/)<br>
[What-When-How Article](http://what-when-how.com/introduction-to-video-and-image-processing/visual-effects-introduction-to-video-and-image-processing-part-1/)<br>
[Stack Overflow Gaussian Blur Question](https://stackoverflow.com/questions/1696113/how-do-i-gaussian-blur-an-image-without-using-any-in-built-gaussian-functions)<br>
[Stack Overflow Gaussian Kernel Question](https://stackoverflow.com/questions/8204645/implementing-gaussian-blur-how-to-calculate-convolution-matrix-kernel?noredirect=1&lq=1)<br>

### Download (Windows)
[Download for Windows 32-bit](https://drive.google.com/file/d/1wyyEONVl6dDCPuGYEisqbPVoYZkxizhw/view?usp=sharing)<br>
[Download for Windows 64-bit](https://drive.google.com/file/d/1vqi_KwDD3qkyD0s-7CD6nSvdfpYu4eR1/view?usp=sharing)<br>
### Depict-It - Buiding on Linux
```sh
# Generate parser & lexer
bison -b Generated/parser -d "Bison Flex/parser.y"
flex -o Generated/lexer.c "Bison Flex/lexer.l"
# Generate objects
gcc -I "Header Files" -c Generated/parser.tab.c Generated/lexer.c
gcc -I "Header Files" -c "Source Files/lodepng.c" "Source Files/image.c" "Source Files/process.c" "Source Files/semantic.c" "Source Files/main.c"
# Create executable
gcc parser.tab.o lexer.o lodepng.o image.o process.o semantic.o main.o -lm -o Depict-It
# Run executable
./Depict-It
```
