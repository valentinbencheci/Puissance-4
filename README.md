# Puissance-4

**Puissance 4** (appelé aussi parfois 4 en ligne) est un jeu de stratégie combinatoire
abstrait


**Par rapport au jeu traditionnel, le projet réalisé permet en plus de :**
```
• Tourner le plateau de 90 degrés sur la gauche ;
• Tourner le plateau de 90 degrés sur la droite ;
• Retourner le plateau.
```

**Il existe 3 mode de jeu :**
```
• Player VS Player;
• Player VS AI;
• AI VS AI.

Pour l'implementation d'AI il est utilisé l'algorithme MinMax.
```

**L'organisation des menus :**
```
• mainMenu;
• gameTypeMenu;
• gameMoveMenu.
```
![mainMenu](/img/mainMenu.png)
![mainMenu](/img/gameTypeMenu.png)
![mainMenu](/img/gameMoveMenu.png)

**Les codes d'erreurs :**

| Code  | Erreur                               |
| ----- |:------------------------------------:|
| 101   | mauvaise nickname_1                  |
| 102   | mauvaise nickname_2                  |
| 103   | mauvaise couleur_1                   |
| 301   | le jeton n'a pas été place           |
| 401   | il n'y a pas de parties sauvegardées |
| 501   | il n'y a pas de statistique          |