fileU=fopen('fileU.bin','r'); % tworzenie pliku dla sygnału u
if fileU == -1 % zbadanie poprawności identyfikatora
 error('Cannot open the file!') % komunikat o błędzie
end 
u=fread(fileU,Inf,'double'); % odczyt danych z pliku
fclose(fileU); % zamknięcie pliku
% Odczyt sygnału wyjściowego – plik został wcześniej utworzony


fileY=fopen('fileY.bin','r'); % tworzenie pliku dla sygnału y
if fileY == -1 % zbadanie poprawności identyfikatora
 error('Cannot open the file!') % komunikat o błędzie
end 
y=fread(fileY,Inf,'double'); % odczyt danych z pliku
fclose(fileY); % zamknięcie pliku

% Wspólne wykresy wejścia u i wyjścia y
T=10; % musi być znany całkowity czas symulacji
h=0.001; % musi być znany zastosowany krok symulacji
t=[0:h:T]'; % oś czasu
%plot(t,y,'r-')
%plot(t,u,'b-')
plot(t,u,'b-',t,y,'r-') % wejście na niebiesko, wyjście na czerwono
grid on % pokazanie siatki na wykresie
pause % oczekiwanie na dowolny klawisz
close % zamknięcie okna z wykresem
return 
