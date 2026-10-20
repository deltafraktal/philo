Ce projet a été réalisé dans le cadre du cursus 42 par dgeara.

Philosophers
Description

Philosophers est un projet 42 qui introduit la programmation concurrente à travers un problème classique de l’informatique : le dîner des philosophes.

Plusieurs philosophes sont assis autour d’une table ronde. Chacun alterne entre trois états : manger, dormir et penser. Pour manger, un philosophe doit prendre les deux fourchettes placées de part et d’autre de lui, mais chaque fourchette ne peut être tenue que par un seul philosophe à la fois.

Le défi consiste à garder tous les philosophes en vie en évitant :

Les deadlocks (interblocages) : tout le monde attend et personne ne peut avancer
Les data races (accès concurrents) : plusieurs threads lisent/écrivent des données partagées sans protection
La famine : un philosophe ne mange jamais et finit par mourir

Chaque philosophe est un thread, chaque fourchette est protégée par un mutex, et un thread moniteur surveille les morts et les quotas de repas.

Concepts clés
Threads

Un thread est un chemin d’exécution indépendant à l’intérieur d’un programme. Plusieurs threads s’exécutent de manière concurrente et partagent la même mémoire.

Dans ce projet, chaque philosophe vit dans son propre thread et exécute la même boucle de façon indépendante :

prendre les fourchettes → manger → poser les fourchettes → dormir → penser → recommencer

Les threads sont créés avec pthread_create, et le thread principal les attend avec pthread_join avant de nettoyer.

Mutex

Un mutex est un verrou qui garantit qu’un seul thread à la fois peut accéder à une ressource partagée. Si un thread tente de verrouiller un mutex déjà détenu, il attend qu’il soit libéré.

Le thread A verrouille le mutex  →  Le thread B attend
Le thread A déverrouille         →  Le thread B peut continuer

Les mutex servent ici à protéger :

Les fourchettes : un seul philosophe peut tenir une fourchette à la fois
Les données partagées : heure du dernier repas, nombre de repas, état de la simulation
L’affichage : pour que les messages imprimés ne se chevauchent pas
Data races

Une data race se produit lorsque deux threads ou plus accèdent à la même variable en même temps, et qu’au moins l’un d’eux y écrit, sans qu’aucun mutex ne protège l’accès. Le résultat est imprévisible.

Dans ce projet, chaque variable partagée n’est lue et écrite que lorsque le mutex approprié est détenu.

Deadlocks

Si chaque philosophe prend d’abord sa fourchette gauche, tous en tiennent une et attendent indéfiniment la seconde : personne ne peut avancer. C’est un deadlock.

Pour l’éviter, les philosophes pairs et impairs prennent leurs fourchettes dans l’ordre inverse, ce qui brise la symétrie.

Le moniteur

Le moniteur s’exécute dans le thread principal et vérifie deux choses en boucle :

Un philosophe a-t-il dépassé time_to_die sans manger ? → afficher died, arrêter la simulation
Tous les philosophes ont-ils atteint le quota de repas optionnel ? → arrêter la simulation
Instructions
Compilation
bash
make

Cette commande produit l’exécutable philo. Les règles Makefile standard sont disponibles :

bash
make clean    # supprime les fichiers objets
make fclean   # supprime les fichiers objets + l'exécutable
make re       # fclean + make
Exécution
bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

Toutes les valeurs de temps sont en millisecondes. Le dernier argument est optionnel.

Arguments
Argument	Description
number_of_philosophers	Nombre de philosophes (et de fourchettes)
time_to_die	Temps en ms avant qu’un philosophe meure sans avoir mangé
time_to_eat	Temps en ms que passe un philosophe à manger
time_to_sleep	Temps en ms que passe un philosophe à dormir
number_of_times_each_philosopher_must_eat	(optionnel) La simulation s’arrête quand tous ont atteint ce nombre de repas
Exemples
bash
# 5 philosophes, sans quota de repas
./philo 5 800 200 200

# S'arrête quand chaque philosophe a mangé au moins 7 fois
./philo 5 800 200 200 7

# Un seul philosophe : ne peut jamais manger (une seule fourchette), meurt après time_to_die
./philo 1 200 100 100
Format de sortie
timestamp_in_ms philosopher_id has taken a fork
timestamp_in_ms philosopher_id is eating
timestamp_in_ms philosopher_id is sleeping
timestamp_in_ms philosopher_id is thinking
timestamp_in_ms philosopher_id died
Tests utiles

Vérifier les fuites mémoire :

bash
valgrind --leak-check=full ./philo 5 800 200 200 3

Vérifier les data races :

bash
valgrind --tool=helgrind ./philo 5 800 200 200 3

Provoquer une mort (un philosophe doit mourir, et aucun message ne doit apparaître après died) :

bash
./philo 4 310 200 100

Test de charge avec beaucoup de threads :

bash
./philo 200 800 200 200 2
Ressources
Threads et mutex
POSIX Threads Programming — LLNL
Documentation de pthread_create
Documentation de pthread_mutex_lock
Code Vault — Playlist Threads (YouTube)
Le problème
Le dîner des philosophes par Oceano (YouTube)
Problème du dîner des philosophes — Wikipédia
Utilisation de l’IA

Claude (Anthropic) a été utilisé pendant ce projet comme outil d’apprentissage, notamment pour :

Expliquer progressivement les threads, mutex, deadlocks et data races avec des exemples concrets
Suggérer des scénarios de test pertinents et aider à interpréter leurs résultats
Aider à vérifier les cas limites (philosophe unique, échec partiel de création de threads, déverrouillage des mutex dans les chemins d’erreur)