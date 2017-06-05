	# EE569 Homework Assignment #1
	# Date: 	02/05/2017
	# Name: 	Aakash Shanbhag
	# USC ID: 	3205699915
	# Email:	 adshanbh@usc.edu
	# 
	#Problem 3a:	Image Denoising
	# Compiled on 	Windows 07 Ultimate.(32 bit system) with Microsoft Visual Studio 2010.
 	#
	# Parameters and arguments to cmd: "program_name noisy_image.raw filtered_output_image.raw BytesPerPixel Size_h Size_w original_image type 	#								order_mask "	
	# 					
	# 
	# Example:	 ext.exe pepper_noisy.raw filtered.raw 3 512 512 pepper.raw 1 3
	#
	# program_name.exe=[agrv[0]]	executable file generated on compilation-ext.exe 
	# noisy_image=[agrv[1]]=	input noisy image in this case -
	# output_image=[agrv[2]]=	output image in this case -equalised.raw
	# BytesPerPixel=[agrv[3]]=	3 in case of RGB image.
	# Size_h=[agrv[4]]=		 Height of the input image=512
	# Size_w=[agrv[5]]= 		Width of the input image-512.
	# input.xls=[agrv[6]]=		Input  original image .
	# type=[agrv[7]]=	type of filter used= 1or 2 or .....12
	#.
	#		1.General Mean=Mask1
	#		2.Median filter.
	#		3. Mask 1 cascade Mask1
	#		4. Median cascade Median
	#		5. Mask 1 cascade Median
	#		6. Median cascade Mask1
	#		7. Mask1 cascade Mask1 cascade Mask1 cascade Mask1 cascade Mask1
	#		.8 Median cascade Median cascade Median  cascade Median cascade Median
	#		9. Mask 2 (Gaussian filter )
	#		10. Mask2 cascade Mask2
	#		11. Mask 2 cascade Median
	#		12. Median cascade Mask2
	#
	# Order_mask=[agrv[8]]= Size of the mask =3 or 5 or......any odd sized mask.
	