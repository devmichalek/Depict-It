@echo off
rem This test should generate <n> images result_<n>.png

>result_success.txt (
Depict-It.exe input.png -average result_00_average.png
Depict-It.exe input.png -blur 2 result_01_blur_2.png
Depict-It.exe input.png -brighten 45 result_02_brighten_45.png
Depict-It.exe input.png -contrast -20 result_03_contrast_20.png
Depict-It.exe input.png -decompose min result_04_decompose_min.png
Depict-It.exe input.png -desaturate result_05_desaturate.png
Depict-It.exe input.png -diffuse 2 result_06_diffuse_2.png
Depict-It.exe input.png -gamma 1.25 result_07_gamma_125.png
Depict-It.exe input.png -grayshade 12 result_08_grayshade_12.png
Depict-It.exe input.png -invert result_09_invert.png
Depict-It.exe input.png -luminance 0.22 0.7 0.14 result_10_luminance_022_07_014.png
Depict-It.exe input.png -pixelate 10 result_11_pixelate_10.png
Depict-It.exe input.png -reduce 5 result_12_reduce_5.png
Depict-It.exe input.png -singlechannel g result_13_singlechannel_g.png
Depict-It.exe input.png -solarise 45 above result_14_solarise_45_above.png

Depict-It.exe input.png -average -reduce 2 result_15_average_reduce_2.png
Depict-It.exe input.png -singlechannel r -pixelate 5 result_16_singlechannel_r_pixelate_5.png
Depict-It.exe input.png -gamma 2.00 -invert -diffuse 2 result_17_gamma_200_invert_diffuse_2.png
)