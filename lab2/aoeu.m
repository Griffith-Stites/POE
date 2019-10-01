hold on;
scatter(testRead, testDistance, 'filled')
scatter(analogRead, distance, 'filled')
fplot(@(x) 5805.99102955023*x^-1.03380467328515)
xlabel('Analog Read')
ylabel('Distance (in)')
xlim([150 500])