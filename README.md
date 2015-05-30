# Boost My Spirit (HackMyChurch)
Projet « Boost My Spirit »

---

## Dispositif

Ce projet est une interface permettant de rappeler à l'utilisateur via son smartphone et via un objet connecté l'intention de prier, afin de rendre régulier la pratique religieuse dans un quotidien déjà saturé. L'utilisateur sait donc chaque jour qu'il doit prier ou consacrer une action qu'il a lui-même planifiée, depuis son smartphone et depuis l'objet connecté qu'il possède chez lui. Une fois l'action effectuée, l'utilisateur peut checker son action sur l'interface ou via un bouton associé sur l'objet connecté.

Techniquement, l'utilisateur possède une application (ou une webapp) qui montre l'état des LEDs de l'objet connecté. Il peut, une fois l'action effectuée, changer l'état de chaque LED via cette interface ; mais il peut également changer l'état de chaque LED depuis le bouton associé.

Au stade du prototype, la communication entre les LEDs et l'interface se fait via Processing/Arduino. L'application présentée est un rendu Processing qui intègre une image d'iPhone avec les zones réactives de l'interface (l'application était montrée sur un écran et non pas sur un smartphone). L'ordinateur affichant l'interface est relié à la carte Arduino pilotant les boutons et les LEDs. Chaque action `Bouton => LED` est gérée par le code Arduino téléversé sur la carte. De même, chaque action sur l'interface, et donc via Processing, est communiquée au code Arduino qui pilote l'éclairage des LEDs.

## Fonctionnement

Le dispositif prototype est constitué de :
* Un écran touch
* Un ordinateur
* Une carte Arduino, sa breadboard et son câble USB
* 3 LED
* 3 boutons poussoirs

## Électronique

![Schema Arduino](/Arduino/Schema.png?raw=true "Schema Arduino")

![Schema Arduino Zoom](/Arduino/Schema-Zoom.png?raw=true "Schema Arduino Zoom")

## Photos

![Light My Prayer](/Photos/LightMyPrayer1.jpg?raw=true)

![Light My Prayer](/Photos/LightMyPrayer2.jpg?raw=true)

La signalétique d'utilisation a été placée par dessus la structure en impression vinyle.

![Light My Prayer](/Photos/LightMyPrayer3.jpg?raw=true)

![Light My Prayer](/Photos/LightMyPrayer4.jpg?raw=true)

![Light My Prayer](/Photos/LightMyPrayer5.jpg?raw=true)

