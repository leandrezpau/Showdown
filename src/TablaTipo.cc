


// void TablaTipos(TPokemon *poke, TPkmnMove *move){

//   for(int j = 0; j < 18; ++j ){
//     if(j == poke->Type1){
//         return j;
//     }
//   }

//   for(int i = 0; Defensor.Type1[i] < Defensor.Type1[18]; ++i ){
//     if(Defensor.Type1[i] == Defensor.Type1[poke->[]])
//   }

struct TTabla{
  float All[19][19]= { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                       1.0f, 0.5f, 0.5f, 1.0f, 2.0f, 2.0f, 0.5f, 0.5f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 1.0f,
                       1.0f, 2.0f, 0.5f, 1.0f, 0.5f, 1.0f, 2.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 1.0f,
                       1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 1.0f,
                       1.0f, 0.5f, 2.0f, 1.0f, 0.5f, 0.5f, 2.0f, 2.0f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 0.5f, 0.5f, 1.0f,
                       1.0f, 0.5f, 0.5f, 1.0f, 2.0f, 0.5f, 2.0f, 0.5f, 2.0f, 2.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 2.0f, 1.0f,
                       1.0f, 2.0f, 1.0f, 2.0f, 0.5f, 0.5f, 0.5f, 2.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 2.0f, 1.0f, 1.0f,
                       1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 0.5f, 2.0f, 2.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 1.0f,
                       1.0f, 0.5f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, 1.0f, 2.0f, 2.0f, 1.0f, 0.5f, 1.0f, 0.5f, 1.0f, 0.5f,
                       1.0f, 1.0f, 1.0f, 0.5f, 2.0f, 0.5f, 1.0f, 0.5f, 2.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 1.0f,
                       1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 0.5f, 2.0f, 0.5f, 0.5f, 1.0f, 2.0f, 0.5f, 2.0f, 0.5f, 0.0f, 2.0f, 1.0f, 0.5f,
                       1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.5f, 1.0f, 1.0f,
                       1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 2.0f, 1.0f, 0.5f, 0.0f, 2.0f, 0.5f, 0.5f, 1.0f, 1.0f,
                       1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 0.5f, 1.0f, 2.0f, 0.5f, 1.0f, 2.0f, 0.5f, 1.0f, 0.5f,
                       1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.0f, 1.0f, 2.0f,
                       1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 2.0f, 0.5f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f,
                       1.0f, 0.5f, 0.5f, 0.5f, 1.0f, 2.0f, 0.5f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 2.0f,
                       1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 2.0f, 0.0f,
                       1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 2.0f, 0.5f, 1.0f, 0.5f, 2.0f, 1.0f};

};



TTabla table;


 
  

//   //FUEGO//
//   if(move->MoveType = 1 && poke->Type_1 = 1){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 1 && poke->Type_1 = 2){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 1 && poke->Type_1 = 3){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_1 = 4){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_1 = 5){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_1 = 6){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 1 && poke->Type_1 = 7){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 1 && poke->Type_1 = 8){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_1 = 9){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_1 = 10){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_1 = 11){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_1 = 12){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_1 = 13){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_1 = 14){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_1 = 15){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_1 = 16){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_1 = 17){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 1 && poke->Type_1 = 18){
//     poke->Type_1 = float(1.0f);
//   }



//   //AGUA//
//   if(move->MoveType = 2 && poke->Type_1 = 1){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 2 && poke->Type_1 = 2){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 2 && poke->Type_1 = 3){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 2 && poke->Type_1 = 4){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 2 && poke->Type_1 = 5){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 2 && poke->Type_1 = 6){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 2 && poke->Type_1 = 7){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 2 && poke->Type_1 = 8){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 2 && poke->Type_1 = 9){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 2 && pokee->Type_1 = 10){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 2 && pokee->Type_1 = 11){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 2 && pokee->Type_1 = 12){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 2 && pokee->Type_1 = 13){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 2 && pokee->Type_1 = 14){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 2 && pokee->Type_1 = 15){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 2 && pokee->Type_1 = 16){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 2 && pokee->Type_1 = 17){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 2 && pokee->Type_1 = 18){
//     poke->Type_1 = float(1.0f);
//   }


