/* Projeto Meta 2 - Parte 2/N (Header File) ||| CG - LEI / FCTUC 2020/21 | Dario Filipe Torres Felix N.2018275530 */



/* ***** BIBLIOTECAS ***** */
#include <windows.h>
#include <stdlib.h>																		// geral padrao
#include <stdio.h>																		// standard input-output
#include <math.h>																		// funcoes matematicas basicas
#include <GL/Glut.h>																	// OpenGL Utility Toolkit (GLUT) is a library of utilities for OpenGL programs
#include "RgbImage.h"
//#include <GL/FreeGlut.h>


/* ***** CONSTANTES / MACROS ***** */
// Cores com Alpha Opaco
#define VERMELHO_ESCURO			0.5, 0.0, 0.0, 1.0
#define VERMELHO				1.0, 0.0, 0.0, 1.0
#define LARANJA					1.0, 0.502, 0.0, 1.0
#define AMARELO					1.0, 1.0, 0.0, 1.0
#define VERDE_CLARO				0.502, 1.0, 0.0, 1.0
#define VERDE_ESCURO			0.0, 0.4, 0.0, 1.0
#define VERDE					0.0, 1.0, 0.0, 1.0
#define VERDE_AGUA				0.0, 1.0, 0.502, 1.0
#define CIANO					0.0, 1.0, 1.0, 1.0
#define AZUL_CLARO				0.0, 0.502, 1.0, 1.0
#define AZUL_VIDRO				0.8, 1.0, 1.0, 1.0
#define AZUL					0.0, 0.0, 1.0, 1.0
#define AZUL_ESCURO				0.0, 0.0, 0.6, 1.0
#define ROXO					0.498, 0.0, 1.0, 1.0
#define ROSA					1.0, 0.0, 1.0, 1.0
#define MAGENTA					1.0, 0.0, 0.498, 1.0
#define BRANCO					1.0, 1.0, 1.0, 1.0
#define CINZENTO_CLARO			0.878, 0.878, 0.878, 1.0
#define CINZENTO				0.502, 0.502, 0.502, 1.0
#define CINZENTO_ESCURO			0.251, 0.251, 0.251, 1.0
#define CINZENTO_SUPER_ESCURO	0.1, 0.1, 0.1, 1.0
#define PRETO					0.0, 0.0, 0.0, 1.0
#define CASTANHO_SUPER_ESCURO	0.1, 0.01, 0.0, 1.0
#define CASTANHO_ESCURO			0.2, 0.098, 0.0, 1.0
#define CASTANHO				0.4, 0.2, 0.0, 1.0
#define CASTANHO_CLARO			0.6, 0.298, 0.0, 1.0
#define CASTANHO_VERDADEIRO		0.545, 0.271, 0.075, 1.0
#define AZUL_VIDRO_A			0.8, 1.0, 1.0, 0.5

// Constantes Matematicas
#define PI						3.14159

// Valores Iniciais
#define RAIO_INIT				15.0													// Observador: raio / distancia
#define ANGULO_INIT				PI/2													// Observador: Angulo - Partida Inicial a volta de YY / Coordenadas Plano xOz
#define PROJECAO_INIT			0														// boolean: qual projecao? ortog Vs persp
#define EIXOS_INIT				1														// boolean: ignorar eixos? sim Vs nao
#define DEBUG_INIT				1														// boolean: ignorar debug? sim Vs nao
#define LEGENDA_INIT			0														// boolean: ignorar legenda? sim Vs nao
#define Y_ALVO_INIT				5.0														// yAlvo (e yObservador)
#define X_ALVO_INIT				0.0														// xAlvo (e xObservador)
#define Z_ALVO_INIT				0.0														// zAlvo (e zObservador)
#define INTENSIDADE_0_INIT		1.0
#define INTENSIDADE_1_INIT		1.0
#define INTENSIDADE_GLOBAL_INIT	0.0
#define SWITCH_0_INIT			1
#define SWITCH_1_INIT			1
#define RGB_INIT				1.0
#define N_PEDACO_INIT			32	
#define X_LUZ_1_INIT			-15.0	
#define Y_LUZ_1_INIT			20.0	
#define Z_LUZ_1_INIT			10.0	
#define SHINE_GERAL_INIT		76.8	
#define SHINE_SILVER_INIT		89.6	

