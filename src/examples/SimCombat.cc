#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "TablaTipo.cc"
#include "CajaPokemon.cc"
#include "CajaMovimientos.cc"


int atacante_id=0;
int defensor_id=0;
int movimiento_id=0;
int respuesta = 2;

const int knPokemon = 12;
const int knMove = 56;

TPokemon Atacante;
TPokemon Defensor;
TPkmnMove Movimiento;


void Mostrar_Lista_Pokemon(){
  for(int i=0;i<knPokemon;i++){
    printf("***************************************************************************\n");
    printf("* %s  Atk: %d   Def: %d   SpcAtk:%d  SpcDef:%d   PS:%d  ID:%d * \n", (caja+i)->Name,(caja+i)->Atk,(caja+i)->Def, (caja+i)->SpcAtk, (caja+i)->SpcDef, (caja+i)->PS, (caja+i)->id);
    printf("***************************************************************************\n");
    printf("\n");
  }
  printf("Elija su pokemon atacante: ");
   scanf("%d",&atacante_id);
   printf("Elija su pokemon defensor: ");
   scanf("%d",&defensor_id);
}


void Mostrar_Lista_Movimiento(){
   printf("Elija el movimiento que desea utilizar: \n");
  for(int i=0;i<knMove;i++){
    if((listamove+i)->Category == 0){
      printf("***************************************************************************\n");
      printf("* %s  Power: %d  Physical *  Accuracy: %f  id: %d \n", (listamove+i)->MoveName,(listamove+i)->Power,(listamove+i)->Acuracy,(listamove+i)->id);
      printf("***************************************************************************\n");
      printf("\n");
    
      
      
    }
    if((listamove+i)->Category == 1){
      printf("***************************************************************************\n");
      printf("* %s  Power: %d  Special *  Accuracy: %f  id: %d \n", (listamove+i)->MoveName,(listamove+i)->Power,(listamove+i)->Acuracy,(listamove+i)->id);
      printf("***************************************************************************\n");
      printf("\n");
    
     
      
    }
  }
  scanf("%d",&movimiento_id);
  printf("\n Movimiento Asignado.\n");
}

void Mostrar_Elegido_Pokemon(){

  printf("Pokemon atacante elegido : %s (%d)\n",(caja+atacante_id)->Name,atacante_id);
  printf("Pokemon defensor elegido : %s (%d)\n",(caja+defensor_id)->Name,defensor_id);

  printf("¿Te parece correcto? (0/1): ");
  scanf("%d", &respuesta);

  if(respuesta==0){

    printf("Elige de nuevo.\n");
    Mostrar_Lista_Pokemon();

  }else if(respuesta==1){

    printf("Adelante.\n");

  }
}

