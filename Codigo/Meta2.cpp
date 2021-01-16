/* Projeto Meta 2 - Parte 1/N (C++ File - MAIN) ||| CG - LEI / FCTUC 2020/21 | Dario Filipe Torres Felix N.2018275530 */



/* ***** MEU HEADER GERAL ***** */
#include "HeaderGeralMeta2.h"



/* ***** FUNCOES ***** */
int main(int argc, char** argv) {
	// Funcao Main

	iniciaVarsGlobaisPadrao();

	printf("**************************************************************************************\n");
	printf("* CG - LEI / FCTUC 2020/21 | Dario Filipe Torres Felix N.2018275530 | Projeto Meta 2 *\n");
	printf("**************************************************************************************\n");
	printHelp();

	glutInit(&argc, argv);																// glutInit is used to initialize the GLUT library.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);							// Sets the initial display mode: Bit mask to select a double buffered window. | An alias for GLUT_RGBA. - Bit mask to select an RGBA mode window | Bit mask to select a window with a depth buffer.
	glutInitWindowSize(W_SCREEN, H_SCREEN);												// This function allows you to request initial dimensions for future windows.
	glutInitWindowPosition(300, 100);													// Requests future windows to open at a given position.
	glutCreateWindow(" Dario Felix N. 2018275530 | CG 2020/2021 - Meta 2 | FCTUC ");	// glutCreateWindow creates a top-level window.

	inicia();

	glutSpecialFunc(tecladoEspecial);													// sets the special keyboard callback for the current window.
	glutDisplayFunc(cenario);															// sets the display callback for the current window.
	glutKeyboardFunc(teclado);															// sets the keyboard callback for the current window.
	glutTimerFunc(MSEC, Timer, 1);														// glutTimerFunc registers a timer callback to be triggered in a specified number of milliseconds.

	glutMainLoop();																		// enters the GLUT event processing loop.

	return 0;
}



void iniciaVarsGlobaisPadrao(void) {
	rVisao = RAIO_INIT;																	// Observador: raio / distancia
	aVisao = ANGULO_INIT;																// Observador: Angulo - Partida Inicial a volta de YY / Coordenadas Plano xOz

	xAlvo = X_ALVO_INIT;																// xAlvo - Para Onde o Observador Esta a Olhar
	yAlvo = Y_ALVO_INIT;																// yAlvo
	zAlvo = Z_ALVO_INIT;																// zAlvo

	xObs = rVisao * cos(aVisao) + xAlvo;												// xObservador - Local Onde o Observador Esta  | Coordenadas Plano xOz
	yObs = yAlvo;																		// yObservador (Altura)
	zObs = rVisao * sin(aVisao) + zAlvo;												// zObservador | Coordenadas Plano xOz

	tipoProjeccao = PROJECAO_INIT;														// boolean: qual projecao? ortog Vs persp
	ignorar_legenda = LEGENDA_INIT;														// boolean: ignorar legenda? sim Vs nao
	ignorar_eixos = EIXOS_INIT;															// boolean: ignorar eixos? sim Vs nao
	ignorar_debug = DEBUG_INIT;

	cao_translacao_min = 0;																// Porta-Cao Fechada
	cao_translacao_max = 0;																// Porta-Cao Aberta > translacao maxima = altura_porta_cao (e feito mais tarde o =)
	cao_translacao = 0;																	// Porta-Cao Inicial
	cao_translacao_inc = 0.1;															// Incremento

	porta_rotacao_min = 0;																// Porta fechada > 0 graus
	porta_rotacao_max = 90;																// Porta aberta > 90 graus
	porta_rotacao = 0;																	// Porta Inicial
	porta_rotacao_inc = 1.5;															// Incremento


	// Valores Absolutos, mais tarde dividir por 2
	espessura_geral = 0.6;																// Z

	altura_porta = 17.0 - espessura_geral;												// Y
	largura_porta = 8.0;																// X

	altura_porta_cao = 2.5;																// Y
	largura_porta_cao = 2.5;															// X
	espessura_ombreira_cao = 0.2;														// X

	largura_ombreira5 = 4.0;															// X

	altura_total = altura_porta + espessura_geral;										// Y
	largura_total = espessura_geral + largura_porta + largura_ombreira5;				// X

	altura_ombreira1 = altura_total;													// Y
	largura_ombreira2 = largura_total;													// X

	altura_janela = altura_total - espessura_geral * 2;									// Y
	largura_janela = largura_ombreira5 - espessura_geral * 2;							// X
	espessura_janela = 0.1;																// Z

	tamanho_peca_diagonal = (GLfloat) sqrt( ((double) largura_janela * (double) largura_janela) + ((double) altura_janela * (double) altura_janela));	// Y
	espessura_peca_diagonal = 0.25;														// Z
	angulo = ((tan(largura_janela / altura_janela)) * 180) / PI - 1.1;					// Calculo de alfa e passar para garaus (o 1.1 >> para limar)

	altura_porta_parte4 = 1.5;															// Y
	largura_porta_parte4 = largura_porta;												// X

	altura_porta_parte1 = altura_porta - altura_porta_cao - altura_porta_parte4;		// Y
	largura_porta_parte1 = largura_porta;												// X

	altura_porta_parte2e3 = altura_porta_cao;											// Y
	largura_porta_parte2e3 = (largura_porta - largura_porta_cao) / 2;					// X

	altura_puxador = 0.6;																// Y
	largura_puxador = altura_puxador;													// X
	espessura_puxador = (altura_puxador / 3);											// Z

	cao_translacao_max = altura_porta_cao;												// Variavale Global Inicializada

	luzRed = RGB_INIT;		 															// Vermelho
	luzGreen = RGB_INIT;																// Verde
	luzBlue = RGB_INIT;																	// Azul
	luz_global_intensidade = INTENSIDADE_GLOBAL_INIT;									// Luz Global | Intensidade
	luz_0_intensidade = INTENSIDADE_0_INIT;
	luz_1_intensidade = INTENSIDADE_1_INIT;
	luz_0_switch = SWITCH_0_INIT;
	luz_1_switch = SWITCH_1_INIT;

	luz_global_cor[0] = luz_global_intensidade;
	luz_global_cor[1] = luz_global_intensidade;
	luz_global_cor[2] = luz_global_intensidade;

	luz_0_posicao[0] = 0;																// Luz 0 | Posicao
	luz_0_posicao[1] = altura_total;
	luz_0_posicao[2] = -10.0;
	luz_0_posicao[3] = 1.0;

	luz_1_posicao[0] = X_LUZ_1_INIT;													// Luz 1 | Posicao
	luz_1_posicao[1] = Y_LUZ_1_INIT;
	luz_1_posicao[2] = Z_LUZ_1_INIT;
	luz_1_posicao[3] = 1.0;

	luz_1_foco_ak = 1.0;				//
	luz_1_foco_al = 0.02f;				//
	luz_1_foco_aq = 0.0f;				//
	luz_1_foco_exp = 0.5;				//
	luz_1_foco_abertura = 15.0;			//

	luz_0_ambiente[0] = luz_0_difusa[0] = luz_0_especular[0] = luzRed * luz_0_intensidade;
	luz_0_ambiente[1] = luz_0_difusa[1] = luz_0_especular[1] = luzGreen * luz_0_intensidade;
	luz_0_ambiente[2] = luz_0_difusa[2] = luz_0_especular[2] = luzBlue * luz_0_intensidade;
	luz_0_ambiente[3] = luz_0_difusa[3] = luz_0_especular[3] = 1.0;

	luz_1_ambiente[0] = luz_1_difusa[0] = luz_1_especular[0] = luzRed * luz_1_intensidade;
	luz_1_ambiente[1] = luz_1_difusa[1] = luz_1_especular[1] = luzGreen * luz_1_intensidade;
	luz_1_ambiente[2] = luz_1_difusa[2] = luz_1_especular[2] = luzBlue * luz_1_intensidade;
	luz_1_ambiente[3] = luz_1_difusa[3] = luz_1_especular[3] = 1.0;

	
	n_pedaco = N_PEDACO_INIT;
	
	shine_geral = SHINE_GERAL_INIT;
	polished_silver_shine = SHINE_SILVER_INIT;
}



