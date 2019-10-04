#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define TAM 10
typedef struct
{
    int dia;
    int mes;
    int anio;
} eFecha;

typedef struct
{
    int legajo;
    char nombre[20];
    int edad;
    char sexo;
    float salario;
    eFecha fechaIngreso;
    int idCarrera;
    int isEmpty;
} eEmployee;

typedef struct
{
    int id;
    char descripcion[20];

} eSector;

// Funciones Alumnos
void mostrarEmpleado(eEmployee x);
void mostrarEmpleados(eEmployee vec[], int tam);
void SortEmployee(eEmployee vec[], int tam);
void initEmployees(eEmployee vec[], int tam);
int buscarLibre(eEmployee vec[], int tam);
int findEmployeeById(int legajo, eEmployee vec[], int tam);
int addEmployees(eEmployee vec[], int tam, int leg);// Funcion que se usa para agregar un empleado
eEmployee newEmpleado(int leg,char nombre[],int edad, char sexo, eFecha f, int idCarrera);
int removeEmployee(eEmployee vec[], int tam);
int modifiEmployee(eEmployee vec[], int tam);
int hardcodearEmployee( eEmployee vec[], int tam, int cantidad);





int main()
{
    int legajo = 20000;
    char salir = 'n';
    eEmployee lista[TAM];

    initEmployees( lista, TAM);

    legajo = legajo + hardcodearEmployee(lista, TAM, 6);


    do
    {

        switch( menu())
        {
        case 1:
            if(addEmployees(lista, TAM, legajo))
            {
                legajo++;
            }
            break;

        case 2:
            removeEmployee(lista, TAM);
            break;

        case 3:
            modifiEmployee(lista, TAM);
            break;

        case 4:
            mostrarEmpleados(lista, TAM);
            break;

        case 5:
            SortEmployee(lista, TAM);
            break;
        case 6:
            menuInformes();
            break;

        case 7:
            printf("Confirma salir?:");
            fflush(stdin);
            salir = getche();
            break;

        default:
            printf("\nOpcion Invalida!\n\n");
        }
        system("pause");
    }
    while(salir == 'n');

    return 0;
}

int menu()
{
    int opcion;

    system("cls");
    printf("======================\n");
    printf("****** TP_02 *********\n");
    printf("======================\n\n");
    printf("1-Alta Empleado\n");
    printf("2-Baja Empleado\n");
    printf("3-Modificar Empleado\n");
    printf("4-Listar Empleado\n");
    printf("5-Ordenar Empleado\n");
    printf("6-Informes Empleado\n");
    printf("7-Salir\n\n");
    printf("Ingrese opcion: ");
    scanf("%d", &opcion);

    return opcion;
}

int menuInformes()
{
    int opcion;
    system("cls");
    printf("****** Informes *******\n\n");
    printf(" 1-Listado de los empleados ordenados por apellido y sector\n");
    printf(" 2-Total y promedio de los salarios\n");
    printf(" 3-Cantidad de empleados que superan el salario promedio\n");
    printf("4-Salir\n\n");
    printf("Ingrese opcion: ");
    scanf("%d", &opcion);

    return opcion;
}
void mostrarEmpleado(eEmployee x)
{
    char descCarrera[20];


    printf("  %d  %10s   %d      %c       %3.2f     %02d/%02d/%d   %s\n",
           x.legajo,
           x.nombre,
           x.edad,
           x.sexo,
           x.salario,
           x.fechaIngreso.dia,
           x.fechaIngreso.mes,
           x.fechaIngreso.anio,
           descCarrera);
}

void mostrarEmpleados(eEmployee vec[], int tam)
{

    int flag = 0;
    system("cls");

    printf(" Legajo    Nombre    Edad   Sexo  Salario   FIngreso  Carrera\n\n");

    for(int i=0; i < tam; i++)
    {
        if( vec[i].isEmpty == 0)
        {
            mostrarEmpleado(vec[i]);
            flag = 1;
        }
    }

    if( flag == 0)
    {
        printf("\nNo hay alumnos que mostrar\n");
    }

    printf("\n\n");
}

void SortEmployee(eEmployee vec[], int tam)
{
    eEmployee auxEmpleado;

    for(int i= 0; i < tam-1 ; i++)
    {
        for(int j= i+1; j <tam; j++)
        {
            if( vec[i].sexo > vec[j].sexo)
            {
                auxEmpleado = vec[i];
                vec[i] = vec[j];
                vec[j] = auxEmpleado;
            }
        }
    }
    printf("Empleados Ordenados\n\n");
}

void initEmployees(eEmployee vec[], int tam)
{
    for(int i = 0; i < tam; i++)
    {
        vec[i].isEmpty = 1;
    }
}


int buscarLibre(eEmployee vec[], int tam)
{
    int indice = -1;

    for(int i=0; i < tam; i++)
    {
        if( vec[i].isEmpty == 1 )
        {
            indice = i;
            break;
        }
    }
    return indice;
}

int findEmployeeById(int legajo, eEmployee vec[], int tam)
{
    int indice = -1;

    for(int i=0; i < tam; i++)
    {
        if( vec[i].legajo == legajo && vec[i].isEmpty == 0)
        {
            indice = i;
            break;
        }
    }
    return indice;
}