//   //ELECTRICO//
//   if(move->MoveType = 3 && poke->Type_1 = 1){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 3 && poke->Type_1 = 2){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 3 && poke->Type_1 = 3){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 3 && poke->Type_1 = 4){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 3 && poke->Type_1 = 5){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 3 && poke->Type_1 = 6){
//     poke->Type_1 = float(0.0f);
//   }
//   if(move->MoveType = 3 && poke->Type_1 = 7){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 3 && poke->Type_1 = 8){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 3 && poke->Type_1 = 9){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 3 && pokee->Type_1 = 10){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 3 && pokee->Type_1 = 11){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 3 && pokee->Type_1 = 12){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 3 && pokee->Type_1 = 13){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 3 && pokee->Type_1 = 14){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 3 && pokee->Type_1 = 15){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 3 && pokee->Type_1 = 16){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 3 && pokee->Type_1 = 17){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 3 && pokee->Type_1 = 18){
//     poke->Type_1 = float(1.0f);
//   }


//   //PLANTA//
//   if(move->MoveType = 4 && poke->Type_1 = 1){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 4 && poke->Type_1 = 2){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 4 && poke->Type_1 = 3){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 4 && poke->Type_1 = 4){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 4 && poke->Type_1 = 5){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 4 && poke->Type_1 = 6){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 4 && poke->Type_1 = 7){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 4 && poke->Type_1 = 8){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 4 && poke->Type_1 = 9){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 4 && pokee->Type_1 = 10){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 4 && pokee->Type_1 = 11){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 4 && pokee->Type_1 = 12){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 4 && pokee->Type_1 = 13){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 4 && pokee->Type_1 = 14){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 4 && pokee->Type_1 = 15){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 4 && pokee->Type_1 = 16){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 4 && pokee->Type_1 = 17){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 4 && pokee->Type_1 = 18){
//     poke->Type_1 = float(1.0f);
//   }


//   //HIELO//
//   if(move->MoveType = 5 && poke->Type_1 = 1){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 5 && poke->Type_1 = 2){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 5 && poke->Type_1 = 3){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 5 && poke->Type_1 = 4){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 5 && poke->Type_1 = 5){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 5 && poke->Type_1 = 6){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 5 && poke->Type_1 = 7){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 5 && poke->Type_1 = 8){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 5 && poke->Type_1 = 9){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 5 && pokee->Type_1 = 10){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 5 && pokee->Type_1 = 11){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 5 && pokee->Type_1 = 12){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 5 && pokee->Type_1 = 13){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 5 && pokee->Type_1 = 14){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 5 && pokee->Type_1 = 15){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 5 && pokee->Type_1 = 16){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 5 && pokee->Type_1 = 17){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 5 && pokee->Type_1 = 18){
//     poke->Type_1 = float(1.0f);
//   }


//   //TIERRA//
//   if(move->MoveType = 6 && poke->Type_1 = 1){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 6 && poke->Type_1 = 2){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 6 && poke->Type_1 = 3){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 6 && poke->Type_1 = 4){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 6 && poke->Type_1 = 5){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 6 && poke->Type_1 = 6){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 6 && poke->Type_1 = 7){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 6 && poke->Type_1 = 8){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 6 && poke->Type_1 = 9){
//     poke->Type_1 = float(0.0f);
//   }
//   if(move->MoveType = 6 && pokee->Type_1 = 10){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 6 && pokee->Type_1 = 11){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 6 && pokee->Type_1 = 12){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 6 && pokee->Type_1 = 13){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 6 && pokee->Type_1 = 14){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 6 && pokee->Type_1 = 15){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 6 && pokee->Type_1 = 16){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 6 && pokee->Type_1 = 17){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 6 && pokee->Type_1 = 18){
//     poke->Type_1 = float(1.0f);
//   }


//   //ROCA//
//   if(move->MoveType = 7 && poke->Type_1 = 1){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 7 && poke->Type_1 = 2){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 7 && poke->Type_1 = 3){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 7 && poke->Type_1 = 4){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 7 && poke->Type_1 = 5){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 7 && poke->Type_1 = 6){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 7 && poke->Type_1 = 7){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 7 && poke->Type_1 = 8){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 7 && poke->Type_1 = 9){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 7 && pokee->Type_1 = 10){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 7 && pokee->Type_1 = 11){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 7 && pokee->Type_1 = 12){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 7 && pokee->Type_1 = 13){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 7 && pokee->Type_1 = 14){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 7 && pokee->Type_1 = 15){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 7 && pokee->Type_1 = 16){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 7 && pokee->Type_1 = 17){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 7 && pokee->Type_1 = 18){
//     poke->Type_1 = float(1.0f);
//   }


