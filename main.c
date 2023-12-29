#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CARS 100
#define MAX_HISTORY 100
#define PRIX_PAR_JOUR 50 


typedef struct {
    int id;
    char description[50];
    int disponible;
} Voiture;


typedef struct {
    int idVoiture;
    char date[20];
    int duree;
    char nomPersonne[50]; 
    char prenomPersonne[50];  
    int carteIdentite;     
} HistoriqueLocation;


void afficherMenu();
void afficherVoituresDisponibles(Voiture voitures[], int nombre);
void afficherHistoriqueLocation(Voiture voitures[], HistoriqueLocation historique[], int nombre);
void louerVoiture(Voiture listeVoitures[], int nombreVoitures, HistoriqueLocation historique[], int *nombreHistorique);

void afficherDetailsVoiture(Voiture voitures[], int nombre);
void supprimerVoitureDefaillante(Voiture voitures[], int *nombre);
void modifierVoiture(Voiture voitures[], int nombre);
void traiterRetour(Voiture voitures[], HistoriqueLocation historique[], int *nombreHistorique);
void rechercherVoituresDisponibles(Voiture voitures[], int nombre);
void rechercherParTypeCarburant(Voiture voitures[], int nombre);
void rechercherParTypeVoiture(Voiture voitures[], int nombre);
void afficherVoituresLouees(Voiture voitures[], HistoriqueLocation historique[], int nombreHistorique);

float calculerPrixLocation(int duree);






int main() {
    system("cls");
    system("color D");
    Voiture voitures[] = {
        {1, "Toyota Camry - Berline - 2022 - Essence", 1},
        {2, "Honda Accord - Berline - 2021 - Essence", 0},             // Non disponible
        {3, "Ford Mustang - Coupe - 2023 - Essence", 1},              // Disponible
        {4, "Chevrolet Malibu - Berline - 2022 - Essence", 1},        // Disponible
        {5, "Volkswagen Golf - Hayon - 2022 - Diesel", 0},            // Non disponible
        {6, "BMW Serie 3 - Berline - 2022 - Essence", 1},             // Disponible
        {7, "Mercedes-Benz Classe C - Berline - 2023 - Essence", 1},  // Disponible
        {8, "Audi A4 - Berline - 2022 - Essence", 0},                // Non disponible
        {9, "Nissan Altima - Berline - 2022 - Essence", 1},          // Disponible
        {10, "Hyundai Sonata - Berline - 2022 - Essence", 1}         // Disponible
    };
    HistoriqueLocation historique[] = {
    {1, "2023-01-15", 7, "John", "Doe", 12345678},
    {2, "2023-02-20", 10, "Alice", "Smith", 87654321},
    {3, "2023-03-25", 5, "Bob", "Johnson", 98765432}
};

    int nombreVoitures = sizeof(voitures) / sizeof(voitures[0]);
    int nombreHistorique = sizeof(historique) / sizeof(historique[0]);
    int choix;

    do {
        afficherMenu();
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                afficherVoituresDisponibles(voitures, nombreVoitures);
                break;
      case 2:
    afficherHistoriqueLocation(voitures, historique, nombreHistorique);
    break;

            case 3:
                louerVoiture(voitures, nombreVoitures, historique, &nombreHistorique);
                break;
            case 4:
                afficherDetailsVoiture(voitures, nombreVoitures);
                break;
            case 5:
                supprimerVoitureDefaillante(voitures, &nombreVoitures);
                break;
            case 6:
                modifierVoiture(voitures, nombreVoitures);
                break;
            case 7:
                traiterRetour(voitures, historique, &nombreHistorique);
                break;
            case 8:
                rechercherVoituresDisponibles(voitures, nombreVoitures);
                break;
            case 9:
                afficherVoituresLouees(voitures, historique, nombreHistorique);
                break;
            case 10:
                printf("Fermeture de l'application. Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez r essayer.\n");
        }

    } while (choix != 10);

    return 0;
}

