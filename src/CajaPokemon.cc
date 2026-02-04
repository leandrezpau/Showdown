struct TPokemon{
  int Atk, SpcAtk, Def, SpcDef;
  int PS;
  int Type_1, Type_2;
  int Level,id;
  char *Name;
  float f_type1, f_type2;
};


TPokemon *caja;

void Llenar_caja(){

  (caja+0)->Atk=162;
  (caja+0)->Def=94;
  (caja+0)->SpcAtk=156;
  (caja+0)->SpcDef=92;
  (caja+0)->PS=185;
  (caja+0)->Type_1=1;
  (caja+0)->Type_2=9;
  (caja+0)->f_type1=0.0f;
  (caja+0)->f_type2=0.0f;
  (caja+0)->Level=50;
  (caja+0)->id=0;
  (caja+0)->Name={"Kabbu Bugfables Xavier Tercero"};
  
  (caja+1)->Atk=162;
  (caja+1)->Def=94;
  (caja+1)->SpcAtk=156;
  (caja+1)->SpcDef=92;
  (caja+1)->PS=185;
  (caja+1)->Type_1=1;
  (caja+1)->Type_2=8;
  (caja+1)->f_type1=0.0f;
  (caja+1)->f_type2=0.0f;
  (caja+1)->Level=50;
  (caja+1)->id=1;
  (caja+1)->Name={"Charizard"};


  (caja+2)->Atk=31;
  (caja+2)->Def=31;
  (caja+2)->SpcAtk=62;
  (caja+2)->SpcDef=110;
  (caja+2)->PS=310;
  (caja+2)->Type_1=11;
  (caja+2)->Type_2=0;
  (caja+2)->Level=50;
  (caja+2)->id=2;
  (caja+2)->Name={"Chansey"};


  (caja+3)->Atk=130;
  (caja+3)->Def=200;
  (caja+3)->SpcAtk=90;
  (caja+3)->SpcDef=55;
  (caja+3)->PS=121;
  (caja+3)->Type_1=2;
  (caja+3)->Type_2=5;
  (caja+3)->Level=50;
  (caja+3)->id=3;
  (caja+3)->Name={"Cloyster"};


  (caja+4)->Atk=118;
  (caja+4)->Def=111;
  (caja+4)->SpcAtk=149;
  (caja+4)->SpcDef=195;
  (caja+4)->PS=152;
  (caja+4)->Type_1=18;
  (caja+4)->Type_2=0;
  (caja+4)->Level=50;
  (caja+4)->id=4;
  (caja+4)->Name={"Florges"};


  (caja+5)->Atk=210;
  (caja+5)->Def=102;
  (caja+5)->SpcAtk=129;
  (caja+5)->SpcDef=93;
  (caja+5)->PS=232;
  (caja+5)->Type_1=11;
  (caja+5)->Type_2=0;
  (caja+5)->Level=50;
  (caja+5)->id=5;
  (caja+5)->Name={"Slaking"};


  (caja+6)->Atk=32;
  (caja+6)->Def=301;
  (caja+6)->SpcAtk=21;
  (caja+6)->SpcDef=301;
  (caja+6)->PS=80;
  (caja+6)->Type_1=8;
  (caja+6)->Type_2=7;
  (caja+6)->Level=50;
  (caja+6)->id=6;
  (caja+6)->Name={"Shuckle"};


  (caja+7)->Atk=102;
  (caja+7)->Def=131;
  (caja+7)->SpcAtk=199;
  (caja+7)->SpcDef=110;
  (caja+7)->PS=145;
  (caja+7)->Type_1=8;
  (caja+7)->Type_2=3;
  (caja+7)->Level=50;
  (caja+7)->id=7;
  (caja+7)->Name={"Vikavolt"};


  (caja+8)->Atk=161;
  (caja+8)->Def=183;
  (caja+8)->SpcAtk=189;
  (caja+8)->SpcDef=112;
  (caja+8)->PS=177;
  (caja+8)->Type_1=16;
  (caja+8)->Type_2=17;
  (caja+8)->Level=50;
  (caja+8)->id=8;
  (caja+8)->Name={"Duralodon"};


  (caja+9)->Atk=205;
  (caja+9)->Def=200;
  (caja+9)->SpcAtk=123;
  (caja+9)->SpcDef=145;
  (caja+9)->PS=192;
  (caja+9)->Type_1=7;
  (caja+9)->Type_2=0;
  (caja+9)->Level=50;
  (caja+9)->id=9;
  (caja+9)->Name={"Gigalith"};

  (caja+10)->Atk=128;
  (caja+10)->Def=139;
  (caja+10)->SpcAtk=194;
  (caja+10)->SpcDef=150;
  (caja+10)->PS=217;
  (caja+10)->Type_1=12;
  (caja+10)->Type_2=0;
  (caja+10)->Level=50;
  (caja+10)->id=10;
  (caja+10)->Name={"Reuniclus"};

  (caja+11)->Atk=190;
  (caja+11)->Def=120;
  (caja+11)->SpcAtk=195;
  (caja+11)->SpcDef=120;
  (caja+11)->PS=207;
  (caja+11)->Type_1=9;
  (caja+11)->Type_2=4;
  (caja+11)->Level=50;
  (caja+11)->id=11;
  (caja+11)->Name={"Shaymin"};


}


// int global_id=1;

// printf("Elija pokemon atacante:\n");
// //********Lista*********//

// for(int i=0;i<12;++i){

// printf("***************************************************************************\n")
// printf("* %s  attk:%d   Def:%d                    *\n"(caja+i).nombre,(caja+i).attk);
// printf("**************************************************************\n")
// printf("\n\n");

// }

// //*******Lista**********//


// //seleccion pokemon atk//

//   switch (Global_id)
//   {
//   case 1:
//     Atacante = *(caja+1);
//     break;
  
//   default:
//   printf("tu puta madre elige un pokemon de la lista o te obligo a jugvar bugfables.");
//     break;
//   };

// //////seleccion pokemonatk//////

// //(system.cls)//

// //seleccion pokemon def///

//   switch (Global_id)
//   {
//   case 1:
//     Atacante = *(caja+1);
//     break;
  
//   default:
//   printf("tu puta madre elige un pokemon de la lista o te obligo a jugvar bugfables.");
//     break;
//   };

// //////seleccion pokemon def//////

// //system.cls//



// //insertarde movimietnos aqui//

// void Mostrar_elegidos(){

//   // attk: id 1
//   //deff id 4
//   //mov. id 15

//   //correcto?(Y/N)
//   //scanf(y)

// }






