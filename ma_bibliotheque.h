#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
/** Fonctions utilitaires **/

float Util_Deg_2_Rad(float input_angle_deg);
float Util_Projeter_Axe_X(float input_vitesse, float input_angle);
float Util_Projeter_Axe_Z(float input_vitesse, float input_angle);

/** Fonctions de simulation physique **/

float Calculer_Z_Trajectoire( float input_x, float input_alpha, float input_v0, float input_x0, float input_z0);
float Calculer_Alpha_Intercepteur(float input_xi, float input_yi_prime, float input_alpha0, float input_v0, float input_x0, float input_z0, float input_vi);
float Calculer_Temps_Vol( float input_x, float input_alpha, float input_v0, float input_x0, float input_z0);
float Calculer_Decalage_Temps( float input_t_vol_projectile, float input_t_vol_intercepteur);
bool Rechercher_Existence_Solution(float input_xi, float input_yi_prime, float input_alpha0, float input_v0, float input_x0, float input_z0, float input_vi, float input_liste_alpha_i[]);
#endif
