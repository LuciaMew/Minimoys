
/****************************************************************************************************

    CarGL (main.cpp)

    Grado en Ingeniería Multimedia.
    Práctica de Gráficos por Computador.
    OpenGL con Shaders.
  ------------------------------------------------------------------------------------------

    CarsGL (C) 2012-2016 - Juan Antonio Puchol García (puchol@dccia.ua.es)

    Changelog:

    Versión 1.0 (Noviembre 2012)
        - Versión inicial para Code::Blocks 10.05

    Versión 1.1 (Noviembre 2012)
        - Arreglado el bug de selección incorrecta debido al panel inferior de controles

    Versión 1.2 (Octubre 2013 )
        - Adaptación de la librería GLUI a Code::Blocks 12.11 y 13.12

    Versión 1.3 (Octubre 2014 )
        - Adaptación de la librería GLUI a Code::Blocks 13.12

    Versión 2.0 (Octubre 2015 )
        - Adaptación del código empleando Shaders (Modern OpenGL Graphics)

    Versión 2.1 (Septiembre 2016 )
        - Modificación de los scrollbars de las luces para manipular la posisión (compatible con Code::Blocks 16.01)

    NOTA:   Para que esta aplicación compile se necesita tener copiados los
            siguientes ficheros desde la carpeta "Para Copiar":

            glut32.dll  -> C:\Windows\system

            Si es un Windows de 32 bits:
            glew32s.lib -> C:\Program Files\CodeBlocks\MinGW\lib
            glew32.lib  -> C:\Program Files\CodeBlocks\MinGW\lib
            libglui32.a -> C:\Program Files\CodeBlocks\MinGW\lib
            glut32.lib  -> C:\Program Files\CodeBlocks\MinGW\lib

            glui.h      -> C:\Program Files\CodeBlocks\MinGW\include\GL
            glut.h      -> C:\Program Files\CodeBlocks\MinGW\include\GL
            glew.h      -> C:\Program Files\CodeBlocks\MinGW\include\GL

            y la carpeta completa
            glm         -> C:\Program Files\CodeBlocks\MinGW\include

            Si es un Windows de 64 bits:
            glew32s.lib -> C:\Program Files (x86)\CodeBlocks\MinGW\lib
            glew32.lib  -> C:\Program Files (x86)\CodeBlocks\MinGW\lib
            libglui32.a -> C:\Program Files (x86)\CodeBlocks\MinGW\lib
            glut32.lib  -> C:\Program Files (x86)\CodeBlocks\MinGW\lib

            glui.h      -> C:\Program Files (x86)\CodeBlocks\MinGW\include\GL
            glut.h      -> C:\Program Files (x86)\CodeBlocks\MinGW\include\GL
            glew.h      -> C:\Program Files (x86)\CodeBlocks\MinGW\include\GL

            y la carpeta completa
            glm         -> C:\Program Files (x86)\CodeBlocks\MinGW\include


            ACLARACIÓN:
                Hay varias librerías libglui32.a en la carpeta "otros"
                - Renombrar libglui32.10.05.a a libglui32.a para usar Code::Blocks 10.05
                - Renombrar libglui32.12.11.a a libglui32.a para usar Code::Blocks 12.11
                - Renombrar libglui32.13.12.a a libglui32.a para usar Code::Blocks 13.12 o superior

****************************************************************************************************/

#include "Objects.h"
//#include "loadjpeg.c"
#include <GL\glui.h>


/**************************************** myGlutKeyboard() **********/

void Keyboard(unsigned char Key, int x, int y)
{
    switch(Key)
    {
        case 27:
        case 'q':
            exit(0);
            break;
        case 'O':
        case 'o':
            //Como no se ve bien, desactivamos la vista Ortog para PrimeraPersona y VistaAerea
            escena.tipoVista=1;
            gui.Reshape(x,y);//Paralela
            break;
        case 'P':
        case 'p':
            escena.tipoVista=0;
            gui.Reshape(x,y);//Perspectiva
            break;
    }
    glutPostRedisplay();
}

/**************************************** mySpecialKey() *************/

static void SpecialKey(int key, int x, int y)
{
    TPrimitiva *car = escena.GetCar(escena.seleccion);
    float angulogiro=(car->ry*PI)/180.0;
    float cosenogiro=cos(angulogiro);
    float senogiro=sin(angulogiro);

    switch (key)
    {
        case GLUT_KEY_UP:   // El coche avanza
            car->rr+=rotacionRueda;
            car->tx += velocidadCoche*senogiro;
            car->tz += velocidadCoche*cosenogiro;
            car->ry += car->ryCoche * 0.02;
            break;
        case GLUT_KEY_DOWN:   // El coche retrocede
            car->rr-=rotacionRueda;
            car->tx -= velocidadCoche*senogiro;
            car->tz -= velocidadCoche*cosenogiro;
            car->ry -= car->ryCoche * 0.02;
            break;

        case GLUT_KEY_LEFT:    //Ruedas giran izquierda
            if(car->ryCoche<45){
                car->ryCoche += 2;
            }
            break;
        case GLUT_KEY_RIGHT:
             if(car->ryCoche>-45){
                car->ryCoche -= 2;
            }
            break;
    }
    glutPostRedisplay();
}

/***************************************** myGlutMenu() ***********/

