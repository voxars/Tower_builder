#include <Gamebuino-Meta.h>

//RGB
int red = 255;
int green = 0;
int blue = 0;

//Variables constantes
int score = 0;

//données d'une brique et init de la première
int brique_x = 64;
int brique_y = 57;
int brique_largeur = 50;
int brique_hauteur = 3;

//tableau de brique
int tab_brique[7][2] = {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};

//stocke dans quelle direction va la brique
boolean deplacement_brique_vers_gauche = true;

//nombre de briques posées (pour monter jusqu'a la hauteur de 7 briques)
int nb_brique = 1; //on compte la brique de départ

//tableau des scores
int tab_score[7] = {0,0,0,0,0,0,0};
String tab_names[6]= {"","","","","",""};
char player_name[10];
bool keyboard_reset = true;

boolean fin_partie = false;

int mode = 0;



void setup() {
  //brique de départ
  tab_brique[0][0] = 14;
  tab_brique[0][1] = brique_largeur;
  gb.begin();

}
void loop() {
  while (!gb.update());
  gb.display.clear();

  switch(mode){
    //menu
    case 0:
      affichageMenu();
      break;
    //Jeux
    case 1:
    affichageJeux();
      break;
    //Tableau des scores
    case 2:
      affichageScore();
      break;
  }

  
}

//fonctions

void affichageJeux(){
  gb.display.clear();

 //RGB
 Color rgb1 = gb.createColor(red, green, blue);
 Color rgb2 = gb.createColor(blue, red, green);
 if (red == 255 && green < 255 && blue == 0){
  green++; 
 }
 if (red != 0 && green == 255 && blue == 0){
  red--; 
 }
 if (red == 0 && green == 255 && blue < 255){
  blue++; 
 }
 if (red == 0 && green != 0 && blue == 255){
  green--; 
 }
 if (red < 255 && green == 0 && blue == 255){
  red++; 
 }
 if (red == 255 && green == 0 && blue != 0){
  blue--; 
 }
 gb.lights.fill(rgb1);

  //zone des briques
  gb.display.setColor(rgb1);
  gb.display.fillRect(14, 0, 2, 63);
  gb.display.fillRect(64, 0, 2, 63);

  //déplacment de la brique à l'horizotale
  if (deplacement_brique_vers_gauche == true){
    if (brique_x + brique_largeur > 14){
      brique_x--;
    }
    else{
      deplacement_brique_vers_gauche = false;
    }
  }
  else{
    if (brique_x < 64){
      brique_x++;
    }
    else{
      deplacement_brique_vers_gauche = true;
    }
  }
  
  // Gestion du clic sur A
  if (gb.buttons.pressed(BUTTON_A)){
  /*******************************************
  Mettre ici la code de posage de brique et du score ainsi que le cas de la défaite
  *******************************************/

  //tant que la brique est sur la pile -> on continue
  if (brique_largeur > 0){
    //découpage de la brique
    //si elle n'est pas parfaitement posé
    if ((tab_brique[(nb_brique - 1)][0] - brique_x) != 0){
      //si elle dépasse sur la droite
      if ((tab_brique[(nb_brique - 1)][0] - brique_x) < 0){
        //on enlève la partie droite
        brique_largeur = brique_largeur + (tab_brique[(nb_brique - 1)][0] - brique_x);
      }
      //si elle dépasse sur la gauche
      else{
        //on enlève la partie gauche
        brique_largeur = brique_largeur - (tab_brique[(nb_brique - 1)][0] - brique_x);
        brique_x = tab_brique[(nb_brique - 1)][0];
      }
    }

    //tant que le tableau n'est pas plein la brique en mouvement monte
    if (tab_brique[6][1] == 0){
      brique_y = brique_y - 3;
    }
    //tant que le tableau n'est pas plein on monte la tour
    if (nb_brique < 7){
      tab_brique[nb_brique][0] = brique_x;
      tab_brique[nb_brique][1] = brique_largeur;
      nb_brique++;
    }
    //sinon on fait tourner les valeurs du tableau pour faire de la place pour la suivante
    else{
      for (int i = 1; i < 7; i++){
        tab_brique[(i-1)][0] = tab_brique[i][0];
        tab_brique[(i-1)][1] = tab_brique[i][1];
      }
      //on pose la brique
      tab_brique[6][0] = brique_x;
      tab_brique[6][1] = brique_largeur;
    }
   }
   //on met la barre à gauche puis à droite alternativement
   if (deplacement_brique_vers_gauche == true){
    brique_x = 14 - brique_largeur;
    deplacement_brique_vers_gauche = false;
   }
   else{
    brique_x = 64;
    deplacement_brique_vers_gauche = true;
   }
   
   //si la brique n'est pas sur la pile -> fin de la partie
   if (brique_largeur <= 0){
    // si l'on à l'écran de fin on reset
    if (fin_partie == true){
      score = 0;
      brique_x = 64;
      brique_y = 57;
      brique_largeur = 50;
      brique_hauteur = 3;
      for (int i = 0; i < 7; i++){
        tab_brique[i][0] = 0;
        tab_brique[i][1] = 0;
      }
      deplacement_brique_vers_gauche = true;
      nb_brique = 1;
      fin_partie = false;
      tab_brique[0][0] = 14;
      tab_brique[0][1] = brique_largeur;
    }
    //sinon on met l'écran de fin
    else{
      fin_partie = true;
    }
   }
   // sinon on monte le score
   else{
    score++;
   
   }
 }

 if (fin_partie == true){
    if ((score >= (tab_score[5]))&& keyboard_reset == true) {
    gb.gui.keyboard("Entre ton nom!",player_name);       
    for(int i = 0; i < 5; i++){
      if(score>= tab_score[i]){
        for (int j = 4; j >= i; j--){
          tab_names[j] = tab_names[(j - 1)];
          tab_score[j] = tab_score[(j - 1)];
        }
        tab_names[i] = String(player_name);
        tab_score[i] = score;
        keyboard_reset = false;
        score = 0;
        break; 
        }
      }
    }
    else if(score >= tab_score[5]){
      for(int i = 0; i < 5; i++){
      if(score>= tab_score[i]){
        for (int j = 5; j >= i; j--){
          tab_names[j] = tab_names[(j - 1)];
          tab_score[j] = tab_score[(j - 1)];
        }
        tab_names[i] = String(player_name);
        tab_score[i] = score;
        score = 0;
        break; 
        }
      }
    }
    gb.display.setColor(rgb2);
    gb.display.setCursor(22, 15);
    gb.display.print("GAME OVER");
    gb.display.setCursor(25, 22);
    gb.display.print("press A");
    gb.display.setCursor(23, 29);
    gb.display.print("to reset");

  }

  //affichage de la brique qui bouge
  gb.display.setColor(rgb1);
  gb.display.fillRect(brique_x, brique_y,brique_largeur,brique_hauteur);
  //affichage de la pile de brique
  for(int i = 0; i < 7; i++){
    //si la brique à une largeur de 0 c'est quelle n'existe pas donc on ne l'afiche pas
    if (tab_brique[i][1] != 0){
      gb.display.fillRect(tab_brique[i][0],60 - i*brique_hauteur,tab_brique[i][1],brique_hauteur);
    }
  }

  //score
  gb.display.setColor(rgb2);
  gb.display.setCursor(25, 5);
  gb.display.print("SCORE: ");
  gb.display.print(score);


  if (gb.buttons.released(BUTTON_B)) {
    mode = 0; // GAMEPLAY // 
    score = 0;
    brique_x = 64;
    brique_y = 57;
    brique_largeur = 50;
    brique_hauteur = 3;
    for (int i = 0; i < 7; i++){
      tab_brique[i][0] = 0;
      tab_brique[i][1] = 0;
    }
    deplacement_brique_vers_gauche = true;
    nb_brique = 1;
    fin_partie = false;
    tab_brique[0][0] = 14;
    tab_brique[0][1] = brique_largeur;
    keyboard_reset = true;
  }

  if (gb.buttons.released(BUTTON_MENU)) {
    mode = 2; // HIGHSCORE //
    score = 0;
    brique_x = 64;
    brique_y = 57;
    brique_largeur = 50;
    brique_hauteur = 3;
    for (int i = 0; i < 7; i++){
      tab_brique[i][0] = 0;
      tab_brique[i][1] = 0;
    }
    deplacement_brique_vers_gauche = true;
    nb_brique = 1;
    fin_partie = false;
    tab_brique[0][0] = 14;
    tab_brique[0][1] = brique_largeur;
    keyboard_reset = true;
  }

}

