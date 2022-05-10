#include <Gamebuino-Meta.h>


//brique de départ
int brique_x=14;
int brique_y = 60;
int brique_largeur = 50;
int brique_hauteur = 3;

//nouvelle brique
float brique_actuelle_x=0;
int brique_actuelle_y = 0;
int brique_actuelle_largeur = 0;
int brique_actuelle_hauteur = 0;
float vitesse = 0.2;

//tableau des scores
int score = 0;
int scoreTab[10];

//mode de vue
byte mode = 0;


void setup() {

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

  //premiere brique
  gb.display.fillRect(brique_x,brique_y,brique_largeur,brique_hauteur);

  //score
  gb.display.setCursor(25, 5);
  gb.display.print("SCORE: ");
  gb.display.print(score);

  if (gb.buttons.released(BUTTON_B)) {
    mode = 0; //retour au menu
  }

  //brique jouable
  //on prend les coordonnées de la brique precedente
  brique_actuelle_x = 65;
  brique_actuelle_y = brique_y-3;
  brique_actuelle_largeur = brique_largeur;
  brique_actuelle_hauteur = brique_hauteur;

  //on déplace la brique actuelle
  if(brique_actuelle_x >= 64){
    vitesse = 0.2;
  }
  if(brique_actuelle_x <= 0){
    vitesse = -0.2;
  }
  brique_actuelle_x += vitesse;
  

  gb.display.setColor(248, 250, 255);

  gb.display.fillRect(brique_actuelle_x,brique_actuelle_y,brique_actuelle_largeur,brique_actuelle_hauteur);

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

