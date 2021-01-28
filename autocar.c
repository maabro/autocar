// gcc autocar.c -o autocar
// autocar.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N_MAX 20
#define N_ASIENTOS 18
struct estructura_acciones{
	int nEntrada, nSalida, nTiquet, nConductor, nMarcha, nEntradaTotal, nAsientos, nCinturones; 
}accion = {
	0,0,0,0,0,0,0,0
};
void vContadores(){
	printf("\n");
	printf(" Han entrado un total de %d pasajeros.\n",accion.nEntradaTotal);
	printf(" En el autocar hay %d pasajeros.\n",accion.nEntrada);
	printf(" Han salido un total de %d pasajeros.\n",accion.nSalida);
	printf(" Han pagado %d tiquets.\n",accion.nTiquet);
	printf(" Hay %d de %d asientos ocupados.\n",accion.nAsientos,N_ASIENTOS);
	printf(" Hay %d de %d cinturones usados.\n",accion.nCinturones,N_ASIENTOS);
	if(accion.nConductor==1){
		printf(" El conductor esta sentado.\n\n");
	}else{
		printf(" El conductor no esta sentado.\n\n");
	}
	printf(" ----- ----- ----- ----- ----- -----\n");
	printf(" | A | | Q | | W | | P | | Z | | X |\n");
	printf(" ----- ----- ----- ----- ----- -----\n");
	printf(" ----- ----- ----- ----- ----- -----\n");
	printf(" | D | | R | | F | | V | | G | | B |\n");
	printf(" ----- ----- ----- ----- ----- -----\n");
	printf(" ----- ----- ----- ----- ----- -----\n");
	printf(" | Y | | H | | N | | U | | J | | O |\n");
	printf(" ----- ----- ----- ----- ----- -----\n\n");
	printf(" E : Entrada de pasajeros.\t T : Compra tiquet.\n ? : [A..O] Asientos pasajeros.\t ? : [a..o] Cinturones pasajeros.\n S : Salida de pasajeros.\t C : Conductor.\n M : Poner en marcha.\n\n");
	printf(" Selecciona un caracter: ");
}
void vEscrituraArchivo(){
	FILE *f;
	char output[128];
	// guarda el tiempo actual
	time_t tiempo = time(0);
	// pasa el tiempo actual al tiempo local con localtime
	struct tm *tlocal = localtime(&tiempo);
	if(accion.nMarcha == 1){
		f = fopen ("reporte.txt","a");
		// strftime transforma el tiempo en un string
		strftime(output,128,"FECHA: %d/%m/%y HORA: %H:%M:%S",tlocal);
		fprintf(f,"\n%s\n\n",output);
		fprintf(f,"Han entrado un total de %d pasajeros.\nHan salido un total de %d pasajeros.\nHan pagado %d tiquets.\nHay %d asientos ocupados.\nHay %d cinturones usados.\n\n",accion.nEntradaTotal,accion.nSalida,accion.nTiquet,accion.nAsientos,accion.nCinturones);
		if(accion.nEntrada > N_ASIENTOS){
			fprintf(f,"AVISO: Exceso de pasajeros.\n");	
		}
		if(accion.nAsientos > accion.nCinturones){
			fprintf(f,"AVISO: Hay pasajeros sin cinturon.\n");
		}
		if(accion.nEntrada > accion.nAsientos){
			fprintf(f,"AVISO: Hay pasajeros viajando de pie.\n");
		}
		if(accion.nEntradaTotal > accion.nTiquet){
			fprintf(f,"AVISO: Hay pasajeros sin pagar tiquet.\n");
		}
		if(accion.nEntradaTotal < accion.nTiquet){
			fprintf(f,"ERROR: Se han pagado tiquets de mas.\n");
		}
		if(accion.nCinturones > accion.nAsientos){
			fprintf(f,"ERROR: Sensor cinturon estropeado.\n");
		}
		if(accion.nConductor==0){
			fprintf(f,"ERROR: No hay conductor en el autocar.\n");
		}
	}
	fclose(f);
}
void vCalculos(char cSel){
	char szAsientos[N_MAX]="AQWPZXDRFVGBYHNUJO", szCinturones[N_MAX]="aqwpzxdrfvgbyhnujo";
	int i=0, j=0;
	if(accion.nAsientos < N_ASIENTOS){
		for(i=0;i<N_MAX;i++){
			if(cSel == szAsientos[i]){
				accion.nAsientos++;
			}	
		}
	}
	if(accion.nCinturones < N_ASIENTOS){
		for(j=0;j<N_MAX;j++){
			if(cSel == szCinturones[j]){
				accion.nCinturones++;
			}	
		}
	}
	if(cSel == 'E'){
		accion.nEntradaTotal++;
		accion.nEntrada++;
	}
	if(cSel == 'S'){
		if(accion.nEntrada == accion.nAsientos){
			accion.nAsientos--;
			accion.nCinturones--;
		}
		accion.nEntrada--;
		accion.nSalida++;		
	}
	if(cSel == 'C'){
		accion.nConductor=1;
	}
	if(cSel == 'T'){
		accion.nTiquet++;
	}	
	if (cSel == 'M'){
		accion.nMarcha = 1;
	}
}
int main(){
	char cEleccion;
	system("cls");
	do{
		vContadores();
		scanf(" %c",&cEleccion);
		system("cls");
		vCalculos(cEleccion);
	}while(accion.nMarcha == 0);	
	vEscrituraArchivo();	
	return 0;
}
