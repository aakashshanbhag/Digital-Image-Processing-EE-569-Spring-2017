-----------------------------------------------------------------------------------------------------------------------------------------------------------------
EE569 Homework Assignment #3 Prob2a
Date: March 26, 2017
Name : Aakash Shanbhag
ID : 3205699915
email : adshanbh@usc.edu
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
SYSTEM CONFIGURATION IN WHICH THIS CODE RAN:

OS: Windows 10 64-bit

Software: Visual Studio 2015 Community (Visual C++)

OpenCV version 3.2
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
STEPS TO DEBUG CODE:

1. Open "Developer Command Prompt for VS2015".

2. Go to the directory that has the .cpp and .h files using "cd" command.

3. To compile code and generate .obj type as below:
   "cl /EHsc <filename>.cpp /Fe<filename>.exe /I C:\OpenCV-3.2.0\opencv\build\include /link /LIBPATH:C:\OpenCV-3.2.0\opencv\build\x64\vc14\lib opencv_world320d.lib"

4. To run type the following in command prompt after doing a successful compilation in step-3:

<program_name> <inp_image> <out_image> <ImgWidth> <ImgHeight> <BytesPerPixel> <low_thresh> <high_thresh> <sigma>

program_name: the name of the .exe file generated
inp_image: the input image file with extension
out_image: the output image file with extension (.jpg or .png)
ImgWidth: Width of the input image
ImgHeight: Height of the input image
BytesPerPixel: bytes per pixel (for RGB = 3)
low_thresh: lower threshold for Canny Edge
high_thresh: higher threshold for Canny Edge
sigma: sigma value 
-----------------------------------------------------------------------------------------------------------------------------------------------------------------