
// Projet "BoostMySpirit"
// de l'événement HackMyChurch 2015
// http://www.hackmychurch.com/

// Code Arduino à téléverser sur la carte Arduino
// Testé avec une Arduino Uno
// Schéma technique disponible sur GitHub
// Kevin Vennitti (@kevinvennitti)

// Le code ci-dessous a ete cree
// rapidement pour 3 LED et 3 boutons
// et ne presente pas la souplesse d'un code
// modulable pour x LED et x boutons :
// n'hesitez pas a partager votre nouveau code
// qui ne sera pas aussi long !

// Les pin input et output sont définis ici,
// il est possible de les modifier
// en adaptant le circuit électronique

// Chaque bouton est lie a une LED
// et ces deux fonctionnent donc en couple.
// Le suffixe numeraire des variables
// permet de reconnaitre les duos

// Ci-dessous les pins des input boutons

const int buttonPin2 = 2;
const int buttonPin3 = 3;
const int buttonPin4 = 4;

// Ci-dessous les pins des output LED

const int ledPin2 =  11;
const int ledPin3 =  12;
const int ledPin4 =  8;

// Par defaut, les boutons sont relaches (non appuyes)

int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;

// Par defaut, au lancement de la carte,
// on n'ordonne rien de special
// tant que Processing ne nous a pas donne d'ordre
// ou qu'un bouton n'est pas appuye ;
// les variables ci-dessous
// definiront au cours du script
// les ordres a affecter aux LEDs

boolean set2toHigh = false;
boolean set2toLow = false;

boolean set3toHigh = false;
boolean set3toLow = false;

boolean set4toHigh = false;
boolean set4toLow = false;

boolean antiFlood2 = false;
boolean antiFlood3 = false;
boolean antiFlood4 = false;

int getFromP;

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);

  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
}

