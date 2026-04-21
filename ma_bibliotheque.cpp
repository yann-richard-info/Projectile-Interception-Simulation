#include <iostream>
#include <cmath>

using namespace std;
//Constante
const float G = 9.81;
const float PI= 3.14159265359;
/** Conversion degrés en radians **/
float Util_Deg_2_Rad(float input_angle_deg)
{
    return input_angle_deg * PI / 180.0;
}



/** Projection de la vitesse**/
float Util_Projeter_Axe_X(float input_vitesse, float input_angle)/** sur l'axe X **/
{
    float angle_rad = Util_Deg_2_Rad(input_angle);//rappel de la fonction de convertion en radian
    return input_vitesse * cos(angle_rad);
}
float Util_Projeter_Axe_Z(float input_vitesse, float input_angle)/** sur l'axe Y **/
{
    float angle_rad = Util_Deg_2_Rad(input_angle);
    return input_vitesse * sin(angle_rad);
}



/** Calcul de l'altitude d'une trajectoire z(x) **/
float Calculer_Z_Trajectoire(float input_x,float input_alpha,float input_v0,float input_x0,float input_z0)
{
    float zTrajectoire ;
    float alpha_rad = Util_Deg_2_Rad(input_alpha);
    zTrajectoire = -(G * pow(input_x - input_x0, 2))/ (2 * pow(input_v0, 2) * pow(cos(alpha_rad), 2))+(input_x - input_x0) * tan(alpha_rad)+input_z0;

    return zTrajectoire;
}



/** Calcul de l'angle de tir de l'intercepteur **/
float Calculer_Alpha_Intercepteur(float input_xi,  float input_yi_prime, float input_alpha0, float input_v0, float input_x0, float input_z0, float input_vi)
{
    float zi,a,b,c,delta,X,alpha_rad,alpha_deg;//Déclaration des variables

    zi = Calculer_Z_Trajectoire(input_xi, input_alpha0, input_v0, input_x0, input_z0);
    a = -(G * pow(input_yi_prime, 2)) / (2 * pow(input_vi, 2));
    b = input_yi_prime;
    c = a - zi;
    delta = b*b - 4 * a * c;
    X = (-b + sqrt(delta)) / (2 * a);//Résolution de l'équation x1
    alpha_rad = atan(X);//Calcul de l'angle x1
    alpha_deg = alpha_rad * 180 / PI;//Conversion en degrés de l'angle x1

    return alpha_deg;
}



/** Calcul du temps de vol **/
float Calculer_Temps_Vol(float input_x, float input_alpha, float input_v0, float input_x0, float input_z0)
{
    float vx = Util_Projeter_Axe_X(input_v0, input_alpha);
    return (input_x - input_x0) / vx;
}



/** Calcul du décalage de tir **/
float Calculer_Decalage_Temps(float input_t_vol_projectile, float input_t_vol_intercepteur)
{
    return input_t_vol_projectile - input_t_vol_intercepteur;
}


bool Rechercher_Existence_Solution(float input_xi,float input_yi_prime,float input_alpha0,float input_v0,float input_x0,float input_z0,float input_vi,float input_liste_alpha_i[])
{
    float z_proj;
    float z_inter;
    float prev_z_inter;

    float alpha0_rad;
    float alpha_rad;
    bool first = true;
    alpha0_rad = Util_Deg_2_Rad(input_alpha0);

    z_proj = -(G / (2 * pow(input_v0, 2) * pow(cos(alpha0_rad), 2)))
             * pow((input_xi - input_x0), 2)
             + tan(alpha0_rad) * (input_xi - input_x0)
             + input_z0;


    for (int i = 0; i <= 90; i++)
    {
        alpha_rad = Util_Deg_2_Rad(input_liste_alpha_i[i]);

        z_inter = -(G / (2 * pow(input_vi, 2) * pow(cos(alpha_rad), 2)))
                  * pow(input_yi_prime, 2)
                  + input_yi_prime * tan(alpha_rad);

        if (!first)
        {
            if ((prev_z_inter <= z_proj && z_inter >= z_proj) ||
                (prev_z_inter >= z_proj && z_inter <= z_proj))
            {
                cout << "Encadrement trouve entre "
                     << input_liste_alpha_i[i - 1]
                     << "° et "
                     << input_liste_alpha_i[i]
                     << "°" << endl;

                return true;
            }
        }

        prev_z_inter = z_inter;
        first = false;
    }

    cout <<"Aucun encadrement trouve :-("<< endl<<"________________________________________________________________________________________________________________________"<< endl<< endl<< "Ecrivez de nouveau parametre"<< endl<< endl;

    return false;
}




