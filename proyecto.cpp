#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;

//Estructuras

struct Horarios
{
    string Hora;
    string Minutos;
};

struct Funciones
{
    int Disponibilidad;
    string Nombre;
    string Genero;
    Horarios Horario;
    int Duracion;
    int Sala;
    int Precio_Boletas;
    int Boletas_Disponibles;
    char Asientos[6][10];
};

//FUNCIONES DE USUARIO

////Funcion Especial

void Funcion_Especial(int Codigo[], int n)
{
    ofstream Premio("premio.txt");

    int No_Premio = 0;

    Premio << "<><><><><><><><><><><>" << endl;
    Premio << endl;

    //Evaluando la ultima posicion del codigo

    if(Codigo[6] == 2)
    {
        Premio << "¡FELICIDADES, HAS GANADO!" << endl;
        Premio << "¡COMBO EXTRAGRANDE!" << endl;
        Premio << endl;
    }
    else if(Codigo[6] == 4)
    {
        Premio << "¡FELICIDADES, HAS GANADO!" << endl;
        Premio << "¡BOLETAS GRATIS!" << endl;
        Premio << endl;
    }
    else if(Codigo[6] == 9)
    {
        Premio << "¡FELICIDADES, HAS GANADO!..." << endl;
        Premio << "¡MERCANCIA!" << endl;
        Premio << endl;
    }
    else// +1 Al contador de NO tener premio
    {
        No_Premio++;
    }

    //Evaluando si el codigo esta en orden creciente o no

    int Contador = 0;
    for(int i=0;i<5;i++)
    {
        if(Codigo[i] < Codigo[i+1])
        {
            Contador++;
        }
    }

    if(Contador==5)
    {
        Premio << "¡FELICIDADES, HAS GANADO!" << endl;
        Premio << "¡MEMBRESIA -PALOMITAS Y PAPITAS- PREMIUM !" << endl;
        Premio << endl;
    }
    else
    {
        No_Premio++; // +1 Al contador de NO tener premio
    }

    if(No_Premio==2)
    {
        Premio << "NO GANASTE NADA, MEJOR SUERTE PARA LA PROXIMA" << endl;
        Premio << "¡DISFRUTA TU FUNCION!" << endl;
        Premio << endl;
    }
}

////Imprimir Factura

void Factura(struct Funciones Nuevo[],int Codigo_peli,int Costo)
{
    srand(time(0));

    int Codigo[6]; //Codigo de la funcion especial

    //Generando el Codigo de la funcion con numeros random del 0 al 9

    for(int i=0;i<6;i++)
    {
        int Random = rand()%9+0;
        Codigo[i] = Random;
    }

    ofstream Boleta("factura.txt");
    if(!Boleta.is_open()){
        cout<<"ERROR AL ABRIR EL ARCHIVO FACTURA"<<endl;
        return;
    }
    Boleta << "----Factura CINE PALOMITAS & PAPITAS----"<<endl;
    Boleta << "Pelicula: " << Nuevo[Codigo_peli].Nombre<<endl;
    Boleta << "Genero: " << Nuevo[Codigo_peli].Genero<<endl;
    Boleta << "Horario" << Nuevo[Codigo_peli].Horario.Hora << ":" << Nuevo[Codigo_peli].Horario.Minutos<<endl;
    Boleta << "Sala: " <<Nuevo[Codigo_peli].Sala<<endl;
    Boleta << "Costo: " << Costo<<endl;
    Boleta << "Codigo: ";
    for(int i=0;i<6;i++)
    {
        Boleta << Codigo[i];
    }
    Boleta << endl;
    cout<<"Factura generada, gracias por su compra y revise su codigo, con el se puede ganar premios!"<<endl;

    Boleta.close();

    Funcion_Especial(Codigo, 6);
}

////Vender Boletas