void inicia(void) {
	// Inicia

	glClearColor(CINZENTO_CLARO);														// specify clear values for the color buffers.
	glShadeModel(GL_SMOOTH);															// The initial value is GL_SMOOTH. GL primitives can have either flat or smooth shading.
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	iniciaTexturas();
	updateLuzes();

	glEnable(GL_DEPTH_TEST);															// GL_DEPTH_TEST. If enabled, do depth comparisons and update the depth buffer.

	glEnable(GL_CULL_FACE);																// From this point on, all the faces that are not front-faces are discarded.
	glCullFace(GL_BACK);																// glCullFace specifies whether front- or back-facing polygons are culled.

	glVertexPointer(3, GL_FLOAT, 0, cubo_vertices);										// Specifies a pointer to the first coordinate of the first vertex in the array.
	glEnableClientState(GL_VERTEX_ARRAY);												// enable or disable client-side capability: the vertex array is enabled for writing and used during rendering when glDrawArrays, or glDrawElements is called.

	glNormalPointer(GL_FLOAT, 0, cubo_normais);											// glNormalPointer specifies the location and data format of an array of normals to use when rendering.
	glEnableClientState(GL_NORMAL_ARRAY);												// enable or disable client-side capability: the normal array is enabled for writing and used during rendering when glDrawArrays, or glDrawElements is called.

	glTexCoordPointer(2, GL_FLOAT, 0, cubo_texturas);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}



void Timer(int value) {
	// Ciclo

	glutPostRedisplay();																// marks the current window as needing to be redisplayed.
	glutTimerFunc(MSEC, Timer, 1);														// glutTimerFunc registers a timer callback to be triggered in a specified number of milliseconds.
}




void cenario(void) {
	// Todo o cenario

	// Apaga 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);									// glClear sets the bitplane area of the window to values previously selected by glClearColor , glClearIndex , glClearDepth , ...

	//updateLuzes();

	// *** Viewport 2 ***
	glViewport(0, 0, W_SCREEN, H_SCREEN);												// 1. JANELA / ECRA (xInicial, yInicial, xFinal, yFinal) em pixeis

	glMatrixMode(GL_PROJECTION);														// glMatrixMode sets the current matrix mode.
	glLoadIdentity();																	// replaces the current matrix with the identity matrix.
	if (tipoProjeccao == 0)
		gluPerspective(ANGULO_Z, (float)W_SCREEN / H_SCREEN, 0.1, 9999);				// 2. PROJECAO / VOLUME MUNDO (Angulo, Razao w/h, dInicial, dFinal) d = distancia, w/h = largura/altura
	if (tipoProjeccao == 1)
		glOrtho(-20, 20, -20, 20, -100, 100);											// 2. PROJECAO / VOLUME MUNDO (xInicial, xFinal, yInicial, yFinal, zInicial, zFinal)

	glMatrixMode(GL_MODELVIEW);															// glMatrixMode sets the current matrix mode.
	glLoadIdentity();																	// replaces the current matrix with the identity matrix.
	gluLookAt(xObs, yObs, zObs, xAlvo, yAlvo, zAlvo, 0, 1, 0);							// 3. OBSERVADOR (xObservador, yObservador, zObservador, xVerAlvo, yVerAlvo, zVerAlvo, xVetorCabeca, yVetorCabeca, zVetorCabeca)

	updateLuzes();
	iluminacao();
	// Objectos / 4. TRANSFORMACOES e 5. DEFINICOES DE OBJETOS
	if (ignorar_eixos == 0) {
		desenhaEixos();
	}
	if (ignorar_debug == 0) {
		desenhaVerAlvoObservador();
		desenhaLocalLuzes();
	}
	cenarioExterior();
	cenarioInterior();
	desenhaPorta();


	if (ignorar_legenda == 0) {
		// *** Viewport 1 - PLANTA-MAPA - Projecao ortogonal ***
		glViewport(0, 0, 0.20 * W_SCREEN, 0.20 * H_SCREEN);								// 1. JANELA / ECRA (xInicial, yInicial, xFinal, yFinal) em pixeis
		glMatrixMode(GL_PROJECTION);													// glMatrixMode sets the current matrix mode.
		glLoadIdentity();																// replaces the current matrix with the identity matrix.
		glOrtho(-30, 30, -30, 30, -100, 100);											// 2. PROJECAO / VOLUME MUNDO (xInicial, xFinal, yInicial, yFinal, zInicial, zFinal)
		glMatrixMode(GL_MODELVIEW);														// glMatrixMode sets the current matrix mode.
		glLoadIdentity();																// replaces the current matrix with the identity matrix.
		gluLookAt(0, 30, 0, 0, 0, 0, 0, 0, -1);											// 3. OBSERVADOR (xObservador, yObservador, zObservador, xVerAlvo, yVerAlvo, zVerAlvo, xVetorCabeca, yVetorCabeca, zVetorCabeca)

		updateLuzes();
		iluminacao();
		// Objectos  / 4. TRANSFORMACOES e 5. DEFINICOES DE OBJETOS
		if (ignorar_eixos == 0) {
			desenhaEixos();
		}
		desenhaLocalObservador();
		desenhaVerAlvoObservador();
		desenhaLocalLuzes();
		cenarioExterior();
		cenarioInterior();
		desenhaPorta();
		desenhaInfo();

	}


	if (ignorar_legenda == 0) {
		// *** Viewport 3 - Texto ***
		glViewport(0, 0.9 * H_SCREEN, 0.1 * W_SCREEN, 0.1 * H_SCREEN);					// 1. JANELA / ECRA (xInicial, yInicial, xFinal, yFinal) em pixeis
		glMatrixMode(GL_PROJECTION);													// glMatrixMode sets the current matrix mode.
		glLoadIdentity();																// replaces the current matrix with the identity matrix.
		glOrtho(-20, 20, -20, 20, -100, 100);											// 2. PROJECAO / VOLUME MUNDO (xInicial, xFinal, yInicial, yFinal, zInicial, zFinal)
		glMatrixMode(GL_MODELVIEW);														// glMatrixMode sets the current matrix mode.
		glLoadIdentity();																// replaces the current matrix with the identity matrix.
		gluLookAt(0, 30, 0, 0, 0, 0, 0, 0, -1);											// 3. OBSERVADOR (xObservador, yObservador, zObservador, xVerAlvo, yVerAlvo, zVerAlvo, xVetorCabeca, yVetorCabeca, zVetorCabeca)
		updateLuzes();
		iluminacao();
		desenhaInfo2();
	}


	// Actualizacao
	glutSwapBuffers();																	// swaps the buffers of the current window if double buffered.
}



void desenhaTexto(char* string, GLfloat x, GLfloat y, GLfloat z) {
	// Escreve Texto no Ecra

	glPushMatrix();
	glTranslatef(x, y, z);
	glRasterPos2f(0, 0);
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *string++);
	glPopMatrix();
}