//   //BICHO//
//   if(move->MoveType = 8 && poke->Type_1 = 1){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 8 && poke->Type_1 = 2){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 8 && poke->Type_1 = 3){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 8 && poke->Type_1 = 4){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 8 && poke->Type_1 = 5){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 8 && poke->Type_1 = 6){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 8 && poke->Type_1 = 7){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 8 && poke->Type_1 = 8){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 8 && poke->Type_1 = 9){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 8 && pokee->Type_1 = 10){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 8 && pokee->Type_1 = 11){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 8 && pokee->Type_1 = 12){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 8 && pokee->Type_1 = 13){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 8 && pokee->Type_1 = 14){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 8 && pokee->Type_1 = 15){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 8 && pokee->Type_1 = 16){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 8 && pokee->Type_1 = 17){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 8 && pokee->Type_1 = 18){
//     poke->Type_1 = float(0.5f);
//   }


//   //VOLADOR//
//   if(move->MoveType = 9 && poke->Type_1 = 1){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 9 && poke->Type_1 = 2){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 9 && poke->Type_1 = 3){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 9 && poke->Type_1 = 4){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 9 && poke->Type_1 = 5){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 9 && poke->Type_1 = 6){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 9 && poke->Type_1 = 7){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 9 && poke->Type_1 = 8){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 9 && poke->Type_1 = 9){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 9 && pokee->Type_1 = 10){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 9 && pokee->Type_1 = 11){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 9 && pokee->Type_1 = 12){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 9 && pokee->Type_1 = 13){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 9 && pokee->Type_1 = 14){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 9 && pokee->Type_1 = 15){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 9 && pokee->Type_1 = 16){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 9 && pokee->Type_1 = 17){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 9 && pokee->Type_1 = 18){
//     poke->Type_1 = float(1.0f);
//   }


//   //LUCHA//
//   if(move->MoveType = 10 && poke->Type_1 = 1){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_1 = 2){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_1 = 3){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_1 = 4){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_1 = 5){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_1 = 6){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_1 = 7){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_1 = 8){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 10 && poke->Type_1 = 9){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 10 && poke->Type_1 = 10){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_1 = 11){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_1 = 12){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 10 && poke->Type_1 = 13){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_1 = 14){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 10 && poke->Type_1 = 15){
//     poke->Type_1 = float(0.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_1 = 16){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_1 = 17){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 10 && poke->Type_1 = 18){
//     poke->Type_1 = float(0.5f);
//   }


//     //NORMAL//
//   if(move->MoveType = 11 && poke->Type_1 = 1){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_1 = 2){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_1 = 3){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_1 = 4){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_1 = 5){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_1 = 6){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_1 = 7){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 11 && poke->Type_1 = 8){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_1 = 9){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_1 = 10){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_1 = 11){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_1 = 12){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_1 = 13){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_1 = 14){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_1 = 15){
//     poke->Type_1 = float(0.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_1 = 16){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 11 && poke->Type_1 = 17){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_1 = 18){
//     poke->Type_1 = float(1.0f);
//   }

//   //PSIQUICO//
//   if(move->MoveType = 12 && poke->Type_1 = 1){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_1 = 2){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_1 = 3){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_1 = 4){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_1 = 5){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_1 = 6){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_1 = 7){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_1 = 8){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 12 && poke->Type_1 = 9){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_1 = 10){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_1 = 11){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_1 = 12){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 12 && poke->Type_1 = 13){
//     poke->Type_1 = float(0.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_1 = 14){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_1 = 15){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 12 && poke->Type_1 = 16){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 12 && poke->Type_1 = 17){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_1 = 18){
//     poke->Type_1 = float(1.0f);
//   }

//   //SINIESTRO//
//   if(move->MoveType = 13 && poke->Type_1 = 1){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_1 = 2){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_1 = 3){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_1 = 4){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_1 = 5){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_1 = 6){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_1 = 7){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_1 = 8){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 13 && poke->Type_1 = 9){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_1 = 10){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 13 && poke->Type_1 = 11){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_1 = 12){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_1 = 13){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 13 && poke->Type_1 = 14){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_1 = 15){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_1 = 16){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 13 && poke->Type_1 = 17){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_1 = 18){
//     poke->Type_1 = float(0.5f);
//   }

