
/****************************************************************************************

    CarGL (Objects.cpp)

    Grado en Ingenieria Multimedia.
    Practica de Graficos por Computador.
    OpenGL con Shaders.
  ---------------------------------------------------------------------------------------

    Noviembre 2012 - Septiembre 2016 (C) Juan Antonio Puchol Garcia (puchol@dccia.ua.es)


*****************************************************************************************/

#include "Objects.h"
#include <GL/glui.h>
#include <iostream>

#include "load3ds.c"

// Variable para inicializar los vectores correpondientes con los valores iniciales
GLfloat light0_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light0_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light0_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
//GLfloat light0_position_c[4] = {   0.0f, 100.0f,  0.0f, 1.0f }; //mi
//GLfloat light0_position_c[4] = {-10.0f, -10.0f, -30.0f, 1.0f }; //rr
GLfloat light0_position_c[4] = {-100.0f, 100.0f, 50.0f, 1.0f }; //pro

GLfloat light1_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light1_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light1_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light1_position_c[4] = {   0.0f, 100.0f,  0.0f, 1.0f };

GLfloat light2_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light2_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light2_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light2_position_c[4] = {   80.0f, 100.0f,  -20.0f, 1.0f };

GLfloat mat_ambient_c[4]    = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat mat_diffuse_c[4]    = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat mat_specular_c[4]   = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat mat_shininess_c[1] = { 100.0f };

