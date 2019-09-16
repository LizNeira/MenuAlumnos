#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<ctype.h>
#define p printf
#define s scanf
typedef struct
{
 int cod;
 char nom[30];
 int pripar;
 int segpar;
 float prom;
} registro;

void mostrar(FILE*,char*);
void tecla(void);
void cargar(FILE*,FILE*);
//int error(char *);
void filtrar(FILE*,FILE*);
int verifica(FILE*,char*);
void linea(int);
void mayu(char[]);
int menprin(void);


int main()
{
  int op,existe=0,ban;
  FILE *arch, *apro;
  char *nomarch="alumnos.dat";
  char*nomapro="aprobados.dat";
  system("color 9f") ;
  srand(time(NULL));
  system("color 9f");
  do
	{
	op=menprin();
	switch(op)
		{
		case 1:
			{
             system("cls");
             ban=verifica(arch,nomarch);
             if(ban==0)
              {
                p("\n EL ARCHIVO %s NO EXISTE SU APERTURA SER%c DE ESCRITURA!! ",nomarch,181);
                arch=fopen(nomarch,"wb+");
              }
               else
                  {
                    p("\n EL ARCHIVO %s EXISTE SU APERTURA SER%c DE LECTURA-ESCRITURA!! ",nomarch,181);
                    arch=fopen(nomarch,"rb+");
                  }
             getch();
             apro=fopen(nomapro,"ab+");
             cargar(arch,apro);
             fclose(arch);
             fclose(apro);
             break;
			}

		case 2:
				{
								system("cls");
								ban=verifica(arch,nomarch);
					if(ban==0)
								{
										p("\n NO SE PUEDEN PROCESAR LOS ALUMNOS PORQUE EL ARCHIVO %s NO EXISTE!!!!",nomarch);
										getch();
								}
					else
								{
									arch=fopen(nomarch,"rb+");
									mostrar(arch,"ALUMNOS");
									fclose(arch);
								}

					break;
				}

		case 3:
		     {
            system("cls");
            ban=verifica(apro,nomapro);
			      if(ban==0)
                  {
                      p("\n El archivo %s no existe!!!!",nomapro);
                      getch();
                  }
			      else
                  {
                    apro=fopen(nomapro,"rb+");
                    mostrar(apro,"APROBADOS");
                    fclose(apro);
                  }
			      break;

		       }

			}
	}while(op<4);
//	getch();
    p("\n\n \t\t***** PRESIONE UNA TECLA LA SALIR DEL PROGRAMA!!! *****");
    getch();
    system("cls");
 return 0;
}

 void linea(int x)
{
 int i;
	//p("\n");
	for(i=1;i<x;i++)
	 p("*");
	p("\n");
}

 int menprin(void)
{
int op;
 	do
	{
	system("cls");
	printf("\n\t\t\t\t*****MEN%c PRINCIPAL DE ALUMNOS*****\n\n",233);
	p("\n\n\t\t\t \t - INGRESO DE NOTAS \t <1>\n");
	p("\n\n\t\t\t \t - LISTADO DE ALUMNOS\t <2>\n");
	p("\n\n\t\t\t \t - LISTADO DE APROBADOS\t <3>\n");
	p("\n\n\t\t\t \t - SALIR               \t <4>\n");
	p("\n\n\n\t\t\t INGRESE OPCI%cN: ",224);s("%d",&op);
	}while(op<1 || op>4);
return(op);
}//CIERRA MENU

int error(char *x)
{
	fprintf(stderr,"no se puede abrir el archivo %s",x);
	return(1);
}

void tecla(void)
{
	p("\n\nPRESIONE CUALQUIER TECLA PARA VOLVER AL MENU PRINCIPAL!!!");
	getch();
}

int verifica(FILE*x,char*y)
{
 int v;
   if((x=fopen(y,"rb+"))==NULL) v=0;
    else v=1;

  return(v);
}
void cargar(FILE *x,FILE*y){// Completar la función
 registro r;
 int ca,ban;
 char nom[30];
 system("cls");
 srand(time(NULL));
 p("\n\nINGRESE C%cDIGO DEL ALUMNO [0-PARA VOLVER AL MEN%C PRINCIPAL]: ",224,233);
 s("%d",&ca);
while(ca!=0)
{
   ban=0;
   rewind(x);
   fread(&r,sizeof(registro),1,x);
   while(!feof(x)&&(ban==0))
   {
     if(ca!=r.cod)
        fread(&r,sizeof(registro),1,x);
     else
      {
          p("\n EL ALUMNO EXISTE Y  YA TIENE LOS DATOS CARGADOS!!! ");
          getch();
          ban=1;
          break;
      }
    }
    if(ban==0)
    {
        fseek(x,0L,SEEK_END);
				r.cod=ca;
				fflush(stdin);
				p("\n INGRESE NOMBRE DEL ALUMNO:");
				s("%[^\n]",r.nom);
				mayu(r.nom);
				r.pripar=rand()%10+1;
				r.segpar=rand()%10+1;
				r.prom=(float)((r.pripar+r.segpar)/2.);
				fwrite(&r,sizeof(registro),1,x);
				if(r.prom>=7) fwrite(&r,sizeof(registro),1,y);
    }
    system("cls");
   p("\n\nINGRESE C%cDIGO DEL ALUMNO [0-PARA VOLVER AL MEN%C PRINCIPAL]: ",224,233); s("%d",&ca);

  }

}

void mostrar(FILE *x,char*y)
{
	registro r;
	int c=0;
	rewind(x);
	p("\n \t\t\tINFORME ACAD%cMICO DE %s \n\n",144,y);
	linea(80);
	p("\n COD.\t ALUMNO\t\t\t1%c PARCIAL\t 2%c PARCIAL \tPROMEDIO\n\n",167,167);
	linea(80);
	fread(&r,sizeof(registro),1,x);
	while(!feof(x))
    {
        p("\n %4d\t%-20s%6d\t\t%4d\t\t%6.2f\n\n",r.cod,r.nom,r.pripar,r.segpar,r.prom);
        fread(&r,sizeof( registro),1,x);
        c++;
    }
    linea(80);
    p("\nCANTIDAD DE %s: %d",y,c);
    tecla();
}

void mayu(char x[])
{
 int i=0;
 while(x[i])
      x[i]=toupper(x[i++]);
}
