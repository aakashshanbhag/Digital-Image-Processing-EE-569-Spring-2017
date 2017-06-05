-----------------------------------------------------------------------------------------------------------------------------------------------------------------
EE569 Homework Assignment #3 Prob3a
Date: March 26, 2017
Name : Aakash Shanbhag
ID : 3205699915
email : adshanbh@usc.edu
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
STEPS TO DEBUG CODE:

Step 1: Downloading and Installing
1. Download OpenCV 3.2 from:  http://opencv.org/downloads.html
2. You can even download the opencv-master zip from:  https://github.com/Itseez/opencv
3. Download opencv_contrib zip from: https://github.com/itseez/opencv_contrib
4. Download and install Visual Studio 2015.
5. Download Cmake from: http://www.cmake.org/files/v3.6.3
6. Extract OpenCV 3.2 
7. If you downloaded the zip, extract it and rename the folder as opencv
8. Extract opencv_contrib. Choose which modules you want.

Step 2: Building and compiling
1. Go to the Opencv folder you extracted. There are two folders inside, ‘Build’ and ‘sources’. Delete everything inside the build folder. Copy everything from the ‘sources’ folder and paste it outside. Note: Opencv3 is the folder where I extracted opencv for this demonstration. You can extract it directly and it’ll save your folder as opencv by default.
2. If you extracted opencv-master, create a new folder build inside it.
3. Go to the opencv_contrib, from the ‘modules’ folder inside it, choose the modules you want and copy paste them in the Opencv ‘modules’ folder. 
4. Open Cmake. Browse source to the main folder you extracted Opencv 3.0 and browse build to the build folder inside it.
5. Click on config6. Click on configure
6. Wait for the analysis to be done.
7. After it’s done. Mark appropriate fields as show beure. It’ll open a new window to select the compiler. If you’re using VS 2015 choose ‘Visual Studio 14’
8. After you've marked everything, click Generate.
9. This will create an 'OpenCV.sln' file in your build folder. Open it with Visual Studio.
10. In the solution explorer, right click on ALL_BUILD and build. This will take time. Once it's built, change the build mode to RELEASE and repeat the same step 
11.After that, right click on INSTALL and build it, Once it's built, again change the build mode to DEBUG and repeat the same step. 
12. Everything will be created in the 'install' folder.


Step 3: Creating a system variable:
Variable name: OPENCV_BUILD
Value: C:\opencv3\build
Path: C:\opencv3\build\install\x86\vc14\bin and restart system

Step 4: Configuration for a sample project
1. Open Visual Studio and create a Console Application
2. Right click on the file and click properties
3. Choose Configuration Manager and add x64 platform if your system is x64 (only if your system is x64)
4. At configuration field, choose all configurations
5. At Configuration Properties -> C/C++ -> Additional Include Directories, add opencv include folders

Additional Include Directories:
C:\opencv3\build\install\include
C:\opencv3\build\install\include\opencv
C:\opencv3\build\install\include\opencv2

6. At Configuration Properties -> Linker -> Additional Library Directories, add opencv library folder


Additional Library Directories:
C:\opencv\build\install\x86\vc11\lib


7. At configuration field, choose Debug mode
8. At Configuration Properties -> Linker-> Additional dependencies -> add dependence libraries

Additional libraries:

opencv_calib3d300d.lib
opencv_core300d.lib
opencv_face300d.lib
opencv_features2d300d.lib
opencv_flann300d.lib
opencv_hal300d.lib
opencv_highgui300d.lib
opencv_imgcodecs300d.lib
opencv_imgproc300d.lib
opencv_ml300d.lib
opencv_objdetect300d.lib
opencv_photo300d.lib
opencv_shape300d.lib
opencv_stitching300d.lib
opencv_superres300d.lib
opencv_ts300d.lib
opencv_video300d.lib
opencv_videoio300d.lib
opencv_videostab300d.lib

Note: These libraries are in the folder- C:\opencv\build\install\x86\vc11\lib
and if you've installed extra modules you'll have to include those libraries as well. This list contains the default libs and the extra 'opencv_face300d.lib' from the face module. 

At configuration field, choose Release mode
At Configuration Properties -> Linker -> Additional dependencies -> add dependence libraries

Additional libraries
opencv_calib3d300.lib
opencv_core300.lib
opencv_face300.lib
opencv_features2d300.lib
opencv_flann300.lib
opencv_hal300.lib
opencv_highgui300.lib
opencv_imgcodecs300.lib
opencv_imgproc300.lib
opencv_ml300.lib
opencv_objdetect300.lib
opencv_photo300.lib
opencv_shape300.lib
opencv_stitching300.lib
opencv_superres300.lib
opencv_ts300.lib
opencv_video300.lib
opencv_videoio300.lib
opencv_videostab300.lib

Note: These libraries are in the folder- C:\opencv\build\install\x86\vc11\lib
Include extra libraries of the modules you've installed. 

Step 5: Build and Debug
Copy paste code to project in teh folders and build it and Debug.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------