void Menu( int value )
{
  Keyboard( value, 0, 0 );
}

void Mouse(int button, int button_state, int x, int y )
{
    gui.Mouse(button, button_state, x, y);
}

void Render()
{
    escena.Render();
}

void Idle()
{
    gui.Idle();
}

void Reshape(int x, int y){
    gui.Reshape(x, y);
}

void Motion(int x, int y){
    gui.Motion(x, y);
}


/**************************************** main() ********************/

int main(int argc, char* argv[])
{
    // Inicializa GLUT and crea la ventana principal
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE );
    glutInitWindowPosition( 200, 200 );
    glutInitWindowSize( 1400, 800 );

    int main_window = glutCreateWindow( "Arthur y los Minimoys - CarGL V2.0 (2019) con Shaders" );

    // Inicializa los valores de OpenGL para esta Aplicacion
    escena.InitGL();
    gui.Init(main_window);

    glutDisplayFunc( Render );
    GLUI_Master.set_glutReshapeFunc( Reshape );
    GLUI_Master.set_glutKeyboardFunc( Keyboard );
    GLUI_Master.set_glutSpecialFunc( SpecialKey );
    GLUI_Master.set_glutMouseFunc( Mouse );
    glutMotionFunc( Motion );


    /**** We register the idle callback with GLUI, *not* with GLUT ****/
    GLUI_Master.set_glutIdleFunc( Idle );

    // Crea los objetos
    TPrimitiva *world = new TPrimitiva(MUNDO_ID, MUNDO_ID);
    TPrimitiva *car1 = new TPrimitiva(1, COCHE_ID);
    TPrimitiva *car2 = new TPrimitiva(2, COCHE_ID);

    TPrimitiva *root = new TPrimitiva(RAIZ_ID,RAIZ_ID);
    TPrimitiva *rootGate = new TPrimitiva(PORTONRAIZ_ID, PORTONRAIZ_ID);
    TPrimitiva *groundRoots = new TPrimitiva(RAICESSUELO_ID, RAICESSUELO_ID);
    TPrimitiva *flowersRoot = new TPrimitiva(FLORESRAIZ_ID, FLORESRAIZ_ID);
    TPrimitiva *flowersCity = new TPrimitiva(FLORESCIUDAD_ID, FLORESCIUDAD_ID);
    TPrimitiva *elements1 = new TPrimitiva(ELEMENTOS1_ID, ELEMENTOS1_ID);
    TPrimitiva *elements2 = new TPrimitiva(ELEMENTOS2_ID, ELEMENTOS2_ID);
    TPrimitiva *elements3 = new TPrimitiva(ELEMENTOS3_ID, ELEMENTOS3_ID);
    TPrimitiva *elements4 = new TPrimitiva(ELEMENTOS4_ID, ELEMENTOS4_ID);
    TPrimitiva *elements5 = new TPrimitiva(ELEMENTOS5_ID, ELEMENTOS5_ID);

    /*
    Asignacion de posiciones y rotaciones

             -z
              |
              |
      -x-------------+x
              |
              |
             +z

    La rotacion para dar la vuelta a algo es en el ry
    */
    car2->colores[0][0] = 0.3;
    car2->colores[0][1] = 0.8;
    car2->colores[0][2] = 0.4;
    car2->colores[0][3] = 1.0;
    car2->tx = 2;
    car2->tz = 3;

    /* Ejemplo parametros
    root->tx = +37;
    root->tz = +33;
    root->ry = 30;
    root->sy = 0.7;
    root->sx = 0.7;
    root->sz = 0.7;
    */
    // Raiz
    root->tx = 0;
    root->tz = 0;

    // Porton de la raiz
    rootGate->tx = 0;
    rootGate->tz = 0;
    rootGate->ry = 0;

    // Raices del suelo
    groundRoots->tx = 0;
    groundRoots->tz = 0;
    groundRoots->ry = 0;

    // Flores raiz
    flowersRoot->tx = 0;
    flowersRoot->tz = 0;
    flowersRoot->ry = 0;

    // Flores ciudad
    flowersCity->tx = 0;
    flowersCity->tz = 0;
    flowersCity->ry = 0;

    // Elementos 1
    elements1->tx = 0;
    elements1->tz = 0;
    elements1->ry = 0;

    // Elementos 2
    elements2->tx = 0;
    elements2->tz = 0;
    elements2->ry = 0;

    // Elementos 3
    elements3->tx = 0;
    elements3->tz = 0;
    elements3->ry = 0;

    // Elementos 4
    elements4->tx = 0;
    elements4->tz = 0;
    elements4->ry = 0;

    // Elementos 5
    elements5->tx = 0;
    elements5->tz = 0;
    elements5->ry = 0;

    //////////////////////
    // Resto de objetos //
    //////////////////////
    escena.AddObject(root);
    escena.AddObject(rootGate);
    escena.AddObject(groundRoots);
    escena.AddObject(flowersRoot);
    escena.AddObject(flowersCity);
    escena.AddObject(elements1);
    escena.AddObject(elements2);
    escena.AddObject(elements3);
    escena.AddObject(elements4);
    escena.AddObject(elements5);

    escena.AddObject(world);
    escena.AddCar(car1);
    escena.AddCar(car2);

    /**** Regular GLUT main loop ****/
    glutMainLoop();

    return EXIT_SUCCESS;
}

