#include<iostream>
#include<fstream>

using namespace std;

const int dimp=5;

int main(){
	//variables
	const int dimc=8;
	
	string cliente[dimc]; //nombre de clientes
	string producto[dimp]; //nombre de productos
	
	float totalkg[dimc][dimp]={},totalkm[dimc][dimp]={}; //suma de kg y km por cliente y producto
	
	int cte_conmaxprod=0,superar=13000; //cod de cliente que tiene max cant de prod,cantidad de kg a superar
	int cantprod[dimc]={},entregas_xprod[dimp]={},poskm[dimp]={}; //cantidad de productos por cliente y entregas por productos; posicion del orden asc de km
	
	void idclientemaxprod(int cp[],int dimc,int& idcl); //Busca el codigo de cliente con mas cant de prod
	void ordenar_km(int ikm[],float tkm[][dimp],int dimc,int idcl); //ordena el vector de posiciones de km
	void imprimir_kmorden(string prod[],int ikm[],float tkm[][dimp],int dimc,int idcl,string cte[]); //imprime el km en orden asc
	void imp_productoMax_km(int ikm[],string prod[],int e_xprod[]); //muestra la cantidad de productos que tuvo el prod con mas km
	
	ifstream archilec; //variable donde se lee el archivo
	
	//abrir archivo Nombres
	archilec.open("Nombres.txt");
	//compruebo que abre
	if (!archilec) {
 		cout << "Error al abrir el archivo" << endl;
 		return 1;
 	}
 	
	 //cargo los clientes 
	for(int i=0;i<dimc && archilec>>cliente[i];++i);
	//cargo los productos
	for(int i=0;i<dimp && archilec>>producto[i];++i);
	
	//cierro el archivo Nombres
	archilec.close();
	
	//abrir archivo Datos
	archilec.open("Datos.txt");
	//compruebo que abre
	if (!archilec) {
 		cout << "Error al abrir el archivo" << endl;
 		return 1;
 	}
 	
 	int icl,iprod; //variables que guardan el cod de cliente y prod leidos del archivo
 	float kg,km; //variables que guardan los kg y km que leen del archivo
 	
 	//cargo los kg y km
	while(archilec>>icl>>iprod>>kg>>km){
 		totalkg[icl][iprod]+=kg;
 		totalkm[icl][iprod]+=km;
 		entregas_xprod[iprod]++;
 	}
 	
	//cierro el archivo Datos
	archilec.close();
	
	//EJERCICIO 1
	
	cout<<"Lista por clientes, de productos que superen los 13000kg:"<<endl<<endl;
	for(int i=0;i<dimc;++i){
		cout<<"	-"<<cliente[i]<<":"<<endl;
		for(int j=0;j<dimp;++j){
			if(totalkg[i][j]>superar){
				cout<<"		"<<producto[j]<<endl;
				cantprod[i]++;
			}
		}
		cout<<endl;
	}
	cout<<endl<<endl;
	
	//EJERCICIO 2
	
	idclientemaxprod(cantprod,dimc,cte_conmaxprod);
	ordenar_km(poskm,totalkm,dimc,cte_conmaxprod);
	imprimir_kmorden(producto,poskm,totalkm,dimc,cte_conmaxprod,cliente);
	
	
	//EJERCICIO 3
	
	imp_productoMax_km(poskm,producto,entregas_xprod);
	
	return 0;

}

void idclientemaxprod(int cp[],int dimc,int& idcl){
	int max=0;
	for(int i=0;i<dimc;++i){
		if(cp[i]>max){
			max=cp[i];
			idcl=i;
		}
	}
}

void ordenar_km(int ikm[],float tkm[][dimp],int dimc,int idcl){
	int aux;
	for(int i=0;i<dimp;++i){
		ikm[i]=i;
	}
	for(int i=0;i<dimp;++i){
		for(int j=0;j<dimp-1;++j){
			if(tkm[idcl][ikm[j]]>tkm[idcl][ikm[j+1]]){
				aux=ikm[j];
				ikm[j]=ikm[j+1];
				ikm[j+1]=aux;
			}
		}
	}
}

void imprimir_kmorden(string prod[],int ikm[],float tkm[][dimp],int dimc,int idcl,string cte[]){
	
		cout<<"Lista de km(ascendente) recorridos por productos para el cliente "<<cte[idcl]<<":"<<endl<<endl;
	for(int i=0;i<dimp;++i){
		cout<<"	"<<prod[ikm[i]]<<": "<<tkm[idcl][ikm[i]]<<endl;
	}
	cout<<endl<<endl;
}

void imp_productoMax_km(int ikm[],string prod[],int e_xprod[]){
	
	cout<<"Para el producto "<<prod[ikm[dimp-1]]<<" hubo "<<e_xprod[ikm[dimp-1]]<<" entregas"<<endl;
	cout<<endl<<endl;
}
