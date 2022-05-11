#include <Gamebuino-Meta.h>


//Variables constantes
int score = 0;

//brique de départ
int brique_x = 14;
int brique_y = 60;
int brique_largeur = 50;
int brique_hauteur = 3;

//tableau de brique
int tab_brique[7][2] = {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};

//nouvelle brique
int brique;


int mode = 0;



void setup() {
  tab_brique[0][0] = brique_x;
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

  //zone des briques
  gb.display.setColor(248, 250, 255);
  gb.display.fillRect(14, 0, 2, 63);
  gb.display.fillRect(64, 0, 2, 63);

  // Gestion du clic sur A
  if (gb.buttons.pressed(BUTTON_A)){
  /*******************************************
  Mettre ici la code de posage de brique et du score ainsi que le cas de la défaite
  *******************************************/

  //si on a pas encore atteint la 7ème brique on fait monter la brique à poser
  if (tab_brique[7][1] == 0){
    brique_y -= 3;
  }
  //sinon on fait tourner les valeurs du tableau pour faire de la place pour la suivante
  else{
    for (int i = 1; i < 7; i++){
      tab_brique[i-1][0] = tab_brique[i][0];
      tab_brique[i-1][1] = tab_brique[i][1];
    }
    //on vide la prochaine case pour la nouvelle brique
    tab_brique[7][0] = 0;
    tab_brique[7][1] = 0;
  }
 }

  //affichage de la pile de brique
  for(int i = 0; i < 7; i++){
    //si la brique à une largeur de 0 c'est quelle n'existe pas donc on ne l'afiche pas
    if (tab_brique[i][1] != 0){
      gb.display.fillRect(tab_brique[0][0],brique_y,tab_brique[0][1],brique_hauteur);
    }
  }

  //score
  gb.display.setCursor(25, 5);
  gb.display.print("SCORE: ");
  gb.display.print(score);

  if (gb.buttons.released(BUTTON_B)) {
    mode = 0; // GAMEPLAY // 
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
}

void affichageScore(){
  gb.display.clear();

  gb.display.setCursor(25, 55);
  gb.display.print("Retour : B");

  if (gb.buttons.released(BUTTON_B)) {
    mode = 0; // GAMEPLAY // 
  }
}


