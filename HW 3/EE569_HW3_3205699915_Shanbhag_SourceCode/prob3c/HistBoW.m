clc;
clear all;
close all;

suv = dlmread('hist_suv.txt');
truck = dlmread('hist_truck.txt');
c1 = dlmread('hist_c1.txt');
c2 = dlmread('hist_c2.txt');

e1 = sum(abs(c2 - suv)) / 8;
e2 = sum(abs(c2 - truck)) / 8;
e3 = sum(abs(c2 - c1)) / 8;

subplot(2,2,1);
bar(suv);
xlabel('Number of bins');
ylabel('Frequency');
title('Histogram SUV');

subplot(2,2,2);
bar(truck);
xlabel('Number of bins');
ylabel('Frequency');
title('Histogram Truck');

subplot(2,2,3);
bar(c1);
xlabel('Number of bins');
ylabel('Frequency');
title('Histogram Convertible1');

subplot(2,2,4);
bar(c2);
xlabel('Number of bins');
ylabel('Frequency');
title('Histogram Convertible2');