FILLEUL Mika - STAVRIDIS Adonis<br>
L3 S5 - CMI Image

# Documentation utilisateur

Ce projet d’algorithmes des réseaux, constitue une banque de données distribuée
avec des notions de respect de la qualité privée des données et étant tolérante
aux pannes en même temps. Dans cette documentation, vous est expliqué comment
est structuré le projet, comment le compiler, l'exécuter, l'utiliser et
éventuellement le modifier.

---

## Dossiers et Fichiers

Dans ce projet vous trouverez plusieurs dossiers et fichiers:
- **bdd** est un dossier dans lequel se trouve *acces.txt* qui est le fichier
contenant toutes les informations des utilisateurs.
- **include** est un dossier dans lequel se trouvent tout les fichiers headers
nécessaires au bon fonctionnement du code. Dans ce dossier il y a le fichier
*types.h* dans lequel se trouvent toutes les MACROS et types/structures
utilisées dans le projet.
- **src** est un dossier dans lequel se trouvent des dossiers, chacun contenant
le code pour un type de noeud de la banque de données: **appli** pour
une application cliente, **s_acces** pour le serveur d'accès et **s_data** pour
un serveur de données.
- *Makefile* est un fichier qui permet de compiler et lancer toutes les
exécutables facilement.
- *Rapport.pdf* est un fichier contenant toutes les informations nécessaires
pour comprendre comment fonctionne la banque de données.
- *README.md* est un fichier contenant toutes les informations nécessaires pour
comprendre comment utiliser la banque de données.

---

## Compilation et exécution

Pour travailler sur la banque de données, ouvrir un terminal et aller au
répertoire du projet.

Pour **compiler** la totatilé du projet, utiliser:

    make

Voici les commandes à écrire depuis le répertoire du projet, pour lancer les
exécutables respectivement d'une application/client, du serveur d'accès et d'un
serveur de données:

    ./bin/appli <PORT>
    ./bin/s_acces
    ./bin/s_data <PORT> <CHAMP>

Dans le *Makefile* il existe plusieures commandes qui permettent de facilement
lancer tout les exécutables. Voici toutes les commandes possibles:

    make test_simple
    make test_all
    make mem_simple
    make mem_all
    make t_appli1
    make t_appli2
    make t_s_acces
    make t_s_data_age1
    make t_s_data_age2
    make t_s_data_gender1
    make t_s_data_gender2

- **make test_simple** lance le serveur d'accès, un serveur de données AGE puis
GENDER, une application cliente, et enfin après 30 secondes un deuxième serveur
de données AGE, pour vérifier le bon fonctionnement de la synchronisation.
- **make test_all** lance le serveur d'accés, deux serveurs de données AGE, puis
deux serveurs de données GENDER, et enfin deux applications clientes.
- **make mem_simple** et **make mem_all** sont les commandes équivalentes à
make test_simple tet make test_all, mais avec l'utilisation de valgrind, pour
la vérification du bon fonctionnement du programme et de la mémoire.
- **make t_appli1** et **make t_appli2** sont des commandes pour lancer deux
clients différents avec deux ports prédefinis dans le *Makefile*.
- **make t_s_acces** lance le serveur d'accès.
- **make t_s_data_age1**, **make t_s_data_age2**, **make t_s_data_gender1** et
**make t_s_data_gender2** sont des commandes qui lancent des serveurs de données
avec des ports et champs différents.

Les terminaux créés avec les commandes **make test_simple**, **make test_all**,
**make mem_simple** et **make mem_all** sont des terminaux GNOME. Si vous
n'utilisez pas ce terminal, ou ne possédez pas la commande **gnome-terminal**
sur votre ordinateur, alors il faudra lancer les exécutables manuellement. Sinon
vous pouvez aussi télécharger le terminal GNOME.

---

## Application / Client

Au lancement, l'application va vérifier si le serveur d'accès est ligne. En cas
d'echec l'application se ferme, sinon elle continue.

Un menu s'affiche alors avec deux options: s'authentifier à la banque ou
quitter. Il faut donc entrer **1** pour s'authentifier ou **2** pour quitter
l'application.

Ensuite, il faut entrer vos coordonnées, donc votre nom d'utilisateur et votre
mot de passe.

Enfin, vous arrivez à l'étape des instructions, où vous pouvez lire, écrire ou
supprimer des données. Voici le format des instructions à écrire:

    lire <champ1> [<champ2> ...]
    ecrire <champ1:valeur1> [<champ2:valeur2> ...]
    supprimer

Pour quitter cette étape, entrer la commande:

    quit

## Serveur d'accès

Au lancement, le serveur d'accès va charger toutes les informations des
utilisateurs. Ensuite des clients et des serveurs de données peuvent se
connecter.

Tout au long de son fonctionnement, le serveur affiche ce qu'il est en train
d'exécuter.

Vous pouvez aussi utiliser les trois commandes suivantes pour respectivement,
afficher tous les nom d'utilisateur chargés, afficher les clients authentifiés
avec leur numéro de port et enfin afficher les serveurs de données connectés
avec leur numéro de port.

    logins
    clients
    datas

Pour éteindre le serveur proprement, utiliser la commande:

    quit

Il faudra attendre 30 secondes maximum, pour la fermeture du deuxième thread du
serveur.

## Serveur de données

Au lancement, le serveur de données va automatiquement tenter de se connecter au
serveur d'accés. S'il reussit alors le serveur continue, sinon il se ferme.

Si le serveur reussit à se connecter, mais qu'il n'est pas le premier de son
champ à l'être, alors ce serveur va se synchroniser avec un autre serveur
connecté de même champ. Sinon, le serveur se connecte normalement et attends des
demandes du serveur d'accès.

Tout au long de son fonctionnement, le serveur affiche ce qu'il est en train
d'exécuter.

Le serveur de données contient une liste chainée, qu'il est possible d'afficher
avec la commande:

    liste

Pour éteindre le serveur proprement, utiliser la commande:

    quit

---

## Modification des Ports

Si besoin, voici comment changer les numéros des ports utilisés dans ce projet.

Pour modifier les ports utilisés par le serveur d'accès, il faut modifier les
valeurs de **PORT_1** et **PORT_2**, qui se trouvent dans le fichier
*/include/types.h*.

Pour modifier les ports utilisés par tout les autres exécutables utilisant les
commandes du *Makefile*, alors il faut modifier les valeurs de **P_APPLI1**,
**P_APPLI2**, **P_DATA_AGE1**, **P_DATA_AGE2**, **P_DATA_GENDER1** et
**P_DATA_GENDER2**, qui se trouvent dans le *Makefile*.

Sinon il est toujours possible de lancer les applications clientes ou les
serveurs de données avec vos prores ports et champs.

---

## Nettoyage

Pour nettoyer ou supprimer tout les fichiers compilés, utiliser la commande:

    make clean

---

Merci d'avoir utilisé notre banque de données!