void desenhaEixos(void) {
	// Temporario - Auxiliar do Projeto

	materialCorGenerico(VERDE_ESCURO);
	glBegin(GL_LINES);																	// -X
	glVertex3i(-15, 0, 0);
	glVertex3i(0, 0, 0);
	glEnd();

	materialCorGenerico(VERDE_CLARO);
	glBegin(GL_LINES);																	// X
	glVertex3i(0, 0, 0);
	glVertex3i(15, 0, 0);
	glEnd();

	materialCorGenerico(VERMELHO_ESCURO);
	glBegin(GL_LINES);																	// -Y
	glVertex3i(0, -15, 0);
	glVertex3i(0, 0, 0);
	glEnd();

	materialCorGenerico(VERMELHO);
	glBegin(GL_LINES);																	// Y
	glVertex3i(0, 0, 0);
	glVertex3i(0, 15, 0);
	glEnd();

	materialCorGenerico(AZUL_ESCURO);
	glBegin(GL_LINES);																	// -Z
	glVertex3i(0, 0, -15);
	glVertex3i(0, 0, 0);
	glEnd();

	materialCorGenerico(AZUL_CLARO);
	glBegin(GL_LINES);																	// Z
	glVertex3i(0, 0, 0);
	glVertex3i(0, 0, 15);
	glEnd();
}



void desenhaLocalObservador(void) {
	// Desenha Cubo: Local Onde o Observador esta.

	materialCorGenerico(LARANJA);
	glPushMatrix();
	glTranslatef(xObs, yObs, zObs);														// Observador
	glutSolidCube(2);																	// Cubo
	glPopMatrix();
}



void desenhaVerAlvoObservador(void) {
	// Desenha Cubo: para Onde o Observador esta a Olhar.

	materialCorGenerico(AMARELO);
	glPushMatrix();
	glTranslatef(xAlvo, yAlvo, zAlvo);													// Alvo
	glutSolidCube(2);																	// Cubo
	glPopMatrix();
}



void desenhaLocalLuzes(void) {
	// Desenha Cubo: Luzes

	materialCorGenerico(ROSA);
	glPushMatrix();
	glTranslatef(luz_0_posicao[0], luz_0_posicao[1], luz_0_posicao[2]);					// Luz 0
	glutSolidCube(2);																	// Cubo
	glPopMatrix();

	materialCorGenerico(ROXO);
	glPushMatrix();
	glTranslatef(luz_1_posicao[0], luz_1_posicao[1], luz_1_posicao[2]);					// Luz 1
	glutSolidCube(2);																	// Cubo
	glPopMatrix();
}



void desenhaInfo(void) {
	// Escreve/Desenha no Ecra MAPA

	materialCorGenerico(PRETO);
	sprintf_s(texto, 30, "MAPA");
	desenhaTexto(texto, -7, 0, -20);
}



void desenhaInfo2(void) {
	// Escreve/Desenha no Ecra o Tipo de Projecao

	materialCorGenerico(PRETO);
	if (tipoProjeccao)
		sprintf_s(texto, 30, "ORTOGONAL");
	else
		sprintf_s(texto, 30, "PERSPECTIVA");
	desenhaTexto(texto, 0, 0, 0);
}