// Constantes Programa
#define MSEC					10														// refresh
#define LEN_TEXT				30
#define W_SCREEN				700														// janela largura
#define H_SCREEN				600														// janela altura

// Valores Cenario Constantes
#define DIM_CUBO				1
#define DIM_MUNDO_X				20.0
#define DIM_MUNDO_Y				100.0													// altura maxima mundo (perspetiva)
#define DIM_MUNDO_Z				20.0
#define ANGULO_Z				95														// Angulo Observador
#define X_ALVO_MAX				DIM_MUNDO_X/2											// MAX xAlvo (e xObservador)
#define Y_OBS_MAX				DIM_MUNDO_Y												// MAX yObservador
#define Z_ALVO_MAX				DIM_MUNDO_Z/2											// MAX zAlvo (e zObservador)
#define RAIO_MAX				19.0													// MAX ZOOM Observador: raio / distancia
#define RAIO_MIN				1.0														// MIN ZOOM Observador: raio / distancia
#define RAIO_INC				0.5														// INC raio / distancia de visao
#define ANGULO_INC				0.1														// INC angulo de visao
#define MOVE_INC				0.5														// INC <setas> em xOx e zOz (e yObs)
#define INTENSIDADE_INC			0.1
#define FOCO_ANGULO_INC			3.0
#define FOCO_ANGULO_MIN			3.0
#define FOCO_ANGULO_MAX			70.0
#define BRILHO_INC				10.0


/* ***** VARIAVEIS GLOBAIS ***** */
char		texto[LEN_TEXT];															// texto para escrever no ecra

GLfloat		rVisao;																		// Observador: raio / distancia
GLfloat		aVisao;																		// Observador: Angulo - Partida Inicial a volta de YY / Coordenadas Plano xOz

GLfloat		xObs;																		// xObservador - Local Onde o Observador Esta  | Coordenadas Plano xOz
GLfloat		yObs;																		// yObservador (Altura)
GLfloat		zObs;																		// zObservador | Coordenadas Plano xOz

GLfloat		xAlvo;																		// xAlvo - Para Onde o Observador Esta a Olhar
GLfloat		yAlvo;																		// yAlvo
GLfloat		zAlvo;																		// zAlvo

int			tipoProjeccao;																// boolean: qual projecao? ortog Vs persp
int			ignorar_legenda;															// boolean: ignorar legenda? sim Vs nao
int			ignorar_eixos;																// boolean: ignorar eixos? sim Vs nao
int			ignorar_debug;																// boolean: ignorar debug? sim Vs nao

GLfloat		cao_translacao_min;															// Porta-Cao Fechada
GLfloat		cao_translacao_max;															// Porta-Cao Aberta > translacao maxima = altura_porta_cao (e feito mais tarde o =)
GLfloat		cao_translacao;																// Porta-Cao Inicial
GLfloat		cao_translacao_inc;															// Incremento

GLfloat		porta_rotacao_min;															// Porta fechada > 0 graus
GLfloat		porta_rotacao_max;															// Porta aberta > 90 graus
GLfloat		porta_rotacao;																// Porta Inicial
GLfloat		porta_rotacao_inc;															// Incremento

GLfloat		espessura_geral;															// Z

GLfloat		altura_porta;																// Y
GLfloat		largura_porta;																// X

GLfloat		altura_porta_cao;															// Y
GLfloat		largura_porta_cao;															// X
GLfloat		espessura_ombreira_cao;														// X

GLfloat		largura_ombreira5;															// X

GLfloat		altura_total;																// Y
GLfloat		largura_total;																// X

GLfloat		altura_ombreira1;															// Y
GLfloat		largura_ombreira2;															// X

GLfloat		altura_janela;																// Y
GLfloat		largura_janela;																// X
GLfloat		espessura_janela;															// Z

GLfloat		tamanho_peca_diagonal;														// Y
GLfloat		espessura_peca_diagonal;													// Z
GLfloat		angulo;																		// Calculo de alfa e passar para garaus (o 1.1 >> para limar)

GLfloat		altura_porta_parte4;														// Y
GLfloat		largura_porta_parte4;														// X

GLfloat		altura_porta_parte1;														// Y
GLfloat		largura_porta_parte1;														// X

GLfloat		altura_porta_parte2e3;														// Y
GLfloat		largura_porta_parte2e3;														// X

GLfloat		altura_puxador;																// Y
GLfloat		largura_puxador;															// X
GLfloat		espessura_puxador;															// Z

