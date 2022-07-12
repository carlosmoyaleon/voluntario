#include <iostream>
#include <cmath>
#include <fstream>



using namespace std;





double CalculoMagnetizacion (int s[][128], int N);
double CalculoEnergia (int s[][128], int N);


 


   
    


int main (){

    int N=128, n, m, i, j, k, contmonte, cont, indice, limite ;
    double T,p,e,fi, num,a, magn, em, c, mag, energia1, energia2, auxenergia, promedio[N][N], f, sumae;
    ofstream energia, magnetizacion, calor, correlacion;

    


    int s[128][128];

    //Inicializamos valores:

    T=1.5;

     energia.open("energia.dat");
    magnetizacion.open("magnetizacion.dat");
    calor.open("calor.dat");
    correlacion.open("correlacion.dat");

//INTRODUCIMOS UN CICLO DO WHILE PARA REALIZAR CÁLCULOS DE LAS TEMPERATURAS
    
    do
    {
       
    contmonte=-1;

    magn=0;
    em=0;
    c=0;
    energia1=0;
    energia2=0;
    auxenergia=0;
    cont=0;
    f=0;
    indice=1;


    for (i = 0; i <N; i++)
    {
        for (j = 0; j < N; j++)
        {
            promedio[i][j]=0;
        }
        
    }
    




    for ( i = 0; i < N; i++)
    {
        for ( j = 0; j < N; j++)

        
        {
           s[i][j]=1;
        }
        
    }

    for ( i=0; i<1000000; i++)
    {

        for ( k = 0; k< N*N; k++)
        {
            
        
        
        // Elegimos punto al azar

      
      n=rand()%(N);
      m=rand()%(N);

      //condiciones de contorno

      if (n==0)
      {
         if (m==0)
         {
            e=2*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][m+1]+s[n][N-1]);
         }
         else if (m==N-1)
         {
            e=2*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][0]+s[n][m-1]);
         }
         else
         {
             e=2*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][m+1]+s[n][m-1]);

         }



      }
      else if (n==N-1)
      {
          if (m==0)
          {
              e=2*s[n][m]*(s[0][m]+s[n-1][m]+s[n][m+1]+s[n][N-1]);
          }
          else if (m==N-1)
         {
            e=2*s[n][m]*(s[0][m]+s[n-1][m]+s[n][0]+s[n][m-1]);
         }

          else
         {
             e=2*s[n][m]*(s[0][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);

         }
          
          
      }

      else {

          if (m==0)
          {
              e=2*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][N-1]);
          }
          else if (m==N-1)
         {
            e=2*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][0]+s[n][m-1]);
         }
         else{

          e=2*(s[n][m])*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);
         }

      }
      
         
         
     
      


     
      
      
        
        

       
        

        

        p=exp(-e/T);
        //Evaluamos p
        if (p>1)
        {
            p=1.0;
        }

         fi=rand()/(RAND_MAX*1.0);

        if (fi<p)
        {
            s[n][m]=-s[n][m];
        }

        }


        contmonte=contmonte+1;

        //VOLUNTARIO


        if (contmonte==100)
        {


            //CALCULAMOS MAGNETIZACION
         mag=CalculoMagnetizacion(s,N);

        magn=magn+mag;

        //CALCULAMOS ENERGÍA


        auxenergia=CalculoEnergia(s,N);

        energia1=energia1+auxenergia;

        energia2= energia2+(pow(auxenergia,2));


        //CALCULAMOS LA FUNCION DE CORRELACION

        for (j = 0; j < N; j++)
        {
            limite=0;

            for (k = 0; k < N; k++)
            {
                if ((j+indice)>N)
                {
                    promedio[j][k]=promedio[j][k]+s[j][k]*s[limite][k];

                    limite=limite+1;
                }

                else{

                    promedio[j][k]=promedio[j][k]+s[j][k]*s[j+indice][k];
                }
                
            }
            
        }

        contmonte=-1;
        cont=cont+1;

        }
    }

    
        
        

     //HACEMOS EL PROMEDIO DIVIDIENDO POR EL CONTADOR DE PASOS


     magn=magn/cont;

     energia1=energia1/cont;

     energia2=energia2/cont;

     em=energia1/(2*N*N);

     c= (energia2-pow(energia1,2))/(pow(N,2)*T);

 
        

     for (j = 0; j < N; j++)
     {
        for (k = 0; k < N; k++)
        {
            f=f+promedio[j][k];
        }
        
     }
     

     f=f/(cont*N*N);

     
//ESCRIBIMOS EN EL FICHERO


      energia << em << " " << T <<endl;

    magnetizacion << magn << " " << T << endl;

    calor << c <<" " << T << endl;

    correlacion << f << " " << T << endl;


    

  


    T=T+0.2;





 } while (T<3.5);


   energia.close();

    magnetizacion.close();

    calor.close();

    correlacion.close();

     

return 0;


}


double CalculoEnergia (int s[][128], int N){


    double sumae=0;
    int i,j;

     for ( i = 1; i < N-1; i++)
    {
        for ( j = 1; j < N-1; j++)
        {
            sumae=sumae+s[i][j]*(s[i][j+1]+s[i][j-1]+s[i+1][j]+s[i-1][j]);
        }

    }

   
    sumae=sumae+s[0][0]*(s[0][1]+s[0][N-1]+s[1][0]+s[N-1][0]);
  

    sumae=sumae+s[0][N-1]*(s[0][0]+s[0][N-2]+s[1][N-1]+s[N-1][N-1]);
   

    for ( j = 1; j < N-1; j++)
    {
        sumae=sumae+s[0][j]*(s[0][j+1]+s[0][j-1]+s[1][j]+s[N-1][j]);
    }

  
    sumae=sumae+s[N-1][0]*(s[N-1][1]+s[N-1][N-1]+s[0][0]+s[N-2][0]);


    sumae=sumae+s[N-1][N-1]*(s[N-1][0]+s[N-1][N-2]+s[0][N-1]+s[N-2][N-1]);
    


    for ( j = 1; j < N-1; j++)
    {
        sumae=sumae+s[N-1][j]*(s[N-1][j+1]+s[N-1][j-1]+s[0][j]+s[N-2][j]);
    }

    

    for ( i = 1; i < N-1; i++)
    {
        sumae=sumae+s[i][0]*(s[i][1]+s[i][N-1]+s[i+1][0]+s[i-1][0]);
    }
    

    for ( i = 1; i < N-1; i++)
    {
        sumae=sumae+s[i][N-1]*(s[i][0]+s[i][N-2]+s[i+1][N-1]+s[i-1][N-1]);
    }




    sumae=-(0.5)*sumae;



    return sumae;
}





double CalculoMagnetizacion (int s[][128], int N){



    double mag;

    int i,j;

    mag=0;

    for ( i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            mag=mag+s[i][j];
        }
        
    }

    mag=abs(mag);

    mag=mag/(N*N);

    return mag;
    
}














        /*
      
      if (i%(N*N)==0){
           for ( k=0; k <N; k++)
        {
            for ( j=0; j < N-1; j++)
            {
                fich << s[k][j] << ", ";
            }

            fich << s[k][N-1];
            fich << "\n";
            
        }
        fich << "\n";
      }
        
    }

    fich.close();

    */




    

    