void desenhaPorta(void) {
	// Desenha Porta >>> Varios Componentes da Porta

	glPushMatrix();																		// ### Shift -Y e -X (Recentrar - Descer Porta) ###
	glTranslatef(-largura_total / 2, 0, 0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, lista_texturas[0]);

	// Peca Diagonal Atras
	glPushMatrix();
	glTranslatef(largura_porta + espessura_geral * 2 + espessura_peca_diagonal / 2, espessura_geral, espessura_peca_diagonal / 2);
	glRotatef(-angulo, 0, 0, 1);
	glTranslatef(0, tamanho_peca_diagonal / 2, 0);
	glScalef(espessura_peca_diagonal / 2, tamanho_peca_diagonal / 2, espessura_peca_diagonal / 2);
	//desenhaCubo(1, CASTANHO_ESCURO, CASTANHO_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO);
	desenhaCubo(1, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO);
	glPopMatrix();

	// Peca Diagonal Frente
	glPushMatrix();
	glTranslatef(largura_porta + espessura_geral * 2 + espessura_peca_diagonal / 2, espessura_geral, espessura_peca_diagonal / 2 + espessura_janela + espessura_peca_diagonal);
	glRotatef(-angulo, 0, 0, 1);
	glTranslatef(0, tamanho_peca_diagonal / 2, 0);
	glScalef(espessura_peca_diagonal / 2, tamanho_peca_diagonal / 2, espessura_peca_diagonal / 2);
	//desenhaCubo(1, CASTANHO_ESCURO, CASTANHO_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO);
	desenhaCubo(1, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, lista_texturas[0]);

	// Ombreira 5 (ver esboco)
	glPushMatrix();
	glTranslatef(largura_total - largura_ombreira5 + largura_ombreira5 / 2, espessura_geral / 2, espessura_geral / 2);
	glScalef(largura_ombreira5 / 2, espessura_geral / 2, espessura_geral / 2);
	//desenhaCubo(1, CASTANHO_ESCURO, CASTANHO_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO);
	desenhaCubo(1, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO);
	glPopMatrix();

	// Ombreira 4 (ver esboco)
	glPushMatrix();
	glTranslatef(largura_total - espessura_geral / 2, altura_ombreira1 / 2, espessura_geral / 2);
	glScalef(espessura_geral / 2, altura_ombreira1 / 2, espessura_geral / 2);
	//desenhaCubo(1, CASTANHO_ESCURO, CASTANHO_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO);
	desenhaCubo(1, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO);
	glPopMatrix();

	// Ombreira 3 (ver esboco)
	glPushMatrix();
	glTranslatef(largura_total - largura_ombreira5 + espessura_geral / 2, altura_ombreira1 / 2, espessura_geral / 2);
	glScalef(espessura_geral / 2, altura_ombreira1 / 2, espessura_geral / 2);
	//desenhaCubo(1, CASTANHO_ESCURO, CASTANHO_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO);
	desenhaCubo(1, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO);
	glPopMatrix();

	// Ombreira 2 (ver esboco)
	glPushMatrix();
	glTranslatef(largura_ombreira2 / 2, altura_porta + espessura_geral / 2, espessura_geral / 2);
	glScalef(largura_ombreira2 / 2, espessura_geral / 2, espessura_geral / 2);
	//desenhaCubo(1, CASTANHO_ESCURO, CASTANHO_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO);
	desenhaCubo(1, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	// ---------- ANIMACAO: PORTA ----------
	glPushMatrix();
	glTranslatef(espessura_geral, 0, 0);
	glRotatef(porta_rotacao, 0, 1, 0);
	glTranslatef(-espessura_geral, 0, 0);

	// ***** CAO *****

	// =========== ANIMACAO: CAO ===========
	glPushMatrix();
	glTranslatef(0, cao_translacao, 0);

	// CAO - Puxador
	glPushMatrix();
	glTranslatef((largura_porta_cao / 2) + espessura_geral + largura_porta_parte2e3, (altura_porta_cao / 3) * 2 + altura_porta_parte4 + espessura_ombreira_cao / 2, -espessura_ombreira_cao / 2 - espessura_ombreira_cao);
	glScalef((largura_porta_cao / 2) / 2, espessura_ombreira_cao / 2, espessura_ombreira_cao / 2);
	materialEspecifico(polished_silver_ambient, polished_silver_diffuse, polished_silver_specular, polished_silver_shine);
	desenhaCuboSimples(1);
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, lista_texturas[1]);

	// CAO - Porta
	glPushMatrix();
	glTranslatef(largura_porta_cao / 2 + espessura_geral + largura_porta_parte2e3, altura_porta_parte4 + altura_porta_cao / 2, -espessura_ombreira_cao / 2);
	glScalef(largura_porta_cao / 2, altura_porta_cao / 2, espessura_ombreira_cao / 2);
	//desenhaCubo(1, CASTANHO, CASTANHO, CASTANHO_CLARO, CASTANHO_CLARO, CASTANHO_CLARO, CASTANHO_CLARO);
	desenhaCubo(1, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	// =========== FIM-ANIMACAO: CAO ===========
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, lista_texturas[0]);

	// CAO - Ombreira 4 Cima
	glPushMatrix();
	glTranslatef(largura_porta_cao / 2 + largura_porta_parte2e3 + espessura_geral, altura_porta_parte4 + altura_porta_cao - espessura_ombreira_cao / 2, espessura_geral / 2);
	glScalef(largura_porta_cao / 2, espessura_ombreira_cao / 2, espessura_geral / 2);
	//desenhaCubo(1, CASTANHO_ESCURO, CASTANHO_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO);
	desenhaCubo(1, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO);
	glPopMatrix();

	// CAO - Ombreira 3 Baixo
	glPushMatrix();
	glTranslatef(largura_porta_cao / 2 + largura_porta_parte2e3 + espessura_geral, altura_porta_parte4 + espessura_ombreira_cao / 2, espessura_geral / 2);
	glScalef(largura_porta_cao / 2, espessura_ombreira_cao / 2, espessura_geral / 2);
	//desenhaCubo(1, CASTANHO_ESCURO, CASTANHO_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO);
	desenhaCubo(1, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO);
	glPopMatrix();

	// CAO - Ombreira 2 Esquerda
	glPushMatrix();
	glTranslatef(-espessura_ombreira_cao / 2 + largura_porta_parte2e3 + largura_porta_cao + espessura_geral, altura_porta_parte4 + altura_porta_cao / 2, espessura_geral / 2);
	glScalef(espessura_ombreira_cao / 2, altura_porta_cao / 2, espessura_geral / 2);
	//desenhaCubo(1, CASTANHO_ESCURO, CASTANHO_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO);
	desenhaCubo(1, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO);
	glPopMatrix();

	// CAO - Ombreira 1 Direita
	glPushMatrix();
	glTranslatef(espessura_ombreira_cao / 2 + largura_porta_parte2e3 + espessura_geral, altura_porta_parte4 + altura_porta_cao / 2, espessura_geral / 2);
	glScalef(espessura_ombreira_cao / 2, altura_porta_cao / 2, espessura_geral / 2);
	//desenhaCubo(1, CASTANHO_ESCURO, CASTANHO_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO);
	desenhaCubo(1, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	// ***** FIM - CAO *****

	// ***** PORTA *****

	// PORTA - Puxador Atras
	glPushMatrix();
	glTranslatef(largura_puxador / 2 + espessura_geral + (largura_porta / 5) * 4, altura_puxador / 2 + altura_porta / 2, -espessura_puxador / 2);
	glScalef(largura_puxador / 2, altura_puxador / 2, espessura_puxador / 2);
	materialEspecifico(polished_silver_ambient, polished_silver_diffuse, polished_silver_specular, polished_silver_shine);
	desenhaCuboSimples(1);
	glPopMatrix();

	// PORTA - Puxador Frente
	glPushMatrix();
	glTranslatef(largura_puxador / 2 + espessura_geral + (largura_porta / 5) * 4, altura_puxador / 2 + altura_porta / 2, espessura_geral + espessura_puxador / 2);
	glScalef(largura_puxador / 2, altura_puxador / 2, espessura_puxador / 2);
	materialEspecifico(polished_silver_ambient, polished_silver_diffuse, polished_silver_specular, polished_silver_shine);
	desenhaCuboSimples(1);
	glPopMatrix();


	// PORTA - Parte 1
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, lista_texturas[2]);

	glPushMatrix();
	glTranslatef(largura_porta_parte1 / 2 + espessura_geral, altura_porta_parte4 + altura_porta_parte2e3 + altura_porta_parte1 / 2, espessura_geral / 2);
	glScalef(largura_porta_parte1 / 2, altura_porta_parte1 / 2, espessura_geral / 2);
	//desenhaCubo(1, CASTANHO_VERDADEIRO, CASTANHO_VERDADEIRO, CASTANHO, CASTANHO, CASTANHO, CASTANHO);
	desenhaCubo(1, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO);
	glPopMatrix();

	// PORTA - Parte 2
	glPushMatrix();
	glTranslatef(largura_porta_parte2e3 / 2 + espessura_geral, altura_porta_parte4 + altura_porta_parte2e3 / 2, espessura_geral / 2);
	glScalef(largura_porta_parte2e3 / 2, altura_porta_parte2e3 / 2, espessura_geral / 2);
	//desenhaCubo(1, CASTANHO_VERDADEIRO, CASTANHO_VERDADEIRO, CASTANHO, CASTANHO, CASTANHO, CASTANHO);
	desenhaCubo(1, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO);
	glPopMatrix();

	// PORTA - Parte 3
	glPushMatrix();
	glTranslatef(largura_porta_parte2e3 / 2 + espessura_geral + largura_porta_parte2e3 + largura_porta_cao, altura_porta_parte4 + altura_porta_parte2e3 / 2, espessura_geral / 2);
	glScalef(largura_porta_parte2e3 / 2, altura_porta_parte2e3 / 2, espessura_geral / 2);
	//desenhaCubo(1, CASTANHO_VERDADEIRO, CASTANHO_VERDADEIRO, CASTANHO, CASTANHO, CASTANHO, CASTANHO);
	desenhaCubo(1, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO);
	glPopMatrix();

	// PORTA - Parte 4
	glPushMatrix();
	glTranslatef(largura_porta_parte4 / 2 + espessura_geral, altura_porta_parte4 / 2, espessura_geral / 2);
	glScalef(largura_porta_parte4 / 2, altura_porta_parte4 / 2, espessura_geral / 2);
	//desenhaCubo(1, CASTANHO_VERDADEIRO, CASTANHO_VERDADEIRO, CASTANHO, CASTANHO, CASTANHO, CASTANHO);
	desenhaCubo(1, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	// ***** FIM - PORTA *****

	glPopMatrix();
	// ---------- FIM-ANIMACAO: PORTA ----------

	// Ombreira 1 (ver esboco)
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, lista_texturas[0]);

	glPushMatrix();
	glTranslatef(espessura_geral / 2, altura_ombreira1 / 2, espessura_geral / 2);
	glScalef(espessura_geral / 2, altura_ombreira1 / 2, espessura_geral / 2);
	//desenhaCubo(1, CASTANHO_ESCURO, CASTANHO_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO, CASTANHO_SUPER_ESCURO);
	desenhaCubo(1, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO, BRANCO);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	// Janela
	glPushMatrix();
	glTranslatef(largura_janela / 2 + largura_porta + espessura_geral * 2, altura_janela / 2 + espessura_geral, espessura_janela / 2 + espessura_peca_diagonal);
	glScalef(largura_janela / 2, altura_janela / 2, espessura_janela / 2);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	desenhaCubo(1, AZUL_VIDRO_A, AZUL_VIDRO_A, AZUL_VIDRO_A, AZUL_VIDRO_A, AZUL_VIDRO_A, AZUL_VIDRO_A);
	glPopMatrix();

	glPopMatrix();
}