GLuint		lista_texturas[7];
RgbImage	imag;


GLfloat		cubo_vertices[24 * 3] = {													// Vertices do Cubo
			-DIM_CUBO,  DIM_CUBO,  DIM_CUBO,											// Frente | 0
			-DIM_CUBO, -DIM_CUBO,  DIM_CUBO,											// 1
			 DIM_CUBO, -DIM_CUBO,  DIM_CUBO,											// 2
			 DIM_CUBO,  DIM_CUBO,  DIM_CUBO,											// 3
			-DIM_CUBO,  DIM_CUBO, -DIM_CUBO,											// Atras | 4
			 DIM_CUBO,  DIM_CUBO, -DIM_CUBO,											// 5
			 DIM_CUBO, -DIM_CUBO, -DIM_CUBO,											// 6
			-DIM_CUBO, -DIM_CUBO, -DIM_CUBO,											// 7
			-DIM_CUBO,  DIM_CUBO, -DIM_CUBO,											// Cima | 8
			-DIM_CUBO,  DIM_CUBO,  DIM_CUBO,											// 9
			 DIM_CUBO,  DIM_CUBO,  DIM_CUBO,											// 10
			 DIM_CUBO,  DIM_CUBO, -DIM_CUBO,											// 11
			-DIM_CUBO, -DIM_CUBO, -DIM_CUBO,											// Baixo | 12
			 DIM_CUBO, -DIM_CUBO, -DIM_CUBO,											// 13
			 DIM_CUBO, -DIM_CUBO,  DIM_CUBO,											// 14
			-DIM_CUBO, -DIM_CUBO,  DIM_CUBO,											// 15
			-DIM_CUBO,  DIM_CUBO, -DIM_CUBO,											// Esquerda | 16
			-DIM_CUBO, -DIM_CUBO, -DIM_CUBO,											// 17
			-DIM_CUBO, -DIM_CUBO,  DIM_CUBO,											// 18
			-DIM_CUBO,  DIM_CUBO,  DIM_CUBO,											// 19
			 DIM_CUBO,  DIM_CUBO, -DIM_CUBO,											// Direita | 20
			 DIM_CUBO,  DIM_CUBO,  DIM_CUBO,											// 21
			 DIM_CUBO, -DIM_CUBO,  DIM_CUBO,											// 22
			 DIM_CUBO, -DIM_CUBO, -DIM_CUBO												// 23
};

GLfloat		cubo_normais[24 * 3] = {													// Normais do Cubo
			 0,  0,  1,																	// Frente | 0 | Z
			 0,  0,  1,																	// 1
			 0,  0,  1,																	// 2
			 0,  0,  1,																	// 3
			 0,  0, -1,																	// Atras | 4 | -Z
			 0,  0, -1,																	// 5
			 0,  0, -1,																	// 6
			 0,  0, -1,																	// 7
			 0,  1,  0,																	// Cima | 8 | Y
			 0,  1,  0,																	// 9
			 0,  1,  0,																	// 10
			 0,  1,  0,																	// 11
			 0, -1,  0,																	// Baixo | 12 | -Y
			 0, -1,  0,																	// 13
			 0, -1,  0,																	// 14
			 0, -1,  0,																	// 15
			-1,  0,  0,																	// Esquerda | 16 | -X
			-1,  0,  0,																	// 17
			-1,  0,  0,																	// 18
			-1,  0,  0,																	// 19
			 1,  0,  0,																	// Direita | 20 | X
			 1,  0,  0,																	// 21
			 1,  0,  0,																	// 22
			 1,  0,  0																	// 23
};

GLfloat cubo_texturas[24 * 2] = {														// Mapeamento Textura do Cubo
			 0,  1,																		// Frente | 0 | Z
			 0,  0,																		// 1
			 1,  0,																		// 2
			 1,  1,																		// 3
			 1,  1,																		// Atras | 4 | -Z
			 0,  1,																		// 5
			 0,  0,																		// 6
			 1,  0,																		// 7
			 0,  1,																		// Cima | 8 | Y
			 0,  0,																		// 9
			 1,  0,																		// 10
			 1,  1,																		// 11
			 1,  1,																		// Baixo | 12 | -Y
			 0,  1,																		// 13
			 1,  1,																		// 14
			 1,  0,																		// 15
			 0,  1,																		// Esquerda | 16 | -X
			 0,  0,																		// 17
			 1,  0,																		// 18
			 1,  1,																		// 19
			 1,  1,																		// Direita | 20 | X
			 0,  1,																		// 21
			 0,  0,																		// 22
			 1,  0																		// 23
};