void Vender_Boletas(Funciones Nuevo[],int Contador,struct Funciones Cart[4][5])
{
    int As;
    int Codigo_peli;

    int Fila;
    int Columna;

    //Usuario dice cual de las peliculas mostradas quiere ver

    cout << "Codigo de la funcion: "; cin >> Codigo_peli;

    //Usuario dice cuantos asientos quiere escoger

    cout << "Cuantos asientos desea Seleccionar: "; cin >> As;
    cout << endl;

    //Mostrando Asientos de la pelicula

    cout << "--------Pantalla--------" << endl;
    cout << endl;

    cout << "  ";

    for(int Cc=0;Cc<10;Cc++)
    {
        cout << Cc+1 << " ";
    }
    cout << endl;

    for(int Cf=0;Cf<6;Cf++)
    {
        cout << Cf+1 << " ";

        for(int Cc=0;Cc<10;Cc++)
        {
            cout << Nuevo[Codigo_peli].Asientos[Cf][Cc] << " ";
        }

        cout << endl;
    }

    //Seleccion de Asientos

    for(int i=0;i<As;i++)
    {
        cout << "Fila de la silla " << i+1 << ": "; cin >> Fila;
        cout << "Columna de la silla " << i+1 << ": "; cin >> Columna;

        Nuevo[Codigo_peli].Asientos[Fila-1][Columna-1] = 'x';
    }

    //Actualizando la matriz principal con las funciones originales

    for(int Cf=0;Cf<4;Cf++)
    {
        for(int Cc=0;Cc<5;Cc++)
        {
            if(Nuevo[Codigo_peli].Sala==Cart[Cf][Cc].Sala && Nuevo[Codigo_peli].Horario.Hora==Cart[Cf][Cc].Horario.Hora)
            {
                for(int i=0; i<6; i++)
                {
                    for(int j=0; j<10; j++)
                    {
                        Cart[Cf][Cc].Asientos[i][j] = Nuevo[Codigo_peli].Asientos[i][j];
                    }
                }
                Cart[Cf][Cc].Boletas_Disponibles = Cart[Cf][Cc].Boletas_Disponibles - As; //Actualizando la cantidad de boletas disponibles
            }
        }
    }

    int Costo = As * Nuevo[Codigo_peli].Precio_Boletas;

    Factura(Nuevo,Codigo_peli,Costo);
}

////Mostrar Boletas

void Mostrar_Boletas(struct Funciones Nuevo[], int Contador, struct Funciones Cart[4][5])
{

    // Mostrando la info de las boletas

    for(int i=0;i<Contador;i++)
    {
        cout << "CODIGO DE PELICULA: " << i << endl; //Codigo de la pelicula, posicion en el arreglo, la cual servira para escoger la funcion
        cout << "Nombre: " << Nuevo[i].Nombre << endl;
        cout << "Horario: " << Nuevo[i].Horario.Hora << ":" << Nuevo[i].Horario.Minutos << endl;
        cout << "Sala: " << Nuevo[i].Sala << endl;
        cout << "Precio de Boletas: " << Nuevo[i].Precio_Boletas << endl;
        cout << "Boletas Disponibles: " << Nuevo[i].Boletas_Disponibles << endl;
        cout << endl;
    }

    Vender_Boletas(Nuevo,Contador,Cart);
}

////Busqueda Por Nombre

void Busqueda_Nombre(struct Funciones Cart[4][5])
{
    Funciones Nuevo[20]; //Arreglo de funciones seleccionadas
        int Contador = 0;
    string Nombre_Pelicula;

        //Poniendo el nombre de la pelicula

    cin.ignore();
    cout << "Nombre de Pelicula: "; getline(cin,Nombre_Pelicula);
    cout << endl;

    //Buscando la pelicula en la matriz

    for(int Cf = 0; Cf<4;Cf++)
    {
        for(int Cc = 0; Cc<5; Cc++)
        {
            if(Nombre_Pelicula == Cart[Cf][Cc].Nombre) //Transferencia de Datos si encuentra la pelicula
            {
                Nuevo[Contador].Disponibilidad = Cart[Cf][Cc].Disponibilidad;
                Nuevo[Contador].Nombre = Cart[Cf][Cc].Nombre;
                Nuevo[Contador].Genero = Cart[Cf][Cc].Genero;
                Nuevo[Contador].Horario = Cart[Cf][Cc].Horario;
                Nuevo[Contador].Sala = Cart[Cf][Cc].Sala;
                Nuevo[Contador].Precio_Boletas = Cart[Cf][Cc].Precio_Boletas;
                Nuevo[Contador].Boletas_Disponibles = Cart[Cf][Cc].Boletas_Disponibles;

                for(int k =0; k<6; k++)
                {
                    for(int y=0; y<10;y++)
                    {
                        Nuevo[Contador].Asientos[k][y] = Cart[Cf][Cc].Asientos[k][y];//Transferencia de datos de los asientos
                    }
                }

                Contador++; // Se mueve a la siguiente posicion del arreglo
            }
        }
    }

    if(Contador == 0)
    {
        cout << "NO SE ENCONTRARON COINCIDENCIAS" <<  endl;
    }
    else
    {
        Mostrar_Boletas(Nuevo,Contador,Cart);
    }
}

//FUNCIONES OPERADOR

////Registrar Funcion