void desenhaCubo(GLfloat dimensao, GLfloat cor_f1, GLfloat cor_f2, GLfloat cor_f3, GLfloat cor_f4, GLfloat cor_a1, GLfloat cor_a2, GLfloat cor_a3, GLfloat cor_a4, GLfloat cor_c1, GLfloat cor_c2, GLfloat cor_c3, GLfloat cor_c4, GLfloat cor_b1, GLfloat cor_b2, GLfloat cor_b3, GLfloat cor_b4, GLfloat cor_e1, GLfloat cor_e2, GLfloat cor_e3, GLfloat cor_e4, GLfloat cor_d1, GLfloat cor_d2, GLfloat cor_d3, GLfloat cor_d4) {
	// Desenha Cubo Simples com Dimensao=dimensao e Cores nas Faces pela Ordem: frente, atras, cima, baixo, esquerda, direita

	glPushMatrix();
	glScalef(dimensao, dimensao, dimensao);

	materialCorGenerico(cor_f1, cor_f2, cor_f3, cor_f4);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cubo_frente);

	materialCorGenerico(cor_a1, cor_a2, cor_a3, cor_a4);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cubo_atras);

	materialCorGenerico(cor_c1, cor_c2, cor_c3, cor_c4);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cubo_cima);

	materialCorGenerico(cor_b1, cor_b2, cor_b3, cor_b4);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cubo_baixo);

	materialCorGenerico(cor_e1, cor_e2, cor_e3, cor_e4);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cubo_esquerda);

	materialCorGenerico(cor_d1, cor_d2, cor_d3, cor_d4);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cubo_direita);
	glPopMatrix();

}



void printHelp(void) {
	// Print na Consola: Help

	printf("\n\n########## AJUDA ##########\n");

	printf("#\n");
	printf("# (KEY : FUNCAO)\n");

	printf("#\n");
	printf("# SUPORTE:\n");
	printf("# KEY \'%s\'\t:\t%s\n", "<ESC>", "Sair/Parar Execucao");
	printf("# KEY \'%s\'\t:\t%s\n", "H", "Print Ajuda");
	printf("# KEY \'%s\'\t:\t%s\n", "R", "Reiniciar Todo o Cenario");
	printf("# KEY \'%s\'\t:\t%s\n", "P", "Trocar Projecao");
	printf("# KEY \'%s\'\t:\t%s\n", "Q", "Ligar/Desligar a Legenda/Planta");
	printf("# KEY \'%s\'\t:\t%s\n", "E", "Ligar/Desligar os Eixos Auxiliares");
	printf("# KEY \'%s\'\t:\t%s\n", "B", "Ligar/Desligar os DEBUG Auxiliar: Luzes, Alvo");

	printf("#\n");
	printf("# OBSERVADOR Pseudo-Primeira-Pessoa (Meta 1):\n");
	printf("# KEY \'%s\'\t:\t%s\n", "<left>", "Mover - para a Esquerda (Obs + Alvo)");
	printf("# KEY \'%s\'\t:\t%s\n", "<right>", "Mover - para a Direita (Obs + Alvo)");
	printf("# KEY \'%s\'\t:\t%s\n", "<up>", "Mover - para a Frente (Obs + Alvo)");
	printf("# KEY \'%s\'\t:\t%s\n", "<down>", "Mover - para Tras (Obs + Alvo)");
	printf("# KEY \'%s\'\t:\t%s\n", "W", "Subir - o Obs em Torno do Alvo");
	printf("# KEY \'%s\'\t:\t%s\n", "S", "Descer - o Obs em Torno do Alvo");
	printf("# KEY \'%s\'\t:\t%s\n", "A", "Rodar - o Obs para a Esquerda em Torno do Alvo");
	printf("# KEY \'%s\'\t:\t%s\n", "D", "Rodar - o Obs para a Direita em Torno do Alvo");
	printf("# KEY \'%s\'\t:\t%s\n", "F", "+Zoom - Aproximar o Obs ao Alvo");
	printf("# KEY \'%s\'\t:\t%s\n", "G", "-Zoom - Afastar o Obs do Alvo");

	printf("#\n");
	printf("# ANIMACAO (Meta 1):\n");
	printf("# KEY \'%s\'\t:\t%s\n", "Z", "Abrir Porta Principal");
	printf("# KEY \'%s\'\t:\t%s\n", "X", "Fechar Porta Principal");
	printf("# KEY \'%s\'\t:\t%s\n", "C", "Abrir Portinhola Cao");
	printf("# KEY \'%s\'\t:\t%s\n", "V", "Fechar Portinhola Cao");

	printf("#\n");
	printf("# ILUMINACAO / TEXTURA / COR (Meta 2):\n");
	printf("# KEY \'%s\'\t:\t%s\n", "0", "Aumentar Intensidade Luz Global");
	printf("# KEY \'%s\'\t:\t%s\n", "1", "Ligar/Desligar Luz Pontual Exterior (0)");
	printf("# KEY \'%s\'\t:\t%s\n", "2", "Ligar/Desligar Luz Foco Interior (1)");
	printf("# KEY \'%s\'\t:\t%s\n", "3", "Aumentar Intensidade Luz Pontual Exterior (0)");
	printf("# KEY \'%s\'\t:\t%s\n", "4", "Aumentar Intensidade Luz Foco Interior (1)");
	printf("# KEY \'%s\'\t:\t%s\n", "5", "Incrementar Coeficiente Brilho Geral e Brilho Silver");
	printf("# KEY \'%s\'\t:\t%s\n", "6", "Decrementar Coeficiente Brilho Geral e Brilho Silver");
	printf("# KEY \'%s\'\t:\t%s\n", "7", "Ligar/Desligar Componente Red da Luz");
	printf("# KEY \'%s\'\t:\t%s\n", "8", "Ligar/Desligar Componente Green da Luz");
	printf("# KEY \'%s\'\t:\t%s\n", "9", "Ligar/Desligar Componente Blue da Luz");
	printf("# KEY \'%s\'\t:\t%s\n", "M", "Aumentar Numero de Pedacos da Malha");
	printf("# KEY \'%s\'\t:\t%s\n", "N", "Diminuir Numero de Pedacos da Malha");
	printf("# KEY \'%s\'\t:\t%s\n", "Y", "Mover Luz 1 para Frente");
	printf("# KEY \'%s\'\t:\t%s\n", "U", "Mover Luz 1 para Tras");
	printf("# KEY \'%s\'\t:\t%s\n", "I", "Mover Luz 1 para Esquerda");
	printf("# KEY \'%s\'\t:\t%s\n", "O", "Mover Luz 1 para Direita");
	printf("# KEY \'%s\'\t:\t%s\n", "K", "Mover Luz 1 para Baixo");
	printf("# KEY \'%s\'\t:\t%s\n", "L", "Mover Luz 1 para Cima");

	printf("###########################\n\n");
}