void afficherMenu() {
    printf("                                    --------------------------------------------------------  \n");
    printf("                                     BIENVENUE DANS NOTRE SYSTEME DE LOCATION DES VOITURES  \n");
    printf("                                    --------------------------------------------------------  \n");
    printf("                                                                                                        \n");
    printf("                                                                                                        \n");
    printf("                                                                                                        \n");
    printf("                                                                                                        \n");

    printf("                                                       Menu de l'application E-Cars    \n");
    printf("                                    ............................................................  \n");

    printf("                                                      1. Afficher les voitures disponibles\n");
    printf("                                                      2. Afficher l'historique de location\n");
    printf("                                                      3. Louer une voiture\n");
    printf("                                                      4. Afficher les details d'une voiture\n");
    printf("                                                      5. Supprimer une voiture defaillante\n");
    printf("                                                      6. Modifier les informations d'une voiture\n");
    printf("                                                      7. gerer le retour d'une voiture\n");
    printf("                                                      8. Rechercher des voitures disponibles\n");
    printf("                                                      9. Afficher les voitures louees\n");
    printf("                                                      10. Quitter\n");
}

void afficherVoituresDisponibles(Voiture voitures[], int nombre) {
    printf("Affichage des voitures disponibles :\n");
    printf("Descriptions detaillees des voitures :\n");

    for (int i = 0; i < nombre; i++) {
        printf("ID de la voiture : %d, Description : %s, Disponible : %s\n", voitures[i].id, voitures[i].description, voitures[i].disponible ? "Oui" : "Non");
    }
}



void afficherHistoriqueLocation(Voiture voitures[], HistoriqueLocation historique[], int nombre) {
    printf("\nHistorique de location :\n");

    if (nombre == 0) {
        printf("Aucun historique de location disponible.\n");
        return;
    }

    for (int i = 0; i < nombre; i++) {
        printf("Enregistrement de location %d :\n", i + 1);
        printf("ID de la voiture : %d\n", historique[i].idVoiture);

        printf("Voiture : %s\n", voitures[historique[i].idVoiture - 1].description);
        printf("Date : %s\n", historique[i].date);
        printf("Nom de la personne : %s\n", historique[i].nomPersonne);
        printf("Prenom de la personne : %s\n", historique[i].prenomPersonne);
        printf("Numero de carte d'identite : %d\n", historique[i].carteIdentite);
        printf("Duree : %dj\n", historique[i].duree);
        printf("------------------------\n");
    }
}

float calculerPrixLocation(int duree) {

    float prixParJour = PRIX_PAR_JOUR;
    float prixLocation = duree * prixParJour;

    return prixLocation;
}




void louerVoiture(Voiture listeVoitures[], int nombreVoitures, HistoriqueLocation historique[], int *nombreHistorique) {
    int idSelectedVoiture;
    printf("Entrez l'ID de la voiture que vous souhaitez louer : ");
    scanf("%d", &idSelectedVoiture);


    if (idSelectedVoiture < 1 || idSelectedVoiture > nombreVoitures) {
        printf("ID de voiture invalide. Veuillez entrer un ID de voiture valide.\n");
        return;
    }


    if (listeVoitures[idSelectedVoiture - 1].disponible == 0) {
        printf("La voiture selectionnee n'est pas disponible   la location.\n");
        return;
    }

    // Demander   l'utilisateur d'entrer la date
    char date[20];
    printf("Entrez la date de location (AAAA-MM-JJ) : ");
    scanf("%s", date);

    int dureeLocation;
    printf("Entrez la duree de la location (en jours) : ");
    scanf("%d", &dureeLocation);

    // Demander   l'utilisateur d'entrer le nom, le pr nom et la carte d'identit 
    char nomPersonne[50];
    char prenomPersonne[50];
    int carteIdentite;

    printf("Entrez votre nom : ");
    scanf(" %[^\n]s", nomPersonne);

    printf("Entrez votre prenom : ");
    scanf(" %[^\n]s", prenomPersonne);

    printf("Entrez votre numero de carte d'identite : ");
    scanf("%d", &carteIdentite);

    // Ajouter l'entr e   l'historique de location
    strcpy(historique[*nombreHistorique].nomPersonne, nomPersonne);
    strcpy(historique[*nombreHistorique].prenomPersonne, prenomPersonne);
    historique[*nombreHistorique].carteIdentite = carteIdentite;
    historique[*nombreHistorique].idVoiture = idSelectedVoiture;
    strcpy(historique[*nombreHistorique].date, date);
    historique[*nombreHistorique].duree = dureeLocation;
    (*nombreHistorique)++;

    // Mettre   jour la disponibilit  de la voiture
    listeVoitures[idSelectedVoiture - 1].disponible = 0;

    // Calculer le prix de la location
       float prixLocation = calculerPrixLocation(dureeLocation);
    printf("                                                   Voiture louee avec succes !\n");
    printf("                                                   Prix de la location : $%.2f\n", prixLocation);
}

