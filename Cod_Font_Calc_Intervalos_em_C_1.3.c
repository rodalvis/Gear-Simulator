#include <stdio.h>

/*
--25.4 / TPI = Metric Pitch
--25.4 / Metric Pitch = TPI
--Inches x 25.4 = mm
--mm / 25.4 = Inches
*/
//Pelles C 64 bits
//teste de calculo de proporção entre eixo arvore e fuso.
//intervalo do encoder para cada pulso do stepper.
//exemplo: 3 intervalos para 1 passo para obter 3mm de rosca.

#define tam(vet) (sizeof((vet)) / sizeof(int))			//macro

void main(){

	float rosc_mm[] = {0.25,0.50,0.85,1.0,1.25,1.75,2.0};
	int rosc_ii[] ={8,9,10,11,12,13,14,15,16,17,18,19,20};

		for(int i =0 ; i<tam(rosc_mm);i++){
		printf("Rosca Milimetro MM: %f \t Espacos: %f \n",rosc_mm[i],(1200/(200/(3.18*rosc_mm[i]))));
	}

		for(int i =0 ; i<tam(rosc_ii);i++){
		printf("Rosca Polegada TPI: %d \t Espacos: %f \n",rosc_ii[i],(1200/(200/(3.18*(25.4/rosc_ii[i])))));

		}
system("pause");
	}

	