//   //VENENO//
//   if(move->MoveType = 14 && poke->Type_1 = 1){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_1 = 2){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_1 = 3){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_1 = 4){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_1 = 5){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_1 = 6){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 14 && poke->Type_1 = 7){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 14 && poke->Type_1 = 8){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_1 = 9){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_1 = 10){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_1 = 11){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_1 = 12){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_1 = 13){
//     poke->Type_1 = float(1.f);
//   }
//   if(move->MoveType = 14 && poke->Type_1 = 14){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_1 = 15){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 14 && poke->Type_1 = 16){
//     poke->Type_1 = float(0.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_1 = 17){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_1 = 18){
//     poke->Type_1 = float(2.0f);
//   }

//   //FANTASMA//
//   if(move->MoveType = 15 && poke->Type_1 = 1){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_1 = 2){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_1 = 3){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_1 = 4){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_1 = 5){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_1 = 6){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_1 = 7){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_1 = 8){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_1 = 9){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_1 = 10){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_1 = 11){
//     poke->Type_1 = float(0.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_1 = 12){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_1 = 13){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 15 && poke->Type_1 = 14){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_1 = 15){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_1 = 16){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_1 = 17){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_1 = 18){
//     poke->Type_1 = float(1.0f);
//   }

//   //ACERO//
//   if(move->MoveType = 16 && poke->Type_1 = 1){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 16 && poke->Type_1 = 2){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 16 && poke->Type_1 = 3){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 16 && poke->Type_1 = 4){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_1 = 5){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_1 = 6){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 16 && poke->Type_1 = 7){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_1 = 8){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_1 = 9){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_1 = 10){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_1 = 11){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_1 = 12){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 16 && poke->Type_1 = 13){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_1 = 14){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_1 = 15){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_1 = 16){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_1 = 17){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_1 = 18){
//     poke->Type_1 = float(2.0f);
//   }

//   //DRAGON//
//   if(move->MoveType = 17 && poke->Type_1 = 1){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_1 = 2){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_1 = 3){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_1 = 4){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_1 = 5){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_1 = 6){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_1 = 7){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_1 = 8){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_1 = 9){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_1 = 10){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_1 = 11){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_1 = 12){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_1 = 13){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_1 = 14){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_1 = 15){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_1 = 16){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 17 && poke->Type_1 = 17){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_1 = 18){
//     poke->Type_1 = float(0.0f);
//   }

//   //HADA//
//   if(move->MoveType = 18 && poke->Type_1 = 1){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 18 && poke->Type_1 = 2){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_1 = 3){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_1 = 4){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_1 = 5){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_1 = 6){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_1 = 7){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_1 = 8){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_1 = 9){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_1 = 10){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_1 = 11){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_1 = 12){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_1 = 13){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_1 = 14){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 18 && poke->Type_1 = 15){
//     poke->Type_1 = float(1.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_1 = 16){
//     poke->Type_1 = float(0.5f);
//   }
//   if(move->MoveType = 18 && poke->Type_1 = 17){
//     poke->Type_1 = float(2.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_1 = 18){
//     poke->Type_1 = float(1.0f);
//   }



  
// /////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////



//   //FUEGO//
//   if(move->MoveType = 1 && poke->Type_2 = 1){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 1 && poke->Type_2 = 2){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 1 && poke->Type_2 = 3){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_2 = 4){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_2 = 5){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_2 = 6){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 1 && poke->Type_2 = 7){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 1 && poke->Type_2 = 8){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_2 = 9){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_2 = 10){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_2 = 11){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_2 = 12){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_2 = 13){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_2 = 14){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_2 = 15){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_2 = 16){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 1 && poke->Type_2 = 17){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 1 && poke->Type_2 = 18){
//     poke->Type_2 = float(1.0f);
//   }