void afficherDetailsVoiture(Voiture voitures[], int nombre) {
    int idVoiture;

    // Demander   l'utilisateur d'entrer l'ID de la voiture
    printf("Entrez l'ID de la voiture pour afficher les details : ");
    scanf("%d", &idVoiture);

    // V rifier un ID de voiture valide
    if (idVoiture < 1 || idVoiture > nombre) {
        printf("ID de voiture invalide.  entrer un ID de voiture valide.\n");
        return;
    }

    // Afficher les d tails de la voiture s lectionn e
    printf("\nDetails de la voiture :\n");
    printf("ID de la voiture : %d\n", voitures[idVoiture - 1].id);
    printf("Description : %s\n", voitures[idVoiture - 1].description);
    printf("Disponible : %s\n", voitures[idVoiture - 1].disponible ? "Oui" : "Non");
}


void supprimerVoitureDefaillante(Voiture voitures[], int *nombre) {
    afficherVoituresDisponibles(voitures, *nombre);

    int idVoiture;
    printf("Entrez l'ID de la voiture a supprimer : ");
    scanf("%d", &idVoiture);

    // V rifier un ID de voiture valide
    if (idVoiture < 1 || idVoiture > *nombre) {
        printf("ID de voiture invalide.  entrer un ID de voiture valide.\n");
        return;
    }

    // Afficher les d tails de la voiture   supprimer
    printf("\n Details de la voiture a supprimer :\n");
    printf("ID de la voiture : %d\n", voitures[idVoiture - 1].id);
    printf("Description : %s\n", voitures[idVoiture - 1].description);
    printf("Disponible : %s\n", voitures[idVoiture - 1].disponible ? "Oui" : "Non");

    // Demander la confirmation de l'utilisateur
    int confirme;
    printf("\n Etes-vous sur de vouloir supprimer cette voiture ? (1 pour Oui, 0 pour Non) : ");
    scanf("%d", &confirme);

    if (!confirme) {
        printf("Suppression de la voiture annulee.\n");
        return;
    }


    for (int i = idVoiture - 1; i < *nombre - 1; i++) {
        voitures[i] = voitures[i + 1];
        // Mettre   jour les ID des voitures restantes
        voitures[i].id = i + 1;
    }

    // D cr menter le nombre total de voitures
    (*nombre)--;

    printf("                                                  Voiture supprimee avec succes. Total de voitures : %d\n", *nombre);
}

void modifierVoiture(Voiture voitures[], int nombre) {
    afficherVoituresDisponibles(voitures, nombre);

    int idVoiture;
    printf("Entrez l'ID de la voiture a modifier : ");
    scanf("%d", &idVoiture);

    // V rifier un ID de voiture valide
    if (idVoiture < 1 || idVoiture > nombre) {
        printf("ID de voiture invalide.  entrer un ID de voiture valide.\n");
        return;
    }

    // Afficher les d tails actuels de la voiture
    printf("\nDetails actuels de la voiture :\n");
    printf("ID de la voiture : %d\n", voitures[idVoiture - 1].id);
    printf("Description : %s\n", voitures[idVoiture - 1].description);
    printf("Disponible : %s\n", voitures[idVoiture - 1].disponible ? "Oui" : "Non");

    // Autoriser l'utilisateur   saisir de nouvelles informations
    printf("\nEntrez la nouvelle description : ");
    scanf(" %[^\n]s", voitures[idVoiture - 1].description);

    // Afficher un message de confirmation
    printf("                                                          Informations de la voiture modifiees avec succes.\n");
}