int addEmployees(eEmployee vec[], int tam, int leg)
{
    int todoOk = 0;
    int indice;
    char nombre[20];
    char sexo;
    int edad;
    int idCarrera;
    eFecha fecha;

    system("cls");

    printf("*****Alta Empleado*****\n\n");

    indice = buscarLibre(vec, tam);

    if( indice == -1)
    {
        printf("\nSistema completo\n\n");
    }
    else
    {
        printf("Ingrese nombre: ");
        fflush(stdin);
        gets(nombre);

        printf("Ingrese edad: ");
        scanf("%d", &edad);

        printf("Ingrese sexo: ");
        fflush(stdin);
        scanf("%c", &sexo);

        printf("Ingrese fecha ingreso: ");
        scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);


        printf("Ingrese Sector: ");
        scanf("%d", &idCarrera);

        vec[indice] = newEmpleado(leg, nombre, edad, sexo, fecha, idCarrera);
        todoOk = 1;
        printf("Alta exitosa!!\n\n");
    }

    return todoOk;
}

eEmployee newEmpleado(
    int leg,
    char nombre[],
    int edad,
    char sexo,
    eFecha fecha,
    int idCarrera
)
{

    eEmployee al;
    al.legajo = leg;
    strcpy( al.nombre, nombre);
    al.sexo = sexo;
    al.edad = edad;
    al.fechaIngreso = fecha;
    al.idCarrera = idCarrera;
    al.isEmpty = 0;

    return al;
}

int removeEmployee(eEmployee vec[], int tam)
{
    int todoOk = 0;
    int legajo;
    int indice;
    char confirma;
    system("cls");
    printf("***** Baja Empleado *****\n\n");
    printf("Ingrese legajo: ");
    scanf("%d", &legajo);

    indice = findEmployeeById(legajo, vec, tam);

    if( indice == -1)
    {
        printf("No existe un empleado con ese legajo\n\n");

    }
    else
    {
        mostrarEmpleado(vec[indice]);

        printf("\nConfirma baja?");
        fflush(stdin);
        scanf("%c", &confirma);

        if( confirma == 's')
        {
            vec[indice].isEmpty = 1;
            todoOk = 1;
            printf("Baja exitosa!!!");
        }
        else
        {
            printf("Se ha cancelado la operacion");
        }
    }

    return todoOk;
}

int modifiEmployee(eEmployee vec[], int tam)
{

    int todoOk = 0;
    int legajo;
    int indice;
    system("cls");
    printf("***** Modificar Empleado *****\n\n");
    printf("Ingrese legajo: ");
    scanf("%d", &legajo);
    int opcion;

    indice = findEmployeeById(legajo, vec, tam);

    if( indice == -1)
    {
        printf("No existe un empleado con ese legajo\n\n");

    }
    else
    {

        mostrarEmpleado(vec[indice]);

        printf("1- Modificar nota1\n");
        printf("2- Modificar nota2\n");
        printf("3- Salir\n\n");
        printf("Ingrese opcion: ");
        scanf("%d", &opcion);
        switch(opcion)
        {
        case 1:
            /*printf("Ingrese nueva nota: ");
            scanf("%d", &vec[indice].nota1);
            vec[indice].salario = (float) (vec[indice].nota1  + vec[indice].nota2)/2;*/
            break;

        case 2:
            /* printf("Ingrese nueva nota: ");
             scanf("%d", &vec[indice].nota2);
             vec[indice].salario = (float) (vec[indice].nota1  + vec[indice].nota2)/2;*/
            break;
        case 3:
            printf("Se ha cancelado la mofdificacion ");
            break;

        }
    }
    return todoOk;
}

int hardcodearEmployee( eEmployee vec[], int tam, int cantidad)
{
    int cont = 0;

    eEmployee suplentes[]=
    {
        { 20000, "Juan", 20, 'm', 6, {12, 5, 2015}, 1002, 0},
        { 20001, "Alberto", 21, 'm', 5, {12, 5, 2019},1001, 0},
        { 20002, "Ana", 22, 'f', 4.5, {2, 7, 2018},1002, 0},
        { 20003, "Luis", 20, 'm', 8.5, {21, 5, 2018},1000, 0},
        { 20004, "Alicia", 21, 'f', 6.5, {11, 9, 2017},1001, 0},
        { 20005, "Diego", 23, 'm', 2, {12, 4, 2014},1000, 0},
        { 20006, "Sofia", 19, 'f', 8.5, {12, 2, 2014},1002, 0},
        { 20007, "Clara", 21, 'f', 3, {28, 8, 2018},1001, 0},
        { 20008, "Mauro", 20, 'm', 5.5, {23, 3, 2015},1001, 0},
        { 20009, "Daniela", 22, 'f', 4, {10, 10, 2016},1000, 0},
        { 20010, "Agustin", 24, 'm', 6.5, {1, 7, 2017},1002, 0},
    };

    if( cantidad <= 10 && tam >= cantidad)
    {
        for(int i=0; i < cantidad; i++)
        {

            vec[i] = suplentes[i];
            cont++;
        }
    }

    return cont;
}
