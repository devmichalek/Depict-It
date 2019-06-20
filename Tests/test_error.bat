@echo off
rem This test should generate errors

rem Make copy of image "input.png"
Depict-It.exe input.png -average in.png

>result_error.txt (
Depict-It.exe
Depict-It.exe not_existing_image.png -average
Depict-It.exe in.png -blur -1
Depict-It.exe in.png -diffuse -1
Depict-It.exe in.png -grayshade -1
Depict-It.exe in.png -pixelate -1
Depict-It.exe in.png -reduce -1
Depict-It.exe in.png -solarise -1
Depict-It.exe in.png -solarise -1 min
Depict-It.exe in.png -luminance -0.1 0.1 0.1
Depict-It.exe in.png -luminance 0.1 -0.1 0.1
Depict-It.exe in.png -luminance 0.1 0.1 -0.1
Depict-It.exe in.png -pixelate 999999
Depict-It.exe in.png -singlechannel x
)