void Registrar_Funcion() {
  ofstream Archivo_Cart("archivocart.txt",
                        ios::app); // Abrir el archivo en modo de escritura

  if (!Archivo_Cart.is_open()) {
    cout << "Error al abrir el archivo para escritura." << endl;
    return;
  }

  Funciones Nueva_Fun;
  char Continuar;

  do {
    cout << "Hora de pelicula: ";
    cin >> Nueva_Fun.Horario.Hora;
    cout << "Minuto de Pelicula: ";
    cin >> Nueva_Fun.Horario.Minutos;
    cout << "Sala: ";
    cin >> Nueva_Fun.Sala;
    cout << "Precio Boletas: ";
    cin >> Nueva_Fun.Precio_Boletas;
    Nueva_Fun.Boletas_Disponibles = 60;
    cout << "Nombre: ";
    cin.ignore(); // Limpiar el búfer
    getline(cin, Nueva_Fun.Nombre);

    Archivo_Cart << endl;
    Archivo_Cart << Nueva_Fun.Horario.Hora << " " << Nueva_Fun.Horario.Minutos
                 << endl;
    Archivo_Cart << Nueva_Fun.Sala << endl;
    Archivo_Cart << Nueva_Fun.Precio_Boletas << endl;
    Archivo_Cart << Nueva_Fun.Boletas_Disponibles << endl;
    Archivo_Cart << Nueva_Fun.Nombre << endl;

    cout << "Desea agregar otra funcion? (S/N): "; cin >> Continuar;
  } while (Continuar == 'S' || Continuar == 's');

  Archivo_Cart.close();
}

////Eliminar por Nombre

void Eliminar_Funcion() {
  ifstream Archivo_Cart("archivocart.txt");
  ofstream Archivo_Temp("archivotemp.txt");

  if (!Archivo_Cart.is_open() || !Archivo_Temp.is_open()) {
    cout << "Error al abrir los archivos." << endl;
    return;
  }

  string Nombre_Eliminar;
  cout << "Ingrese el nombre de la funcion a eliminar: ";
  cin.ignore();
  getline(cin, Nombre_Eliminar);

  Funciones Lectura[100];
  int Contador = 0;

    while(Archivo_Cart >> Lectura[Contador].Horario.Hora >> Lectura[Contador].Horario.Minutos >> Lectura[Contador].Sala >> Lectura[Contador].Genero >> Lectura[Contador].Precio_Boletas >> Lectura[Contador].Boletas_Disponibles)
    {
        Archivo_Cart.ignore();
        getline(Archivo_Cart, Lectura[Contador].Nombre);
        Contador++;
    }

  for (int i = 0; i < Contador; i++) {
    if (Lectura[i].Nombre != Nombre_Eliminar) {
      Archivo_Temp << Lectura[i].Horario.Hora << " "
                   << Lectura[i].Horario.Minutos << endl;
        Archivo_Temp << Lectura[i].Sala << endl;
        Archivo_Temp << Lectura[i].Genero << endl;
        Archivo_Temp << Lectura[i].Precio_Boletas << endl;
        Archivo_Temp << Lectura[i].Boletas_Disponibles << endl;
        Archivo_Temp << Lectura[i].Nombre << endl;
    }
  }

    Archivo_Cart.close();
    Archivo_Temp.close();
    remove("archivocart.txt");
    rename("archivotemp.txt", "archivocart.txt");
    cout << "Funcion eliminada con exito" << endl;
    cout << endl;
}

////Menu de Operador

void Menu_Operador(struct Funciones Cart[4][5])
{
    cout << endl;
    bool Bandera_Operador = true;
    int Menu;

    while(Bandera_Operador == true)
    {
        cout << "-----OPERACION DESEADA-----" << endl;
        cout << "1.Registrar Funcion" << endl;
        cout << "2.Eliminar Funcion" << endl;
        cout << "3.Volver a menu principal" << endl;
        cin >> Menu;

        switch(Menu)
        {
        case 1:
            Registrar_Funcion();
            cout << endl;
            break;
        case 2:
            Eliminar_Funcion();
            cout << endl;
            break;
        case 3:

            cout << "FUNCION DE OPERADOR FINALIZADA" << endl;
            cout << endl;

            Bandera_Operador = false;
            break;

        default:

            cout << "VALOR INVALIDO" << endl,
            cout << endl;
        }
    }
}

//VER CARTELERA

