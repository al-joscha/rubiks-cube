#include "TestGlm.hpp"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

void TestGlm::Initialize()
{
	glm::vec3 first_vector = glm::vec3(1.0f, 2.0f, 3.0f);
	glm::vec4 second_vector = glm::vec4(first_vector, 1.0f);

	first_vector = glm::normalize(first_vector);
	float inner = glm::dot(first_vector, first_vector);
	float* pointer = glm::value_ptr(first_vector);

	glm::mat4 first_mat = glm::mat4(1.0f);
	glm::vec4 transform = first_mat * second_vector;

	glm::mat4 trans = glm::translate(glm::mat4(1.0f), first_vector);
	glm::vec4 second_trans = trans * second_vector;
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0f),
	                               glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 compound = trans * rotate; //erst verdrehen dann verschieben ( andersherum wegen column-major)
	glm::mat4 alternate_compound = glm::rotate(trans,
	                                           glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 diff = alternate_compound - compound;

	float* mat_pointer = glm::value_ptr(diff);
	glm::mat4 test = glm::lookAt(glm::vec3(0.0f, 0.0f, -1.0f),
	                             glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 object_view = test * alternate_compound; //Look At Transformation
	glm::mat4 view_to_clip = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 10.0f);
	glm::vec4 test_vec = glm::vec4(1.0f, 2.0f, 3.0f, 1.0f);
	glm::vec4 first_transform = object_view * test_vec;
	glm::vec4 complete_trans = view_to_clip * object_view * test_vec;


	int blub = 1;
	m_orientationQuaternion = glm::quat(1.0f, 0.0, 0.0, 0.0);
}


void TestGlm::Update(double deltaTime)
{
	glm::quat rotation_velocity = glm::quat(0.0f, glm::radians(180.0f), 0.0f, 0.0f);
	glm::quat time_derivation = 0.0f * rotation_velocity * m_orientationQuaternion;
	m_orientationQuaternion += time_derivation * static_cast<float>(deltaTime);
	m_orientationQuaternion = glm::normalize(m_orientationQuaternion);


	float test_length = glm::length(m_orientationQuaternion);
	glm::mat4 final_rotation = glm::mat4_cast(m_orientationQuaternion);
	
	int blib = 1;
}


void TestGlm::Render(float aspectRatio)
{
	glm::mat4 complete = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 10.0f)
		* glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f))
		* glm::mat4_cast(m_orientationQuaternion);

	float* pointer = glm::value_ptr(complete);
}

// vectoren: aus der lib brauche ich noch skalarprodukt und length/distanze können auch noch hilfreich sein
// matrizen: glm matth4
// Tipp: Kamera bleibt fix und nur der Cube dreht sich ( der würfel wird in welrkoordinaten rotiert ) 


// Logicmodel:
// 
// 2 Varianten
// Die erste Variante wird vom prof nicht empfohlen:
// zunächst einfachere V1: (im laufe der entwicklung bringt diese probleme mit sich ) 
// Aufgefallteter Würfel: ( Kreuz mit unterer seite doppelt untereinander) 
//  in der 2d repräsentation werden dann die drehoperationen dargstellt
//  Ist allerdings für die letzten 10 bis 20% prozent aufwändig weil viele randfälle beachtet werden müssen 
// 
// x,y,z Achse
// 0,1,2 Scheibe
// +,-
//  ( unschöne lange if statements und Animation nur schwer umsetzbar) 
//
//
// 2. Variante ( vom Prof empfohlen )
// Logisches 3d Model:
//  - nicht die Farben wechseln sondern die Würfelseiten rotieren
//  jeden stein darstellen (mini cubie) (insg. 3x3x3 = 27) 
// 
// für jeden Stein müssen wir 2x verdrehen
// wir brauchen 4d matrix um mit der 4. dimension ..... zu beschreiben ( nicht ganz verstanden ) 
// glm:mat4[3][3][3][2]
// d 1-3: 


// Koordinaten (-1,1,1) hat im Arrayspace (0,2,2) weil das mat4[3][3][3] keine negativen indizes hat,  muss also immer umgerechnet werden
// Wie folgt rechne ich aus wo der cubie landet nachdem man eine rotation durchgeführt hat: 
// Für die position des minicubies: 
// rot = rotate(90,(0,1,0) // rotiert um y-achse
// newpos = rot * pos_alt
// 
// Und für die Roation des mini cubies
// rot_new = rot * rot_alt
// glm::mat4([2][3][3][3]
// [2] ist sourcebuffer und destinationbuffer
// Wir kopieren bei Rotationen von srccubie in destcubie
// qxig, x,y,z Achse , 0,1,2 - slice, +1 ,-1 quaternion
// * rot matrix
// rohindex -> rohindex  -(1,1,1) -> rot_mat * A -> round (gegen rundungsfehler) -> + (1,1,1)
// srcbuf ist 0 oder 1 , destbuff ist -1 oder 0
// es bietet sich an den ganzen src buffer in destbuffer zum convertieren
//  state_new = rot_mat * state_old
//
// Tipp vom Prof: Die zweite Umdrehung des selben Cubies funktioniert nicht:
// passiert wenn die MUltiplikationsreihenfolge falschherum ist:  state_new = rot _mat * state_old // so herum ist richtig 
//
// 
// Erst rotieren und dann translieren: 
// PERSP * VIEWMAT * ROTCUBE *(an diese Stelle kommt später die animationsmatrix rein) * TRANSCUBE (TRANSLATION DES MINI CUbies) * ROTCUBIE
//
//
// Würfel soll beliebig verdrehbar sein: 
// Kamera relative steuerung (notwendig für maussteuerung ): 
//ges = vcew * object
// ges * (1,0,0) = ( x ,y, z)
// -> (x,y)^0      //normalisieren
// 
// 
// 3 normalvectoren (x,y)^0... diese werden benutzt um zwischen welt und objekt koordinaten zu wechseln 
// 
// 
// 
// Dreiecke:
// wir nehmen einfachere varianten mit mit vertices angeben ( die vertices liegen im sog. VBA ( vertice buffer aray) auf der GPU
// VBO (vertices buffer objects) liegen auch auf der GPU , hier liegen die eigentlichen vertice koordinaten drin
// wir nutzen VBA,VBO, Vertexshader, UNIFORMDATA, Fragmetshader,
// 
// Kommt alles im Vertex-Shader zusammen
// MOGG,= CUBE:SPACE
// RGBA-Farbe
// 16 (komisches wort) Koordinaten : 2,3,4 (kann ich nicht lesen) 
// 
// Fürs ABNAHMEGESPRÄCH SHADERUTIL H UND SHADERUTIL CPP erklären können !!! 
//
