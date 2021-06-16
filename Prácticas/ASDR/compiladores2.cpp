#include<stdio.h>
#include<stdlib.h>

void movS(char cad[], int &cont);
void movA(char cad[], int &cont);

int main()
{
    char cad[] = "abbaaacc";
    int cont = 0;
    movS(cad,cont);
    
    return 0;
}

void movS(char cad[], int &cont)
{
    if(cad[cont] == 'a')
    {
        cont++;
        if(cad[cont] == 'b')
        {
        	cont++;
            movS(cad,cont);
            movA(cad,cont);
        }
        
        else
		{
			printf("No pertenece");	
			exit (1);
		}
    }
    
    else if(cad[cont] == 'b')
    {
        cont++;
        movA(cad,cont);
    }
    
    else
	{
		printf("No pertenece");
		exit (1);
	}
}

void movA(char cad[], int &cont)
{
	if(cad[cont]=='a')
	{
		cont++;
		movA(cad,cont);
	}
		
	else if(cad[cont]=='c')
	{
		printf("La cadena pertenece");
		exit (1);
	}
	
	else 
	{
		printf("No pertenece");
		exit (1);
	}
		
}



