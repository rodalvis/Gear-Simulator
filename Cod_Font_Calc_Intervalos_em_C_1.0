#include <stdio.h>
#include <math.h>
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
void main(){
	float II2MM =0;
	float result=0; 
		for(float MM =0.1; MM<= 4.0;MM+=0.1){
		result=roundf(600/(200/3.18*MM));
		printf("Para MM valor de MM:%f valor intervalo:%f\n",MM,result);
	}
		for(int II=5;II<=50;II++){
		II2MM =(25.4/II);
		result=roundf(600/(200/3.18*II2MM));
		printf("Para TPI valor de TPI:%d valor intervalo:%f\n",II,result);
	}

}
