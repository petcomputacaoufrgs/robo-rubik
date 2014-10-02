#include <opencv2/core/core.hpp>
#include "opencv/cv.h"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <math.h>
#include <fstream>

#define Rvermelho 0.35
#define Bazul 0.65
#define Gamarelo 0.39
#define Glaranja 0.25
#define Gverde 0.42

using namespace std;
using namespace cv;

class ColorRecognizer
{
private:
	char key;
	float totalBGR;
	float B, G, R;
	float totalMedia;
	int quadradoX,quadradoY;
	float azul, verde, laranja, amarelo, vermelho, branco;
	int contador;
public:
	ColorRecognizer() {
		totalMedia = 0;
		azul = 0;
		verde = 0;
		laranja = 0;
		amarelo = 0;
		vermelho = 0;
		branco = 0;
		contador = 0;
	}
  std::string getFaceColors() {
    ofstream faceCores;

    int linha, coluna;
    int x, y;

    string corFace;
    CvScalar v;

    cvNamedWindow("Recognizer", 1);    //Create window
    CvCapture* capture = cvCaptureFromCAM(CV_CAP_ANY);  //Capture using any camera connected to your system
    //while(1) {
    IplImage* frame;
    //while(cvWaitKey(10) != 'k') {
        frame = cvQueryFrame(capture); //Create image frames from capture
        cvShowImage("Recognizer", frame);   //Show image frames on created window

        for(  y=0; y<frame->height; y++ )
        {
            for( x=0; x<frame->width; x++ )
            {
                v = cvGet2D(frame, y, x);

                frame->imageData[y*frame->widthStep+3*x+0]=(uchar)255; //PINTANDO DE BRANCO TUDO
                frame->imageData[y*frame->widthStep+3*x+1]=(uchar)255;
                frame->imageData[y*frame->widthStep+3*x+2]=(uchar)255;

                B = v.val[0];
                G = v.val[1];
                R = v.val[2];
                totalBGR = B + G + R;

                B = B/totalBGR;
                G = G/totalBGR;
                R = R/totalBGR;

                if(B>Bazul)  //azul
                {
                    frame->imageData[y*frame->widthStep+3*x+0]=(uchar)255;
                    frame->imageData[y*frame->widthStep+3*x+1]=(uchar)0;
                    frame->imageData[y*frame->widthStep+3*x+2]=(uchar)0;
                }
                else if(R>Rvermelho)  //vermelho
                {
                    if(G>Gamarelo)  //amarelo
                    {
                        frame->imageData[y*frame->widthStep+3*x+0]=(uchar)0; //azul
                        frame->imageData[y*frame->widthStep+3*x+1]=(uchar)255; //verde
                        frame->imageData[y*frame->widthStep+3*x+2]=(uchar)255; //vermelho
                    }
                    else if(G>Glaranja) //laranja REVISAR
                    {
                        frame->imageData[y*frame->widthStep+3*x+0]=(uchar)0; //azul
                        frame->imageData[y*frame->widthStep+3*x+1]=(uchar)125; //verde
                        frame->imageData[y*frame->widthStep+3*x+2]=(uchar)255; //vermelho
                    }


                    else  //vermelho
                    {
                        frame->imageData[y*frame->widthStep+3*x+0]=(uchar)0; //azul
                        frame->imageData[y*frame->widthStep+3*x+1]=(uchar)0; //verde
                        frame->imageData[y*frame->widthStep+3*x+2]=(uchar)255; //vermelho
                    }
                }
                else if(G>Gverde) //verde
                {
                    frame->imageData[y*frame->widthStep+3*x+0]=(uchar)0;
                    frame->imageData[y*frame->widthStep+3*x+1]=(uchar)255;
                    frame->imageData[y*frame->widthStep+3*x+2]=(uchar)0;
                }

            }
        }
        for(  linha=0; linha<frame->height; linha++ )  //desenha as colunas
        {

            for( coluna=0; coluna<frame->width; coluna= coluna + 127 )
            {
                v = cvGet2D(frame, linha, coluna);
                frame->imageData[linha*frame->widthStep+3*coluna+0]=(uchar)0; //PINTANDO DE PRETO
                frame->imageData[linha*frame->widthStep+3*coluna+1]=(uchar)0;
                frame->imageData[linha*frame->widthStep+3*coluna+2]=(uchar)0;
            }
        }
        for(  linha=75; linha<frame->height; linha = linha +127 )  //desenha as linhas
        {

            for( coluna=0; coluna<frame->width; coluna++ )
            {
                v = cvGet2D(frame, linha, coluna);
                frame->imageData[linha*frame->widthStep+3*coluna+0]=(uchar)0; //PINTANDO DE PRETO
                frame->imageData[linha*frame->widthStep+3*coluna+1]=(uchar)0;
                frame->imageData[linha*frame->widthStep+3*coluna+2]=(uchar)0;
            }
        }
        corFace = "";
        for(quadradoY=0; quadradoY<=254; quadradoY = quadradoY + 127) //FAZENDO PARA CADA QUADRADO DO CUBO
        {
            for(quadradoX=0; quadradoX<=254; quadradoX = quadradoX + 127)
            {
                for(  linha=75 + 25 + quadradoY; linha<75+127 -25 + quadradoY; linha++ )   //TESTANDO O PRIMEIRO QUADRADO -> FAZER ISSO 9 VEZES PARA CADA QUADRADO
                {
                    for( coluna=127 + 25 + quadradoX; coluna<127 + 127 -25 +quadradoX; coluna++ )
                    {
                        v = cvGet2D(frame, linha, coluna);
                        frame->imageData[linha*frame->widthStep+3*coluna+0]=(uchar)0; //PINTANDO DE PRETO
                        frame->imageData[linha*frame->widthStep+3*coluna+1]=(uchar)0;
                        frame->imageData[linha*frame->widthStep+3*coluna+2]=(uchar)0;
                        B = v.val[0];
                        G = v.val[1];
                        R = v.val[2];
                        totalBGR = B + G + R;

                        B = B/totalBGR;
                        G = G/totalBGR;
                        R = R/totalBGR;

                        if(B>Bazul)  //azul
                        {
                            azul++;
                        }
                        else if(R>Rvermelho)  //vermelho
                        {
                            if(G>Gamarelo)  //amarelo
                            {
                                amarelo++;
                            }
                            else if(G>Glaranja) //laranja REVISAR
                            {
                                laranja++;
                            }
                            else  //vermelho
                            {
                                vermelho++;
                            }
                        }
                        else if(G>Gverde) //verde
                        {
                            verde ++;
                        }
                        else
                        {
                            branco++;
                        }
                    }
                }
                totalMedia = azul + verde + laranja + amarelo + vermelho +branco;
                azul = azul/totalMedia;
                verde = verde/totalMedia;
                laranja = laranja/totalMedia;
                amarelo = amarelo/totalMedia;
                vermelho = vermelho/totalMedia;
                branco = branco/totalMedia;

                //FAZER TESTE DE PROPORÇÃO. SE TIVER MAIS DE 50% DAQUELA COR EH A COR ACEITA
                if(azul > 0.5)
                {
                    corFace = corFace + '1';
                }
                else if(verde > 0.5)
                {
                    corFace = corFace + '3';
                }
                else if(laranja > 0.5)
                {
                    corFace = corFace + '2';
                }
                else if(amarelo > 0.5)
                {
                    corFace = corFace + '4';
                }
                else if(vermelho > 0.5)
                {
                    corFace = corFace + '5';
                }
                else if(branco > 0.5)
                {
                    corFace = corFace + '0';
                }
                else
                {
                    corFace = corFace + 'E'; //ERRO, NAO DETECTOU NENHUMA DAS CORES VALIDAS
                }
                azul=0;
                verde=0;
                laranja=0;
                amarelo=0;
                vermelho=0;
                branco=0;
            }
        }
        cvShowImage("Recognizer", frame);   //Show image frames on created window
   // }
    //    while(cvWaitKey(10) != 'k') {}

    cvReleaseCapture(&capture); //Release capture.
    cvDestroyWindow("Recognizer"); //Destroy Window
    return corFace;
  }
};
