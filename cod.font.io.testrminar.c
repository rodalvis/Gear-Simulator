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
int arred_ii(float n);
int arred_mm(float n);
void main(){
	int v_enc;
	char[]= fuso;
float v_fuso;	
	
	printf("Qual é a quantidade de pulsos por giro o seu Encoder Tem?");
		scanf(%d,v_enc);
	printf("O seu fuso é Milimetro ou Polegada?");
		scanf(%c,fuso);
	if(fuso==milimetro){v_fuso = 1.0;}
	else if(fuso==polegada){v_fuso = 3.18;}
	else{printf("digite milimetro ou polegada");}


	float II2MM =0;
	float result=0; 
		for(float MM =0.25; MM<= 3.50;MM+=0.25){
		result=arred_mm((v_enc/(200/v_fuso*MM)));
		result<=0 ? printf("") : printf("Para MMs:%f  Intervalo de Linhas:%f\n",MM,result);
	}
		for(int II=5;II<=52;II++){
		II2MM =(25.4/II);
		result=arred_ii((v_enc/(200/v_fuso*II2MM)));
		result<=0 ? printf("") : printf("Para TPIs:%d  Intervalo de Linhas:%f\n",II,result);
	}

	
}

int arred_mm(float n){
	int n_int = n;
		if(n - n_int <= 0.40){return n_int;}
		else if(n - n_int >=0.60){return n_int;}
		else return 0; 
	}
int arred_ii(float n){
	int n_int = n;
		if(n - n_int <= 0.30){return n_int;}
		else if(n - n_int >=0.85){return n_int;}
		else return 0; 
	}