void affichageMenu(){
  gb.display.clear();

  //titre
  gb.display.setCursor(16, 5);
  gb.display.print("TOWER BUILDER");

  gb.display.setCursor(25, 25);
  gb.display.print("Jouer : A");

  gb.display.setCursor(10, 35);
  gb.display.print("Scores : SELECT");

  gb.display.setCursor(2, 50);
  gb.display.print("Appuyer sur A pour");
  gb.display.setCursor(25,55);
  gb.display.print("empiler !");

  if (gb.buttons.released(BUTTON_A)) {
    mode = 1; // GAMEPLAY // 
  }

  if (gb.buttons.released(BUTTON_MENU)) {
    mode = 2; // HIGHSCORE //
  }
   if (score >= (tab_score[5])){
      keyboard_reset = true;
    }
}

void affichageScore(){
  gb.display.clear();
  gb.display.setCursor(15, 0);
  gb.display.print("Meilleur score");
  gb.display.setCursor(9, 8);
  gb.display.print(tab_names[0]);
  gb.display.setCursor(49, 8);
  gb.display.print(" - ");
  gb.display.print(tab_score[0]);
  gb.display.setCursor(9, 14);
  gb.display.print(tab_names[1]);
  gb.display.setCursor(49, 14);
  gb.display.print(" - ");
  gb.display.print(tab_score[1]);
  gb.display.setCursor(9, 20);
  gb.display.print(tab_names[2]);
  gb.display.setCursor(49, 20);
  gb.display.print(" - ");
  gb.display.print(tab_score[2]);
  gb.display.setCursor(9, 26);
  gb.display.print(tab_names[3]);
  gb.display.setCursor(49, 26);
  gb.display.print(" - ");
  gb.display.print(tab_score[3]);
  gb.display.setCursor(9, 32);
  gb.display.print(tab_names[4]);
  gb.display.setCursor(49, 32);
  gb.display.print(" - ");
  gb.display.print(tab_score[4]);
  

  gb.display.setCursor(25, 55);
  gb.display.print("Retour : B");

  if (gb.buttons.released(BUTTON_B)) {
    mode = 0; // GAMEPLAY // 
  }
}
