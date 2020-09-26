x = linspace(0.2, 0.95, 16);
x_2 = [0.005, 0.01, 0.015, 0.020, 0.025, 0.030]
y_1 = [1.124999 1.166648 1.214299 1.269168 1.333242 1.409050 1.499916 1.611284 1.749853 1.928167 2.165954 2.496970 2.992333 3.817173 5.469014 10.428264]
y_2 = [32.647066 36.427701 42.274040 52.493409 74.885989 163.915399]

% x used SERVICE TIME=1 
% x_2 used SERVICE_TIME = 30

plot(x,y_1);
hold on
plot(x_2,y_2);
hold off
title("Arrival Rate vs Averaged Mean Delay 400122166");
xlabel("Arrival Rate");
ylabel("Averaged Mean Delay");

SERVICE_TIME = 1;
sum = 0
for i = [1:16]
    
    ARRIVAL_RATE = x(i);
    
    res = 0.5*SERVICE_TIME*(2-(SERVICE_TIME*ARRIVAL_RATE))/(1-(SERVICE_TIME*ARRIVAL_RATE))
    
    error = abs(100*(y_1(i)-res)/y_1(i));
    
    sum = sum + error
    disp(error);
    
    
end

average = sum/16
disp(average)

SERVICE_TIME = 30;
sum = 0
for i = [1:6]
    
    ARRIVAL_RATE = x_2(i);
    
    res = 0.5*SERVICE_TIME*(2-(SERVICE_TIME*ARRIVAL_RATE))/(1-(SERVICE_TIME*ARRIVAL_RATE))
    
    error = abs(100*(y_2(i)-res)/y_2(i));
    
    sum = sum + error
    disp(error);
    
    
end

average1 = sum/6
disp(average1)


%%%%% 

y_3 = [1.702717 1.694997 1.408554 0.614292 4732943.681495 1.365564 1067752.647292 59695734.826042 4635872.165987 1.300803 19175586.133777 12333048.569886 427007.180997 14607607.912565  19575866.559220 47636126.865886]; 

plot(x,y_3);
title("Averaged Mean Delay vs Arrival Rate (Exp. Distributed Service Times)");
xlabel("Arrival Rate");
ylabel("Averaged Mean Delay");