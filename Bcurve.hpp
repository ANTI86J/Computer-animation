#ifndef _SPLINE_H
#define _SPLINE_H
#define DIV_FACTOR 0.10 //adjust this factor to adjust the curve smoothness
#include <math.h>
#include <GL/glut.h>
#include <vector>
#include <list>
#include <math.h>
#include <stdlib.h>
#include "glm/glm.hpp"
using namespace glm;
 	// vector
		 



			class Curve
			{
			public:
				std::vector<vec3> Verts;
				vec3 A;
				vec3 B;
				vec3 C;
			 
				int    Ndiv;

				Curve(vec3 a,vec3 b,vec3 c,int ndiv) 
				{
					A = a;
					B = b;
					C = c;
					Ndiv = ndiv;
				}

				float max3i(float a,float b,float c)
				{
					float temp = a;
					if(b>temp)
						temp = b;
					if(c>temp)
						temp = c;

					return temp;
				}
				Curve(vec3 a, vec3 b, vec3 c )
				{
					A = a;
					B = b;
					C = c;
					Ndiv = (int)(max3i(fabs(A.x), fabs(A.y), fabs(A.z)) / DIV_FACTOR);
				}
		 
				Curve() 
				{	
				};

				void PutCurve(vec3 a, vec3 b, vec3 c)
				{
					A = a;
					B = b;
					C = c;
					Ndiv = (int)(max3i(fabs(A.x),fabs(A.y),fabs(A.z))/DIV_FACTOR);
				}

				void draw(vec3 p) 
				{
				 
					vec3 Orig, New;
					float  t,f,g,h;
					if (Ndiv==0)
						Ndiv=1;

					Orig  = p ;
					 

				//	 glBegin(GL_LINES);
			
			
					for(int i=1; i<=Ndiv ; i++)  
					{
						t = 1.0f / (float)Ndiv * (float)i;
						f = t*t*(3.0f-2.0f*t);
						g = t*(t-1.0f)*(t-1.0f);
						h = t*t*(t-1.0f);
						New = (p + A*f + B*g + C*h);
				 
					 	Verts.push_back(New);
					//	 glVertex3f(Orig.x,Orig.y,Orig.z);
					//	 glVertex3f(New.x,New.y,New.z);
						Orig=New;
					 
					}
				//	 glEnd();
				}
				 
		 
			};

	 
			class Bcurve
			{

			public:
				Curve curve;
				vec3* P;
				vec3* A;
				vec3* B;
				vec3* C;
 
				float* k;
				float* Mat[3];
				 
				int  NP;
				Bcurve()
				{}
				// constructor
				void init(std::vector<vec3> pt)
				{
					NP = pt.size();
					P  = new vec3[NP];
				 
					A  = new vec3[NP];
			 
					B  = new vec3[NP];
				 
					C  = new vec3[NP];
				 
					k = new float[NP];
					Mat[0] = new float[NP];
					Mat[1] = new float[NP];
					Mat[2] = new float[NP];

					for (int i = 0; i < NP; i++)
					{
						P[i] = pt[i];
				 
					}

					Generate();
				}


				~Bcurve()
				{
					delete[] P;
					 
					delete[] A;
					 
					delete[] B;
				 
					delete[] C;
					delete[] k;
					delete[] Mat[0];
					delete[] Mat[1];
					delete[] Mat[2];
				}

				void Generate()
				{
					float AMag, AMagOld;
					// vector A
					for (int i = 0; i <= NP - 2; i++)
					{

						A[i]  = P[i + 1]  - P[i] ;
						 
					}						   
					// k
					AMagOld = (float)sqrt(A[0].x * A[0].x + A[0].y * A[0].y + A[0].z * A[0].z);
					for (int i = 0; i <= NP - 3; i++)
					{
						AMag = (float)sqrt(A[i + 1].x * A[i + 1].x + A[i + 1].y * A[i + 1].y + A[i + 1].z * A[i + 1].z);
						k[i] = AMagOld / AMag;
						AMagOld = AMag;
					}
					k[NP - 2] = 1.0f;

					// Matrix
					for (int i = 1; i <= NP - 2; i++)
					{
						Mat[0][i] = 1.0f;
						Mat[1][i] = 2.0f * k[i - 1] * (1.0f + k[i - 1]);
						Mat[2][i] = k[i - 1] * k[i - 1] * k[i];
					}
					Mat[1][0] = 2.0f;
					Mat[2][0] = k[0];
					Mat[0][NP - 1] = 1.0f;
					Mat[1][NP - 1] = 2.0f * k[NP - 2];

					// 
					for (int i = 1; i <= NP - 2; i++)
					{

						B [i] = 3.0f * (A [i - 1] + k[i - 1] * k[i - 1] * A [i]);
						 
					}
					B [0] = 3.0f * A [0];
				 
					B [NP - 1] = 3.0f * A [NP - 2];
				 
 
					MatrixSolve(B);
				 
					 

					for (int i = 0; i <= NP - 2; i++)
					{
						C[i]  = k[i] * B [i + 1];
					 
					}
				}

				void MatrixSolve(vec3 B[])
				{
					vec3* Work = new vec3[NP];
					vec3* WorkB = new vec3[NP];
					for (int i = 0; i <= NP - 1; i++)
					{
						Work[i] = B[i] / Mat[1][i];
						WorkB[i] = Work[i];
					}

					for (int j = 0; j < 10; j++)
					{ ///  need convergence judge
						Work[0] = (B[0] - Mat[2][0] * WorkB[1]) / Mat[1][0];
						for (int i = 1; i < NP - 1; i++)
						{
							Work[i] = (B[i] - Mat[0][i] * WorkB[i - 1] - Mat[2][i] * WorkB[i + 1])
								/ Mat[1][i];
						}
						Work[NP - 1] = (B[NP - 1] - Mat[0][NP - 1] * WorkB[NP - 2]) / Mat[1][NP - 1];

						for (int i = 0; i <= NP - 1; i++)
						{
							WorkB[i] = Work[i];
						}
					}
					for (int i = 0; i <= NP - 1; i++)
					{
						B[i] = Work[i];
					}
					delete[] Work;
					delete[] WorkB;
				}

				void draw()
				{
					
					for (int i = 0; i < NP; i++)
					{
						curve.PutCurve(A[i],B[i],C[i]);
						curve.draw(P[i]);
					}

				}
			};
			 
			#endif
