%constants 
L = 1; 
nelem = 100; % length of rod
nnode = 100; % number of elements
nnode = nelem - 1; % number of nodes
del_x = L/nelem; %delta x
k = 10; % heat conductivity
rho = 10; %density 
Cp = 420; 
T_o = 20; %initial temp
t_end = 70; %end temp

t = 7200*2; % number of seconds to do timesteps for 
time_steps = 500; %number of time steps
del_t = t/(time_steps - 1); %delta t

% basis functions
syms h1(r);
h1(r) = 0.5*(1-r);
syms h2(r);
h2(r) = 0.5*(1+r);

% Setting up [A][t] = [B][S]
% A matrix for each element
a =[-2*int(diff(h1)*diff(h1),[-1,1]) -2*int(diff(h1)*diff(h2),[-1,1]);
    -2*int(diff(h2)*diff(h1),[-1,1]) -2*int(diff(h2)*diff(h2),[-1,1])]

% B matrix for each element
b = [int(h1*h1,[-1,1]) int(h1*h2,[-1,1]);
int(h2*h1,[-1,1]) int(h2*h2,[-1,1])]

A = spalloc (nelem, nelem, nelem^2);
B = spalloc(nelem, nelem, nelem^2);

% Matrix assemblage
for i = 1:nelem-1
A(i,i) = A(i,i) + a(1,1);
A(i,i+1) = A(i,i+1) + a(1,2);
A(i+1,i) = A(i+1,i) + a(2,1);
A(i+1,i+1) = A(i+1,i+1) + a(2,2);
B(i,i) + B(i,i) + b(1,1);
B(i,i+1) = B(i,i+1) + b(1,2);
B(i+1,i) = B(i+1,i) + b(2,1);
B(i+1,i+1) = B(i+1,i+1) + b(2,2);
end

%setting up source term 
S = zeros(nelem,1); 
for i = 1:nelem
    for j = 1:time_steps
        S(i,j) = sin(pi*i/nelem); 
    end
end

% Time marching
% Euler - forward method
T = linspace(T_o, T_end, nelem);
T = T';
for i = 1:time_steps
    if mod((i-1),(time_steps/10)) == 0
        plot(linspace(0,L,nelem),T)
    end
    hold on
    T_n = del_t*k/(Cp*rho*del_x)*(A*T+del_x*B*S(:,i))+T;
    T = T_n;
    % boundary conditions
    T(1) = T_o;
    T(end) = T_end;
end

% Graph properties
xlabel('Length')
ylabel('Temperature')
set(gca,'FontSize',15)
% Plot the source
hold on
yyaxis right
plot(linspace(0,L,nelem),S(:,1),'-.','LineWidth',5)
ylabel('Steady Heat Source [W/m^2]')

%% Plot the transient source surface
[X,Y] = meshgrid(linspace(0,t,time_steps),linspace(0,L,nelem));
s = surf(X,Y,S);
xlabel('Time')
ylabel('Length')
zlabel('Heat Flux')
title('Constant Source')
set(gca,'FontSize',15)
s.EdgeColor = 'none';