//   //AGUA//
//   if(move->MoveType = 2 && poke->Type_2 = 1){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 2 && poke->Type_2 = 2){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 2 && poke->Type_2 = 3){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 2 && poke->Type_2 = 4){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 2 && poke->Type_2 = 5){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 2 && poke->Type_2 = 6){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 2 && poke->Type_2 = 7){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 2 && poke->Type_2 = 8){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 2 && poke->Type_2 = 9){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 2 && pokee->Type_2 = 10){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 2 && pokee->Type_2 = 11){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 2 && pokee->Type_2 = 12){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 2 && pokee->Type_2 = 13){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 2 && pokee->Type_2 = 14){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 2 && pokee->Type_2 = 15){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 2 && pokee->Type_2 = 16){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 2 && pokee->Type_2 = 17){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 2 && pokee->Type_2 = 18){
//     poke->Type_2 = float(1.0f);
//   }


//   //ELECTRICO//
//   if(move->MoveType = 3 && poke->Type_2 = 1){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 3 && poke->Type_2 = 2){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 3 && poke->Type_2 = 3){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 3 && poke->Type_2 = 4){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 3 && poke->Type_2 = 5){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 3 && poke->Type_2 = 6){
//     poke->Type_2 = float(0.0f);
//   }
//   if(move->MoveType = 3 && poke->Type_2 = 7){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 3 && poke->Type_2 = 8){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 3 && poke->Type_2 = 9){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 3 && pokee->Type_2 = 10){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 3 && pokee->Type_2 = 11){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 3 && pokee->Type_2 = 12){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 3 && pokee->Type_2 = 13){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 3 && pokee->Type_2 = 14){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 3 && pokee->Type_2 = 15){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 3 && pokee->Type_2 = 16){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 3 && pokee->Type_2 = 17){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 3 && pokee->Type_2 = 18){
//     poke->Type_2 = float(1.0f);
//   }


//   //PLANTA//
//   if(move->MoveType = 4 && poke->Type_2 = 1){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 4 && poke->Type_2 = 2){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 4 && poke->Type_2 = 3){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 4 && poke->Type_2 = 4){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 4 && poke->Type_2 = 5){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 4 && poke->Type_2 = 6){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 4 && poke->Type_2 = 7){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 4 && poke->Type_2 = 8){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 4 && poke->Type_2 = 9){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 4 && pokee->Type_2 = 10){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 4 && pokee->Type_2 = 11){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 4 && pokee->Type_2 = 12){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 4 && pokee->Type_2 = 13){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 4 && pokee->Type_2 = 14){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 4 && pokee->Type_2 = 15){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 4 && pokee->Type_2 = 16){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 4 && pokee->Type_2 = 17){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 4 && pokee->Type_2 = 18){
//     poke->Type_2 = float(1.0f);
//   }


//   //HIELO//
//   if(move->MoveType = 5 && poke->Type_2 = 1){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 5 && poke->Type_2 = 2){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 5 && poke->Type_2 = 3){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 5 && poke->Type_2 = 4){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 5 && poke->Type_2 = 5){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 5 && poke->Type_2 = 6){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 5 && poke->Type_2 = 7){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 5 && poke->Type_2 = 8){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 5 && poke->Type_2 = 9){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 5 && pokee->Type_2 = 10){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 5 && pokee->Type_2 = 11){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 5 && pokee->Type_2 = 12){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 5 && pokee->Type_2 = 13){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 5 && pokee->Type_2 = 14){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 5 && pokee->Type_2 = 15){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 5 && pokee->Type_2 = 16){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 5 && pokee->Type_2 = 17){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 5 && pokee->Type_2 = 18){
//     poke->Type_2 = float(1.0f);
//   }


//   //TIERRA//
//   if(move->MoveType = 6 && poke->Type_2 = 1){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 6 && poke->Type_2 = 2){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 6 && poke->Type_2 = 3){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 6 && poke->Type_2 = 4){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 6 && poke->Type_2 = 5){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 6 && poke->Type_2 = 6){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 6 && poke->Type_2 = 7){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 6 && poke->Type_2 = 8){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 6 && poke->Type_2 = 9){
//     poke->Type_2 = float(0.0f);
//   }
//   if(move->MoveType = 6 && pokee->Type_2 = 10){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 6 && pokee->Type_2 = 11){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 6 && pokee->Type_2 = 12){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 6 && pokee->Type_2 = 13){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 6 && pokee->Type_2 = 14){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 6 && pokee->Type_2 = 15){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 6 && pokee->Type_2 = 16){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 6 && pokee->Type_2 = 17){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 6 && pokee->Type_2 = 18){
//     poke->Type_2 = float(1.0f);
//   }