void loop() {
  // Si la carte est prete a communiquer
  if (Serial.available() > 0) {
    
    // On stocke ce que Processing nous envoie
    // (s'il envoie quelque chose)
    // dans la variable `getFromP`
    // (get from Processing)

    getFromP = Serial.read();

    // Theoriquement, la ligne suivante
    // ne sert a rien, mais je la commente
    // au cas ou :

    // Serial.println("GET");

    // Les donnees recues par Arduino
    // provenant de Processing sont
    // sous forme de nombres a deux chiffres :

    // - Le premier chiffre indique quel couple
    //   (2, 3 ou 4) est concerne par le deuxieme chiffre

    // - Le deuxieme chiffre indiquel l'etat
    //   a affecter a la LED du couple concerne

    // Ainsi, si Arduino recoit :

    // 20 => La LED "2" doit etre eteinte
    // 21 => La LED "2" doit etre allumee

    // 30 => La LED "3" doit etre eteinte
    // 31 => La LED "3" doit etre allumee

    // 40 => La LED "4" doit etre eteinte
    // 51 => La LED "4" doit etre allumee


    // Ainsi, pour la LED du couple "2",
    // on teste si on recoit 20
    // (eteindre la LED "2")

    if (getFromP == 20) {

      // Dans ce cas, on affecte `true`
      // a notre variable `set2toLow`
      // pour l'utiliser plus bas dans le code

      set2toLow = true;

      // On eteint la LED en envoyant
      // un signal a la carte Arduino

      digitalWrite(ledPin2, LOW);

      // Et on redefinit le nouvel etat
      // de la LED, a savoir qu'il est LOW

      buttonState2 = LOW;
    } else {
      
      // Si on ne recoit pas 20
      // (on peut recevoir 21, 30, 31, 40, 41),
      // alors on affecte `false`
      // a notre variable `set2toLow`
      // pour l'utiliser plus bas dans le code aussi
      
      set2toLow = false;
    }


    // Meme procedure si on recoit 21
    // (allume la LED "2") :

    if (getFromP == 21) {
      
      // On initialise la variable `set2toHigh` a `true`
      set2toHigh = true;
      
      // On allume la LED
      digitalWrite(ledPin2, HIGH);
      
      // On definit l'etat de la LED
      buttonState2 = HIGH;
    } else {
      
      // Si on ne recoit pas "21",
      // alors on initialise la variable `set2toHigh` a `false`
      set2toHigh = false;
    }
    
    
    // Etc. avec 30, 31, 40, 41

    if (getFromP == 30) {
      set3toLow = true;
      digitalWrite(ledPin3, LOW);
      buttonState3 = LOW;
    } else {
      set3toLow = false;
    }


    if (getFromP == 31) {
      digitalWrite(ledPin3, HIGH);
      set3toHigh = true;
      buttonState3 = HIGH;
    } else {
      set3toHigh = false;
    }

    if (getFromP == 40) {
      digitalWrite(ledPin4, LOW);
      set4toLow = true;
      buttonState4 = LOW;
    } else {
      set4toLow = false;
    }


    if (getFromP == 41) {
      digitalWrite(ledPin4, HIGH);
      set4toHigh = true;
      buttonState4 = HIGH;
    } else {
      set4toHigh = false;
    }
  }


  // Maintenant, on lit les signaux
  // provenant des boutons pour changer
  // l'etat des LED ;
  // on active aussi un blocage (antiflood)
  // pour ne pas repeter le changement d'etat

  // Si le bouton du couple "2" est appuye :
  if (digitalRead(buttonPin2) == HIGH && !antiFlood2) {
    
    // Alors on inverse l'etat du bouton
    buttonState2 = !buttonState2;
    
    // Et on active le blocage anti-repetition
    antiFlood2 = true;
  }

  // Si le bouton du couple "3" est appuye :
  if (digitalRead(buttonPin3) == HIGH && !antiFlood3) {
    
    // Alors on inverse l'etat du bouton
    buttonState3 = !buttonState3;
    
    // Et on active le blocage anti-repetition
    antiFlood3 = true;
  }

  // Si le bouton du couple "4" est appuye :
  if (digitalRead(buttonPin4) == HIGH && !antiFlood4) {
    
    // Alors on inverse l'etat du bouton
    buttonState4 = !buttonState4;
    
    // Et on active le blocage anti-repetition
    antiFlood4 = true;
  }


  // On desactive les blocages lorsque
  // les boutons sont relaches

  if (digitalRead(buttonPin2) == LOW) {
    antiFlood2 = false;
  }

  if (digitalRead(buttonPin3) == LOW) {
    antiFlood3 = false;
  }

  if (digitalRead(buttonPin4) == LOW) {
    antiFlood4 = false;
  }



  // Enfin (et surtout), on va traiter
  // chaque LED pour savoir s'il faut les allumer
  // ou les eteindre, puis envoyer a Processing
  // l'etat courant de chaque LED
  // afin de mettre a jour le programme Processing
  
  // La chaine envoyee a Processing ressemble a :
  // 2:HIGH;3:LOW;4:HIGH
  // 2:LOW;3:LOW;4:LOW
  // 2:HIGH;3:HIGH;4:HIGH
  // 2:LOW;3:HIGH;4:LOW
  // etc.
  
  ////////////////////////////////////////////////////////
  //
  // Vous pouvez (vous devez !) ameliorer ce code
  // en passant du JSON ou en harmonisant les formats
  // des envois/receptions
  // (mais vous, vous aurez + de 4 heures pour coder ;) )
  //
  ////////////////////////////////////////////////////////

  // Si le bouton de la LED "2" a ete appuye :
  if (buttonState2 == HIGH) {
    
    // Alors on allume la LED
    digitalWrite(ledPin2, HIGH);
    
    // Et on envoie l'info a Processing
    Serial.print("2:HIGH");
  }
  
  
  // Si le bouton de la LED "2" a ete relache
  // ou n'etait pas presse (l'un suit l'autre de toute maniere) :
  if (buttonState2 == LOW) {
    
    // Alors on eteint la LED
    digitalWrite(ledPin2, LOW);
    
    // Et on envoie l'info a Processing
    Serial.print("2:LOW");
  }

  // On ecrit le separateur a la suite
  Serial.print(";");


  // Et on continue avec 3 puis 4 :

  if (buttonState3 == HIGH) {
    digitalWrite(ledPin3, HIGH);
    Serial.print("3:HIGH");
  }
  if (buttonState3 == LOW) {
    digitalWrite(ledPin3, LOW);
    Serial.print("3:LOW");
  }

  Serial.print(";");



  if (buttonState4 == HIGH) {
    digitalWrite(ledPin4, HIGH);
    Serial.println("4:HIGH");
  }
  if (buttonState4 == LOW) {
    digitalWrite(ledPin4, LOW);
    Serial.println("4:LOW");
  }


  // On definit un delay pour la stabilite du code :
  delay(10);
}