// Matriz de 4x4 = (I)
float view_rotate_c[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float view_position_c[3] = { 0.0, -10.0, -50.0 };


float coloresc_c[2][4] = { {1, 0.5, 0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color del coche
float coloresr_c[2][4] = { {0.4, 0.3, 0.3, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color del mundo
float coloresRootGate_c[2][4] = { {0.93, 0.28, 0.1, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color del porton de la raiz
float coloresFlowersRoot_c[2][4] = { {0.48, 0.86, 0.4, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de las flores al rededor de la raiz
float coloresRoot_c[2][4] = { {0.84, 0.8, 0.54, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de la raiz
float coloresGroundRoots_c[2][4] = { {0.78, 0.78, 0.78, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de las raices del suelo
float coloresFlowersCity_c[2][4] = { {0.44, 0.4, 0.14, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de las flores el resto de la ciudad
float coloresElements1_c[2][4] = { {0.33, 0.51, 0.32, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de los elementos 1
float coloresElements2_c[2][4] = { {0.83, 0.83, 0.83, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de los elementos 2
float coloresElements3_c[2][4] = { {0.03, 0.26, 0.47, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de los elementos 3
float coloresElements4_c[2][4] = { {0.33, 0.26, 0.47, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de los elementos 4
float coloresElements5_c[2][4] = { {0.93, 0.16, 0.57, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de los elementos 5


//************************************************************** Variables de clase

TEscena escena;
TGui    gui;

//************************************************************** Clase TPrimitiva

TPrimitiva::TPrimitiva(int DL, int t)
{
    ID   = DL;
    tipo = t;
    anguloRuedas=0;
    sx = sy = sz = 1;
    rx = ry = rz = 0;
	switch (tipo) {
		case MUNDO_ID: {  // Creacion del mundo
		    tx = ty = tz = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por vertice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/lucia/mundoBn.3ds", &num_vertices0);
            break;
		}
		case COCHE_ID: { // Creacion del coche
		    rr =  0.0;
		    ryCoche = 0;
            //ty=0.6;

		    tx = -1.0;
		    ty =  0.0;
		    tz =  0.0;

		    memcpy(colores, coloresc_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por vertice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/lucia/coche.3ds", &num_vertices0);
            modelo1 = Load3DS("../../Modelos/lucia/ruedaDelanteraIzqdCentro.3ds", &num_vertices1);
            break;
		}
		case RAIZ_ID: {
            tx = ty = tz = 0;

            memcpy(colores, coloresRoot_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/lucia/raizSinTramas.3ds", &num_vertices0);
            break;
		}
		case PORTONRAIZ_ID: {
            tx = ty = tz = 0;

            memcpy(colores, coloresRootGate_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/lucia/portonRaiz.3ds", &num_vertices0);
            break;
		}
		case RAICESSUELO_ID: {
            tx = ty = tz = 0;

            memcpy(colores, coloresGroundRoots_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/lucia/tramasRaiz.3ds", &num_vertices0);
            break;
		}
		case FLORESRAIZ_ID: {
            tx = ty = tz = 0;

            memcpy(colores, coloresFlowersRoot_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/lucia/floresRaiz.3ds", &num_vertices0);
            break;
		}
		case FLORESCIUDAD_ID: {
            tx = ty = tz = 0;

            memcpy(colores, coloresFlowersCity_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/lucia/floresCiudad.3ds", &num_vertices0);
            break;
		}
		case ELEMENTOS1_ID: {
            tx = ty = tz = 0;

            memcpy(colores, coloresElements1_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/lucia/elementos1.3ds", &num_vertices0);
            break;
		}
		case ELEMENTOS2_ID: {
            tx = ty = tz = 0;

            memcpy(colores, coloresElements2_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/lucia/elementos2.3ds", &num_vertices0);
            break;
		}
		case ELEMENTOS3_ID: {
            tx = ty = tz = 0;

            memcpy(colores, coloresElements3_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/lucia/elementos3.3ds", &num_vertices0);
            break;
		}
		case ELEMENTOS4_ID: {
            tx = ty = tz = 0;

            memcpy(colores, coloresElements4_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/lucia/elementos4.3ds", &num_vertices0);
            break;
		}
		case ELEMENTOS5_ID: {
            tx = ty = tz = 0;

            memcpy(colores, coloresElements5_c, 8*sizeof(float));
            modelo0 = Load3DS("../../Modelos/lucia/elementos5.3ds", &num_vertices0);
            break;
		}
	} // switch
}

void __fastcall TPrimitiva::Render(int seleccion, bool reflejo)
{
    glm::mat4   modelMatrix;
    glm::mat4   modelViewMatrix;

    switch (tipo) {
        case MUNDO_ID: {
            if (escena.show_world) {
                // Calculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //Asociamos los vertices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case PORTONRAIZ_ID: {
            if(escena.show_rootGate){
                glUniform4fv(escena.uColorLocation,1,colores[0]);
                // Calculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx,ty,tz));

                //Antes definimos su rotacion en Y y ahora se la asignamos
                //Podriamos no asignar rotacion y simplemente pasarle por aqui un valor en grados
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));

                //Escalado
                modelMatrix     = glm::scale(modelMatrix,glm::vec3(sx,sy,sz));

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                //Asociamos los vertices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case RAICESSUELO_ID: {
            if(escena.show_groundRoots){
                glUniform4fv(escena.uColorLocation,1,colores[0]);
                // Calculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx,ty,tz));

                //Antes definimos su rotacion en Y y ahora se la asignamos
                //Podriamos no asignar rotacion y simplemente pasarle por aqui un valor en grados
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));

                //Escalado
                modelMatrix     = glm::scale(modelMatrix,glm::vec3(sx,sy,sz));

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                //Asociamos los vertices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case FLORESRAIZ_ID: {
            if(escena.show_flowersRoot){
                glUniform4fv(escena.uColorLocation,1,colores[0]);

                // Calculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx,ty,tz));

                //Antes definimos su rotacion en Y y ahora se la asignamos
                //Podriamos no asignar rotacion y simplemente pasarle por aqui un valor en grados
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));

                //Escalado
                modelMatrix     = glm::scale(modelMatrix,glm::vec3(sx,sy,sz));

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                //Asociamos los vertices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case FLORESCIUDAD_ID: {
            if(escena.show_flowersCity){
                glUniform4fv(escena.uColorLocation,1,colores[0]);
                // Calculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx,ty,tz));

                //Antes definimos su rotacion en Y y ahora se la asignamos
                //Podriamos no asignar rotacion y simplemente pasarle por aqui un valor en grados
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));

                //Escalado
                modelMatrix     = glm::scale(modelMatrix,glm::vec3(sx,sy,sz));

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                //Asociamos los vertices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case ELEMENTOS1_ID: {
            if(escena.show_elements1){
                glUniform4fv(escena.uColorLocation,1,colores[0]);
                // Calculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx,ty,tz));

                //Antes definimos su rotacion en Y y ahora se la asignamos
                //Podriamos no asignar rotacion y simplemente pasarle por aqui un valor en grados
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));

                //Escalado
                modelMatrix     = glm::scale(modelMatrix,glm::vec3(sx,sy,sz));

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                //Asociamos los vertices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case ELEMENTOS2_ID: {
            if(escena.show_elements2){
                glUniform4fv(escena.uColorLocation,1,colores[0]);
                // Calculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx,ty,tz));

                //Antes definimos su rotacion en Y y ahora se la asignamos
                //Podriamos no asignar rotacion y simplemente pasarle por aqui un valor en grados
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));

                //Escalado
                modelMatrix     = glm::scale(modelMatrix,glm::vec3(sx,sy,sz));

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                //Asociamos los vertices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case ELEMENTOS3_ID: {
            if(escena.show_elements3){
                glUniform4fv(escena.uColorLocation,1,colores[0]);
                // Calculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx,ty,tz));

                //Antes definimos su rotacion en Y y ahora se la asignamos
                //Podriamos no asignar rotacion y simplemente pasarle por aqui un valor en grados
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));

                //Escalado
                modelMatrix     = glm::scale(modelMatrix,glm::vec3(sx,sy,sz));

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                //Asociamos los vertices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case ELEMENTOS4_ID: {
            if(escena.show_elements4){
                glUniform4fv(escena.uColorLocation,1,colores[0]);
                // Calculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx,ty,tz));

                //Antes definimos su rotacion en Y y ahora se la asignamos
                //Podriamos no asignar rotacion y simplemente pasarle por aqui un valor en grados
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));

                //Escalado
                modelMatrix     = glm::scale(modelMatrix,glm::vec3(sx,sy,sz));

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                //Asociamos los vertices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case ELEMENTOS5_ID: {
            if(escena.show_elements5){
                glUniform4fv(escena.uColorLocation,1,colores[0]);
                // Calculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx,ty,tz));

                //Antes definimos su rotacion en Y y ahora se la asignamos
                //Podriamos no asignar rotacion y simplemente pasarle por aqui un valor en grados
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));

                //Escalado
                modelMatrix     = glm::scale(modelMatrix,glm::vec3(sx,sy,sz));

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                //Asociamos los vertices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case RAIZ_ID: {
            if(escena.show_root){
                glUniform4fv(escena.uColorLocation,1,colores[0]);
                // Calculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx,ty,tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));   // en radianes


                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                //Asociamos los vertices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            break;
        }
        case COCHE_ID: {
            if (escena.show_car) {
                if(ID == escena.seleccion && escena.seleccion==1){

                    glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) colores[0]);
                    /*
                    glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2);
                    glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2);
                    glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2 + 3);
                    */
                    modelMatrix     = glm::mat4(1.0f); // matriz identidad
                    modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx-(sin(glm::radians(ry))) , ty + 3, tz-(cos(glm::radians(ry)))));
                    //modelMatrix     = glm::rotate(modelMatrix,(float) glm::radians(-90.0),glm::vec3(1,0,0));
                    modelViewMatrix = escena.viewMatrix * modelMatrix;

                    glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);
                    //glDrawArrays(GL_TRIANGLES, 0, num_vertices2);
                }
                 if(ID == escena.seleccion && escena.seleccion==2){

                    glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) colores[0]);
                    /*
                    glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2);
                    glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2 + 3);
                    */
                    modelMatrix     = glm::mat4(1.0f); // matriz identidad
                    modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty + 3, tz));
                    //modelMatrix     = glm::rotate(modelMatrix,(float) glm::radians(-90.0),glm::vec3(1,0,0));
                    modelViewMatrix = escena.viewMatrix * modelMatrix;

                    glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);
                    //glDrawArrays(GL_TRIANGLES, 0, num_vertices2);
                }
                glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) colores[0]);
                // Asociamos los vértices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                // Cálculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }
            if (escena.show_wheels) {
                glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) colores[1]);
                // Asociamos los vértices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+3);

                // RUEDA Delantera Izquierda : Cálculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));      // en radianes
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(1, -0.42, 1.40));
                //modelMatrix     = glm::translate(modelMatrix, glm::vec3(0.68, 0.35, 1.05));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ryCoche), glm::vec3(0,1,0));      // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));      // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(180.0), glm::vec3(0,0,1));   // en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

                // RUEDA Trasera Derecha : Cálculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));      // en radianes
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(-1, -0.42, 1.40));
                //modelMatrix     = glm::translate(modelMatrix, glm::vec3(-0.68, 0.35, 1.05));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ryCoche), glm::vec3(0,1,0));      // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

                // RUEDA Delantera Izquierda : Cálculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));      // en radianes
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(1, -0.42, -1.20));
                //modelMatrix     = glm::translate(modelMatrix, glm::vec3(0.68, 0.35, -0.7));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));      // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(180.0), glm::vec3(0,0,1));   // en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

                // RUEDA Trasera Derecha : Cálculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(-1, -0.42, -1.20));
                //modelMatrix     = glm::translate(modelMatrix, glm::vec3(-0.68, +0.35, -0.7));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);
                break;
            }
            /* Antes de que girasen las ruedas
            if (escena.show_car) {
                glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) colores[0]);
                // Asociamos los vertices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                // Calculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty, tz));

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }

            if (escena.show_wheels)
            {
                glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) colores[1]);
                // Asociamos los vertices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+3);

                // RUEDA Delantera Izquierda : Calculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx+1, ty-0.42, tz+1.40));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));      // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(180.0), glm::vec3(0,0,1));   // en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

                // RUEDA Trasera Derecha : Calculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx-1, ty-0.42, tz+1.40));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

                // RUEDA Delantera Izquierda : Calculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx+1, ty-0.42, tz-1.20));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));      // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(180.0), glm::vec3(0,0,1));   // en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);

                // RUEDA Trasera Derecha : Calculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx-1, ty-0.42, tz-1.20));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);
                break;
            }*/
        }
    } // switch

}

//************************************************************** Clase TEscena

TEscena::TEscena()
{
    seleccion = 1;
    ultimoSelec = 0;
    num_objects = 0;
    num_cars = 0;

    //Aqui inicializo las variables de la interfaz. Ejemplo: los ticks de mostrar los objetos
    show_car = 1;
    show_wheels = 1;
    show_world = 1;
    show_root = 0;
    show_rootGate = 0;
    show_groundRoots = 0;
    show_flowersRoot = 0;
    show_flowersCity = 0;
    show_elements1 = 0;
    show_elements2 = 0;
    show_elements3 = 0;
    show_elements4 = 0;
    show_elements5 = 0;

    cam = 0;
    mode_cam=1;
    tipoVista=0;
    luzEspecular=1;

    // live variables usadas por GLUI en TGui
    wireframe = 0;
    z_buffer = 1;
    culling = 0;

    scale = 1.0;
    xy_aspect = 1;
    last_x = 0;
    last_y = 0;

    memcpy(view_position, view_position_c, 3*sizeof(float));
    memcpy(view_rotate, view_rotate_c, 16*sizeof(float));

    memcpy(light0_ambient, light0_ambient_c, 4*sizeof(float));

    memcpy(light0_ambient, light0_ambient_c, 4*sizeof(float));
    memcpy(light0_diffuse, light0_diffuse_c, 4*sizeof(float));
    memcpy(light0_specular, light0_specular_c, 4*sizeof(float));
    memcpy(light0_position, light0_position_c, 4*sizeof(float));

    memcpy(light1_ambient, light1_ambient_c, 4*sizeof(float));
    memcpy(light1_diffuse, light1_diffuse_c, 4*sizeof(float));
    memcpy(light1_specular, light1_specular_c, 4*sizeof(float));
    memcpy(light1_position, light1_position_c, 4*sizeof(float));

    memcpy(light2_ambient, light2_ambient_c, 4*sizeof(float));
    memcpy(light2_diffuse, light2_diffuse_c, 4*sizeof(float));
    memcpy(light2_specular, light2_specular_c, 4*sizeof(float));
    memcpy(light2_position, light2_position_c, 4*sizeof(float));

    memcpy(mat_ambient, mat_ambient_c, 4*sizeof(float));
    memcpy(mat_diffuse, mat_diffuse_c, 4*sizeof(float));
    memcpy(mat_specular, mat_specular_c, 4*sizeof(float));
    memcpy(mat_shininess, mat_shininess_c, 1*sizeof(float));
}

void __fastcall TEscena::InitGL()
{
    int tx, ty, tw, th;

    // Habilita el z_buffer
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_SHADE_MODEL);
    //glEnable(GL_FRONT_FACE);
    glDepthFunc(GL_LESS);

    // Inicializacion de GLEW
    std::cout << "Inicializando GLEW" << std::endl << std::endl;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    // print out some info about the graphics drivers
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendedor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    // Carga de los Shaders
    std::cout << std::endl << "Cargando Shaders" << std::endl;

    Shader shader;

    std::vector<GLuint> shaders;
    shaders.push_back(shader.LoadShader("../../Shaders/VertexShader.glsl", GL_VERTEX_SHADER));
    //std::cout << "Vertex Shader: " << shader.ReturnShaderID() << std::endl;
    shaders.push_back(shader.LoadShader("../../Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER));
    //std::cout << "Fragment Shader: " << shader.ReturnShaderID() << std::endl;
    shaderProgram = new Program(shaders);


    glUseProgram(shaderProgram->ReturnProgramID());
    //glValidateProgram(shaderProgram->ReturnProgramID());

    aPositionLocation=shaderProgram->attrib(A_POSITION);
    aNormalLocation=shaderProgram->attrib(A_NORMAL);


    uProjectionMatrixLocation=shaderProgram->uniform(U_PROJECTIONMATRIX);
    uMVMatrixLocation=shaderProgram->uniform(U_MVMATRIX);
    uVMatrixLocation=shaderProgram->uniform(U_VMATRIX);
    uColorLocation=shaderProgram->uniform(U_COLOR);

    //Habilitamos el paso del clickado
    seleccionarLocation=shaderProgram->uniform(CLICKADO);

    //Habilitamos cosas de luz 0
    uLuz0Location=shaderProgram->uniform(U_LUZ0);
    uLight0_xLocation=shaderProgram->uniform(U_LIGHT0_X);
    uLight0_yLocation=shaderProgram->uniform(U_LIGHT0_Y);
    uLight0_zLocation=shaderProgram->uniform(U_LIGHT0_Z);
    uLight0_iLocation=shaderProgram->uniform(U_LIGHT0_I);

    //Habilitamos cosas de luz 1
    uLuz1Location=shaderProgram->uniform(U_LUZ1);
    uLight1_xLocation=shaderProgram->uniform(U_LIGHT1_X);
    uLight1_yLocation=shaderProgram->uniform(U_LIGHT1_Y);
    uLight1_zLocation=shaderProgram->uniform(U_LIGHT1_Z);
    uLight1_iLocation=shaderProgram->uniform(U_LIGHT1_I);

    //Habilitamos cosas de luz 2
    uLuz2Location=shaderProgram->uniform(U_LUZ2);
    uLight2_xLocation=shaderProgram->uniform(U_LIGHT2_X);
    uLight2_yLocation=shaderProgram->uniform(U_LIGHT2_Y);
    uLight2_zLocation=shaderProgram->uniform(U_LIGHT2_Z);
    uLight2_iLocation=shaderProgram->uniform(U_LIGHT2_I);

    //uLuzEspecularLocation=shaderProgram->uniform(U_LUZ_ESPECULAR);

    /*
    std::cout << "a_Position Location: " << aPositionLocation << std::endl;
    std::cout << "a_Normal Location: " << aNormalLocation << std::endl;

    std::cout << "u_ProjectionMatrix Location: " << uProjectionMatrixLocation << std::endl;
    std::cout << "u_MVMatrix Location: " << uMVMatrixLocation << std::endl;
    std::cout << "u_VMatrix Location: " << uVMatrixLocation << std::endl;
    std::cout << "u_Color Location: " << uColorLocation << std::endl;
    std::cout << "u_Luz0 Location: " << uLuz0Location << std::endl;
    */


    // Habilitamos el paso de attributes
    glEnableVertexAttribArray(aPositionLocation);
    glEnableVertexAttribArray(aNormalLocation);

    // Estableciendo la matriz de proyeccion perspectiva
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
    xy_aspect = (float)tw / (float)th;
    projectionMatrix = glm::perspective(45.0f, xy_aspect, 0.1f, 1000.0f);
    glUniformMatrix4fv(uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}


/************************** TEscena::AddCar(TPrimitiva *car) *****************/

void __fastcall TEscena::AddCar(TPrimitiva *car)
{
    cars[num_cars] = car;
    num_cars++;
}

/******************** TEscena::AddObject(TPrimitiva *object) *****************/

void __fastcall TEscena::AddObject(TPrimitiva *object)
{
    objects[num_objects] = object;
    num_objects++;
}

/******************** TPrimitiva *TEscena::GetCar(int id) ********************/

TPrimitiva __fastcall *TEscena::GetCar(int id)
{
    TPrimitiva *p=NULL;
    for (int i=0; i<num_cars; i++)
    {
        if (cars[i]->ID==id)
        {
            p = cars[i];
        }
    }
    return(p);
}

/******************** TEscena::RenderCars() **********************************/

void __fastcall TEscena::RenderCars(bool reflejo)
{
    for (int i=0; i<num_cars; i++)
    {
        cars[i]->Render(seleccion, reflejo);
    }
}

/******************** TEscena::RenderCars() **********************************/

void __fastcall TEscena::RenderObjects(bool reflejo)
{
    for (int i=0; i<num_objects; i++)
    {
        objects[i]->Render(seleccion, reflejo);
    }
}

/***************************************** TEscena::Render() *****************/

void __fastcall TEscena::Render()
{
    glm::mat4 rotateMatrix;

    glClearColor(0.0, 0.7, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Calculo de la vista (camara)
    /////////////////////////////////////////////
    //          Configuracion camaras          //
    /////////////////////////////////////////////
    switch(escena.mode_cam){
        //CAMARA SEGUIMIENTO
        case 0: {
            TPrimitiva *coche = GetCar(seleccion);
            if(coche){
                float cX = coche->tx-20.0*sin(glm::radians(0.0));
                float cZ = coche->tz-20.0*cos(glm::radians(0.0));
                float angulo = (coche->ry*PI)/180.0;

                viewMatrix = glm::lookAt(glm::vec3(cX*sin(angulo),10,cZ*cos(angulo)), glm::vec3(coche->tx,coche->ty,coche->tz),glm::vec3(0,1,0));
            }
            break;
        }
        //CAMARA GENERAL (movimiento blender)
        case 1: {
            viewMatrix = glm::mat4(1.0f);
            rotateMatrix = glm::make_mat4(view_rotate);
            viewMatrix = glm::translate(viewMatrix,glm::vec3(view_position[0],view_position[1],view_position[2]));
            viewMatrix = viewMatrix*rotateMatrix;
            viewMatrix = glm::scale(viewMatrix,glm::vec3(scale,scale,scale));
            break;
        }
        //CAMARA AEREA
        case 2: {
            TPrimitiva *coche = GetCar(seleccion);
            if(coche){
                viewMatrix = glm::lookAt(glm::vec3(coche->tx,50,coche->tz),glm::vec3(coche->tx,0,coche->tz),glm::vec3(0,0,1));
            }
            break;
        }
        //Camara 1ª Persona
        case 3: {
            TPrimitiva *coche = GetCar(seleccion);
            float angulo = (coche->ry*PI)/180.0;
            if(coche){
                 viewMatrix = glm::lookAt(glm::vec3(coche->tx+sin(angulo),coche->ty+3,coche->tz*cos(angulo)),glm::vec3(coche->tx+5*sin(angulo),5,coche->tz+5*cos(angulo)),glm::vec3(0,1,0));
            }
        }
    }

    //PICK 3D IMPORTANT
    glUniform1i(seleccionarLocation,0);
    glUniform1i(uLuz0Location, gui.light0_enabled);
    glUniform1i(uLuz1Location, gui.light1_enabled);
    glUniform1i(uLuz2Location, gui.light2_enabled);
    glUniformMatrix4fv(uVMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix)); // Para la luz matrix view pero sin escalado!

    // Dibujar carretera y objetos
    RenderObjects(seleccion);

    // Dibujar coches
    RenderCars(seleccion);

    //Usamos dos paginas de video. Dibujamos usando dos buffer
    /** Muestra los renders **/
    glutSwapBuffers();
}

// Selecciona un objeto a traves del raton
void __fastcall TEscena::Pick3D(int mouse_x, int mouse_y)
{
    unsigned char res[4];
    GLint viewport[4];
    int tx,ty,tw,th;

    renderSeleccion();

    GLUI_Master.get_viewport_area(&tx,&ty,&tw,&th);
    glGetIntegerv(GL_VIEWPORT,viewport);
    glReadPixels(mouse_x,th-mouse_y+87,1,1,GL_RGBA,GL_UNSIGNED_BYTE,&res);

    //El caso de mis dos coches
    switch(res[0]){
        //Coche 1
        case 255:
            printf("Seleccionado coche 1 %d\n",res[0]);
            seleccion=1;
            break;
        //Coche 2
        case 76:
            printf("Seleccionado coche 2 %d\n",res[0]);
            seleccion=2;
            break;
        //Resto de objetos
        default:
            printf("Otro: (%d,%d) %d\n",mouse_x,mouse_y,res[0]);
            //seleccion=0;
            break;
    }
}

void __fastcall TEscena::renderSeleccion()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //set matrices to identity
    //glm::mat4 rotateMatrix;

    // set camera as in the regular rendering function

    //viewMatrix = glm::mat4(1.0f);
    //rotateMatrix = glm::make_mat4(view_rotate);
    //viewMatrix = glm::translate(viewMatrix,glm::vec3(view_position[0],view_position[1],view_position[2]));
    //viewMatrix = viewMatrix*rotateMatrix;

    if(scale < 0.01) {
        scale = 0.01;
    }
    //viewMatrix = glm::scale(viewMatrix,glm::vec3(scale/100.0,scale/100.0,scale/100.0));

    glUniform1i(seleccionarLocation,1);

    // restore clear color if needed
    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    RenderObjects();
    RenderCars(seleccion);
}


//************************************************************** Clase TGui

TGui::TGui()
{
    sel = 1;
    enable_panel2 = 1;

    light0_enabled = 1;
    light0_intensity = 0.8;
    /*
    escena.light0_position[0] = 100;
    escena.light0_position[1] = 100;
    escena.light0_position[2] = 100;
    */

    light1_enabled = 1;
    light1_intensity = 0.8;

    light2_enabled = 1;
    light2_intensity = 0.4;

    memcpy(light0_position, light0_position_c, 4*sizeof(float));
    memcpy(light1_position, light1_position_c, 4*sizeof(float));
    memcpy(light2_position, light2_position_c, 4*sizeof(float));
}

void controlCallback(int control)
{
    gui.ControlCallback(control);
}

void __fastcall TGui::Init(int main_window)
{
    /****************************************************/
    /*        Codigo con el interfaz Grafico GLUI       */
    /****************************************************/
    printf( "GLUI version: %3.2f\n", GLUI_Master.get_version() );

    window_id = main_window;

    /*** Crea a ventana lateral ***/
    glui = GLUI_Master.create_glui_subwindow( window_id, GLUI_SUBWINDOW_RIGHT );

    // Anyade una separacion
    new GLUI_StaticText( glui, "" );

    // Anyade un panel con texto con el valor de la seleccion
    GLUI_Panel *panel0 = new GLUI_Panel(glui, "Seleccion");
    GLUI_RadioGroup *radioGroup = new GLUI_RadioGroup(panel0, &sel, SEL_ID, controlCallback);
    glui->add_radiobutton_to_group(radioGroup, "NINGUNO");
    glui->add_radiobutton_to_group(radioGroup, "COCHE 1");
    glui->add_radiobutton_to_group(radioGroup, "COCHE 2");

    // Anyade una separacion
    new GLUI_StaticText( glui, "" );


    /***** Control para las propiedades de escena *****/

    obj_panel = new GLUI_Rollout(glui, "Propiedades", true );
    new GLUI_Checkbox( obj_panel, "Sentido Horario", &escena.sentido, SENTIDO_ID, controlCallback );
    new GLUI_Checkbox( obj_panel, "Modo Sombreado", &escena.sombreado, SOMBREADO_ID, controlCallback );

    glui->add_column_to_panel(obj_panel, true);
    new GLUI_Checkbox( obj_panel, "Culling", &escena.culling, CULLING_ID, controlCallback );
    new GLUI_Checkbox( obj_panel, "Z Buffer", &escena.z_buffer, ZBUFFER_ID, controlCallback );
    //new GLUI_Checkbox( obj_panel, "Luz especular", &escena.luzEspecular, LUZ_ESPECULAR_ID, controlCallback );

    // Anyade una separacion
    new GLUI_StaticText( glui, "" );

    GLUI_Panel *panel2 = new GLUI_Panel(glui,"Modos de visualizacion");
    GLUI_RadioGroup *radioGroup2 = new GLUI_RadioGroup(panel2,&escena.visualizacion,VISUALIZACION_ID,controlCallback);
    glui->add_radiobutton_to_group(radioGroup2,"Modo Solido");
    glui->add_radiobutton_to_group(radioGroup2,"Modo Alambrico");
    glui->add_radiobutton_to_group(radioGroup2,"Modo Puntos");

    // Anyade una separacion
    new GLUI_StaticText( glui, "" );

    GLUI_Panel *panel1 = new GLUI_Panel(glui,"Camaras");
    GLUI_RadioGroup *radioGroup1 = new GLUI_RadioGroup(panel1,&escena.cam,CAM_ID,controlCallback);
    glui->add_radiobutton_to_group(radioGroup1,"Camara Seguimiento");
    glui->add_radiobutton_to_group(radioGroup1,"Camara General (mov. libre)");
    glui->add_radiobutton_to_group(radioGroup1,"Camara Aerea");
    glui->add_radiobutton_to_group(radioGroup1,"Camara 1ª Persona");

    /******** Anyade controles para las luces ********/

    // Anyade una separacion
    new GLUI_StaticText( glui, "" );

    GLUI_Rollout *roll_lights = new GLUI_Rollout(glui, "Luces", true );

    GLUI_Panel *light0 = new GLUI_Panel( roll_lights, "Luz 1" );
    GLUI_Panel *light1 = new GLUI_Panel( roll_lights, "Luz 2" );
    GLUI_Panel *light2 = new GLUI_Panel( roll_lights, "Luz 3" );

    new GLUI_Checkbox( light0, "Encendida", &light0_enabled, LIGHT0_ENABLED_ID, controlCallback );
    light0_spinner = new GLUI_Spinner( light0, "Intensidad:", &light0_intensity,
                            LIGHT0_INTENSITY_ID, controlCallback );
    light0_spinner->set_float_limits( 0.0, 1.0 );
    GLUI_Scrollbar *sb;
    sb = new GLUI_Scrollbar( light0, "X",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_position[0],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light0, "Y",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_position[1],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light0, "Z",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_position[2],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);

    new GLUI_Checkbox( light1, "Encendida", &light1_enabled, LIGHT1_ENABLED_ID, controlCallback );
    light1_spinner = new GLUI_Spinner( light1, "Intensidad:", &light1_intensity,
                            LIGHT1_INTENSITY_ID, controlCallback );
    light1_spinner->set_float_limits( 0.0, 1.0 );
    sb = new GLUI_Scrollbar( light1, "X",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_position[0],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light1, "Y",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_position[1],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light1, "Z",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_position[2],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);

    new GLUI_Checkbox( light2, "Encendida", &light2_enabled, LIGHT2_ENABLED_ID, controlCallback );
    light2_spinner = new GLUI_Spinner( light2, "Intensidad:", &light2_intensity,
                            LIGHT2_INTENSITY_ID, controlCallback );
    light2_spinner->set_float_limits( 0.0, 1.0 );
    sb = new GLUI_Scrollbar( light2, "X",GLUI_SCROLL_HORIZONTAL,
                            &escena.light2_position[0],LIGHT2_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light2, "Y",GLUI_SCROLL_HORIZONTAL,
                            &escena.light2_position[1],LIGHT2_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light2, "Z",GLUI_SCROLL_HORIZONTAL,
                            &escena.light2_position[2],LIGHT2_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);

    // Anyade una separacion
    new GLUI_StaticText( glui, "" );

    /***  Rollout de Opciones ***/
    GLUI_Rollout *options = new GLUI_Rollout(glui, "Opciones", true );
    new GLUI_Checkbox( options, "Dibujar Coche", &escena.show_car );
    new GLUI_Checkbox( options, "Dibujar Ruedas", &escena.show_wheels );
    new GLUI_Checkbox( options, "Dibujar Mundo", &escena.show_world );
    new GLUI_Checkbox( options, "Dibujar Raiz", &escena.show_root );
    new GLUI_Checkbox( options, "Dibujar Porton de la raiz", &escena.show_rootGate );
    new GLUI_Checkbox( options, "Dibujar Raices del suelo", &escena.show_groundRoots );
    new GLUI_Checkbox( options, "Dibujar Flores raiz", &escena.show_flowersRoot );
    new GLUI_Checkbox( options, "Dibujar Flores ciudad", &escena.show_flowersCity );
    new GLUI_Checkbox( options, "Dibujar Elementos 1 (Oreja)", &escena.show_elements1 );
    new GLUI_Checkbox( options, "Dibujar Elementos 2 (Puente)", &escena.show_elements2 );
    new GLUI_Checkbox( options, "Dibujar Elementos 3 (Tulipan)", &escena.show_elements3 );
    new GLUI_Checkbox( options, "Dibujar Elementos 4 (Corazon)", &escena.show_elements4 );
    new GLUI_Checkbox( options, "Dibujar Elementos 5 (Luna)", &escena.show_elements5 );


    /*** Disable/Enable botones ***/
    // Anyade una separacion
    new GLUI_StaticText( glui, "" );
    new GLUI_Checkbox( glui, "Bloquear Movimiento", &enable_panel2 );

    // Anyade una separacion
    new GLUI_StaticText( glui, "" );
    new GLUI_Button( glui, "Resetear Posicion", RESET_ID, controlCallback );

    // Anyade una separacion
    new GLUI_StaticText( glui, "" );

    new GLUI_Separator( glui );

     // Anyade una separacion
    new GLUI_StaticText( glui, "" );

    new GLUI_StaticText( glui, "  Autor:" );
    new GLUI_StaticText( glui, "  2019-2020 (C) Araceli Lucia Rebollo Dominguez  " );

    // Anyade una separacion
    new GLUI_StaticText( glui, "" );

    new GLUI_Separator( glui );

    // Anyade una separacion
    new GLUI_StaticText( glui, "" );

    /****** A 'quit' button *****/
    new GLUI_Button( glui, "Salir", 0,(GLUI_Update_CB)exit );

    // Crea la subventana inferior
    glui2 = GLUI_Master.create_glui_subwindow( window_id, GLUI_SUBWINDOW_BOTTOM );

    /**** Link windows to GLUI, and register idle callback ******/
    glui->set_main_gfx_window( window_id );
    glui2->set_main_gfx_window( window_id );

    view_rot = new GLUI_Rotation(glui2, "Rotacion Escena", escena.view_rotate );
    view_rot->set_spin( 1.0 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_xy = new GLUI_Translation(glui2, "Traslacion Escena XY", GLUI_TRANSLATION_XY, escena.view_position );
    trans_xy->set_speed( 1.0 );
    //trans_xy->set_speed( .05 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_x =  new GLUI_Translation(glui2, "Traslacion Escena X", GLUI_TRANSLATION_X, escena.view_position );
    trans_x->set_speed( 1.0 );
    //trans_x->set_speed( .05 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_y = new GLUI_Translation( glui2, "Traslacion Escena Y", GLUI_TRANSLATION_Y, &escena.view_position[1] );
    trans_y->set_speed( 1.0 );
    //trans_y->set_speed( .05 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_z = new GLUI_Translation( glui2, "Traslacion Escena Z", GLUI_TRANSLATION_Z, &escena.scale );
    trans_z->set_speed( 1.0 );
    //trans_z->set_speed( .005 );
}

/**************************************** TGui::ControlCallback() *******************/

void __fastcall TGui::ControlCallback( int control )
{
    switch (control) {
        case VISUALIZACION_ID: {
            if(escena.visualizacion==0) {
                //SOLIDO
                printf("Modo solido...\n");
                glPolygonMode(GL_FRONT, GL_FILL);
                glPolygonMode(GL_BACK, GL_FILL);
            } else if(escena.visualizacion==1) {
                //ALAMBRICO
                printf("Modo alambrico...\n");
                glPolygonMode(GL_FRONT, GL_LINE);//DELANTERO
                glPolygonMode(GL_BACK, GL_LINE);//TRASERO
            } else if(escena.visualizacion==2) {
                //PUNTOS
                printf("Modo puntos...\n");
                glPolygonMode(GL_FRONT, GL_POINT);//DELANTERO
                glPolygonMode(GL_BACK, GL_POINT);//TRASERO
            }
            break;
        }
        case CULLING_ID: {
            if(escena.culling){
                printf("Culling activado...\n");
                glEnable(GL_CULL_FACE);
                glCullFace(GL_FRONT);
            }
            else{
                printf("Culling desactivado...\n");
                glDisable(GL_CULL_FACE);
            }
            break;
        }case ZBUFFER_ID: {
            if(escena.z_buffer){
                printf("Zbuffer activado...\n");
                glEnable(GL_DEPTH_TEST);
            }else{
                printf("Zbuffer desactivado...\n");
                glDisable(GL_DEPTH_TEST);
            }
            break;
        }
        case SOMBREADO_ID: {
            glEnable(GL_SHADE_MODEL);
            if(escena.sombreado){
                printf("Sombreado activado...\n");
                glShadeModel(GL_SMOOTH);//SUAVIZADO
            }else{
                printf("Sombreado desactivado...\n");
                glShadeModel(GL_FLAT);//PLANO;
            }
            break;
        }
        case SENTIDO_ID: {
            glEnable(GL_FRONT_FACE);
            if(escena.sentido){
                printf("Sentido antihorario...\n");
                glFrontFace(GL_CCW);//ANTIHORARIO
            }else{
                printf("Sentido horario...\n");
                glFrontFace(GL_CW);//HORARIO
            }
            break;
        }
        case LUZ_ESPECULAR_ID: {
            if(escena.luzEspecular){
                printf("Luz especular activada...\n");
                glUniform1i(escena.uLuzEspecularLocation,1);
            }else{
                printf("Luz especular desactivada...\n");
                glUniform1i(escena.uLuzEspecularLocation,0);
            }
            break;
        }
        case LIGHT0_ENABLED_ID: {
            if ( light0_enabled )
                light0_spinner->enable();
            else
                light0_spinner->disable();
            break;
        }
        case LIGHT1_ENABLED_ID: {
            if ( light1_enabled )
                light1_spinner->enable();
            else
                light1_spinner->disable();
            break;
        }
        case LIGHT2_ENABLED_ID: {
            if ( light2_enabled )
                light2_spinner->enable();
            else
                light2_spinner->disable();
            break;
        }
        case LIGHT0_INTENSITY_ID: {

            float v[] = {
                escena.light0_diffuse[0],  escena.light0_diffuse[1],
                escena.light0_diffuse[2],  escena.light0_diffuse[3] };

            v[0] *= light0_intensity;
            v[1] *= light0_intensity;
            v[2] *= light0_intensity;
            glUniform1f(escena.uLight0_iLocation,light0_intensity);
            break;
        }
        case LIGHT0_POSITION_ID: {
            //En escena.light0_position[] tenemos el x y z de la luz
            glUniform1f(escena.uLight0_xLocation,escena.light0_position[0]);
            glUniform1f(escena.uLight0_yLocation,escena.light0_position[1]);
            glUniform1f(escena.uLight0_zLocation,escena.light0_position[2]);

        }
        case LIGHT1_INTENSITY_ID: {
            float v[] = {
                escena.light1_diffuse[0],  escena.light1_diffuse[1],
                escena.light1_diffuse[2],  escena.light1_diffuse[3] };

            v[0] *= light1_intensity;
            v[1] *= light1_intensity;
            v[2] *= light1_intensity;
            glUniform1f(escena.uLight1_iLocation,light1_intensity);
            break;
        }
        case LIGHT1_POSITION_ID: {
            //En escena.light0_position[] tenemos el x y z de la luz
            glUniform1f(escena.uLight1_xLocation,escena.light1_position[0]);
            glUniform1f(escena.uLight1_yLocation,escena.light1_position[1]);
            glUniform1f(escena.uLight1_zLocation,escena.light1_position[2]);
        }
        case LIGHT2_INTENSITY_ID: {
            float v[] = {
                escena.light2_diffuse[0],  escena.light2_diffuse[1],
                escena.light2_diffuse[2],  escena.light2_diffuse[3] };

            v[0] *= light2_intensity;
            v[1] *= light2_intensity;
            v[2] *= light2_intensity;
            glUniform1f(escena.uLight2_iLocation,light2_intensity);
            break;
        }
        case LIGHT2_POSITION_ID: {
            //En escena.light0_position[] tenemos el x y z de la luz
            glUniform1f(escena.uLight2_xLocation,escena.light2_position[0]);
            glUniform1f(escena.uLight2_yLocation,escena.light2_position[1]);
            glUniform1f(escena.uLight2_zLocation,escena.light2_position[2]);
        }
        case ENABLE_ID: {
            glui2->enable();
            break;
        }
        case DISABLE_ID: {
            glui2->disable();
            break;
        }
        case RESET_ID: {
            memcpy(escena.view_position,view_position_c,3*sizeof(float));
            view_rot->reset();
            escena.scale = 1.0;
            break;
        }
        case SEL_ID: {
            escena.seleccion = sel;
            //GLUI_Master.SetFocus(true);
            glutSetWindow( glui->get_glut_window_id() );
            break;
        }
        case CAM_ID: {
            escena.mode_cam = escena.cam;
            printf("Camara seleccionada numero: %d \n",escena.mode_cam);
            break;
        }
  } // switch
}

/***************************************** TGui::Idle() ***********/

void __fastcall TGui::Idle( void )
{
  /* According to the GLUT specification, the current window is
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != window_id )
    glutSetWindow(window_id);

  /*  GLUI_Master.sync_live_all();  -- not needed - nothing to sync in this
                                       application  */
    if (enable_panel2)
        glui2->enable();
    else
        glui2->disable();

  glutPostRedisplay();
}

/**************************************** TGui::reshape() *************/

void __fastcall TGui::Reshape( int x, int y )
{
    int tx, ty, tw, th;
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
    glViewport( tx, ty, tw, th );

    escena.xy_aspect = (float)tw / (float)th;

    glMatrixMode(GL_PROJECTION);
    //escena.projectionMatrix = glm::perspective(45.0f, escena.xy_aspect, 0.1f, 1000.0f);

    //Cambios de vista ortogonal a perspectiva
    if(escena.tipoVista){
          //glOrtho(left, right, bottom, top, near, far)
         escena.projectionMatrix = glm::ortho(escena.xy_aspect,10*escena.xy_aspect, -10.0f, 10.0f, -100.0f, 1000.0f);
         printf("Seleccionada: Vista Ortogonal\n\n");
    }else{
        //gluPerspective(alpha, aspect, near, far)
         escena.projectionMatrix = glm::perspective(45.0f, escena.xy_aspect, 0.1f, 1000.0f);
         printf("Seleccionada: Vista Perspectiva\n\n");
    }

    glUniformMatrix4fv(escena.uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(escena.projectionMatrix));
    //std::cout << "xy aspect: " << escena.xy_aspect << std::endl;

    glutPostRedisplay();
}

/***************************************** gui::motion() **********/

void __fastcall TGui::Motion(int x, int y )
{
    glutPostRedisplay();
}

/***************************************** gui::Mouse() **********/

void __fastcall TGui::Mouse(int button, int button_state, int x, int y )
{
    escena.Pick3D(x, y);
}