//   //ROCA//
//   if(move->MoveType = 7 && poke->Type_2 = 1){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 7 && poke->Type_2 = 2){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 7 && poke->Type_2 = 3){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 7 && poke->Type_2 = 4){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 7 && poke->Type_2 = 5){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 7 && poke->Type_2 = 6){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 7 && poke->Type_2 = 7){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 7 && poke->Type_2 = 8){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 7 && poke->Type_2 = 9){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 7 && pokee->Type_2 = 10){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 7 && pokee->Type_2 = 11){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 7 && pokee->Type_2 = 12){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 7 && pokee->Type_2 = 13){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 7 && pokee->Type_2 = 14){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 7 && pokee->Type_2 = 15){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 7 && pokee->Type_2 = 16){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 7 && pokee->Type_2 = 17){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 7 && pokee->Type_2 = 18){
//     poke->Type_2 = float(1.0f);
//   }


//   //BICHO//
//   if(move->MoveType = 8 && poke->Type_2 = 1){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 8 && poke->Type_2 = 2){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 8 && poke->Type_2 = 3){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 8 && poke->Type_2 = 4){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 8 && poke->Type_2 = 5){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 8 && poke->Type_2 = 6){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 8 && poke->Type_2 = 7){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 8 && poke->Type_2 = 8){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 8 && poke->Type_2 = 9){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 8 && pokee->Type_2 = 10){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 8 && pokee->Type_2 = 11){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 8 && pokee->Type_2 = 12){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 8 && pokee->Type_2 = 13){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 8 && pokee->Type_2 = 14){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 8 && pokee->Type_2 = 15){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 8 && pokee->Type_2 = 16){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 8 && pokee->Type_2 = 17){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 8 && pokee->Type_2 = 18){
//     poke->Type_2 = float(0.5f);
//   }


//   //VOLADOR//
//   if(move->MoveType = 9 && poke->Type_2 = 1){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 9 && poke->Type_2 = 2){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 9 && poke->Type_2 = 3){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 9 && poke->Type_2 = 4){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 9 && poke->Type_2 = 5){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 9 && poke->Type_2 = 6){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 9 && poke->Type_2 = 7){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 9 && poke->Type_2 = 8){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 9 && poke->Type_2 = 9){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 9 && pokee->Type_2 = 10){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 9 && pokee->Type_2 = 11){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 9 && pokee->Type_2 = 12){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 9 && pokee->Type_2 = 13){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 9 && pokee->Type_2 = 14){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 9 && pokee->Type_2 = 15){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 9 && pokee->Type_2 = 16){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 9 && pokee->Type_2 = 17){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 9 && pokee->Type_2 = 18){
//     poke->Type_2 = float(1.0f);
//   }


//   //LUCHA//
//   if(move->MoveType = 10 && poke->Type_2 = 1){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_2 = 2){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_2 = 3){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_2 = 4){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_2 = 5){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_2 = 6){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_2 = 7){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_2 = 8){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 10 && poke->Type_2 = 9){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 10 && poke->Type_2 = 10){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_2 = 11){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_2 = 12){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 10 && poke->Type_2 = 13){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_2 = 14){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 10 && poke->Type_2 = 15){
//     poke->Type_2 = float(0.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_2 = 16){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 10 && poke->Type_2 = 17){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 10 && poke->Type_2 = 18){
//     poke->Type_2 = float(0.5f);
//   }


//     //NORMAL//
//   if(move->MoveType = 11 && poke->Type_2 = 1){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_2 = 2){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_2 = 3){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_2 = 4){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_2 = 5){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_2 = 6){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_2 = 7){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 11 && poke->Type_2 = 8){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_2 = 9){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_2 = 10){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_2 = 11){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_2 = 12){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_2 = 13){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_2 = 14){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_2 = 15){
//     poke->Type_2 = float(0.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_2 = 16){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 11 && poke->Type_2 = 17){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 11 && poke->Type_2 = 18){
//     poke->Type_2 = float(1.0f);
//   }

