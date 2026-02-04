struct TPkmnMove{
  int id;
  int MoveType;
  int Power;
  char *MoveName;
  float Acuracy; 
  int Category; //0 FÍSICO    1 ESPECIAL
  
};

TPkmnMove *listamove;

void Llenar_movimientos(){
  ///////////////////////////////////////////////////
  //////////////////FUEGO/////////////////////////////
  ///////////////////////////////////////////////////

  (listamove + 0)->id = 0;
  (listamove + 0)->MoveType = 1;
  (listamove + 0)->Power = 90;
  (listamove + 0)->Acuracy = 100;
  (listamove + 0)->Category = 1;
  (listamove + 0)->MoveName = {"Lanzallamas\0"};


  (listamove + 1)->id = 1;
  (listamove + 1)->MoveType = 1;
  (listamove + 1)->Power = 85;
  (listamove + 1)->Acuracy = 100;
  (listamove + 1)->Category = 0;
  (listamove + 1)->MoveName = {"Punyo Fuego\0"};



  (listamove + 2)->id = 2;
  (listamove + 2)->MoveType = 1;
  (listamove + 2)->Power = 40;
  (listamove + 2)->Acuracy = 100;
  (listamove + 2)->Category = 1;
  (listamove + 2)->MoveName = {"Ascuas\0"};



  (listamove + 3)->id = 3;
  (listamove + 3)->MoveType = 1;
  (listamove + 3)->Power = 40;
  (listamove + 3)->Acuracy = 100;
  (listamove + 3)->Category = 0;
  (listamove + 3)->MoveName = {"Colmillo Fuego\0"};

  ///////////////////////////////////////////////////
  //////////////////AGUA/////////////////////////////
  ///////////////////////////////////////////////////


  (listamove + 4)->id = 4;
  (listamove + 4)->MoveType = 2;
  (listamove + 4)->Power = 100;
  (listamove + 4)->Acuracy = 80;
  (listamove + 4)->Category = 1;
  (listamove + 4)->MoveName = {"Hidrobomba\0"};


  (listamove + 5)->id = 5;
  (listamove + 5)->MoveType = 2;
  (listamove + 5)->Power = 90;
  (listamove + 5)->Acuracy = 100;
  (listamove + 5)->Category = 0;
  (listamove + 5)->MoveName = {"Acuacola\0"};



  (listamove + 6)->id = 6;
  (listamove + 6)->MoveType = 2;
  (listamove + 6)->Power = 40;
  (listamove + 6)->Acuracy = 100;
  (listamove + 6)->Category = 1;
  (listamove + 6)->MoveName = {"Pistola Agua\0"};



  (listamove + 7)->id = 7;
  (listamove + 7)->MoveType = 2;
  (listamove + 7)->Power = 50;
  (listamove + 7)->Acuracy = 100;
  (listamove + 7)->Category = 0;
  (listamove + 7)->MoveName = {"Concha Filo\0"};



  ///////////////////////////////////////////////////
  //////////////////ELECTRICO/////////////////////////////
  ///////////////////////////////////////////////////


  (listamove + 8)->id = 8;
  (listamove + 8)->MoveType = 3;
  (listamove + 8)->Power = 110;
  (listamove + 8)->Acuracy = 90;
  (listamove + 8)->Category = 1;
  (listamove + 8)->MoveName = {"Trueno\0"};


  (listamove + 9)->id = 9;
  (listamove + 9)->MoveType = 3;
  (listamove + 9)->Power = 85;
  (listamove + 9)->Acuracy = 100;
  (listamove + 9)->Category = 0;
  (listamove + 9)->MoveName = {"Puño Trueno\0"};



  (listamove + 10)->id = 10;
  (listamove + 10)->MoveType = 3;
  (listamove + 10)->Power = 40;
  (listamove + 10)->Acuracy = 100;
  (listamove + 10)->Category = 1;
  (listamove + 10)->MoveName = {"Impactrueno\0"};



  (listamove + 11)->id = 11;
  (listamove + 11)->MoveType = 3;
  (listamove + 11)->Power = 50;
  (listamove + 11)->Acuracy = 100;
  (listamove + 11)->Category = 0;
  (listamove + 11)->MoveName = {"Colmillo Electrico\0"};


  ///////////////////////////////////////////////////
  //////////////////PLANTA/////////////////////////////
  ///////////////////////////////////////////////////


  (listamove + 12)->id = 12;
  (listamove + 12)->MoveType = 4;
  (listamove + 12)->Power = 110;
  (listamove + 12)->Acuracy = 80;
  (listamove + 12)->Category = 1;
  (listamove + 12)->MoveName = {"Lluevehojas\0"};


  (listamove + 13)->id = 13;
  (listamove + 13)->MoveType = 4;
  (listamove + 13)->Power = 90;
  (listamove + 13)->Acuracy = 100;
  (listamove + 13)->Category = 0;
  (listamove + 13)->MoveName = {"Hoja Aguda\0"};



  (listamove + 14)->id = 14;
  (listamove + 14)->MoveType = 4;
  (listamove + 14)->Power = 40;
  (listamove + 14)->Acuracy = 100;
  (listamove + 14)->Category = 1;
  (listamove + 14)->MoveName = {"Megagotar\0"};



  (listamove + 15)->id = 15;
  (listamove + 15)->MoveType = 4;
  (listamove + 15)->Power = 50;
  (listamove + 15)->Acuracy = 100;
  (listamove + 15)->Category = 0;
  (listamove + 15)->MoveName = {"Latigo Cepa\0"};


  ///////////////////////////////////////////////////
  //////////////////HIELO/////////////////////////////
  ///////////////////////////////////////////////////


  (listamove + 16)->id = 16;
  (listamove + 16)->MoveType = 5;
  (listamove + 16)->Power = 110;
  (listamove + 16)->Acuracy = 80;
  (listamove + 16)->Category = 1;
  (listamove + 16)->MoveName = {"Ventisca\0"};


  (listamove + 17)->id = 17;
  (listamove + 17)->MoveType = 5;
  (listamove + 17)->Power = 999999999;
  (listamove + 17)->Acuracy = 30;
  (listamove + 17)->Category = 0;
  (listamove + 17)->MoveName = {"Frio Polar\0"};



  (listamove + 18)->id = 18;
  (listamove + 18)->MoveType = 5;
  (listamove + 18)->Power = 40;
  (listamove + 18)->Acuracy = 100;
  (listamove + 18)->Category = 1;
  (listamove + 18)->MoveName = {"Nieve Polvo\0"};



  (listamove + 19)->id = 19;
  (listamove + 19)->MoveType = 5;
  (listamove + 19)->Power = 50;
  (listamove + 19)->Acuracy = 100;
  (listamove + 19)->Category = 0;
  (listamove + 19)->MoveName = {"Colmillo Hielo\0"};


  ///////////////////////////////////////////////////
  //////////////////TIERRA/////////////////////////////
  ///////////////////////////////////////////////////


  (listamove + 20)->id = 20;
  (listamove + 20)->MoveType = 6;
  (listamove + 20)->Power = 999999999;
  (listamove + 20)->Acuracy = 30;
  (listamove + 20)->Category = 1;
  (listamove + 20)->MoveName = {"Fisura\0"};


  (listamove + 21)->id = 21;
  (listamove + 21)->MoveType = 6;
  (listamove + 21)->Power = 100;
  (listamove + 21)->Acuracy = 100;
  (listamove + 21)->Category = 0;
  (listamove + 21)->MoveName = {"Terremoto\0"};



  (listamove + 22)->id = 22;
  (listamove + 22)->MoveType = 6;
  (listamove + 22)->Power = 40;
  (listamove + 22)->Acuracy = 100;
  (listamove + 22)->Category = 1;
  (listamove + 22)->MoveName = {"Disparo Lodo\0"};



  (listamove + 23)->id = 23;
  (listamove + 23)->MoveType = 6;
  (listamove + 23)->Power = 50;
  (listamove + 23)->Acuracy = 100;
  (listamove + 23)->Category = 0;
  (listamove + 23)->MoveName = {"Terratemblor\0"};


  ///////////////////////////////////////////////////
  //////////////////ROCA/////////////////////////////
  ///////////////////////////////////////////////////

  (listamove + 24)->id = 24;
  (listamove + 24)->MoveType = 7;
  (listamove + 24)->Power = 40;
  (listamove + 24)->Acuracy = 100;
  (listamove + 24)->Category = 1;
  (listamove + 24)->MoveName = {"Pedrada\0"};


  (listamove + 25)->id = 25;
  (listamove + 25)->MoveType = 7;
  (listamove + 25)->Power = 40;
  (listamove + 25)->Acuracy = 100;
  (listamove + 25)->Category = 0;
  (listamove + 25)->MoveName = {"Golpe Roca\0"};



  (listamove + 26)->id = 26;
  (listamove + 26)->MoveType = 7;
  (listamove + 26)->Power = 120;
  (listamove + 26)->Acuracy = 85;
  (listamove + 26)->Category = 1;
  (listamove + 26)->MoveName = {"Roca Afilada\0"};



  (listamove + 27)->id = 27;
  (listamove + 27)->MoveType = 7;
  (listamove + 27)->Power = 100;
  (listamove + 27)->Acuracy = 100;
  (listamove + 27)->Category = 0;
  (listamove + 27)->MoveName = {"Rompe Roca\0"};

  ///////////////////////////////////////////////////
  //////////////////BICHO/////////////////////////////
  ///////////////////////////////////////////////////

  (listamove + 28)->id = 28;
  (listamove + 28)->MoveType = 8;
  (listamove + 28)->Power = 80;
  (listamove + 28)->Acuracy = 100;
  (listamove + 28)->Category = 1;
  (listamove + 28)->MoveName = {"Chupavidas\0"};


  (listamove + 29)->id = 29;
  (listamove + 29)->MoveType = 8;
  (listamove + 29)->Power = 120;
  (listamove + 29)->Acuracy = 85;
  (listamove + 29)->Category = 0;
  (listamove + 29)->MoveName = {"Megacuerno\0"};



  (listamove + 30)->id = 30;
  (listamove + 30)->MoveType = 8;
  (listamove + 30)->Power = 50;
  (listamove + 30)->Acuracy = 100;
  (listamove + 30)->Category = 1;
  (listamove + 30)->MoveName = {"Aguijon Letal\0"};



  (listamove + 31)->id = 31;
  (listamove + 31)->MoveType = 8;
  (listamove + 31)->Power = 30;
  (listamove + 31)->Acuracy = 100;
  (listamove + 31)->Category = 0;
  (listamove + 31)->MoveName = {"Picadura\0"};

  ///////////////////////////////////////////////////
  //////////////////VOLADOR/////////////////////////////
  ///////////////////////////////////////////////////

  (listamove + 32)->id = 32;
  (listamove + 32)->MoveType = 9;
  (listamove + 32)->Power = 110;
  (listamove + 32)->Acuracy = 70;
  (listamove + 32)->Category = 1;
  (listamove + 32)->MoveName = {"Huracan\0"};


  (listamove + 33)->id = 33;
  (listamove + 33)->MoveType = 9;
  (listamove + 33)->Power = 120;
  (listamove + 33)->Acuracy = 100;
  (listamove + 33)->Category = 0;
  (listamove + 33)->MoveName = {"Pajaro Osado\0"};



  (listamove + 34)->id = 34;
  (listamove + 34)->MoveType = 9;
  (listamove + 34)->Power = 50;
  (listamove + 34)->Acuracy = 100;
  (listamove + 34)->Category = 1;
  (listamove + 34)->MoveName = {"Tornado\0"};



  (listamove + 35)->id = 35;
  (listamove + 35)->MoveType = 9;
  (listamove + 35)->Power = 60;
  (listamove + 35)->Acuracy = 100;
  (listamove + 35)->Category = 0;
  (listamove + 35)->MoveName = {"Ataque Ala\0"};


  ///////////////////////////////////////////////////
  //////////////////LUCHA/////////////////////////////
  ///////////////////////////////////////////////////

  (listamove + 36)->id = 36;
  (listamove + 36)->MoveType = 10;
  (listamove + 36)->Power = 40;
  (listamove + 36)->Acuracy = 100;
  (listamove + 36)->Category = 1;
  (listamove + 36)->MoveName = {"Golpe Certero\0"};


  (listamove + 37)->id = 37;
  (listamove + 37)->MoveType = 10;
  (listamove + 37)->Power = 30;
  (listamove + 37)->Acuracy = 100;
  (listamove + 37)->Category = 0;
  (listamove + 37)->MoveName = {"Punta Pie\0"};



  (listamove + 38)->id = 38;
  (listamove + 38)->MoveType = 10;
  (listamove + 38)->Power = 120;
  (listamove + 38)->Acuracy = 100;
  (listamove + 38)->Category = 1;
  (listamove + 38)->MoveName = {"Abocajarro\0"};



  (listamove + 39)->id = 39;
  (listamove + 39)->MoveType = 10;
  (listamove + 39)->Power = 120;
  (listamove + 39)->Acuracy = 70;
  (listamove + 39)->Category = 0;
  (listamove + 39)->MoveName = {"Onda Certera\0"};

  ///////////////////////////////////////////////////
  //////////////////NORMAL/////////////////////////////
  ///////////////////////////////////////////////////

  (listamove + 40)->id = 40;
  (listamove + 40)->MoveType = 11;
  (listamove + 40)->Power = 110;
  (listamove + 40)->Acuracy = 100;
  (listamove + 40)->Category = 1;
  (listamove + 40)->MoveName = {"Hiperrayo\0"};


  (listamove + 41)->id = 41;
  (listamove + 41)->MoveType = 11;
  (listamove + 41)->Power = 120;
  (listamove + 41)->Acuracy = 100;
  (listamove + 41)->Category = 0;
  (listamove + 41)->MoveName = {"Giga Impacto\0"};



  (listamove + 42)->id = 42;
  (listamove + 42)->MoveType = 11;
  (listamove + 42)->Power = 60;
  (listamove + 42)->Acuracy = 100;
  (listamove + 42)->Category = 1;
  (listamove + 42)->MoveName = {"Canon\0"};



  (listamove + 43)->id = 43;
  (listamove + 43)->MoveType = 11;
  (listamove + 43)->Power = 40;
  (listamove + 43)->Acuracy = 100;
  (listamove + 43)->Category = 0;
  (listamove + 43)->MoveName = {"Placaja\0"};

   ///////////////////////////////////////////////////
  //////////////////PSIQUICO/////////////////////////////
  ///////////////////////////////////////////////////

  (listamove + 44)->id = 44;
  (listamove + 44)->MoveType = 12;
  (listamove + 44)->Power = 120;
  (listamove + 44)->Acuracy = 100;
  (listamove + 44)->Category = 1;
  (listamove + 44)->MoveName = {"Premonicion\0"};


  (listamove + 45)->id = 45;
  (listamove + 45)->MoveType = 12;
  (listamove + 45)->Power = 90;
  (listamove + 45)->Acuracy = 90;
  (listamove + 45)->Category = 0;
  (listamove + 45)->MoveName = {"Cabezazo Zen\0"};



  (listamove + 46)->id = 46;
  (listamove + 46)->MoveType = 12;
  (listamove + 46)->Power = 40;
  (listamove + 46)->Acuracy = 100;
  (listamove + 46)->Category = 1;
  (listamove + 46)->MoveName = {"Psicocarga\0"};



  (listamove + 47)->id = 47;
  (listamove + 47)->MoveType = 12;
  (listamove + 47)->Power = 60;
  (listamove + 47)->Acuracy = 100;
  (listamove + 47)->Category = 0;
  (listamove + 47)->MoveName = {"Psicocolmillo\0"};


   ///////////////////////////////////////////////////
  //////////////////SINIESTRO/////////////////////////////
  ///////////////////////////////////////////////////

  (listamove + 48)->id = 48;
  (listamove + 48)->MoveType = 13;
  (listamove + 48)->Power = 80;
  (listamove + 48)->Acuracy = 100;
  (listamove + 48)->Category = 1;
  (listamove + 48)->MoveName = {"Pulso Umbrio\0"};


  (listamove + 49)->id = 49;
  (listamove + 49)->MoveType = 13;
  (listamove + 49)->Power = 90;
  (listamove + 49)->Acuracy = 100;
  (listamove + 49)->Category = 0;
  (listamove + 49)->MoveName = {"Juego Sucio\0"};



  (listamove + 50)->id = 50;
  (listamove + 50)->MoveType = 13;
  (listamove + 50)->Power = 50;
  (listamove + 50)->Acuracy = 100;
  (listamove + 50)->Category = 1;
  (listamove + 50)->MoveName = {"Alario\0"};



  (listamove + 51)->id = 51;
  (listamove + 51)->MoveType = 13;
  (listamove + 51)->Power = 20;
  (listamove + 51)->Acuracy = 100;
  (listamove + 51)->Category = 0;
  (listamove + 51)->MoveName = {"Chuleria\0"};


   ///////////////////////////////////////////////////
  //////////////////VENENO/////////////////////////////
  ///////////////////////////////////////////////////

  (listamove + 52)->id = 52;
  (listamove + 52)->MoveType = 14;
  (listamove + 52)->Power = 110;
  (listamove + 52)->Acuracy = 80;
  (listamove + 52)->Category = 1;
  (listamove + 52)->MoveName = {"Lanzamugre\0"};


  (listamove + 53)->id = 53;
  (listamove + 53)->MoveType = 14;
  (listamove + 53)->Power = 90;
  (listamove + 53)->Acuracy = 100;
  (listamove + 53)->Category = 0;
  (listamove + 53)->MoveName = {"Punya Nociva\0"};



  (listamove + 54)->id = 54;
  (listamove + 54)->MoveType = 14;
  (listamove + 54)->Power = 40;
  (listamove + 54)->Acuracy = 100;
  (listamove + 54)->Category = 1;
  (listamove + 54)->MoveName = {"Bomba germen\0"};



  (listamove + 55)->id = 55;
  (listamove + 55)->MoveType = 14;
  (listamove + 55)->Power = 15;
  (listamove + 55)->Acuracy = 100;
  (listamove + 55)->Category = 0;
  (listamove + 55)->MoveName = {"Picotazo venenoso\0"};

}