# Depict-It
Depict-It contains combination of the most basic and the most popular image processing algorithms.

![umbrella](https://user-images.githubusercontent.com/19840443/59093871-36e7f300-8915-11e9-8fde-61ad9d488b4b.gif)

## List of Commands
```-blur <matrix size>``` - blurs the image with given matrix size (Gaussian Blur Algorithm).<br>
```-brighten <level>``` - brightens the image with positive values (max 255) or dims it with negative values (min -255).<br>
```-reduce <n>``` - reduces image colors to the n to the power of 3 colors.<br>
```-contrast <level>``` - make image more contrast (positive values up to 255) or more smear (negative values down to -255).<br>
```-diffuse <n>``` - reduces to the n to the power of 3 colors with Floyd-Steinberg Error Diffusion.<br>
```-gamma <level>``` - produces so called gamma correction on image with given level.<br>
```-average``` - grays the image by averaging RGB channels of the image.<br>
```-luminance <r> <g> <b>``` - luminances the image, takes each ratio separetaly for each channel.<br>
```-desaturate``` - desaturates the image, converts RGB channel into HSL channels each divided by two.<br>
```-decompose <min/max>``` - decomposes the image by taking the smallest/greatest channel of each pixel.<br>
```-grayshade <number of shades>``` - grays the image determined by number of shades.<br>
```-invert``` - inverts RGB channels of the image.<br>
```-solarise <below/above> <threshold>``` - solarises the image up/down to given threshold.<br>
```-singechannel <r/g/b>``` - grays the image by single chosen RGB channel.<br>
<br>
**Example:** ```image.png -blur 8 -luminance 0.2 0.5 0.3``` - image.png will be blurred with Gaussian Kernel 8x8 then luminanced.<br>
## List of Helpful Articles
[Francis G. Loch Article](https://www.dfstudios.co.uk/articles/programming/image-programming-algorithms/image-processing-algorithms-part-1-finding-nearest-colour/)<br>
[Wikipedia Article](https://en.wikipedia.org/wiki/List_of_monochrome_and_RGB_palettes#6-bit_RGB)<br>
[Tanner Helland Article](http://www.tannerhelland.com/3643/grayscale-image-algorithm-vb6/)<br>
[What-When-How Article](http://what-when-how.com/introduction-to-video-and-image-processing/visual-effects-introduction-to-video-and-image-processing-part-1/)<br>
[Stack Overflow Gaussian Blur Question](https://stackoverflow.com/questions/1696113/how-do-i-gaussian-blur-an-image-without-using-any-in-built-gaussian-functions)<br>
[Stack Overflow Gaussian Kernel Question](https://stackoverflow.com/questions/8204645/implementing-gaussian-blur-how-to-calculate-convolution-matrix-kernel?noredirect=1&lq=1)<br>
