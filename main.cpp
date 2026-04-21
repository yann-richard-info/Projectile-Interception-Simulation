#include <iostream>
using namespace std;
#include "ma_bibliotheque.h"
                                        /** Déclaration et affectation des variables constantes **/
const float G_PESANTEUR = 9.81;

int main()
{
    cout << endl<< endl<< "                                      Simulateur d'un intercepteur de missile"<< endl<<"________________________________________________________________________________________________________________________"<< endl<< endl<< endl;
    bool solution=0;
    float v0,x0,z0,alpha0,xi,yi_prime,vi,zi,alpha_i,temps_projectile,temps_intercepteur,decalage_temps=0;//déclaration des variables
    float alpha_liste[91];
    for (int i = 0; i <= 90; i++) {alpha_liste[i] = i;}
    do
        {
                                        /** Demande à l'utilisateur les paramètres **/


        cout << "Entrer la vitesse initiale du projectile v0 (m/s) : ";
        cin >> v0;
        cout << "Entrer la position initiale x0 (m) : ";
        cin >> x0;
        cout << "Entrer la hauteur initiale z0 (m) : ";
        cin >> z0;
        cout << "Entrer l'angle de tir alpha0 (deg) : ";
        cin >> alpha0;
        cout << "Entrer la position d'interception xi (m) : ";
        cin >> xi;
        cout << "Entrer la distance yi' (m) de l'intercepteur : ";
        cin >> yi_prime;
        cout << "Entrer la vitesse initiale de l'intercepteur vi (m/s) : ";
        cin >> vi;
        cout<< endl;
                                            /** Zone d'appel de fonction **/

        solution=Rechercher_Existence_Solution(xi,yi_prime,alpha0,v0,x0,z0,vi,alpha_liste);// calcul de possibilité de solution avec les paramètres choisit
        zi = Calculer_Z_Trajectoire(xi, alpha0, v0, x0, z0); // Calcul de la hauteur (zi) du projectile au point xi
        alpha_i = Calculer_Alpha_Intercepteur(xi, yi_prime, alpha0, v0, x0, z0, vi);// Calcul de l'angle de tir de l'intercepteur (ai)
        temps_projectile = Calculer_Temps_Vol(xi, alpha0, v0, x0, z0);// Temps de vol du projectile
        temps_intercepteur = Calculer_Temps_Vol(yi_prime, alpha_i, vi, 0, 0);// Temps de vol de l'intercepteur pour atteindre le missile à xi
        decalage_temps = Calculer_Decalage_Temps(temps_projectile, temps_intercepteur);     // Calcul du décalage de tir

        if(decalage_temps<0)
                {
                cout<<endl<<"Cependant"<<endl<<"L'intercepeteur n'a pas reussi a atteindre le missile a temps, cela ne fonctionne donc pas :("<<endl<<endl<<"________________________________________________________________________________________________________________________"<< endl<< endl<< "Ecrivez de nouveau parametre"<< endl<< endl;
                }
        }
    while(solution == 0 || decalage_temps<0 );
                                            /** Zone de calcul **/
    cout << endl<< endl<< "                                                     ZONE DE CALCUL"<<endl<<"________________________________________________________________________________________________________________________"<< endl<< endl;
    cout << endl;
    cout << "Altitude du projectile au point d'interception : " << zi << " m" << endl;
    cout << "Angle de tir de l'intercepteur : " << alpha_i << " deg" << endl;
    cout << "Temps de vol du projectile : " << temps_projectile << " s" << endl;
    cout << "Temps de vol de l'intercepteur : " << temps_intercepteur << " s" << endl;
    cout << "Decalage entre les tirs : " << decalage_temps << " s" << endl;
    cout << endl<<"Interception reussite :)"<< endl<< endl<<"________________________________________________________________________________________________________________________"<< endl;
    return 0;
}