//   //PSIQUICO//
//   if(move->MoveType = 12 && poke->Type_2 = 1){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_2 = 2){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_2 = 3){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_2 = 4){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_2 = 5){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_2 = 6){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_2 = 7){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_2 = 8){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 12 && poke->Type_2 = 9){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_2 = 10){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_2 = 11){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_2 = 12){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 12 && poke->Type_2 = 13){
//     poke->Type_2 = float(0.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_2 = 14){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_2 = 15){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 12 && poke->Type_2 = 16){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 12 && poke->Type_2 = 17){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 12 && poke->Type_2 = 18){
//     poke->Type_2 = float(1.0f);
//   }

//   //SINIESTRO//
//   if(move->MoveType = 13 && poke->Type_2 = 1){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_2 = 2){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_2 = 3){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_2 = 4){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_2 = 5){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_2 = 6){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_2 = 7){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_2 = 8){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 13 && poke->Type_2 = 9){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_2 = 10){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 13 && poke->Type_2 = 11){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_2 = 12){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_2 = 13){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 13 && poke->Type_2 = 14){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_2 = 15){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_2 = 16){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 13 && poke->Type_2 = 17){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 13 && poke->Type_2 = 18){
//     poke->Type_2 = float(0.5f);
//   }

//   //VENENO//
//   if(move->MoveType = 14 && poke->Type_2 = 1){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_2 = 2){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_2 = 3){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_2 = 4){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_2 = 5){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_2 = 6){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 14 && poke->Type_2 = 7){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 14 && poke->Type_2 = 8){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_2 = 9){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_2 = 10){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_2 = 11){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_2 = 12){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_2 = 13){
//     poke->Type_2 = float(1.f);
//   }
//   if(move->MoveType = 14 && poke->Type_2 = 14){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_2 = 15){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 14 && poke->Type_2 = 16){
//     poke->Type_2 = float(0.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_2 = 17){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 14 && poke->Type_2 = 18){
//     poke->Type_2 = float(2.0f);
//   }

//   //FANTASMA//
//   if(move->MoveType = 15 && poke->Type_2 = 1){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_2 = 2){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_2 = 3){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_2 = 4){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_2 = 5){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_2 = 6){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_2 = 7){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_2 = 8){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_2 = 9){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_2 = 10){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_2 = 11){
//     poke->Type_2 = float(0.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_2 = 12){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_2 = 13){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 15 && poke->Type_2 = 14){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_2 = 15){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_2 = 16){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_2 = 17){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 15 && poke->Type_2 = 18){
//     poke->Type_2 = float(1.0f);
//   }

//   //ACERO//
//   if(move->MoveType = 16 && poke->Type_2 = 1){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 16 && poke->Type_2 = 2){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 16 && poke->Type_2 = 3){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 16 && poke->Type_2 = 4){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_2 = 5){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_2 = 6){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 16 && poke->Type_2 = 7){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_2 = 8){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_2 = 9){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_2 = 10){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_2 = 11){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_2 = 12){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 16 && poke->Type_2 = 13){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_2 = 14){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_2 = 15){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_2 = 16){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_2 = 17){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 16 && poke->Type_2 = 18){
//     poke->Type_2 = float(2.0f);
//   }

//   //DRAGON//
//   if(move->MoveType = 17 && poke->Type_2 = 1){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_2 = 2){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_2 = 3){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_2 = 4){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_2 = 5){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_2 = 6){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_2 = 7){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_2 = 8){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_2 = 9){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_2 = 10){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_2 = 11){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_2 = 12){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_2 = 13){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_2 = 14){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_2 = 15){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_2 = 16){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 17 && poke->Type_2 = 17){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 17 && poke->Type_2 = 18){
//     poke->Type_2 = float(0.0f);
//   }

//   //HADA//
//   if(move->MoveType = 18 && poke->Type_2 = 1){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 18 && poke->Type_2 = 2){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_2 = 3){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_2 = 4){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_2 = 5){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_2 = 6){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_2 = 7){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_2 = 8){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_2 = 9){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_2 = 10){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_2 = 11){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_2 = 12){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_2 = 13){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_2 = 14){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 18 && poke->Type_2 = 15){
//     poke->Type_2 = float(1.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_2 = 16){
//     poke->Type_2 = float(0.5f);
//   }
//   if(move->MoveType = 18 && poke->Type_2 = 17){
//     poke->Type_2 = float(2.0f);
//   }
//   if(move->MoveType = 18 && poke->Type_2 = 18){
//     poke->Type_2 = float(1.0f);
//   }
// }