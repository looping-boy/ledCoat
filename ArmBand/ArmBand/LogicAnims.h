#ifndef LOGIC_ANIMS_H
#define LOGIC_ANIMS_H

// --------------------------------------------------------------------------------------------------------------------------------------
// LINE OF PATTERN 1 --------------------------------------------------------------------------------------------------------------------

void animFullStatic() {
  CHSV colorValue = CHSV(hue, 255, brightness);
  for (uint8_t i = 0; i < totalLine * totalColumn; i++) {
    leds[1][i] = colorValue;
  }
  // Because static
  animDone = true;
}

void animAlertFull(long currentTime) {
  float barCycleTime = (60000 / bpm) * (tweakBPM / 4);
  float phase = (float)(currentTime % (uint32_t)barCycleTime) / barCycleTime;
  uint8_t j = (uint8_t)((sin(phase * 2 * 3.14159265359) + 1) * (brightness / 2));

  CHSV colorValue = CHSV(hue, 255, j);
  
  for (uint8_t i = 0; i < totalLine * totalColumn; i++) {
    leds[1][i] = colorValue;
  }
}

void animDownLine(long currentTime, long startAnimationTime) {
  float barCycleTime = (60000 / bpm) * (tweakBPM / 16) * tweakPhase;
  uint8_t pulseBrightness = (uint8_t) brightness * 1.5;
  // Iterate over two or more
  //for (int phase = 0; phase < tweakPhase; phase++) {
    //uint8_t pos = (uint8_t)(((((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * totalLine) / barCycleTime) + (phase * (totalLine / tweakPhase))) % totalLine;
    for (int k = 24; k < 48; k++) {
        leds[1][k] = CHSV(200, 255, 255);
    }
  //} 
}

void animVerticalRainbow(long currentTime, long startAnimationTime) {
  // Calcul de la durée d'un cycle complet pour la barre
  float barCycleTime = ((60000 / bpm)) * (tweakBPM / 4);

  // Calcul de la position actuelle de la barre en fonction du temps
  uint8_t j = (uint8_t)(((currentTime - startAnimationTime) % (uint32_t)barCycleTime) * totalColumn / barCycleTime);

  // Luminosité réduite pour la barre
  uint8_t lowerBrightness = (uint8_t)(brightness * 0.5);

  // Boucle sur chaque ligne de la matrice LED
  for (int row = 0; row < totalLine; row++) {
    int index;

    // Calcul de l'index de la LED à allumer en fonction du motif zigzag
    if (row % 2 == 0) {
      index = row * (totalColumn - 1) + j;  // Ligne paire (gauche à droite)
    } else {
      index = row * (totalColumn - 1) + (totalColumn - 1 - j);  // Ligne impaire (droite à gauche)
    }

    // Affecter la couleur à l'index calculé
    leds[1][index] = CHSV(hue, 255, lowerBrightness);
  }

  // Affichage des LEDs
  FastLED.show();
}

#endif