void teclado(unsigned char key, int x, int y) {
	// EVENTOS: teclado teclas normais

	switch (key) {

	case 'h':
	case 'H':																			// Print Ajuda na Consola (Key e Funcao)
		printf(">>> \'%s\' : %s\n", "H", "Print Ajuda");
		printHelp();
		break;

	case 'p':
	case 'P':																			// troca tipo projecao entre 0 > 1 > 0 > ...
		printf(">>> \'%s\' : %s\n", "P", "Trocar Projecao");
		tipoProjeccao = (tipoProjeccao + 1) % 2;
		glutPostRedisplay();															// marks the current window as needing to be redisplayed.
		break;

	case 'q':
	case 'Q':																			// ignorar legenda?
		printf(">>> \'%s\' : %s\n", "Q", "Ligar/Desligar a Legenda/Planta");
		ignorar_legenda = (ignorar_legenda + 1) % 2;
		glutPostRedisplay();
		break;

	case 'e':
	case 'E':																			// ignorar eixos?
		printf(">>> \'%s\' : %s\n", "E", "Ligar/Desligar os Eixos Auxiliares");
		ignorar_eixos = (ignorar_eixos + 1) % 2;
		glutPostRedisplay();
		break;

	case 'b':
	case 'B':																			// ignorar debug?
		printf(">>> \'%s\' : %s\n", "B", "Ligar/Desligar os DEBUG Auxiliar: Luzes, Alvo");
		ignorar_debug = (ignorar_debug + 1) % 2;
		glutPostRedisplay();
		break;

	case 'r':
	case 'R':																			// Reiniciar os valores do programa (PROJECAO) e  (ANIMACAO)
		printf(">>> \'%s\' : %s\n", "R", "Reiniciar Todo o Cenario");
		iniciaVarsGlobaisPadrao();
		updateLuzes();
		glutPostRedisplay();
		break;

	case 'w':
	case 'W':																			// Mover paara cima Y
		printf(">>> \'%s\' : %s\n", "W", "Subir - o Obs em Torno do Alvo");
		yObs = yObs + MOVE_INC;
		if (yObs > Y_OBS_MAX)
			yObs = Y_OBS_MAX;
		glutPostRedisplay();
		break;

	case 's':
	case 'S':																			// Mover para baixo Y
		printf(">>> \'%s\' : %s\n", "S", "Descer - o Obs em Torno do Alvo");
		yObs = yObs - MOVE_INC;
		if (yObs < -Y_OBS_MAX)
			yObs = -Y_OBS_MAX;
		glutPostRedisplay();
		break;

	case 'a':
	case 'A':																			// Rodar em torno do Alvo <-
		printf(">>> \'%s\' : %s\n", "A", "Rodar - o Obs para a Esquerda em Torno do Alvo");
		aVisao = aVisao + ANGULO_INC;
		xObs = rVisao * cos(aVisao) + xAlvo;
		zObs = rVisao * sin(aVisao) + zAlvo;
		glutPostRedisplay();
		break;

	case 'd':
	case 'D':																			// Rodar em torno do Alvo ->
		printf(">>> \'%s\' : %s\n", "D", "Rodar - o Obs para a Direita em Torno do Alvo");
		aVisao = aVisao - ANGULO_INC;
		xObs = rVisao * cos(aVisao) + xAlvo;
		zObs = rVisao * sin(aVisao) + zAlvo;
		glutPostRedisplay();
		break;

	case 'f':
	case 'F':																			// + Zoom | O observador aproxima-se
		printf(">>> \'%s\' : %s\n", "F", "+Zoom - Aproximar o Obs ao Alvo");
		rVisao = rVisao - RAIO_INC;
		if (rVisao < RAIO_MIN)
			rVisao = RAIO_MIN;
		xObs = rVisao * cos(aVisao) + xAlvo;
		zObs = rVisao * sin(aVisao) + zAlvo;
		glutPostRedisplay();
		break;

	case 'g':
	case 'G':																			// - Zoom | O observador afasta-se
		printf(">>> \'%s\' : %s\n", "G", "-Zoom - Afastar o Obs do Alvo");
		rVisao = rVisao + RAIO_INC;
		if (rVisao > RAIO_MAX)
			rVisao = RAIO_MAX;
		xObs = rVisao * cos(aVisao) + xAlvo;
		zObs = rVisao * sin(aVisao) + zAlvo;
		glutPostRedisplay();
		break;

	case 'z':
	case 'Z':																			// Animacao: Abrir Porta (Principal)
		printf(">>> \'%s\' : %s\n", "Z", "Abrir Porta Principal");
		porta_rotacao = porta_rotacao + porta_rotacao_inc;
		if (porta_rotacao > porta_rotacao_max)   porta_rotacao = porta_rotacao_max;
		glutPostRedisplay();
		break;

	case 'x':
	case 'X':																			// Animacao: Fechar Porta (Principal)
		printf(">>> \'%s\' : %s\n", "X", "Fechar Porta Principal");
		porta_rotacao = porta_rotacao - porta_rotacao_inc;
		if (porta_rotacao < porta_rotacao_min)   porta_rotacao = porta_rotacao_min;
		glutPostRedisplay();
		break;

	case 'c':
	case 'C':																			// Animacao: Abrir Porta Cao
		printf(">>> \'%s\' : %s\n", "C", "Abrir Portinhola Cao");
		cao_translacao = cao_translacao + cao_translacao_inc;
		if (cao_translacao > cao_translacao_max)   cao_translacao = cao_translacao_max;
		glutPostRedisplay();
		break;

	case 'v':
	case 'V':																			// Animacao: Fechar Porta Cao
		printf(">>> \'%s\' : %s\n", "V", "Fechar Portinhola Cao");
		cao_translacao = cao_translacao - cao_translacao_inc;
		if (cao_translacao < cao_translacao_min)   cao_translacao = cao_translacao_min;
		glutPostRedisplay();
		break;

	case '0':																			// Ligar/Desligar == Aumentar Intensidade Luz Global/Ambiente
		printf(">>> \'%s\' : %s\n", "0", "Aumentar Intensidade Luz Global");
		luz_global_intensidade = luz_global_intensidade + INTENSIDADE_INC;
		if (luz_global_intensidade > (GLfloat) 1) {
			luz_global_intensidade = 0.0;
		}
		updateLuzes();
		glutPostRedisplay();
		break;

	case '1':																			// Ligar/Desligar Luz 0
		printf(">>> \'%s\' : %s\n", "1", "Ligar/Desligar Luz Pontual Exterior (0)");
		luz_0_switch = !luz_0_switch;
		glutPostRedisplay();
		break;

	case '2':																			// Ligar/Desligar Luz 1
		printf(">>> \'%s\' : %s\n", "2", "Ligar/Desligar Luz Foco Interior (1)");
		luz_1_switch = !luz_1_switch;
		glutPostRedisplay();
		break;

	case '3':																			// Aumentar Intensidade Luz 0
		printf(">>> \'%s\' : %s\n", "3", "Aumentar Intensidade Luz Pontual Exterior (0)");
		luz_0_intensidade = luz_0_intensidade + INTENSIDADE_INC;
		if (luz_0_intensidade > (GLfloat)1) {
			luz_0_intensidade = 0.0;
		}
		updateLuzes();
		glutPostRedisplay();
		break;

	case '4':																			// Aumentar Intensidade Luz 1
		printf(">>> \'%s\' : %s\n", "4", "Aumentar Intensidade Luz Foco Interior (1)");
		luz_1_intensidade = luz_1_intensidade + INTENSIDADE_INC;
		if (luz_1_intensidade > (GLfloat)1) {
			luz_1_intensidade = 0.0;
		}
		updateLuzes();
		glutPostRedisplay();
		break;

	case '5':																			// Incrementar Coeficiente Brilho Geral e Brilho Silver
		printf(">>> \'%s\' : %s\n", "5", "Incrementar Coeficiente Brilho Geral e Brilho Silver");
		shine_geral = shine_geral + BRILHO_INC;
		polished_silver_shine = polished_silver_shine + BRILHO_INC;
		if (shine_geral > (GLfloat) 128) {
			shine_geral = 128.0;
		}
		if (polished_silver_shine > (GLfloat)128) {
			polished_silver_shine = 128.0;
		}
		glutPostRedisplay();
		break;

	case '6':																			// Decrementar Coeficiente Brilho Geral e Brilho Silver
		printf(">>> \'%s\' : %s\n", "6", "Decrementar Coeficiente Brilho Geral e Brilho Silver");
		shine_geral = shine_geral - BRILHO_INC;
		polished_silver_shine = polished_silver_shine - BRILHO_INC;
		if (shine_geral < (GLfloat) 0) {
			shine_geral = 0.0;
		}
		if (polished_silver_shine < (GLfloat) 0) {
			polished_silver_shine = 0.0;
		}
		glutPostRedisplay();
		break;

	case '7':																			// Red
		printf(">>> \'%s\' : %s\n", "7", "Ligar/Desligar Componente Red da Luz");
		luzRed = !luzRed;
		updateLuzes();
		glutPostRedisplay();
		break;

	case '8':																			// Green
		printf(">>> \'%s\' : %s\n", "8", "Ligar/Desligar Componente Green da Luz");
		luzGreen = !luzGreen;
		updateLuzes();
		glutPostRedisplay();
		break;

	case '9':																			// Blue
		printf(">>> \'%s\' : %s\n", "9", "Ligar/Desligar Componente Blue da Luz");
		luzBlue = !luzBlue;
		updateLuzes();
		glutPostRedisplay();
		break;

	case 'm':
	case 'M':																			// + Pedacos
		printf(">>> \'%s\' : %s\n", "M", "Aumentar Numero de Pedacos da Malha");
		n_pedaco = n_pedaco + 2;
		if (n_pedaco > 128) {
			n_pedaco = 128;
		}
		glutPostRedisplay();
		break;

	case 'n':
	case 'N':																			// - Pedacos
		printf(">>> \'%s\' : %s\n", "N", "Diminuir Numero de Pedacos da Malha");
		n_pedaco = n_pedaco - 2;
		if (n_pedaco < 1) {
			n_pedaco = 1;
		}
		glutPostRedisplay();
		break;

	case 'y':
	case 'Y':																			// Mover Luz 1 para frente -Z
		printf(">>> \'%s\' : %s\n", "Y", "Mover Luz 1 para Frente");
		luz_1_posicao[2] = luz_1_posicao[2] - MOVE_INC;
		if (luz_1_posicao[2] < - DIM_MUNDO_Z)
			luz_1_posicao[2] = - DIM_MUNDO_Z;
		updateLuzes();
		glutPostRedisplay();
		break;

	case 'u':
	case 'U':																			// Mover Luz 1 para tras Z
		printf(">>> \'%s\' : %s\n", "U", "Mover Luz 1 para Tras");
		luz_1_posicao[2] = luz_1_posicao[2] + MOVE_INC;
		if (luz_1_posicao[2] > DIM_MUNDO_Z)
			luz_1_posicao[2] = DIM_MUNDO_Z;
		updateLuzes();
		glutPostRedisplay();
		break;

	case 'i':
	case 'I':																			// Mover Luz 1 para esquerda -X
		printf(">>> \'%s\' : %s\n", "I", "Mover Luz 1 para Esquerda");
		luz_1_posicao[0] = luz_1_posicao[0] - MOVE_INC;
		if (luz_1_posicao[0] < - DIM_MUNDO_X)
			luz_1_posicao[0] = - DIM_MUNDO_X;
		updateLuzes();
		glutPostRedisplay();
		break;

	case 'o':
	case 'O':																			// Mover Luz 1 para direita X
		printf(">>> \'%s\' : %s\n", "O", "Mover Luz 1 para Direita");
		luz_1_posicao[0] = luz_1_posicao[0] + MOVE_INC;
		if (luz_1_posicao[0] > DIM_MUNDO_X)
			luz_1_posicao[0] = DIM_MUNDO_X;
		updateLuzes();
		glutPostRedisplay();
		break;

	case 'k':
	case 'K':																			// Mover Luz 1 para baixo -Y
		printf(">>> \'%s\' : %s\n", "K", "Mover Luz 1 para Baixo");
		luz_1_posicao[1] = luz_1_posicao[1] - MOVE_INC;
		if (luz_1_posicao[1] < - DIM_MUNDO_Y)
			luz_1_posicao[1] = - DIM_MUNDO_Y;
		updateLuzes();
		glutPostRedisplay();
		break;

	case 'l':
	case 'L':																			// Mover Luz 1 para cima Y
		printf(">>> \'%s\' : %s\n", "L", "Mover Luz 1 para Cima");
		luz_1_posicao[1] = luz_1_posicao[1] + MOVE_INC;
		if (luz_1_posicao[1] > DIM_MUNDO_Y)
			luz_1_posicao[1] = DIM_MUNDO_Y;
		updateLuzes();
		glutPostRedisplay();
		break;

	case 27:																			// ESC/Escape >>> sair
		printf(">>> \'%s\' : %s\n", "<ESC>", "Sair/Parar Execucao");
		exit(0);
		break;
	
	default:
		printf("> ERRO: Tecla \'%c\' Nao Funcional | Press \'H\' para Ajuda.\n", key);
		break;
	}
}