GLuint		cubo_frente[4] = { 0,1,2,3 };												// Face do Cubo: Frente
GLuint		cubo_atras[4] = { 4,5,6,7 };												// Face do Cubo: Atras
GLuint		cubo_cima[4] = { 8,9,10,11 };												// Face do Cubo: Cima
GLuint		cubo_baixo[4] = { 12,13,14,15 };											// Face do Cubo: Baixo
GLuint		cubo_esquerda[4] = { 16,17,18,19 };											// Face do Cubo: Esquerda
GLuint		cubo_direita[4] = { 20,21,22,23 };											// Face do Cubo: Direita


GLfloat		polished_silver_ambient[] = { 0.23125, 0.23125, 0.23125, 1.0 };				// Material Cinza-Polido
GLfloat		polished_silver_diffuse[] = { 0.2775, 0.2775, 0.2775, 1.0 };				// Material
GLfloat		polished_silver_specular[] = { 0.773911, 0.773911, 0.773911, 1.0 };			// Material
GLfloat		polished_silver_shine;														// Material

GLfloat		shine_geral;

GLfloat		luzRed;		 																// Vermelho
GLfloat		luzGreen;																	// Verde
GLfloat		luzBlue;																	// Azul

GLint		luz_0_switch;
GLfloat		luz_0_intensidade;															// Luz 0 | Intensidade 
GLfloat		luz_0_posicao[4];															// Luz 0 | Posicao
GLfloat		luz_0_ambiente[4];
GLfloat		luz_0_difusa[4];
GLfloat		luz_0_especular[4];

GLint		luz_1_switch;
GLfloat		luz_1_intensidade;															// Luz 1 | Intensidade 
GLfloat		luz_1_posicao[4];															// Luz 1 | Posicao
GLfloat		luz_1_ambiente[4];
GLfloat		luz_1_difusa[4];
GLfloat		luz_1_especular[4];

GLfloat		luz_1_foco_direccao[] = { 0, -1, 0, 0 };									// -Y
GLfloat		luz_1_foco_ak;
GLfloat		luz_1_foco_al;
GLfloat		luz_1_foco_aq;
GLfloat		luz_1_foco_exp;
GLfloat		luz_1_foco_abertura;

GLfloat		luz_global_intensidade;														// Luz Global | Intensidade 
GLfloat		luz_global_cor[3];															// Luz 0 | Posicao

int			n_pedaco;



/* ***** PROTOTIPOS ***** */
void inicia(void);
void Timer(int value);
void teclado(unsigned char key, int x, int y);
void tecladoEspecial(int key, int x, int y);
void cenario(void);
void desenhaTexto(char* string, GLfloat x, GLfloat y, GLfloat z);
void desenhaEixos(void);
void desenhaLocalObservador(void);
void desenhaVerAlvoObservador(void);
void desenhaInfo(void);
void desenhaPorta(void);
void desenhaCubo(GLfloat dimensao, GLfloat cor_f1, GLfloat cor_f2, GLfloat cor_f3, GLfloat cor_f4, GLfloat cor_a1, GLfloat cor_a2, GLfloat cor_a3, GLfloat cor_a4, GLfloat cor_c1, GLfloat cor_c2, GLfloat cor_c3, GLfloat cor_c4, GLfloat cor_b1, GLfloat cor_b2, GLfloat cor_b3, GLfloat cor_b4, GLfloat cor_e1, GLfloat cor_e2, GLfloat cor_e3, GLfloat cor_e4, GLfloat cor_d1, GLfloat cor_d2, GLfloat cor_d3, GLfloat cor_d4);
void desenhaInfo2(void);
void printHelp(void);
void iniciaVarsGlobaisPadrao(void);
void iniciaTexturas(void);
void updateLuzes(void);
void iluminacao(void);
void cenarioExterior(void);
void cenarioInterior(void);
void materialCorGenerico(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
void materialEspecifico(GLfloat* amb, GLfloat* dif, GLfloat* esp, GLfloat coef);
void desenhaCuboSimples(GLfloat dimensao);
void desenhaPlano(GLfloat dimensaoX, GLfloat dimensaoY, int n_frag_textura);
void desenhaLocalLuzes(void);

