// załączenie bibliotek
#include <iostream>
#include <fstream>
#include <cmath>
#include <conio.h>
// deklaracje zasięgów
using namespace std;
// stałe w programie
#define h 0.001 // krok obliczeń
#define T 10.0 // całkowity czas symulacji – przedział [0 , T]
#define L 2.5 // liczba okresów sygnału sinus w przedziale T
#define M 8.0 // amplituda sygnału sinus
#define PI 3.14159265 // liczba PI
// pomocniczy typ – kolejne bajty danej ’double’
 typedef union { char c[sizeof(double)]; double d; } Box;
// zmienne globalne w programie
double u[(int)(1.0*T/h)+1]; // sygnał wejściowy
double u1p[(int)(1.0*T/h)+1]; // pierwsza pochodna sygnału wejściowego
double u2p[(int)(1.0*T/h)+1]; // druga pochodna sygnału wejściowego
double u3p[(int)(1.0*T/h)+1]; // trzecia pochodna sygnału wejściowego
double y[(int)(1.0*T/h)+1]; // sygnał wyjściowy
double y1p[(int)(1.0*T/h)+1]; // pierwsza pochodna sygnału wyjściowego
double y2p[(int)(1.0*T/h)+1]; // druga pochodna sygnału wyjściowego
double y3p[(int)(1.0*T/h)+1]; // trzecia pochodna sygnału wyjściowego
double y4p[(int)(1.0*T/h)+1]; // czwarta pochodna sygnału wyjściowego
Box z; // zmienna: pojedyncza wartość sygnału (u lub y)
// program główny
int main()
{
 int i,j,total;
 double a3,a2,a1,a0,b3,b2,b1,b0,w;
 // wczytanie parametrów modelu
 a3=0;//cout << "\n a3 = "; cin >> a3;
 a2=2;//cout << "\n a2 = "; cin >> a2;
 a1=1;//cout << "\n a1 = "; cin >> a1;
 a0=0;//cout << "\n a0 = "; cin >> a0;
 b3=0;//cout << "\n b3 = "; cin >> b3;
 b2=0;//cout << "\n b2 = "; cin >> b2;
 b1=0;//cout << "\n b1 = "; cin >> b1;
 b0=1;//cout << "\n b0 = "; cin >> b0;
 cout << "\n\n";
 total=sizeof(u)/sizeof(u[0]); // rozmiar wektorów danych
 w=2.0*PI*L/T; // częstotliwość sinusoidy
 for(i=0; i<total; i++) // sygnał wejściowy i jego pochodne
 {
 u[i]=M*sin(w*i*h); // sygnał wejściowy: u=M*sin(w*t) , t=i*h
 u1p[i]=M*w*cos(w*i*h); // pochodna 1: u’(t)
 u2p[i]=-M*w*w*sin(w*i*h); // pochodna 2: u’’(t)
 u3p[i]=-M*w*w*w*cos(w*i*h); // pochodna 3: u’’’(t)
 }
 y[0]=0; y1p[0]=0; y2p[0]=0; y3p[0]=0; // zerowe warunki początkowe
 for(i=0; i<total-1; i++) // główna pętla obliczeń
 {
 y4p[i]=-a3*y3p[i]-a2*y2p[i]-a1*y1p[i]-a0*y[i]+b3*u3p[i]+b2*u2p[i]+b1*u1p[i]+b0*u[i];
 y3p[i+1]=y3p[i]+h*y4p[i];
 y2p[i+1]=y2p[i]+h*y3p[i]+(h*h/2.0)*y4p[i];
 y1p[i+1]=y1p[i]+h*y2p[i]+(h*h/2.0)*y3p[i]+(h*h*h/6.0)*y4p[i];
 y[i+1]=y[i]+h*y1p[i]+(h*h/2.0)*y2p[i]+(h*h*h/6.0)*y3p[i]+(h*h*h*h/24.0)*y4p[i];
 }
 ofstream fileU("fileU.bin",ios::binary); // zapisanie wyników u(t) do pliku
 if (fileU.fail())
 {
 cout << "\n\n Saving u(t): error! Press a key ... \n\n";
 (void)getch();
 return(-1);
 }
for(i=0; i<total; i++)
    for(j=0, z.d=u[i]; j<sizeof(z); j++)
        fileU << z.c[j];
 fileU.close();
 
 ofstream fileY("fileY.bin",ios::binary); // zapisanie wyników y(t) do pliku
 if (fileY.fail())
 {
 cout << "\n\n Saving y(t): error! Press a key ... \n\n";
 (void)getch();
 return(-2);
 }
 for(i=0; i<total; i++)
    for(j=0, z.d=y[i]; j<sizeof(z); j++)
        fileY << z.c[j];
 fileY.close();
 
ofstream Y("Y.txt",ios::binary); // zapisanie wyników y(t) do pliku
 if (fileY.fail())
 {
 cout << "\n\n Saving y(t): error! Press a key ... \n\n";
 (void)getch();
 return(-2);
 }
 for(i=0; i<total; i++)
    for(j=0, z.d=y[i]; j<sizeof(z); j++)
        Y << y[i] << "\n";
 fileY.close();

 return(0);
} 