void tecladoEspecial(int key, int x, int y) {
	// EVENTOS:  teclado teclas especiais


	if (key == GLUT_KEY_UP) {															// Deslocamento de xObs e xAlvo para a Frente em Z
		printf(">>> \'%s\' : %s\n", "<up>", "Mover - para a Frente (Obs + Alvo)");
		zAlvo = zAlvo - MOVE_INC;
		if (zAlvo < -Z_ALVO_MAX)
			zAlvo = -Z_ALVO_MAX;
		zObs = rVisao * sin(aVisao) + zAlvo;
	}


	if (key == GLUT_KEY_DOWN) {															// Deslocamento de xObs e xAlvo para a Tras em Z
		printf(">>> \'%s\' : %s\n", "<down>", "Mover - para Tras (Obs + Alvo)");
		zAlvo = zAlvo + MOVE_INC;
		if (zAlvo > Z_ALVO_MAX)
			zAlvo = Z_ALVO_MAX;
		zObs = rVisao * sin(aVisao) + zAlvo;
	}

	if (key == GLUT_KEY_LEFT) {															// Deslocamento de xObs e xAlvo para a Esquerda <- em X
		printf(">>> \'%s\' : %s\n", "<left>", "Mover - para a Esquerda (Obs + Alvo)");
		xAlvo = xAlvo - MOVE_INC;
		if (xAlvo < -X_ALVO_MAX)
			xAlvo = -X_ALVO_MAX;
		xObs = rVisao * cos(aVisao) + xAlvo;

	}

	if (key == GLUT_KEY_RIGHT) {														// Deslocamento de xObs e xAlvo para a Direita -> em X
		printf(">>> \'%s\' : %s\n", "<right>", "Mover - para a Direita (Obs + Alvo)");
		xAlvo = xAlvo + MOVE_INC;
		if (xAlvo > X_ALVO_MAX)
			xAlvo = X_ALVO_MAX;
		xObs = rVisao * cos(aVisao) + xAlvo;
	}

	glutPostRedisplay();																// marks the current window as needing to be redisplayed.
}



