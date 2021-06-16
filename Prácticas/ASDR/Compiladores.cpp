#include <stdio.h>

void movA(char cad[],int &x);
void movB(char cad[],int &x);

int main(){
	char cad[] = "aca";
	int x = 0;
	
	movA(cad,x);
	
	return 0;
	
}

void movA(char cad[], int &x)
{
	if(cad[x] == 'a')
	{
		x++;
		movB(cad,x);
	}
	
	else printf("No pertenece\n");
}

void movB(char cad[], int &x)
{
	if(cad[x] == 'b')
	{
		x++;
		movA(cad,x);
	}
	
	else if(cad[x] == 'c')
	{
		int temp = x;
		int i=1,cont = 0;
		
		while(cont != x)
		{
			if(cad[x-i] == cad[x+i])
			{
				cont++;
			}
			
			else
			{
				printf("No pertenece\n");
				break;	
			}
			i++;
		}
		
		if(cont == x)
		{
			printf("La cadena '%s' pertenece\n",cad);
		}
	}
	
	else printf("No pertenece\n");
}
