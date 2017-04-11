%Nathaniel Talbt
%GE 1502 Cornerstone of Engineering 2
%This program will create plots of weather and alcohol sensor data
%collected by the Mars Rover project

%read weather data from text file into array
weather = dlmread('WEATHER.TXT', '\t', 2,0);

%create figure windows for each plot
fig_alcohol = figure('Name', 'Alcohol Level');
fig_temp = figure('Name', 'Temperature');
fig_humid = figure('Name', 'Humidity');
fig_pressure = figure('Name', 'Pressure');
fig_light = figure('Name', 'Light');

%calcluate number of rows in the array, for the range
file_size = size(weather,1)

%create range from length of the file
x_range = linspace(10,10*file_size,file_size);

%plot alcohol level
figure(fig_alcohol);
plot(x_range, weather(:,1));
xlabel('Time(s)');
ylabel('Alcohol Level');
title('Alcohol Level');

%plot temperature
figure(fig_temp);
plot(x_range, weather(:,2));
xlabel('Time(s)');
ylabel('Temperature(F)');
title('Temperature');

%plot humidity
figure(fig_humid);
plot(x_range, weather(:,3));
xlabel('Time(s)');
ylabel('Humidity(% humid)');
title('Humidity');

%plot pressure
figure(fig_pressure);
plot(x_range, weather(:,4));
xlabel('Time(s)');
ylabel('Pressure (Pa)');
title('Pressure');

%plot light level
figure(fig_light);
plot(x_range, weather(:,5));
xlabel('Time(s)');
ylabel('Light level (V)');
title('Light Level');