void iniciaTexturas(void) {
	// Iniciar texturas 
	
	glGenTextures(1, &lista_texturas[0]);
	glBindTexture(GL_TEXTURE_2D, lista_texturas[0]);
	imag.LoadBmpFile("Wood028_2K_Color.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

	glGenTextures(1, &lista_texturas[1]);
	glBindTexture(GL_TEXTURE_2D, lista_texturas[1]);
	imag.LoadBmpFile("Wood027_2K_Color.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

	glGenTextures(1, &lista_texturas[2]);
	glBindTexture(GL_TEXTURE_2D, lista_texturas[2]);
	imag.LoadBmpFile("Wood026_2K_Color.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

	glGenTextures(1, &lista_texturas[3]);
	glBindTexture(GL_TEXTURE_2D, lista_texturas[3]);
	imag.LoadBmpFile("PavingStones070_2K_Color.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

	glGenTextures(1, &lista_texturas[4]);
	glBindTexture(GL_TEXTURE_2D, lista_texturas[4]);
	imag.LoadBmpFile("Tiles074_2K_Color.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

	glGenTextures(1, &lista_texturas[5]);
	glBindTexture(GL_TEXTURE_2D, lista_texturas[5]);
	imag.LoadBmpFile("Bricks034_2K_Color.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

	glGenTextures(1, &lista_texturas[6]);
	glBindTexture(GL_TEXTURE_2D, lista_texturas[6]);
	imag.LoadBmpFile("Plaster002_2K_Color.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

}



void updateLuzes(void) {
	// Update Luzes

	luz_global_cor[0] = luz_global_intensidade;
	luz_global_cor[1] = luz_global_intensidade;
	luz_global_cor[2] = luz_global_intensidade;

	luz_0_ambiente[0] = luz_0_difusa[0] = luz_0_especular[0] = luzRed * luz_0_intensidade;
	luz_0_ambiente[1] = luz_0_difusa[1] = luz_0_especular[1] = luzGreen * luz_0_intensidade;
	luz_0_ambiente[2] = luz_0_difusa[2] = luz_0_especular[2] = luzBlue * luz_0_intensidade;
	luz_0_ambiente[3] = luz_0_difusa[3] = luz_0_especular[3] = 1.0;

	luz_1_ambiente[0] = luz_1_difusa[0] = luz_1_especular[0] = luzRed * luz_1_intensidade;
	luz_1_ambiente[1] = luz_1_difusa[1] = luz_1_especular[1] = luzGreen * luz_1_intensidade;
	luz_1_ambiente[2] = luz_1_difusa[2] = luz_1_especular[2] = luzBlue * luz_1_intensidade;
	luz_1_ambiente[3] = luz_1_difusa[3] = luz_1_especular[3] = 1.0;


	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz_global_cor);


	glLightfv(GL_LIGHT0, GL_POSITION, luz_0_posicao);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luz_0_ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_0_difusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luz_0_especular);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.01);


	glLightfv(GL_LIGHT1, GL_POSITION, luz_1_posicao);
	glLightfv(GL_LIGHT1, GL_AMBIENT, luz_1_ambiente);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luz_1_difusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, luz_1_especular);
	//glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, luz_1_foco_ak);							// specifies one of the three light attenuation factors.
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, luz_1_foco_al);								// specifies one of the three light attenuation factors.
	//glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, luz_1_foco_aq);							// specifies one of the three light attenuation factors.
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, luz_1_foco_abertura);								// specifies the maximum spread angle of a light source. 
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, luz_1_foco_direccao);							// specify the direction of the light in homogeneous object coordinates.
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, luz_1_foco_exp);									// specifies the intensity distribution of the light.
	
}


void iluminacao(void) {
	// Luzes

	if (luz_0_switch) {
		glEnable(GL_LIGHT0);
	} else {
		glDisable(GL_LIGHT0);
	}


	if (luz_1_switch) {
		glEnable(GL_LIGHT1);
	} else {
		glDisable(GL_LIGHT1);
	}
}



void cenarioExterior(void) {
	// Cenario Exterior Extra-Porta
	

	// Chao Exterior
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, lista_texturas[3]);
	materialCorGenerico(BRANCO);

	glTranslatef(0,0, (DIM_MUNDO_Z/2) + espessura_geral/2);
	glRotatef(-90, 1, 0, 0);
	desenhaPlano(DIM_MUNDO_X*2, DIM_MUNDO_Z, 4);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	// Parede Exterior - Esquerdo
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, lista_texturas[5]);
	materialCorGenerico(BRANCO);

	glTranslatef(- ((DIM_MUNDO_X - (largura_total/2))/2) - (largura_total / 2), altura_total / 2, espessura_geral);
	desenhaPlano(DIM_MUNDO_X - (largura_total/2), altura_total, 2);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	// Parede Exterior - Direito
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, lista_texturas[5]);
	materialCorGenerico(BRANCO);

	glTranslatef(+((DIM_MUNDO_X - (largura_total / 2)) / 2) + (largura_total / 2), altura_total / 2, espessura_geral);
	desenhaPlano(DIM_MUNDO_X - (largura_total / 2), altura_total, 2);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}



void cenarioInterior(void) {
	// Cenario Interior Extra-Porta



	// Chao Interior
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, lista_texturas[4]);
	materialCorGenerico(BRANCO);

	glTranslatef(0, 0, - (DIM_MUNDO_Z / 2) + (espessura_geral/2));
	glRotatef(-90, 1, 0, 0);
	desenhaPlano(DIM_MUNDO_X * 2, DIM_MUNDO_Z, 4);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	// Parede Interior - Esquerdo
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, lista_texturas[6]);
	materialCorGenerico(BRANCO);

	glTranslatef(-((DIM_MUNDO_X - (largura_total / 2)) / 2) - (largura_total / 2), altura_total / 2, 0);
	glRotatef(180, 0, 1, 0);
	desenhaPlano(DIM_MUNDO_X - (largura_total / 2), altura_total, 4);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	// Parede Interior - Direito
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, lista_texturas[6]);
	materialCorGenerico(BRANCO);

	glTranslatef(+((DIM_MUNDO_X - (largura_total / 2)) / 2) + (largura_total / 2), altura_total / 2, 0);
	glRotatef(180, 0, 1, 0);
	desenhaPlano(DIM_MUNDO_X - (largura_total / 2), altura_total, 4);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();





}



void materialCorGenerico(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	// Cor-Material

	GLfloat cor_amb[4];
	cor_amb[0] = r * 0.25;
	cor_amb[1] = g * 0.25;
	cor_amb[2] = b * 0.25;
	cor_amb[3] = 1;

	GLfloat cor_dif[4];
	cor_dif[0] = r * 0.4;
	cor_dif[1] = g * 0.4;
	cor_dif[2] = b * 0.4;
	cor_dif[3] = a;

	GLfloat cor_esp[4];
	cor_esp[0] = r * 0.774597;
	cor_esp[1] = g * 0.774597;
	cor_esp[2] = b * 0.774597;
	cor_esp[3] = 1;

	glMaterialfv(GL_FRONT, GL_AMBIENT, cor_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cor_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, cor_esp);
	glMaterialf(GL_FRONT, GL_SHININESS, shine_geral);

}



void materialEspecifico(GLfloat * amb, GLfloat * dif, GLfloat * esp, GLfloat coef) {
	// Material

	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, esp);
	glMaterialf(GL_FRONT, GL_SHININESS, coef);

}



void desenhaCuboSimples(GLfloat dimensao) {
	// Desenha Cubo Simples com Dimensao=dimensao

	glPushMatrix();
	glScalef(dimensao, dimensao, dimensao);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cubo_frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cubo_atras);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cubo_cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cubo_baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cubo_esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cubo_direita);
	glPopMatrix();
}



void desenhaPlano(GLfloat dimensaoX, GLfloat dimensaoY, int n_frag_textura) {
	// Desenha Plano Simples com Dimensao=dimensao, centrado (n_frag_textura = numero de mosaicos)

	int i, j;

	glPushMatrix();
	glTranslatef( -dimensaoX /2,  -dimensaoY/2, 0);										// meio do poligono 
	glScalef(dimensaoX, dimensaoY, 1);

	glNormal3f(0, 0, 1);																// Y
	glBegin(GL_QUADS);

	for (i = 0; i < n_pedaco; i++) {													// linha
		for (j = 0; j < n_pedaco; j++) {												// coluna
			//A
			glTexCoord2f((float)(j * n_frag_textura) / n_pedaco, (float)(i * n_frag_textura) / n_pedaco);
			glVertex3d((float)j / n_pedaco, (float)i / n_pedaco, 0);

			//B
			glTexCoord2f((float)((j + 1) * n_frag_textura) / n_pedaco, (float)(i * n_frag_textura) / n_pedaco);
			glVertex3d((float)(j + 1) / n_pedaco, (float)i / n_pedaco, 0);

			//C
			glTexCoord2f((float)((j + 1) * n_frag_textura) / n_pedaco, (float)((i + 1) * n_frag_textura) / n_pedaco);
			glVertex3d((float)(j + 1) / n_pedaco, (float)(i + 1) / n_pedaco, 0);

			//D
			glTexCoord2f(((float)j * n_frag_textura) / n_pedaco, (float)((i + 1) * n_frag_textura) / n_pedaco);
			glVertex3d((float)j / n_pedaco , (float)(i + 1) / n_pedaco, 0);
		}
	}
	glEnd();

	glPopMatrix();

}


