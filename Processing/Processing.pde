
// Projet "Boost My Spirit"
// de l'événement HackMyChurch 2015
// http://www.hackmychurch.com/

// Code Processing qui exécute le dispositif
// et qui écoute les données Arduino (via Serial)
// Testé avec Processing 2.2.1
// Fonctionne sous Mac

import processing.serial.*;

Serial port;

Boolean useArduino = true;

// On crée un tableau à 5 entrées,
// pour n'utiliser que les 3 dernières
// aux ids buttonState[2], buttonState[3], buttonState[4]
// Pourquoi ? Pour être coherent avec les variables
// Arduino, mais je reconnais que c'est bourrin :
// améliorez tout ça ! :)

Boolean[] buttonState = new Boolean[5];

PImage fond, iphone, param1on, param1off, param2on, param2off, param3on, param3off;

void setup() 
{
  size(960, 1080);

  if (useArduino) {
    printArray(Serial.list());
    
    // Le port Arduino est défini ici
    String portName = Serial.list()[5];
    
    port = new Serial(this, portName, 9600);
    port.clear();
    port.bufferUntil('\n');
  }

  for (int i = 2; i <= 4; i++) {
    // On définit par défaut l'etat des boutons à HIGH (true)
    buttonState[i] = true;
  }
  
  // On charge les images à afficher

  fond = loadImage("fond.jpg");
  iphone = loadImage("iphone.png");
  
  // Pour chaque parametre (= couple),
  // on a deux images : l'une pour l'état actif,
  // l'autre pour l'état inactif
  // (et vous remarquerez que les chiffres
  // ne correspondent plus, mea culpa)

  param1on = loadImage("param1on.png");
  param1off = loadImage("param1off.png");

  param2on = loadImage("param2on.png");
  param2off = loadImage("param2off.png");

  param3on = loadImage("param3on.png");
  param3off = loadImage("param3off.png");
}

void draw()
{
  background(0);
  image(fond, 0, 0);
  image(iphone, 250, 80);
  
  // Si le bouton "2" est pressé
  // ou que la LED doit être allumée

  if (buttonState[2] == true) {
    
    // On affiche l'image active
    image(param3on, 370, 350);
  }
  
  // Si le bouton "2" est relâché
  // ou que la LED doit être éteinte

  if (buttonState[2] == false) {
    
    // On affiche l'image inactive
    image(param3off, 370, 350);
  }


  if (buttonState[3] == true) {
    image(param2on, 370, 520);
  }
  if (buttonState[3] == false) {
    image(param2off, 370, 520);
  }


  if (buttonState[4] == true) {
    image(param1on, 370, 690);
  }
  if (buttonState[4] == false) {
    image(param1off, 370, 690);
  }
}


// On lit les données provenant de Arduino

void serialEvent(Serial port) {
  
  // On stocke la chaîne reçue dans la variable `get`
  String get = port.readStringUntil('\n');

  // Si Arduino nous envoie quelque chose :
  if (get != null) {
    
    // Utile à un moment :
    // println(get);
    
    // On explode la chaîne reçue
    // en séparant par `;` pour obtenir
    // 3 sections, sous la forme :
    
    // 2:HIGH;3:LOW;4:HIGH
    // > datas[0] = 2:HIGH
    // > datas[1] = 3:LOW
    // > datas[2] = 4:HIGH
    
    String[] datas = split(get, ';');

    // Si on en a bien 3
    // (Arduino pouvant en renvoyer 1 ou 2
    // au début du handshake, faussant alors le script)
    
    if (datas.length == 3) {

      // On analyse ensuite chaque section
      for (int i = 0; i < 3; i++) {
        
        // On explode la section par `:`
        // pour séparer l'id du couple
        // de l'état à affecter, sous la forme :
        
        // 2:HIGH
        // > data[0] = 2
        // > data[1] = HIGH
        
        String[] data = split(datas[i], ':');
        
        // Si on a bien deux parties à cette section :
        if (data.length == 2) {
          
          // On teste alors la deuxième partie
          
          // Si elle vaut `HIGH` :          
          if (trim(data[1]).equals("HIGH")) {
            
            // Alors l'état du bouton courant est `true`
            buttonState[i+2] = true;
          } else {
            
            // Sinon, l'état du bouton courant est `false`
            buttonState[i+2] = false;
          }
        }
      }
    }
  }
}

// Pour contrôler les LED depuis Processing,
// une mini-interface propose 3 boutons
// qui sont simulés en rendant réactif
// 3 zones de l'écran Processing :
// on définit donc ces 3 zones
// dans mouseClicked()

void mouseClicked() {
  // Chaque zone prend la largeur totale
  // du script (pour simplifier l'usage)
  
  // Si le clic se situe
  // entre 350px et 489px de haut
  
  if (mouseY > 350 && mouseY < 489) {
    // Alors on inverse l'état du bouton "2",
    // et donc de la LED "2"
    buttonState[2] = !buttonState[2];

    // Si l'état du bouton "2" est `true`
    if (buttonState[2] == true) {
      if (useArduino) {
        
        // Alors on envoie à Arduino
        // le nouvel état pour mettre à jour
        // et allumer la LED "2"
        
        port.write(21);
      }
    }

    // Si l'état du bouton "2" est `false`
    if (buttonState[2] == false) {
      if (useArduino) {
        
        // Alors on envoie à Arduino
        // le nouvel état pour mettre à jour
        // et éteindre la LED "2"
        
        port.write(20);
      }
    }
  }

  // Etc avec le second et le troisième bouton

  if (mouseY > 520 && mouseY < 659) {
    buttonState[3] = !buttonState[3];

    if (buttonState[3] == true) {
      if (useArduino) {
        port.write(31);
      }
    }

    if (buttonState[3] == false) {
      if (useArduino) {
        port.write(30);
      }
    }
  }

  if (mouseY > 690 && mouseY < 829) {
    buttonState[4] = !buttonState[4];

    if (buttonState[4] == true) {
      if (useArduino) {
        port.write(41);
      }
    }

    if (buttonState[4] == false) {
      if (useArduino) {
        port.write(40);
      }
    }
  }
}