void Mostrar_Elegido_Move(){

  printf("Movimiento elegido : %s (%d)\n",(listamove+movimiento_id)->MoveName,movimiento_id);
  printf("¿Te parece correcto? (0/1): ");
  scanf("%d", &respuesta);
  if(respuesta==0){

    printf("Elige de nuevo.\n");
    Mostrar_Lista_Movimiento();

  }else if(respuesta==1){

    printf("Adelante.\n");

  }
}


  void Asignar_Valores(TPokemon *Atacante, TPokemon *Defensor, TPkmnMove *Movimiento){
    printf("Asignando Valores.");
     Atacante = (caja+atacante_id); //pasamos valor con el indice del atacante
     Defensor = (caja+defensor_id);
     Movimiento = (listamove+movimiento_id);

    

   Defensor->f_type1 = table.All[Movimiento->MoveType][Defensor->Type_1];
   Defensor->f_type2 = table.All[Movimiento->MoveType][Defensor->Type_2];


    
   float D = 0.0f;  // Total damage recieved by the pokemon
   float B = 1.0f;  // S.T.A.B (If the type of the attack id similar to the pokemon that used it it does more damage)
   float V = (float) (rand()%16 + 85);  // Random variable of the move power between 85 and 100 
   float P = Movimiento->Power; // Power of the move
   float CH = (float) (rand()%16 + 1); // Chance of a Critical Hit
   int A;
   A = (Movimiento->Acuracy/100) * 255;
   int R = rand()%256;
   if(R <= A){
     if(CH == 16.0f){
       CH = 2.0f;
     }else{
       CH = 1.0f;
     }
     if(Movimiento->Category = 0){
       Atacante->SpcAtk = 0;
       Defensor->SpcDef = 0;
     }else if(Movimiento->Category = 1){
       Atacante->Atk = 0;
       Defensor->Def = 0;
     }
    
     if((Movimiento->MoveType = Atacante->Type_1) || (Movimiento->MoveType = Atacante->Type_2)){
      B = 1.5f;
     }else{
      B = 1.0f;
     }
      D = (((((((Atacante->Level * 2.0f / 5.0f) + 2.0f) * Movimiento->Power * (Atacante->Atk + Atacante->SpcAtk) / 50.0f) / (Defensor->Def + Defensor->SpcDef)) + 2.0f) * CH  * V / 100.0f) * B *  Defensor->f_type1 *  Defensor->f_type2);
      printf("\nDamage Dealt: %f\n", D);
      if(CH == 2.0f){
        printf("CHITICAL HIT");
      }
        if(Defensor->f_type1 * Defensor->f_type2 == 0.0f){

          printf("El pokemon %s es inmune al movimiento %s \n", Defensor->Name, Movimiento->MoveName);

        }

        if(Defensor->f_type1 * Defensor->f_type2 == 0.5f){

          printf("El pokemon %s es resistente al movimiento %s \n", Defensor->Name, Movimiento->MoveName);

        }

        if(Defensor->f_type1 * Defensor->f_type2 == 0.25f){

           printf("El pokemon %s es muy resistente al movimiento %s \n", Defensor->Name, Movimiento->MoveName);

        }

        if(Defensor->f_type1 * Defensor->f_type2 == 1.0f){

          printf("El pokemon %s es neutral ante el movimiento %s \n", Defensor->Name, Movimiento->MoveName);

        }

        if(Defensor->f_type1 * Defensor->f_type2 == 2.0f){

          printf("El pokemon %s es debil al movimiento %s \n", Defensor->Name, Movimiento->MoveName);

        }

        if(Defensor->f_type1 * Defensor->f_type2 == 4.0f){

          printf("El pokemon %s es muy debil al movimiento %s \n", Defensor->Name, Movimiento->MoveName);

        }

      printf("\n PS Restantes: %f\n", (Defensor->PS - D));
      printf(" tipe_1: %f\n", Defensor->f_type1);
      printf(" tipe_2: %f\n", Defensor->f_type2);

  }else{
    
    printf("\nEl movimiento ha fallado.\n");

  }

  }



 //void CombatEquation(TPokemon *Atacante, TPokemon *Defensor, TPkmnMove *Movimiento){
//
//
//
//
//
 //  //}
 //}

//     switch (Defensor.Type1 * Defensor.Type2){
//       case 0.0f:
//         printf("El pokemon %c es inmune al movimientos %c \n", &Defensor.Name, &Movimiento.MoveName);
//       break;
//       case 0.5f:
//         printf("El pokemon %c es resistente al movimientos %c \n", &Defensor.Name, &Movimiento.MoveName);
//       break;
//       case 0.25f:
//         printf("El pokemon %c es muy resistente al movimientos %c \n", &Defensor.Name, &Movimiento.MoveName);
//       break;
//       case 1.0f:
//         printf("El pokemon %c neutral ante el movimientos %c \n", &Defensor.Name, &Movimiento.MoveName);
//       break;
//       case 2.0f:
//         printf("El pokemon %c debil al movimientos %c \n", &Defensor.Name, &Movimiento.MoveName);
//       break;
//       case 4.0f:
//         printf("El pokemon %c muy debil al movimientos %c \n", &Defensor.Name, &Movimiento.MoveName);
//       break;
//     }
//     printf("PS Restantes: %f\n", (D - poke2->PS));
//   }else(printf("The move failed"));
// }
 




int main(){
  srand (time(NULL));
  caja = (TPokemon*) malloc(knPokemon * sizeof(TPokemon));
  listamove = (TPkmnMove*)malloc(56*sizeof(TPkmnMove));
  Llenar_caja();
  Llenar_movimientos();
  Mostrar_Lista_Pokemon();
  Mostrar_Elegido_Pokemon();
  Mostrar_Lista_Movimiento();
  Mostrar_Elegido_Move();

  Asignar_Valores(&Atacante,&Defensor, &Movimiento);


  

  
 //printf("\n%f\n",Defensor.f_type1);
 //printf("\n%f\n",Defensor.f_type2);

  //CombatEquation(&Atacante,&Defensor,&Movimiento);

  free(caja);
  free(listamove);
}