void Mostra_Cartelera(struct Funciones Cart[4][5])
{
    for(int Cf=0; Cf<4;Cf++)
    {
        for(int Cc=0;Cc<5;Cc++)
        {
            if(Cart[Cf][Cc].Disponibilidad == 1)
            {
                cout << "Nombre: " << Cart[Cf][Cc].Nombre << endl;
                cout << "Genero: " << Cart[Cf][Cc].Genero << endl;
                cout << "Sala: " << Cart[Cf][Cc].Sala << endl;
                cout << "Horario: " << Cart[Cf][Cc].Horario.Hora << ":" << Cart[Cf][Cc].Horario.Minutos << endl;
                cout << "Precio de Boletas: " << Cart[Cf][Cc].Precio_Boletas << endl;
                cout << "Boletas Disponibles: " << Cart[Cf][Cc].Boletas_Disponibles << endl;
            }
        }
    }
}

//MAIN

int main()
{
    Funciones Cart[4][5];

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<5; j++)
        {
            Cart[i][j].Disponibilidad = 0;
            Cart[i][j].Nombre = "N/A";
            Cart[i][j].Genero = "N/A";
            Cart[i][j].Horario.Hora = "00";
            Cart[i][j].Horario.Minutos = "00";
            Cart[i][j].Duracion = 0;
            Cart[i][j].Sala = 0;
            Cart[i][j].Precio_Boletas = 0;
            Cart[i][j].Boletas_Disponibles = 0;
            for(int k=0; k<6; k++){
                for(int r=0; r<10; r++){
                    Cart[i][j].Asientos[k][r] = 'n';
                }
            }
        }
    }

    //Creando Valores del cine iniciales

    ifstream Archivo_Cart("archivocart.txt");

    if(!Archivo_Cart.is_open())
    {
        cout << "ERROR" << endl;
        cout << endl;
        return 0;
    }

    Funciones Lectura[100];
    int Contador = 0;

    while(Archivo_Cart >> Lectura[Contador].Horario.Hora >> Lectura[Contador].Horario.Minutos >> Lectura[Contador].Sala >> Lectura[Contador].Genero >> Lectura[Contador].Precio_Boletas >> Lectura[Contador].Boletas_Disponibles)
    {
        Archivo_Cart.ignore();
        getline(Archivo_Cart, Lectura[Contador].Nombre);
        Contador++;
    }

    for(int L=0;L<Contador;L++)
    {
        int fila = Lectura[L].Sala-1;
        int columna = -1;
        if(Lectura[L].Horario.Hora == "11" && Lectura[L].Horario.Minutos == "00"){
            columna = 0;
        }
        else if(Lectura[L].Horario.Hora == "01" && Lectura[L].Horario.Minutos == "30"){
            columna = 1;
        }
        else if(Lectura[L].Horario.Hora == "03" && Lectura[L].Horario.Minutos == "00"){
            columna = 2;
        }
        else if(Lectura[L].Horario.Hora == "05" && Lectura[L].Horario.Minutos == "30"){
            columna = 3;
        }
        else if(Lectura[L].Horario.Hora == "07" && Lectura[L].Horario.Minutos == "00"){
            columna = 4;
        }
        Cart[fila][columna].Disponibilidad = 1;
        Cart[fila][columna].Nombre = Lectura[L].Nombre;
        Cart[fila][columna].Genero = Lectura[L].Genero;
        Cart[fila][columna].Horario.Hora = Lectura[L].Horario.Hora;
        Cart[fila][columna].Horario.Minutos = Lectura[L].Horario.Minutos;
        Cart[fila][columna].Duracion = Lectura[L].Duracion;
        Cart[fila][columna].Sala = Lectura[L].Sala;
        Cart[fila][columna].Precio_Boletas = Lectura[L].Precio_Boletas;
        Cart[fila][columna].Boletas_Disponibles = Lectura[L].Boletas_Disponibles;
    }


    bool Bandera_Main = true;
    int Menu;

    while (Bandera_Main==true)
    {
        cout << "====BIENVENIDO A CINEMA PALOMITAS Y PAPITAS====" << endl;
        cout << endl;
        cout << "1.Usuario" << endl;
        cout << "2.Operador" << endl;
        cout << "3.Ver cartelera" << endl;
        cout << "4.Log Out" << endl;
        cin >> Menu;

        switch(Menu)
        {
        case 1:

            Busqueda_Nombre(Cart);
            cout << endl;
            break;

        case 2:
            Menu_Operador(Cart);
            cout << endl;
            break;

        case 3:
            Mostra_Cartelera(Cart);
            cout << endl;
            break;

        case 4://Opcion de Log out

            cout << "GRACIAS POR VISITAR PALOMITAS Y PAPITAS" << endl;
            cout << endl;

            Bandera_Main = false;
            break;

        default://Opcion que no esta en el menu

            cout << "OPCION INVALIDA" << endl;
            cout << endl;
        }
    }

return 0;
}