void traiterRetour(Voiture voitures[], HistoriqueLocation historique[], int *nombreHistorique) {
    // Afficher les voitures actuellement lou es
    printf("Voitures actuellement louees :\n");
    for (int i = 0; i < *nombreHistorique; i++) {
        printf("Enregistrement de location %d :\n", i + 1);
        printf("ID de la voiture : %d\n", historique[i].idVoiture);
        printf("Date : %s\n", historique[i].date);
        printf("------------------------\n");
    }

    // V rifier si l'historique de location est vide
if (*nombreHistorique == 0) {
    printf("Aucune voiture actuellement louee.\n");
    return;
}

    int idVoiture;
    printf("Entrez l'ID de la voiture   traiter pour le retour : ");
    scanf("%d", &idVoiture);

    // V rifier un ID de voiture valide
    if (idVoiture < 1 || idVoiture > *nombreHistorique) {
        printf("ID de voiture invalide. entrer un ID de voiture valide.\n");
        return;
    }

    // Mettre   jour la disponibilit  de la voiture
    voitures[historique[idVoiture - 1].idVoiture - 1].disponible = 1;

    // Supprimer l'entr e de l'historique de location
    for (int i = idVoiture - 1; i < *nombreHistorique - 1; i++) {
        historique[i] = historique[i + 1];
    }

    // D cr menter le nombre total d'entr es dans l'historique de location
    (*nombreHistorique)--;

    printf("                                           Retour de voiture traite avec succes.\n");
}

void rechercherVoituresDisponibles(Voiture voitures[], int nombre) {
    // Demander   l'utilisateur de choisir la m thode de recherche
    printf("Choisissez la methode de recherche :\n");
    printf("1. Rechercher par type de carburant\n");
    printf("2. Rechercher par type de voiture\n");
    int choix;
    printf("Entrez votre choix : ");
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            rechercherParTypeCarburant(voitures, nombre);
            break;
        case 2:
            rechercherParTypeVoiture(voitures, nombre);
            break;
        default:
            printf("Choix invalide. Retour au menu principal.\n");
    }
}

void rechercherParTypeCarburant(Voiture voitures[], int nombre) {
    char typeCarburant[50];
    printf("Entrez le type de carburant a rechercher : ");
    scanf(" %[^\n]s", typeCarburant);

    printf("\nResultats de la recherche :\n");

    int found = 0;


    for (int i = 0; typeCarburant[i]; i++) {
        typeCarburant[i] = toupper(typeCarburant[i]);
    }

    for (int i = 0; i < nombre; i++) {

        char carburantUpper[50];
        strcpy(carburantUpper, voitures[i].description);
        for (int j = 0; carburantUpper[j]; j++) {
            carburantUpper[j] = toupper(carburantUpper[j]);
        }

        if (strstr(carburantUpper, typeCarburant) != NULL) {
            printf("ID de la voiture : %d, Description : %s, Disponible : %s\n", voitures[i].id, voitures[i].description, voitures[i].disponible ? "Oui" : "Non");
            found = 1;
        }
    }

    if (!found) {
        printf("Aucun resultat trouve pour le type de carburant : %s\n", typeCarburant);
    }
}




void rechercherParTypeVoiture(Voiture voitures[], int nombre) {
    char typeVoiture[50];
    printf("Entrez le type de voiture a rechercher : ");
    scanf(" %[^\n]s", typeVoiture);

    printf("\nResultats de la recherche :\n");

    int found = 0;


    for (int i = 0; typeVoiture[i]; i++) {
        typeVoiture[i] = toupper(typeVoiture[i]);
    }

    for (int i = 0; i < nombre; i++) {

        char descriptionUpper[50];
        strcpy(descriptionUpper, voitures[i].description);
        for (int j = 0; descriptionUpper[j]; j++) {
            descriptionUpper[j] = toupper(descriptionUpper[j]);
        }

        if (strstr(descriptionUpper, typeVoiture) != NULL) {
            printf("ID de la voiture : %d, Description : %s, Disponible : %s\n", voitures[i].id, voitures[i].description, voitures[i].disponible ? "Oui" : "Non");
            found = 1;
        }
    }

    if (!found) {
        printf("Aucun resultat trouve pour le type de voiture : %s\n", typeVoiture);
    }
}


void afficherVoituresLouees(Voiture voitures[], HistoriqueLocation historique[], int nombreHistorique) {
    printf("\nVoitures actuellement louees :\n");

    for (int i = 0; i < nombreHistorique; i++) {
        int idVoiture = historique[i].idVoiture;

        printf("Enregistrement de location %d :\n", i + 1);
        printf("ID de la voiture : %d\n", idVoiture);
        printf("Description : %s\n", voitures[idVoiture - 1].description);
        printf("Date : %s\n", historique[i].date);
        printf("------------------------\n");
    }

    if (nombreHistorique == 0) {
        printf("Aucune voiture actuellement louee.\n");
    }
}


