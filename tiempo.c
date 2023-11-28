#include <stdio.h>
#include <stdint.h>
#include <tiempo.h>

//struct tiempo tiempesin;
//int segundos=0;

struct tiempo
{
	int sanio;
	int smes;
	int sdia;
	int shora;
	int sminuto;
	int ssegundo;
};

struct tiempo maketime(int segundos)
{
	struct tiempo t;
	
	int anio=2000;
	int mes=01;
	int dia=01;
	int hora=00;
	int minuto=00;
	int segundo=00;

	int estadoanio=0;
	
	printf("=== Inicio de conversion int->struct === \n\n");
	printf("Año (segundos restantes): %i \n",segundos);
	while(estadoanio==0)
	{
		if( (anio-2000)%4==0 && segundos>=31622400) //años bisiestos
		{
			segundos-=31622400;
			anio++;
		}
		else if(segundos>=31536000) //años no bisiestos
		{	
			segundos-=31536000;
			anio++;
		}
		else
		{
			estadoanio=1;
		}
	}
	
	printf("Mes (segundos restantes): %i \n",segundos);
	
	int estadomes=0;
	
	while(estadomes==0)
	{
		if((mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12) && segundos>=2678400) // meses con 31 días
		{
			segundos-=2678400;
			mes++;
		}
		else if((mes==4 || mes==6 || mes==9 || mes==11) && segundos>=2592000) // meses de 30 días
		{
			segundos-=2592000;
			mes++;
		}
		else if((anio-2000)%4==0 && segundos>=2505600) // febrero de 29 días (año actual bisiesto)
		{
			segundos-=2505600;
			mes++;
		}
		else if(segundos>=2419200) // febrero de 28 días
		{
			segundos-=2419200;
			mes++;
		}
		else
		{
			estadomes=1;
		}
	}
	
	printf("Dia (segundos restantes): %i \n",segundos);
	
	int estadodia=0;
	
	while(estadodia==0)
	{
		if(segundos>=86400)
		{
			segundos-=86400;
			dia++;
		}
		else
		{
			estadodia=1;
		}
	}
	
	printf("Hora (segundos restantes): %i \n",segundos);
	
	int estadohora=0;
	
	while(estadohora==0)
	{
		if(segundos>=3600)
		{
			segundos-=3600;
			hora++;
		}
		else
		{
			estadohora=1;
		}
	}
	
	printf("Minuto (segundos restantes): %i \n",segundos);
	
	int estadominuto=0;
	
	while(estadominuto==0)
	{
		if(segundos>=60)
		{
			segundos-=60;
			minuto++;
		}
		else
		{
			estadominuto=1;
		}
	}
	
	printf("Segundo (segundos restantes): %i \n\n",segundos);
	segundo=segundos;
	
	printf("Fecha actual: %i:%i:%i del %i/%i/%i \n\n",hora,minuto,segundo,dia,mes,anio);

	t.sanio=anio;
	t.smes=mes;
	t.sdia=dia;
	t.shora=hora;
	t.sminuto=minuto;
	t.ssegundo=segundo; 
	
	return t;
}

int makeseconds(struct tiempo t)
{
	
	// Importante; que sea día/mes/anio n no quiere decir que hayan pasado n días/meses/anios completos, los que pasaron 
	// completos en realidad fueron n-1 días/meses/anios
	
	int anio=t.sanio-1; //*
	int mes=t.smes-1; //*
	int dia=t.sdia-1; //*
	int hora=t.shora;
	int minuto=t.sminuto;
	int segundo=t.ssegundo;
	
	printf("=== Inicio de conversion struct->int ===\n\n");
	
	segundos+=segundo;
	printf("Segundos (segundos acumulados): %i \n",segundos);
	segundos+=minuto*60;
	printf("Minutos (segundos acumulados): %i \n",segundos);
	segundos+=hora*3600;
	printf("Horas (segundos acumulados): %i \n",segundos);
	segundos+=dia*86400;
	printf("Dia (segundos acumulados): %i \n",segundos);
	
	int estadomes=0;
	
	while(estadomes==0)
	{
		if((mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12)) // meses con 31 días
		{
			segundos+=2678400;
			mes--;
		}
		else if((mes==4 || mes==6 || mes==9 || mes==11)) // meses de 30 días
		{
			segundos+=2592000;
			mes--;
		}
		else if(mes==2 && (anio-2000)%4==0) // febrero de 29 días (año actual bisiesto)
		{
			segundos+=2505600;
			mes--;
		}
		else if(mes==2) // febrero de 28 días
		{
			segundos+=2419200;
			mes--;
		}
		else
		{
			estadomes=1;
		}
	}
	
	printf("Mes (segundos acumulados): %i \n",segundos);
	
	int estadoanio=0;
	
	while(estadoanio==0)
	{
		if((anio-2000)%4==0 && anio>=2000) //años bisiestos
		{
			segundos+=31622400;
			anio--;
		}
		else if(anio>=2000) //años no bisiestos
		{	
			segundos+=31536000;
			anio--;
		}
		else
		{
			estadoanio=1;
		}
	}
	
	printf("Año (segundos acumulados): %i \n\n",segundos);
	
	printf("Segundos desde 01/01/2000 00:00:00 : %i",segundos);
	
	return segundos;
}
